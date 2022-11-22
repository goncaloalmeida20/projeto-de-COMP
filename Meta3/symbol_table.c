#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "symbol_table.h"
#include "tree.h"

SymTab *global_symtab = NULL;
SymTab *symtab_list = NULL;


SymTab* search_symtab(char *scope){	
	if(scope == NULL) return global_symtab;
	
	if(symtab_list == NULL){
		return NULL;
	}

	for(SymTab *aux = symtab_list; aux != NULL; aux = aux->next)
		if(strcmp(scope, aux->scope) == 0) return aux;
	
	printf("SCOPE NOT FOUND ERROR\n");
	return NULL;
}

TableElement *search_el(char *name, TableElement *symbols){
	for(TableElement *aux = symbols; aux; aux=aux->next)
		if(!aux->params && strcmp(aux->name, name)==0)
			return aux;
	return NULL;
}

TableElement *search_el_scope(char *name, char *scope){
	SymTab *symtab = search_symtab(scope);
	if(!symtab) return NULL;
	
	//verificar a existência do identificador no scope atual
	TableElement *el = search_el(name, symtab->symbols);
	if(el) return el;

	//verificar o scope global caso o scope atual não seja o global
	if(!scope) return NULL;
	return search_el(name, global_symtab->symbols);
}

Param* add_param(Param *params, char *name, char *type){
	Param *new_param = (Param *)malloc(sizeof(Param));
	if(!new_param){
		printf("ERRO DE MALLOC ADD_PARAMS\n");
		return NULL;
	}
	if(!name) new_param->name = NULL;
	else new_param->name = strdup(name);
	new_param->param_type = strdup(type);
	new_param->next = NULL;

	if(!params) return new_param;

	Param *aux, *previous;
	for(aux = params; aux; previous = aux, aux = aux->next);
	previous->next = new_param;

	return params;
}

int compare_params(Param *pt1,Param *pt2){
	Param *aux1 = pt1, *aux2 = pt2;
	for(; aux1 && aux2; aux1 = aux1->next, aux2=aux2->next)
		if(strcmp(aux1->param_type, aux2->param_type) != 0) return 0;
	if(!aux1 && !aux2) return 1;
	return 0;
}

TableElement *search_el_func(char *name, Param *params){
	for(TableElement *aux=global_symtab->symbols; aux; aux=aux->next)
		if(aux->params && strcmp(aux->name, name)==0 && compare_params(params, aux->params))
			return aux;
	return NULL;
}

int insert_el(char *name, char *type, char *scope){
	//verificar se o scope existe
	SymTab *symtab = search_symtab(scope);
	if(!symtab){
		return 0;
	}

	if(search_el(name, symtab->symbols)) return 0;
	
	TableElement *previous, *newSymbol=(TableElement*) malloc(sizeof(TableElement));

	newSymbol->name = strdup(name);
	newSymbol->type = strdup(type);
	newSymbol->next = NULL;

	if(!symtab->symbols){
		symtab->symbols = newSymbol;
		return 1;
	}

	for(TableElement *aux= symtab->symbols; aux; previous = aux, aux=aux->next);
	previous->next = newSymbol;
	
	return 1;
}

int insert_symtab(char *name, char *type, Param *params){
	SymTab *newSymTab = (SymTab*) malloc(sizeof(SymTab));
	if(!newSymTab){
		printf("MALLOC ERROR INSERT_SYMTAB\n");
		return 0;
	}

	newSymTab->scope = strdup(name);
	newSymTab->type = strdup(type);
	newSymTab->params = params;
	newSymTab->symbols = NULL;
	newSymTab->next = NULL;

	if(!symtab_list){
		symtab_list = newSymTab;
		return 1;
	}
	SymTab *aux, *previous;
	for(aux = symtab_list; aux; previous=aux, aux=aux->next);
	previous->next = newSymTab;

	return 1;
}

int insert_el_func(char *name, char *type, Param *params){
	if(search_el_func(name, params)) return 0;

	TableElement *newSymbol=(TableElement*) malloc(sizeof(TableElement));
	newSymbol->name = strdup(name);
	if(!params){
		newSymbol->params = add_param(NULL, NULL, "");
	}
	else newSymbol->params = params;
	newSymbol->type = strdup(type);
	newSymbol->next = NULL;
	if(!global_symtab->symbols){
		global_symtab->symbols = newSymbol;
		return insert_symtab(name, type, params);
	}

	TableElement *aux, *previous;
	for(aux=global_symtab->symbols; aux; previous = aux, aux=aux->next);
	previous->next = newSymbol;

	return insert_symtab(name, type, params);
}

int init_global_symtab(){
	global_symtab = (SymTab*) malloc(sizeof(SymTab));
	if(!global_symtab){
		printf("MALLOC ERROR INIT_GLOBAL_SYMTAB\n");
		return 0;
	}
	global_symtab->scope = NULL;
	global_symtab->params = NULL;
	global_symtab->symbols = NULL;
	global_symtab->next = NULL;
	return 1;
}

char* convert_type(char *type){
    if(strcmp(type, "Int") == 0) return "int";
    else if(strcmp(type, "Bool") == 0) return "boolean";
    else if(strcmp(type, "Double") == 0) return "double";
    else if(strcmp(type, "StringArray") == 0) return "String[]";
    else if(strcmp(type, "Void") == 0) return "void";
    else return type;
}

void print_params(Param *params){
    Param *aux;
    for(aux=params; aux; aux = aux->next){
        printf("%s", convert_type(aux->param_type));
        if (aux->next) printf(",");
    }
}

void show_table(){
    TableElement *aux, *aux_symbols;
    Param *aux_param;
    SymTab *aux_symtab;
    printf("===== Class %s Symbol Table =====\n", root->son->value);
    for(aux=global_symtab->symbols; aux; aux=aux->next) {
        if (aux->params) {
            printf("%s\t(", aux->name);
            print_params(aux->params);
            printf(")\t%s\n", convert_type(aux->type));
        }
        else
            printf("%s\t%s\n", aux->name, convert_type(aux->type));
    }
    for(aux_symtab = symtab_list; aux_symtab; aux_symtab = aux_symtab->next){
        printf("\n===== Method %s(", aux_symtab->scope);
        print_params(aux_symtab->params);
        printf(") Symbol Table =====\n"); 
        printf("return\t\t%s\n", convert_type(aux_symtab->type));
		for(aux_param = aux_symtab->params; aux_param; aux_param= aux_param->next)
			printf("%s\t%s\tparam\n", aux_param->name, convert_type(aux_param->param_type));
        for (aux_symbols=aux_symtab->symbols; aux_symbols; aux_symbols = aux_symbols->next)
            printf("%s\t\t%s\n", aux_symbols->name, convert_type(aux_symbols->type));
    }
	printf("\n");	
}
