%{
    #include <stdio.h>
    #include <stdlib.h>

    int line = 1;
    int col = 1;
%}
num [0-9]
let [$_a-zA-Z]
ignore [" "\t\r\f]
invalid_escape [^\n\t\r\f]
%X STRING
%%
"\"" {printf("STRLIT\n"); BEGIN (STRING); col += yyleng;}
<STRING>"\\f" {printf("STRLIT(\"\\f\")\n"); col += yyleng;}
<STRING>"\\n" {printf("STRLIT(\"\\n\")\n"); col += yyleng;}
<STRING>"\\r" {printf("STRLIT(\"\\r\")\n"); col += yyleng;}
<STRING>"\\t" {printf("STRLIT(\"\\t\")\n"); col += yyleng;}
<STRING>"\\\\" {printf("STRLIT(\"\\\\\")\n"); col += yyleng;}
<STRING>"\\"{invalid_escape} {printf("Invalid escape character (%s)\n", yytext); col += yyleng;}
<STRING>"\n" {printf("Unterminated string literal\n"); line++; col += yyleng; BEGIN (0);}
<STRING>"\"" {printf("STRLIT(\"\\\"\")n"); col += yyleng; BEGIN (0);}
"&&" {printf("AND\n"); col += yyleng;}
"=" {printf("ASSIGN\n"); col += yyleng;}
"*" {printf("STAR\n"); col += yyleng;}
"," {printf("COMMA\n"); col += yyleng;}
"/" {printf("DIV\n"); col += yyleng;}
"==" {printf("EQ\n"); col += yyleng;}
">=" {printf("GE\n"); col += yyleng;}
">" {printf("GT\n"); col += yyleng;}
"{" {printf("LBRACE\n"); col += yyleng;}
"<=" {printf("LE\n"); col += yyleng;}
"(" {printf("LPAR\n"); col += yyleng;}
"[" {printf("LSQ\n"); col += yyleng;}
"<" {printf("LT\n"); col += yyleng;}
"-" {printf("MINUS\n"); col += yyleng;}
"%" {printf("MOD\n"); col += yyleng;}
"!=" {printf("NE\n"); col += yyleng;}
"!" {printf("NOT\n"); col += yyleng;}
"||" {printf("OR\n"); col += yyleng;}
"+" {printf("PLUS\n"); col += yyleng;}
"}" {printf("RBRACE\n"); col += yyleng;}
")" {printf("RPAR\n"); col += yyleng;}
"]" {printf("RSQ\n"); col += yyleng;}
";" {printf("SEMICOLON\n"); col += yyleng;}
"->" {printf("ARROW\n"); col += yyleng;}
"<<" {printf("LSHIFT\n"); col += yyleng;}
">>" {printf("RSHIFT\n"); col += yyleng;}
"^" {printf("XOR\n"); col += yyleng;}
"true"|"false" {printf("BOOLLIT\n"); col += yyleng;}
"boolean" {printf("BOOL\n"); col += yyleng;}
"class" {printf("CLASS\n"); col += yyleng;}
".length" {printf("DOTLENGTH\n"); col += yyleng;}
"double" {printf("DOUBLE\n"); col += yyleng;}
"else" {printf("ELSE\n"); col += yyleng;}
"if" {printf("IF\n"); col += yyleng;}
"int" {printf("INT\n"); col += yyleng;}
"System.out.print" {printf("PRINT\n"); col += yyleng;}
"Integer.parseInt" {printf("PARSEINT\n"); col += yyleng;}
"public" {printf("PUBLIC\n"); col += yyleng;}
"return" {printf("RETURN\n"); col += yyleng;}
"static" {printf("STATIC\n"); col += yyleng;}
"String" {printf("STRING\n"); col += yyleng;}
"void" {printf("VOID\n"); col += yyleng;}
"while" {printf("WHILE\n"); col += yyleng;}
"++"|"--"|"null"|"Integer"|"System" {printf("RESERVED\n"); col += yyleng;}
{num}("_"*{num})* {printf("INTLIT(%s)\n", yytext); col += yyleng;}
{num}("_"*{num})*("."{num}("_"*{num})*)?(("e"|"E")("+"|"-"|""){num}("_"*{num})*("."{num}("_"*{num})*)?)? {printf("REALLIT(%s)\n", yytext); col += yyleng;}
"."{num}("_"*{num})*(("e"|"E")("+"|"-"|""){num}("_"*{num})*("."{num}("_"*{num})*)?)? {printf("REALLIT(%s)\n", yytext); col += yyleng;}
{let}({let}|{num})* {printf("ID(%s)\n", yytext);}
"\n" {line++; col = 1;}
{ignore} {;}
. {printf("Line %d, col %d: illegal character (%c)\n", line, col, yytext[0]); col += yyleng;}
%%
int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}
