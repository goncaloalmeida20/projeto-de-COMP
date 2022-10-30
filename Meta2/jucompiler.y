%{
    /*
        Autores:
            Gonçalo Fernandes Diogo de Almeida, nº2020218868
            João Bernardo de Jesus Santos, nº2020218995
    */
    
    #include <stdio.h>
    #include <string.h>
    #include "tree.h"

    extern int yylex(void);
    extern void yyerror(const char*);
    extern char* yytext;
    char current_type[SIZE];
    int flag = 0, flag_yacc = 0;

%}
%union{char* str; Node* node;}
%token BOOL INT DOUBLE AND ASSIGN STAR COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ SEMICOLON ARROW LSHIFT RSHIFT XOR CLASS DOTLENGTH ELSE IF PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID WHILE
%token <str> RESERVED STRLIT BOOLLIT INTLIT REALLIT ID
%nonassoc ASSIGN
%nonassoc EQ GE GT LE LT NE
%right LPAR
%left RPAR
%right IF ELSE
%left OR
%left AND
%left XOR
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV
%left MOD
%right NOT
%type <node> MethodFieldDecl MethodDecl FieldDecl FieldCommaId Type MethodHeader MethodBody FormalParams StatementVarDecl CommaTypeIds VarDecl VarCommaId Statement     MethodInvocation CommaExpr Assignment ParseArgs Expr
%%

Program: CLASS ID LBRACE RBRACE                     {root = create_node("Program", NULL); add_son(root, create_node("Id",$2));}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE        {root = create_node("Program", NULL); add_son(root, add_bro(create_node("Id",$2), $4));}   
    ;

MethodFieldDecl: MethodDecl                         {$$=$1;}
    | FieldDecl                                     {$$=$1;}
    | SEMICOLON                                     {$$=NULL;}
    | MethodDecl MethodFieldDecl                    {$$=add_bro($1,$2);}
    | FieldDecl MethodFieldDecl                     {$$=add_bro($1,$2);}
    | SEMICOLON MethodFieldDecl                     {$$=$2;}
    ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody   {$$=add_son(create_node("MethodDecl", NULL), add_bro($3, $4));}

FieldDecl: PUBLIC STATIC Type ID SEMICOLON          {$$=add_son(create_node("FieldDecl",NULL), add_bro($3, create_node("Id", $4)));} 
    | PUBLIC STATIC Type ID FieldCommaId SEMICOLON  {$$=add_bro(add_son(create_node("FieldDecl",NULL), add_bro($3, create_node("Id", $4))), $5);}   
    ;

FieldCommaId: COMMA ID                              {$$=add_son(create_node("FieldDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2)));}   
    | COMMA ID FieldCommaId                         {$$=add_bro(add_son(create_node("FieldDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2))), $3);}   
    ;

Type: BOOL                                          {$$=create_node("Bool", NULL); strcpy(current_type, "Bool"); }
    | INT                                           {$$=create_node("Int", NULL); strcpy(current_type, "Int");}
    | DOUBLE                                        {$$=create_node("Double", NULL); strcpy(current_type, "Double"); }
    ;

MethodHeader: Type ID LPAR RPAR                     {$$=add_son(create_node("MethodHeader", NULL), add_bro($1, create_node("Id",$2)));}
    | Type ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL), add_bro($1, add_bro(create_node("Id",$2), add_son(create_node("MethodParams", NULL),$4))));}
    | VOID ID LPAR RPAR                             {$$=add_son(create_node("MethodHeader", NULL), add_bro(create_node("Void", NULL), create_node("Id",$2)));}
    | VOID ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL), add_bro(create_node("Void", NULL), add_bro(create_node("Id",$2), $4)));}
    ;

FormalParams: Type ID                               {$$=add_son(create_node("ParamDecl", NULL), add_bro($1, create_node("Id", $2)));}
    | Type ID CommaTypeIds                          {$$=add_bro(add_son(create_node("ParamDecl", NULL), add_bro($1, create_node("Id", $2))),$3);}
    | STRING LSQ RSQ ID                             {$$=add_son(create_node("ParamDecl", NULL), add_bro(create_node("StringArray", NULL), create_node("Id", $4)));}
    ;

CommaTypeIds: COMMA Type ID                         {$$=add_son(create_node("ParamDecl", NULL), add_bro($2, create_node("Id", $3)));}
    | COMMA Type ID CommaTypeIds                    {$$=add_bro(add_son(create_node("ParamDecl", NULL), add_bro($2, create_node("Id", $3))),$4);}
    ;

MethodBody: LBRACE RBRACE                           {$$=create_node("MethodBody", NULL);}
    | LBRACE StatementVarDecl RBRACE                {$$=add_son(create_node("MethodBody", NULL), $2);}
    ;

StatementVarDecl: Statement                         {$$=$1;}    
    | VarDecl                                       {$$=$1;}
    | Statement StatementVarDecl                    {$$=add_bro($1,$2);}
    | VarDecl StatementVarDecl                      {$$=add_bro($1,$2);}
    ;

VarDecl: Type ID SEMICOLON                          {$$=add_son(create_node("VarDecl",NULL), add_bro($1, create_node("Id", $2)));}
    | Type ID VarCommaId SEMICOLON                  {$$=add_bro(add_son(create_node("VarDecl",NULL), add_bro($1, create_node("Id", $2))), $3);}
    ;

VarCommaId: COMMA ID                                {$$=add_son(create_node("VarDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2)));}   
    | COMMA ID VarCommaId                           {$$=add_bro(add_son(create_node("VarDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2))), $3);}   
    ;


Statement: LBRACE RBRACE                            {;}
    | LBRACE MultipleStatements RBRACE              {;}
    | IF LPAR Expr RPAR Statement                   {;}
    | IF LPAR Expr RPAR Statement ELSE Statement    {;}
    | WHILE LPAR Expr RPAR Statement                {;}
    | RETURN SEMICOLON                              {;}
    | RETURN Expr SEMICOLON                         {;}
    | SEMICOLON                                     {$$=NULL;}
    | MethodInvocation SEMICOLON                    {;}
    | Assignment SEMICOLON                          {;}
    | ParseArgs SEMICOLON                           {;}
    | PRINT LPAR STRLIT RPAR SEMICOLON              {;}
    | PRINT LPAR Expr RPAR SEMICOLON                {;}
    ;

MultipleStatements: Statement MultipleStatements    {;}
    | Statement                                     {;}
    ;

MethodInvocation: ID LPAR RPAR                      {printf("Id %s\n", $1);}
    | ID LPAR Expr RPAR                             {printf("Id %s\n", $1);}
    | ID LPAR Expr CommaExpr RPAR                   {printf("Id %s\n", $1);}
    ;

CommaExpr: COMMA Expr                               {;}
    | COMMA Expr CommaExpr                          {;}
    ;

Assignment: ID ASSIGN Expr                          {printf("Assign\n"); printf("Id %s\n", $1);}

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR       {printf("ParseInt\n"); printf("Id %s\n", $3);}

Expr: Expr PLUS Expr                                {printf("Sum\n");}
    | Expr MINUS Expr                               {printf("Sub\n");}
    | Expr STAR Expr                                {printf("Star\n");}
    | Expr DIV Expr                                 {printf("Div\n");}
    | Expr MOD Expr                                 {printf("Mod\n");}
    | Expr AND Expr                                 {printf("And\n");}
    | Expr OR Expr                                  {printf("Or\n");}
    | Expr XOR Expr                                 {printf("Xor\n");}
    | Expr LSHIFT Expr                              {printf("Lshift\n");}
    | Expr RSHIFT Expr                              {printf("Rshift\n");}
    | Expr EQ Expr                                  {printf("Eq\n");}
    | Expr GE Expr                                  {printf("Ge\n");}
    | Expr GT Expr                                  {printf("Gt\n");}
    | Expr LE Expr                                  {printf("Le\n");}
    | Expr LT Expr                                  {printf("Lt\n");}
    | Expr NE Expr                                  {printf("Ne\n");}
    | MINUS Expr                                    {printf("Minus\n");}
    | NOT Expr                                      {printf("Not\n");}
    | PLUS Expr                                     {printf("Plus\n");}
    | LPAR Expr RPAR                                {;}
    | MethodInvocation                              {;}
    | Assignment                                    {;}
    | ParseArgs                                     {;}
    | ID DOTLENGTH                                  {printf("Id %s\n", $1); printf("DotLength\n");}
    | ID                                            {printf("Id %s\n", $1);}
    | INTLIT                                        {printf("IntLit %s\n", $1);} 
    | REALLIT                                       {printf("RealLit %s\n", $1);}
    | BOOLLIT                                       {printf("BoolLit %s\n", $1);}
    ;
%%
/*
int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0) {
            flag = 1;
            yylex();
        }
        else if(strcmp(argv[1], "-e1") == 0) {
            flag = 0;
            yylex();
        }
        else if(strcmp(argv[1], "-e2") == 0) {
            flag_yacc = 0;
            yyparse();
        }
        else if(strcmp(argv[1], "-t") == 0) {
            flag_yacc = 1;
            yyparse();
        }
    }
    return 0;
}*/
void yyerror (const char *s) { 
  printf ("%s: %s\n", s, yytext);
}
/*int main(int argc, char* argv[]) {
    if(argc > 1){
        if(strcmp(argv[1], "-t") == 0) flag = 1;
        else if(strcmp(argv[1], "-e2") == 0) flag = 0;
    }
    yyparse();
    return 0;
}*/
