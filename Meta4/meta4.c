#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meta4.h"
#include "symbol_table.h"

int gen_llvmir(Node *node);

char *curr_return_type = NULL;
int counter = 0;

char *convert_type(char *s){
    if (strcmp(s, "Bool") == 0) return "i1";
    else if (strcmp(s, "Double") == 0) return "double";
    else if (strcmp(s, "Int") == 0) return "i32";
    else return "void";
}

void print_boolean(char *s){
    printf("call void @.print_boolean(i1 %s)\n", s);
}

void print_int(char *i){
    printf("tail call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @p_int, i64 0, i64 0), i32 %s)\n", i);
}

void print_double(char *d){
    printf("tail call i32 (i8*, ...) @printf(i8* getelementptr ([6 x i8], [6 x i8]* @p_double, i64 0, i64 0), double %s)\n", d);
}

void print_func(Node *node){
    char *method_type = convert_type(node->son->type);
    char *method_name = node->son->bro->value;
    printf("\ndefine %s @%s", method_type, method_name);
    Node *aux, *params = node->son->bro->bro->son;
    for(aux = params; aux; aux = aux->bro){
        char *type = convert_type(aux->son->type);
        printf("_%s", type);
    } 
    printf("(");
    for(aux = params; aux; aux = aux->bro){
        if(aux != params) printf(", ");
        char *type = convert_type(aux->son->type);
        char *value = aux->son->son->value;
        printf("%s %%%s", type, value);
    }
    printf(") {\n");

}

/*void load_value(Node *node){
    char *node_conv_type = convert_type(node->true_type);
    if(strcmp(node->type, "Id") == 0){
        // Se o operando for uma variável
        // Guarda-se o nome da variável (ex.: counter_op1 = "b")
        if(strcmp(node_conv_type, "i32") == 0 || strcmp(node_conv_type, "i1") == 0) printf("%%%d = add %s %%%s, 0\n", ++counter, node_conv_type, aux->value);
        else printf("%%%d = fadd double %%%s, 0.0\n", ++counter, aux->value);
    }
    else if(strcmp(node->type, "DecLit") == 0 || strcmp(node->type, "RealLit") == 0 || strcmp(node->type, "BoolLit") == 0){
        // Se o operando for um número
        // Guarda-se o valor do counter onde será guardado o número (ex.: counter_op1 = counter)
        if(strcmp(node->type, "DecLit") == 0 || strcmp(node->type, "BoolLit") == 0) printf("%%%d = add %s %s, 0\n", ++counter, node_conv_type, aux->value);
        else
            printf("%%%d = fadd double %s, 0.0\n", ++counter, aux->value);
        counter_op[count] = counter;
    }
}*/

void two_son_int_double(Node *node, char *op_int, char *op_double){
    // Para fazer as conversões necessárias
        int count = 0;
        Node *aux = node->son;
        int counter_op[2];
        while(count < 2){
            if (count == 1) aux = node->son->bro;
            char *aux_true_type = convert_type(aux->true_type);
            if(strcmp(aux->type, "Id") == 0){
                // Se o operando for uma variável
                // Guarda-se o nome da variável (ex.: counter_op1 = "b")
                if(strcmp(aux_true_type, "i32") == 0)
                    printf("%%%d = add i32 %%%s, 0\n", ++counter, aux->value);
                else
                    printf("%%%d = fadd double %%%s, 0.0\n", ++counter, aux->value);
                counter_op[count] = counter;
            }
            else if(strcmp(aux->type, "DecLit") == 0 || strcmp(aux->type, "RealLit") == 0){
                // Se o operando for um número
                // Guarda-se o valor do counter onde será guardado o número (ex.: counter_op1 = counter)
                if(strcmp(aux->type, "DecLit") == 0)
                    printf("%%%d = add i32 %s, 0\n", ++counter, aux->value);
                else
                    printf("%%%d = fadd double %s, 0.0\n", ++counter, aux->value);
                counter_op[count] = counter;
            }
            else{
                // Se o operando for uma operação
                // Guarda-se o valor do counter onde foi guardado o valor da operação (ex.: counter_op1 = counter - 1)
                gen_llvmir(aux);
                counter_op[count] = counter;
            }
            count++;
        }

        // Para descobrir se é uma adição do tipo: int + int / int + double / double + int / double + double
        char *son_true_type = convert_type(node->son->true_type);
        char *other_son_true_type = convert_type(node->son->bro->true_type);
        if(strcmp(node->true_type, "int") == 0)
           printf("%%%d = %s i32 %%%d, %%%d\n", ++counter, op_int, counter_op[0], counter_op[1]);
        else {
            if(strcmp(son_true_type, "i32") == 0){
                printf("%%%d = uitofp i32 %%%d to double\n", ++counter, counter_op[0]);
                counter_op[0] = counter;
            } else if(strcmp(other_son_true_type, "i32") == 0){
                printf("%%%d = uitofp i32 %%%d to double\n", ++counter, counter_op[1]);
                counter_op[1] = counter;
            }
            printf("%%%d = %s double %%%d, %%%d\n", ++counter, op_double, counter_op[0], counter_op[1]);
        }
}

void two_son_boolean(Node *node, char *op_boolean){
    // Para fazer as conversões necessárias
    int count = 0;
    Node *aux = node->son;
    int counter_op[2];
    while(count < 2){
        if (count == 1) aux = node->son->bro;
        char *aux_true_type = convert_type(aux->true_type);
        if(strcmp(aux->type, "Id") == 0){
            // Se o operando for uma variável ou um valor booleano
            // Guarda-se o valor da variável ou o valor booleano, respetivamente
            printf("%%%d = add i1 %%%s, 0\n", ++counter, aux->value);
            counter_op[count] = counter;
        }
        else if (strcmp(aux->type, "BoolLit") == 0){
            printf("%%%d = add i1 %s, 0\n", ++counter, aux->value);
            counter_op[count] = counter;
        }
        else{
            // Se o operando for uma operação
            // Guarda-se o valor do counter onde foi guardado o valor da operação 
            gen_llvmir(aux);
            counter_op[count] = counter;
        }
        count++;
    }
    printf("%%%d = %s i1 %%%d, %%%d\n", ++counter, op_boolean, counter_op[0], counter_op[1]);
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
        print_func(method_header);
        gen_llvmir(method_body->son);
        printf("}\n");
        return 0;
    }
    if(strcmp(node->type, "Return") == 0){
        return 0;
    }
    if(strcmp(node->type, "Assign") == 0){
        gen_llvmir(node->son->bro);
        if(strcmp(node->type, "Int") == 0 || strcmp(node->type, "Boolean") == 0)
            printf("%%%s = add %s %%%d\n", node->son = counter);
        return 0;
    }
    if(strcmp(node->type, "Add") == 0){
        two_son_int_double(node, "add", "fadd");
        return 0;
    }
    if(strcmp(node->type, "Sub") == 0){
        two_son_int_double(node, "sub", "fsub");
        return 0;
    }
    if(strcmp(node->type, "Mul") == 0){
        two_son_int_double(node, "mul", "fmul");
        return 0;
    }
    if(strcmp(node->type, "Div") == 0){
        two_son_int_double(node, "udiv", "fdiv");
        return 0;
    }
    if(strcmp(node->type, "Mod") == 0){
        two_son_int_double(node, "urem", NULL);
        return 0;
    }
    if (strcmp(node->type, "Xor") == 0){
        two_son_boolean(node, "xor");
        return 0;
    }
    if (strcmp(node->type, "And") == 0){
        two_son_boolean(node, "and");
        return 0;
    }
    if (strcmp(node->type, "Or") == 0){
        two_son_boolean(node, "or");
        return 0;
    }
    if (strcmp(node->type, "Not") == 0){
        int counter_op;
        if(strcmp(node->son->type, "Id") == 0){
            // Se o operando for uma variável ou um valor booleano
            // Guarda-se o valor da variável ou o valor booleano, respetivamente
            printf("%%%d = add i1 %%%s, 0\n", ++counter, node->son->value);
            counter_op = counter;
        }
        else if (strcmp(node->son->type, "BoolLit") == 0){
            printf("%%%d = add i1 %s, 0\n", ++counter, node->son->value);
            counter_op = counter;
        }
        else{
            // Se o operando for uma operação
            // Guarda-se o valor do counter onde foi guardado o valor da operação 
            gen_llvmir(node->son);
            counter_op = counter;
        }
        printf("%%%d = xor i1 1, %%%d\n", ++counter, counter_op);
        return 0;
    }
    if(strcmp(node->type, "Plus") == 0){
        int count = 0;
        Node *aux = node->son;
        char *aux_true_type = convert_type(aux->true_type);
        int counter_op;
        if(strcmp(aux->type, "Id") == 0){
            // Se o operando for uma variável
            // Guarda-se o nome da variável (ex.: counter_op1 = "b")
            if(strcmp(aux_true_type, "i32") == 0)
                printf("%%%d = add i32 0, %%%s\n", ++counter, aux->value);
            else
                printf("%%%d = fadd double 0.0, %%%s\n", ++counter, aux->value);
            counter_op = counter;
        }
        else if(strcmp(aux->type, "DecLit") == 0 || strcmp(aux->type, "RealLit") == 0){
            // Se o operando for um número
            // Guarda-se o valor do counter onde será guardado o número (ex.: counter_op1 = counter)
            if(strcmp(aux->type, "DecLit") == 0)
                printf("%%%d = add i32 0, %%%s\n", ++counter, aux->value);
            else
                printf("%%%d = fadd double 0.0, %%%s\n", ++counter, aux->value);
            counter_op = counter;
        }
        else{
            // Se o operando for uma operação
            // Guarda-se o valor do counter onde foi guardado o valor da operação (ex.: counter_op1 = counter - 1)
            gen_llvmir(aux);
            counter_op = counter;
        }
    }
    if(strcmp(node->type, "Minus") == 0){
        int count = 0;
        char *aux_true_type = convert_type(node->son->true_type);
        int counter_op;
        if(strcmp(node->son->type, "Id") == 0){
            // Se o operando for uma variável
            // Guarda-se o nome da variável (ex.: counter_op1 = "b")
            if(strcmp(aux_true_type, "i32") == 0)
                printf("%%%d = sub i32 0, %%%s\n", ++counter, node->son->value);
            else
                printf("%%%d = fsub double 0.0, %%%s\n", ++counter, node->son->value);
            counter_op = counter;
        }
        else if(strcmp(node->son->type, "DecLit") == 0 || strcmp(node->son->type, "RealLit") == 0){
            // Se o operando for um número
            // Guarda-se o valor do counter onde será guardado o número (ex.: counter_op1 = counter)
            if(strcmp(node->son->type, "DecLit") == 0)
                printf("%%%d = sub i32 0, %%%s\n", ++counter, node->son->value);
            else
                printf("%%%d = fsub double 0.0, %%%s\n", ++counter, node->son->value);
            counter_op = counter;
        }
        else{
            // Se o operando for uma operação
            // Guarda-se o valor do counter onde foi guardado o valor da operação (ex.: counter_op1 = counter - 1)
            gen_llvmir(node->son);
            char *op_true_type = convert_type(node->son->true_type);
            if(strcmp(op_true_type, "i32") == 0)
                printf("%%%d = sub i32 0, %%%d\n", counter + 1, counter);
            else
                printf("%%%d = fsub double 0.0, %%%d\n", counter + 1, counter);
            counter_op = ++counter;
        }
        return 0;
    }
    
    gen_llvmir(node->son);
    gen_llvmir(node->bro);
    return 0;
}

int setup_llvmir(){
    printf("@.false = private unnamed_addr constant [6 x i8] c\"false\\00\"\n");
    printf("@.true = private unnamed_addr constant [5 x i8] c\"true\\00\"\n");
    printf("@.booleans = dso_local global [2 x i8*] [i8* getelementptr ([6 x i8], [6 x i8]* @.false, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.true, i32 0, i32 0)]\n");
    printf("@p_int = private unnamed_addr constant [3 x i8] c\"%%d\\00\"\n");
    printf("@p_double = private unnamed_addr constant [6 x i8] c\"%%.16e\\00\"\n");
    printf("\ndeclare i32 @printf(i8* nocapture readonly, ...) nounwind\n");
    printf("\ndeclare i32 @atoi(i8* nocapture readonly) nounwind\n");
    printf("\ndefine void @.print_boolean(i1 %%.boolean) {\n");
    printf("%%1 = zext i1 %%.boolean to i32\n");
    printf("%%2 = getelementptr [2 x i8*], [2 x i8*]* @.booleans, i32 0, i32 %%1\n");
    printf("%%3 = load i8*, i8** %%2\n");
    printf("tail call i32 (i8*, ...) @printf(i8* %%3)\n");
    printf("ret void\n}\n\n");
    printf("\ndefine i32 @main() {\n");
    gen_llvmir(root);
    print_boolean("%6");
    printf("ret i32 0\n}\n");
    
}