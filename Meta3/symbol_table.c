#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "symbol_table.h"
#include "tree.h"

SymTab *global_symtab = NULL;
SymTab *symtab_list = NULL;

/*
mapeia tipos segundo as seguintes regras:
double -> 1
int -> 0
outro -> -1
*/
int map_int_double(char *type){
    if(strcmp(type, "int") == 0 || strcmp(type, "Int") == 0 || strcmp(type, "DecLit") == 0) return 0;
    if(strcmp(type, "double") == 0 || strcmp(type, "Double") == 0 || strcmp(type, "RealLit") == 0) return 1;
    return -1;
}

int compare_params(Param *p1,Param *p2){
	Param *aux1 = p1, *aux2 = p2;
	int return_promoted = 1; //1-os parâmetros coincidem, 2-há ints em parâmetros double
	int mapped_p1_type, mapped_p2_type;
	for(; aux1 && aux2; aux1 = aux1->next, aux2=aux2->next){
		if(strcmp(aux1->param_type, aux2->param_type) == 0) continue;
		mapped_p1_type = map_int_double(aux1->param_type);
		mapped_p2_type = map_int_double(aux2->param_type);
		//printf("aaaa %s %d %s %d\n", aux1->name, mapped_p1_type, aux2->name, mapped_p2_type);
		if(mapped_p1_type >= 0 && mapped_p2_type >= 0 && mapped_p1_type >= mapped_p2_type){
			return_promoted = 2;
		}
		else return 0;
	}
	if(!aux1 && !aux2) return return_promoted;
	return 0;
}

SymTab* search_symtab(char *scope, Param *params){	
	if(scope == NULL) return global_symtab;
	
	if(symtab_list == NULL){
		return NULL;
	}

	for(SymTab *aux = symtab_list; aux != NULL; aux = aux->next){
		/*printf("aaaa %s %s\n", scope, aux->scope);
		print_params(params);
		printf("\nzzzz\n");
		print_params(aux->params);
		printf("--------\n");*/
		if(strcmp(scope, aux->scope) == 0 && compare_params(params, aux->params) == 1) return aux;
	}
		
	
	printf("SCOPE NOT FOUND ERROR\n");
	return NULL;
}


char *search_el(char *name, SymTab *symtab){
	for(Param *aux = symtab->params; aux; aux = aux->next)
		if(strcmp(aux->name, name)==0)
			return aux->param_type;
	for(TableElement *aux = symtab->symbols; aux; aux=aux->next)
		if(!aux->params && strcmp(aux->name, name)==0)
			return aux->type;
		
	return NULL;
}

char *search_el_scope(char *name, char *scope, Param* params){
	SymTab *symtab = search_symtab(scope, params);
	if(!symtab) return NULL;
	//verificar a existência do identificador no scope atual
	char *el = search_el(name, symtab);
	if(el) return el;

	//verificar o scope global caso o scope atual não seja o global
	if(!scope) return NULL;
	return search_el(name, global_symtab);
}

Param* param_dup(Param *params){
	Param *previous = NULL, *param_list = NULL;
	for(Param *aux = params; aux; aux = aux->next){
		Param *newParam = (Param *)malloc(sizeof(Param));
		if(aux->name) newParam->name = strdup(aux->name);
		else newParam->name = NULL;
		newParam->param_type = strdup(aux->param_type);
		newParam->next = NULL;
		if(param_list){
			previous->next = newParam;
			previous = newParam;
		}
		else{
			param_list = newParam;
			previous = newParam;
		}
	}
	return param_list;
}

Param* add_param(Param *params, char *name, char *type, int *already_exists){
	if(already_exists) *already_exists = 0;
	if(name){
		for(Param *p = params; p; p = p->next)
			if(strcmp(p->name, name) == 0 && already_exists) *already_exists = 1;
	}

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

TableElement *search_el_func(char *name, Param *params, int *ambiguous){
	if(ambiguous) *ambiguous = 0;
	int ambiguous_count = 0;
	TableElement *promoted_int_func = NULL;
	for(TableElement *aux=global_symtab->symbols; aux; aux=aux->next){
		if(aux->params && strcmp(aux->name, name)==0){
			if(!params)
				params = add_param(NULL, NULL, "", NULL);
			int comparison = compare_params(aux->params, params);
			if(comparison == 1) return aux;
			if(ambiguous && comparison == 2){
				if(ambiguous_count == 0){
					promoted_int_func = aux;
					ambiguous_count++;
				}
				else{
					*ambiguous = 1;
					return NULL;
				}
			} 
		}
	}
	return promoted_int_func;
}

int insert_el(char *name, char *type, char *scope, Param *params){
	//verificar se o scope existe
	SymTab *symtab = search_symtab(scope, params);
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

int insert_symtab(char *name, char *type, Param *params){
	SymTab *newSymTab = (SymTab*) malloc(sizeof(SymTab));
	if(!newSymTab){
		printf("MALLOC ERROR INSERT_SYMTAB\n");
		return 0;
	}

	newSymTab->scope = strdup(name);
	newSymTab->type = strdup(type);
	newSymTab->params = param_dup(params);
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
	if(search_el_func(name, params, NULL)) return 0;

	TableElement *newSymbol=(TableElement*) malloc(sizeof(TableElement));
	newSymbol->name = strdup(name);
	if(!params){
		newSymbol->params = add_param(NULL, NULL, "", NULL);
	}
	else newSymbol->params = param_dup(params);
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

/*
char* convert_type(char *type){
    if(strcmp(type, "Int") == 0) return "int";
    else if(strcmp(type, "Bool") == 0) return "boolean";
    else if(strcmp(type, "Double") == 0) return "double";
    else if(strcmp(type, "StringArray") == 0) return "String[]";
    else if(strcmp(type, "Void") == 0) return "void";
    else return type;
}*/

void print_params(Param *params){
    Param *aux;
    for(aux=params; aux; aux = aux->next){
        printf("%s", aux->param_type);
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
            printf(")\t%s\n", aux->type);
        }
        else
            printf("%s\t\t%s\n", aux->name, aux->type);
    }
    for(aux_symtab = symtab_list; aux_symtab; aux_symtab = aux_symtab->next){
        printf("\n===== Method %s(", aux_symtab->scope);
        print_params(aux_symtab->params);
        printf(") Symbol Table =====\n"); 
        printf("return\t\t%s\n", aux_symtab->type);
		for(aux_param = aux_symtab->params; aux_param; aux_param= aux_param->next)
			printf("%s\t\t%s\tparam\n", aux_param->name, aux_param->param_type);
        for (aux_symbols=aux_symtab->symbols; aux_symbols; aux_symbols = aux_symbols->next)
            printf("%s\t\t%s\n", aux_symbols->name, aux_symbols->type);
    }
	printf("\n");	
}
