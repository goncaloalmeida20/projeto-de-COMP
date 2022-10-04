%{
    #include <stdio.h>
    #include <stdlib.h>

    int line = 1;
    int col = 1;
    const char* valid_esc = "ntrf\\";

    void invalid_escape_sequences(const char* string, int leng);
%}
num [0-9]
let [$_a-zA-Z]
ignore [ \t\r\f]
invalid_escape [^\\\n\t\r\fntrf]
%X MLCOMMENT
%%
"\n" {line++; col = 1;}
"//".* {;}
"/*" {BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {BEGIN (0);}
<MLCOMMENT>"\n" {line++; col = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {;}
"\""[^\"\n]*("\\"{invalid_escape})[^\"\n]*("\"") {invalid_escape_sequences(yytext, yyleng); col += yyleng;}
"\""[^\"\n]*("\n")? {printf("Line %d, col %d: unterminated string literal\n", line, col); line++; col = 1;}
"\""[^\"\n]*"\"" {yytext[yyleng-1] = 0; printf("STRLIT(\"%s\")\n", &yytext[1]); col += yyleng;}
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
{let}({let}|{num})* {printf("ID(%s)\n", yytext); col += yyleng;}
{ignore} {col += yyleng;}
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

int is_invalid_esc(const char c){
    for(int i = 0; valid_esc[i] != 0; i++){
        if(c == valid_esc[i]) return 0;
    }
    return 1;
}

void invalid_escape_sequences(const char* string, int leng){
    int col_temp = col;
    for(int i = 0; i < leng; i++, col_temp++){
        if(string[i] == '\\' && i < leng && is_invalid_esc(string[i+1])){
            printf("Line %d, col %d: invalid escape sequence (\\%c)\n", line, col_temp++, string[i+1]);
            i++;
        }
    }
}
