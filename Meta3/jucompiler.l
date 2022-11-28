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
    #include "symbol_table.h"
    #include "semantics.h"

    extern int flag_yacc;
    extern int line_yacc, col_yacc;
    extern int yacc_error;
    extern void yyerror(char*);

    void update_vars(char*);

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

"\""{valid_str}"\"" {update_vars(yytext); if(flag) printf("STRLIT(%s)\n", yytext); if(flag_yacc >= 0) return STRLIT;}
"\""{valid_str}{new_line}? {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1;}
"\""{valid_str}"\\"{invalid_escape} {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 2, &yytext[yyleng-2]); BEGIN (STRING_ERROR);}
"\""{valid_str}"\\" {col_temp = col; col_temp += yyleng; printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp - 1, &yytext[yyleng-1]); BEGIN (STRING_ERROR);}
<STRING_ERROR>"\"" {col_temp += yyleng; col = col_temp; BEGIN (0);}
<STRING_ERROR><<EOF>> {printf("Line %d, col %d: unterminated string literal\n", line, col); BEGIN (0);}
<STRING_ERROR>{new_line} {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1; BEGIN (0);}
<STRING_ERROR>("\\"{escape_chars})|[^\\] {col_temp += yyleng;}
<STRING_ERROR>("\\"{invalid_escape}?) {printf("Line %d, col %d: invalid escape sequence (%s)\n", line, col_temp, yytext); col_temp += yyleng;}

"&&" {update_vars(NULL); if(flag) printf("AND\n"); if(flag_yacc >= 0) return AND;}
"="  {update_vars(NULL); if(flag) printf("ASSIGN\n"); if(flag_yacc >= 0) return ASSIGN;}
"*"  {update_vars(NULL); if(flag) printf("STAR\n"); if(flag_yacc >= 0) return STAR;}
","  {update_vars(NULL); if(flag) printf("COMMA\n"); if(flag_yacc >= 0) return COMMA;}
"/"  {update_vars(NULL); if(flag) printf("DIV\n"); if(flag_yacc >= 0) return DIV;}
"==" {update_vars(NULL); if(flag) printf("EQ\n"); if(flag_yacc >= 0) return EQ;}
">=" {update_vars(NULL); if(flag) printf("GE\n"); if(flag_yacc >= 0) return GE;}
">"  {update_vars(NULL); if(flag) printf("GT\n"); if(flag_yacc >= 0) return GT;}
"{"  {update_vars(NULL); if(flag) printf("LBRACE\n"); if(flag_yacc >= 0) return LBRACE;}
"<=" {update_vars(NULL); if(flag) printf("LE\n"); if(flag_yacc >= 0) return LE;}
"("  {update_vars(NULL); if(flag) printf("LPAR\n"); if(flag_yacc >= 0) return LPAR;}
"["  {update_vars(NULL); if(flag) printf("LSQ\n"); if(flag_yacc >= 0) return LSQ;}
"<"  {update_vars(NULL); if(flag) printf("LT\n"); if(flag_yacc >= 0) return LT;}
"-"  {update_vars(NULL); if(flag) printf("MINUS\n"); if(flag_yacc >= 0) return MINUS;}
"%"  {update_vars(NULL); if(flag) printf("MOD\n"); if(flag_yacc >= 0) return MOD;}
"!=" {update_vars(NULL); if(flag) printf("NE\n"); if(flag_yacc >= 0) return NE;}
"!"  {update_vars(NULL); if(flag) printf("NOT\n"); if(flag_yacc >= 0) return NOT;}
"||" {update_vars(NULL); if(flag) printf("OR\n"); if(flag_yacc >= 0) return OR;}
"+"  {update_vars(NULL); if(flag) printf("PLUS\n"); if(flag_yacc >= 0) return PLUS;}
"}"  {update_vars(NULL); if(flag) printf("RBRACE\n"); if(flag_yacc >= 0) return RBRACE;}
")"  {update_vars(NULL); if(flag) printf("RPAR\n"); if(flag_yacc >= 0) return RPAR;}
"]"  {update_vars(NULL); if(flag) printf("RSQ\n"); if(flag_yacc >= 0) return RSQ;}
";"  {update_vars(NULL); if(flag) printf("SEMICOLON\n"); if(flag_yacc >= 0) return SEMICOLON;}
"->" {update_vars(NULL); if(flag) printf("ARROW\n"); if(flag_yacc >= 0) return ARROW;}
"<<" {update_vars(NULL); if(flag) printf("LSHIFT\n"); if(flag_yacc >= 0) return LSHIFT;}
">>" {update_vars(NULL); if(flag) printf("RSHIFT\n"); if(flag_yacc >= 0) return RSHIFT;}
"^"  {update_vars(NULL); if(flag) printf("XOR\n"); if(flag_yacc >= 0) return XOR;}
"true"|"false" {update_vars(yytext); if(flag) printf("BOOLLIT(%s)\n", yytext); if(flag_yacc >= 0) return BOOLLIT;}
"boolean" {update_vars(NULL); if(flag) printf("BOOL\n"); if(flag_yacc >= 0) return BOOL;}
"class"   {update_vars(NULL); if(flag) printf("CLASS\n"); if(flag_yacc >= 0) return CLASS;}
".length" {update_vars(NULL); if(flag) printf("DOTLENGTH\n"); if(flag_yacc >= 0) return DOTLENGTH;}
"double"  {update_vars(NULL); if(flag) printf("DOUBLE\n"); if(flag_yacc >= 0) return DOUBLE;}
"else"    {update_vars(NULL); if(flag) printf("ELSE\n"); if(flag_yacc >= 0) return ELSE;}
"if"      {update_vars(NULL); if(flag) printf("IF\n"); if(flag_yacc >= 0) return IF;}
"int"     {update_vars(NULL); if(flag) printf("INT\n"); if(flag_yacc >= 0) return INT;}
"System.out.print" {update_vars(NULL); if(flag) printf("PRINT\n"); if(flag_yacc >= 0) return PRINT;}
"Integer.parseInt" {update_vars(NULL); if(flag) printf("PARSEINT\n"); if(flag_yacc >= 0) return PARSEINT;}
"public" {update_vars(NULL); if(flag) printf("PUBLIC\n"); if(flag_yacc >= 0) return PUBLIC;}
"return" {update_vars(NULL); if(flag) printf("RETURN\n"); if(flag_yacc >= 0) return RETURN;}
"static" {update_vars(NULL); if(flag) printf("STATIC\n"); if(flag_yacc >= 0) return STATIC;}
"String" {update_vars(NULL); if(flag) printf("STRING\n"); if(flag_yacc >= 0) return STRING;}
"void"   {update_vars(NULL); if(flag) printf("VOID\n"); if(flag_yacc >= 0) return VOID;}
"while"  {update_vars(NULL); if(flag) printf("WHILE\n"); if(flag_yacc >= 0) return WHILE;}
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while"  {update_vars(yytext); if(flag) printf("RESERVED(%s)\n", yytext); if(flag_yacc >= 0) return RESERVED;}
{numnotzero}("_"*{num})* {update_vars(yytext); if(flag) printf("INTLIT(%s)\n", yytext); if(flag_yacc >= 0) return INTLIT;}
{num}("_"*{num})*(("e"|"E")("+"|"-"|""){num}("_"*{num})*) {update_vars(yytext); if(flag) printf("REALLIT(%s)\n", yytext); if(flag_yacc >= 0) return REALLIT;}
(("0"?"."{num}("_"*{num})*)|({num}("_"*{num})*("."({num}("_"*{num})*)?)))(("e"|"E")("+"|"-"|""){num}("_"*{num})*)? {update_vars(yytext); if(flag) printf("REALLIT(%s)\n", yytext); if(flag_yacc >= 0) return REALLIT;}
"0" {update_vars(yytext); if(flag) printf("INTLIT(%s)\n", yytext); if(flag_yacc >= 0) return INTLIT;}
{let}({let}|{num})* {update_vars(yytext); if(flag) printf("ID(%s)\n", yytext); if(flag_yacc >= 0) return ID;}
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
        }
        else if(strcmp(argv[1], "-t") == 0) {
            flag_yacc = 1;
            yyparse();
            if(!yacc_error){
                print_tree(root, 0);
            }
        }
        else if(strcmp(argv[1], "-s") == 0) {
            flag_yacc = 1;
            yyparse();
            if(!yacc_error){
                semantics_check();
                show_table();
                print_tree(root, 0);
            }
        }else{
            flag_yacc = 1;
            yyparse();
            if(!yacc_error){
                semantics_check();
            }
        }
    }
    else{
        flag_yacc = 1;
        yyparse();
        if(!yacc_error){
            semantics_check();

        }
    }
    //free_tables();
    //free_tree(root);
    return 0;
}

void update_vars(char *value){
	col_yacc = col; 
	line_yacc = line; 
	col += yyleng;
    if(flag_yacc >= 0) {
        //printf("adasdsada %s %d %d\n", yytext, line_yacc, col_yacc);
        yylval.tk = (Tk *) malloc(sizeof(Tk));
        yylval.tk->value = NULL;
        if (value)
            yylval.tk->value = strdup(value);
        yylval.tk->line = line_yacc;
        yylval.tk->col = col_yacc;
    }
}

int yywrap(){
    return 1;
}