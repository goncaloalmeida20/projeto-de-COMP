%{
    /*
        Autores:
            Gonçalo Fernandes Diogo de Almeida, nº2020218868
            João Bernardo de Jesus Santos, nº2020218995
    */
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int line = 1, line_temp = 1;
    int col = 1, col_temp = 1;
    int flag = 0; // 0: -e1 or no flag, 1: -l
%}
num [0-9]
numnotzero [1-9]
let [$_a-zA-Z]
new_line "\r\n"|"\n"|"\r"
escape_chars [\\\"ntrf]
invalid_escape [^\n\r\\\"ntrf]
valid_str (("\\"{escape_chars})|[^\\\"\r\n])*
ignore [ \t\r\f]
%X MLCOMMENT STRING_ERROR
%%
{new_line} {line++; col = 1;}
"//"[^\r\n]* {;}

"/*" {line_temp = line; col_temp = col; col_temp += yyleng; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {col_temp += yyleng; line = line_temp; col = col_temp; BEGIN (0);}
<MLCOMMENT>{new_line} {line_temp++; col_temp = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {col_temp+=yyleng;}

"\""{valid_str}"\"" {col += yyleng; if(flag) printf("STRLIT(%s)\n", yytext);}
"\""{valid_str}{new_line}? {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1;}
"\""{valid_str}"\\"{invalid_escape} {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 2, &yytext[yyleng-2]); BEGIN (STRING_ERROR);}
"\""{valid_str}"\\" {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 1, &yytext[yyleng-1]); BEGIN (STRING_ERROR);}
<STRING_ERROR>"\"" {col_temp += yyleng; col = col_temp; BEGIN (0);}
<STRING_ERROR><<EOF>> {printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING_ERROR>{new_line} {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1; BEGIN (0);}
<STRING_ERROR>("\\"{escape_chars})|[^\\] {col_temp += yyleng;}
<STRING_ERROR>("\\"{invalid_escape}?) {printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}

"&&" {if(flag) printf("AND\n"); col += yyleng;}
"=" {if(flag) printf("ASSIGN\n"); col += yyleng;}
"*" {if(flag) printf("STAR\n"); col += yyleng;}
"," {if(flag) printf("COMMA\n"); col += yyleng;}
"/" {if(flag) printf("DIV\n"); col += yyleng;}
"==" {if(flag) printf("EQ\n"); col += yyleng;}
">=" {if(flag) printf("GE\n"); col += yyleng;}
">" {if(flag) printf("GT\n"); col += yyleng;}
"{" {if(flag) printf("LBRACE\n"); col += yyleng;}
"<=" {if(flag) printf("LE\n"); col += yyleng;}
"(" {if(flag) printf("LPAR\n"); col += yyleng;}
"[" {if(flag) printf("LSQ\n"); col += yyleng;}
"<" {if(flag) printf("LT\n"); col += yyleng;}
"-" {if(flag) printf("MINUS\n"); col += yyleng;}
"%" {if(flag) printf("MOD\n"); col += yyleng;}
"!=" {if(flag) printf("NE\n"); col += yyleng;}
"!" {if(flag) printf("NOT\n"); col += yyleng;}
"||" {if(flag) printf("OR\n"); col += yyleng;}
"+" {if(flag) printf("PLUS\n"); col += yyleng;}
"}" {if(flag) printf("RBRACE\n"); col += yyleng;}
")" {if(flag) printf("RPAR\n"); col += yyleng;}
"]" {if(flag) printf("RSQ\n"); col += yyleng;}
";" {if(flag) printf("SEMICOLON\n"); col += yyleng;}
"->" {if(flag) printf("ARROW\n"); col += yyleng;}
"<<" {if(flag) printf("LSHIFT\n"); col += yyleng;}
">>" {if(flag) printf("RSHIFT\n"); col += yyleng;}
"^" {if(flag) printf("XOR\n"); col += yyleng;}
"true"|"false" {if(flag) printf("BOOLLIT(%s)\n", yytext); col += yyleng;}
"boolean" {if(flag) printf("BOOL\n"); col += yyleng;}
"class" {if(flag) printf("CLASS\n"); col += yyleng;}
".length" {if(flag) printf("DOTLENGTH\n"); col += yyleng;}
"double" {if(flag) printf("DOUBLE\n"); col += yyleng;}
"else" {if(flag) printf("ELSE\n"); col += yyleng;}
"if" {if(flag) printf("IF\n"); col += yyleng;}
"int" {if(flag) printf("INT\n"); col += yyleng;}
"System.out.print" {if(flag) printf("PRINT\n"); col += yyleng;}
"Integer.parseInt" {if(flag) printf("PARSEINT\n"); col += yyleng;}
"public" {if(flag) printf("PUBLIC\n"); col += yyleng;}
"return" {if(flag) printf("RETURN\n"); col += yyleng;}
"static" {if(flag) printf("STATIC\n"); col += yyleng;}
"String" {if(flag) printf("STRING\n"); col += yyleng;}
"void" {if(flag) printf("VOID\n"); col += yyleng;}
"while" {if(flag) printf("WHILE\n"); col += yyleng;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while" {if(flag) printf("RESERVED(%s)\n", yytext); col += yyleng;}
{numnotzero}("_"*{num})* {if(flag) printf("INTLIT(%s)\n", yytext); col += yyleng;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|""){num}("_"*{num})*) {if(flag) printf("REALLIT(%s)\n", yytext); col += yyleng;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|""){num}("_"*{num})*)? {if(flag) printf("REALLIT(%s)\n", yytext); col += yyleng;}
"0" {if(flag) printf("INTLIT(%s)\n", yytext); col += yyleng;}
{let}({let}|{num})* {if(flag) printf("ID(%s)\n", yytext); col += yyleng;}
{ignore} {col += yyleng;}
. {printf("Line %d, col %d: illegal character (%s)\n", line, col, yytext); col += yyleng;}
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

