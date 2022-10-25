%{
/*
Autores:
Gonçalo Almeida, nº2020218868
João Santos, nº2020218995
*/
    #include <stdio.h>
    #include <stdlib.h>
    #include "y.tab.h"
    #define MAX_STRING_SIZE 1024

    extern int flag;
    int line = 1, line_temp = 1;
    int col = 1, col_temp = 1;
    int current_string_pos = 0, print_string = 1;
    char string[MAX_STRING_SIZE];
%}
num [0-9]
numnotzero [1-9]
let [$_a-zA-Z]
escape_chars [\\\"ntrf]
invalid_escape [^\n\r\\\"ntrf]
ignore [ \t\r\f]
%X MLCOMMENT STRING_STATE
%%
"\n" {line++; col = 1;}
"//"[^\r\n]* {;}
"/*" {line_temp = line; col_temp = col; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {line = line_temp; col = col_temp; BEGIN (0);}
<MLCOMMENT>"\n" {line_temp++; col_temp = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {col_temp++;}
"\"" {col_temp = col; col_temp += yyleng; current_string_pos = 0; print_string = 1; BEGIN (STRING);}
<STRING_STATE>"\"" {col_temp += yyleng; string[0] = 0; col = col_temp; BEGIN (0); if(print_string) printf("STRLIT(\"%s\")\n", string); yylval.str = strdup(string); string[0] = 0; return STRLIT; }
<STRING_STATE><<EOF>> {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING_STATE>"\n" {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); string[0] = 0; line++; col = 1; BEGIN (0);}
<STRING_STATE>("\\"{escape_chars})|[^\\] {col_temp += yyleng; strcpy(&string[current_string_pos], yytext); current_string_pos += yyleng;}
<STRING_STATE>("\\"{invalid_escape}?) {print_string = 0; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}
"&&" {col += yyleng; if(flag) printf("AND\n"); return AND;}
"="  {col += yyleng; if(flag) printf("ASSIGN\n"); return ASSIGN;}
"*"  {col += yyleng; if(flag) printf("STAR\n"); return STAR;}
","  {col += yyleng; if(flag) printf("COMMA\n"); return COMMA;}
"/"  {col += yyleng; if(flag) printf("DIV\n"); return DIV;}
"==" {col += yyleng; if(flag) printf("EQ\n"); return EQ;}
">=" {col += yyleng; if(flag) printf("GE\n"); return GE;}
">"  {col += yyleng; if(flag) printf("GT\n"); return GT;}
"{"  {col += yyleng; if(flag) printf("LBRACE\n"); return LBRACE;}
"<=" {col += yyleng; if(flag) printf("LE\n"); return LE;}
"("  {col += yyleng; if(flag) printf("LPAR\n"); return LPAR;}
"["  {col += yyleng; if(flag) printf("LSQ\n"); return LSQ;}
"<"  {col += yyleng; if(flag) printf("LT\n"); return LT;}
"-"  {col += yyleng; if(flag) printf("MINUS\n"); return MINUS;}
"%"  {col += yyleng; if(flag) printf("MOD\n"); return MOD;}
"!=" {col += yyleng; if(flag) printf("NE\n"); return NE;}
"!"  {col += yyleng; if(flag) printf("NOT\n"); return NOT;}
"||" {col += yyleng; if(flag) printf("OR\n"); return OR;}
"+"  {col += yyleng; if(flag) printf("PLUS\n"); return PLUS;}
"}"  {col += yyleng; if(flag) printf("RBRACE\n"); return RBRACE;}
")"  {col += yyleng; if(flag) printf("RPAR\n"); return RPAR;}
"]"  {col += yyleng; if(flag) printf("RSQ\n"); return RSQ;}
";"  {col += yyleng; if(flag) printf("SEMICOLON\n"); return SEMICOLON;}
"->" {col += yyleng; if(flag) printf("ARROW\n"); return ARROW;}
"<<" {col += yyleng; if(flag) printf("LSHIFT\n"); return LSHIFT;}
">>" {col += yyleng; if(flag) printf("RSHIFT\n"); return RSHIFT;}
"^"  {col += yyleng; if(flag) printf("XOR\n"); return XOR;}
"true"|"false" {col += yyleng; if(flag) printf("BOOLLIT(%s)\n", yytext); yylval.str = strdup(yytext); return BOOLLIT;}
"boolean" {col += yyleng; if(flag) printf("BOOL\n"); return BOOL;}
"class"   {col += yyleng; if(flag) printf("CLASS\n"); return CLASS;}
".length" {col += yyleng; if(flag) printf("DOTLENGTH\n");return DOTLENGTH;}
"double"  {col += yyleng; if(flag) printf("DOUBLE\n"); return DOUBLE;}
"else"    {col += yyleng; if(flag) printf("ELSE\n"); return ELSE;}
"if"      {col += yyleng; if(flag) printf("IF\n"); return IF;}
"int"     {col += yyleng; if(flag) printf("INT\n"); return INT;}
"System.out.print" {col += yyleng; if(flag) printf("PRINT\n"); return PRINT;}
"Integer.parseInt" {col += yyleng; if(flag) printf("PARSEINT\n"); return PARSEINT;}
"public" {col += yyleng; if(flag) printf("PUBLIC\n"); return PUBLIC;}
"return" {col += yyleng; if(flag) printf("RETURN\n"); return RETURN;}
"static" {col += yyleng; if(flag) printf("STATIC\n"); return STATIC;}
"String" {col += yyleng; if(flag) printf("STRING\n"); return STRING;}
"void"   {col += yyleng; if(flag) printf("VOID\n"); return VOID;}
"while"  {col += yyleng; if(flag) printf("WHILE\n"); return WHILE;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while" {col += yyleng; if(flag) printf("RESERVED(%s)\n", yytext); yylval.str = strdup(yytext); return RESERVED;}
{numnotzero}("_"*{num})* {col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); return INTLIT;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|"")("0."|"0"("0"|"_"+"0")*|("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)?))) {col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); return REALLIT;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|"")("0."|"0"|("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)?)))? {col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); return REALLIT;}
"0" {col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); return INTLIT;}
{let}({let}|{num})* {col += yyleng; if(flag) printf("ID(%s)\n", yytext); yylval.str = strdup(yytext); return ID;}
{ignore} {col += yyleng;}
. {printf("Line %d, col %d: illegal character (%c)\n", line, col, yytext[0]); col += yyleng;}
%%

int yywrap(){
    return 1;
}
