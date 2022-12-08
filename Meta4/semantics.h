#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "tree.h"
#include "symbol_table.h"

typedef struct _str{
    int string_id, len;
    char *value;
    struct _str *next;
} Str; 

extern Str *string_list;

int semantics_check();
void free_tables();
void free_string();
Str* search_string(char *value);

#endif