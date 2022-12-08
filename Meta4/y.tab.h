/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    DOUBLE = 259,                  /* DOUBLE  */
    COMMA = 260,                   /* COMMA  */
    LBRACE = 261,                  /* LBRACE  */
    LPAR = 262,                    /* LPAR  */
    LSQ = 263,                     /* LSQ  */
    RBRACE = 264,                  /* RBRACE  */
    RPAR = 265,                    /* RPAR  */
    RSQ = 266,                     /* RSQ  */
    SEMICOLON = 267,               /* SEMICOLON  */
    ARROW = 268,                   /* ARROW  */
    CLASS = 269,                   /* CLASS  */
    DOTLENGTH = 270,               /* DOTLENGTH  */
    ELSE = 271,                    /* ELSE  */
    IF = 272,                      /* IF  */
    PRINT = 273,                   /* PRINT  */
    PARSEINT = 274,                /* PARSEINT  */
    PUBLIC = 275,                  /* PUBLIC  */
    RETURN = 276,                  /* RETURN  */
    STATIC = 277,                  /* STATIC  */
    STRING = 278,                  /* STRING  */
    VOID = 279,                    /* VOID  */
    STAR = 280,                    /* STAR  */
    DIV = 281,                     /* DIV  */
    MINUS = 282,                   /* MINUS  */
    MOD = 283,                     /* MOD  */
    PLUS = 284,                    /* PLUS  */
    LSHIFT = 285,                  /* LSHIFT  */
    RSHIFT = 286,                  /* RSHIFT  */
    ASSIGN = 287,                  /* ASSIGN  */
    NOT = 288,                     /* NOT  */
    AND = 289,                     /* AND  */
    OR = 290,                      /* OR  */
    XOR = 291,                     /* XOR  */
    EQ = 292,                      /* EQ  */
    GE = 293,                      /* GE  */
    GT = 294,                      /* GT  */
    LE = 295,                      /* LE  */
    LT = 296,                      /* LT  */
    NE = 297,                      /* NE  */
    BOOL = 298,                    /* BOOL  */
    WHILE = 299,                   /* WHILE  */
    RESERVED = 300,                /* RESERVED  */
    STRLIT = 301,                  /* STRLIT  */
    BOOLLIT = 302,                 /* BOOLLIT  */
    INTLIT = 303,                  /* INTLIT  */
    REALLIT = 304,                 /* REALLIT  */
    ID = 305,                      /* ID  */
    UNARY = 306                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT 258
#define DOUBLE 259
#define COMMA 260
#define LBRACE 261
#define LPAR 262
#define LSQ 263
#define RBRACE 264
#define RPAR 265
#define RSQ 266
#define SEMICOLON 267
#define ARROW 268
#define CLASS 269
#define DOTLENGTH 270
#define ELSE 271
#define IF 272
#define PRINT 273
#define PARSEINT 274
#define PUBLIC 275
#define RETURN 276
#define STATIC 277
#define STRING 278
#define VOID 279
#define STAR 280
#define DIV 281
#define MINUS 282
#define MOD 283
#define PLUS 284
#define LSHIFT 285
#define RSHIFT 286
#define ASSIGN 287
#define NOT 288
#define AND 289
#define OR 290
#define XOR 291
#define EQ 292
#define GE 293
#define GT 294
#define LE 295
#define LT 296
#define NE 297
#define BOOL 298
#define WHILE 299
#define RESERVED 300
#define STRLIT 301
#define BOOLLIT 302
#define INTLIT 303
#define REALLIT 304
#define ID 305
#define UNARY 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "jucompiler.y"
Node* node; Tk* tk;

#line 172 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
