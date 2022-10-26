typedef struct node{
	char * type;
	char * value;
	struct node * son;
    struct node * bro;
} Node;

Node* root;

Node* create_node(char * type, char * value);
void add_son(Node * fat, Node * son);

void print_tree(Node* n, int nivel);
void free_tree(Node* n);
