/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "jucompiler.y"

    /*
        Autores:
            Gonçalo Fernandes Diogo de Almeida, nº2020218868
            João Bernardo de Jesus Santos, nº2020218995
    */
    
    #include <stdio.h>
    #include <string.h>
    #include "tree.h"

    #define MAX_TK 6

    extern int yylex(void);
    extern void yyerror(char*);
    extern char* yytext;

    void free_tk(Tk *tk1, Tk *tk2, Tk *tk3, Tk *tk4, Tk *tk5, Tk *tk6);

    int yacc_error = 0;
    
    char current_type[TYPE_SIZE];
    char current_true_type[TYPE_SIZE];

    int line_yacc = 1, col_yacc = 1;
    int flag_yacc = 0;


#line 100 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 258 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_DOUBLE = 4,                     /* DOUBLE  */
  YYSYMBOL_COMMA = 5,                      /* COMMA  */
  YYSYMBOL_LBRACE = 6,                     /* LBRACE  */
  YYSYMBOL_LPAR = 7,                       /* LPAR  */
  YYSYMBOL_LSQ = 8,                        /* LSQ  */
  YYSYMBOL_RBRACE = 9,                     /* RBRACE  */
  YYSYMBOL_RPAR = 10,                      /* RPAR  */
  YYSYMBOL_RSQ = 11,                       /* RSQ  */
  YYSYMBOL_SEMICOLON = 12,                 /* SEMICOLON  */
  YYSYMBOL_ARROW = 13,                     /* ARROW  */
  YYSYMBOL_CLASS = 14,                     /* CLASS  */
  YYSYMBOL_DOTLENGTH = 15,                 /* DOTLENGTH  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_PRINT = 18,                     /* PRINT  */
  YYSYMBOL_PARSEINT = 19,                  /* PARSEINT  */
  YYSYMBOL_PUBLIC = 20,                    /* PUBLIC  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_STATIC = 22,                    /* STATIC  */
  YYSYMBOL_STRING = 23,                    /* STRING  */
  YYSYMBOL_VOID = 24,                      /* VOID  */
  YYSYMBOL_STAR = 25,                      /* STAR  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_MINUS = 27,                     /* MINUS  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_LSHIFT = 30,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 31,                    /* RSHIFT  */
  YYSYMBOL_ASSIGN = 32,                    /* ASSIGN  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_XOR = 36,                       /* XOR  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_GE = 38,                        /* GE  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_LE = 40,                        /* LE  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_NE = 42,                        /* NE  */
  YYSYMBOL_BOOL = 43,                      /* BOOL  */
  YYSYMBOL_WHILE = 44,                     /* WHILE  */
  YYSYMBOL_RESERVED = 45,                  /* RESERVED  */
  YYSYMBOL_STRLIT = 46,                    /* STRLIT  */
  YYSYMBOL_BOOLLIT = 47,                   /* BOOLLIT  */
  YYSYMBOL_INTLIT = 48,                    /* INTLIT  */
  YYSYMBOL_REALLIT = 49,                   /* REALLIT  */
  YYSYMBOL_ID = 50,                        /* ID  */
  YYSYMBOL_UNARY = 51,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_Program = 53,                   /* Program  */
  YYSYMBOL_MethodFieldDecl = 54,           /* MethodFieldDecl  */
  YYSYMBOL_MethodDecl = 55,                /* MethodDecl  */
  YYSYMBOL_FieldDecl = 56,                 /* FieldDecl  */
  YYSYMBOL_FieldCommaId = 57,              /* FieldCommaId  */
  YYSYMBOL_Type = 58,                      /* Type  */
  YYSYMBOL_MethodHeader = 59,              /* MethodHeader  */
  YYSYMBOL_FormalParams = 60,              /* FormalParams  */
  YYSYMBOL_CommaTypeIds = 61,              /* CommaTypeIds  */
  YYSYMBOL_MethodBody = 62,                /* MethodBody  */
  YYSYMBOL_StatementVarDecl = 63,          /* StatementVarDecl  */
  YYSYMBOL_VarDecl = 64,                   /* VarDecl  */
  YYSYMBOL_VarCommaId = 65,                /* VarCommaId  */
  YYSYMBOL_Statement = 66,                 /* Statement  */
  YYSYMBOL_MultipleStatements = 67,        /* MultipleStatements  */
  YYSYMBOL_MethodInvocation = 68,          /* MethodInvocation  */
  YYSYMBOL_CommaExpr = 69,                 /* CommaExpr  */
  YYSYMBOL_Assignment = 70,                /* Assignment  */
  YYSYMBOL_ParseArgs = 71,                 /* ParseArgs  */
  YYSYMBOL_Expr = 72,                      /* Expr  */
  YYSYMBOL_ExprNoAssign = 73               /* ExprNoAssign  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   441

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    49,    49,    50,    51,    52,    55,    56,    57,    58,
      59,    60,    63,    65,    66,    67,    70,    71,    74,    75,
      76,    79,    80,    81,    82,    85,    86,    87,    90,    91,
      94,    95,    98,    99,   100,   101,   104,   105,   108,   109,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   130,   131,   134,   135,   136,
     137,   140,   141,   144,   146,   147,   150,   151,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "DOUBLE",
  "COMMA", "LBRACE", "LPAR", "LSQ", "RBRACE", "RPAR", "RSQ", "SEMICOLON",
  "ARROW", "CLASS", "DOTLENGTH", "ELSE", "IF", "PRINT", "PARSEINT",
  "PUBLIC", "RETURN", "STATIC", "STRING", "VOID", "STAR", "DIV", "MINUS",
  "MOD", "PLUS", "LSHIFT", "RSHIFT", "ASSIGN", "NOT", "AND", "OR", "XOR",
  "EQ", "GE", "GT", "LE", "LT", "NE", "BOOL", "WHILE", "RESERVED",
  "STRLIT", "BOOLLIT", "INTLIT", "REALLIT", "ID", "UNARY", "$accept",
  "Program", "MethodFieldDecl", "MethodDecl", "FieldDecl", "FieldCommaId",
  "Type", "MethodHeader", "FormalParams", "CommaTypeIds", "MethodBody",
  "StatementVarDecl", "VarDecl", "VarCommaId", "Statement",
  "MultipleStatements", "MethodInvocation", "CommaExpr", "Assignment",
  "ParseArgs", "Expr", "ExprNoAssign", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-57)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -11,   -32,    29,    44,   -40,   122,    23,    16,   181,    38,
      57,   188,   193,   -40,   -40,   -40,   105,    62,   -40,   -40,
     -40,   -40,    24,   -40,    35,    98,   -40,    72,    66,   148,
     -40,   107,    68,   135,   -40,   108,   110,    63,   -40,   -40,
     119,   125,   137,   257,   152,    17,   106,   163,   167,   203,
     168,   169,   171,   -40,   179,   145,   186,   194,   -40,   204,
     -40,   -40,   -40,   217,   291,   266,     8,   114,   -40,   302,
     302,   302,   -40,   -40,   -40,    33,   -40,   -40,   -40,   191,
     328,   291,     4,   291,     1,   -40,   -40,   -40,   -40,   -40,
     -40,   205,   214,   -40,   -40,   -40,   -40,   231,   216,   218,
     220,   221,   223,   219,   229,   232,    52,   -40,   -40,   -40,
     -40,   -40,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   234,   235,
     -40,     2,   -40,   201,   -40,   243,   206,    73,   -40,   -40,
     -40,   253,   245,   246,   -40,   291,   -40,   -40,   -40,   -40,
     149,   -40,   149,   389,   389,   364,   346,   382,   400,   317,
     317,   317,   317,   400,   253,   -40,   291,   -40,   250,   236,
     -40,   -40,   212,   247,   -40,   -40,   255,   -40,   263,   -40,
     -40,   214,   253,   267,   -40,   -40,   -40,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     4,    11,     0,     0,     9,    10,
      19,    20,     0,    18,     0,     0,     5,     0,     0,     0,
      12,     0,     0,     0,    13,     0,     0,     0,    30,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,     0,    16,    21,     0,
      14,    54,    40,     0,     0,     0,     0,     0,    46,     0,
       0,     0,    94,    92,    93,    91,    88,    67,    89,     0,
      66,     0,     0,     0,     0,    31,    35,    34,    49,    50,
      51,     0,    25,    24,    17,    22,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    84,    86,    85,
      90,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,    63,     0,    36,     0,     0,     0,    26,    55,
      42,     0,     0,     0,    65,     0,    95,    87,    70,    71,
      69,    72,    68,    76,    77,    73,    74,    75,    78,    79,
      80,    81,    82,    83,     0,    60,     0,    58,     0,    38,
      37,    27,     0,    43,    52,    53,     0,    45,    61,    59,
      39,    28,     0,     0,    62,    29,    44,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -40,   -40,    75,   -40,   -40,   222,    -1,   -40,   249,    97,
     -40,    76,   -40,   111,   -36,   190,   -29,   113,   -39,   -27,
     -26,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    10,    11,    12,    35,    46,    25,    56,   138,
      30,    47,    48,   135,    49,    98,    76,   168,    51,    78,
      79,    80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    63,    52,     1,    77,   129,   133,   166,    50,   102,
      52,    67,   167,   134,   130,    24,    -2,    14,     3,    50,
      50,    52,    52,    42,    82,    77,    77,    97,    77,     4,
      55,    69,    55,    70,    50,    13,    52,    71,    99,   101,
      82,   105,    77,    77,    77,   107,   108,   109,   110,    83,
       5,    72,    73,    74,    75,   128,   131,   132,   103,    82,
      16,    97,    -3,    26,    36,    83,    17,   110,    50,    37,
      52,    32,    62,    33,    27,    39,    20,    21,    34,    31,
      40,    41,    42,    15,    43,    28,    18,    19,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    29,   173,    77,    44,    20,    21,
      20,    21,    50,    45,    52,   104,    23,    53,    57,   176,
      60,    67,    61,     6,    86,    87,    64,    77,   177,    22,
      54,     7,    65,    42,     8,    50,   172,    52,    20,    21,
     178,    69,     9,    70,    66,    58,   186,    71,    23,    36,
      23,    20,    21,    50,    37,    52,    84,    38,    54,    81,
      39,    72,    73,    74,    75,    40,    41,    42,    36,    43,
      20,    21,    85,    37,   112,   113,   -33,   115,    23,    39,
      88,    89,     6,    90,    40,    41,    42,    91,    43,     6,
      -8,    23,    44,     8,     6,    92,    93,    -6,    45,    32,
       8,     9,    -7,   111,    36,     8,    20,    21,     9,    37,
      23,    44,   -32,     9,    95,    39,   136,    45,    36,   137,
      40,    41,    42,    37,    43,   140,    96,   145,   141,    39,
     142,   143,    36,   144,    40,    41,    42,    37,    43,   146,
     -56,   133,   147,    39,   164,   165,    23,    44,    40,    41,
      42,   169,    43,    45,    36,   170,   171,   174,   175,    37,
     179,    44,   181,   182,    67,    39,   183,    45,   166,    68,
      40,    41,    42,    67,    43,    44,    42,   187,   185,    94,
     180,    45,    59,     0,    69,    42,    70,   139,     0,     0,
      71,   184,     0,    69,     0,    70,     0,    44,    67,    71,
       0,     0,     0,    45,    72,    73,    74,    75,     0,    67,
      42,     0,   100,    72,    73,    74,    75,     0,    69,     0,
      70,    42,     0,     0,    71,     0,     0,     0,     0,    69,
       0,    70,     0,     0,     0,    71,     0,     0,    72,    73,
      74,    75,   112,   113,   114,   115,   116,   117,   118,    72,
      73,    74,   106,   112,   113,   114,   115,   116,   117,   118,
       0,     0,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   112,   113,   114,   115,   116,   117,   118,     0,     0,
     119,     0,   121,   122,   123,   124,   125,   126,   127,   112,
     113,   114,   115,   116,   117,   118,     0,     0,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   112,   113,   114,
     115,   116,   117,   118,   112,   113,   114,   115,   116,   122,
     123,   124,   125,   126,   127,   112,   113,   114,   115,   116,
     117,   118,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126
};

static const yytype_int16 yycheck[] =
{
      29,    37,    29,    14,    43,     1,     5,     5,    37,     1,
      37,     7,    10,    12,    10,    16,     0,     1,    50,    48,
      49,    48,    49,    19,     7,    64,    65,    63,    67,     0,
      31,    27,    33,    29,    63,    12,    63,    33,    64,    65,
       7,    67,    81,    82,    83,    69,    70,    71,    15,    32,
       6,    47,    48,    49,    50,    81,    82,    83,    50,     7,
      22,    97,     0,     1,     1,    32,     9,    15,    97,     6,
      97,     5,     9,     7,    50,    12,     3,     4,    12,     7,
      17,    18,    19,     8,    21,    50,    11,    12,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     6,   141,   145,    44,     3,     4,
       3,     4,   141,    50,   141,     1,    43,    10,    50,   145,
      12,     7,    12,     1,    48,    49,     7,   166,   164,    24,
      23,     9,     7,    19,    12,   164,   137,   164,     3,     4,
     166,    27,    20,    29,     7,    10,   182,    33,    43,     1,
      43,     3,     4,   182,     6,   182,    50,     9,    23,     7,
      12,    47,    48,    49,    50,    17,    18,    19,     1,    21,
       3,     4,     9,     6,    25,    26,     9,    28,    43,    12,
      12,    12,     1,    12,    17,    18,    19,     8,    21,     1,
       9,    43,    44,    12,     1,    50,    10,     9,    50,     5,
      12,    20,     9,    12,     1,    12,     3,     4,    20,     6,
      43,    44,     9,    20,    10,    12,    11,    50,     1,     5,
      17,    18,    19,     6,    21,     9,     9,     8,    10,    12,
      10,    10,     1,    10,    17,    18,    19,     6,    21,    10,
       9,     5,    10,    12,    10,    10,    43,    44,    17,    18,
      19,    50,    21,    50,     1,    12,    50,    12,    12,     6,
      10,    44,    50,    16,     7,    12,    11,    50,     5,    12,
      17,    18,    19,     7,    21,    44,    19,    10,   181,    57,
     169,    50,    33,    -1,    27,    19,    29,    97,    -1,    -1,
      33,   178,    -1,    27,    -1,    29,    -1,    44,     7,    33,
      -1,    -1,    -1,    50,    47,    48,    49,    50,    -1,     7,
      19,    -1,    46,    47,    48,    49,    50,    -1,    27,    -1,
      29,    19,    -1,    -1,    33,    -1,    -1,    -1,    -1,    27,
      -1,    29,    -1,    -1,    -1,    33,    -1,    -1,    47,    48,
      49,    50,    25,    26,    27,    28,    29,    30,    31,    47,
      48,    49,    50,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      34,    -1,    36,    37,    38,    39,    40,    41,    42,    25,
      26,    27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,
      36,    37,    38,    39,    40,    41,    42,    25,    26,    27,
      28,    29,    30,    31,    25,    26,    27,    28,    29,    37,
      38,    39,    40,    41,    42,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    14,    53,    50,     0,     6,     1,     9,    12,    20,
      54,    55,    56,    12,     1,    54,    22,     9,    54,    54,
       3,     4,    24,    43,    58,    59,     1,    50,    50,     6,
      62,     7,     5,     7,    12,    57,     1,     6,     9,    12,
      17,    18,    19,    21,    44,    50,    58,    63,    64,    66,
      68,    70,    71,    10,    23,    58,    60,    50,    10,    60,
      12,    12,     9,    66,     7,     7,     7,     7,    12,    27,
      29,    33,    47,    48,    49,    50,    68,    70,    71,    72,
      73,     7,     7,    32,    50,     9,    63,    63,    12,    12,
      12,     8,    50,    10,    57,    10,     9,    66,    67,    72,
      46,    72,     1,    50,     1,    72,    50,    73,    73,    73,
      15,    12,    25,    26,    27,    28,    29,    30,    31,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    72,     1,
      10,    72,    72,     5,    12,    65,    11,     5,    61,    67,
       9,    10,    10,    10,    10,     8,    10,    10,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    10,    10,     5,    10,    69,    50,
      12,    50,    58,    66,    12,    12,    72,    66,    72,    10,
      65,    50,    16,    11,    69,    61,    66,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    55,    56,    56,    56,    57,    57,    58,    58,
      58,    59,    59,    59,    59,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    68,
      68,    69,    69,    70,    71,    71,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     5,     5,     6,     1,     1,     1,     2,
       2,     2,     4,     5,     6,     2,     2,     3,     1,     1,
       1,     4,     5,     4,     5,     2,     3,     4,     3,     4,
       2,     3,     1,     1,     2,     2,     3,     4,     2,     3,
       2,     3,     4,     5,     7,     5,     2,     3,     1,     2,
       2,     2,     5,     5,     2,     2,     1,     3,     4,     5,
       4,     2,     3,     3,     7,     4,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     3,     1,     1,
       2,     1,     1,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: CLASS ID LBRACE RBRACE  */
#line 49 "jucompiler.y"
                                                    {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, create_node("Id",(yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL)); free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1484 "y.tab.c"
    break;

  case 3: /* Program: CLASS ID LBRACE MethodFieldDecl RBRACE  */
#line 50 "jucompiler.y"
                                                    {root = create_node("Program", NULL, 0, 0, NULL); add_son(root, add_bro(create_node("Id",(yyvsp[-3].tk)->value, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, NULL), (yyvsp[-1].node))); free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1490 "y.tab.c"
    break;

  case 4: /* Program: CLASS ID LBRACE RBRACE error  */
#line 51 "jucompiler.y"
                                                    {yacc_error = 1; free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[-1].tk), NULL, NULL);}
#line 1496 "y.tab.c"
    break;

  case 5: /* Program: CLASS ID LBRACE MethodFieldDecl RBRACE error  */
#line 52 "jucompiler.y"
                                                    {yacc_error = 1; free_tk((yyvsp[-5].tk), (yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), NULL, NULL);}
#line 1502 "y.tab.c"
    break;

  case 6: /* MethodFieldDecl: MethodDecl  */
#line 55 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1508 "y.tab.c"
    break;

  case 7: /* MethodFieldDecl: FieldDecl  */
#line 56 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1514 "y.tab.c"
    break;

  case 8: /* MethodFieldDecl: SEMICOLON  */
#line 57 "jucompiler.y"
                                                    {(yyval.node)=NULL; free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1520 "y.tab.c"
    break;

  case 9: /* MethodFieldDecl: MethodDecl MethodFieldDecl  */
#line 58 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node),(yyvsp[0].node));}
#line 1526 "y.tab.c"
    break;

  case 10: /* MethodFieldDecl: FieldDecl MethodFieldDecl  */
#line 59 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node),(yyvsp[0].node));}
#line 1532 "y.tab.c"
    break;

  case 11: /* MethodFieldDecl: SEMICOLON MethodFieldDecl  */
#line 60 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node); free_tk((yyvsp[-1].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1538 "y.tab.c"
    break;

  case 12: /* MethodDecl: PUBLIC STATIC MethodHeader MethodBody  */
#line 63 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodDecl", NULL, 0, 0, NULL), add_bro((yyvsp[-1].node), (yyvsp[0].node))); free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), NULL, NULL, NULL, NULL);}
#line 1544 "y.tab.c"
    break;

  case 13: /* FieldDecl: PUBLIC STATIC Type ID SEMICOLON  */
#line 65 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro((yyvsp[-2].node), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL)));free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1550 "y.tab.c"
    break;

  case 14: /* FieldDecl: PUBLIC STATIC Type ID FieldCommaId SEMICOLON  */
#line 66 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro((yyvsp[-3].node), create_node("Id", (yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL))), (yyvsp[-1].node));free_tk((yyvsp[-5].tk), (yyvsp[-4].tk), NULL, (yyvsp[-2].tk), NULL, (yyvsp[0].tk));}
#line 1556 "y.tab.c"
    break;

  case 15: /* FieldDecl: error SEMICOLON  */
#line 67 "jucompiler.y"
                                                    {yacc_error = 1; (yyval.node)=NULL;}
#line 1562 "y.tab.c"
    break;

  case 16: /* FieldCommaId: COMMA ID  */
#line 70 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, current_true_type), create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL)));free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1568 "y.tab.c"
    break;

  case 17: /* FieldCommaId: COMMA ID FieldCommaId  */
#line 71 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("FieldDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, current_true_type), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL))), (yyvsp[0].node));free_tk((yyvsp[-2].tk), (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1574 "y.tab.c"
    break;

  case 18: /* Type: BOOL  */
#line 74 "jucompiler.y"
                                                    {(yyval.node)=create_node("Bool", NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "boolean"); strcpy(current_type, "Bool"); strcpy(current_true_type, "boolean");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1580 "y.tab.c"
    break;

  case 19: /* Type: INT  */
#line 75 "jucompiler.y"
                                                    {(yyval.node)=create_node("Int", NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "int"); strcpy(current_type, "Int"); strcpy(current_true_type, "int");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1586 "y.tab.c"
    break;

  case 20: /* Type: DOUBLE  */
#line 76 "jucompiler.y"
                                                    {(yyval.node)=create_node("Double", NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "double"); strcpy(current_type, "Double"); strcpy(current_true_type, "double");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1592 "y.tab.c"
    break;

  case 21: /* MethodHeader: Type ID LPAR RPAR  */
#line 79 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro((yyvsp[-3].node), add_bro(create_node("Id",(yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));free_tk(NULL, (yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1598 "y.tab.c"
    break;

  case 22: /* MethodHeader: Type ID LPAR FormalParams RPAR  */
#line 80 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro((yyvsp[-4].node), add_bro(create_node("Id",(yyvsp[-3].tk)->value, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),(yyvsp[-1].node)))));free_tk(NULL, (yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1604 "y.tab.c"
    break;

  case 23: /* MethodHeader: VOID ID LPAR RPAR  */
#line 81 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, "void"), add_bro(create_node("Id",(yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL), create_node("MethodParams", NULL, 0, 0, NULL))));free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1610 "y.tab.c"
    break;

  case 24: /* MethodHeader: VOID ID LPAR FormalParams RPAR  */
#line 82 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodHeader", NULL, 0, 0, NULL), add_bro(create_node("Void", NULL, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, "void"), add_bro(create_node("Id",(yyvsp[-3].tk)->value, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, NULL), add_son(create_node("MethodParams", NULL, 0, 0, NULL),(yyvsp[-1].node)))));free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1616 "y.tab.c"
    break;

  case 25: /* FormalParams: Type ID  */
#line 85 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro((yyvsp[-1].node), create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL)));free_tk(NULL, (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1622 "y.tab.c"
    break;

  case 26: /* FormalParams: Type ID CommaTypeIds  */
#line 86 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro((yyvsp[-2].node), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL))),(yyvsp[0].node));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1628 "y.tab.c"
    break;

  case 27: /* FormalParams: STRING LSQ RSQ ID  */
#line 87 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro(create_node("StringArray", NULL, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, "String[]"), create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL)));free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL);}
#line 1634 "y.tab.c"
    break;

  case 28: /* CommaTypeIds: COMMA Type ID  */
#line 90 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro((yyvsp[-1].node), create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL)));free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1640 "y.tab.c"
    break;

  case 29: /* CommaTypeIds: COMMA Type ID CommaTypeIds  */
#line 91 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("ParamDecl", NULL, 0, 0, NULL), add_bro((yyvsp[-2].node), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL))),(yyvsp[0].node));free_tk((yyvsp[-3].tk), (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1646 "y.tab.c"
    break;

  case 30: /* MethodBody: LBRACE RBRACE  */
#line 94 "jucompiler.y"
                                                    {(yyval.node)=create_node("MethodBody", NULL, 0, 0, NULL);free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1652 "y.tab.c"
    break;

  case 31: /* MethodBody: LBRACE StatementVarDecl RBRACE  */
#line 95 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("MethodBody", NULL, 0, 0, NULL), (yyvsp[-1].node));free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1658 "y.tab.c"
    break;

  case 32: /* StatementVarDecl: Statement  */
#line 98 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1664 "y.tab.c"
    break;

  case 33: /* StatementVarDecl: VarDecl  */
#line 99 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1670 "y.tab.c"
    break;

  case 34: /* StatementVarDecl: Statement StatementVarDecl  */
#line 100 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node),(yyvsp[0].node));}
#line 1676 "y.tab.c"
    break;

  case 35: /* StatementVarDecl: VarDecl StatementVarDecl  */
#line 101 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node),(yyvsp[0].node));}
#line 1682 "y.tab.c"
    break;

  case 36: /* VarDecl: Type ID SEMICOLON  */
#line 104 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro((yyvsp[-2].node), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL)));free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1688 "y.tab.c"
    break;

  case 37: /* VarDecl: Type ID VarCommaId SEMICOLON  */
#line 105 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro((yyvsp[-3].node), create_node("Id", (yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL))), (yyvsp[-1].node));free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1694 "y.tab.c"
    break;

  case 38: /* VarCommaId: COMMA ID  */
#line 108 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, current_true_type), create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL)));free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1700 "y.tab.c"
    break;

  case 39: /* VarCommaId: COMMA ID VarCommaId  */
#line 109 "jucompiler.y"
                                                    {(yyval.node)=add_bro(add_son(create_node("VarDecl",NULL, 0, 0, NULL), add_bro(create_node(current_type, NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, current_true_type), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL))), (yyvsp[0].node));free_tk((yyvsp[-2].tk), (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1706 "y.tab.c"
    break;

  case 40: /* Statement: LBRACE RBRACE  */
#line 113 "jucompiler.y"
                                                    {(yyval.node)=NULL;free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1712 "y.tab.c"
    break;

  case 41: /* Statement: LBRACE Statement RBRACE  */
#line 114 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[-1].node);free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1718 "y.tab.c"
    break;

  case 42: /* Statement: LBRACE Statement MultipleStatements RBRACE  */
#line 115 "jucompiler.y"
                                                    {(yyval.node)=create_blocks((yyvsp[-2].node),(yyvsp[-1].node));free_tk((yyvsp[-3].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1724 "y.tab.c"
    break;

  case 43: /* Statement: IF LPAR Expr RPAR Statement  */
#line 116 "jucompiler.y"
                                                    {(yyval.node)=add_if((yyvsp[-2].node), (yyvsp[0].node), NULL, (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col);free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), NULL, NULL, NULL);}
#line 1730 "y.tab.c"
    break;

  case 44: /* Statement: IF LPAR Expr RPAR Statement ELSE Statement  */
#line 117 "jucompiler.y"
                                                    {(yyval.node)=add_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-6].tk)->line, (yyvsp[-6].tk)->col);free_tk((yyvsp[-6].tk), (yyvsp[-5].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), NULL, NULL);}
#line 1736 "y.tab.c"
    break;

  case 45: /* Statement: WHILE LPAR Expr RPAR Statement  */
#line 118 "jucompiler.y"
                                                    {(yyval.node)=add_while((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col);free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), NULL, NULL, NULL);}
#line 1742 "y.tab.c"
    break;

  case 46: /* Statement: RETURN SEMICOLON  */
#line 119 "jucompiler.y"
                                                    {(yyval.node)=create_node("Return", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "return");free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1748 "y.tab.c"
    break;

  case 47: /* Statement: RETURN Expr SEMICOLON  */
#line 120 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Return", NULL, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, "return"), (yyvsp[-1].node));free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1754 "y.tab.c"
    break;

  case 48: /* Statement: SEMICOLON  */
#line 121 "jucompiler.y"
                                                    {(yyval.node)=NULL;free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1760 "y.tab.c"
    break;

  case 49: /* Statement: MethodInvocation SEMICOLON  */
#line 122 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Call", NULL, (yyvsp[-1].node)->line, (yyvsp[-1].node)->col, NULL), (yyvsp[-1].node));free_tk(NULL, (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1766 "y.tab.c"
    break;

  case 50: /* Statement: Assignment SEMICOLON  */
#line 123 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[-1].node);free_tk(NULL, (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1772 "y.tab.c"
    break;

  case 51: /* Statement: ParseArgs SEMICOLON  */
#line 124 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[-1].node);free_tk(NULL, (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1778 "y.tab.c"
    break;

  case 52: /* Statement: PRINT LPAR STRLIT RPAR SEMICOLON  */
#line 125 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Print", NULL, (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col, "System.out.print"), create_node("StrLit", (yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, "String"));free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL);}
#line 1784 "y.tab.c"
    break;

  case 53: /* Statement: PRINT LPAR Expr RPAR SEMICOLON  */
#line 126 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Print",NULL, (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col, "System.out.print"), (yyvsp[-2].node));free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), NULL, (yyvsp[-1].tk), (yyvsp[0].tk), NULL);}
#line 1790 "y.tab.c"
    break;

  case 54: /* Statement: error SEMICOLON  */
#line 127 "jucompiler.y"
                                                    {yacc_error = 1; (yyval.node)=NULL;}
#line 1796 "y.tab.c"
    break;

  case 55: /* MultipleStatements: Statement MultipleStatements  */
#line 130 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node),(yyvsp[0].node));}
#line 1802 "y.tab.c"
    break;

  case 56: /* MultipleStatements: Statement  */
#line 131 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1808 "y.tab.c"
    break;

  case 57: /* MethodInvocation: ID LPAR RPAR  */
#line 134 "jucompiler.y"
                                                    {(yyval.node)=create_node("Id", (yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL);free_tk((yyvsp[-2].tk), (yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL);}
#line 1814 "y.tab.c"
    break;

  case 58: /* MethodInvocation: ID LPAR Expr RPAR  */
#line 135 "jucompiler.y"
                                                    {(yyval.node)=add_bro(create_node("Id", (yyvsp[-3].tk)->value, (yyvsp[-3].tk)->line, (yyvsp[-3].tk)->col, NULL), (yyvsp[-1].node));free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL);}
#line 1820 "y.tab.c"
    break;

  case 59: /* MethodInvocation: ID LPAR Expr CommaExpr RPAR  */
#line 136 "jucompiler.y"
                                                    {(yyval.node)=add_bro(create_node("Id", (yyvsp[-4].tk)->value, (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col, NULL), add_bro((yyvsp[-2].node), (yyvsp[-1].node)));free_tk((yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[0].tk), NULL, NULL, NULL);}
#line 1826 "y.tab.c"
    break;

  case 60: /* MethodInvocation: ID LPAR error RPAR  */
#line 137 "jucompiler.y"
                                                    {yacc_error = 1; (yyval.node)=NULL;}
#line 1832 "y.tab.c"
    break;

  case 61: /* CommaExpr: COMMA Expr  */
#line 140 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);free_tk((yyvsp[-1].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1838 "y.tab.c"
    break;

  case 62: /* CommaExpr: COMMA Expr CommaExpr  */
#line 141 "jucompiler.y"
                                                    {(yyval.node)=add_bro((yyvsp[-1].node), (yyvsp[0].node));free_tk((yyvsp[-2].tk), NULL, NULL, NULL, NULL, NULL);}
#line 1844 "y.tab.c"
    break;

  case 63: /* Assignment: ID ASSIGN Expr  */
#line 144 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Assign", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "="), add_bro(create_node("Id", (yyvsp[-2].tk)->value, (yyvsp[-2].tk)->line, (yyvsp[-2].tk)->col, NULL),(yyvsp[0].node)));free_tk((yyvsp[-2].tk), (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1850 "y.tab.c"
    break;

  case 64: /* ParseArgs: PARSEINT LPAR ID LSQ Expr RSQ RPAR  */
#line 146 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("ParseArgs", NULL, (yyvsp[-6].tk)->line, (yyvsp[-6].tk)->col, "Integer.parseInt"), add_bro(create_node("Id", (yyvsp[-4].tk)->value, (yyvsp[-4].tk)->line, (yyvsp[-4].tk)->col, NULL),(yyvsp[-2].node))); free_tk((yyvsp[-6].tk), (yyvsp[-5].tk), (yyvsp[-4].tk), (yyvsp[-3].tk), (yyvsp[-1].tk), (yyvsp[0].tk));}
#line 1856 "y.tab.c"
    break;

  case 65: /* ParseArgs: PARSEINT LPAR error RPAR  */
#line 147 "jucompiler.y"
                                                    {yacc_error = 1; (yyval.node)=NULL;free_tk((yyvsp[-3].tk), (yyvsp[-2].tk), NULL, (yyvsp[0].tk), NULL, NULL);}
#line 1862 "y.tab.c"
    break;

  case 66: /* Expr: ExprNoAssign  */
#line 150 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1868 "y.tab.c"
    break;

  case 67: /* Expr: Assignment  */
#line 151 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 1874 "y.tab.c"
    break;

  case 68: /* ExprNoAssign: ExprNoAssign PLUS ExprNoAssign  */
#line 154 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Add", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "+"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1880 "y.tab.c"
    break;

  case 69: /* ExprNoAssign: ExprNoAssign MINUS ExprNoAssign  */
#line 155 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Sub", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "-"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1886 "y.tab.c"
    break;

  case 70: /* ExprNoAssign: ExprNoAssign STAR ExprNoAssign  */
#line 156 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Mul", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "*"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1892 "y.tab.c"
    break;

  case 71: /* ExprNoAssign: ExprNoAssign DIV ExprNoAssign  */
#line 157 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Div", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "/"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1898 "y.tab.c"
    break;

  case 72: /* ExprNoAssign: ExprNoAssign MOD ExprNoAssign  */
#line 158 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Mod", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "%"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1904 "y.tab.c"
    break;

  case 73: /* ExprNoAssign: ExprNoAssign AND ExprNoAssign  */
#line 159 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("And", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "&&"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1910 "y.tab.c"
    break;

  case 74: /* ExprNoAssign: ExprNoAssign OR ExprNoAssign  */
#line 160 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Or", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "||"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1916 "y.tab.c"
    break;

  case 75: /* ExprNoAssign: ExprNoAssign XOR ExprNoAssign  */
#line 161 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Xor", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "^"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1922 "y.tab.c"
    break;

  case 76: /* ExprNoAssign: ExprNoAssign LSHIFT ExprNoAssign  */
#line 162 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Lshift", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "<<"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1928 "y.tab.c"
    break;

  case 77: /* ExprNoAssign: ExprNoAssign RSHIFT ExprNoAssign  */
#line 163 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Rshift", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, ">>"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1934 "y.tab.c"
    break;

  case 78: /* ExprNoAssign: ExprNoAssign EQ ExprNoAssign  */
#line 164 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Eq", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "=="), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1940 "y.tab.c"
    break;

  case 79: /* ExprNoAssign: ExprNoAssign GE ExprNoAssign  */
#line 165 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Ge", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, ">="), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1946 "y.tab.c"
    break;

  case 80: /* ExprNoAssign: ExprNoAssign GT ExprNoAssign  */
#line 166 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Gt", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, ">"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1952 "y.tab.c"
    break;

  case 81: /* ExprNoAssign: ExprNoAssign LE ExprNoAssign  */
#line 167 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Le", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "<="), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1958 "y.tab.c"
    break;

  case 82: /* ExprNoAssign: ExprNoAssign LT ExprNoAssign  */
#line 168 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Lt", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "<"), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1964 "y.tab.c"
    break;

  case 83: /* ExprNoAssign: ExprNoAssign NE ExprNoAssign  */
#line 169 "jucompiler.y"
                                                                    {(yyval.node)=add_son(create_node("Ne", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "!="), add_bro((yyvsp[-2].node), (yyvsp[0].node)));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1970 "y.tab.c"
    break;

  case 84: /* ExprNoAssign: MINUS ExprNoAssign  */
#line 170 "jucompiler.y"
                                                            {(yyval.node)=add_son(create_node("Minus", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "-"), (yyvsp[0].node));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1976 "y.tab.c"
    break;

  case 85: /* ExprNoAssign: NOT ExprNoAssign  */
#line 171 "jucompiler.y"
                                                            {(yyval.node)=add_son(create_node("Not", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "!"), (yyvsp[0].node));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1982 "y.tab.c"
    break;

  case 86: /* ExprNoAssign: PLUS ExprNoAssign  */
#line 172 "jucompiler.y"
                                                            {(yyval.node)=add_son(create_node("Plus", NULL, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, "+"), (yyvsp[0].node));free_tk(NULL, (yyvsp[-1].tk), NULL, NULL, NULL, NULL);}
#line 1988 "y.tab.c"
    break;

  case 87: /* ExprNoAssign: LPAR Expr RPAR  */
#line 173 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[-1].node);free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 1994 "y.tab.c"
    break;

  case 88: /* ExprNoAssign: MethodInvocation  */
#line 174 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Call", NULL, (yyvsp[0].node)->line, (yyvsp[0].node)->col, NULL), (yyvsp[0].node));}
#line 2000 "y.tab.c"
    break;

  case 89: /* ExprNoAssign: ParseArgs  */
#line 175 "jucompiler.y"
                                                    {(yyval.node)=(yyvsp[0].node);}
#line 2006 "y.tab.c"
    break;

  case 90: /* ExprNoAssign: ID DOTLENGTH  */
#line 176 "jucompiler.y"
                                                    {(yyval.node)=add_son(create_node("Length", NULL, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, ".length"), create_node("Id", (yyvsp[-1].tk)->value, (yyvsp[-1].tk)->line, (yyvsp[-1].tk)->col, NULL));free_tk((yyvsp[-1].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 2012 "y.tab.c"
    break;

  case 91: /* ExprNoAssign: ID  */
#line 177 "jucompiler.y"
                                                    {(yyval.node)=create_node("Id", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, NULL);free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 2018 "y.tab.c"
    break;

  case 92: /* ExprNoAssign: INTLIT  */
#line 178 "jucompiler.y"
                                                    {(yyval.node)=create_node("DecLit", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "int");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 2024 "y.tab.c"
    break;

  case 93: /* ExprNoAssign: REALLIT  */
#line 179 "jucompiler.y"
                                                    {(yyval.node)=create_node("RealLit", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "double");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 2030 "y.tab.c"
    break;

  case 94: /* ExprNoAssign: BOOLLIT  */
#line 180 "jucompiler.y"
                                                    {(yyval.node)=create_node("BoolLit", (yyvsp[0].tk)->value, (yyvsp[0].tk)->line, (yyvsp[0].tk)->col, "boolean");free_tk((yyvsp[0].tk), NULL, NULL, NULL, NULL, NULL);}
#line 2036 "y.tab.c"
    break;

  case 95: /* ExprNoAssign: LPAR error RPAR  */
#line 181 "jucompiler.y"
                                                    {yacc_error = 1; (yyval.node)=NULL;free_tk((yyvsp[-2].tk), (yyvsp[0].tk), NULL, NULL, NULL, NULL);}
#line 2042 "y.tab.c"
    break;


#line 2046 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 184 "jucompiler.y"


void free_tk(Tk *tk1, Tk *tk2, Tk *tk3, Tk *tk4, Tk *tk5, Tk *tk6){
    Tk *tks[MAX_TK] = {tk1, tk2, tk3, tk4, tk5, tk6};
    for(int i = 0; i < MAX_TK; i++){
        if(tks[i]){
            if(tks[i]->value) free(tks[i]->value);
            free(tks[i]);
        }
    }
}

void yyerror (char * s) {
    printf ("Line %d, col %d: %s: %s\n", line_yacc, col_yacc, s, yytext);
}
