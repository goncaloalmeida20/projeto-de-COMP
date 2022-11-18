#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct param_types{
	char* param_type;
	struct param_types *next;
} ParamTypes;

typedef struct table_element{
	char *name;
	char *type;
	ParamTypes *param_types;
	struct table_element *next;
} TableElement;

typedef struct sym_tab{
	char *scope;
	ParamTypes *param_types;
	TableElement *symbols;
	struct sym_tab *next;
} SymTab;

extern SymTab *global_symtab;
extern SymTab *symtab_list;

ParamTypes* add_param_types(ParamTypes *param_types, char *type);
TableElement *search_el_scope(char *name, char *scope);
TableElement *search_el_func(char *name, ParamTypes *param_types);
int insert_el(char *name, char *type, char *scope);
int insert_el_func(char *name, char *type, ParamTypes *param_types);
void show_table();

#endif
