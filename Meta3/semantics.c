#include <stdio.h>
#include <string.h>
#include "semantics.h"
#include "symbol_table.h"

char *scope = NULL;

void error_already_defined(Node *n){
    printf("Line %d, col %d: Symbol %s already defined\n", n->line, n->col, n->value);
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
    printf("%s\n", node->type);
    return NULL;
}

int semantics_check(){
    init_global_symtab();
    check(root);
    show_table();
    return 1;
}