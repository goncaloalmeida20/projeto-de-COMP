num [0-9]
let [a-zA-Z]
%X STRING
%%
"\"" {printf("STRLIT\n"); BEGIN (STRING);}
<STRING> "\\f" {printf("STRLIT\n");}
<STRING> "\\n" {printf("STRLIT\n");}
<STRING> "\\r" {printf("STRLIT\n");}
<STRING> "\\t" {printf("STRLIT\n");}
<STRING> "\\" {printf("STRLIT\n");}
<STRING> "\"" {printf("STRLIT\n"); BEGIN (0);}
"true"|"false" {printf("BOOLLIT\n");}
"&&" {printf("AND\n");}
"=" {printf("ASSIGN\n");}
"*" {printf("STAR\n");}
"," {printf("COMMA\n");}
"/" {printf("DIV\n");}
"==" {printf("EQ\n");}
">=" {printf("GE\n");}
">" {printf("GT\n");}
"{" {printf("LBRACE\n");}
"<=" {printf("LE\n");}
"(" {printf("LPAR\n");}
"[" {printf("LSQ\n");}
"<" {printf("LT\n");}
"-" {printf("MINUS\n");}
"%" {printf("MOD\n");}
"!=" {printf("NE\n");}
"!" {printf("NOT\n");}
"||" {printf("OR\n");}
"+" {printf("PLUS\n");}
"}" {printf("RBRACE\n");}
")" {printf("RPAR\n");}
"]" {printf("RSQ\n");}
";" {printf("SEMICOLON\n");}
"->" {printf("ARROW\n");}
"<<" {printf("LSHIFT\n");}
">>" {printf("RSHIFT\n");}
"^" {printf("XOR\n");}
"boolean" {printf("BOOL\n");}
"class" {printf("CLASS\n");}
".length" {printf("DOTLENGTH\n");}
"double" {printf("DOUBLE\n");}
"else" {printf("ELSE\n");}
"if" {printf("IF\n");}
"int" {printf("INT\n");}
"System.out.print" {printf("PRINT\n");}
"Integer.parseInt" {printf("PARSEINT\n");}
"public" {printf("PUBLIC\n");}
"return" {printf("RETURN\n");}
"static" {printf("STATIC\n");}
"String" {printf("STRING\n");}
"void" {printf("VOID\n");}
"while" {printf("WHILE\n");}
"++" {printf("RESERVED\n");}
"--" {printf("RESERVED\n");}
"null" {printf("RESERVED\n");}
"Integer" {printf("RESERVED\n");}
"System" {printf("RESERVED\n");}
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
