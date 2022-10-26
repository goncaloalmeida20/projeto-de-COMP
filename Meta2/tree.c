Node* create_node(char * type, char * value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) exit(0); // No memory
    node->type = type;
	node->value = value;
    node->bro = NULL;
	node->son = NULL;
    return node;
}

void add_son(Node * fat, Node * son) {
    if (fat == NULL || son == NULL) return;
    fat->son = son;
}

void print_tree(Node* n, int level){
    if (n == NULL) return;

}

void free_tree(Node* n){

}
