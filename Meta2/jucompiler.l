%{
    /*
        Autores:
            Gonçalo Fernandes Diogo de Almeida, nº2020218868
            João Bernardo de Jesus Santos, nº2020218995
    */
    
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "y.tab.h"

    #define MAX_STRING_SIZE 32768

    extern int flag_yacc;
    extern int line_yacc, col_yacc;
    extern void yyerror(char*);

    int flag = 0;
    int line, line_temp = 1;
    int col, col_temp = 1;
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
"\r\n"|"\n"|"\r" {line++; col = 1;}
"//"[^\r\n]* {;}

"/*" {line_temp = line; col_temp = col; col_temp += yyleng; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {col_temp += yyleng; line = line_temp; col = col_temp; BEGIN (0);}
<MLCOMMENT>"\r\n"|"\n"|"\r" {line_temp++; col_temp = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {col_temp+=yyleng;}

"\"" {col_temp = col; col_temp += yyleng; current_string_pos = 0; print_string = 1; BEGIN (STRING_STATE);}
<STRING_STATE>"\"" {col_temp += yyleng; if(print_string && flag) printf("STRLIT(\"%s\")\n", string); yylval.str = strdup(string); string[0] = 0; col = col_temp; BEGIN (0); if(flag_yacc >= 0) return STRLIT;}
<STRING_STATE><<EOF>> {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING_STATE>"\r\n"|"\n"|"\r" {print_string = 0; printf("Line %d, col %d: unterminated string literal\n", line, col); string[0] = 0; line++; col = 1; BEGIN (0);}
<STRING_STATE>("\\"{escape_chars})|[^\\] {col_temp += yyleng; strcpy(&string[current_string_pos], yytext); current_string_pos += yyleng;}
<STRING_STATE>("\\"{invalid_escape}?) {print_string = 0; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}

"&&" {col += yyleng; if(flag) printf("AND\n"); if(flag_yacc >= 0) return AND;}
"="  {col += yyleng; if(flag) printf("ASSIGN\n"); if(flag_yacc >= 0) return ASSIGN;}
"*"  {col += yyleng; if(flag) printf("STAR\n"); if(flag_yacc >= 0) return STAR;}
","  {col += yyleng; if(flag) printf("COMMA\n"); if(flag_yacc >= 0) return COMMA;}
"/"  {col += yyleng; if(flag) printf("DIV\n"); if(flag_yacc >= 0) return DIV;}
"==" {col += yyleng; if(flag) printf("EQ\n"); if(flag_yacc >= 0) return EQ;}
">=" {col += yyleng; if(flag) printf("GE\n"); if(flag_yacc >= 0) return GE;}
">"  {col += yyleng; if(flag) printf("GT\n"); if(flag_yacc >= 0) return GT;}
"{"  {col += yyleng; if(flag) printf("LBRACE\n"); if(flag_yacc >= 0) return LBRACE;}
"<=" {col += yyleng; if(flag) printf("LE\n"); if(flag_yacc >= 0) return LE;}
"("  {col += yyleng; if(flag) printf("LPAR\n"); if(flag_yacc >= 0) return LPAR;}
"["  {col += yyleng; if(flag) printf("LSQ\n"); if(flag_yacc >= 0) return LSQ;}
"<"  {col += yyleng; if(flag) printf("LT\n"); if(flag_yacc >= 0) return LT;}
"-"  {col += yyleng; if(flag) printf("MINUS\n"); if(flag_yacc >= 0) return MINUS;}
"%"  {col += yyleng; if(flag) printf("MOD\n"); if(flag_yacc >= 0) return MOD;}
"!=" {col += yyleng; if(flag) printf("NE\n"); if(flag_yacc >= 0) return NE;}
"!"  {col += yyleng; if(flag) printf("NOT\n"); if(flag_yacc >= 0) return NOT;}
"||" {col += yyleng; if(flag) printf("OR\n"); if(flag_yacc >= 0) return OR;}
"+"  {col += yyleng; if(flag) printf("PLUS\n"); if(flag_yacc >= 0) return PLUS;}
"}"  {col += yyleng; if(flag) printf("RBRACE\n"); if(flag_yacc >= 0) return RBRACE;}
")"  {col += yyleng; if(flag) printf("RPAR\n"); if(flag_yacc >= 0) return RPAR;}
"]"  {col += yyleng; if(flag) printf("RSQ\n"); if(flag_yacc >= 0) return RSQ;}
";"  {col += yyleng; if(flag) printf("SEMICOLON\n"); if(flag_yacc >= 0) return SEMICOLON;}
"->" {col += yyleng; if(flag) printf("ARROW\n"); if(flag_yacc >= 0) return ARROW;}
"<<" {col += yyleng; if(flag) printf("LSHIFT\n"); if(flag_yacc >= 0) return LSHIFT;}
">>" {col += yyleng; if(flag) printf("RSHIFT\n"); if(flag_yacc >= 0) return RSHIFT;}
"^"  {col += yyleng; if(flag) printf("XOR\n"); if(flag_yacc >= 0) return XOR;}
"true"|"false" {col += yyleng; if(flag) printf("BOOLLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return BOOLLIT;}
"boolean" {col += yyleng; if(flag) printf("BOOL\n"); if(flag_yacc >= 0) return BOOL;}
"class"   {col += yyleng; if(flag) printf("CLASS\n"); if(flag_yacc >= 0) return CLASS;}
".length" {col += yyleng; if(flag) printf("DOTLENGTH\n"); if(flag_yacc >= 0) return DOTLENGTH;}
"double"  {col += yyleng; if(flag) printf("DOUBLE\n"); if(flag_yacc >= 0) return DOUBLE;}
"else"    {col += yyleng; if(flag) printf("ELSE\n"); if(flag_yacc >= 0) return ELSE;}
"if"      {col += yyleng; if(flag) printf("IF\n"); if(flag_yacc >= 0) return IF;}
"int"     {col += yyleng; if(flag) printf("INT\n"); if(flag_yacc >= 0) return INT;}
"System.out.print" {col += yyleng; if(flag) printf("PRINT\n"); if(flag_yacc >= 0) return PRINT;}
"Integer.parseInt" {col += yyleng; if(flag) printf("PARSEINT\n"); if(flag_yacc >= 0) return PARSEINT;}
"public" {col += yyleng; if(flag) printf("PUBLIC\n"); if(flag_yacc >= 0) return PUBLIC;}
"return" {col += yyleng; if(flag) printf("RETURN\n"); if(flag_yacc >= 0) return RETURN;}
"static" {col += yyleng; if(flag) printf("STATIC\n"); if(flag_yacc >= 0) return STATIC;}
"String" {col += yyleng; if(flag) printf("STRING\n"); if(flag_yacc >= 0) return STRING;}
"void"   {col += yyleng; if(flag) printf("VOID\n"); if(flag_yacc >= 0) return VOID;}
"while"  {col += yyleng; if(flag) printf("WHILE\n"); if(flag_yacc >= 0) return WHILE;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while"  {col += yyleng; if(flag) printf("RESERVED(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return RESERVED;}
{numnotzero}("_"*{num})* {col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return INTLIT;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|""){num}("_"*{num})*) {col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return REALLIT;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|""){num}("_"*{num})*)? {col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return REALLIT;}
"0" {col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return INTLIT;}
{let}({let}|{num})* {col += yyleng; if(flag) printf("ID(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return ID;}
{ignore} {col += yyleng;}
. {printf("Line %d, col %d: illegal character (%s)\n", line, col, yytext); col += yyleng;}
%%

int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0) {
            flag = 1;
            flag_yacc = -1;
            yylex();
        }
        else if(strcmp(argv[1], "-e1") == 0) {
            flag = 0;
            flag_yacc = -1;
            yylex();
        }
        else if(strcmp(argv[1], "-e2") == 0) {
            flag_yacc = 0;
            yyparse();
        }
        else if(strcmp(argv[1], "-t") == 0) {
            flag_yacc = 1;
            yyparse();
            print_tree(root, 0);
        }
    }
    return 0;
}

int yywrap(){
    return 1;
}
