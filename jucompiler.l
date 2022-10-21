%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define MAX_STRING_SIZE 1024

    int line = 1, line_temp = 1;
    int col = 1, col_temp = 1;
    int flag = 0; // 0: -e1 or no flag, 1: -l
    int current_string_pos = 0, print_string = 1;
    char string[MAX_STRING_SIZE];
%}
num [0-9]
numnotzero [1-9]
let [$_a-zA-Z]
escape_chars [\\\"ntrf]
invalid_escape [^\n\r\\\"ntrf]
ignore [ \t\r\f]
%X MLCOMMENT STRING
%%
"\n" {line++; col = 1;}
"//"[^\r\n]* {;}
"/*" {line_temp = line; col_temp = col; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {line = line_temp; col = col_temp; BEGIN (0);}
<MLCOMMENT>"\n" {line_temp++; col_temp = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {col_temp++;}
"\"" {col_temp = col; col_temp += yyleng; current_string_pos = 0; print_string = 1; BEGIN (STRING);}
<STRING>"\"" {col_temp += yyleng; string[0] = 0; col = col_temp; BEGIN (0); if(print_string) return STRLIT; }
<STRING><<EOF>> {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING>"\n" {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); string[0] = 0; line++; col = 1; BEGIN (0);}
<STRING>("\\"{escape_chars})|[^\\] {col_temp += yyleng; strcpy(&string[current_string_pos], yytext); current_string_pos += yyleng;}
<STRING>("\\"{invalid_escape}?) {print_string = 0; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}
"&&" {col += yyleng; if(flag) return AND;}
"="  {col += yyleng; if(flag) return ASSIGN;}
"*"  {col += yyleng; if(flag) return STAR;}
","  {col += yyleng; if(flag) return COMMA;}
"/"  {col += yyleng; if(flag) return DIV;}
"==" {col += yyleng; if(flag) return EQ;}
">=" {col += yyleng; if(flag) return GE;}
">"  {col += yyleng; if(flag) return GT;}
"{"  {col += yyleng; if(flag) return LBRACE;}
"<=" {col += yyleng; if(flag) return LE;}
"("  {col += yyleng; if(flag) return LPAR;}
"["  {col += yyleng; if(flag) return LSQ;}
"<"  {col += yyleng; if(flag) return LT;}
"-"  {col += yyleng; if(flag) return MINUS;}
"%"  {col += yyleng; if(flag) return MOD;}
"!=" {col += yyleng; if(flag) return NE;}
"!"  {col += yyleng; if(flag) return NOT;}
"||" {col += yyleng; if(flag) return OR;}
"+"  {col += yyleng; if(flag) return PLUS;}
"}"  {col += yyleng; if(flag) return RBRACE;}
")"  {col += yyleng; if(flag) return RPAR;}
"]"  {col += yyleng; if(flag) return RSQ;}
";"  {col += yyleng; if(flag) return SEMICOLON;}
"->" {col += yyleng; if(flag) return ARROW;}
"<<" {col += yyleng; if(flag) return LSHIFT;}
">>" {col += yyleng; if(flag) return RSHIFT;}
"^"  {col += yyleng; if(flag) return XOR;}
"true"|"false" {col += yyleng; if(flag) return BOOLLIT;}
"boolean" {col += yyleng; if(flag) return BOOL;}
"class"   {col += yyleng; if(flag) return CLASS;}
".length" {col += yyleng; if(flag) return DOTLENGTH;}
"double"  {col += yyleng; if(flag) return DOUBLE;}
"else"    {col += yyleng; if(flag) return ELSE;}
"if"      {col += yyleng; if(flag) return IF;}
"int"     {col += yyleng; if(flag) return INT;}
"System.out.print" {col += yyleng; if(flag) return PRINT;}
"Integer.parseInt" {col += yyleng; if(flag) return PARSEINT;}
"public" {col += yyleng; if(flag) return PUBLIC;}
"return" {col += yyleng; if(flag) return RETURN;}
"static" {col += yyleng; if(flag) return STATIC;}
"String" {col += yyleng; if(flag) return STRING;}
"void"   {col += yyleng; if(flag) return VOID;}
"while"  {col += yyleng; if(flag) return WHILE;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while" {col += yyleng; if(flag) return RESERVED;}
{numnotzero}("_"*{num})* {col += yyleng; if(flag) return INTLIT;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|"")("0."|"0"("0"|"_"+"0")*|("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)?))) {col += yyleng; if(flag) return REALLIT;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|"")("0."|"0"|("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)?)))? {col += yyleng; if(flag) return REALLIT;}
"0" {col += yyleng; if(flag) return INTLIT;}
{let}({let}|{num})* {col += yyleng; if(flag) return ID;}
{ignore} {col += yyleng;}
. {printf("Line %d, col %d: illegal character (%c)\n", line, col, yytext[0]); col += yyleng;}
%%
int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0) flag = 1;
        else if(strcmp(argv[1], "-e1") == 0) flag = 0;
    }
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}
