/*
	Autores:
		Gonçalo Fernandes Diogo de Almeida, nº2020218868
		João Bernardo de Jesus Santos, nº2020218995
*/

#ifndef TREE_H
#define TREE_H

#include "symbol_table.h"

#define TYPE_SIZE 100

typedef struct _tk{
	char *value;
	int line;
    int col;
} Tk;

typedef struct node{
	char *type;
	char *value;
	char *semantic_type;
	Param *params;
	struct node * son;
    struct node * bro;
    int line;
    int col;
} Node;

extern Node* root;

Node* create_node(char *type, char *value, int line, int col);
Node* add_son(Node *fat, Node *son);
Node* add_bro(Node *n, Node *bro);

Node* add_if(Node *expr, Node *statement_if, Node *statement_else, int line, int col);
Node* add_while(Node *expr, Node *statement_while, int line, int col);

Node* create_blocks(Node *statement1, Node* statement2);

void print_tree(Node *n, int level);
void free_tree(Node *n);

#endif
