#include "symbol_table.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

SymTab *global_symtab = NULL;
SymTab *symtab_list = NULL;


SymTab* search_symtab(char *scope){
	if(symtab_list == NULL){
		return NULL;
	}
	
	if(scope == NULL) return global_symtab;

	for(SymTab *aux = symtab_list; aux != NULL; aux = aux->next)
		if(strcmp(scope, aux->scope) == 0) return aux;
	
	printf("SCOPE NOT FOUND ERROR\n");
	return NULL;
}

TableElement *search_el(char *name, TableElement *symbols){
	for(TableElement *aux = symbols; aux; aux=aux->next)
		if(strcmp(aux->name, name)==0)
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
	return search_el(name, global_symtab);
}

ParamTypes* add_param_types(ParamTypes *param_types, char *type){
	ParamTypes *new_param = (ParamTypes *)malloc(sizeof(ParamTypes));
	if(!new_param){
		printf("ERRO DE MALLOC ADD_PARAM_TYPES\n");
		return NULL;
	}
	new_param->param_type = strdup(type);
	new_param->next = NULL;

	if(!param_types) return new_param;

	ParamTypes *aux;
	for(aux = param_types; aux; aux = aux->next);
	aux->next = new_param;

	return param_types;
}

int compare_param_types(ParamTypes *pt1,ParamTypes *pt2){
	ParamTypes *aux1 = pt1, *aux2 = pt2;
	for(; aux1 && aux2; aux1 = aux1->next, aux2=aux2->next)
		if(strcmp(aux1->param_type, aux2->param_type) != 0) return 0;
	if(!aux1 && !aux2) return 1;
	return 0;
}

TableElement *search_el_func(char *name, ParamTypes *param_types){
	for(TableElement *aux=global_symtab; aux; aux=aux->next)
		if(aux->param_types && strcmp(aux->name, name)==0 && compare_param_types(param_types, aux->param_types))
			return aux;
	return NULL;
}

int insert_el(char *name, char *type, char *scope){
	//verificar se o scope existe
	SymTab *symtab = search_symtab(scope);
	if(!symtab){
		return 0;
	}
	
	if(search_el(name, symtab)) return 0;
	
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

int insert_symtab(char *name, char *type, ParamTypes *param_types){
	SymTab *newSymTab = (SymTab*) malloc(sizeof(SymTab));
	newSymTab->scope = strdup(name);
	newSymTab->param_types = param_types;
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

int insert_el_func(char *name, char *type, ParamTypes *param_types){
	if(search_el_func(name, param_types)) return 0;

	TableElement *newSymbol=(TableElement*) malloc(sizeof(TableElement));
	newSymbol->name = strdup(name);
	newSymbol->param_types = param_types;
	newSymbol->type = strdup(type);
	newSymbol->next = NULL;

	if(!global_symtab->symbols){
		global_symtab->symbols = newSymbol;
		return 1;
	}

	TableElement *aux, *previous;
	for(aux=global_symtab; aux; previous = aux, aux=aux->next);
	previous->next = newSymbol;

	return 1;
}

// AINDA POR ALTERAR
void show_table(){
    TableElement *aux;
    printf("\n");
    for(aux=global_symtab; aux; aux=aux->next)
	    printf("%s\t[ParamTypes]\t%s[ntparam]", aux->name, aux->type);
}
