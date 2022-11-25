#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "symbol_table.h"

char *scope = NULL;
char *return_type = NULL;

void error_out_of_bounds(char *value, Node *pos){
    printf("Line %d, col %d: Number %s out of bounds\n", pos->line, pos->col, value);
}

void error_ambiguous_func(Param *params, char *method, Node *pos){
    printf("Line %d, col %d: Reference to method %s(", pos->line, pos->col, method);
    print_params(params);
    printf(") is ambiguous\n");
}

void error_incompatible_type(char *statement, char *type, Node *pos){
    printf("Line %d, col %d: Incompatible type %s in %s statement\n", pos->line, pos->col, type, statement);
}

void error_symbol_not_found(Param *params, char *symbol, Node *pos){
    printf("Line %d, col %d: Cannot find symbol %s", pos->line, pos->col, pos->value);
    if(params){
        printf("(");
        print_params(params);
        printf(")\n");
    } 
    else printf("\n");
}

void error_already_defined(Param *params, char* symbol, Node *pos){
    printf("Line %d, col %d: Symbol %s", pos->line, pos->col, symbol);
    if(params){
        printf("(");
        print_params(params);
        printf(")");
    }
    printf(" already defined\n");
}

void error_operator_cannot_be_applied(char *operator, char *type1, char *type2, Node *pos){
    if (type2) printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", pos->line, pos->col, operator, type1, type2);
    else printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", pos->line, pos->col, operator, type1);
}

void declare_method(Node *node){
        Node *method_header = node->son, *method_type = method_header->son, *method_id = method_type->bro;
        Node *method_params = method_id->bro;
        Param *params = NULL;
        int already_exists = 0;
        for(Node *aux = method_params->son; aux; aux = aux->bro){
            params = add_param(params, aux->son->bro->value, aux->son->true_type, &already_exists);
            if(already_exists)
                error_already_defined(NULL, aux->son->bro->value, aux->son->bro);
        }
        if(!insert_el_func(method_id->value, method_type->true_type, params))
            error_already_defined(params, method_id->value, method_id);
}

void declare_var(Node *node){
        Node *type_node = node->son;
        Node *id_node = type_node->bro;
        if(!insert_el(id_node->value, type_node->true_type, scope))
            error_already_defined(NULL, id_node->value, id_node);
}

char* check(Node *node){
    if(!node) return NULL;
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
        char *method_return_type = node->son->son->true_type;
        char *method_id = node->son->son->bro->value;
        scope = strdup(method_id);
        return_type = strdup(method_return_type);
        Node *method_body = node->son->bro;
        for(Node *aux = method_body->son; aux; aux = aux->bro){
            check(aux);
        }
        scope = NULL;
        return_type = NULL;
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
        if(!node->son) return NULL;
        char *son_type = check(node->son);
        if(strcmp(son_type, "void") == 0){
            error_incompatible_type(node->true_type, son_type, node->son);
        }
        else if(strcmp(son_type, return_type) != 0){
            error_incompatible_type(node->true_type, son_type, node->son);
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
            params = add_param(params, NULL, aux->true_type, NULL);
        }
        int ambiguous = 0;
        TableElement *func = search_el_func(func_id, params, &ambiguous);
        if(!func){
            func_id_node->params = params;
            if(ambiguous) error_ambiguous_func(node->son->params, node->son->value, node->son);
            else error_symbol_not_found(node->son->params, node->son->value, node->son);
            func_id_node->true_type = strdup("undef");
            func_id_node->print_true_type = 1;
            func_id_node->params = NULL;
            node->true_type = strdup("undef");
            node->print_true_type = 1;
            return "undef";
        }
        func_id_node->true_type = NULL;
        func_id_node->print_true_type = 1;
        func_id_node->params = param_dup(func->params);
        node->true_type = strdup(func->type);
        node->print_true_type = 1;
        return node->true_type;
    }
    if(strcmp(node->type, "Print") == 0){
        char *son_type = check(node->son);
        if(strcmp(son_type, "void") == 0 || strcmp(son_type, "undef") == 0){
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
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "Assign") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        int mapped_son_type = map_int_double(son_type);
        int mapped_other_son_type = map_int_double(other_son_type);
        if(!(strcmp(son_type, other_son_type) == 0) && !(mapped_son_type >= 0 && mapped_other_son_type >= 0 && mapped_son_type >= mapped_other_son_type)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
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
        }
        node->true_type = strdup(son_type);
        node->print_true_type = 1;
        return son_type;
    }
    if(strcmp(node->type, "Or") == 0 || strcmp(node->type, "And") == 0 || strcmp(node->type, "Xor") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "boolean") == 0 && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
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
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "Minus") == 0 || strcmp(node->type, "Plus") == 0){
        char *son_type = check(node->son);
        node->print_true_type = 1;
        if (map_int_double(son_type) < 0){
            node->true_type = strdup(son_type);
            return son_type;
        } 

        error_operator_cannot_be_applied(node->true_type, son_type, NULL, node);
        node->true_type = strdup("undef");
        return "undef";
    }
    if(strcmp(node->type, "Length") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "String[]") == 0)){
           error_operator_cannot_be_applied(node->true_type, son_type, NULL, node);
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "Eq") == 0 || strcmp(node->type, "Ne") == 0 || strcmp(node->type, "Lt") == 0 || strcmp(node->type, "Gt") == 0 || strcmp(node->type, "Le") == 0 || strcmp(node->type, "Ge") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, other_son_type) == 0 || map_int_double(son_type) + map_int_double(other_son_type) == 1)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
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
            node->true_type = strdup("undef");
            return "undef";
        }

        if(son_type_mapped + other_son_type_mapped == 0){
            node->true_type = strdup("int");
            return "int";
        }
        node->true_type = strdup("double");
        return "double";
    }
    if(strcmp(node->type, "Lshift") == 0 || strcmp(node->type, "Rshift") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "int") == 0 && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node->true_type, son_type, other_son_type, node);
            node->true_type = strdup("undef");
            node->print_true_type = 1;
            return "undef";
        }
        node->true_type = strdup("int");
        node->print_true_type = 1;
        return "int";
    }
    if(strcmp(node->type, "DecLit") == 0){
        node->true_type = strdup("int");
        node->print_true_type = 1;
        long value = atol(node->value);
        if(value > 2147483647 || value < -2147483648) error_out_of_bounds(node->value, node);
        return "int";
    }
    if(strcmp(node->type, "RealLit") == 0){
        node->true_type = strdup("double");
        node->print_true_type = 1;
        return "double";
    }
    if(strcmp(node->type, "BoolLit") == 0){
        node->true_type = strdup("boolean");
        node->print_true_type = 1;
        return "boolean";
    }
    if(strcmp(node->type, "StrLit") == 0){
        node->true_type = strdup("String");
        node->print_true_type = 1;
        return "String";
    }
    if(strcmp(node->type, "Id") == 0){
        char *id_type = search_el_scope(node->value, scope);
        node->print_true_type = 1;
        if(!id_type){
            error_symbol_not_found(node->params, node->value, node);
            node->true_type = strdup("undef");
            return "undef";
        }
        node->true_type = strdup(id_type);
        return node->true_type;
    }
    printf("TYPE ERROR%s\n", node->type);
    return NULL;
}

int semantics_check(){
    init_global_symtab();
    check(root);
    return 1;
}