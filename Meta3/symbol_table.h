#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct table_element{
	char name[32];
	char * type;
	struct table_element *next;
} TableElement;

TableElement *insert_el(char *name, char *type);
void show_table();
TableElement *search_el(char *name);

#endif
