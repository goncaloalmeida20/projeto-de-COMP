#ifndef TREE_H
#define TREE_H

#define SIZE 1024

typedef struct node{
	char *type;
	char *value;
	struct node * son;
    struct node * bro;
} Node;

extern Node* root;

Node* create_node(char *type, char *value);
Node* add_son(Node *fat, Node *son);
Node* add_bro(Node *n, Node *bro);

Node* add_if(Node *expr, Node *statement_if, Node *statement_else);
Node* add_while(Node *expr, Node *statement_while);

void print_tree(Node *n, int level);
void free_tree(Node *n);

#endif
