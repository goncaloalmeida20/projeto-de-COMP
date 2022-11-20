#include <stdio.h>
#include <string.h>
#include "semantics.h"
#include "symbol_table.h"

char *scope = NULL;

void error_already_defined(Node *n){
    printf("Line %d, col %d: Symbol %s already defined\n", n->line, n->col, n->value);
}

int check(Node *node){
    if(!node) return 0;
    if(strcmp(node->type, "Program") == 0){
        int error_count = 0;
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            error_count += check(aux);
        }
        return 0;
    }
    if(strcmp(node->type, "FieldDecl") == 0 || strcmp(node->type, "VarDecl") == 0){
        Node *type_node = node->son;
        Node *id_node = type_node->bro;
        if(!insert_el(id_node->value, type_node->type, scope)){
            error_already_defined(id_node);
            return 1;
        }
        return 0;
    }
    if(strcmp(node->type, "MethodDecl") == 0){

    }
    printf("%s\n", node->type);
}

int semantics_check(){
    init_global_symtab();
    int error_count = check(root);
    show_table();
    return 1;
}