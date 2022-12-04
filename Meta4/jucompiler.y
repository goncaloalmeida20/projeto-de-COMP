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

    int yacc_error = 0;
    
    char current_type[TYPE_SIZE];
    char current_true_type[TYPE_SIZE];

    int line_yacc = 1, col_yacc = 1;
    int flag_yacc = 0;

%}
%union{Node* node; Tk* tk;}
// %destructor <tk> {if($$->value) free($$->value);}
// %destructor <node> {free_tree($$);}
%token <tk> INT DOUBLE COMMA LBRACE LPAR LSQ RBRACE RPAR RSQ SEMICOLON ARROW CLASS DOTLENGTH ELSE IF PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID STAR DIV MINUS MOD PLUS LSHIFT RSHIFT ASSIGN NOT AND OR XOR EQ GE GT LE LT NE BOOL WHILE RESERVED STRLIT BOOLLIT INTLIT REALLIT ID
%right ASSIGN
%right LPAR
%left RPAR
%right IF ELSE
%left OR
%left AND
%left XOR
%left EQ NE
%left GE GT LE LT
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV MOD
%right NOT UNARY
%type <node> MethodFieldDecl MethodDecl FieldDecl FieldCommaId Type MethodHeader MethodBody FormalParams StatementVarDecl CommaTypeIds VarDecl VarCommaId Statement MultipleStatements MethodInvocation CommaExpr Assignment ParseArgs Expr ExprNoAssign
%%

Program: CLASS ID LBRACE RBRACE                     {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, create_node("Id",$2->value, $2->line, $2->col, NULL));}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE        {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), $4));}   
    | CLASS ID LBRACE RBRACE error                  {yacc_error = 1;}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE error  {yacc_error = 1;}   
    ;

MethodFieldDecl: MethodDecl                         {$$=$1;}
    | FieldDecl                                     {$$=$1;}
    | SEMICOLON                                     {$$=NULL;}
    | MethodDecl MethodFieldDecl                    {$$=add_bro($1,$2);}
    | FieldDecl MethodFieldDecl                     {$$=add_bro($1,$2);}
    | SEMICOLON MethodFieldDecl                     {$$=$2;}
    ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody   {$$=add_son(create_node("MethodDecl", NULL, 0, 0, NULL), add_bro($3, $4));}

FieldDecl: PUBLIC STATIC Type ID SEMICOLON          {$$=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro($3, create_node("Id", $4->value, $4->line, $4->col, NULL)));} 
    | PUBLIC STATIC Type ID FieldCommaId SEMICOLON  {$$=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro($3, create_node("Id", $4->value, $4->line, $4->col, NULL))), $5);}   
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

FieldCommaId: COMMA ID                              {$$=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL)));}   
    | COMMA ID FieldCommaId                         {$$=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);}   
    ;

Type: BOOL                                          {$$=create_node("Bool", NULL, $1->line, $1->col, "boolean"); strcpy(current_type, "Bool"); strcpy(current_true_type, "boolean");}
    | INT                                           {$$=create_node("Int", NULL, $1->line, $1->col, "int"); strcpy(current_type, "Int"); strcpy(current_true_type, "int");}
    | DOUBLE                                        {$$=create_node("Double", NULL, $1->line, $1->col, "double"); strcpy(current_type, "Double"); strcpy(current_true_type, "double");}
    ;

MethodHeader: Type ID LPAR RPAR                     {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro($1, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));}
    | Type ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro($1, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),$4))));}
    | VOID ID LPAR RPAR                             {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, $2->line, $2->col, "void"), add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));}
    | VOID ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, $2->line, $2->col, "void"), add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),$4))));}
    ;

FormalParams: Type ID                               {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL)));}
    | Type ID CommaTypeIds                          {$$=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL))),$3);}
    | STRING LSQ RSQ ID                             {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro(create_node("StringArray", NULL, $1->line, $1->col, "String[]"), create_node("Id", $4->value, $4->line, $4->col, NULL)));}
    ;

CommaTypeIds: COMMA Type ID                         {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($2, create_node("Id", $3->value, $3->line, $3->col, NULL)));}
    | COMMA Type ID CommaTypeIds                    {$$=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($2, create_node("Id", $3->value, $3->line, $3->col, NULL))),$4);}
    ;

MethodBody: LBRACE RBRACE                           {$$=create_node("MethodBody", NULL, 0, 0, NULL);}
    | LBRACE StatementVarDecl RBRACE                {$$=add_son(create_node("MethodBody", NULL, 0, 0, NULL), $2);}
    ;

StatementVarDecl: Statement                         {$$=$1;}    
    | VarDecl                                       {$$=$1;}
    | Statement StatementVarDecl                    {$$=add_bro($1,$2);}
    | VarDecl StatementVarDecl                      {$$=add_bro($1,$2);}
    ;

VarDecl: Type ID SEMICOLON                          {$$=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL)));}
    | Type ID VarCommaId SEMICOLON                  {$$=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);}
    ;

VarCommaId: COMMA ID                                {$$=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL)));}   
    | COMMA ID VarCommaId                           {$$=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);}   
    ;


Statement: LBRACE RBRACE                            {$$=NULL;}
    | LBRACE Statement RBRACE                       {$$=$2;}
    | LBRACE Statement MultipleStatements RBRACE    {$$=create_blocks($2,$3);}
    | IF LPAR Expr RPAR Statement                   {$$=add_if($3, $5, NULL, $1->line, $1->col);}
    | IF LPAR Expr RPAR Statement ELSE Statement    {$$=add_if($3, $5, $7, $1->line, $1->col);}
    | WHILE LPAR Expr RPAR Statement                {$$=add_while($3, $5, $1->line, $1->col);}
    | RETURN SEMICOLON                              {$$=create_node("Return", NULL, $1->line, $1->col, "return");}
    | RETURN Expr SEMICOLON                         {$$=add_son(create_node("Return", NULL, $1->line, $1->col, "return"), $2);}
    | SEMICOLON                                     {$$=NULL;}
    | MethodInvocation SEMICOLON                    {$$=add_son(create_node("Call", NULL, $1->line, $1->col, NULL), $1);}
    | Assignment SEMICOLON                          {$$=$1;}
    | ParseArgs SEMICOLON                           {$$=$1;}
    | PRINT LPAR STRLIT RPAR SEMICOLON              {$$=add_son(create_node("Print", NULL, $1->line, $1->col, "System.out.print"), create_node("StrLit", $3->value, $3->line, $3->col, "String"));}
    | PRINT LPAR Expr RPAR SEMICOLON                {$$=add_son(create_node("Print",NULL, $1->line, $1->col, "System.out.print"), $3);}
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

MultipleStatements: Statement MultipleStatements    {$$=add_bro($1,$2);}
    | Statement                                     {$$=$1;}
    ;

MethodInvocation: ID LPAR RPAR                      {$$=create_node("Id", $1->value, $1->line, $1->col, NULL);}
    | ID LPAR Expr RPAR                             {$$=add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL), $3);}
    | ID LPAR Expr CommaExpr RPAR                   {$$=add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL), add_bro($3, $4));}
    | ID LPAR error RPAR                            {yacc_error = 1; $$=NULL;}
    ;

CommaExpr: COMMA Expr                               {$$=$2;}
    | COMMA Expr CommaExpr                          {$$=add_bro($2, $3);}
    ;

Assignment: ID ASSIGN Expr                          {$$=add_son(create_node("Assign", NULL, $2->line, $2->col, "="), add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL),$3));}

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR       {$$=add_son(create_node("ParseArgs", NULL, $1->line, $1->col, "Integer.parseInt"), add_bro(create_node("Id", $3->value, $3->line, $3->col, NULL),$5));}
    | PARSEINT LPAR error RPAR                      {yacc_error = 1; $$=NULL;}
    ;

Expr: ExprNoAssign                                  {$$=$1;}
    | Assignment                                    {$$=$1;} 
    ;

ExprNoAssign: ExprNoAssign PLUS ExprNoAssign                        {$$=add_son(create_node("Add", NULL, $2->line, $2->col, "+"), add_bro($1, $3));} 
    | ExprNoAssign MINUS ExprNoAssign                               {$$=add_son(create_node("Sub", NULL, $2->line, $2->col, "-"), add_bro($1, $3));} 
    | ExprNoAssign STAR ExprNoAssign                                {$$=add_son(create_node("Mul", NULL, $2->line, $2->col, "*"), add_bro($1, $3));} 
    | ExprNoAssign DIV ExprNoAssign                                 {$$=add_son(create_node("Div", NULL, $2->line, $2->col, "/"), add_bro($1, $3));} 
    | ExprNoAssign MOD ExprNoAssign                                 {$$=add_son(create_node("Mod", NULL, $2->line, $2->col, "%"), add_bro($1, $3));} 
    | ExprNoAssign AND ExprNoAssign                                 {$$=add_son(create_node("And", NULL, $2->line, $2->col, "&&"), add_bro($1, $3));} 
    | ExprNoAssign OR ExprNoAssign                                  {$$=add_son(create_node("Or", NULL, $2->line, $2->col, "||"), add_bro($1, $3));} 
    | ExprNoAssign XOR ExprNoAssign                                 {$$=add_son(create_node("Xor", NULL, $2->line, $2->col, "^"), add_bro($1, $3));} 
    | ExprNoAssign LSHIFT ExprNoAssign                              {$$=add_son(create_node("Lshift", NULL, $2->line, $2->col, "<<"), add_bro($1, $3));} 
    | ExprNoAssign RSHIFT ExprNoAssign                              {$$=add_son(create_node("Rshift", NULL, $2->line, $2->col, ">>"), add_bro($1, $3));} 
    | ExprNoAssign EQ ExprNoAssign                                  {$$=add_son(create_node("Eq", NULL, $2->line, $2->col, "=="), add_bro($1, $3));} 
    | ExprNoAssign GE ExprNoAssign                                  {$$=add_son(create_node("Ge", NULL, $2->line, $2->col, ">="), add_bro($1, $3));} 
    | ExprNoAssign GT ExprNoAssign                                  {$$=add_son(create_node("Gt", NULL, $2->line, $2->col, ">"), add_bro($1, $3));} 
    | ExprNoAssign LE ExprNoAssign                                  {$$=add_son(create_node("Le", NULL, $2->line, $2->col, "<="), add_bro($1, $3));} 
    | ExprNoAssign LT ExprNoAssign                                  {$$=add_son(create_node("Lt", NULL, $2->line, $2->col, "<"), add_bro($1, $3));} 
    | ExprNoAssign NE ExprNoAssign                                  {$$=add_son(create_node("Ne", NULL, $2->line, $2->col, "!="), add_bro($1, $3));} 
    | MINUS ExprNoAssign                       %prec UNARY  {$$=add_son(create_node("Minus", NULL, $1->line, $1->col, "-"), $2);} 
    | NOT ExprNoAssign                                      {$$=add_son(create_node("Not", NULL, $1->line, $1->col, "!"), $2);} 
    | PLUS ExprNoAssign                        %prec UNARY  {$$=add_son(create_node("Plus", NULL, $1->line, $1->col, "+"), $2);} 
    | LPAR Expr RPAR                                {$$=$2;}
    | MethodInvocation                              {$$=add_son(create_node("Call", NULL, $1->line, $1->col, NULL), $1);} 
    | ParseArgs                                     {$$=$1;} 
    | ID DOTLENGTH                                  {$$=add_son(create_node("Length", NULL, $2->line, $2->col, ".length"), create_node("Id", $1->value, $1->line, $1->col, NULL));}
    | ID                                            {$$=create_node("Id", $1->value, $1->line, $1->col, NULL);} 
    | INTLIT                                        {$$=create_node("DecLit", $1->value, $1->line, $1->col, "int");}
    | REALLIT                                       {$$=create_node("RealLit", $1->value, $1->line, $1->col, "double");}
    | BOOLLIT                                       {$$=create_node("BoolLit", $1->value, $1->line, $1->col, "boolean");}
    | LPAR error RPAR                               {yacc_error = 1; $$=NULL;}
    ;

%%

void yyerror (char * s) {
    printf ("Line %d, col %d: %s: %s\n", line_yacc, col_yacc, s, yytext);
}