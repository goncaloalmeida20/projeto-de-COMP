%{
    #include <stdio.h>
    #include <stdlib.h>

    int line = 1;
    int line_temp = 1;
    int col = 1;
    const char* valid_esc = "ntrf\\";

    void invalid_escape_sequences(const char* string, int leng, int unterminated_string);
%}
num [0-9]
numnotzero [1-9]
let [$_a-zA-Z]
escape_chars [\\\"ntrf]
invalid_escape [^\\\"ntrf]
%X MLCOMMENT
%%
"\n" {line++; col = 1;}
"//".* {;}
"/*" {line_temp = line; BEGIN (MLCOMMENT);}
<MLCOMMENT>"*/" {line = line_temp; BEGIN (0);}
<MLCOMMENT>"\n" {line_temp++; col = 1;}
<MLCOMMENT><<EOF>> {printf("Line %d, col %d: unterminated comment\n", line, col); BEGIN (0);}
<MLCOMMENT>. {;}
"\""[^\"\n]*("\\"{escape_chars})+[^\"\n]*"\"" {yytext[yyleng-1] = 0; printf("STRLIT(\"%s\")\n", &yytext[1]); col += yyleng;}
"\""[^\"\n]*("\\"{invalid_escape}?)[^\"\n]*("\"") {invalid_escape_sequences(yytext, yyleng, 0);}
"\""[^\"\n]*("\\"{invalid_escape}?)[^\"\n]*("\n")?  {invalid_escape_sequences(yytext, yyleng, 1);}
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
"true"|"false" {printf("BOOLLIT(%s)\n", yytext); col += yyleng;}
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
"Integer"|"null"|"System"|"--"|"++"|"abstract"|"continue"|"for"|"new"|"switch"|"assert"|"default"|"if"|"package"|"synchronized"|"boolean"|"do"|"goto"|"private"|"this"|"break"|"double"|"implements"|"protected"|"throw"|"byte"|"else"|"import"|"public"|"throws"|"case"|"enum"|"instanceof"|"return"|"transient"|"catch"|"extends"|"int"|"short"|"try"|"char"|"final"|"interface"|"static"|"void"|"class"|"finally"|"long"|"strictfp"|"volatile"|"const"|"float"|"native"|"super"|"while"|"_" {printf("RESERVED(%s)\n", yytext); col += yyleng;}
"0"|({numnotzero}("_"*{num})*) {printf("INTLIT(%s)\n", yytext); col += yyleng;}
"0."|("0"?"."{num}("_"*{num})*)|({numnotzero}("_"*{num})*("."({num}("_"*{num})*)?)?)(("e"|"E")("+"|"-"|"")("0."|("0"?"."{num}("_"*{num})*)|({numnotzero}("_"*{num})*("."({num}("_"*{num})*)?)?)))? {printf("REALLIT(%s)\n", yytext); col += yyleng;}
{let}({let}|{num})* {printf("ID(%s)\n", yytext); col += yyleng;}
" " {col += yyleng;}
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

void invalid_escape_sequences(const char* string, int leng, int unterminated_string){
    int col_temp = col;
    
    for(int i = 0; i < leng; i++, col_temp++){
        if(string[i] == '\\' && i < leng-1 && is_invalid_esc(string[i+1])){
            if(string[i+1] == '\n')
                printf("Line %d, col %d: invalid escape sequence (\\)\n", line, col_temp++);
            else
                printf("Line %d, col %d: invalid escape sequence (\\%c)\n", line, col_temp++, string[i+1]);
            i++;
        }
    
        
    }
    if(unterminated_string){
        printf("Line %d, col %d: unterminated string literal\n", line, col); 
        line++;
        col = 1;
    }else col += leng;
}
