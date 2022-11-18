#include <stdio.h>
#include <string.h>
#include "semantics.h"
#include "symbol_table.h"

int sem_check(){
    init_tables();
    check(root);
}

int check(Node *node){
    if(!node) return 0;
    if(strcmp(node->type, "Program") == 0){
        for(Node *aux = node->son; aux; aux = aux->bro){
            check(aux);
        }
    }
    printf("%s\n", node->type);
}