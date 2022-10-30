#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node* root;

Node* create_node(char * type, char * value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {printf("ERRO MEMÓRIA\n"); exit(0);} // No memory

    node->type = strdup(type);

    if (value == NULL) node->value = NULL;
    else node->value = strdup(value);
        
    node->bro = NULL;
	node->son = NULL;

    return node;
}

Node* add_son(Node *fat, Node *son) {
    if (fat == NULL) {printf("ERRO ADICIONAR FILHO\n"); return NULL;}
    fat->son = son;
    return fat;
}

Node* add_bro(Node *n, Node *bro) {
    if (n == NULL && bro == NULL) {printf("ERRO ADICIONAR BROTHA\n"); return NULL;}
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
    if (n->value == NULL) printf("%s\n", n->type);
    else printf("%s(%s)\n", n->type, n->value);

    print_tree(n->son, level+1);
    print_tree(n->bro, level);
}

void free_tree(Node* n){
    if (n == NULL) return;
    free_tree(n->son);
    free_tree(n->bro);
    free(n);
}
