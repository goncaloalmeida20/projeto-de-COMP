#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meta4.h"
#include "symbol_table.h"

int gen_llvmir(Node *node);

char *curr_return_type = NULL;
VarCounter *var_counter = NULL, *var_counter_global = NULL;
int counter = -1, label_counter = 0;

char* conv_escape(char *s, int *new_len){
    *new_len = 0;
    int esc_counter = 0;
    char *aux, *new_aux;
    for(aux = s+1; *(aux+1); aux++, (*new_len)++){
        if(*aux == '\\'){
            esc_counter += 2;
            aux++;
        }
        else if(*aux == '%'){
            esc_counter++;
            (*new_len)++;
        }
    }
    char *new_s = (char*) malloc(sizeof(char) * (strlen(s) + 1 + esc_counter));
    if(!new_s){
        printf("ERROR MALLOC CONV ESC\n");
        return NULL;
    }
    for(aux = s + 1, new_aux = new_s; *(aux+1); aux++){
        if(*aux == '\\'){
            *new_aux++ = *aux++;
            switch(*aux){
                case 'f':
                    *new_aux++ = '0';
                    *new_aux++ = 'C';
                    break;
                case 'n':
                    *new_aux++ = '0';
                    *new_aux++ = 'A';
                    break;
                case 'r':
                    *new_aux++ = '0';
                    *new_aux++ = 'D';
                    break;
                case 't':
                    *new_aux++ = '0';
                    *new_aux++ = '9';
                    break;
                case '\\':
                    *new_aux++ = '5';
                    *new_aux++ = 'C';
                    break;
                case '\"':
                    *new_aux++ = '2';
                    *new_aux++ = '2';
                    break;
            }
        }
        else if(*aux == '%'){
            *new_aux++ = '%';
            *new_aux++ = '%';
        }
        else *new_aux++ = *aux;
    }
    *new_aux = 0;
    return new_s;
}

int counter_size(){
    int aux = counter, size = 0;
    for(; aux > 0; aux /= 10, size++);
    return size;
}

VarCounter* search_var_counter(char *var){
    for(VarCounter *aux = var_counter; aux; aux = aux->next){
        if(strcmp(var, aux->name) == 0) return aux;
    }

    for(VarCounter *aux = var_counter_global; aux; aux = aux->next){
        if(strcmp(var, aux->name) == 0) return aux;
    }
        
    return NULL;
}

int create_var_counter(char *var, int cnt){
    VarCounter* new_var = (VarCounter *) malloc(sizeof(VarCounter));
    if(!new_var){
        printf("ERRO MALLOC INSERT_VAR_COUNTER\n");
        return -1;
    }
    new_var->name = strdup(var);
    new_var->next = NULL;
    if(cnt < 0){
        new_var->counter = (char*) malloc(sizeof(char)*(strlen(var)+2));
        sprintf(new_var->counter, "@%s", var);
        if(!var_counter_global){
            var_counter_global = new_var;
            return cnt;
        } 
        
        VarCounter *aux, *previous;
        for(aux = var_counter_global; aux; previous = aux, aux = aux->next);
        previous->next = new_var;
        return cnt;
    }
    else{
        new_var->counter = (char*) malloc(sizeof(char)*(counter_size()+3));
        sprintf(new_var->counter, "%%%d", cnt);
        if(!var_counter){
            var_counter = new_var;
            return cnt;
        } 
        
        VarCounter *aux, *previous;
        for(aux = var_counter; aux; previous = aux, aux = aux->next);
        previous->next = new_var;
        return cnt;
    } 
}

char* get_counter(char *var){
    VarCounter *vc = search_var_counter(var);
    return vc->counter;
}

void free_var_counter(VarCounter *vc){
    if(!vc) return;
    free_var_counter(vc->next);
    free(vc->counter);
    free(vc->name);
    free(vc);
}

char * convert_type(char * s){
    if (strcmp(s, "Bool") == 0 || strcmp(s, "boolean") == 0 || strcmp(s, "BoolLit") == 0) return "i1";
    else if (strcmp(s, "Double") == 0 || strcmp(s, "double") == 0 || strcmp(s, "RealLit") == 0) return "double";
    else if (strcmp(s, "Int") == 0 || strcmp(s, "int") == 0 || strcmp(s, "DecLit") == 0) return "i32";
    else if (strcmp(s, "StringArray") == 0 || strcmp(s, "String[]") == 0) return "i8**";
    else return "void";
}

char * reverse_type(char * s){
    if (strcmp(s, "boolean") == 0) return "Bool";
    else if (strcmp(s, "double") == 0) return "Double";
    else if (strcmp(s, "int") == 0) return "Int";
    else if (strcmp(s, "String[]") == 0) return "StringArray";
    else return "Void";
}

void init_global_vars(){
    for(TableElement *aux = global_symtab->symbols; aux; aux = aux->next){
        if(!aux->params){
            char *conv_type = convert_type(aux->type);
            create_var_counter(aux->name, -1);
            if(strcmp(conv_type, "double") == 0) 
                printf("%s = global double 0.0\n", get_counter(aux->name));
            else
                printf("%s = global %s 0\n", get_counter(aux->name), conv_type);
        }
    }
}

void print_boolean(char *s){
    printf("call void @.print_boolean(i1 %s)\n", s);
}

void print_int(char *i){
    printf("call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @.int, i32 0, i32 0), i32 %s)\n", i);
    counter++;
}

void print_double(char *d){
    printf("call i32 (i8*, ...) @printf(i8* getelementptr ([6 x i8], [6 x i8]* @.double, i32 0, i32 0), double %s)\n", d);
    counter++;
}

void init_strings(){
    int new_len = 0;
    char *val;
    Str *aux, *previous;
    for(aux = string_list; aux; previous = aux, aux = aux->next, new_len = 0){
        val = conv_escape(aux->value, &new_len);
        aux->len = new_len + 1;
        printf("@.str.%d = private unnamed_addr constant [%d x i8] c\"%s\\00\"\n", aux->string_id, aux->len, val);
        free(val);
    }
}

void print_string(char *s){ 
    Str *full_str = search_string(s);
    int s_len = full_str->len, s_id = full_str->string_id;
    printf("call i32 (i8*, ...) @printf(i8* getelementptr ([%d x i8], [%d x i8]* @.str.%d, i32 0, i32 0))\n", s_len, s_len, s_id);
    counter++;
}

void print_func(Node *node){
    char *method_type = convert_type(node->son->type);
    char *method_name = node->son->bro->value;
    curr_return_type = strdup(method_type);
    printf("\ndefine %s @%s", method_type, method_name);
    Node *aux, *params = node->son->bro->bro->son;
    if(!params) printf(".Void");
    else{
        for(aux = params; aux; aux = aux->bro){
            printf(".%s", aux->son->type);
        }
    } 
    printf("(");
    int temp_counter = counter;
    for(aux = params; aux; aux = aux->bro){
        if(aux != params) printf(", ");
        char *type = convert_type(aux->son->type);
        char *value = aux->son->bro->value;
        printf("%s %%%d", type, ++counter);
    }
    printf(") {\n");
    counter++;
    for(aux = params; aux; aux = aux->bro){
        char *type = convert_type(aux->son->type);
        char *value = aux->son->bro->value;
        create_var_counter(value, ++counter);
        printf("%%%d = alloca %s\n", counter, type);
        printf("store %s %%%d, %s* %%%d\n", type, ++temp_counter, type, counter);
    }
}

char* format_num(char *num){
    char *val = strdup(num);

    char *i = val, *j = val;

    int first_is_dot = 0;
    int has_dot=0;
    int e = 0;

    for(; *i; i++){
        if(*i == 'e' || *i == 'E'){
            e = 1;
        } 
        else if(*i == '.'){
            has_dot = 1;
            if(i == val) first_is_dot = 1;
        } 
        if(*i != '_'){
            *j = *i;
            j++;
        }
    }
    *j = 0;

    if(first_is_dot){
        char *new_num=(char *) malloc(sizeof(char) * (strlen(val) + 2));
        new_num[0] = '0';
        new_num[1] = 0;
        strcat(new_num, val);
        free(val);
        return new_num;
    }

    if(!has_dot && e){
        char *new_num=(char *) malloc(sizeof(char) * (strlen(val) + 2));
        j = new_num;
        i = val;
        for(;*i;i++){
            if(*i == 'e' || *i == 'E') *j++ = '.';
            *j++ = *i;
        }
        *j = 0;
        free(val);
        return new_num;
    }
    return val;
}

void load_value(Node *node, char **op){
    if(!node) return;
    if(strcmp(node->type, "DecLit") == 0 || strcmp(node->type, "RealLit") == 0){
        *op = format_num(node->value);
        return;
    }
    if(strcmp(node->type, "BoolLit") == 0){
        *op = strdup(node->value);
        return;
    }
    if(strcmp(node->type, "Id") == 0){
        char *node_conv_type = convert_type(node->true_type);
        printf("%%%d = load %s, %s* %s\n", ++counter, node_conv_type, node_conv_type, get_counter(node->value));
    }
    else gen_llvmir(node);
    
    *op = (char *)malloc(sizeof(char)*(counter_size() + 3)); // \0->+1 %%->+2
    sprintf(*op, "%%%d", counter);
}

void two_son_int_double(Node *node, char *op_int, char *op_double){
    char *op[2];
    load_value(node->son, &op[0]);
    load_value(node->son->bro, &op[1]);

    // Para descobrir se é uma adição do tipo: int + int / int + double / double + int / double + double
    Node *son = node->son;
    char *node_true_type = convert_type(node->true_type);
    char *son_true_type = convert_type(son->true_type);
    char *other_son_true_type = convert_type(son->bro->true_type);
    if(strcmp(node_true_type, "i32") == 0)
        printf("%%%d = %s i32 %s, %s\n", ++counter, op_int, op[0], op[1]);
    else {
        if(strcmp(son_true_type, "i32") == 0){
            printf("%%%d = sitofp i32 %s to double\n", ++counter, op[0]);
            op[0] = (char *)realloc(op[0], sizeof(char)*(counter_size() + 3));
            sprintf(op[0], "%%%d", counter);
        } else if(strcmp(other_son_true_type, "i32") == 0){
            printf("%%%d = sitofp i32 %s to double\n", ++counter, op[1]);
            op[1] = (char *)realloc(op[1], sizeof(char)*(counter_size() + 3));
            sprintf(op[1], "%%%d", counter);
        }
        printf("%%%d = %s double %s, %s\n", ++counter, op_double, op[0], op[1]);
    }
    free(op[0]);
    free(op[1]);
}

void two_son_boolean(Node *node, char *op_boolean){
    char *op[2];
    load_value(node->son, &op[0]);
    load_value(node->son->bro, &op[1]);

    printf("%%%d = %s i1 %s, %s\n", ++counter, op_boolean, op[0], op[1]);
    free(op[0]);
    free(op[1]);
}

void two_son_cmp(Node *node, char *op_ins, char *op_ins_f){
    char *op[2];
    load_value(node->son, &op[0]);
    load_value(node->son->bro, &op[1]);

    Node *son = node->son;
    char *son_true_type = convert_type(son->true_type);
    char *other_son_true_type = convert_type(son->bro->true_type);
    if(strcmp(son_true_type, "i32") == 0 && strcmp(other_son_true_type, "i32") == 0 
    || strcmp(son_true_type, "i1") == 0 && strcmp(other_son_true_type, "i1") == 0)
        printf("%%%d = icmp %s %s %s, %s\n", ++counter, op_ins, son_true_type, op[0], op[1]);
    else{
        if(strcmp(son_true_type, "i32") == 0){
            printf("%%%d = sitofp i32 %s to double\n", ++counter, op[0]);
            op[0] = (char *)realloc(op[0], sizeof(char)*(counter_size() + 3));
            sprintf(op[0], "%%%d", counter);
        } else if(strcmp(other_son_true_type, "i32") == 0){
            printf("%%%d = sitofp i32 %s to double\n", ++counter, op[1]);
            op[1] = (char *)realloc(op[1], sizeof(char)*(counter_size() + 3));
            sprintf(op[1], "%%%d", counter);
        }
        printf("%%%d = fcmp %s double %s, %s\n", ++counter, op_ins_f, op[0], op[1]);
    }
    free(op[0]);
    free(op[1]);
}

int gen_llvmir(Node *node){
    if(!node) return 0;
    if(strcmp(node->type, "Program") == 0){
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            gen_llvmir(aux);
        }
        return 0;
    }
    if(strcmp(node->type, "MethodDecl") == 0){
        Node *method_header = node->son, *method_body = method_header->bro;
        var_counter = NULL;
        counter = -1;
        print_func(method_header);
        for(Node *aux = method_body->son; aux; aux = aux->bro)
            gen_llvmir(aux);
        if(strcmp(curr_return_type, "void") == 0) printf("ret void\n");
        else if(strcmp(curr_return_type, "double") == 0) printf("ret double 0.0\n");
        else printf("ret %s 0\n", curr_return_type);
        printf("}\n");
        free(curr_return_type);
        curr_return_type = NULL;
        free_var_counter(var_counter);
        var_counter = NULL;
        return 0;
    }
    /*if(strcmp(node->type, "FieldDecl") == 0){
        Node *son = node->son, *other_son = son->bro;
        char *conv_type = convert_type(son->type);
        create_var_counter(other_son->value, -1);
        if(strcmp(conv_type, "double") == 0) 
            printf("%s = global double 0.0\n", get_counter(other_son->value));
        else
            printf("%s = global %s 0\n", get_counter(other_son->value), conv_type);
    }*/
    if(strcmp(node->type, "VarDecl") == 0){
        Node *son = node->son, *other_son = son->bro;
        char *conv_type = convert_type(son->type);
        create_var_counter(other_son->value, ++counter);
        printf("%s = alloca %s\n", get_counter(other_son->value), conv_type);
        if(strcmp(conv_type, "double") == 0) printf("store double 0.0, double* %s\n", get_counter(other_son->value));
        else printf("store %s 0, %s* %s\n", conv_type, conv_type, get_counter(other_son->value));
        
    }
    if(strcmp(node->type, "Return") == 0){
        Node *son = node->son;
        if(son == NULL){
            printf("ret void\n");
            counter++;
            return 0;
        }

        char *son_true_type = convert_type(son->true_type);
        char *op;
        load_value(node->son, &op);

        if(strcmp(curr_return_type, "i32") == 0 || strcmp(curr_return_type, "i1") == 0){
            printf("ret %s %s\n", son_true_type, op);
        }
        else{
            if(strcmp(son_true_type, "i32") == 0){
                printf("%%%d = sitofp i32 %s to double\n", ++counter, op);
                op = (char *)realloc(op, sizeof(char)*(counter_size() + 3));
                sprintf(op, "%%%d", counter);
            }
            printf("ret double %s\n", op);
        }
        free(op);
        counter++;
        return 0;       
    }
    if(strcmp(node->type, "Assign") == 0){
        Node *son = node->son, *other_son = son->bro;
        char *son_true_type = convert_type(son->true_type);
        char *other_son_true_type = convert_type(other_son->true_type);
        char *op;
        load_value(other_son, &op);
        if(strcmp(son_true_type, "double") == 0 && strcmp(other_son_true_type, "i32") == 0){
            printf("%%%d = sitofp i32 %s to double\n", ++counter, op);
            printf("store %s %%%d, %s* %s\n", son_true_type, counter, son_true_type, get_counter(son->value));
        }
        else printf("store %s %s, %s* %s\n", son_true_type, op, son_true_type, get_counter(son->value));
        printf("%%%d = load %s, %s* %s\n", ++counter, son_true_type, son_true_type, get_counter(son->value));
        free(op);
        return 0;
    }
    if(strcmp(node->type, "Print") == 0){
        Node *son = node->son;
        if(strcmp(son->true_type, "String") == 0){
            print_string(node->son->value);
            return 0;
        } 
        char *son_conv_type = convert_type(son->true_type);
        char *op;
        load_value(son, &op);
        if(strcmp(son_conv_type, "i32") == 0) print_int(op);
        else if(strcmp(son_conv_type, "double") == 0) print_double(op);
        else if(strcmp(son_conv_type, "i1") == 0) print_boolean(op);
        free(op);
        return 0;
    }
    if(strcmp(node->type, "Call") == 0){
        Node *func_id_node = node->son;
        char *son_type, *func_id = func_id_node->value;

        int param_count = 0, i = 0;
        for(Node *aux = node->son->bro; aux; aux = aux->bro, param_count++);

        char *op, *op_list[param_count];

        Param *params = NULL;
        for(Node *aux = func_id_node->bro; aux; aux = aux->bro){
            load_value(aux, &op);
            op_list[i++] = op;
            params = add_param(params, NULL, aux->true_type, NULL);
        }
        if(!params) params = add_param(NULL, NULL, "", NULL);


        Param *aux1, *aux2;
        for(aux1 = func_id_node->params, aux2 = params, i = 0; aux1 && aux2; aux1 = aux1->next, aux2 = aux2->next, i++){
            if(strcmp(convert_type(aux1->param_type), "double") == 0 && strcmp(convert_type(aux2->param_type), "i32") == 0){
                printf("%%%d = sitofp i32 %s to double\n", ++counter, op_list[i]);
                op_list[i] = (char *)realloc(op_list[i], sizeof(char)*(counter_size() + 3));
                sprintf(op_list[i], "%%%d", counter);
            }
        }
        

        i = 0;

        char *return_type = convert_type(node->true_type);
        if(strcmp(return_type, "void") == 0) printf("call void @%s", func_id_node->value);
        else printf("%%%d = call %s @%s", ++counter, return_type, func_id_node->value);

        for(Param *aux = func_id_node->params; aux; aux = aux->next) printf(".%s", reverse_type(aux->param_type));

        printf("(");
        if(!(strcmp(convert_type(func_id_node->params->param_type), "void")==0)){
            for(Param *aux = func_id_node->params; aux; aux = aux->next){
                if(aux != func_id_node->params) printf(", ");
                printf("%s %s", convert_type(aux->param_type), op_list[i++]);
            }
        }
        printf(")\n");

        free_params(params);
        for(i = 0; i < param_count; i++) free(op_list[i]);
        return 0;
    }
    if(strcmp(node->type, "Add") == 0){
        two_son_int_double(node, "add", "fadd");
        return 0;
    }
    if(strcmp(node->type, "Sub") == 0){
        two_son_int_double(node, "sub", "fsub");
        return 0;
    }
    if(strcmp(node->type, "Mul") == 0){
        two_son_int_double(node, "mul", "fmul");
        return 0;
    }
    if(strcmp(node->type, "Div") == 0){
        two_son_int_double(node, "sdiv", "fdiv");
        return 0;
    }
    if(strcmp(node->type, "Mod") == 0){
        two_son_int_double(node, "srem", "frem");
        return 0;
    }
    if (strcmp(node->type, "Xor") == 0){
        if(strcmp(node->son->true_type, "int") == 0) two_son_int_double(node, "xor", NULL);
        else two_son_boolean(node, "xor");
        return 0;
    }
    if (strcmp(node->type, "And") == 0){
        Node *son = node->son;
        char *op1, *op2;

        int temp_label_counter = ++label_counter;
        printf("br label %%and_entry.%d\n\n", temp_label_counter);
        
        printf("and_entry.%d:\n", temp_label_counter);
        load_value(son, &op1);
        printf("br i1 %s, label %%and_normal.%d, label %%and_short_circuit.%d\n\n", op1, temp_label_counter, temp_label_counter);
        
        printf("and_normal.%d:\t\t;preds = %%and_entry.%d\n", temp_label_counter, temp_label_counter);
        load_value(son->bro, &op2);
        printf("br label %%and_no_short_circuit.%d\n\n", temp_label_counter);

        printf("and_no_short_circuit.%d:\t\t;preds = %%and_normal.%d\n", temp_label_counter, temp_label_counter);
        printf("br label %%and_cont.%d\n\n", temp_label_counter);
        
        printf("and_short_circuit.%d:\t\t;preds = %%and_entry.%d\n", temp_label_counter, temp_label_counter);
        printf("br label %%and_cont.%d\n\n", temp_label_counter);
        
        printf("and_cont.%d:\t\t;preds = %%and_no_short_circuit.%d, %%and_short_circuit.%d\n", temp_label_counter, temp_label_counter, temp_label_counter);
        printf("%%%d = phi i1 [%s, %%and_no_short_circuit.%d], [false, %%and_short_circuit.%d]\n\n", ++counter, op2, temp_label_counter, temp_label_counter);

        free(op1);
        free(op2);
        return 0;
    }
    if (strcmp(node->type, "Or") == 0){
        Node *son = node->son;
        char *op1, *op2;

        int temp_label_counter = ++label_counter;
        printf("br label %%or_entry.%d\n\n", temp_label_counter);

        printf("or_entry.%d:\n", temp_label_counter);
        load_value(son, &op1);
        printf("br i1 %s, label %%or_short_circuit.%d, label %%or_normal.%d\n\n", op1, temp_label_counter, temp_label_counter);
        
        printf("or_short_circuit.%d:\t\t;preds = %%or_entry.%d\n", temp_label_counter, temp_label_counter);
        printf("br label %%or_cont.%d\n\n", temp_label_counter);
        
        printf("or_normal.%d:\t\t;preds = %%or_entry.%d\n", temp_label_counter, temp_label_counter);
        load_value(son->bro, &op2);
        printf("br label %%or_no_short_circuit.%d\n\n", temp_label_counter);

        printf("or_no_short_circuit.%d:\t\t;preds = %%or_normal.%d\n", temp_label_counter, temp_label_counter);
        printf("br label %%or_cont.%d\n\n", temp_label_counter);
        
        printf("or_cont.%d:\t\t;preds = %%or_no_short_circuit.%d, %%or_short_circuit.%d\n", temp_label_counter, temp_label_counter, temp_label_counter);
        printf("%%%d = phi i1 [true, %%or_short_circuit.%d], [%s, %%or_no_short_circuit.%d]\n\n", ++counter, temp_label_counter, op2, temp_label_counter);
        free(op1);
        free(op2);
        return 0;
    }
    if (strcmp(node->type, "Not") == 0){
        int count = 0;
        Node *son = node->son;

        char *op;
        load_value(son, &op);

        printf("%%%d = xor i1 1, %s\n", ++counter, op);
        free(op);
        return 0;
    }
    if(strcmp(node->type, "Plus") == 0){
        int count = 0;
        Node *son = node->son;
        char *op;
        load_value(son, &op);

        if(strcmp(convert_type(son->true_type), "i32") == 0)
            printf("%%%d = add i32 0, %s\n", ++counter, op);
        else
            printf("%%%d = fadd double 0.0, %s\n", ++counter, op);

        free(op);
        return 0;
    }
    if(strcmp(node->type, "Minus") == 0){
        Node *son = node->son;
        char *op;
        load_value(son, &op);

        if(strcmp(convert_type(son->true_type), "i32") == 0)
            printf("%%%d = sub i32 0, %s\n", ++counter, op);
        else
            printf("%%%d = fneg double %s\n", ++counter, op);

        free(op); 
        return 0;
    }
    if (strcmp(node->type, "Lshift") == 0){
        char *op1;
        load_value(node->son, &op1);
        char *op2;
        load_value(node->son->bro, &op2);
        printf("%%%d = shl i32 %s, %s\n", ++counter, op1, op2);
        free(op1);
        free(op2);
        return 0;
    }
    if (strcmp(node->type, "Rshift") == 0){
        char *op1;
        load_value(node->son, &op1);
        char *op2;
        load_value(node->son->bro, &op2);
        printf("%%%d = ashr i32 %s, %s\n", ++counter, op1, op2);
        free(op1);
        free(op2);
        return 0;
    }
    if (strcmp(node->type, "Eq") == 0){
        two_son_cmp(node, "eq", "oeq");
        return 0;
    }
    if (strcmp(node->type, "Ne") == 0){
        two_son_cmp(node, "ne", "one");
        return 0;
    }
    if (strcmp(node->type, "Lt") == 0){
        two_son_cmp(node, "slt", "olt");
        return 0;
    }
    if (strcmp(node->type, "Gt") == 0){
        two_son_cmp(node, "sgt", "ogt");
        return 0;
    }
    if (strcmp(node->type, "Le") == 0){
        two_son_cmp(node, "sle", "ole");
        return 0;
    }
    if (strcmp(node->type, "Ge") == 0){
        two_son_cmp(node, "sge", "oge");
        return 0;
    }
    if (strcmp(node->type, "If") == 0){
        int temp_label_counter = ++label_counter;
        char *op;
        printf("br label %%entry.%d\n", temp_label_counter);
        printf("\nentry.%d:\n", temp_label_counter);
        load_value(node->son, &op);
        printf("br i1 %s, label %%then.%d, label %%else.%d\n", op, temp_label_counter, temp_label_counter);
        printf("then.%d:\n", temp_label_counter);
        gen_llvmir(node->son->bro);
        printf("br label %%ifcont.%d\n\n", temp_label_counter);
        printf("else.%d:\n", temp_label_counter);
        gen_llvmir(node->son->bro->bro);
        printf("br label %%ifcont.%d\n\n", temp_label_counter);
        printf("ifcont.%d:\n", temp_label_counter);
        free(op);
        return 0;
    }
    if (strcmp(node->type, "While") == 0){
        int temp_label_counter = ++label_counter;
        char *op;
        printf("br label %%entry.%d\n", temp_label_counter);
        printf("\nentry.%d:\n", temp_label_counter);
        load_value(node->son, &op);
        printf("br i1 %s, label %%body.%d, label %%exit.%d\n", op, temp_label_counter, temp_label_counter);
        printf("body.%d:\n", temp_label_counter);
        gen_llvmir(node->son->bro);
        printf("br label %%entry.%d\n", temp_label_counter);
        printf("exit.%d:\n", temp_label_counter);
        free(op);
        return 0;
    }
    if(strcmp(node->type, "Block") == 0){
        for(Node *aux = node->son; aux; aux = aux->bro){
            gen_llvmir(aux);
        }
        return 0;
    }
    if(strcmp(node->type, "Length") == 0){
        printf("%%%d = load i32, i32* @.argc\n", ++counter);
        return 0;
    }
    if(strcmp(node->type, "ParseArgs") == 0){
        char *op;
        load_value(node->son->bro, &op);
        printf("%%%d = load i8**, i8*** %s\n", ++counter, get_counter(node->son->value));
        printf("%%%d = add i32 %s, 1\n", ++counter, op);
        printf("%%%d = getelementptr i8*, i8** %%%d, i32 %%%d\n", counter + 1, counter - 1, counter);
        counter++;
        printf("%%%d = load i8*, i8** %%%d\n", counter + 1, counter);
        counter++;
        printf("%%%d = call i32 @atoi(i8* %%%d)\n", counter + 1, counter);
        counter++;
        free(op);
        return 0;
    }
    return 0;
}

int setup_llvmir(){
    printf("@.false = private unnamed_addr constant [6 x i8] c\"false\\00\"\n");
    printf("@.true = private unnamed_addr constant [5 x i8] c\"true\\00\"\n");
    printf("@.booleans = global [2 x i8*] [i8* getelementptr ([6 x i8], [6 x i8]* @.false, i32 0, i32 0), i8* getelementptr ([5 x i8], [5 x i8]* @.true, i32 0, i32 0)]\n");
    printf("@.int = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
    printf("@.double = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("@.string = private constant [3 x i8] c\"%%s\\00\"\n");
    init_strings();
    printf("@.argc = global i32 0\n\n");
    init_global_vars();
    printf("\ndeclare i32 @printf(i8* nocapture readonly, ...) nounwind");
    printf("\ndeclare i32 @atoi(i8* nocapture readonly) nounwind\n");
    printf("\ndefine void @.print_boolean(i1 %%.boolean) {\n");
    printf("%%1 = zext i1 %%.boolean to i32\n");
    printf("%%2 = getelementptr [2 x i8*], [2 x i8*]* @.booleans, i32 0, i32 %%1\n");
    printf("%%3 = load i8*, i8** %%2\n");
    printf("call i32 (i8*, ...) @printf(i8* %%3)\n");
    printf("ret void\n}\n");

    int main_exists = 0;
    for(TableElement *aux = global_symtab->symbols; aux; aux = aux->next){
        if(strcmp(aux->name, "main") == 0 && strcmp(aux->params->param_type, "String[]") == 0){
            main_exists = 1;
            break;
        }
    }

    if(main_exists) gen_llvmir(root);

    
    printf("\ndefine i32 @main(i32 %%0, i8** %%1) {\n");
    printf("%%3 = sub i32 %%0, 1\n");
    printf("store i32 %%3, i32* @.argc\n");

    
    if(main_exists) printf("call void @main.StringArray(i8** %%1)\n");
    
    printf("ret i32 0\n}\n");
    //printf("\ndefine i32 @main() {\n");
    
    //print_boolean("%6");
    //printf("ret i32 0\n}\n");

    free_var_counter(var_counter_global);
}