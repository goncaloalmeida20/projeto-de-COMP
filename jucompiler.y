%{
    #include <stdio.h>

    int flag = 0; // 0: -e2 or no flag, 1: -t

    int yylex(void);
    void yyerror (const char *s);
%}

%token AND ASSIGN STAR COMMA DIV EQ GE GT LBRACE LE LPAR LSQ LT MINUS MOD NE NOT OR PLUS RBRACE RPAR RSQ SEMICOLON ARROW LSHIFT RSHIFT XOR BOOL CLASS DOTLENGTH DOUBLE ELSE IF INT PRINT PARSEINT PUBLIC RETURN STATIC STRING VOID WHILE
%token STRLIT BOOLLIT RESERVED INTLIT REALLIT ID


%%
Program: CLASS ID LBRACE '{' MethodDecl | FieldDecl | SEMICOLON '}' RBRACE

MethodDecl: PUBLIC STATIC MethodHeader MethodBody

FieldDecl: PUBLIC STATIC Type ID '{' COMMA ID '}' SEMICOLON

Type: BOOL | INT | DOUBLE

MethodHeader: '(' Type | VOID ')' ID LPAR '[' FormalParams ']' RPAR

FormalParams: Type ID { COMMA Type ID }
    | STRING LSQ RSQ ID
    ;

MethodBody: LBRACE '{' Statement | VarDecl '}' RBRACE

VarDecl: Type ID '{' COMMA ID '}' SEMICOLON

Statement: LBRACE '{' Statement '}' RBRACE
    | IF LPAR Expr RPAR Statement '[' ELSE Statement ']'
    | WHILE LPAR Expr RPAR Statement
    | RETURN '[' Expr ']' SEMICOLON
    | '[' '(' MethodInvocation | Assignment | ParseArgs ')' ']' SEMICOLON
    | PRINT LPAR '(' Expr | STRLIT ')' RPAR SEMICOLON
    ;

MethodInvocation: ID LPAR '[' Expr '{' COMMA Expr '}' ']' RPAR

Assignment: ID ASSIGN Expr

ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR

Expr: Expr '(' PLUS | MINUS | STAR | DIV | MOD ')' Expr
    | Expr '(' AND | OR | XOR | LSHIFT | RSHIFT ')' Expr
    | Expr '(' EQ | GE | GT | LE | LT | NE ')' Expr
    | '(' MINUS | NOT | PLUS ')' Expr
    | LPAR Expr RPAR
    | MethodInvocation | Assignment | ParseArgs
    | ID '[' DOTLENGTH ']'
    | INTLIT | REALLIT | BOOLLIT
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

