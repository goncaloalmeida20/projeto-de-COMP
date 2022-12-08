#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "semantics.h"
#include "symbol_table.h"

char *scope = NULL;
char *return_type = NULL;
Param *curr_params = NULL;
Str *string_list = NULL;
int error = 0, string_id = 0;

void error_out_of_bounds(char *value, Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Number %s out of bounds\n", pos->line, pos->col, value);
}

void error_underscore_reserved(Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Symbol _ is reserved\n", pos->line, pos->col);
}

void error_ambiguous_func(Param *params, char *method, Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Reference to method %s(", pos->line, pos->col, method);
    print_params(params);
    printf(") is ambiguous\n");
}

void error_incompatible_type(char *statement, char *type, Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Incompatible type %s in %s statement\n", pos->line, pos->col, type, statement);
}

void error_symbol_not_found(Param *params, char *symbol, Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Cannot find symbol %s", pos->line, pos->col, pos->value);
    if(params){
        printf("(");
        print_params(params);
        printf(")\n");
    } 
    else printf("\n");
}

void error_already_defined(Param *params, char* symbol, Node *pos){
    if(!error) error = 1;
    printf("Line %d, col %d: Symbol %s", pos->line, pos->col, symbol);
    if(params){
        printf("(");
        print_params(params);
        printf(")");
    }
    printf(" already defined\n");
}

void error_operator_cannot_be_applied(char *operator, char *type1, char *type2, Node *pos){
    if(!error) error = 1;
    if (type2) printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", pos->line, pos->col, operator, type1, type2);
    else printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", pos->line, pos->col, operator, type1);
}

int is_zero(char *s){
    if(!s) return 0;
    for(char *c = s; *c && *c != 'E' && *c != 'e' ; c++) if(*c != '0' && *c != '.') return 0;
    return 1;
}

double convert_num(char *value, int *base_is_zero, char **conv_str){
    char *val = strdup(value);

    double b = 0; 
    long e = 0;
    char *i = val, *j = val;
    for(; *i; i++){
        if(*i != '_'){
            *j = *i;
            j++;
        }
    }

    *j = 0;
    double res = atof(val);
    if(base_is_zero) *base_is_zero = is_zero(val);
    if(conv_str) *conv_str = val;
    else free(val);
    return res;
}

int bigger_than_long(char * value){
    if(strlen(value) > 10) return 1;
    char longi[11] = "2147483647";
    for(int i = 0; i < 10; i++){
        if (value[i] < longi[i]) return 0;
        if (value[i] > longi[i]) return 1;
    }
    return 0;
}

void declare_method(Node *node){
    Node *method_header = node->son, *method_type = method_header->son, *method_id = method_type->bro;
    Node *method_params = method_id->bro;
    if(strcmp(method_id->value, "_") == 0){
        error_underscore_reserved(node);
        return;
    }
    Param *params = NULL;
    int error = 0;
    for(Node *aux = method_params->son; aux; aux = aux->bro){
        params = add_param(params, aux->son->bro->value, aux->son->true_type, &error);
        if(error == 1){
            error_already_defined(NULL, aux->son->bro->value, aux->son->bro);
        }
        else if(error == 2){
            error_underscore_reserved(aux->son->bro);
        }
    }
    if(!insert_el_func(method_id->value, method_type->true_type, params)){
        if(!params) params = add_param(NULL, NULL, "", NULL);
        error_already_defined(params, method_id->value, method_id);
        node->check_node = 0;
    }
    if(params) free_params(params);            
}

void declare_var(Node *node){
    Node *type_node = node->son;
    Node *id_node = type_node->bro;
    if(strcmp(id_node->value, "_") == 0){
        error_underscore_reserved(id_node);
        return;
    }
    if(!insert_el(id_node->value, type_node->true_type, scope, curr_params))
        error_already_defined(NULL, id_node->value, id_node);
}

Str* search_string(char *value){
    for(Str *aux = string_list; aux; aux = aux->next){
        if(strcmp(value, aux->value) == 0) return aux;
    }
    return NULL;
}

int create_string(char *value){
    Str *new_string = search_string(value);
    if(new_string) return new_string->string_id;
    new_string = (Str *) malloc(sizeof(Str));
    if(!new_string){
        printf("ERRO MALLOC INSERT_NEW_STRING\n");
        return -1;
    }
    
    new_string->len = 0;
    new_string->string_id = string_id++;
    new_string->value = strdup(value);
    new_string->next = NULL;

    if(!string_list){
        string_list = new_string;
        return new_string->string_id;
    } 
    
    Str *aux, *previous;
    for(aux = string_list; aux; previous = aux, aux = aux->next);
    previous->next = new_string;
    return new_string->string_id;
}

void free_string(Str *str){
    if(!str) return;
    free_string(str->next);
    free(str->value);
    free(str);
}

char* check(Node *node){
    if(!node || !node->check_node) return NULL;
    if(strcmp(node->type, "Program") == 0){
        //registar os metodos e variaveis globais primeiro
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            if(strcmp(aux->type, "FieldDecl") == 0) declare_var(aux);
            else if(strcmp(aux->type, "MethodDecl") == 0) declare_method(aux);
        }

        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            check(aux);
        }
        return 0;
    }
    if(strcmp(node->type, "FieldDecl") == 0) return NULL;
    if(strcmp(node->type, "VarDecl") == 0){
        declare_var(node);
        return NULL;
    }
    if(strcmp(node->type, "MethodDecl") == 0){
        Node *method_header = node->son;
        char *method_return_type = method_header->son->true_type;
        char *method_id = method_header->son->bro->value;
        scope = strdup(method_id);
        return_type = strdup(method_return_type);
        curr_params = NULL;
        for(Node *p = method_header->son->bro->bro->son; p; p = p->bro){
            curr_params = add_param(curr_params, p->son->bro->value, p->son->true_type, NULL);
        }

        Node *method_body = node->son->bro;
        for(Node *aux = method_body->son; aux; aux = aux->bro){
            check(aux);
        }
        free(scope);
        free(return_type);
        free_params(curr_params);
        scope = NULL;
        return_type = NULL;
        curr_params = NULL;
        return NULL;
    }
    if(strcmp(node->type, "Block") == 0){
        if(!node->son) return NULL;
        for(Node *aux = node->son; aux; aux = aux->bro) check(aux);
        return NULL;
    }
    if(strcmp(node->type, "If") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "boolean") == 0)){
            error_incompatible_type(node->true_type, son_type, node->son);
        }
        check(node->son->bro);
        check(node->son->bro->bro);
        return NULL;
    }
    if(strcmp(node->type, "While") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "boolean") == 0)){
            error_incompatible_type(node->true_type, son_type, node->son);
        }
        check(node->son->bro);
        return NULL;
    }
    if(strcmp(node->type, "Return") == 0){
        if(!node->son && !(strcmp(return_type, "void") == 0)){
            error_incompatible_type(node->true_type, "void", node);
            return NULL;
        } 
        if(!node->son) return NULL;
        char *son_type = check(node->son);
        int int_double = map_int_double(return_type) >= map_int_double(son_type) && map_int_double(return_type) >= 0 && map_int_double(son_type) >= 0;
        if(strcmp(son_type, "void") == 0){
            error_incompatible_type(node->true_type, son_type, node->son);
        }
        else if(strcmp(son_type, return_type) != 0 ){
            if(!int_double)error_incompatible_type(node->true_type, son_type, node->son);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup(son_type);
        return NULL;
    }
    if(strcmp(node->type, "Call") == 0){
        Node *func_id_node = node->son;
        char *son_type, *func_id = func_id_node->value;
        Param *params = NULL;
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            son_type = check(aux);
            params = add_param(params, NULL, son_type, NULL);
        }
        if(!params) params = add_param(NULL, NULL, "", NULL);
        int ambiguous = 0;
        TableElement *func = search_el_func(func_id, params, &ambiguous);
        if(!func){
            if(func_id_node->params){
                free_params(func_id_node->params);
                func_id_node->params = NULL;
            }
            func_id_node->params = param_dup(params);

            if(ambiguous) error_ambiguous_func(node->son->params, node->son->value, node->son);
            else error_symbol_not_found(node->son->params, node->son->value, node->son);
            if(func_id_node->true_type){
                free(func_id_node->true_type);
                func_id_node->true_type = NULL;
            }
            func_id_node->true_type = strdup("undef");
            func_id_node->print_true_type = 1;
            func_id_node->params = NULL;

            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("undef");
            node->print_true_type = 1;
            return "undef";
        }
        if(func_id_node->true_type){
            free(func_id_node->true_type);
            func_id_node->true_type = NULL;
        }
        func_id_node->print_true_type = 1;
        if(func_id_node->params){
            free_params(func_id_node->params);
            func_id_node->params = NULL;
        }
        func_id_node->params = param_dup(func->params);

        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup(func->type);
        node->print_true_type = 1;
        free_params(params);
        return node->true_type;
    }
    if(strcmp(node->type, "Print") == 0){
        char *son_type = check(node->son);
        if(strcmp(son_type, "void") == 0 || strcmp(son_type, "undef") == 0 || strcmp(son_type, "String[]") == 0){
            error_incompatible_type(node->true_type, son_type, node->son);
        }
        return NULL;
    }
    if(strcmp(node->type, "ParseArgs") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "String[]") == 0 && strcmp(other_son_type, "int") == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "Assign") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        int mapped_son_type = map_int_double(son_type);
        int mapped_other_son_type = map_int_double(other_son_type);
        int valid_int_doubles = mapped_son_type >= 0 && mapped_other_son_type >= 0 && mapped_son_type >= mapped_other_son_type;
        if(!(strcmp(son_type, other_son_type) == 0 && strcmp(son_type, "boolean") == 0 || valid_int_doubles)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup(son_type);
        node->print_true_type = 1;
        return son_type;
    }
    if(strcmp(node->type, "Xor") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!((strcmp(son_type, "int") == 0 || strcmp(son_type, "boolean") == 0) && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("undef");
            node->print_true_type = 1;
            return "undef";
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup(son_type);
        node->print_true_type = 1;
        return son_type;
    }
    if(strcmp(node->type, "Or") == 0 || strcmp(node->type, "And") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "boolean") == 0 && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "Not") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "boolean") == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, NULL, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "Minus") == 0 || strcmp(node->type, "Plus") == 0){
        char *son_type = check(node->son);
        node->print_true_type = 1;
        if (map_int_double(son_type) >= 0){
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup(son_type);
            return son_type;
        } 

        error_operator_cannot_be_applied(node->true_type, son_type, NULL, node);
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("undef");
        return "undef";
    }
    if(strcmp(node->type, "Length") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "String[]") == 0)){
           error_operator_cannot_be_applied(node->true_type, son_type, NULL, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "Eq") == 0 || strcmp(node->type, "Ne") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        int booleans = strcmp(son_type, "boolean") == 0 && strcmp(son_type, other_son_type) == 0;
        int valid_numbers = strcmp(son_type, other_son_type) == 0 || map_int_double(son_type) + map_int_double(other_son_type) == 1;
        if(!(map_int_double(son_type) >= 0 && map_int_double(other_son_type) >= 0 && valid_numbers || booleans)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "Lt") == 0 || strcmp(node->type, "Gt") == 0 || strcmp(node->type, "Le") == 0 || strcmp(node->type, "Ge") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(map_int_double(son_type) >= 0 && map_int_double(other_son_type) >= 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "Add") == 0 || strcmp(node->type, "Mul") == 0 || strcmp(node->type, "Sub") == 0 || strcmp(node->type, "Div") == 0 || strcmp(node->type, "Mod") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        int son_type_mapped = map_int_double(son_type);
        int other_son_type_mapped = map_int_double(other_son_type);
        node->print_true_type = 1;
        if(son_type_mapped < 0 || other_son_type_mapped < 0){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("undef");
            return "undef";
        }

        if(son_type_mapped + other_son_type_mapped == 0){
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("int");
            return "int";
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("double");
        return "double";
    }
    if(strcmp(node->type, "Lshift") == 0 || strcmp(node->type, "Rshift") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "int") == 0 && strcmp(other_son_type, "int") == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("undef");
            node->print_true_type = 1;
            return "undef";
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "DecLit") == 0){
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        char *converted_str = node->value;
        long value = (long)convert_num(node->value, NULL, &converted_str);
        if (value > 2147483647 || value < 0 || strlen(converted_str) >= 10 && bigger_than_long(converted_str)) error_out_of_bounds(node->value, node);
        free(converted_str);
        return "int";
    }
    if(strcmp(node->type, "RealLit") == 0){
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("double");
        node->print_true_type = 1;
        int base_is_zero = 0;
        double value = convert_num(node->value, &base_is_zero, NULL);
        int max_cond = value > 1.7976931348623157e308;
        int min_cond = value == 0 && !base_is_zero;
        if(max_cond || min_cond){
            error_out_of_bounds(node->value, node);
        }
        return "double";
    }
    if(strcmp(node->type, "BoolLit") == 0){
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "StrLit") == 0){
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup("String");
        node->print_true_type = 1;
        create_string(node->value);
        return "String";
    }
    if(strcmp(node->type, "Id") == 0){
        char *id_type = search_el_scope(node->value, scope, curr_params);
        node->print_true_type = 1;
        if(!id_type){
            error_symbol_not_found(node->params, node->value, node);
            if(node->true_type){
                free(node->true_type);
                node->true_type = NULL;
            }
            node->true_type = strdup("undef");
            return "undef";
        }
        if(node->true_type){
            free(node->true_type);
            node->true_type = NULL;
        }
        node->true_type = strdup(id_type);
        return node->true_type;
    }
    return "none";
}

int semantics_check(){
    init_global_symtab();
    check(root);
    return error;
}

void free_tables(){
    free_string(string_list);
    free_sym_tab(symtab_list);
    free_sym_tab(global_symtab);
}