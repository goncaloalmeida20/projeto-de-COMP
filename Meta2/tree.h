typedef struct node{
	char * type;
	char * value;
	struct node * son;
} Node;

Node* root;

Node* create_node(char * type, char * value);
void add_son(Node * fat, Node * son);
void add_bro(Node * n, Node * bro);

void print_tree(Node* n, int level);
void free_tree(Node* n);
