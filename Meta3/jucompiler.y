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

    int line_yacc = 1, col_yacc = 1;
    int flag_yacc = 0;

%}
%union{char* str; Node* node;}
%token BOOL INT DOUBLE AND ASSIGN STAR COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ SEMICOLON ARROW LSHIFT RSHIFT XOR CLASS DOTLENGTH ELSE IF PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID WHILE
%token <str> RESERVED STRLIT BOOLLIT INTLIT REALLIT ID

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

Program: CLASS ID LBRACE RBRACE                     {root = create_node("Program", NULL, line_yacc, col_yacc); add_son(root, create_node("Id",$2, line_yacc, col_yacc));}                   
    | CLASS ID LBRACE MethodFieldDecl RBRACE        {root = create_node("Program", NULL, line_yacc, col_yacc); add_son(root, add_bro(create_node("Id",$2, line_yacc, col_yacc), $4));}   
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

MethodDecl: PUBLIC STATIC MethodHeader MethodBody   {$$=add_son(create_node("MethodDecl", NULL, line_yacc, col_yacc), add_bro($3, $4));}

FieldDecl: PUBLIC STATIC Type ID SEMICOLON          {$$=add_son(create_node("FieldDecl",NULL, line_yacc, col_yacc), add_bro($3, create_node("Id", $4, line_yacc, col_yacc)));} 
    | PUBLIC STATIC Type ID FieldCommaId SEMICOLON  {$$=add_bro(add_son(create_node("FieldDecl",NULL, line_yacc, col_yacc), add_bro($3, create_node("Id", $4, line_yacc, col_yacc))), $5);}   
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

FieldCommaId: COMMA ID                              {$$=add_son(create_node("FieldDecl",NULL, line_yacc, col_yacc), add_bro(create_node(current_type, NULL, line_yacc, col_yacc), create_node("Id", $2, line_yacc, col_yacc)));}   
    | COMMA ID FieldCommaId                         {$$=add_bro(add_son(create_node("FieldDecl",NULL, line_yacc, col_yacc), add_bro(create_node(current_type, NULL, line_yacc, col_yacc), create_node("Id", $2, line_yacc, col_yacc))), $3);}   
    ;

Type: BOOL                                          {$$=create_node("Bool", NULL, line_yacc, col_yacc); strcpy(current_type, "Bool"); }
    | INT                                           {$$=create_node("Int", NULL, line_yacc, col_yacc); strcpy(current_type, "Int");}
    | DOUBLE                                        {$$=create_node("Double", NULL, line_yacc, col_yacc); strcpy(current_type, "Double"); }
    ;

MethodHeader: Type ID LPAR RPAR                     {$$=add_son(create_node("MethodHeader", NULL, line_yacc, col_yacc), add_bro($1, add_bro(create_node("Id",$2, line_yacc, col_yacc), create_node("MethodParams", NULL, line_yacc, col_yacc))));}
    | Type ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, line_yacc, col_yacc), add_bro($1, add_bro(create_node("Id",$2, line_yacc, col_yacc), add_son(create_node("MethodParams", NULL, line_yacc, col_yacc),$4))));}
    | VOID ID LPAR RPAR                             {$$=add_son(create_node("MethodHeader", NULL, line_yacc, col_yacc), add_bro(create_node("Void", NULL, line_yacc, col_yacc), add_bro(create_node("Id",$2, line_yacc, col_yacc), create_node("MethodParams", NULL, line_yacc, col_yacc))));}
    | VOID ID LPAR FormalParams RPAR                {$$=add_son(create_node("MethodHeader", NULL, line_yacc, col_yacc), add_bro(create_node("Void", NULL, line_yacc, col_yacc), add_bro(create_node("Id",$2, line_yacc, col_yacc), add_son(create_node("MethodParams", NULL, line_yacc, col_yacc),$4))));}
    ;

FormalParams: Type ID                               {$$=add_son(create_node("ParamDecl", NULL, line_yacc, col_yacc), add_bro($1, create_node("Id", $2, line_yacc, col_yacc)));}
    | Type ID CommaTypeIds                          {$$=add_bro(add_son(create_node("ParamDecl", NULL, line_yacc, col_yacc), add_bro($1, create_node("Id", $2, line_yacc, col_yacc))),$3);}
    | STRING LSQ RSQ ID                             {$$=add_son(create_node("ParamDecl", NULL, line_yacc, col_yacc), add_bro(create_node("StringArray", NULL, line_yacc, col_yacc), create_node("Id", $4, line_yacc, col_yacc)));}
    ;

CommaTypeIds: COMMA Type ID                         {$$=add_son(create_node("ParamDecl", NULL, line_yacc, col_yacc), add_bro($2, create_node("Id", $3, line_yacc, col_yacc)));}
    | COMMA Type ID CommaTypeIds                    {$$=add_bro(add_son(create_node("ParamDecl", NULL, line_yacc, col_yacc), add_bro($2, create_node("Id", $3, line_yacc, col_yacc))),$4);}
    ;

MethodBody: LBRACE RBRACE                           {$$=create_node("MethodBody", NULL, line_yacc, col_yacc);}
    | LBRACE StatementVarDecl RBRACE                {$$=add_son(create_node("MethodBody", NULL, line_yacc, col_yacc), $2);}
    ;

StatementVarDecl: Statement                         {$$=$1;}    
    | VarDecl                                       {$$=$1;}
    | Statement StatementVarDecl                    {$$=add_bro($1,$2);}
    | VarDecl StatementVarDecl                      {$$=add_bro($1,$2);}
    ;

VarDecl: Type ID SEMICOLON                          {$$=add_son(create_node("VarDecl",NULL, line_yacc, col_yacc), add_bro($1, create_node("Id", $2, line_yacc, col_yacc)));}
    | Type ID VarCommaId SEMICOLON                  {$$=add_bro(add_son(create_node("VarDecl",NULL, line_yacc, col_yacc), add_bro($1, create_node("Id", $2, line_yacc, col_yacc))), $3);}
    ;

VarCommaId: COMMA ID                                {$$=add_son(create_node("VarDecl",NULL, line_yacc, col_yacc), add_bro(create_node(current_type, NULL, line_yacc, col_yacc), create_node("Id", $2, line_yacc, col_yacc)));}   
    | COMMA ID VarCommaId                           {$$=add_bro(add_son(create_node("VarDecl",NULL, line_yacc, col_yacc), add_bro(create_node(current_type, NULL, line_yacc, col_yacc), create_node("Id", $2, line_yacc, col_yacc))), $3);}   
    ;


Statement: LBRACE RBRACE                            {$$=NULL;}
    | LBRACE Statement RBRACE                       {$$=$2;}
    | LBRACE Statement MultipleStatements RBRACE    {$$=create_blocks($2,$3, line_yacc, col_yacc);}
    | IF LPAR Expr RPAR Statement                   {$$=add_if($3, $5, NULL, line_yacc, col_yacc);}
    | IF LPAR Expr RPAR Statement ELSE Statement    {$$=add_if($3, $5, $7, line_yacc, col_yacc);}
    | WHILE LPAR Expr RPAR Statement                {$$=add_while($3, $5, line_yacc, col_yacc);}
    | RETURN SEMICOLON                              {$$=create_node("Return", NULL, line_yacc, col_yacc);}
    | RETURN Expr SEMICOLON                         {$$=add_son(create_node("Return", NULL, line_yacc, col_yacc), $2);}
    | SEMICOLON                                     {$$=NULL;}
    | MethodInvocation SEMICOLON                    {$$=add_son(create_node("Call", NULL, line_yacc, col_yacc), $1);}
    | Assignment SEMICOLON                          {$$=add_son(create_node("Assign", NULL, line_yacc, col_yacc), $1);}
    | ParseArgs SEMICOLON                           {$$=add_son(create_node("ParseArgs", NULL, line_yacc, col_yacc), $1);}
    | PRINT LPAR STRLIT RPAR SEMICOLON              {$$=add_son(create_node("Print", NULL, line_yacc, col_yacc), create_node("StrLit", $3, line_yacc, col_yacc));}
    | PRINT LPAR Expr RPAR SEMICOLON                {$$=add_son(create_node("Print",NULL, line_yacc, col_yacc), $3);}
    | error SEMICOLON                               {yacc_error = 1; $$=NULL;}
    ;

MultipleStatements: Statement MultipleStatements    {$$=add_bro($1,$2);}
    | Statement                                     {$$=$1;}
    ;

MethodInvocation: ID LPAR RPAR                      {$$=create_node("Id", $1, line_yacc, col_yacc);}
    | ID LPAR Expr RPAR                             {$$=add_bro(create_node("Id", $1, line_yacc, col_yacc), $3);}
    | ID LPAR Expr CommaExpr RPAR                   {$$=add_bro(create_node("Id", $1, line_yacc, col_yacc), add_bro($3, $4));}
    | ID LPAR error RPAR                            {yacc_error = 1; $$=NULL;}
    ;

CommaExpr: COMMA Expr                               {$$=$2;}
    | COMMA Expr CommaExpr                          {$$=add_bro($2, $3);}
    ;

Assignment: ID ASSIGN Expr                          {$$=add_bro(create_node("Id", $1, line_yacc, col_yacc),$3);}

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR       {$$=add_bro(create_node("Id", $3, line_yacc, col_yacc),$5);}
    | PARSEINT LPAR error RPAR                      {yacc_error = 1; $$=NULL;}
    ;

Expr: Expr PLUS ExprNoAssign                                {$$=add_son(create_node("Add", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr MINUS ExprNoAssign                               {$$=add_son(create_node("Sub", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr STAR ExprNoAssign                                {$$=add_son(create_node("Mul", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr DIV ExprNoAssign                                 {$$=add_son(create_node("Div", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr MOD ExprNoAssign                                 {$$=add_son(create_node("Mod", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr AND ExprNoAssign                                 {$$=add_son(create_node("And", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr OR ExprNoAssign                                  {$$=add_son(create_node("Or", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr XOR ExprNoAssign                                 {$$=add_son(create_node("Xor", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr LSHIFT ExprNoAssign                              {$$=add_son(create_node("Lshift", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr RSHIFT ExprNoAssign                              {$$=add_son(create_node("Rshift", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr EQ ExprNoAssign                                  {$$=add_son(create_node("Eq", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr GE ExprNoAssign                                  {$$=add_son(create_node("Ge", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr GT ExprNoAssign                                  {$$=add_son(create_node("Gt", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr LE ExprNoAssign                                  {$$=add_son(create_node("Le", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr LT ExprNoAssign                                  {$$=add_son(create_node("Lt", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | Expr NE ExprNoAssign                                  {$$=add_son(create_node("Ne", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | MINUS ExprNoAssign                       %prec UNARY  {$$=add_son(create_node("Minus", NULL, line_yacc, col_yacc), $2);} 
    | NOT ExprNoAssign                                      {$$=add_son(create_node("Not", NULL, line_yacc, col_yacc), $2);} 
    | PLUS ExprNoAssign                        %prec UNARY  {$$=add_son(create_node("Plus", NULL, line_yacc, col_yacc), $2);} 
    | LPAR Expr RPAR                                {$$=$2;}
    | MethodInvocation                              {$$=add_son(create_node("Call", NULL, line_yacc, col_yacc), $1);} 
    | Assignment                                    {$$=add_son(create_node("Assign", NULL, line_yacc, col_yacc), $1);} 
    | ParseArgs                                     {$$=add_son(create_node("ParseArgs", NULL, line_yacc, col_yacc), $1);} 
    | ID DOTLENGTH                                  {$$=add_son(create_node("Length", NULL, line_yacc, col_yacc), create_node("Id", $1, line_yacc, col_yacc));}
    | ID                                            {$$=create_node("Id", $1, line_yacc, col_yacc);} 
    | INTLIT                                        {$$=create_node("DecLit", $1, line_yacc, col_yacc);}
    | REALLIT                                       {$$=create_node("RealLit", $1, line_yacc, col_yacc);}
    | BOOLLIT                                       {$$=create_node("BoolLit", $1, line_yacc, col_yacc);}
    | LPAR error RPAR                               {yacc_error = 1; $$=NULL;}
    ;

ExprNoAssign: ExprNoAssign PLUS ExprNoAssign                        {$$=add_son(create_node("Add", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign MINUS ExprNoAssign                               {$$=add_son(create_node("Sub", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign STAR ExprNoAssign                                {$$=add_son(create_node("Mul", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign DIV ExprNoAssign                                 {$$=add_son(create_node("Div", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign MOD ExprNoAssign                                 {$$=add_son(create_node("Mod", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign AND ExprNoAssign                                 {$$=add_son(create_node("And", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign XOR ExprNoAssign                                 {$$=add_son(create_node("Xor", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign LSHIFT ExprNoAssign                              {$$=add_son(create_node("Lshift", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign RSHIFT ExprNoAssign                              {$$=add_son(create_node("Rshift", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign EQ ExprNoAssign                                  {$$=add_son(create_node("Eq", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign GE ExprNoAssign                                  {$$=add_son(create_node("Ge", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign GT ExprNoAssign                                  {$$=add_son(create_node("Gt", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign LE ExprNoAssign                                  {$$=add_son(create_node("Le", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign LT ExprNoAssign                                  {$$=add_son(create_node("Lt", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | ExprNoAssign NE ExprNoAssign                                  {$$=add_son(create_node("Ne", NULL, line_yacc, col_yacc), add_bro($1, $3));} 
    | MINUS ExprNoAssign                       %prec UNARY  {$$=add_son(create_node("Minus", NULL, line_yacc, col_yacc), $2);} 
    | NOT ExprNoAssign                                      {$$=add_son(create_node("Not", NULL, line_yacc, col_yacc), $2);} 
    | PLUS ExprNoAssign                        %prec UNARY  {$$=add_son(create_node("Plus", NULL, line_yacc, col_yacc), $2);} 
    | LPAR Expr RPAR                                {$$=$2;}
    | MethodInvocation                              {$$=add_son(create_node("Call", NULL, line_yacc, col_yacc), $1);} 
    | ParseArgs                                     {$$=add_son(create_node("ParseArgs", NULL, line_yacc, col_yacc), $1);} 
    | ID DOTLENGTH                                  {$$=add_son(create_node("Length", NULL, line_yacc, col_yacc), create_node("Id", $1, line_yacc, col_yacc));}
    | ID                                            {$$=create_node("Id", $1, line_yacc, col_yacc);} 
    | INTLIT                                        {$$=create_node("DecLit", $1, line_yacc, col_yacc);}
    | REALLIT                                       {$$=create_node("RealLit", $1, line_yacc, col_yacc);}
    | BOOLLIT                                       {$$=create_node("BoolLit", $1, line_yacc, col_yacc);}
    | LPAR error RPAR                               {yacc_error = 1; $$=NULL;}
    ;

%%

void yyerror (char * s) {
    printf ("Line %d, col %d: %s: %s\n", line_yacc, col_yacc, s, yytext);
}
