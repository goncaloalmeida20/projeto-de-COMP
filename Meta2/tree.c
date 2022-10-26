Node* create_node(char * type, char * value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {printf("ERRO MEMÓRIA\n"); exit(0);} // No memory
    node->type = type;
	node->value = value;
    node->bro = NULL;
	node->son = NULL;
    return node;
}

void add_son(Node * fat, Node * son) {
    if (fat == NULL || son == NULL) {printf("ERRO ADICIONAR FILHO\n"); return}
    fat->son = son;
}

void add_bro(Node * n, Node * bro) {
    if (n == NULL || bro == NULL) {printf("ERRO ADICIONAR BROTHA\n"); return}
    n->bro = bro;
}

void print_tree(Node* n, int level){
    if (n == NULL) return;
    char points[level * 2];
    int i;
    for(i = 0; i < level * 2; i++) points[i] = '.';
    if (n->value == NULL) printf("%s\n", n->type);
    else printf("%s(%s)\n", n->type, n->value);
    print_tree(n->son);
    print_tree(n->bro);
}

void free_tree(Node* n){
    if (n == NULL) return;
    free_tree(n->son);
    free_tree(n->bro);
    free(n);
}
