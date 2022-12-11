#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct param{
	char *name;
	char *param_type;
	int valid;
	struct param *next;
} Param;

typedef struct table_element{
	char *name;
	char *type;
	Param *params;
	struct table_element *next;
} TableElement;

typedef struct sym_tab{
	char *type;
	char *scope;
	Param *params;
	TableElement *symbols;
	struct sym_tab *next;
} SymTab;

extern SymTab *global_symtab;
extern SymTab *symtab_list;

int map_int_double(char *type);
Param* param_dup(Param *params);
Param* add_param(Param *params, char *name, char *type, int *error);
char *search_el_scope(char *name, char *scope, Param *params);
TableElement *search_el_func(char *name, Param *params, int *ambiguous);
int insert_el(char *name, char *type, char *scope, Param *params);
int insert_el_func(char *name, char *type, Param *params);
int init_global_symtab();
void print_params(Param *params);
void show_table();
void free_params(Param *params);
void free_table_element(TableElement *table_element);
void free_sym_tab(SymTab *sym_tab);


#endif
