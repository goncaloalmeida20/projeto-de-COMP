#include "symbol_table.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

extern TableElement* symtab;

TableElement *insert_el(char *name, char *type)
{
	TableElement *newSymbol=(TableElementt*) malloc(sizeof(TableElement));
	TableElement *aux;
	TableElement *previous;

	strcpy(newSymbol->name, name);
	newSymbol->type=type;
	newSymbol->next=NULL;	

	if(symtab)	//Se a tabela ja tem elementos
	{	//Procura cauda da lista e verifica se simbolo ja existe (NOTA: assume-se uma tabela de simbolos globais!)
		for(aux=symtab; aux; previous=aux, aux=aux->next)
			if(strcmp(aux->name, name)==0)
				return NULL;
		
		previous->next=newSymbol;	
	}
	else symtab=newSymbol;

	return newSymbol; 
}

// AINDA POR ALTERAR
void show_table()
{
    TableElement *aux;
    printf("\n");
    for(aux=symtab; aux; aux=aux->next)
	    printf("%s\t[ParamTypes]\t%s[ntparam]", aux->name, aux->type);
}

TableElement *search_el(char *name)
{
    TableElement *aux;

    for(aux=symtab; aux; aux=aux->next)
    	if(strcmp(aux->name, name)==0)
		    return aux;

    return NULL;
}





