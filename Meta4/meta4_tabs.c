#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meta4.h"
#include "symbol_table.h"

int gen_llvmir(Node *node, int scope);

char *curr_return_type = NULL;
VarCounter *var_counter = NULL;
int counter = 0, act_counter = 0;

VarCounter* search_var_counter(char *var){
    for(VarCounter *aux = var_counter; aux; aux = aux->next)  
        if(strcmp(var, aux->name) == 0) return aux;
    return NULL;
}

int update_var_counter(char *var, int cnt){
    VarCounter *new_var = search_var_counter(var);
    if(!new_var){
        new_var = (VarCounter *) malloc(sizeof(VarCounter));
        if(!new_var){
            printf("ERRO MALLOC INSERT_VAR_COUNTER\n");
            return -1;
        }
        new_var->name = strdup(var);
        new_var->counter = cnt;

        if(!var_counter){
            new_var->next = NULL;
            var_counter = new_var;
            return cnt;
        } 
        
        VarCounter *aux, *previous;
        for(aux = var_counter; aux; previous = aux, aux = aux->next);
        previous->next = new_var;
        return cnt;
    }
    new_var->counter = cnt;
    return cnt;
}

int get_counter(char *var){
    VarCounter *vc = search_var_counter(var);
    if(!vc) return update_var_counter(var, counter++);
    return vc->counter;
}

void free_var_counter(VarCounter *vc){
    if(!vc) return;
    free_var_counter(vc->next);
    free(vc);
}

int counter_size(){
    int aux = counter, size = 0;
    for(; aux > 0; aux /= 10, size++);
    return size;
}

char * convert_type(char * s){
    if (strcmp(s, "Bool") == 0 || strcmp(s, "boolean") == 0 || strcmp(s, "BoolLit") == 0) return "i1";
    else if (strcmp(s, "Double") == 0 || strcmp(s, "double") == 0 || strcmp(s, "RealLit") == 0) return "double";
    else if (strcmp(s, "Int") == 0 || strcmp(s, "int") == 0 || strcmp(s, "DecLit") == 0) return "i32";
    else return "void";
}

void print_boolean(char *s, int scope){
    for(int i = 0; i < scope ; i++) printf("\t");
    printf("call void @.print_boolean(i1 %s)\n", s);
}

void print_int(char *i, int scope){
    for(int i = 0; i < scope ; i++) printf("\t");
    printf("tail call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @p_int, i64 0, i64 0), i32 %s)\n", i);
    counter++;
}

void print_double(char *d, int scope){
    for(int i = 0; i < scope ; i++) printf("\t");
    printf("tail call i32 (i8*, ...) @printf(i8* getelementptr ([6 x i8], [6 x i8]* @p_double, i64 0, i64 0), double %s)\n", d);
    counter++;
}

void print_func(Node *node, int scope){
    char *method_type = convert_type(node->son->type);
    char *method_name = node->son->bro->value;
    curr_return_type = strdup(method_type);
    printf("\ndefine %s @%s", method_type, method_name);
    Node *aux, *params = node->son->bro->bro->son;
    for(aux = params; aux; aux = aux->bro){
        char *type = convert_type(aux->son->type);
        printf("_%s", type);
    } 
    printf("(");
    for(aux = params; aux; aux = aux->bro){
        if(aux != params) printf(", ");
        char *type = convert_type(aux->son->type);
        char *value = aux->son->son->value;
        printf("%s %%%d", type, get_counter(value));
    }
    printf(") {\n");
    //for(int i = 0; i < scope ; i++) printf("\t");
    //printf("entry.%d:\n", act_counter);
}

void load_value(Node *node, char **op, int scope){
    if(!node) return;
    if(strcmp(node->type, "DecLit") == 0 || strcmp(node->type, "RealLit") == 0 || strcmp(node->type, "BoolLit") == 0){
        *op = strdup(node->value);
        return;
    }
    
    if(strcmp(node->type, "Id") == 0){
        *op = (char *)malloc(sizeof(char)*(counter_size() + 3)); // \0->+1 %%->+2
        sprintf(*op, "%%%d", get_counter(node->value));
        return;
    } 

    gen_llvmir(node, scope);
    *op = (char *)malloc(sizeof(char)*(counter_size() + 3)); // \0->+1 %%->+2
    sprintf(*op, "%%%d", counter);
}

void two_son_int_double(Node *node, char *op_int, char *op_double, int scope){
    // Para fazer as conversões necessárias
    int count;
    Node *aux = node->son;
    char *op[2];
    load_value(node->son, &op[0], scope);
    load_value(node->son->bro, &op[1], scope);

    // Para descobrir se é uma adição do tipo: int + int / int + double / double + int / double + double
    Node *son = node->son;
    char *son_true_type = convert_type(son->true_type);
    char *other_son_true_type = convert_type(son->bro->true_type);
    if(strcmp(node->true_type, "int") == 0){
        for(int i = 0; i < scope ; i++) printf("\t");
        printf("%%%d = %s i32 %s, %s\n", ++counter, op_int, op[0], op[1]);
    }
    else {
        if(strcmp(son_true_type, "i32") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = uitofp i32 %s to double\n", ++counter, op[0]);
            op[0] = (char *)realloc(op[0], sizeof(char)*(counter_size() + 3));
            sprintf(op[0], "%%%d", counter);
        } else if(strcmp(other_son_true_type, "i32") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = uitofp i32 %s to double\n", ++counter, op[1]);
            op[1] = (char *)realloc(op[1], sizeof(char)*(counter_size() + 3));
            sprintf(op[1], "%%%d", counter);
        }
        for(int i = 0; i < scope ; i++) printf("\t");
        printf("%%%d = %s double %s, %s\n", ++counter, op_double, op[0], op[1]);
    }
    free(op[0]);
    free(op[1]);
}

void two_son_boolean(Node *node, char *op_boolean, int scope){
    // Para fazer as conversões necessárias
    int count;
    Node *aux = node->son;
    char *op[2];
    load_value(node->son, &op[0], scope);
    load_value(node->son->bro, &op[1], scope);
    for(int i = 0; i < scope ; i++) printf("\t");
    printf("%%%d = %s i1 %s, %s\n", ++counter, op_boolean, op[0], op[1]);
    free(op[0]);
    free(op[1]);
}

void two_son_cmp(Node *node, char *op_ins, int scope){
            Node *aux = node->son;
        char *op[2];
        load_value(node->son, &op[0], scope);
        load_value(node->son->bro, &op[1], scope);

        Node *son = node->son;
        char *son_true_type = convert_type(son->true_type);
        char *other_son_true_type = convert_type(son->bro->true_type);
        if(strcmp(son_true_type, "i32") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = icmp %s i32 %s, %s\n", ++counter, op_ins, op[0], op[1]);
        }
        else if (strcmp(node->true_type, "double") == 0){
            if(strcmp(son_true_type, "i32") == 0){
                for(int i = 0; i < scope ; i++) printf("\t");
                printf("%%%d = uitofp i32 %s to double\n", ++counter, op[0]);
                op[0] = (char *)realloc(op[0], sizeof(char)*(counter_size() + 3));
                sprintf(op[0], "%%%d", counter);
            } else if(strcmp(other_son_true_type, "i32") == 0){
                for(int i = 0; i < scope ; i++) printf("\t");
                printf("%%%d = uitofp i32 %s to double\n", ++counter, op[1]);
                op[1] = (char *)realloc(op[1], sizeof(char)*(counter_size() + 3));
                sprintf(op[1], "%%%d", counter);
            }
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = icmp %s double %s, %s\n", ++counter, op_ins, op[0], op[1]);
        } else {
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = icmp %s i1 %s, %s\n", ++counter, op_ins, op[0], op[1]);
        }
        free(op[0]);
        free(op[1]);
}

int gen_llvmir(Node *node, int scope){
    if(!node) return 0;
    if(strcmp(node->type, "Program") == 0){
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            gen_llvmir(aux, scope);
        }
        return 0;
    }
    if(strcmp(node->type, "MethodDecl") == 0){
        Node *method_header = node->son, *method_body = method_header->bro;
        var_counter = NULL;
        //print_func(method_header, scope++);
        print_func(method_header, scope);
        for(Node *aux = method_body->son; aux; aux = aux->bro)
            gen_llvmir(aux, scope);
        printf("}\n");
        curr_return_type = NULL;
        free_var_counter(var_counter);
        var_counter = NULL;
        return 0;
    }
    if(strcmp(node->type, "Return") == 0){
        Node *son = node->son;
        print_boolean("%2", scope);
        if(son == NULL){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("ret void\n");
            return 0;
        }

        char *son_true_type = convert_type(son->true_type);
        char *op;
        load_value(node->son, &op, scope);

        if(strcmp(curr_return_type, "i32") == 0 || strcmp(curr_return_type, "i1") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("ret %s %s, 0\n", son_true_type, op);
        }
        else{
            if(strcmp(son_true_type, "i32") == 0){
                for(int i = 0; i < scope ; i++) printf("\t");
                printf("%%%d = uitofp i32 %s to double\n", ++counter, op);
                op = (char *)realloc(op, sizeof(char)*(counter_size() + 3));
                sprintf(op, "%%%d", counter);
            }
            printf("ret double %s\n", op);
        }
        free(op);
        return 0;       
    }
    if(strcmp(node->type, "Assign") == 0){
        Node *son = node->son, *other_son = son->bro;
        char *son_true_type = convert_type(son->true_type);
        char *other_son_true_type = convert_type(other_son->true_type);

        if(strcmp(other_son->type, "Id") == 0){
            update_var_counter(son->value, get_counter(other_son->value));
            return 0;
        } 

        if(strcmp(other_son->type, "DecLit") == 0 || strcmp(other_son->type, "RealLit") == 0 || strcmp(other_son->type, "BoolLit") == 0){
            char *op;
            load_value(other_son, &op, scope);
            if(strcmp(son_true_type, "i32") == 0 || strcmp(son_true_type, "i1") == 0){
                for(int i = 0; i < scope ; i++) printf("\t");
                printf("%%%d = add %s %s, 0\n", update_var_counter(son->value, ++counter), son_true_type, op);
            }
            else{
                if(strcmp(other_son_true_type, "i32") == 0) {
                    for(int i = 0; i < scope ; i++) printf("\t");
                    printf("%%%d = uitofp i32 %s to double\n", update_var_counter(son->value, ++counter), op);
                }
                else{
                    for(int i = 0; i < scope ; i++) printf("\t");
                    printf("%%%d = fadd double %s, 0.0\n", update_var_counter(son->value, ++counter), op);
                }
            }
            free(op);
            return 0;
        }
        gen_llvmir(other_son, scope);
        update_var_counter(son->value, counter);
        return 0;
    }
    if(strcmp(node->type, "Print") == 0){
        Node *son = node->son;
        char *son_conv_type = convert_type(son->true_type);
        char *op;
        load_value(son, &op, scope);
        if(strcmp(son_conv_type, "i32") == 0) print_int(op, scope);
        else if(strcmp(son_conv_type, "double") == 0) print_double(op, scope);
        else if(strcmp(son_conv_type, "i1") == 0) print_boolean(op, scope);
    }
    if(strcmp(node->type, "Add") == 0){
        two_son_int_double(node, "add", "fadd", scope);
        return 0;
    }
    if(strcmp(node->type, "Sub") == 0){
        two_son_int_double(node, "sub", "fsub", scope);
        return 0;
    }
    if(strcmp(node->type, "Mul") == 0){
        two_son_int_double(node, "mul", "fmul", scope);
        return 0;
    }
    if(strcmp(node->type, "Div") == 0){
        two_son_int_double(node, "sdiv", "fdiv", scope);
        return 0;
    }
    if(strcmp(node->type, "Mod") == 0){
        two_son_int_double(node, "urem", NULL, scope);
        return 0;
    }
    if (strcmp(node->type, "Xor") == 0){
        two_son_boolean(node, "xor", scope);
        return 0;
    }
    if (strcmp(node->type, "And") == 0){
        two_son_boolean(node, "and", scope);
        return 0;
    }
    if (strcmp(node->type, "Or") == 0){
        two_son_boolean(node, "or", scope);
        return 0;
    }
    if (strcmp(node->type, "Not") == 0){
        int count = 0;
        Node *son = node->son;

        char *op;
        load_value(son, &op, scope);

        for(int i = 0; i < scope ; i++) printf("\t");
        printf("%%%d = xor i1 1, %s\n", ++counter, op);
        return 0;
    }
    if(strcmp(node->type, "Plus") == 0){
        int count = 0;
        Node *son = node->son;
        char *op;
        load_value(son, &op, scope);

        if(strcmp(convert_type(son->true_type), "i32") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = add i32 %s, 0\n", counter++, op);
        }
        else{
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = fadd double %s, 0.0\n", counter++, op);
        }
        return 0;
    }
    if(strcmp(node->type, "Minus") == 0){
        Node *son = node->son;
        char *op;
        load_value(son, &op, scope);

        if(strcmp(convert_type(son->true_type), "i32") == 0){
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = sub i32 %s, 0\n", counter++, op);
        }
        else{
            for(int i = 0; i < scope ; i++) printf("\t");
            printf("%%%d = fsub double %s, 0.0\n", counter++, op);
        }
        return 0;
    }
    if (strcmp(node->type, "Lshift") == 0){
        char *op1;
        load_value(node->son, &op1, scope);
        char *op2;
        load_value(node->son->bro, &op2, scope);
        for(int i = 0; i < scope ; i++) printf("\t");
        printf("%%%d = shl i32 %s, %s\n", ++counter, op1, op2);
    }
    if (strcmp(node->type, "Rshift") == 0){
        char *op1;
        load_value(node->son, &op1, scope);
        char *op2;
        load_value(node->son->bro, &op2, scope);
        for(int i = 0; i < scope ; i++) printf("\t");
        printf("%%%d = lshr i32 %s, %s\n", ++counter, op1, op2);
    }
    if (strcmp(node->type, "Eq") == 0){
        two_son_cmp(node, "eq", scope);
    }
    if (strcmp(node->type, "Ne") == 0){
        two_son_cmp(node, "ne", scope);
    }
    if (strcmp(node->type, "Lt") == 0){
        two_son_cmp(node, "ult", scope);
    }
    if (strcmp(node->type, "Gt") == 0){
        two_son_cmp(node, "ugt", scope);
    }
    if (strcmp(node->type, "Le") == 0){
        two_son_cmp(node, "ule", scope);
    }
    if (strcmp(node->type, "Ge") == 0){
        two_son_cmp(node, "uge", scope);
    }
    return 0;
}

int setup_llvmir(){
    printf("@.false = private unnamed_addr constant [6 x i8] c\"false\\00\"\n");
    printf("@.true = private unnamed_addr constant [5 x i8] c\"true\\00\"\n");
    printf("@.booleans = dso_local global [2 x i8*] [i8* getelementptr ([6 x i8], [6 x i8]* @.false, i32 0, i32 0), i8* getelementptr ([5 x i8], [5 x i8]* @.true, i32 0, i32 0)]\n");
    printf("@p_int = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
    printf("@p_double = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("\ndeclare i32 @printf(i8* nocapture readonly, ...) nounwind\n");
    printf("\ndeclare i32 @atoi(i8* nocapture readonly) nounwind\n");
    printf("\ndefine void @.print_boolean(i1 %%.boolean) {\n");
    printf("\t%%1 = zext i1 %%.boolean to i32\n");
    printf("\t%%2 = getelementptr [2 x i8*], [2 x i8*]* @.booleans, i32 0, i32 %%1\n");
    printf("\t%%3 = load i8*, i8** %%2\n");
    printf("\ttail call i32 (i8*, ...) @printf(i8* %%3)\n");
    printf("\tret void\n}\n");

    int found_main = 0;
    for(TableElement *aux = global_symtab->symbols; aux; aux = aux->next){
        if(strcmp(aux->name, "main") == 0 && aux->params){
            found_main = 1;
            break;
        } 
    }
    if(!found_main){
        printf("\ndefine void @main(printf(\"entry:\n\");\n) {\nret void\n}\n");
    }
    //printf("\ndefine i32 @main() {\n");
    gen_llvmir(root, 1);
    //printf("ret i32 0\n}\n");
    
}
