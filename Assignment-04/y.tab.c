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
#include "symbol_table.h"

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
int scope_level = 0;
int function_declared = 0;
data_type_t current_type = TYPE_UNKNOWN;

void print_syntax_success(char* construct) {
    printf("SYNTAX OK (Line %d): %s\n", line_number, construct);
}

data_type_t token_to_type(int token) {
    switch(token) {
        case INT_TOK: return TYPE_INT;
        case FLOAT_TOK: return TYPE_FLOAT;
        case CHAR_TOK: return TYPE_CHAR;
        case VOID_TOK: return TYPE_VOID;
        default: return TYPE_UNKNOWN;
    }
}

scope_type_t get_current_scope_type() {
    if (sym_table.current_scope_level == 0) return SCOPE_GLOBAL;
    else if (sym_table.current_scope_level == 1) return SCOPE_FUNCTION;
    else return SCOPE_BLOCK;
}

#line 108 "y.tab.c"

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
    VOID_TOK = 261,                /* VOID_TOK  */
    WHILE_TOK = 262,               /* WHILE_TOK  */
    FOR_TOK = 263,                 /* FOR_TOK  */
    DO_TOK = 264,                  /* DO_TOK  */
    IF_TOK = 265,                  /* IF_TOK  */
    ELSE_TOK = 266,                /* ELSE_TOK  */
    RETURN_TOK = 267,              /* RETURN_TOK  */
    ID_TOK = 268,                  /* ID_TOK  */
    STRING_TOK = 269,              /* STRING_TOK  */
    INTCONST_TOK = 270,            /* INTCONST_TOK  */
    FLOATCONST_TOK = 271,          /* FLOATCONST_TOK  */
    ADD_TOK = 272,                 /* ADD_TOK  */
    SUB_TOK = 273,                 /* SUB_TOK  */
    MUL_TOK = 274,                 /* MUL_TOK  */
    DIV_TOK = 275,                 /* DIV_TOK  */
    MOD_TOK = 276,                 /* MOD_TOK  */
    LT_TOK = 277,                  /* LT_TOK  */
    GT_TOK = 278,                  /* GT_TOK  */
    LE_TOK = 279,                  /* LE_TOK  */
    GE_TOK = 280,                  /* GE_TOK  */
    EQ_TOK = 281,                  /* EQ_TOK  */
    NEQ_TOK = 282,                 /* NEQ_TOK  */
    AND_TOK = 283,                 /* AND_TOK  */
    OR_TOK = 284,                  /* OR_TOK  */
    NOT_TOK = 285,                 /* NOT_TOK  */
    BIT_AND_TOK = 286,             /* BIT_AND_TOK  */
    BIT_OR_TOK = 287,              /* BIT_OR_TOK  */
    BIT_XOR_TOK = 288,             /* BIT_XOR_TOK  */
    BIT_NOT_TOK = 289,             /* BIT_NOT_TOK  */
    BIT_LSHIFT_TOK = 290,          /* BIT_LSHIFT_TOK  */
    BIT_RSHIFT_TOK = 291,          /* BIT_RSHIFT_TOK  */
    ASSIGN_TOK = 292,              /* ASSIGN_TOK  */
    ADD_ASSIGN_TOK = 293,          /* ADD_ASSIGN_TOK  */
    SUB_ASSIGN_TOK = 294,          /* SUB_ASSIGN_TOK  */
    MUL_ASSIGN_TOK = 295,          /* MUL_ASSIGN_TOK  */
    DIV_ASSIGN_TOK = 296,          /* DIV_ASSIGN_TOK  */
    MOD_ASSIGN_TOK = 297,          /* MOD_ASSIGN_TOK  */
    INC_TOK = 298,                 /* INC_TOK  */
    DEC_TOK = 299,                 /* DEC_TOK  */
    TERNARY_TOK = 300,             /* TERNARY_TOK  */
    COLON_TOK = 301,               /* COLON_TOK  */
    LPAREN_TOK = 302,              /* LPAREN_TOK  */
    RPAREN_TOK = 303,              /* RPAREN_TOK  */
    LBRACE_TOK = 304,              /* LBRACE_TOK  */
    RBRACE_TOK = 305,              /* RBRACE_TOK  */
    LBRACKET_TOK = 306,            /* LBRACKET_TOK  */
    RBRACKET_TOK = 307,            /* RBRACKET_TOK  */
    SEMICOLON_TOK = 308,           /* SEMICOLON_TOK  */
    COMMA_TOK = 309,               /* COMMA_TOK  */
    ERROR_TOK = 310,               /* ERROR_TOK  */
    ID_TOO_LONG_ERROR = 311,       /* ID_TOO_LONG_ERROR  */
    NUM_TOO_LONG_ERROR = 312,      /* NUM_TOO_LONG_ERROR  */
    ILLEGAL_CHAR_ERROR = 313,      /* ILLEGAL_CHAR_ERROR  */
    UNMATCHED_STRING_ERROR = 314,  /* UNMATCHED_STRING_ERROR  */
    SPELLING_ERROR = 315,          /* SPELLING_ERROR  */
    INVALID_NUM_ERROR = 316,       /* INVALID_NUM_ERROR  */
    UNARY_MINUS = 317,             /* UNARY_MINUS  */
    UNARY_PLUS = 318               /* UNARY_PLUS  */
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
#define VOID_TOK 261
#define WHILE_TOK 262
#define FOR_TOK 263
#define DO_TOK 264
#define IF_TOK 265
#define ELSE_TOK 266
#define RETURN_TOK 267
#define ID_TOK 268
#define STRING_TOK 269
#define INTCONST_TOK 270
#define FLOATCONST_TOK 271
#define ADD_TOK 272
#define SUB_TOK 273
#define MUL_TOK 274
#define DIV_TOK 275
#define MOD_TOK 276
#define LT_TOK 277
#define GT_TOK 278
#define LE_TOK 279
#define GE_TOK 280
#define EQ_TOK 281
#define NEQ_TOK 282
#define AND_TOK 283
#define OR_TOK 284
#define NOT_TOK 285
#define BIT_AND_TOK 286
#define BIT_OR_TOK 287
#define BIT_XOR_TOK 288
#define BIT_NOT_TOK 289
#define BIT_LSHIFT_TOK 290
#define BIT_RSHIFT_TOK 291
#define ASSIGN_TOK 292
#define ADD_ASSIGN_TOK 293
#define SUB_ASSIGN_TOK 294
#define MUL_ASSIGN_TOK 295
#define DIV_ASSIGN_TOK 296
#define MOD_ASSIGN_TOK 297
#define INC_TOK 298
#define DEC_TOK 299
#define TERNARY_TOK 300
#define COLON_TOK 301
#define LPAREN_TOK 302
#define RPAREN_TOK 303
#define LBRACE_TOK 304
#define RBRACE_TOK 305
#define LBRACKET_TOK 306
#define RBRACKET_TOK 307
#define SEMICOLON_TOK 308
#define COMMA_TOK 309
#define ERROR_TOK 310
#define ID_TOO_LONG_ERROR 311
#define NUM_TOO_LONG_ERROR 312
#define ILLEGAL_CHAR_ERROR 313
#define UNMATCHED_STRING_ERROR 314
#define SPELLING_ERROR 315
#define INVALID_NUM_ERROR 316
#define UNARY_MINUS 317
#define UNARY_PLUS 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "parse.y"

    int int_val;
    float float_val;
    char* string_val;
    int type_val;

#line 294 "y.tab.c"

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
  YYSYMBOL_INT_TOK = 3,                    /* INT_TOK  */
  YYSYMBOL_FLOAT_TOK = 4,                  /* FLOAT_TOK  */
  YYSYMBOL_CHAR_TOK = 5,                   /* CHAR_TOK  */
  YYSYMBOL_VOID_TOK = 6,                   /* VOID_TOK  */
  YYSYMBOL_WHILE_TOK = 7,                  /* WHILE_TOK  */
  YYSYMBOL_FOR_TOK = 8,                    /* FOR_TOK  */
  YYSYMBOL_DO_TOK = 9,                     /* DO_TOK  */
  YYSYMBOL_IF_TOK = 10,                    /* IF_TOK  */
  YYSYMBOL_ELSE_TOK = 11,                  /* ELSE_TOK  */
  YYSYMBOL_RETURN_TOK = 12,                /* RETURN_TOK  */
  YYSYMBOL_ID_TOK = 13,                    /* ID_TOK  */
  YYSYMBOL_STRING_TOK = 14,                /* STRING_TOK  */
  YYSYMBOL_INTCONST_TOK = 15,              /* INTCONST_TOK  */
  YYSYMBOL_FLOATCONST_TOK = 16,            /* FLOATCONST_TOK  */
  YYSYMBOL_ADD_TOK = 17,                   /* ADD_TOK  */
  YYSYMBOL_SUB_TOK = 18,                   /* SUB_TOK  */
  YYSYMBOL_MUL_TOK = 19,                   /* MUL_TOK  */
  YYSYMBOL_DIV_TOK = 20,                   /* DIV_TOK  */
  YYSYMBOL_MOD_TOK = 21,                   /* MOD_TOK  */
  YYSYMBOL_LT_TOK = 22,                    /* LT_TOK  */
  YYSYMBOL_GT_TOK = 23,                    /* GT_TOK  */
  YYSYMBOL_LE_TOK = 24,                    /* LE_TOK  */
  YYSYMBOL_GE_TOK = 25,                    /* GE_TOK  */
  YYSYMBOL_EQ_TOK = 26,                    /* EQ_TOK  */
  YYSYMBOL_NEQ_TOK = 27,                   /* NEQ_TOK  */
  YYSYMBOL_AND_TOK = 28,                   /* AND_TOK  */
  YYSYMBOL_OR_TOK = 29,                    /* OR_TOK  */
  YYSYMBOL_NOT_TOK = 30,                   /* NOT_TOK  */
  YYSYMBOL_BIT_AND_TOK = 31,               /* BIT_AND_TOK  */
  YYSYMBOL_BIT_OR_TOK = 32,                /* BIT_OR_TOK  */
  YYSYMBOL_BIT_XOR_TOK = 33,               /* BIT_XOR_TOK  */
  YYSYMBOL_BIT_NOT_TOK = 34,               /* BIT_NOT_TOK  */
  YYSYMBOL_BIT_LSHIFT_TOK = 35,            /* BIT_LSHIFT_TOK  */
  YYSYMBOL_BIT_RSHIFT_TOK = 36,            /* BIT_RSHIFT_TOK  */
  YYSYMBOL_ASSIGN_TOK = 37,                /* ASSIGN_TOK  */
  YYSYMBOL_ADD_ASSIGN_TOK = 38,            /* ADD_ASSIGN_TOK  */
  YYSYMBOL_SUB_ASSIGN_TOK = 39,            /* SUB_ASSIGN_TOK  */
  YYSYMBOL_MUL_ASSIGN_TOK = 40,            /* MUL_ASSIGN_TOK  */
  YYSYMBOL_DIV_ASSIGN_TOK = 41,            /* DIV_ASSIGN_TOK  */
  YYSYMBOL_MOD_ASSIGN_TOK = 42,            /* MOD_ASSIGN_TOK  */
  YYSYMBOL_INC_TOK = 43,                   /* INC_TOK  */
  YYSYMBOL_DEC_TOK = 44,                   /* DEC_TOK  */
  YYSYMBOL_TERNARY_TOK = 45,               /* TERNARY_TOK  */
  YYSYMBOL_COLON_TOK = 46,                 /* COLON_TOK  */
  YYSYMBOL_LPAREN_TOK = 47,                /* LPAREN_TOK  */
  YYSYMBOL_RPAREN_TOK = 48,                /* RPAREN_TOK  */
  YYSYMBOL_LBRACE_TOK = 49,                /* LBRACE_TOK  */
  YYSYMBOL_RBRACE_TOK = 50,                /* RBRACE_TOK  */
  YYSYMBOL_LBRACKET_TOK = 51,              /* LBRACKET_TOK  */
  YYSYMBOL_RBRACKET_TOK = 52,              /* RBRACKET_TOK  */
  YYSYMBOL_SEMICOLON_TOK = 53,             /* SEMICOLON_TOK  */
  YYSYMBOL_COMMA_TOK = 54,                 /* COMMA_TOK  */
  YYSYMBOL_ERROR_TOK = 55,                 /* ERROR_TOK  */
  YYSYMBOL_ID_TOO_LONG_ERROR = 56,         /* ID_TOO_LONG_ERROR  */
  YYSYMBOL_NUM_TOO_LONG_ERROR = 57,        /* NUM_TOO_LONG_ERROR  */
  YYSYMBOL_ILLEGAL_CHAR_ERROR = 58,        /* ILLEGAL_CHAR_ERROR  */
  YYSYMBOL_UNMATCHED_STRING_ERROR = 59,    /* UNMATCHED_STRING_ERROR  */
  YYSYMBOL_SPELLING_ERROR = 60,            /* SPELLING_ERROR  */
  YYSYMBOL_INVALID_NUM_ERROR = 61,         /* INVALID_NUM_ERROR  */
  YYSYMBOL_UNARY_MINUS = 62,               /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 63,                /* UNARY_PLUS  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_program = 65,                   /* program  */
  YYSYMBOL_66_1 = 66,                      /* $@1  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_global_declarations = 69,       /* global_declarations  */
  YYSYMBOL_global_declaration = 70,        /* global_declaration  */
  YYSYMBOL_71_4 = 71,                      /* $@4  */
  YYSYMBOL_data_type = 72,                 /* data_type  */
  YYSYMBOL_declarator_list = 73,           /* declarator_list  */
  YYSYMBOL_declarator = 74,                /* declarator  */
  YYSYMBOL_main_function = 75,             /* main_function  */
  YYSYMBOL_76_5 = 76,                      /* $@5  */
  YYSYMBOL_77_6 = 77,                      /* $@6  */
  YYSYMBOL_user_functions = 78,            /* user_functions  */
  YYSYMBOL_user_function = 79,             /* user_function  */
  YYSYMBOL_function_declaration = 80,      /* function_declaration  */
  YYSYMBOL_81_7 = 81,                      /* $@7  */
  YYSYMBOL_82_8 = 82,                      /* $@8  */
  YYSYMBOL_function_definition = 83,       /* function_definition  */
  YYSYMBOL_84_9 = 84,                      /* $@9  */
  YYSYMBOL_85_10 = 85,                     /* $@10  */
  YYSYMBOL_parameter_list = 86,            /* parameter_list  */
  YYSYMBOL_parameter = 87,                 /* parameter  */
  YYSYMBOL_compound_statement = 88,        /* compound_statement  */
  YYSYMBOL_89_11 = 89,                     /* $@11  */
  YYSYMBOL_90_12 = 90,                     /* $@12  */
  YYSYMBOL_statement_list = 91,            /* statement_list  */
  YYSYMBOL_statement = 92,                 /* statement  */
  YYSYMBOL_declaration_statement = 93,     /* declaration_statement  */
  YYSYMBOL_94_13 = 94,                     /* $@13  */
  YYSYMBOL_expression_statement = 95,      /* expression_statement  */
  YYSYMBOL_selection_statement = 96,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 97,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 98,            /* jump_statement  */
  YYSYMBOL_expression = 99,                /* expression  */
  YYSYMBOL_assignment_expr = 100,          /* assignment_expr  */
  YYSYMBOL_ternary_expr = 101,             /* ternary_expr  */
  YYSYMBOL_logical_or_expr = 102,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 103,         /* logical_and_expr  */
  YYSYMBOL_bit_or_expr = 104,              /* bit_or_expr  */
  YYSYMBOL_bit_xor_expr = 105,             /* bit_xor_expr  */
  YYSYMBOL_bit_and_expr = 106,             /* bit_and_expr  */
  YYSYMBOL_equality_expr = 107,            /* equality_expr  */
  YYSYMBOL_relational_expr = 108,          /* relational_expr  */
  YYSYMBOL_shift_expr = 109,               /* shift_expr  */
  YYSYMBOL_additive_expr = 110,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 111,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 112,               /* unary_expr  */
  YYSYMBOL_unary_operator = 113,           /* unary_operator  */
  YYSYMBOL_postfix_expr = 114,             /* postfix_expr  */
  YYSYMBOL_argument_list = 115,            /* argument_list  */
  YYSYMBOL_primary_expr = 116              /* primary_expr  */
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   757

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    97,    97,    97,   104,   104,   111,   111,   121,   122,
     125,   125,   127,   129,   135,   141,   150,   151,   152,   153,
     157,   158,   159,   165,   173,   181,   190,   199,   205,   214,
     214,   227,   227,   243,   244,   245,   248,   249,   252,   252,
     260,   260,   270,   270,   282,   282,   297,   298,   299,   305,
     313,   321,   333,   333,   338,   338,   343,   349,   358,   359,
     363,   364,   365,   366,   367,   368,   369,   378,   378,   380,
     389,   391,   393,   402,   404,   406,   412,   418,   427,   429,
     431,   433,   435,   441,   450,   452,   454,   460,   469,   470,
     471,   477,   485,   486,   487,   488,   489,   490,   491,   492,
     498,   506,   507,   508,   514,   520,   528,   529,   532,   533,
     536,   537,   540,   541,   544,   545,   548,   549,   550,   553,
     554,   555,   556,   557,   560,   561,   562,   565,   566,   567,
     570,   571,   572,   573,   576,   577,   578,   579,   582,   583,
     584,   585,   588,   589,   590,   596,   602,   604,   606,   612,
     618,   619,   622,   623,   624,   630,   638,   651,   652,   653,
     654,   655,   661
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
  "CHAR_TOK", "VOID_TOK", "WHILE_TOK", "FOR_TOK", "DO_TOK", "IF_TOK",
  "ELSE_TOK", "RETURN_TOK", "ID_TOK", "STRING_TOK", "INTCONST_TOK",
  "FLOATCONST_TOK", "ADD_TOK", "SUB_TOK", "MUL_TOK", "DIV_TOK", "MOD_TOK",
  "LT_TOK", "GT_TOK", "LE_TOK", "GE_TOK", "EQ_TOK", "NEQ_TOK", "AND_TOK",
  "OR_TOK", "NOT_TOK", "BIT_AND_TOK", "BIT_OR_TOK", "BIT_XOR_TOK",
  "BIT_NOT_TOK", "BIT_LSHIFT_TOK", "BIT_RSHIFT_TOK", "ASSIGN_TOK",
  "ADD_ASSIGN_TOK", "SUB_ASSIGN_TOK", "MUL_ASSIGN_TOK", "DIV_ASSIGN_TOK",
  "MOD_ASSIGN_TOK", "INC_TOK", "DEC_TOK", "TERNARY_TOK", "COLON_TOK",
  "LPAREN_TOK", "RPAREN_TOK", "LBRACE_TOK", "RBRACE_TOK", "LBRACKET_TOK",
  "RBRACKET_TOK", "SEMICOLON_TOK", "COMMA_TOK", "ERROR_TOK",
  "ID_TOO_LONG_ERROR", "NUM_TOO_LONG_ERROR", "ILLEGAL_CHAR_ERROR",
  "UNMATCHED_STRING_ERROR", "SPELLING_ERROR", "INVALID_NUM_ERROR",
  "UNARY_MINUS", "UNARY_PLUS", "$accept", "program", "$@1", "$@2", "$@3",
  "global_declarations", "global_declaration", "$@4", "data_type",
  "declarator_list", "declarator", "main_function", "$@5", "$@6",
  "user_functions", "user_function", "function_declaration", "$@7", "$@8",
  "function_definition", "$@9", "$@10", "parameter_list", "parameter",
  "compound_statement", "$@11", "$@12", "statement_list", "statement",
  "declaration_statement", "$@13", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "expression", "assignment_expr", "ternary_expr", "logical_or_expr",
  "logical_and_expr", "bit_or_expr", "bit_xor_expr", "bit_and_expr",
  "equality_expr", "relational_expr", "shift_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "unary_operator", "postfix_expr",
  "argument_list", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-155)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -145,     9,   252,   293,   293,  -145,    18,  -145,  -145,  -145,
    -145,   252,  -145,    32,  -145,    38,   293,  -145,    62,     7,
    -145,  -145,    33,   293,    13,   -15,    18,    23,  -145,   102,
     293,  -145,  -145,  -145,    15,    18,  -145,    34,    95,   293,
    -145,    83,    88,    17,    18,    98,   105,  -145,  -145,    97,
      26,  -145,  -145,  -145,  -145,   114,   293,  -145,   185,   293,
     221,   224,  -145,  -145,  -145,   206,   253,    21,  -145,   233,
      25,   222,   293,  -145,   240,   293,   247,   289,   271,  -145,
     233,   233,    28,   250,  -145,  -145,  -145,  -145,    87,   256,
     257,   373,     5,   446,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,   710,   710,   490,  -145,    18,  -145,   373,   266,
     424,  -145,  -145,  -145,  -145,  -145,  -145,    47,  -145,  -145,
      79,   291,   285,   300,   314,   129,   284,   194,   154,   223,
     186,   710,   107,  -145,  -145,  -145,   233,  -145,  -145,  -145,
     512,   666,   269,   339,   710,   534,   294,  -145,    56,  -145,
    -145,   301,    64,   183,    18,   322,  -145,   269,  -145,   710,
    -145,   556,   710,   710,   578,   710,   710,   710,   710,   710,
     710,   710,   710,   710,   710,   710,   710,   710,   710,   710,
     710,   710,   710,   600,   710,   710,   710,   710,   710,  -145,
    -145,  -145,   468,   622,  -145,   302,   135,   666,   304,   138,
     305,   143,  -145,   710,  -145,  -145,   710,  -145,    18,   116,
    -145,  -145,  -145,  -145,   127,   291,  -145,   308,   142,   285,
     300,   314,   129,   284,   284,   194,   194,   194,   194,   154,
     154,   223,   223,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,   307,  -145,   193,   197,   296,    52,
     373,   373,   373,   688,   710,   710,   373,   373,   373,   373,
    -145,   710,   710,   710,   710,  -145,   710,  -145,   644,  -145,
     710,  -145,  -145,  -145,   309,  -145,   373,   198,   200,  -145,
    -145,  -145,   347,  -145,  -145,   212,  -145,   215,  -145,   219,
    -145,   373,   306,   373,  -145,  -145,  -145
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     1,     0,    16,    17,    18,
      19,     0,     9,     0,    12,     0,    35,     7,    24,     0,
      21,     8,     0,    35,     0,    24,     0,     0,    29,     0,
       5,    34,    36,    37,     0,     0,    15,     0,    24,     3,
      14,     0,     0,     0,    13,     0,     0,    38,    33,     0,
       0,    26,    22,    23,    20,     0,     0,    11,     0,     0,
       0,     0,    28,    27,    25,     0,     0,     0,    47,     0,
       0,     0,     0,    39,    50,     0,     0,     0,     0,    30,
       0,     0,     0,     0,    48,    41,    49,    46,     0,     0,
       0,     0,     0,     0,   156,   159,   157,   158,   138,   139,
     140,   141,     0,     0,     0,    71,     0,    62,     0,     0,
       0,    59,    60,    61,    63,    64,    65,     0,    88,    92,
       0,   106,   108,   110,   112,   114,   116,   119,   124,   127,
       0,     0,   134,   142,    32,    43,     0,    51,    57,    66,
       0,     0,     0,     0,     0,     0,     0,    85,     0,   135,
     136,     0,     0,     0,     0,     0,    55,    56,    58,    72,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     150,   151,     0,     0,    45,     0,     0,     0,     0,     0,
       0,     0,    87,    86,    84,   162,   161,   160,    69,     0,
      53,    90,    91,    89,     0,   107,   130,     0,     0,   109,
     111,   113,   115,   117,   118,   120,   121,   122,   123,   125,
     126,   128,   129,   131,   132,   133,    99,   100,    93,    94,
      95,    96,    97,    98,     0,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,   149,   148,   147,     0,   145,
     144,   143,    83,    82,    88,    78,     0,     0,     0,    77,
      76,    75,    73,   105,   104,    92,   102,     0,   155,     0,
      79,     0,     0,     0,    80,    81,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,  -145,  -145,  -145,  -145,   349,  -145,   118,    -1,
     -33,   112,  -145,  -145,   338,    -2,   136,  -145,  -145,  -145,
    -145,  -145,   -49,   -19,   -68,  -145,  -145,   254,   -91,  -145,
    -145,  -134,  -145,  -145,  -145,   -90,  -144,    49,  -145,   201,
     202,   204,   196,   205,    66,   170,    74,    84,   -82,  -145,
    -145,  -145,  -145
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     3,     4,    11,    12,    26,   106,    27,
      20,    16,    45,    46,    30,    31,    32,    41,    42,    33,
      60,    61,    67,    68,   107,   108,   109,   110,   111,   112,
     154,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   247,   133
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     143,    79,    52,   148,    54,    19,   144,   197,    35,     5,
      70,    52,   134,   135,   152,   211,    49,   213,    35,   158,
     149,   150,    75,    82,    44,    43,    75,    63,    48,    75,
      50,    18,   -38,    24,    24,    53,    34,    48,   236,   238,
     239,   240,   241,   242,   243,    25,    38,    18,   159,   189,
     196,    28,   145,   270,   199,   201,    84,   203,    87,   211,
      36,    37,   211,   253,   158,   206,    40,    51,   194,    76,
      57,    37,   214,    80,   218,    77,   136,    37,    64,    77,
     162,   216,    77,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   233,   234,   235,
     160,   161,   246,   249,   271,   153,   161,   274,   163,   204,
     161,   211,   207,    34,   274,    47,    17,    35,   161,   211,
      13,    15,    15,    23,   164,  -101,   211,  -101,   255,    22,
      55,  -101,  -101,  -101,    29,    56,   251,   138,    14,   255,
     139,    29,   -29,   263,   258,    58,    34,    14,    29,    62,
     190,   191,    59,   209,   192,   169,   170,    29,   193,   272,
     273,   275,    65,   277,   278,   279,   280,   281,   282,   260,
      37,   177,   178,   261,    66,    52,   287,    66,   289,   216,
     216,   161,   216,   252,   208,   290,   256,   182,   264,   161,
      66,   259,   161,    66,   255,    66,   161,   161,   266,   255,
     294,   255,   296,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,   255,  -130,  -130,  -130,
     255,  -130,  -130,   183,   184,   185,   186,   187,   188,   175,
     176,  -130,  -130,    69,  -130,   223,   224,    37,  -130,  -130,
    -130,  -153,   179,   180,   181,   267,   291,   161,   292,   229,
     230,   268,   161,     6,   161,     7,     8,     9,    10,    73,
    -103,   231,   232,  -154,  -103,  -103,    74,  -152,    71,   161,
      81,    72,    88,   161,     7,     8,     9,    10,    89,    90,
      91,    92,    78,    93,    94,    95,    96,    97,    98,    99,
      86,    83,     7,     8,     9,    10,     7,     8,     9,    10,
      85,   100,   137,   140,   141,   101,   171,   172,   173,   174,
     283,   284,   285,   286,   102,   103,   156,   166,   104,   165,
      78,   -54,   139,   142,   105,     7,     8,     9,    10,    89,
      90,    91,    92,   167,    93,    94,    95,    96,    97,    98,
      99,   225,   226,   227,   228,   168,   198,   202,   269,   205,
     250,   254,   100,   257,   262,   265,   101,   -90,   293,   295,
      21,    39,   155,   221,   215,   102,   103,   219,     0,   104,
     220,    78,   210,   222,   142,   105,     7,     8,     9,    10,
      89,    90,    91,    92,     0,    93,    94,    95,    96,    97,
      98,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   100,     0,     0,     0,   101,     0,     0,
       0,     0,     0,     0,     0,     0,   102,   103,     0,     0,
     104,     0,    78,     0,     0,   157,   105,     7,     8,     9,
      10,    89,    90,    91,    92,     0,    93,    94,    95,    96,
      97,    98,    99,     0,     0,     0,     0,   146,     0,     0,
       0,     0,     0,     0,   100,     0,     0,     0,   101,    94,
      95,    96,    97,    98,    99,     0,     0,   102,   103,   244,
       0,   104,     0,    78,     0,     0,   100,   105,     0,     0,
     101,    94,    95,    96,    97,    98,    99,     0,     0,   102,
     103,   151,     0,   104,     0,     0,     0,     0,   100,   147,
       0,     0,   101,    94,    95,    96,    97,    98,    99,     0,
       0,   102,   103,   195,     0,   104,   245,     0,     0,     0,
     100,     0,     0,     0,   101,    94,    95,    96,    97,    98,
      99,     0,     0,   102,   103,   200,     0,   104,     0,     0,
       0,     0,   100,     0,     0,     0,   101,    94,    95,    96,
      97,    98,    99,     0,     0,   102,   103,   212,     0,   104,
       0,     0,     0,     0,   100,     0,     0,     0,   101,    94,
      95,    96,    97,    98,    99,     0,     0,   102,   103,   217,
       0,   104,     0,     0,     0,     0,   100,     0,     0,     0,
     101,    94,    95,    96,    97,    98,    99,     0,     0,   102,
     103,   237,     0,   104,     0,     0,     0,     0,   100,     0,
       0,     0,   101,    94,    95,    96,    97,    98,    99,     0,
       0,   102,   103,   248,     0,   104,     0,     0,     0,     0,
     100,     0,     0,     0,   101,    94,    95,    96,    97,    98,
      99,     0,     0,   102,   103,   288,     0,   104,     0,     0,
       0,     0,   100,     0,     0,     0,   101,    94,    95,    96,
      97,    98,    99,     0,     0,   102,   103,     0,     0,   104,
       0,     0,     0,     0,   100,     0,     0,     0,   101,    94,
      95,    96,    97,    98,    99,     0,     0,   102,   103,     0,
       0,   104,     0,     0,     0,     0,   100,     0,     0,     0,
     101,    94,    95,    96,    97,    98,    99,     0,     0,   102,
     103,     0,     0,   104,     0,     0,     0,     0,   100,   105,
       0,     0,   101,    94,    95,    96,    97,    98,    99,     0,
       0,   102,   103,     0,     0,   104,   276,     0,     0,     0,
     100,     0,     0,     0,   101,     0,     0,     0,     0,     0,
       0,     0,     0,   102,   103,     0,     0,   104
};

static const yytype_int16 yycheck[] =
{
      91,    69,    35,    93,    37,     6,     1,   141,     1,     0,
      59,    44,    80,    81,   104,   159,     1,   161,     1,   110,
     102,   103,     1,    72,     1,    26,     1,     1,    30,     1,
      15,    13,    47,     1,     1,     1,    51,    39,   182,   183,
     184,   185,   186,   187,   188,    13,    13,    13,     1,   131,
     140,    13,    47,     1,   144,   145,    75,     1,    77,   203,
      53,    54,   206,   197,   155,     1,    53,    52,   136,    48,
      53,    54,   162,    48,   164,    54,    48,    54,    52,    54,
       1,   163,    54,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
      53,    54,   192,   193,    52,   106,    54,   251,    29,    53,
      54,   255,    48,    51,   258,    13,     4,     1,    54,   263,
       2,     3,     4,    11,    45,    46,   270,    48,     1,    11,
      47,    52,    53,    54,    16,    47,     1,    50,     2,     1,
      53,    23,    47,     1,     1,    47,    51,    11,    30,    52,
      43,    44,    47,   154,    47,    26,    27,    39,    51,   250,
     251,   252,    48,   253,   254,   256,   257,   258,   259,    53,
      54,    17,    18,    46,    56,   208,   266,    59,   268,   261,
     262,    54,   264,    48,     1,   276,    48,     1,    46,    54,
      72,    48,    54,    75,     1,    77,    54,    54,     1,     1,
     291,     1,   293,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,     1,    31,    32,    33,
       1,    35,    36,    37,    38,    39,    40,    41,    42,    35,
      36,    45,    46,    48,    48,   169,   170,    54,    52,    53,
      54,    48,    19,    20,    21,    48,    48,    54,    48,   175,
     176,    54,    54,     1,    54,     3,     4,     5,     6,    53,
      48,   177,   178,    48,    52,    53,    13,    48,    47,    54,
      48,    47,     1,    54,     3,     4,     5,     6,     7,     8,
       9,    10,    49,    12,    13,    14,    15,    16,    17,    18,
       1,    51,     3,     4,     5,     6,     3,     4,     5,     6,
      53,    30,    52,    47,    47,    34,    22,    23,    24,    25,
     261,   262,   263,   264,    43,    44,    50,    32,    47,    28,
      49,    50,    53,     1,    53,     3,     4,     5,     6,     7,
       8,     9,    10,    33,    12,    13,    14,    15,    16,    17,
      18,   171,   172,   173,   174,    31,     7,    53,    52,    48,
      48,    47,    30,    48,    46,    48,    34,    48,    11,    53,
      11,    23,   108,   167,   163,    43,    44,   165,    -1,    47,
     166,    49,    50,   168,     1,    53,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    14,    15,    16,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    -1,
      47,    -1,    49,    -1,    -1,     1,    53,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    13,
      14,    15,    16,    17,    18,    -1,    -1,    43,    44,     1,
      -1,    47,    -1,    49,    -1,    -1,    30,    53,    -1,    -1,
      34,    13,    14,    15,    16,    17,    18,    -1,    -1,    43,
      44,     1,    -1,    47,    -1,    -1,    -1,    -1,    30,    53,
      -1,    -1,    34,    13,    14,    15,    16,    17,    18,    -1,
      -1,    43,    44,     1,    -1,    47,    48,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    13,    14,    15,    16,    17,
      18,    -1,    -1,    43,    44,     1,    -1,    47,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    34,    13,    14,    15,
      16,    17,    18,    -1,    -1,    43,    44,     1,    -1,    47,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    13,
      14,    15,    16,    17,    18,    -1,    -1,    43,    44,     1,
      -1,    47,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    13,    14,    15,    16,    17,    18,    -1,    -1,    43,
      44,     1,    -1,    47,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    13,    14,    15,    16,    17,    18,    -1,
      -1,    43,    44,     1,    -1,    47,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    13,    14,    15,    16,    17,
      18,    -1,    -1,    43,    44,     1,    -1,    47,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    34,    13,    14,    15,
      16,    17,    18,    -1,    -1,    43,    44,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    13,
      14,    15,    16,    17,    18,    -1,    -1,    43,    44,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,
      34,    13,    14,    15,    16,    17,    18,    -1,    -1,    43,
      44,    -1,    -1,    47,    -1,    -1,    -1,    -1,    30,    53,
      -1,    -1,    34,    13,    14,    15,    16,    17,    18,    -1,
      -1,    43,    44,    -1,    -1,    47,    48,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,    66,    67,    68,     0,     1,     3,     4,     5,
       6,    69,    70,    72,    80,    72,    75,    75,    13,    73,
      74,    70,    72,    75,     1,    13,    71,    73,    13,    72,
      78,    79,    80,    83,    51,     1,    53,    54,    13,    78,
      53,    81,    82,    73,     1,    76,    77,    13,    79,     1,
      15,    52,    74,     1,    74,    47,    47,    53,    47,    47,
      84,    85,    52,     1,    52,    48,    72,    86,    87,    48,
      86,    47,    47,    53,    13,     1,    48,    54,    49,    88,
      48,    48,    86,    51,    87,    53,     1,    87,     1,     7,
       8,     9,    10,    12,    13,    14,    15,    16,    17,    18,
      30,    34,    43,    44,    47,    53,    72,    88,    89,    90,
      91,    92,    93,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   116,    88,    88,    48,    52,    50,    53,
      47,    47,     1,    92,     1,    47,     1,    53,    99,   112,
     112,     1,    99,    73,    94,    91,    50,     1,    92,     1,
      53,    54,     1,    29,    45,    28,    32,    33,    31,    26,
      27,    22,    23,    24,    25,    35,    36,    17,    18,    19,
      20,    21,     1,    37,    38,    39,    40,    41,    42,   112,
      43,    44,    47,    51,    88,     1,    99,    95,     7,    99,
       1,    99,    53,     1,    53,    48,     1,    48,     1,    73,
      50,   100,     1,   100,    99,   103,   112,     1,    99,   104,
     105,   106,   107,   108,   108,   109,   109,   109,   109,   110,
     110,   111,   111,   112,   112,   112,   100,     1,   100,   100,
     100,   100,   100,   100,     1,    48,    99,   115,     1,    99,
      48,     1,    48,    95,    47,     1,    48,    48,     1,    48,
      53,    46,    46,     1,    46,    48,     1,    48,    54,    52,
       1,    52,    92,    92,   100,    92,    48,    99,    99,    92,
      92,    92,    92,   101,   101,   101,   101,    99,     1,    99,
      92,    48,    48,    11,    92,    53,    92
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    66,    65,    67,    65,    68,    65,    69,    69,
      71,    70,    70,    70,    70,    70,    72,    72,    72,    72,
      73,    73,    73,    73,    74,    74,    74,    74,    74,    76,
      75,    77,    75,    78,    78,    78,    79,    79,    81,    80,
      82,    80,    84,    83,    85,    83,    86,    86,    86,    86,
      87,    87,    89,    88,    90,    88,    88,    88,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    94,    93,    93,
      95,    95,    95,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    99,    99,
      99,    99,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   101,   101,   102,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   107,   108,
     108,   108,   108,   108,   109,   109,   109,   110,   110,   110,
     111,   111,   111,   111,   112,   112,   112,   112,   113,   113,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   115,   115,   115,   115,   116,   116,   116,   116,
     116,   116,   116
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     0,     2,     2,     1,
       0,     4,     1,     3,     3,     3,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     4,     3,     4,     4,     0,
       6,     0,     7,     2,     1,     0,     1,     1,     0,     6,
       0,     7,     0,     6,     0,     7,     3,     1,     3,     3,
       2,     4,     0,     4,     0,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     4,     3,
       2,     1,     2,     5,     7,     5,     5,     5,     5,     6,
       7,     7,     5,     5,     3,     2,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     5,     5,     5,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     4,     4,     4,     3,     4,     4,     4,
       2,     2,     3,     1,     3,     3,     1,     1,     1,     1,
       3,     3,     3
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
  case 2: /* $@1: %empty  */
#line 97 "parse.y"
         { init_symbol_table(); }
#line 1700 "y.tab.c"
    break;

  case 3: /* program: $@1 global_declarations main_function user_functions  */
#line 98 "parse.y"
         { 
           print_syntax_success("Complete C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1711 "y.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 104 "parse.y"
         { init_symbol_table(); }
#line 1717 "y.tab.c"
    break;

  case 5: /* program: $@2 main_function user_functions  */
#line 105 "parse.y"
         { 
           print_syntax_success("C program with main function");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1728 "y.tab.c"
    break;

  case 6: /* $@3: %empty  */
#line 111 "parse.y"
         { init_symbol_table(); }
#line 1734 "y.tab.c"
    break;

  case 7: /* program: $@3 main_function  */
#line 112 "parse.y"
         { 
           print_syntax_success("Simple C program with main function only");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1745 "y.tab.c"
    break;

  case 10: /* $@4: %empty  */
#line 125 "parse.y"
                              { current_type = token_to_type((yyvsp[0].type_val)); }
#line 1751 "y.tab.c"
    break;

  case 11: /* global_declaration: data_type $@4 declarator_list SEMICOLON_TOK  */
#line 126 "parse.y"
                   { print_syntax_success("Global variable declaration"); }
#line 1757 "y.tab.c"
    break;

  case 12: /* global_declaration: function_declaration  */
#line 128 "parse.y"
                   { print_syntax_success("Function declaration"); }
#line 1763 "y.tab.c"
    break;

  case 13: /* global_declaration: data_type declarator_list error  */
#line 130 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after variable declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1773 "y.tab.c"
    break;

  case 14: /* global_declaration: data_type error SEMICOLON_TOK  */
#line 136 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid variable declarator list\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1783 "y.tab.c"
    break;

  case 15: /* global_declaration: error declarator_list SEMICOLON_TOK  */
#line 142 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid or missing data type in declaration\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 1793 "y.tab.c"
    break;

  case 16: /* data_type: INT_TOK  */
#line 150 "parse.y"
                   { (yyval.type_val) = INT_TOK; }
#line 1799 "y.tab.c"
    break;

  case 17: /* data_type: FLOAT_TOK  */
#line 151 "parse.y"
                     { (yyval.type_val) = FLOAT_TOK; }
#line 1805 "y.tab.c"
    break;

  case 18: /* data_type: CHAR_TOK  */
#line 152 "parse.y"
                    { (yyval.type_val) = CHAR_TOK; }
#line 1811 "y.tab.c"
    break;

  case 19: /* data_type: VOID_TOK  */
#line 153 "parse.y"
                    { (yyval.type_val) = VOID_TOK; }
#line 1817 "y.tab.c"
    break;

  case 22: /* declarator_list: declarator_list error declarator  */
#line 160 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Missing comma ',' between variable declarations\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1827 "y.tab.c"
    break;

  case 23: /* declarator_list: declarator_list COMMA_TOK error  */
#line 166 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid declarator after comma\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1837 "y.tab.c"
    break;

  case 24: /* declarator: ID_TOK  */
#line 174 "parse.y"
           {
             // Add variable to symbol table
             if (!add_symbol((yyvsp[0].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free((yyvsp[0].string_val));
           }
#line 1849 "y.tab.c"
    break;

  case 25: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK  */
#line 182 "parse.y"
           {
             // Add array variable to symbol table
             if (!add_symbol((yyvsp[-3].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             printf("SYNTAX OK: Array declaration '%s[%d]'\n", (yyvsp[-3].string_val), (yyvsp[-1].int_val));
             free((yyvsp[-3].string_val));
           }
#line 1862 "y.tab.c"
    break;

  case 26: /* declarator: ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 191 "parse.y"
           {
             // Add array variable to symbol table (no size specified)
             if (!add_symbol((yyvsp[-2].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             printf("SYNTAX OK: Array declaration '%s[]'\n", (yyvsp[-2].string_val));
             free((yyvsp[-2].string_val));
           }
#line 1875 "y.tab.c"
    break;

  case 27: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK error  */
#line 200 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Missing closing bracket ']' in array declaration\n", line_number);
             error_count++;
             yyerrok;
           }
#line 1885 "y.tab.c"
    break;

  case 28: /* declarator: ID_TOK LBRACKET_TOK error RBRACKET_TOK  */
#line 206 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Invalid array size\n", line_number);
             error_count++;
             yyerrok;
           }
#line 1895 "y.tab.c"
    break;

  case 29: /* $@5: %empty  */
#line 214 "parse.y"
                                { 
                 // Add function to symbol table
                 if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                     error_count++;
                 }
                 enter_scope();
               }
#line 1907 "y.tab.c"
    break;

  case 30: /* main_function: data_type ID_TOK $@5 LPAREN_TOK RPAREN_TOK compound_statement  */
#line 221 "parse.y"
               { 
                 print_syntax_success("Main function definition");
                 function_declared = 1;
                 exit_scope();
                 free((yyvsp[-4].string_val));
               }
#line 1918 "y.tab.c"
    break;

  case 31: /* $@6: %empty  */
#line 227 "parse.y"
                                { 
                 // Add function to symbol table
                 if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                     error_count++;
                 }
                 enter_scope();
               }
#line 1930 "y.tab.c"
    break;

  case 32: /* main_function: data_type ID_TOK $@6 LPAREN_TOK parameter_list RPAREN_TOK compound_statement  */
#line 234 "parse.y"
               { 
                 print_syntax_success("Main function with parameters");
                 function_declared = 1;
                 exit_scope();
                 free((yyvsp[-5].string_val));
               }
#line 1941 "y.tab.c"
    break;

  case 38: /* $@7: %empty  */
#line 252 "parse.y"
                                       {
                       // Add function declaration to symbol table
                       if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free((yyvsp[0].string_val));
                     }
#line 1953 "y.tab.c"
    break;

  case 39: /* function_declaration: data_type ID_TOK $@7 LPAREN_TOK RPAREN_TOK SEMICOLON_TOK  */
#line 259 "parse.y"
                     { print_syntax_success("Function declaration"); }
#line 1959 "y.tab.c"
    break;

  case 40: /* $@8: %empty  */
#line 260 "parse.y"
                                       {
                       // Add function declaration to symbol table
                       if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free((yyvsp[0].string_val));
                     }
#line 1971 "y.tab.c"
    break;

  case 41: /* function_declaration: data_type ID_TOK $@8 LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK  */
#line 267 "parse.y"
                     { print_syntax_success("Function declaration with parameters"); }
#line 1977 "y.tab.c"
    break;

  case 42: /* $@9: %empty  */
#line 270 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                      enter_scope();
                    }
#line 1989 "y.tab.c"
    break;

  case 43: /* function_definition: data_type ID_TOK $@9 LPAREN_TOK RPAREN_TOK compound_statement  */
#line 277 "parse.y"
                    { 
                      print_syntax_success("Function definition");
                      exit_scope();
                      free((yyvsp[-4].string_val));
                    }
#line 1999 "y.tab.c"
    break;

  case 44: /* $@10: %empty  */
#line 282 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                      enter_scope();
                    }
#line 2011 "y.tab.c"
    break;

  case 45: /* function_definition: data_type ID_TOK $@10 LPAREN_TOK parameter_list RPAREN_TOK compound_statement  */
#line 289 "parse.y"
                    { 
                      print_syntax_success("Function definition with parameters");
                      exit_scope();
                      free((yyvsp[-5].string_val));
                    }
#line 2021 "y.tab.c"
    break;

  case 48: /* parameter_list: parameter_list error parameter  */
#line 300 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Missing comma ',' between parameters\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2031 "y.tab.c"
    break;

  case 49: /* parameter_list: parameter_list COMMA_TOK error  */
#line 306 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Invalid parameter after comma\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2041 "y.tab.c"
    break;

  case 50: /* parameter: data_type ID_TOK  */
#line 314 "parse.y"
          {
            // Add parameter to symbol table
            if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free((yyvsp[0].string_val));
          }
#line 2053 "y.tab.c"
    break;

  case 51: /* parameter: data_type ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 322 "parse.y"
          {
            // Add array parameter to symbol table
            if (!add_symbol((yyvsp[-2].string_val), token_to_type((yyvsp[-3].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            printf("SYNTAX OK: Array parameter '%s[]'\n", (yyvsp[-2].string_val));
            free((yyvsp[-2].string_val));
          }
#line 2066 "y.tab.c"
    break;

  case 52: /* $@11: %empty  */
#line 333 "parse.y"
                               { enter_scope(); }
#line 2072 "y.tab.c"
    break;

  case 53: /* compound_statement: LBRACE_TOK $@11 statement_list RBRACE_TOK  */
#line 334 "parse.y"
                   { 
                     print_syntax_success("Compound statement");
                     exit_scope();
                   }
#line 2081 "y.tab.c"
    break;

  case 54: /* $@12: %empty  */
#line 338 "parse.y"
                               { enter_scope(); }
#line 2087 "y.tab.c"
    break;

  case 55: /* compound_statement: LBRACE_TOK $@12 RBRACE_TOK  */
#line 339 "parse.y"
                   { 
                     print_syntax_success("Empty compound statement");
                     exit_scope();
                   }
#line 2096 "y.tab.c"
    break;

  case 56: /* compound_statement: LBRACE_TOK statement_list error  */
#line 344 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Missing closing brace '}'\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 2106 "y.tab.c"
    break;

  case 57: /* compound_statement: LBRACE_TOK error RBRACE_TOK  */
#line 350 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid statement inside compound statement\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 2116 "y.tab.c"
    break;

  case 66: /* statement: error SEMICOLON_TOK  */
#line 370 "parse.y"
          {
            printf("SYNTAX ERROR (Line %d): Invalid statement\n", line_number);
            error_count++;
            yyerrok;
          }
#line 2126 "y.tab.c"
    break;

  case 67: /* $@13: %empty  */
#line 378 "parse.y"
                                 { current_type = token_to_type((yyvsp[0].type_val)); }
#line 2132 "y.tab.c"
    break;

  case 68: /* declaration_statement: data_type $@13 declarator_list SEMICOLON_TOK  */
#line 379 "parse.y"
                      { print_syntax_success("Local variable declaration"); }
#line 2138 "y.tab.c"
    break;

  case 69: /* declaration_statement: data_type declarator_list error  */
#line 381 "parse.y"
                      {
                        printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after local variable declaration\n", line_number);
                        error_count++;
                        yyerrok;
                      }
#line 2148 "y.tab.c"
    break;

  case 70: /* expression_statement: expression SEMICOLON_TOK  */
#line 390 "parse.y"
                     { print_syntax_success("Expression statement"); }
#line 2154 "y.tab.c"
    break;

  case 71: /* expression_statement: SEMICOLON_TOK  */
#line 392 "parse.y"
                     { print_syntax_success("Empty statement"); }
#line 2160 "y.tab.c"
    break;

  case 72: /* expression_statement: expression error  */
#line 394 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after expression\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 2170 "y.tab.c"
    break;

  case 73: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 403 "parse.y"
                    { print_syntax_success("If statement"); }
#line 2176 "y.tab.c"
    break;

  case 74: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement  */
#line 405 "parse.y"
                    { print_syntax_success("If-else statement"); }
#line 2182 "y.tab.c"
    break;

  case 75: /* selection_statement: IF_TOK LPAREN_TOK expression error statement  */
#line 407 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in if condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2192 "y.tab.c"
    break;

  case 76: /* selection_statement: IF_TOK LPAREN_TOK error RPAREN_TOK statement  */
#line 413 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid expression in if condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2202 "y.tab.c"
    break;

  case 77: /* selection_statement: IF_TOK error expression RPAREN_TOK statement  */
#line 419 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in if statement\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2212 "y.tab.c"
    break;

  case 78: /* iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 428 "parse.y"
                    { print_syntax_success("While loop"); }
#line 2218 "y.tab.c"
    break;

  case 79: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement  */
#line 430 "parse.y"
                    { print_syntax_success("For loop"); }
#line 2224 "y.tab.c"
    break;

  case 80: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement  */
#line 432 "parse.y"
                    { print_syntax_success("For loop with increment"); }
#line 2230 "y.tab.c"
    break;

  case 81: /* iteration_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK  */
#line 434 "parse.y"
                    { print_syntax_success("Do-while loop"); }
#line 2236 "y.tab.c"
    break;

  case 82: /* iteration_statement: WHILE_TOK LPAREN_TOK expression error statement  */
#line 436 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2246 "y.tab.c"
    break;

  case 83: /* iteration_statement: WHILE_TOK LPAREN_TOK error RPAREN_TOK statement  */
#line 442 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid expression in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2256 "y.tab.c"
    break;

  case 84: /* jump_statement: RETURN_TOK expression SEMICOLON_TOK  */
#line 451 "parse.y"
               { print_syntax_success("Return statement with value"); }
#line 2262 "y.tab.c"
    break;

  case 85: /* jump_statement: RETURN_TOK SEMICOLON_TOK  */
#line 453 "parse.y"
               { print_syntax_success("Return statement"); }
#line 2268 "y.tab.c"
    break;

  case 86: /* jump_statement: RETURN_TOK expression error  */
#line 455 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2278 "y.tab.c"
    break;

  case 87: /* jump_statement: RETURN_TOK error SEMICOLON_TOK  */
#line 461 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Invalid expression in return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2288 "y.tab.c"
    break;

  case 90: /* expression: expression error assignment_expr  */
#line 472 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Missing comma ',' between expressions\n", line_number);
             error_count++;
             yyerrok;
           }
#line 2298 "y.tab.c"
    break;

  case 91: /* expression: expression COMMA_TOK error  */
#line 478 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Invalid expression after comma\n", line_number);
             error_count++;
             yyerrok;
           }
#line 2308 "y.tab.c"
    break;

  case 99: /* assignment_expr: unary_expr error assignment_expr  */
#line 493 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 2318 "y.tab.c"
    break;

  case 100: /* assignment_expr: unary_expr ASSIGN_TOK error  */
#line 499 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid expression after assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 2328 "y.tab.c"
    break;

  case 103: /* ternary_expr: logical_or_expr TERNARY_TOK expression error ternary_expr  */
#line 509 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Missing ':' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2338 "y.tab.c"
    break;

  case 104: /* ternary_expr: logical_or_expr TERNARY_TOK error COLON_TOK ternary_expr  */
#line 515 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Invalid expression in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2348 "y.tab.c"
    break;

  case 105: /* ternary_expr: logical_or_expr error expression COLON_TOK ternary_expr  */
#line 521 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Missing '?' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2358 "y.tab.c"
    break;

  case 144: /* postfix_expr: postfix_expr LBRACKET_TOK expression error  */
#line 591 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing bracket ']'\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2368 "y.tab.c"
    break;

  case 145: /* postfix_expr: postfix_expr LBRACKET_TOK error RBRACKET_TOK  */
#line 597 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid array index expression\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2378 "y.tab.c"
    break;

  case 146: /* postfix_expr: postfix_expr LPAREN_TOK RPAREN_TOK  */
#line 603 "parse.y"
              { print_syntax_success("Function call"); }
#line 2384 "y.tab.c"
    break;

  case 147: /* postfix_expr: postfix_expr LPAREN_TOK argument_list RPAREN_TOK  */
#line 605 "parse.y"
              { print_syntax_success("Function call with arguments"); }
#line 2390 "y.tab.c"
    break;

  case 148: /* postfix_expr: postfix_expr LPAREN_TOK argument_list error  */
#line 607 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function call\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2400 "y.tab.c"
    break;

  case 149: /* postfix_expr: postfix_expr LPAREN_TOK error RPAREN_TOK  */
#line 613 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2410 "y.tab.c"
    break;

  case 154: /* argument_list: argument_list error expression  */
#line 625 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing comma ',' between function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2420 "y.tab.c"
    break;

  case 155: /* argument_list: argument_list COMMA_TOK error  */
#line 631 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression after comma in argument list\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2430 "y.tab.c"
    break;

  case 156: /* primary_expr: ID_TOK  */
#line 639 "parse.y"
             {
               // Check if variable is declared before use
               if (!is_variable_declared((yyvsp[0].string_val))) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, (yyvsp[0].string_val));
                   error_count++;
               } else {
                   symbol_t* sym = lookup_symbol((yyvsp[0].string_val));
                   printf("VARIABLE USE: '%s' (Type: %s, Scope: %s)\n", 
                          (yyvsp[0].string_val), type_to_string(sym->type), scope_to_string(sym->scope));
               }
               free((yyvsp[0].string_val));
             }
#line 2447 "y.tab.c"
    break;

  case 159: /* primary_expr: STRING_TOK  */
#line 653 "parse.y"
                         { free((yyvsp[0].string_val)); }
#line 2453 "y.tab.c"
    break;

  case 161: /* primary_expr: LPAREN_TOK expression error  */
#line 656 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')'\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2463 "y.tab.c"
    break;

  case 162: /* primary_expr: LPAREN_TOK error RPAREN_TOK  */
#line 662 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression inside parentheses\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2473 "y.tab.c"
    break;


#line 2477 "y.tab.c"

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

#line 669 "parse.y"


#include "lex.yy.c"

int main() {
    printf("=== C LANGUAGE SUBSET PARSER WITH SYMBOL TABLE ===\n");
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
