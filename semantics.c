#include <stdio.h>
#include <string.h>
#include "semantics.h"
#include "symbol_table.h"

char *scope = NULL;

/*
mapeia tipos segundo as seguintes regras:
double -> 1
int -> 0
outro -> -1
*/
int map_int_double(char *type){
    if(strcmp(type, "int") == 0) return 0;
    if(strcmp(type, "double") == 0) return 1;
    return -1;
}

void error_symbol_not_found(Node *n){
    printf("Line %d, col %d: Cannot find symbol %s\n", n->line, n->col, n->value);
}

void error_already_defined(Node *n){
    printf("Line %d, col %d: Symbol %s already defined\n", n->line, n->col, n->value);
}

void error_operator_cannot_be_applied(Node *n, char *type1, char *type2){
    if (type2) printf("Line %d, col %d: Operator %s cannot be applied to types %s, %s\n", n->line, n->col, n->type, type1, type2);
    else printf("Line %d, col %d: Operator %s cannot be applied to type %s\n", n->line, n->col, n->type, type1);
}

void declare_method(Node *node){
        Node *method_header = node->son, *method_type = method_header->son, *method_id = method_type->bro;
        Node *method_params = method_id->bro;
        Param *params = NULL;
        
        for(Node *aux = method_params->son; aux; aux = aux->bro){
            params = add_param(params, aux->son->bro->value, aux->son->type);
        }
        insert_el_func(method_id->value, method_type->type, params);
}

void declare_var(Node *node){
        Node *type_node = node->son;
        Node *id_node = type_node->bro;
        if(!insert_el(id_node->value, type_node->type, scope))
            error_already_defined(id_node);
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
        char *method_id = node->son->son->bro->value;
        scope = strdup(method_id);
        Node *method_body = node->son->bro;
        for(Node *aux = method_body->son; aux; aux = aux->bro){
            check(aux);
        }
        scope = NULL;
        return NULL;
    }
    if(strcmp(node->type, "Block") == 0){
        if(!node->son) return NULL;
        for(Node *aux = node->son; aux; aux = aux->bro) check(aux);
        return NULL;
    }
    if(strcmp(node->type, "If") == 0){
        check(node->son);
        check(node->son->bro);
        check(node->son->bro->bro);
        return NULL;
    }
    if(strcmp(node->type, "While") == 0){
        check(node->son);
        check(node->son->bro);
        return NULL;
    }
    if(strcmp(node->type, "Return") == 0){
        check(node->son);
        return NULL;
    }
    if(strcmp(node->type, "Print") == 0){
        check(node->son);
        return NULL;
    }
    if(strcmp())
    if(strcmp(node->type, "Or") == 0 || strcmp(node->type, "And") == 0 || strcmp(node->type, "Xor") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "boolean") == 0 && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node, son_type, other_son_type);
        }
        node->semantic_type = strdup("boolean");
        return "boolean";
    }
    if(strcmp(node->type, "Not") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "boolean") == 0)){
            error_operator_cannot_be_applied(node, son_type, NULL);
        }
        node->semantic_type = strdup("boolean");
        return "boolean";
    }
    if(strcmp(node->type, "Minus") == 0 || strcmp(node->type, "Plus") == 0){
        char *son_type = check(node->son);

        if (map_int_double(son_type) < 0){
            node->semantic_type = strdup(son_type);
            return son_type;
        } 

        error_operator_cannot_be_applied(node, son_type, NULL);
        node->semantic_type = strdup("undef");
        return "undef";
    }
    if(strcmp(node->type, "Length") == 0){
        char *son_type = check(node->son);
        if(!(strcmp(son_type, "StringArray") == 0)){
           error_operator_cannot_be_applied(node, son_type, NULL);
        }
        node->semantic_type = strdup("int");
        return "int";
    }
    if(strcmp(node->type, "Eq") == 0 || strcmp(node->type, "Ne") == 0 || strcmp(node->type, "Lt") == 0 || strcmp(node->type, "Gt") == 0 || strcmp(node->type, "Le") == 0 || strcmp(node->type, "Ge") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node, son_type, other_son_type);
        }
        node->semantic_type = strdup("boolean");
        return "boolean";
    }
    if(strcmp(node->type, "Add") == 0 || strcmp(node->type, "Mul") == 0 || strcmp(node->type, "Sub") == 0 || strcmp(node->type, "Div") == 0 || strcmp(node->type, "Mod") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        int son_type_mapped = map_int_double(son_type);
        int other_son_type_mapped = map_int_double(other_son_type);
        if(son_type_mapped < 0 || other_son_type_mapped < 0){
            error_operator_cannot_be_applied(node, son_type, other_son_type);
            node->semantic_type = strdup("undef");
            return "undef";
        }

        if(son_type_mapped + other_son_type_mapped == 0){
            node->semantic_type = strdup("int");
            return "int";
        }
        node->semantic_type = strdup("double");
        return "double";
    }
    if(strcmp(node->type, "Lshift") == 0 || strcmp(node->type, "Rshift") == 0){
        char *son_type = check(node->son);
        char *other_son_type = check(node->son->bro);
        if(!(strcmp(son_type, "int") == 0 && strcmp(son_type, other_son_type) == 0)){
            error_operator_cannot_be_applied(node, son_type, other_son_type);
        }
        node->semantic_type = strdup("int");
        return "int";
    }
    if(strcmp(node->type, "DecLit") == 0){
        node->semantic_type = strdup("int");
        return "int";
    }
    if(strcmp(node->type, "RealLit") == 0){
        node->semantic_type = strdup("double");
        return "double";
    }
    if(strcmp(node->type, "BoolLit") == 0){
        node->semantic_type = strdup("boolean");
        return "boolean";
    }
    if(strcmp(node->type, "Id") == 0){
        TableElement *id_found = search_el_scope(node->value, scope);
        if(!id_found){
            error_symbol_not_found(node);
            node->semantic_type = strdup("undef");
            return "undef";
        }
        node->semantic_type = strdup(convert_type(id_found->type));
        return node->semantic_type;
    }
    printf("TYPE ERROR%s\n", node->type);
    return NULL;
}

int semantics_check(){
    init_global_symtab();
    check(root);
    show_table();
    return 1;
}