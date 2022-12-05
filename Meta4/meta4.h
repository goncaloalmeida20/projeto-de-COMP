#ifndef META4_H
#define META4_H

#include "tree.h"

typedef struct _var_counter{
    char *name;
    char *counter;
    struct _var_counter *next;
} VarCounter;

int setup_llvmir();

#endif