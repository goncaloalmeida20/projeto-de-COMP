#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meta4.h"

void print_boolean(char *s){
    int len = strlen(s);
    printf("%%print_boolean = getelementptr [%d x i8], [%d x i8]* @p_%s, i64 0, i64 0\n", len+1, len+1, s);  
    printf("tail call i32 (i8*, ...) @printf(i8* %%print_boolean, i32 %s)\n", s);
}

void print_int(char *i){
    printf("%%print_int = getelementptr [3 x i8], [3 x i8]* @p_int, i64 0, i64 0\n");  
    printf("tail call i32 (i8*, ...) @printf(i8* %%print_int, i32 %s)\n", i);
}

void print_double(char *d){
    printf("%%print_double = getelementptr [6 x i8], [6 x i8]* @p_double, i64 0, i64 0\n");  
    printf("tail call i32 (i8*, ...) @printf(i8* %%print_double, double %s)\n", d);
}

int gen_llvmir(Node *node){
    if(!node) return 0;
    if(strcmp(node->type, "Program") == 0){
        for(Node *aux = node->son->bro; aux; aux = aux->bro){
            gen_llvmir(aux);
        }
        return 0;
    }
    if(strcmp(node->type, "MethodDecl") == 0){
        Node *method_header = node->son, *method_body = method_header->son->bro;
        
        return 0;
    }
    return 0;
}

int setup_llvmir(){
    printf("@p_true = private unnamed_addr constant [5 x i8] c\"true\\00\"\n");
    printf("@p_false = private unnamed_addr constant [6 x i8] c\"false\\00\"\n");
    printf("@p_int = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
    printf("@p_double = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("\ndeclare i32 @printf(i8* nocapture readonly, ...) nounwind\n");
    printf("\ndeclare i32 @atoi(i8* nocapture readonly) nounwind\n");
    printf("\ndefine i32 @main() {\n");
    print_double("12.1e20");
    printf("ret i32 0\n}\n");
    gen_llvmir(root);
}