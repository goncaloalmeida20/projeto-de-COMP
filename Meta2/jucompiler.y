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
    extern void yyerror(char*);
    extern char* yytext;
    
    char current_type[SIZE];

    int line_yacc = 1, col_yacc = 1;
    int flag_yacc = 0;

%}
%union{char* str; Node* node;}
%token BOOL INT DOUBLE AND ASSIGN STAR COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ SEMICOLON ARROW LSHIFT RSHIFT XOR CLASS DOTLENGTH ELSE IF PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID WHILE
%token <str> RESERVED STRLIT BOOLLIT INTLIT REALLIT ID
%right LPAR
%left RPAR
%right IF ELSE
%left ASSIGN
%left OR
%left AND
%left XOR
%left EQ NE
%left GE GT LE LT
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV
%left MOD
%right UNARY
%right NOT
%type <node> MethodFieldDecl MethodDecl FieldDecl FieldCommaId Type MethodHeader MethodBody FormalParams StatementVarDecl CommaTypeIds VarDecl VarCommaId Statement MultipleStatements   MethodInvocation CommaExpr Assignment ParseArgs Expr
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
    | error SEMICOLON                               {$$=NULL;}
    ;

FieldCommaId: COMMA ID                              {$$=add_son(create_node("FieldDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2)));}   
    | COMMA ID FieldCommaId                         {$$=add_bro(add_son(create_node("FieldDecl",NULL), add_bro(create_node(current_type, NULL), create_node("Id", $2))), $3);}   
    ;

Type: BOOL                                          {$$=create_node("Bool", NULL); strcpy(current_type, "Bool"); }
    | INT                                           {$$=create_node("Int", NULL); strcpy(current_type, "Int");}
    | DOUBLE                                        {$$=create_node("Double", NULL); strcpy(current_type, "Double"); }
    ;

MethodHeader: Type ID LPAR RPAR                     {$$=add_son(create_node("MethodHeader", NULL), add_bro($1, add_bro(create_node("Id",$2), create_node("MethodParams", NULL))));}
    | Type ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL), add_bro($1, add_bro(create_node("Id",$2), add_son(create_node("MethodParams", NULL),$4))));}
    | VOID ID LPAR RPAR                             {$$=add_son(create_node("MethodHeader", NULL), add_bro(create_node("Void", NULL), add_bro(create_node("Id",$2), create_node("MethodParams", NULL))));}
    | VOID ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL), add_bro(create_node("Void", NULL), add_bro(create_node("Id",$2), add_son(create_node("MethodParams", NULL),$4))));}
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


Statement: LBRACE RBRACE                            {$$=create_node("Block", NULL);}
    | LBRACE Statement RBRACE                       {$$=$2;}
    | LBRACE Statement MultipleStatements RBRACE    {$$=add_son(create_node("Block", NULL), add_bro($2, $3));}
    | IF LPAR Expr RPAR Statement                   {$$=add_if($3, $5, NULL);}
    | IF LPAR Expr RPAR Statement ELSE Statement    {$$=add_if($3, $5, $7);}
    | WHILE LPAR Expr RPAR Statement                {$$=add_while($3, $5);}
    | RETURN SEMICOLON                              {$$=create_node("Return", NULL);}
    | RETURN Expr SEMICOLON                         {$$=add_son(create_node("Return", NULL), $2);}
    | SEMICOLON                                     {$$=NULL;}
    | MethodInvocation SEMICOLON                    {$$=add_son(create_node("Call", NULL), $1);}
    | Assignment SEMICOLON                          {$$=add_son(create_node("Assign", NULL), $1);}
    | ParseArgs SEMICOLON                           {$$=add_son(create_node("ParseArgs", NULL), $1);}
    | PRINT LPAR STRLIT RPAR SEMICOLON              {$$=add_son(create_node("Print", NULL), create_node("StrLit", $3));}
    | PRINT LPAR Expr RPAR SEMICOLON                {$$=add_son(create_node("Print",NULL), $3);}
    | error SEMICOLON                               {$$=NULL;}
    ;

MultipleStatements: Statement MultipleStatements    {$$=add_bro($1,$2);}
    | Statement                                     {$$=$1;}
    ;

MethodInvocation: ID LPAR RPAR                      {$$=create_node("Id", $1);}
    | ID LPAR Expr RPAR                             {$$=add_bro(create_node("Id", $1), $3);}
    | ID LPAR Expr CommaExpr RPAR                   {$$=add_bro(create_node("Id", $1), add_bro($3, $4));}
    | ID LPAR error RPAR                            {$$=NULL;}
    ;

CommaExpr: COMMA Expr                               {$$=$2;}
    | COMMA Expr CommaExpr                          {$$=add_bro($2, $3);}
    ;

Assignment: ID ASSIGN Expr                          {$$=add_bro(create_node("Id", $1),$3);}

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR       {$$=add_bro(create_node("Id", $3),$5);}
    | PARSEINT LPAR error RPAR                      {$$=NULL;}
    ;

Expr: Expr PLUS Expr                                {$$=add_son(create_node("Add", NULL), add_bro($1, $3));} 
    | Expr MINUS Expr                               {$$=add_son(create_node("Sub", NULL), add_bro($1, $3));} 
    | Expr STAR Expr                                {$$=add_son(create_node("Mul", NULL), add_bro($1, $3));} 
    | Expr DIV Expr                                 {$$=add_son(create_node("Div", NULL), add_bro($1, $3));} 
    | Expr MOD Expr                                 {$$=add_son(create_node("Mod", NULL), add_bro($1, $3));} 
    | Expr AND Expr                                 {$$=add_son(create_node("And", NULL), add_bro($1, $3));} 
    | Expr OR Expr                                  {$$=add_son(create_node("Or", NULL), add_bro($1, $3));} 
    | Expr XOR Expr                                 {$$=add_son(create_node("Xor", NULL), add_bro($1, $3));} 
    | Expr LSHIFT Expr                              {$$=add_son(create_node("Lshift", NULL), add_bro($1, $3));} 
    | Expr RSHIFT Expr                              {$$=add_son(create_node("Rshift", NULL), add_bro($1, $3));} 
    | Expr EQ Expr                                  {$$=add_son(create_node("Eq", NULL), add_bro($1, $3));} 
    | Expr GE Expr                                  {$$=add_son(create_node("Ge", NULL), add_bro($1, $3));} 
    | Expr GT Expr                                  {$$=add_son(create_node("Gt", NULL), add_bro($1, $3));} 
    | Expr LE Expr                                  {$$=add_son(create_node("Le", NULL), add_bro($1, $3));} 
    | Expr LT Expr                                  {$$=add_son(create_node("Lt", NULL), add_bro($1, $3));} 
    | Expr NE Expr                                  {$$=add_son(create_node("Ne", NULL), add_bro($1, $3));} 
    | MINUS Expr                       %prec UNARY  {$$=add_son(create_node("Minus", NULL), $2);} 
    | NOT Expr                                      {$$=add_son(create_node("Not", NULL), $2);} 
    | PLUS Expr                        %prec UNARY  {$$=add_son(create_node("Add", NULL), $2);} 
    | LPAR Expr RPAR                                {$$=$2;}
    | MethodInvocation                              {$$=add_son(create_node("Call", NULL), $1);} 
    | Assignment                                    {$$=add_son(create_node("Assign", NULL), $1);} 
    | ParseArgs                                     {$$=add_son(create_node("ParseArgs", NULL), $1);} 
    | ID DOTLENGTH                                  {$$=add_son(create_node("Length", NULL), create_node("Id", $1));}
    | ID                                            {$$=create_node("Id", $1);} 
    | INTLIT                                        {$$=create_node("DecLit", $1);}
    | REALLIT                                       {$$=create_node("RealLit", $1);}
    | BOOLLIT                                       {$$=create_node("BoolLit", $1);}
    | LPAR error RPAR                               {$$=NULL;}
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

void yyerror (char * s) {
printf ("Line %d, col %d: %s: %s\n", line_yacc, col_yacc, s, yytext);
}

/*int main(int argc, char* argv[]) {
    if(argc > 1){
        if(strcmp(argv[1], "-t") == 0) flag = 1;
        else if(strcmp(argv[1], "-e2") == 0) flag = 0;
    }
    yyparse();
    return 0;
}*/
