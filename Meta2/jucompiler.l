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

    extern int flag_yacc;
    extern int line_yacc, col_yacc;
    extern int yacc_error;
    extern void yyerror(char*);

    int flag = 0;
    int line = 1, line_temp = 1;
    int col = 1, col_temp = 1;
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
{new_line} {line++; col = 1; col_yacc = col; line_yacc = line;}
"//"[^\r\n]* {;}

"/*" {line_temp = line; col_temp = col; col_temp += yyleng; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {col_temp += yyleng; line = line_temp; col = col_temp; BEGIN (0);}
<MLCOMMENT>{new_line} {line_temp++; col_temp = 1;}
<MLCOMMENT><<EOF>> {col_yacc = col_temp; line_yacc = line_temp; printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {col_temp+=yyleng;}

"\""{valid_str}"\"" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("STRLIT(%s)\n", yytext); if(flag_yacc >= 0){yylval.str = strdup(yytext); return STRLIT;}}
"\""{valid_str}{new_line}? {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1;}
"\""{valid_str}"\\"{invalid_escape} {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 2, &yytext[yyleng-2]); BEGIN (STRING_ERROR);}
"\""{valid_str}"\\" {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 1, &yytext[yyleng-1]); BEGIN (STRING_ERROR);}
<STRING_ERROR>"\"" {col_temp += yyleng; col = col_temp; BEGIN (0);}
<STRING_ERROR><<EOF>> {printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING_ERROR>{new_line} {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1; BEGIN (0);}
<STRING_ERROR>("\\"{escape_chars})|[^\\] {col_temp += yyleng;}
<STRING_ERROR>("\\"{invalid_escape}?) {printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}

"&&" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("AND\n"); if(flag_yacc >= 0) return AND;}
"="  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("ASSIGN\n"); if(flag_yacc >= 0) return ASSIGN;}
"*"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("STAR\n"); if(flag_yacc >= 0) return STAR;}
","  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("COMMA\n"); if(flag_yacc >= 0) return COMMA;}
"/"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("DIV\n"); if(flag_yacc >= 0) return DIV;}
"==" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("EQ\n"); if(flag_yacc >= 0) return EQ;}
">=" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("GE\n"); if(flag_yacc >= 0) return GE;}
">"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("GT\n"); if(flag_yacc >= 0) return GT;}
"{"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LBRACE\n"); if(flag_yacc >= 0) return LBRACE;}
"<=" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LE\n"); if(flag_yacc >= 0) return LE;}
"("  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LPAR\n"); if(flag_yacc >= 0) return LPAR;}
"["  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LSQ\n"); if(flag_yacc >= 0) return LSQ;}
"<"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LT\n"); if(flag_yacc >= 0) return LT;}
"-"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("MINUS\n"); if(flag_yacc >= 0) return MINUS;}
"%"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("MOD\n"); if(flag_yacc >= 0) return MOD;}
"!=" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("NE\n"); if(flag_yacc >= 0) return NE;}
"!"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("NOT\n"); if(flag_yacc >= 0) return NOT;}
"||" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("OR\n"); if(flag_yacc >= 0) return OR;}
"+"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("PLUS\n"); if(flag_yacc >= 0) return PLUS;}
"}"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("RBRACE\n"); if(flag_yacc >= 0) return RBRACE;}
")"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("RPAR\n"); if(flag_yacc >= 0) return RPAR;}
"]"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("RSQ\n"); if(flag_yacc >= 0) return RSQ;}
";"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("SEMICOLON\n"); if(flag_yacc >= 0) return SEMICOLON;}
"->" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("ARROW\n"); if(flag_yacc >= 0) return ARROW;}
"<<" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("LSHIFT\n"); if(flag_yacc >= 0) return LSHIFT;}
">>" {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("RSHIFT\n"); if(flag_yacc >= 0) return RSHIFT;}
"^"  {col_yacc = col; line_yacc = line; col += yyleng; if(flag) printf("XOR\n"); if(flag_yacc >= 0) return XOR;}
"true"|"false" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("BOOLLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return BOOLLIT;}
"boolean" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("BOOL\n"); if(flag_yacc >= 0) return BOOL;}
"class"   {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("CLASS\n"); if(flag_yacc >= 0) return CLASS;}
".length" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("DOTLENGTH\n"); if(flag_yacc >= 0) return DOTLENGTH;}
"double"  {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("DOUBLE\n"); if(flag_yacc >= 0) return DOUBLE;}
"else"    {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("ELSE\n"); if(flag_yacc >= 0) return ELSE;}
"if"      {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("IF\n"); if(flag_yacc >= 0) return IF;}
"int"     {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("INT\n"); if(flag_yacc >= 0) return INT;}
"System.out.print" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("PRINT\n"); if(flag_yacc >= 0) return PRINT;}
"Integer.parseInt" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("PARSEINT\n"); if(flag_yacc >= 0) return PARSEINT;}
"public" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("PUBLIC\n"); if(flag_yacc >= 0) return PUBLIC;}
"return" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("RETURN\n"); if(flag_yacc >= 0) return RETURN;}
"static" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("STATIC\n"); if(flag_yacc >= 0) return STATIC;}
"String" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("STRING\n"); if(flag_yacc >= 0) return STRING;}
"void"   {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("VOID\n"); if(flag_yacc >= 0) return VOID;}
"while"  {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("WHILE\n"); if(flag_yacc >= 0) return WHILE;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while"  {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("RESERVED(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return RESERVED;}
{numnotzero}("_"*{num})* {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return INTLIT;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|""){num}("_"*{num})*) {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return REALLIT;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|""){num}("_"*{num})*)? {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("REALLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return REALLIT;}
"0" {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("INTLIT(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return INTLIT;}
{let}({let}|{num})* {col_yacc = col; line_yacc = line;col += yyleng; if(flag) printf("ID(%s)\n", yytext); yylval.str = strdup(yytext); if(flag_yacc >= 0) return ID;}
{ignore} {col += yyleng; col_yacc = col;}
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
            free_tree(root);
        }
        else if(strcmp(argv[1], "-t") == 0) {
            flag_yacc = 1;
            yyparse();
            if(!yacc_error){
                print_tree(root, 0);
            }
            free_tree(root);
        }
    }
    return 0;
}

int yywrap(){
    return 1;
}
