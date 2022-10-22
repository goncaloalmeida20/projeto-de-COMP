```
%{
    #include <stdio.h>

    int flag = 0; // 0: -e2 or no flag, 1: -t

    int yylex(void);
    void yyerror (const char *s);
%}
%token AND ASSIGN STAR COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ SEMICOLON ARROW LSHIFT RSHIFT XOR BOOL CLASS DOTLENGTH DOUBLE ELSE IF INT PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID WHILE
%token STRLIT BOOLLIT RESERVED INTLIT REALLIT ID
%nonassoc ASSIGN
%nonassoc EQ GE GT LE LT NE
%left OR
%left AND
%left XOR
%left LSHIFT RSHIFT
%left PLUS MINUS
%left STAR DIV
%left MOD

%%
Program: CLASS ID LBRACE RBRACE
    | CLASS ID LBRACE MethodFieldDecl RBRACE

MethodFieldDecl: MethodDecl
    | FieldDecl
    | SEMICOLON
    | MethodDecl MethodFieldDecl
    | FieldDecl MethodFieldDecl
    | SEMICOLON MethodFieldDecl
    
MethodDecl: PUBLIC STATIC MethodHeader MethodBody

FieldDecl: PUBLIC STATIC Type ID CommaId SEMICOLON
    | PUBLIC STATIC Type ID SEMICOLON

CommaId: COMMA ID CommaId 
    | COMMA ID

Type: BOOL | INT | DOUBLE

MethodHeader: Type ID LPAR RPAR
    | Type ID LPAR FormalParams RPAR
    | VOID ID LPAR RPAR
    | VOID ID LPAR FormalParams RPAR
    
FormalParams: Type ID
    | Type ID CommaTypeIds
    | STRING LSQ RSQ ID
    ;

CommaTypeIds: COMMA Type ID
    | COMMA Type ID CommaTypeIds

MethodBody: LBRACE RBRACE
    | LBRACE StatementVarDecl RBRACE

StatementVarDecl: Statement 
    | VarDecl
    | Statement StatementVarDecl
    | VarDecl StatementVarDecl
    
VarDecl: Type ID CommaId SEMICOLON
    | Type ID SEMICOLON

Statement: LBRACE RBRACE
    | LBRACE MultipleStatements RBRACE
    | IF LPAR Expr RPAR Statement
    | IF LPAR Expr RPAR Statement ELSE Statement
    | WHILE LPAR Expr RPAR Statement
    | RETURN SEMICOLON
    | RETURN Expr SEMICOLON
    | SEMICOLON
    | MethodInvocation SEMICOLON
    | Assignment SEMICOLON
    | ParseArgs SEMICOLON
    | PRINT LPAR STRLIT RPAR SEMICOLON
    | PRINT LPAR Expr RPAR SEMICOLON
    ;

MultipleStatements: Statement MultipleStatements
    | Statement

MethodInvocation: ID LPAR RPAR
    | ID LPAR Expr RPAR
    | ID LPAR Expr CommaExpr RPAR

CommaExpr: COMMA Expr
    | COMMA Expr CommaExpr

Assignment: ID ASSIGN Expr

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR

Expr: Expr PLUS Expr {}
    | Expr MINUS Expr {}
    | Expr STAR Expr {}
    | Expr DIV Expr {}
    | Expr MOD Expr {}
    | Expr AND Expr {}
    | Expr OR Expr {}
    | Expr XOR Expr {}
    | Expr LSHIFT Expr {}
    | Expr RSHIFT Expr {}
    | Expr EQ Expr {}
    | Expr GE Expr {}
    | Expr GT Expr {}
    | Expr LE Expr {}
    | Expr LT Expr {}
    | Expr NE Expr {}
    | MINUS Expr {}
    | NOT Expr {}
    | PLUS Expr {}
    | LPAR Expr RPAR {}
    | MethodInvocation {}
    | Assignment {}
    | ParseArgs {}
    | ID DOTLENGTH {}
    | ID {}
    | INTLIT {} 
    | REALLIT {} 
    | BOOLLIT {}
    ;
%%

int main() {
    if(argc > 1){
        if(strcmp(argv[1], "-t") == 0) flag = 1;
        else if(strcmp(argv[1], "-e2") == 0) flag = 0;
    }
    yyparse();
    return 0;
}
