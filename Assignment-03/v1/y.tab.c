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
#line 1 "parse.y"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
int scope_level = 0;
int function_declared = 0;

void print_syntax_success(char* construct) {
    printf("SYNTAX OK (Line %d): %s\n", line_number, construct);
}

#line 90 "y.tab.c"

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
    INT_TOK = 258,                 /* INT_TOK  */
    FLOAT_TOK = 259,               /* FLOAT_TOK  */
    CHAR_TOK = 260,                /* CHAR_TOK  */
    WHILE_TOK = 261,               /* WHILE_TOK  */
    FOR_TOK = 262,                 /* FOR_TOK  */
    DO_TOK = 263,                  /* DO_TOK  */
    IF_TOK = 264,                  /* IF_TOK  */
    ELSE_TOK = 265,                /* ELSE_TOK  */
    RETURN_TOK = 266,              /* RETURN_TOK  */
    ID_TOK = 267,                  /* ID_TOK  */
    INTCONST_TOK = 268,            /* INTCONST_TOK  */
    FLOATCONST_TOK = 269,          /* FLOATCONST_TOK  */
    STRING_TOK = 270,              /* STRING_TOK  */
    ADD_TOK = 271,                 /* ADD_TOK  */
    SUB_TOK = 272,                 /* SUB_TOK  */
    MUL_TOK = 273,                 /* MUL_TOK  */
    DIV_TOK = 274,                 /* DIV_TOK  */
    MOD_TOK = 275,                 /* MOD_TOK  */
    LT_TOK = 276,                  /* LT_TOK  */
    GT_TOK = 277,                  /* GT_TOK  */
    LE_TOK = 278,                  /* LE_TOK  */
    GE_TOK = 279,                  /* GE_TOK  */
    EQ_TOK = 280,                  /* EQ_TOK  */
    NEQ_TOK = 281,                 /* NEQ_TOK  */
    AND_TOK = 282,                 /* AND_TOK  */
    OR_TOK = 283,                  /* OR_TOK  */
    NOT_TOK = 284,                 /* NOT_TOK  */
    BIT_AND_TOK = 285,             /* BIT_AND_TOK  */
    BIT_OR_TOK = 286,              /* BIT_OR_TOK  */
    BIT_XOR_TOK = 287,             /* BIT_XOR_TOK  */
    BIT_NOT_TOK = 288,             /* BIT_NOT_TOK  */
    BIT_LSHIFT_TOK = 289,          /* BIT_LSHIFT_TOK  */
    BIT_RSHIFT_TOK = 290,          /* BIT_RSHIFT_TOK  */
    ASSIGN_TOK = 291,              /* ASSIGN_TOK  */
    ADD_ASSIGN_TOK = 292,          /* ADD_ASSIGN_TOK  */
    SUB_ASSIGN_TOK = 293,          /* SUB_ASSIGN_TOK  */
    MUL_ASSIGN_TOK = 294,          /* MUL_ASSIGN_TOK  */
    DIV_ASSIGN_TOK = 295,          /* DIV_ASSIGN_TOK  */
    MOD_ASSIGN_TOK = 296,          /* MOD_ASSIGN_TOK  */
    INC_TOK = 297,                 /* INC_TOK  */
    DEC_TOK = 298,                 /* DEC_TOK  */
    TERNARY_TOK = 299,             /* TERNARY_TOK  */
    COLON_TOK = 300,               /* COLON_TOK  */
    LPAREN_TOK = 301,              /* LPAREN_TOK  */
    RPAREN_TOK = 302,              /* RPAREN_TOK  */
    LBRACE_TOK = 303,              /* LBRACE_TOK  */
    RBRACE_TOK = 304,              /* RBRACE_TOK  */
    LBRACKET_TOK = 305,            /* LBRACKET_TOK  */
    RBRACKET_TOK = 306,            /* RBRACKET_TOK  */
    SEMICOLON_TOK = 307,           /* SEMICOLON_TOK  */
    COMMA_TOK = 308,               /* COMMA_TOK  */
    ERROR_TOK = 309,               /* ERROR_TOK  */
    ID_TOO_LONG_ERROR = 310,       /* ID_TOO_LONG_ERROR  */
    NUM_TOO_LONG_ERROR = 311,      /* NUM_TOO_LONG_ERROR  */
    ILLEGAL_CHAR_ERROR = 312,      /* ILLEGAL_CHAR_ERROR  */
    UNMATCHED_STRING_ERROR = 313,  /* UNMATCHED_STRING_ERROR  */
    SPELLING_ERROR = 314,          /* SPELLING_ERROR  */
    INVALID_NUM_ERROR = 315,       /* INVALID_NUM_ERROR  */
    UNARY_MINUS = 316,             /* UNARY_MINUS  */
    UNARY_PLUS = 317               /* UNARY_PLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INT_TOK 258
#define FLOAT_TOK 259
#define CHAR_TOK 260
#define WHILE_TOK 261
#define FOR_TOK 262
#define DO_TOK 263
#define IF_TOK 264
#define ELSE_TOK 265
#define RETURN_TOK 266
#define ID_TOK 267
#define INTCONST_TOK 268
#define FLOATCONST_TOK 269
#define STRING_TOK 270
#define ADD_TOK 271
#define SUB_TOK 272
#define MUL_TOK 273
#define DIV_TOK 274
#define MOD_TOK 275
#define LT_TOK 276
#define GT_TOK 277
#define LE_TOK 278
#define GE_TOK 279
#define EQ_TOK 280
#define NEQ_TOK 281
#define AND_TOK 282
#define OR_TOK 283
#define NOT_TOK 284
#define BIT_AND_TOK 285
#define BIT_OR_TOK 286
#define BIT_XOR_TOK 287
#define BIT_NOT_TOK 288
#define BIT_LSHIFT_TOK 289
#define BIT_RSHIFT_TOK 290
#define ASSIGN_TOK 291
#define ADD_ASSIGN_TOK 292
#define SUB_ASSIGN_TOK 293
#define MUL_ASSIGN_TOK 294
#define DIV_ASSIGN_TOK 295
#define MOD_ASSIGN_TOK 296
#define INC_TOK 297
#define DEC_TOK 298
#define TERNARY_TOK 299
#define COLON_TOK 300
#define LPAREN_TOK 301
#define RPAREN_TOK 302
#define LBRACE_TOK 303
#define RBRACE_TOK 304
#define LBRACKET_TOK 305
#define RBRACKET_TOK 306
#define SEMICOLON_TOK 307
#define COMMA_TOK 308
#define ERROR_TOK 309
#define ID_TOO_LONG_ERROR 310
#define NUM_TOO_LONG_ERROR 311
#define ILLEGAL_CHAR_ERROR 312
#define UNMATCHED_STRING_ERROR 313
#define SPELLING_ERROR 314
#define INVALID_NUM_ERROR 315
#define UNARY_MINUS 316
#define UNARY_PLUS 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
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
  YYSYMBOL_INT_TOK = 3,                    /* INT_TOK  */
  YYSYMBOL_FLOAT_TOK = 4,                  /* FLOAT_TOK  */
  YYSYMBOL_CHAR_TOK = 5,                   /* CHAR_TOK  */
  YYSYMBOL_WHILE_TOK = 6,                  /* WHILE_TOK  */
  YYSYMBOL_FOR_TOK = 7,                    /* FOR_TOK  */
  YYSYMBOL_DO_TOK = 8,                     /* DO_TOK  */
  YYSYMBOL_IF_TOK = 9,                     /* IF_TOK  */
  YYSYMBOL_ELSE_TOK = 10,                  /* ELSE_TOK  */
  YYSYMBOL_RETURN_TOK = 11,                /* RETURN_TOK  */
  YYSYMBOL_ID_TOK = 12,                    /* ID_TOK  */
  YYSYMBOL_INTCONST_TOK = 13,              /* INTCONST_TOK  */
  YYSYMBOL_FLOATCONST_TOK = 14,            /* FLOATCONST_TOK  */
  YYSYMBOL_STRING_TOK = 15,                /* STRING_TOK  */
  YYSYMBOL_ADD_TOK = 16,                   /* ADD_TOK  */
  YYSYMBOL_SUB_TOK = 17,                   /* SUB_TOK  */
  YYSYMBOL_MUL_TOK = 18,                   /* MUL_TOK  */
  YYSYMBOL_DIV_TOK = 19,                   /* DIV_TOK  */
  YYSYMBOL_MOD_TOK = 20,                   /* MOD_TOK  */
  YYSYMBOL_LT_TOK = 21,                    /* LT_TOK  */
  YYSYMBOL_GT_TOK = 22,                    /* GT_TOK  */
  YYSYMBOL_LE_TOK = 23,                    /* LE_TOK  */
  YYSYMBOL_GE_TOK = 24,                    /* GE_TOK  */
  YYSYMBOL_EQ_TOK = 25,                    /* EQ_TOK  */
  YYSYMBOL_NEQ_TOK = 26,                   /* NEQ_TOK  */
  YYSYMBOL_AND_TOK = 27,                   /* AND_TOK  */
  YYSYMBOL_OR_TOK = 28,                    /* OR_TOK  */
  YYSYMBOL_NOT_TOK = 29,                   /* NOT_TOK  */
  YYSYMBOL_BIT_AND_TOK = 30,               /* BIT_AND_TOK  */
  YYSYMBOL_BIT_OR_TOK = 31,                /* BIT_OR_TOK  */
  YYSYMBOL_BIT_XOR_TOK = 32,               /* BIT_XOR_TOK  */
  YYSYMBOL_BIT_NOT_TOK = 33,               /* BIT_NOT_TOK  */
  YYSYMBOL_BIT_LSHIFT_TOK = 34,            /* BIT_LSHIFT_TOK  */
  YYSYMBOL_BIT_RSHIFT_TOK = 35,            /* BIT_RSHIFT_TOK  */
  YYSYMBOL_ASSIGN_TOK = 36,                /* ASSIGN_TOK  */
  YYSYMBOL_ADD_ASSIGN_TOK = 37,            /* ADD_ASSIGN_TOK  */
  YYSYMBOL_SUB_ASSIGN_TOK = 38,            /* SUB_ASSIGN_TOK  */
  YYSYMBOL_MUL_ASSIGN_TOK = 39,            /* MUL_ASSIGN_TOK  */
  YYSYMBOL_DIV_ASSIGN_TOK = 40,            /* DIV_ASSIGN_TOK  */
  YYSYMBOL_MOD_ASSIGN_TOK = 41,            /* MOD_ASSIGN_TOK  */
  YYSYMBOL_INC_TOK = 42,                   /* INC_TOK  */
  YYSYMBOL_DEC_TOK = 43,                   /* DEC_TOK  */
  YYSYMBOL_TERNARY_TOK = 44,               /* TERNARY_TOK  */
  YYSYMBOL_COLON_TOK = 45,                 /* COLON_TOK  */
  YYSYMBOL_LPAREN_TOK = 46,                /* LPAREN_TOK  */
  YYSYMBOL_RPAREN_TOK = 47,                /* RPAREN_TOK  */
  YYSYMBOL_LBRACE_TOK = 48,                /* LBRACE_TOK  */
  YYSYMBOL_RBRACE_TOK = 49,                /* RBRACE_TOK  */
  YYSYMBOL_LBRACKET_TOK = 50,              /* LBRACKET_TOK  */
  YYSYMBOL_RBRACKET_TOK = 51,              /* RBRACKET_TOK  */
  YYSYMBOL_SEMICOLON_TOK = 52,             /* SEMICOLON_TOK  */
  YYSYMBOL_COMMA_TOK = 53,                 /* COMMA_TOK  */
  YYSYMBOL_ERROR_TOK = 54,                 /* ERROR_TOK  */
  YYSYMBOL_ID_TOO_LONG_ERROR = 55,         /* ID_TOO_LONG_ERROR  */
  YYSYMBOL_NUM_TOO_LONG_ERROR = 56,        /* NUM_TOO_LONG_ERROR  */
  YYSYMBOL_ILLEGAL_CHAR_ERROR = 57,        /* ILLEGAL_CHAR_ERROR  */
  YYSYMBOL_UNMATCHED_STRING_ERROR = 58,    /* UNMATCHED_STRING_ERROR  */
  YYSYMBOL_SPELLING_ERROR = 59,            /* SPELLING_ERROR  */
  YYSYMBOL_INVALID_NUM_ERROR = 60,         /* INVALID_NUM_ERROR  */
  YYSYMBOL_UNARY_MINUS = 61,               /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 62,                /* UNARY_PLUS  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_program = 64,                   /* program  */
  YYSYMBOL_global_declarations = 65,       /* global_declarations  */
  YYSYMBOL_global_declaration = 66,        /* global_declaration  */
  YYSYMBOL_main_function = 67,             /* main_function  */
  YYSYMBOL_user_functions = 68,            /* user_functions  */
  YYSYMBOL_user_function = 69,             /* user_function  */
  YYSYMBOL_function_declaration = 70,      /* function_declaration  */
  YYSYMBOL_function_definition = 71,       /* function_definition  */
  YYSYMBOL_parameter_list = 72,            /* parameter_list  */
  YYSYMBOL_parameter = 73,                 /* parameter  */
  YYSYMBOL_data_type = 74,                 /* data_type  */
  YYSYMBOL_declarator_list = 75,           /* declarator_list  */
  YYSYMBOL_declarator = 76,                /* declarator  */
  YYSYMBOL_compound_statement = 77,        /* compound_statement  */
  YYSYMBOL_78_1 = 78,                      /* $@1  */
  YYSYMBOL_79_2 = 79,                      /* $@2  */
  YYSYMBOL_80_3 = 80,                      /* $@3  */
  YYSYMBOL_81_4 = 81,                      /* $@4  */
  YYSYMBOL_local_declarations = 82,        /* local_declarations  */
  YYSYMBOL_local_declaration = 83,         /* local_declaration  */
  YYSYMBOL_statement_list = 84,            /* statement_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_expression_statement = 86,      /* expression_statement  */
  YYSYMBOL_assignment_statement = 87,      /* assignment_statement  */
  YYSYMBOL_conditional_statement = 88,     /* conditional_statement  */
  YYSYMBOL_iterative_statement = 89,       /* iterative_statement  */
  YYSYMBOL_for_init = 90,                  /* for_init  */
  YYSYMBOL_for_condition = 91,             /* for_condition  */
  YYSYMBOL_for_update = 92,                /* for_update  */
  YYSYMBOL_declaration_expression = 93,    /* declaration_expression  */
  YYSYMBOL_assignment_expression = 94,     /* assignment_expression  */
  YYSYMBOL_return_statement = 95,          /* return_statement  */
  YYSYMBOL_expression = 96,                /* expression  */
  YYSYMBOL_assignment_expr = 97,           /* assignment_expr  */
  YYSYMBOL_conditional_expr = 98,          /* conditional_expr  */
  YYSYMBOL_logical_or_expr = 99,           /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 100,         /* logical_and_expr  */
  YYSYMBOL_bitwise_or_expr = 101,          /* bitwise_or_expr  */
  YYSYMBOL_bitwise_xor_expr = 102,         /* bitwise_xor_expr  */
  YYSYMBOL_bitwise_and_expr = 103,         /* bitwise_and_expr  */
  YYSYMBOL_equality_expr = 104,            /* equality_expr  */
  YYSYMBOL_relational_expr = 105,          /* relational_expr  */
  YYSYMBOL_shift_expr = 106,               /* shift_expr  */
  YYSYMBOL_additive_expr = 107,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 108,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 109,               /* unary_expr  */
  YYSYMBOL_unary_operator = 110,           /* unary_operator  */
  YYSYMBOL_postfix_expr = 111,             /* postfix_expr  */
  YYSYMBOL_argument_list = 112,            /* argument_list  */
  YYSYMBOL_primary_expr = 113              /* primary_expr  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   644

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  339

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    73,    79,    88,    89,    92,    94,    96,
     102,   108,   117,   122,   130,   131,   132,   135,   136,   139,
     141,   143,   149,   155,   163,   165,   170,   171,   172,   178,
     186,   187,   191,   192,   193,   197,   198,   199,   205,   213,
     214,   215,   220,   222,   219,   226,   228,   225,   235,   244,
     245,   248,   250,   256,   262,   271,   272,   276,   277,   278,
     279,   280,   281,   284,   286,   287,   296,   298,   300,   302,
     304,   306,   308,   310,   316,   322,   331,   333,   335,   341,
     347,   356,   358,   360,   362,   368,   374,   380,   386,   392,
     400,   401,   402,   405,   406,   409,   410,   413,   415,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   427,   431,
     433,   435,   441,   450,   453,   454,   455,   456,   457,   458,
     459,   462,   463,   466,   467,   470,   471,   474,   475,   478,
     479,   482,   483,   486,   487,   488,   491,   492,   493,   494,
     495,   498,   499,   500,   503,   504,   505,   508,   509,   510,
     511,   514,   515,   516,   517,   520,   521,   522,   523,   526,
     527,   528,   534,   540,   542,   544,   550,   556,   557,   560,
     561,   562,   568,   576,   577,   578,   579,   580,   581,   587
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_TOK", "FLOAT_TOK",
  "CHAR_TOK", "WHILE_TOK", "FOR_TOK", "DO_TOK", "IF_TOK", "ELSE_TOK",
  "RETURN_TOK", "ID_TOK", "INTCONST_TOK", "FLOATCONST_TOK", "STRING_TOK",
  "ADD_TOK", "SUB_TOK", "MUL_TOK", "DIV_TOK", "MOD_TOK", "LT_TOK",
  "GT_TOK", "LE_TOK", "GE_TOK", "EQ_TOK", "NEQ_TOK", "AND_TOK", "OR_TOK",
  "NOT_TOK", "BIT_AND_TOK", "BIT_OR_TOK", "BIT_XOR_TOK", "BIT_NOT_TOK",
  "BIT_LSHIFT_TOK", "BIT_RSHIFT_TOK", "ASSIGN_TOK", "ADD_ASSIGN_TOK",
  "SUB_ASSIGN_TOK", "MUL_ASSIGN_TOK", "DIV_ASSIGN_TOK", "MOD_ASSIGN_TOK",
  "INC_TOK", "DEC_TOK", "TERNARY_TOK", "COLON_TOK", "LPAREN_TOK",
  "RPAREN_TOK", "LBRACE_TOK", "RBRACE_TOK", "LBRACKET_TOK", "RBRACKET_TOK",
  "SEMICOLON_TOK", "COMMA_TOK", "ERROR_TOK", "ID_TOO_LONG_ERROR",
  "NUM_TOO_LONG_ERROR", "ILLEGAL_CHAR_ERROR", "UNMATCHED_STRING_ERROR",
  "SPELLING_ERROR", "INVALID_NUM_ERROR", "UNARY_MINUS", "UNARY_PLUS",
  "$accept", "program", "global_declarations", "global_declaration",
  "main_function", "user_functions", "user_function",
  "function_declaration", "function_definition", "parameter_list",
  "parameter", "data_type", "declarator_list", "declarator",
  "compound_statement", "$@1", "$@2", "$@3", "$@4", "local_declarations",
  "local_declaration", "statement_list", "statement",
  "expression_statement", "assignment_statement", "conditional_statement",
  "iterative_statement", "for_init", "for_condition", "for_update",
  "declaration_expression", "assignment_expression", "return_statement",
  "expression", "assignment_expr", "conditional_expr", "logical_or_expr",
  "logical_and_expr", "bitwise_or_expr", "bitwise_xor_expr",
  "bitwise_and_expr", "equality_expr", "relational_expr", "shift_expr",
  "additive_expr", "multiplicative_expr", "unary_expr", "unary_operator",
  "postfix_expr", "argument_list", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-193)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-174)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     132,     9,  -193,  -193,  -193,    56,   132,  -193,   212,  -193,
      26,   -16,    25,  -193,  -193,  -193,   212,   212,  -193,  -193,
    -193,    19,    -6,    36,    27,   576,    47,     9,  -193,    29,
     212,  -193,   125,  -193,    17,   146,     9,  -193,   307,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,   598,   598,   466,  -193,
    -193,  -193,    -4,    41,    77,    89,    98,   135,   218,   152,
     141,   259,  -193,   598,   142,  -193,    81,  -193,  -193,  -193,
     151,    86,    21,    34,  -193,   133,   576,   576,   576,   576,
     576,   576,  -193,  -193,  -193,   121,    53,   598,   576,   598,
     598,   598,   598,   598,   598,   598,   598,   598,   598,   598,
     598,   598,   598,   598,   598,   598,  -193,  -193,  -193,   444,
     488,  -193,    21,    48,  -193,  -193,   221,  -193,  -193,   107,
       0,   206,   127,  -193,  -193,  -193,  -193,  -193,  -193,  -193,
    -193,  -193,    41,   178,    77,    89,    98,   135,   218,   218,
     152,   152,   152,   152,   141,   141,   259,   259,  -193,  -193,
    -193,   161,  -193,  -193,    50,   180,    58,  -193,     0,   194,
    -193,  -193,  -193,  -193,  -193,  -193,  -193,  -193,   202,   598,
    -193,   576,  -193,   510,  -193,  -193,  -193,  -193,  -193,   325,
     375,  -193,  -193,  -193,  -193,  -193,     9,    32,  -193,   422,
     422,    46,   210,    52,   126,   222,   422,   130,   101,   275,
    -193,  -193,   223,  -193,  -193,  -193,  -193,  -193,  -193,     5,
     270,  -193,  -193,     9,  -193,   576,   576,   209,   268,   576,
     532,  -193,  -193,    10,   576,   554,   576,   576,   576,   576,
     576,   576,  -193,  -193,  -193,  -193,   228,    60,   246,   292,
     296,   308,    18,  -193,  -193,   234,   276,   277,   122,  -193,
    -193,   283,   297,    31,  -193,   298,   321,   299,   351,   301,
     354,   304,   356,   309,   358,   311,   422,   422,   422,   576,
     576,   576,   576,   576,   576,  -193,  -193,  -193,  -193,   324,
     576,   576,   576,   422,   422,   422,   422,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,   327,  -193,  -193,  -193,
    -193,  -193,  -193,  -193,  -193,  -193,   576,   312,  -193,    38,
     318,  -193,  -193,  -193,   359,   576,  -193,   140,   140,   140,
      54,   422,   314,   323,  -193,   328,   123,  -193,  -193,  -193,
    -193,   422,   422,   422,   422,  -193,  -193,  -193,  -193
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    32,    33,    34,     0,     0,     6,     4,     8,
       0,    39,     0,    36,     1,     5,    16,     3,    15,    17,
      18,     0,     0,     0,     0,     0,     0,     0,    11,     0,
       2,    14,     0,    10,     0,     0,     9,     7,   173,   174,
     175,   176,   155,   156,   157,   158,     0,     0,     0,    41,
     113,   114,   121,   123,   125,   127,   129,   131,   133,   136,
     141,   144,   147,     0,   151,   159,     0,    37,    38,    35,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
       0,     0,   173,   152,   153,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   154,   167,   168,     0,
       0,    40,     0,     0,    23,    21,     0,    19,    12,     0,
       0,     0,    30,   115,   116,   117,   118,   119,   120,   179,
     178,   177,   124,     0,   126,   128,   130,   132,   134,   135,
     137,   138,   139,   140,   142,   143,   145,   146,   148,   149,
     150,     0,   163,   170,     0,     0,     0,    24,     0,     0,
      50,    50,    22,    28,    20,    13,    29,    26,     0,     0,
     166,   165,   164,     0,   162,   161,   160,    25,    48,     0,
       0,    31,   122,   171,   172,   169,     0,     0,    49,    43,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,    58,     0,    55,    57,    62,    59,    60,    61,     0,
       0,    54,    53,    52,    51,     0,     0,    92,     0,     0,
       0,   112,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,    65,    63,    47,     0,     0,     0,     0,
       0,     0,     0,    91,    90,     0,     0,     0,     0,   111,
     110,     0,     0,     0,   113,     0,   113,     0,   113,     0,
     113,     0,   113,     0,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,    98,
      94,    94,     0,     0,     0,     0,     0,    75,    74,    73,
      66,    67,    68,    69,    70,    71,     0,    85,    84,    81,
      99,   100,   101,   102,   103,   104,     0,     0,    93,     0,
       0,    80,    79,    78,    76,     0,    97,    96,    96,    96,
       0,     0,     0,     0,    95,     0,     0,    89,    83,    77,
      72,     0,     0,     0,     0,    87,    88,    86,    82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -193,  -193,  -193,   366,   379,   377,    12,   119,  -193,   326,
     -76,     1,    -8,   -24,   -62,  -193,  -193,  -193,  -193,   233,
    -193,   215,  -192,  -193,  -193,  -193,  -193,  -193,   116,  -144,
    -193,   181,  -193,   -25,   -63,   230,  -193,   313,   316,   317,
     310,   319,   103,   163,   120,   164,   -38,  -193,  -193,  -193,
    -193
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     5,     6,     7,     8,    17,    18,    19,    20,    73,
      74,    21,    12,    13,   201,   160,   202,   161,   210,   179,
     188,   189,   203,   204,   205,   206,   207,   242,   307,   323,
     243,   324,   208,   209,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,   154,
      65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    10,    24,    67,   218,    69,   233,    10,    83,    84,
     118,   249,    67,   123,   124,   125,   126,   127,   128,   280,
      25,    11,   115,    86,    87,   106,    27,    22,    36,    31,
      68,    32,   289,   192,    26,   119,    75,    34,    23,   318,
      88,    11,    31,   163,    11,   167,    33,    27,   116,   119,
     157,   171,   164,   213,   130,   327,    14,   234,   165,   175,
      66,   267,   250,   133,    71,   148,   149,   150,    89,   116,
     281,    75,    25,   117,   297,   298,   299,    28,    29,    37,
      29,   120,    35,   290,   153,   156,    26,   121,   -39,   -39,
     319,   311,   312,   313,   314,   158,   177,   172,   211,    29,
     131,   121,   221,   173,   214,    29,   328,   268,    90,   176,
       2,     3,     4,    38,    39,    40,    41,    42,    43,     9,
      75,    91,    75,   285,   333,     9,    34,   215,    92,   329,
      44,   219,   111,     1,    45,     2,     3,     4,   114,   335,
     336,   337,   338,    46,    47,   122,   183,    48,   185,     2,
       3,     4,   238,   222,     2,     3,     4,   101,   102,   162,
      93,    94,   254,   256,   258,   260,   262,   264,   129,   286,
     334,    70,   216,   223,   325,   326,   220,   168,   191,   193,
     187,   187,   239,   240,   107,   108,    99,   100,   109,    67,
     236,   237,   110,    72,   246,   248,   138,   139,   112,   251,
     253,   255,   257,   259,   261,   263,   265,   166,   170,     2,
       3,     4,     2,     3,     4,     2,     3,     4,   241,   144,
     145,   238,   159,   169,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   174,   -42,   -42,   -42,   -42,   -42,   -42,   -42,    95,
      96,    97,    98,   178,   300,   301,   302,   303,   304,   305,
     -42,   239,   240,   181,   -42,   308,   308,   310,   140,   141,
     142,   143,   212,   -42,   -42,   146,   147,   -42,   217,   -42,
     -42,   235,   232,   -42,   245,   266,   224,   103,   104,   105,
     282,   316,   269,   270,   271,   272,   273,   274,   275,   276,
     322,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   277,  -173,  -173,  -173,   278,  -173,
    -173,   225,   226,   227,   228,   229,   230,  -173,  -173,  -173,
     279,  -173,  -116,   283,   284,   231,   186,  -173,     2,     3,
       4,   -56,   -56,   -56,   -56,   287,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,    76,    77,    78,    79,    80,    81,   288,
     291,   292,  -117,   293,   -56,  -118,   294,  -119,   -56,  -120,
     306,   295,   296,   315,   317,   320,   330,   -56,   -56,   321,
     331,   -56,    15,   -56,   -56,   332,   186,   -56,     2,     3,
       4,   -56,   -56,   -56,   -56,    16,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,    30,   180,   190,   113,   309,   244,   182,
     132,   136,     0,     0,   -56,   134,     0,   135,   -56,     0,
       0,   137,     0,     0,     0,     0,     0,   -56,   -56,     0,
       0,   -56,     0,   -56,     0,     0,     0,   -56,   194,   195,
     196,   197,     0,   198,   199,    39,    40,    41,    42,    43,
       0,     0,     0,     0,     0,   151,     0,     0,     0,     0,
       0,    44,     0,     0,     0,    45,    38,    39,    40,    41,
      42,    43,     0,     0,    46,    47,     0,    85,    48,     0,
     116,     0,     0,    44,   200,     0,     0,    45,    38,    39,
      40,    41,    42,    43,     0,     0,    46,    47,     0,   155,
      48,   152,     0,     0,     0,    44,     0,     0,     0,    45,
      38,    39,    40,    41,    42,    43,     0,     0,    46,    47,
       0,   184,    48,     0,     0,     0,     0,    44,     0,     0,
       0,    45,    38,    39,    40,    41,    42,    43,     0,     0,
      46,    47,     0,   247,    48,     0,     0,     0,     0,    44,
       0,     0,     0,    45,    38,    39,    40,    41,    42,    43,
       0,     0,    46,    47,     0,   252,    48,     0,     0,     0,
       0,    44,     0,     0,     0,    45,    38,    39,    40,    41,
      42,    43,     0,     0,    46,    47,     0,     0,    48,     0,
       0,     0,     0,    44,     0,     0,     0,    45,    38,    39,
      40,    41,    42,    43,     0,     0,    46,    47,     0,     0,
      48,     0,     0,     0,     0,    44,     0,     0,     0,    45,
      82,    39,    40,    41,    42,    43,     0,     0,    46,    47,
       0,     0,    48,     0,     0,     0,     0,    44,     0,     0,
       0,    45,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    47,     0,     0,    48
};

static const yytype_int16 yycheck[] =
{
      25,     0,    10,    27,   196,    29,     1,     6,    46,    47,
      72,     1,    36,    76,    77,    78,    79,    80,    81,     1,
      36,    12,     1,    48,    28,    63,     1,     1,     1,    17,
       1,    12,     1,     1,    50,     1,    35,     1,    12,     1,
      44,    12,    30,   119,    12,   121,    52,     1,    48,     1,
     112,     1,    52,     1,     1,     1,     0,    52,   120,     1,
      13,     1,    52,    88,    47,   103,   104,   105,    27,    48,
      52,    70,    36,    52,   266,   267,   268,    52,    53,    52,
      53,    47,    46,    52,   109,   110,    50,    53,    52,    53,
      52,   283,   284,   285,   286,    47,   158,    47,    52,    53,
      47,    53,     1,    53,    52,    53,    52,    47,    31,    51,
       3,     4,     5,    12,    13,    14,    15,    16,    17,     0,
     119,    32,   121,     1,     1,     6,     1,     1,    30,   321,
      29,     1,    51,     1,    33,     3,     4,     5,    52,   331,
     332,   333,   334,    42,    43,    12,   171,    46,   173,     3,
       4,     5,    12,    52,     3,     4,     5,    16,    17,    52,
      25,    26,   225,   226,   227,   228,   229,   230,    47,    47,
      47,    46,    46,   198,   318,   319,    46,    50,   186,   187,
     179,   180,    42,    43,    42,    43,    34,    35,    46,   213,
     215,   216,    50,    47,   219,   220,    93,    94,    47,   224,
     225,   226,   227,   228,   229,   230,   231,     1,    47,     3,
       4,     5,     3,     4,     5,     3,     4,     5,   217,    99,
     100,    12,     1,    45,     3,     4,     5,     6,     7,     8,
       9,    51,    11,    12,    13,    14,    15,    16,    17,    21,
      22,    23,    24,    49,   269,   270,   271,   272,   273,   274,
      29,    42,    43,    51,    33,   280,   281,   282,    95,    96,
      97,    98,    52,    42,    43,   101,   102,    46,    46,    48,
      49,     1,    49,    52,     6,    47,     1,    18,    19,    20,
      46,   306,    36,    37,    38,    39,    40,    41,    42,    43,
     315,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    12,    30,    31,    32,    12,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      12,    46,     1,    47,    47,    50,     1,    52,     3,     4,
       5,     6,     7,     8,     9,    52,    11,    12,    13,    14,
      15,    16,    17,    36,    37,    38,    39,    40,    41,    52,
      52,    52,     1,    52,    29,     1,    52,     1,    33,     1,
      36,    52,    51,    36,    52,    47,    52,    42,    43,    10,
      47,    46,     6,    48,    49,    47,     1,    52,     3,     4,
       5,     6,     7,     8,     9,     6,    11,    12,    13,    14,
      15,    16,    17,    16,   161,   180,    70,   281,   217,   169,
      87,    91,    -1,    -1,    29,    89,    -1,    90,    33,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,
      -1,    46,    -1,    48,    -1,    -1,    -1,    52,     6,     7,
       8,     9,    -1,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    33,    12,    13,    14,    15,
      16,    17,    -1,    -1,    42,    43,    -1,     1,    46,    -1,
      48,    -1,    -1,    29,    52,    -1,    -1,    33,    12,    13,
      14,    15,    16,    17,    -1,    -1,    42,    43,    -1,     1,
      46,    47,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      12,    13,    14,    15,    16,    17,    -1,    -1,    42,    43,
      -1,     1,    46,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    33,    12,    13,    14,    15,    16,    17,    -1,    -1,
      42,    43,    -1,     1,    46,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    33,    12,    13,    14,    15,    16,    17,
      -1,    -1,    42,    43,    -1,     1,    46,    -1,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    33,    12,    13,    14,    15,
      16,    17,    -1,    -1,    42,    43,    -1,    -1,    46,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    -1,    33,    12,    13,
      14,    15,    16,    17,    -1,    -1,    42,    43,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,    33,
      12,    13,    14,    15,    16,    17,    -1,    -1,    42,    43,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    43,    -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,    64,    65,    66,    67,    70,
      74,    12,    75,    76,     0,    66,    67,    68,    69,    70,
      71,    74,     1,    12,    75,    36,    50,     1,    52,    53,
      68,    69,    12,    52,     1,    46,     1,    52,    12,    13,
      14,    15,    16,    17,    29,    33,    42,    43,    46,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   113,    13,    76,     1,    76,
      46,    47,    47,    72,    73,    74,    36,    37,    38,    39,
      40,    41,    12,   109,   109,     1,    96,    28,    44,    27,
      31,    32,    30,    25,    26,    21,    22,    23,    24,    34,
      35,    16,    17,    18,    19,    20,   109,    42,    43,    46,
      50,    51,    47,    72,    52,     1,    48,    52,    77,     1,
      47,    53,    12,    97,    97,    97,    97,    97,    97,    47,
       1,    47,   100,    96,   101,   102,   103,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     109,     1,    47,    96,   112,     1,    96,    77,    47,     1,
      78,    80,    52,    73,    52,    77,     1,    73,    50,    45,
      47,     1,    47,    53,    51,     1,    51,    77,    49,    82,
      82,    51,    98,    96,     1,    96,     1,    74,    83,    84,
      84,    75,     1,    75,     6,     7,     8,     9,    11,    12,
      52,    77,    79,    85,    86,    87,    88,    89,    95,    96,
      81,    52,    52,     1,    52,     1,    46,    46,    85,     1,
      46,     1,    52,    96,     1,    36,    37,    38,    39,    40,
      41,    50,    49,     1,    52,     1,    96,    96,    12,    42,
      43,    74,    90,    93,    94,     6,    96,     1,    96,     1,
      52,    96,     1,    96,    97,    96,    97,    96,    97,    96,
      97,    96,    97,    96,    97,    96,    47,     1,    47,    36,
      37,    38,    39,    40,    41,    42,    43,    12,    12,    12,
       1,    52,    46,    47,    47,     1,    47,    52,    52,     1,
      52,    52,    52,    52,    52,    52,    51,    85,    85,    85,
      96,    96,    96,    96,    96,    96,    36,    91,    96,    91,
      96,    85,    85,    85,    85,    36,    96,    52,     1,    52,
      47,    10,    96,    92,    94,    92,    92,     1,    52,    85,
      52,    47,    47,     1,    47,    85,    85,    85,    85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    69,    69,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    72,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    76,
      76,    76,    78,    79,    77,    80,    81,    77,    77,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    95,    96,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    99,    99,   100,   100,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   105,   105,   105,   105,
     105,   106,   106,   106,   107,   107,   107,   108,   108,   108,
     108,   109,   109,   109,   109,   110,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   112,   113,   113,   113,   113,   113,   113,   113
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     2,     1,     3,     1,     3,
       3,     3,     5,     6,     2,     1,     0,     1,     1,     5,
       6,     5,     6,     5,     5,     6,     3,     1,     3,     3,
       2,     4,     1,     1,     1,     3,     1,     3,     3,     1,
       4,     3,     0,     0,     6,     0,     0,     6,     3,     2,
       0,     3,     3,     3,     3,     2,     0,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     4,     4,     4,     4,
       4,     4,     7,     4,     4,     4,     5,     7,     5,     5,
       5,     5,     9,     7,     5,     5,     9,     9,     9,     7,
       1,     1,     0,     1,     0,     1,     0,     4,     2,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       3,     3,     2,     1,     1,     3,     3,     3,     3,     3,
       3,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       4,     4,     4,     3,     4,     4,     4,     2,     2,     3,
       1,     3,     3,     1,     1,     1,     1,     3,     3,     3
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
  case 2: /* program: global_declarations main_function user_functions  */
#line 68 "parse.y"
         { 
           print_syntax_success("Complete C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
#line 1663 "y.tab.c"
    break;

  case 3: /* program: main_function user_functions  */
#line 74 "parse.y"
         { 
           print_syntax_success("C program with main function");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
#line 1673 "y.tab.c"
    break;

  case 4: /* program: main_function  */
#line 80 "parse.y"
         { 
           print_syntax_success("Simple C program with main function only");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
         }
#line 1683 "y.tab.c"
    break;

  case 7: /* global_declaration: data_type declarator_list SEMICOLON_TOK  */
#line 93 "parse.y"
                   { print_syntax_success("Global variable declaration"); }
#line 1689 "y.tab.c"
    break;

  case 8: /* global_declaration: function_declaration  */
#line 95 "parse.y"
                   { print_syntax_success("Function declaration"); }
#line 1695 "y.tab.c"
    break;

  case 9: /* global_declaration: data_type declarator_list error  */
#line 97 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after variable declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1705 "y.tab.c"
    break;

  case 10: /* global_declaration: data_type error SEMICOLON_TOK  */
#line 103 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid variable declarator list\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1715 "y.tab.c"
    break;

  case 11: /* global_declaration: error declarator_list SEMICOLON_TOK  */
#line 109 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid or missing data type in declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1725 "y.tab.c"
    break;

  case 12: /* main_function: data_type ID_TOK LPAREN_TOK RPAREN_TOK compound_statement  */
#line 118 "parse.y"
               { 
                 print_syntax_success("Main function definition");
                 function_declared = 1;
               }
#line 1734 "y.tab.c"
    break;

  case 13: /* main_function: data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK compound_statement  */
#line 123 "parse.y"
               { 
                 print_syntax_success("Main function with parameters");
                 function_declared = 1;
               }
#line 1743 "y.tab.c"
    break;

  case 19: /* function_declaration: data_type ID_TOK LPAREN_TOK RPAREN_TOK SEMICOLON_TOK  */
#line 140 "parse.y"
                     { print_syntax_success("Function declaration"); }
#line 1749 "y.tab.c"
    break;

  case 20: /* function_declaration: data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK  */
#line 142 "parse.y"
                     { print_syntax_success("Function declaration with parameters"); }
#line 1755 "y.tab.c"
    break;

  case 21: /* function_declaration: data_type ID_TOK LPAREN_TOK RPAREN_TOK error  */
#line 144 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 1765 "y.tab.c"
    break;

  case 22: /* function_declaration: data_type ID_TOK LPAREN_TOK parameter_list error SEMICOLON_TOK  */
#line 150 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 1775 "y.tab.c"
    break;

  case 23: /* function_declaration: data_type ID_TOK error RPAREN_TOK SEMICOLON_TOK  */
#line 156 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in function declaration\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 1785 "y.tab.c"
    break;

  case 24: /* function_definition: data_type ID_TOK LPAREN_TOK RPAREN_TOK compound_statement  */
#line 164 "parse.y"
                    { print_syntax_success("Function definition"); }
#line 1791 "y.tab.c"
    break;

  case 25: /* function_definition: data_type ID_TOK LPAREN_TOK parameter_list RPAREN_TOK compound_statement  */
#line 166 "parse.y"
                    { print_syntax_success("Function definition with parameters"); }
#line 1797 "y.tab.c"
    break;

  case 28: /* parameter_list: parameter_list error parameter  */
#line 173 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Missing comma ',' between parameters\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 1807 "y.tab.c"
    break;

  case 29: /* parameter_list: parameter_list COMMA_TOK error  */
#line 179 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Invalid parameter after comma\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 1817 "y.tab.c"
    break;

  case 37: /* declarator_list: declarator_list error declarator  */
#line 200 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Missing comma ',' between declarators\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1827 "y.tab.c"
    break;

  case 38: /* declarator_list: declarator_list COMMA_TOK error  */
#line 206 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid declarator after comma\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1837 "y.tab.c"
    break;

  case 42: /* $@1: %empty  */
#line 220 "parse.y"
                    { scope_level++; }
#line 1843 "y.tab.c"
    break;

  case 43: /* $@2: %empty  */
#line 222 "parse.y"
                    { scope_level--; }
#line 1849 "y.tab.c"
    break;

  case 44: /* compound_statement: LBRACE_TOK $@1 local_declarations statement_list $@2 RBRACE_TOK  */
#line 224 "parse.y"
                    { print_syntax_success("Compound statement"); }
#line 1855 "y.tab.c"
    break;

  case 45: /* $@3: %empty  */
#line 226 "parse.y"
                    { scope_level++; }
#line 1861 "y.tab.c"
    break;

  case 46: /* $@4: %empty  */
#line 228 "parse.y"
                    { scope_level--; }
#line 1867 "y.tab.c"
    break;

  case 47: /* compound_statement: LBRACE_TOK $@3 local_declarations statement_list $@4 error  */
#line 230 "parse.y"
                    { 
                      printf("SYNTAX ERROR (Line %d): Missing closing brace '}'\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 1877 "y.tab.c"
    break;

  case 48: /* compound_statement: LBRACE_TOK error RBRACE_TOK  */
#line 236 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid content inside braces\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 1887 "y.tab.c"
    break;

  case 51: /* local_declaration: data_type declarator_list SEMICOLON_TOK  */
#line 249 "parse.y"
                  { print_syntax_success("Local variable declaration"); }
#line 1893 "y.tab.c"
    break;

  case 52: /* local_declaration: data_type declarator_list error  */
#line 251 "parse.y"
                  {
                    printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after local declaration\n", line_number);
                    error_count++;
                    yyerrok;
                  }
#line 1903 "y.tab.c"
    break;

  case 53: /* local_declaration: data_type error SEMICOLON_TOK  */
#line 257 "parse.y"
                  {
                    printf("SYNTAX ERROR (Line %d): Invalid local variable declarator\n", line_number);
                    error_count++;
                    yyerrok;
                  }
#line 1913 "y.tab.c"
    break;

  case 54: /* local_declaration: error declarator_list SEMICOLON_TOK  */
#line 263 "parse.y"
                  {
                    printf("SYNTAX ERROR (Line %d): Invalid data type in local declaration\n", line_number);
                    error_count++;
                    yyerrok;
                  }
#line 1923 "y.tab.c"
    break;

  case 63: /* expression_statement: expression SEMICOLON_TOK  */
#line 285 "parse.y"
                     { print_syntax_success("Expression statement"); }
#line 1929 "y.tab.c"
    break;

  case 65: /* expression_statement: expression error  */
#line 288 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after expression\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 1939 "y.tab.c"
    break;

  case 66: /* assignment_statement: ID_TOK ASSIGN_TOK expression SEMICOLON_TOK  */
#line 297 "parse.y"
                     { print_syntax_success("Assignment statement"); }
#line 1945 "y.tab.c"
    break;

  case 67: /* assignment_statement: ID_TOK ADD_ASSIGN_TOK expression SEMICOLON_TOK  */
#line 299 "parse.y"
                     { print_syntax_success("Add-assignment statement"); }
#line 1951 "y.tab.c"
    break;

  case 68: /* assignment_statement: ID_TOK SUB_ASSIGN_TOK expression SEMICOLON_TOK  */
#line 301 "parse.y"
                     { print_syntax_success("Sub-assignment statement"); }
#line 1957 "y.tab.c"
    break;

  case 69: /* assignment_statement: ID_TOK MUL_ASSIGN_TOK expression SEMICOLON_TOK  */
#line 303 "parse.y"
                     { print_syntax_success("Mul-assignment statement"); }
#line 1963 "y.tab.c"
    break;

  case 70: /* assignment_statement: ID_TOK DIV_ASSIGN_TOK expression SEMICOLON_TOK  */
#line 305 "parse.y"
                     { print_syntax_success("Div-assignment statement"); }
#line 1969 "y.tab.c"
    break;

  case 71: /* assignment_statement: ID_TOK MOD_ASSIGN_TOK expression SEMICOLON_TOK  */
#line 307 "parse.y"
                     { print_syntax_success("Mod-assignment statement"); }
#line 1975 "y.tab.c"
    break;

  case 72: /* assignment_statement: ID_TOK LBRACKET_TOK expression RBRACKET_TOK ASSIGN_TOK expression SEMICOLON_TOK  */
#line 309 "parse.y"
                     { print_syntax_success("Array assignment statement"); }
#line 1981 "y.tab.c"
    break;

  case 73: /* assignment_statement: ID_TOK ASSIGN_TOK expression error  */
#line 311 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after assignment\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 1991 "y.tab.c"
    break;

  case 74: /* assignment_statement: ID_TOK ASSIGN_TOK error SEMICOLON_TOK  */
#line 317 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Invalid expression in assignment\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 2001 "y.tab.c"
    break;

  case 75: /* assignment_statement: ID_TOK error expression SEMICOLON_TOK  */
#line 323 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Invalid assignment operator\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 2011 "y.tab.c"
    break;

  case 76: /* conditional_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 332 "parse.y"
                      { print_syntax_success("If statement"); }
#line 2017 "y.tab.c"
    break;

  case 77: /* conditional_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement  */
#line 334 "parse.y"
                      { print_syntax_success("If-else statement"); }
#line 2023 "y.tab.c"
    break;

  case 78: /* conditional_statement: IF_TOK LPAREN_TOK expression error statement  */
#line 336 "parse.y"
                      {
                        printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in if condition\n", line_number);
                        error_count++;
                        yyerrok;
                      }
#line 2033 "y.tab.c"
    break;

  case 79: /* conditional_statement: IF_TOK LPAREN_TOK error RPAREN_TOK statement  */
#line 342 "parse.y"
                      {
                        printf("SYNTAX ERROR (Line %d): Invalid expression in if condition\n", line_number);
                        error_count++;
                        yyerrok;
                      }
#line 2043 "y.tab.c"
    break;

  case 80: /* conditional_statement: IF_TOK error expression RPAREN_TOK statement  */
#line 348 "parse.y"
                      {
                        printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in if statement\n", line_number);
                        error_count++;
                        yyerrok;
                      }
#line 2053 "y.tab.c"
    break;

  case 81: /* iterative_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 357 "parse.y"
                    { print_syntax_success("While loop"); }
#line 2059 "y.tab.c"
    break;

  case 82: /* iterative_statement: FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition SEMICOLON_TOK for_update RPAREN_TOK statement  */
#line 359 "parse.y"
                    { print_syntax_success("For loop"); }
#line 2065 "y.tab.c"
    break;

  case 83: /* iterative_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK  */
#line 361 "parse.y"
                    { print_syntax_success("Do-while loop"); }
#line 2071 "y.tab.c"
    break;

  case 84: /* iterative_statement: WHILE_TOK LPAREN_TOK expression error statement  */
#line 363 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2081 "y.tab.c"
    break;

  case 85: /* iterative_statement: WHILE_TOK error expression RPAREN_TOK statement  */
#line 369 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in while loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2091 "y.tab.c"
    break;

  case 86: /* iterative_statement: FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition SEMICOLON_TOK for_update error statement  */
#line 375 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in for loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2101 "y.tab.c"
    break;

  case 87: /* iterative_statement: FOR_TOK LPAREN_TOK for_init error for_condition SEMICOLON_TOK for_update RPAREN_TOK statement  */
#line 381 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' in for loop initialization\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2111 "y.tab.c"
    break;

  case 88: /* iterative_statement: FOR_TOK LPAREN_TOK for_init SEMICOLON_TOK for_condition error for_update RPAREN_TOK statement  */
#line 387 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' in for loop condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2121 "y.tab.c"
    break;

  case 89: /* iterative_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK error  */
#line 393 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after do-while loop\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2131 "y.tab.c"
    break;

  case 97: /* declaration_expression: data_type ID_TOK ASSIGN_TOK expression  */
#line 414 "parse.y"
                       { print_syntax_success("For loop variable declaration"); }
#line 2137 "y.tab.c"
    break;

  case 109: /* return_statement: RETURN_TOK SEMICOLON_TOK  */
#line 432 "parse.y"
                 { print_syntax_success("Return statement"); }
#line 2143 "y.tab.c"
    break;

  case 110: /* return_statement: RETURN_TOK expression SEMICOLON_TOK  */
#line 434 "parse.y"
                 { print_syntax_success("Return statement with value"); }
#line 2149 "y.tab.c"
    break;

  case 111: /* return_statement: RETURN_TOK expression error  */
#line 436 "parse.y"
                 {
                   printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return statement\n", line_number);
                   error_count++;
                   yyerrok;
                 }
#line 2159 "y.tab.c"
    break;

  case 112: /* return_statement: RETURN_TOK error  */
#line 442 "parse.y"
                 {
                   printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return\n", line_number);
                   error_count++;
                   yyerrok;
                 }
#line 2169 "y.tab.c"
    break;

  case 161: /* postfix_expr: postfix_expr LBRACKET_TOK expression error  */
#line 529 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing bracket ']'\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2179 "y.tab.c"
    break;

  case 162: /* postfix_expr: postfix_expr LBRACKET_TOK error RBRACKET_TOK  */
#line 535 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid array index expression\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2189 "y.tab.c"
    break;

  case 163: /* postfix_expr: postfix_expr LPAREN_TOK RPAREN_TOK  */
#line 541 "parse.y"
              { print_syntax_success("Function call"); }
#line 2195 "y.tab.c"
    break;

  case 164: /* postfix_expr: postfix_expr LPAREN_TOK argument_list RPAREN_TOK  */
#line 543 "parse.y"
              { print_syntax_success("Function call with arguments"); }
#line 2201 "y.tab.c"
    break;

  case 165: /* postfix_expr: postfix_expr LPAREN_TOK argument_list error  */
#line 545 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function call\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2211 "y.tab.c"
    break;

  case 166: /* postfix_expr: postfix_expr LPAREN_TOK error RPAREN_TOK  */
#line 551 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2221 "y.tab.c"
    break;

  case 171: /* argument_list: argument_list error expression  */
#line 563 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing comma ',' between function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2231 "y.tab.c"
    break;

  case 172: /* argument_list: argument_list COMMA_TOK error  */
#line 569 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression after comma in argument list\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2241 "y.tab.c"
    break;

  case 178: /* primary_expr: LPAREN_TOK expression error  */
#line 582 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')'\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2251 "y.tab.c"
    break;

  case 179: /* primary_expr: LPAREN_TOK error RPAREN_TOK  */
#line 588 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression inside parentheses\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2261 "y.tab.c"
    break;


#line 2265 "y.tab.c"

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

#line 595 "parse.y"


#include "lex.yy.c"

int main() {
    printf("=== C LANGUAGE SUBSET PARSER ===\n");
    printf("Parsing input...\n\n");
    
    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No syntax errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Syntax errors found at line %d\n", line_number);
    }
    
    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}

