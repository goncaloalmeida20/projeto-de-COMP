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

typedef struct symtab_list{
	char *scope;
	TableElement *symtab;
	struct symtab_list *next;
} SymTabList;

extern TableElement *global_symtab;
extern SymTabList *symtab_list;

TableElement *search_el_scope(char *name, char *scope);
TableElement *search_el_func(char *name, ParamTypes *param_types);
int insert_el(char *name, char *type, char *scope);
int insert_el_func(char *name, char *type, ParamTypes *param_types);
void show_table();

#endif
