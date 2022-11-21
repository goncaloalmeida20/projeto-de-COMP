#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct param{
	char *name;
	char *param_type;
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

Param* add_param(Param *params, char *name, char *type);
TableElement *search_el_scope(char *name, char *scope);
TableElement *search_el_func(char *name, Param *params);
int insert_el(char *name, char *type, char *scope);
int insert_el_func(char *name, char *type, Param *params);
int init_global_symtab();
void show_table();
char* convert_type(char *type);

#endif
