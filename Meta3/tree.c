/*
    Autores:
        Gonçalo Fernandes Diogo de Almeida, nº2020218868
        João Bernardo de Jesus Santos, nº2020218995
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* root = NULL;

Node* create_node(char *type, char *value, int line, int col, char *true_type) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {printf("ERRO MEMÓRIA\n"); exit(0);} // No memory

    node->print_true_type = 0;
    node->check_node = 1;
    node->params = NULL;
    node->type = strdup(type);
    if (value == NULL) node->value = NULL;
    else node->value = strdup(value);
    if(true_type) node->true_type = strdup(true_type);
    else node->true_type = NULL;
        
    node->bro = NULL;
	node->son = NULL;
    
    node->line = line;
    node->col = col;

    return node;
}

Node* add_son(Node *fat, Node *son) {
    if (fat == NULL) {printf("ERRO ADICIONAR FILHO\n"); return NULL;}
    fat->son = son;
    return fat;
}

Node* add_bro(Node *n, Node *bro) {
    if (n == NULL && bro == NULL) {return NULL;}
    if (n == NULL) return bro;
    if (bro == NULL) return n;
    Node *n_bro = n;
    while(n_bro->bro != NULL) n_bro = n_bro->bro;
    n_bro->bro = bro;
    return n;
}

void print_tree(Node *n, int level){
    if (n == NULL) return;
    int i;
    
    for(i = 0; i < level * 2; i++) putchar('.');
    if (n->value == NULL){
        if(n->print_true_type){
            if(n->params){
                printf("%s - (", n->type);
                print_params(n->params);
                printf(")\n");
            }else printf("%s - %s\n", n->type, n->true_type);
        } else printf("%s\n", n->type);
    } 
    else{
        if(n->print_true_type){
            if(n->params){
                printf("%s(%s) - (", n->type, n->value);
                print_params(n->params);
                printf(")\n");
            }
            else printf("%s(%s) - %s\n", n->type, n->value, n->true_type);
        } 
        else printf("%s(%s)\n", n->type, n->value);
    }
    //else printf("%s(%s) %d %d\n", n->type, n->value, n->line, n->col);

    print_tree(n->son, level+1);
    print_tree(n->bro, level);
}

void free_tree(Node* n){
    if (n == NULL) return;
    free_tree(n->son);
    free_tree(n->bro);
    free(n->type);
    if(n->value != NULL) free(n->value);
    free(n);
}

Node* add_if(Node *expr, Node *statement_if, Node *statement_else, int line, int col){
    if(statement_if == NULL) statement_if = create_node("Block", NULL, 0, 0, NULL);
    if(statement_else == NULL) statement_else = create_node("Block", NULL, 0, 0, NULL);
    return add_son(create_node("If", NULL, line, col, "if"), add_bro(expr, add_bro(statement_if,statement_else)));
}

Node* add_while(Node *expr, Node *statement_while, int line, int col){
    if(statement_while == NULL) statement_while = create_node("Block", NULL, 0, 0, NULL);
    return add_son(create_node("While", NULL, line, col, "while"), add_bro(expr, statement_while));
}

Node* create_blocks(Node *statement1, Node* statement2){
    if(statement1 == NULL && statement2 == NULL) return NULL;
    if(statement1 == NULL) return statement2;
    if(statement2 == NULL) return statement1;
    return add_son(create_node("Block", NULL, 0, 0, NULL), add_bro(statement1, statement2));
}