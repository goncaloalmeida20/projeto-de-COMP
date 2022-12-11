%{
    /*
        Autores:
            Gonçalo Fernandes Diogo de Almeida, nº2020218868
            João Bernardo de Jesus Santos, nº2020218995
    */
    
    #include <stdio.h>
    #include <string.h>
    #include "tree.h"

    #define MAX_TK 6

    extern int yylex(void);
    extern void yyerror(char*);
    extern char* yytext;

    void free_tk(Tk *tk1, Tk *tk2, Tk *tk3, Tk *tk4, Tk *tk5, Tk *tk6);

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

Program: CLASS ID LBRACE RBRACE                     {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, create_node("Id",$2->value, $2->line, $2->col, NULL)); free_tk($1, $2, $3, $4, NULL, NULL);}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE        {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), $4)); free_tk($1, $2, $3, $5, NULL, NULL);}   
    | CLASS ID LBRACE RBRACE error                  {yacc_error = 1;}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE error  {yacc_error = 1;}   
    ;

MethodFieldDecl: MethodDecl                         {$$=$1;}
    | FieldDecl                                     {$$=$1;}
    | SEMICOLON                                     {$$=NULL; free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | MethodDecl MethodFieldDecl                    {$$=add_bro($1,$2);}
    | FieldDecl MethodFieldDecl                     {$$=add_bro($1,$2);}
    | SEMICOLON MethodFieldDecl                     {$$=$2; free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody   {$$=add_son(create_node("MethodDecl", NULL, 0, 0, NULL), add_bro($3, $4)); free_tk($1, $2, NULL, NULL, NULL, NULL);}

FieldDecl: PUBLIC STATIC Type ID SEMICOLON          {$$=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro($3, create_node("Id", $4->value, $4->line, $4->col, NULL)));free_tk($1, $2, $4, $5, NULL, NULL);} 
    | PUBLIC STATIC Type ID FieldCommaId SEMICOLON  {$$=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro($3, create_node("Id", $4->value, $4->line, $4->col, NULL))), $5);free_tk($1, $2, NULL, $4, NULL, $6);}   
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

FieldCommaId: COMMA ID                              {$$=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL)));free_tk($1, $2, NULL, NULL, NULL, NULL);}   
    | COMMA ID FieldCommaId                         {$$=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);free_tk($1, $2, NULL, NULL, NULL, NULL);}   
    ;

Type: BOOL                                          {$$=create_node("Bool", NULL, $1->line, $1->col, "boolean"); strcpy(current_type, "Bool"); strcpy(current_true_type, "boolean");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | INT                                           {$$=create_node("Int", NULL, $1->line, $1->col, "int"); strcpy(current_type, "Int"); strcpy(current_true_type, "int");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | DOUBLE                                        {$$=create_node("Double", NULL, $1->line, $1->col, "double"); strcpy(current_type, "Double"); strcpy(current_true_type, "double");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    ;

MethodHeader: Type ID LPAR RPAR                     {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro($1, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));free_tk(NULL, $2, $3, $4, NULL, NULL);}
    | Type ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro($1, add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),$4))));free_tk(NULL, $2, $3, $5, NULL, NULL);}
    | VOID ID LPAR RPAR                             {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, $2->line, $2->col, "void"), add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));free_tk($1, $2, $3, $4, NULL, NULL);}
    | VOID ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, $2->line, $2->col, "void"), add_bro(create_node("Id",$2->value, $2->line, $2->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),$4))));free_tk($1, $2, $3, $5, NULL, NULL);}
    ;

FormalParams: Type ID                               {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL)));free_tk(NULL, $2, NULL, NULL, NULL, NULL);}
    | Type ID CommaTypeIds                          {$$=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL))),$3);free_tk(NULL, $2, NULL, NULL, NULL, NULL);}
    | STRING LSQ RSQ ID                             {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro(create_node("StringArray", NULL, $1->line, $1->col, "String[]"), create_node("Id", $4->value, $4->line, $4->col, NULL)));free_tk($1, $2, $3, $4, NULL, NULL);}
    ;

CommaTypeIds: COMMA Type ID                         {$$=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($2, create_node("Id", $3->value, $3->line, $3->col, NULL)));free_tk($1, $3, NULL, NULL, NULL, NULL);}
    | COMMA Type ID CommaTypeIds                    {$$=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro($2, create_node("Id", $3->value, $3->line, $3->col, NULL))),$4);free_tk($1, $3, NULL, NULL, NULL, NULL);}
    ;

MethodBody: LBRACE RBRACE                           {$$=create_node("MethodBody", NULL, 0, 0, NULL);free_tk($1, $2, NULL, NULL, NULL, NULL);}
    | LBRACE StatementVarDecl RBRACE                {$$=add_son(create_node("MethodBody", NULL, 0, 0, NULL), $2);free_tk($1, $3, NULL, NULL, NULL, NULL);}
    ;

StatementVarDecl: Statement                         {$$=$1;}    
    | VarDecl                                       {$$=$1;}
    | Statement StatementVarDecl                    {$$=add_bro($1,$2);}
    | VarDecl StatementVarDecl                      {$$=add_bro($1,$2);}
    ;

VarDecl: Type ID SEMICOLON                          {$$=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL)));free_tk($2, $3, NULL, NULL, NULL, NULL);}
    | Type ID VarCommaId SEMICOLON                  {$$=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro($1, create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);free_tk($2, $4, NULL, NULL, NULL, NULL);}
    ;

VarCommaId: COMMA ID                                {$$=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL)));free_tk($1, $2, NULL, NULL, NULL, NULL);}   
    | COMMA ID VarCommaId                           {$$=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, $2->line, $2->col, current_true_type), create_node("Id", $2->value, $2->line, $2->col, NULL))), $3);free_tk($1, $2, NULL, NULL, NULL, NULL);}   
    ;


Statement: LBRACE RBRACE                            {$$=NULL;free_tk($1, $2, NULL, NULL, NULL, NULL);}
    | LBRACE Statement RBRACE                       {$$=$2;free_tk($1, $3, NULL, NULL, NULL, NULL);}
    | LBRACE Statement MultipleStatements RBRACE    {$$=create_blocks($2,$3);free_tk($1, $4, NULL, NULL, NULL, NULL);}
    | IF LPAR Expr RPAR Statement                   {$$=add_if($3, $5, NULL, $1->line, $1->col);free_tk($1, $2, $4, NULL, NULL, NULL);}
    | IF LPAR Expr RPAR Statement ELSE Statement    {$$=add_if($3, $5, $7, $1->line, $1->col);free_tk($1, $2, $4, $6, NULL, NULL);}
    | WHILE LPAR Expr RPAR Statement                {$$=add_while($3, $5, $1->line, $1->col);free_tk($1, $2, $4, NULL, NULL, NULL);}
    | RETURN SEMICOLON                              {$$=create_node("Return", NULL, $1->line, $1->col, "return");free_tk($1, $2, NULL, NULL, NULL, NULL);}
    | RETURN Expr SEMICOLON                         {$$=add_son(create_node("Return", NULL, $1->line, $1->col, "return"), $2);free_tk($1, $3, NULL, NULL, NULL, NULL);}
    | SEMICOLON                                     {$$=NULL;free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | MethodInvocation SEMICOLON                    {$$=add_son(create_node("Call", NULL, $1->line, $1->col, NULL), $1);free_tk(NULL, $2, NULL, NULL, NULL, NULL);}
    | Assignment SEMICOLON                          {$$=$1;free_tk(NULL, $2, NULL, NULL, NULL, NULL);}
    | ParseArgs SEMICOLON                           {$$=$1;free_tk(NULL, $2, NULL, NULL, NULL, NULL);}
    | PRINT LPAR STRLIT RPAR SEMICOLON              {$$=add_son(create_node("Print", NULL, $1->line, $1->col, "System.out.print"), create_node("StrLit", $3->value, $3->line, $3->col, "String"));free_tk($1, $2, $3, $4, $5, NULL);}
    | PRINT LPAR Expr RPAR SEMICOLON                {$$=add_son(create_node("Print",NULL, $1->line, $1->col, "System.out.print"), $3);free_tk($1, $2, NULL, $4, $5, NULL);}
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

MultipleStatements: Statement MultipleStatements    {$$=add_bro($1,$2);}
    | Statement                                     {$$=$1;}
    ;

MethodInvocation: ID LPAR RPAR                      {$$=create_node("Id", $1->value, $1->line, $1->col, NULL);free_tk($1, $2, $3, NULL, NULL, NULL);}
    | ID LPAR Expr RPAR                             {$$=add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL), $3);free_tk($1, $2, $4, NULL, NULL, NULL);}
    | ID LPAR Expr CommaExpr RPAR                   {$$=add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL), add_bro($3, $4));free_tk($1, $2, $5, NULL, NULL, NULL);}
    | ID LPAR error RPAR                            {yacc_error = 1; $$=NULL;}
    ;

CommaExpr: COMMA Expr                               {$$=$2;free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | COMMA Expr CommaExpr                          {$$=add_bro($2, $3);free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    ;

Assignment: ID ASSIGN Expr                          {$$=add_son(create_node("Assign", NULL, $2->line, $2->col, "="), add_bro(create_node("Id", $1->value, $1->line, $1->col, NULL),$3));free_tk($1, $2, NULL, NULL, NULL, NULL);}

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR       {$$=add_son(create_node("ParseArgs", NULL, $1->line, $1->col, "Integer.parseInt"), add_bro(create_node("Id", $3->value, $3->line, $3->col, NULL),$5)); free_tk($1, $2, $3, $4, $6, $7);}
    | PARSEINT LPAR error RPAR                      {yacc_error = 1; $$=NULL;}
    ;

Expr: ExprNoAssign                                  {$$=$1;}
    | Assignment                                    {$$=$1;} 
    ;

ExprNoAssign: ExprNoAssign PLUS ExprNoAssign                        {$$=add_son(create_node("Add", NULL, $2->line, $2->col, "+"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign MINUS ExprNoAssign                               {$$=add_son(create_node("Sub", NULL, $2->line, $2->col, "-"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign STAR ExprNoAssign                                {$$=add_son(create_node("Mul", NULL, $2->line, $2->col, "*"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign DIV ExprNoAssign                                 {$$=add_son(create_node("Div", NULL, $2->line, $2->col, "/"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign MOD ExprNoAssign                                 {$$=add_son(create_node("Mod", NULL, $2->line, $2->col, "%"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign AND ExprNoAssign                                 {$$=add_son(create_node("And", NULL, $2->line, $2->col, "&&"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign OR ExprNoAssign                                  {$$=add_son(create_node("Or", NULL, $2->line, $2->col, "||"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign XOR ExprNoAssign                                 {$$=add_son(create_node("Xor", NULL, $2->line, $2->col, "^"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign LSHIFT ExprNoAssign                              {$$=add_son(create_node("Lshift", NULL, $2->line, $2->col, "<<"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign RSHIFT ExprNoAssign                              {$$=add_son(create_node("Rshift", NULL, $2->line, $2->col, ">>"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign EQ ExprNoAssign                                  {$$=add_son(create_node("Eq", NULL, $2->line, $2->col, "=="), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign GE ExprNoAssign                                  {$$=add_son(create_node("Ge", NULL, $2->line, $2->col, ">="), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign GT ExprNoAssign                                  {$$=add_son(create_node("Gt", NULL, $2->line, $2->col, ">"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign LE ExprNoAssign                                  {$$=add_son(create_node("Le", NULL, $2->line, $2->col, "<="), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign LT ExprNoAssign                                  {$$=add_son(create_node("Lt", NULL, $2->line, $2->col, "<"), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | ExprNoAssign NE ExprNoAssign                                  {$$=add_son(create_node("Ne", NULL, $2->line, $2->col, "!="), add_bro($1, $3));free_tk(NULL, $2, NULL, NULL, NULL, NULL);} 
    | MINUS ExprNoAssign                       %prec UNARY  {$$=add_son(create_node("Minus", NULL, $1->line, $1->col, "-"), $2);free_tk(NULL, $1, NULL, NULL, NULL, NULL);} 
    | NOT ExprNoAssign                                      {$$=add_son(create_node("Not", NULL, $1->line, $1->col, "!"), $2);free_tk(NULL, $1, NULL, NULL, NULL, NULL);} 
    | PLUS ExprNoAssign                        %prec UNARY  {$$=add_son(create_node("Plus", NULL, $1->line, $1->col, "+"), $2);free_tk(NULL, $1, NULL, NULL, NULL, NULL);} 
    | LPAR Expr RPAR                                {$$=$2;free_tk($1, $3, NULL, NULL, NULL, NULL);}
    | MethodInvocation                              {$$=add_son(create_node("Call", NULL, $1->line, $1->col, NULL), $1);} 
    | ParseArgs                                     {$$=$1;} 
    | ID DOTLENGTH                                  {$$=add_son(create_node("Length", NULL, $2->line, $2->col, ".length"), create_node("Id", $1->value, $1->line, $1->col, NULL));free_tk($1, $2, NULL, NULL, NULL, NULL);}
    | ID                                            {$$=create_node("Id", $1->value, $1->line, $1->col, NULL);free_tk($1, NULL, NULL, NULL, NULL, NULL);} 
    | INTLIT                                        {$$=create_node("DecLit", $1->value, $1->line, $1->col, "int");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | REALLIT                                       {$$=create_node("RealLit", $1->value, $1->line, $1->col, "double");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | BOOLLIT                                       {$$=create_node("BoolLit", $1->value, $1->line, $1->col, "boolean");free_tk($1, NULL, NULL, NULL, NULL, NULL);}
    | LPAR error RPAR                               {yacc_error = 1; $$=NULL;}
    ;

%%

void free_tk(Tk *tk1, Tk *tk2, Tk *tk3, Tk *tk4, Tk *tk5, Tk *tk6){
    Tk *tks[MAX_TK] = {tk1, tk2, tk3, tk4, tk5, tk6};
    for(int i = 0; i < MAX_TK; i++){
        if(tks[i]){
            if(tks[i]->value) free(tks[i]->value);
            free(tks[i]);
        }
    }
}

void yyerror (char * s) {
    printf ("Line %d, col %d: %s: %s\n", line_yacc, col_yacc, s, yytext);
}