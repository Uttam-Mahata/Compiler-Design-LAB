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

#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "symbol_table.h"

extern int line_number;
extern int error_count;
extern char* yytext;
extern int yylex();

void yyerror(char *);
data_type_t current_type = TYPE_UNKNOWN;

void print_syntax_success(char* construct) {
    printf("SYNTAX OK (Line %d): %s\n", line_number, construct);
}

void print_type_error(char* message) {
    printf("TYPE ERROR (Line %d): %s\n", line_number, message);
    error_count++;
}

// Forward declaration - will be defined after token definitions
data_type_t token_to_type(int token);

scope_type_t get_current_scope_type() {
    if (sym_table.current_scope_level == 0) return SCOPE_GLOBAL;
    else if (sym_table.current_scope_level == 1) return SCOPE_FUNCTION;
    else return SCOPE_BLOCK;
}

// Type checking helper functions
data_type_t check_binary_op_type(data_type_t left, data_type_t right, char* op) {
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Binary operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in binary operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    if (left == TYPE_FLOAT || right == TYPE_FLOAT) {
        return TYPE_FLOAT;
    }
    return left;
}

data_type_t check_relational_op_type(data_type_t left, data_type_t right, char* op) {
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Relational operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in relational operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    return TYPE_INT;
}

data_type_t check_logical_op_type(data_type_t left, data_type_t right, char* op) {
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Logical operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in logical operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }

    return TYPE_INT;
}

void check_assignment_type(data_type_t left_type, data_type_t right_type, int is_lvalue) {
    if (!is_lvalue) {
        print_type_error("Left side of assignment must be an lvalue (variable or array element)");
        return;
    }

    if (is_array_type(left_type)) {
        print_type_error("Cannot assign to an array directly");
        return;
    }

    if (!are_types_compatible(left_type, right_type)) {
        char msg[256];
        sprintf(msg, "Type mismatch in assignment: cannot assign '%s' to '%s'",
                type_to_string(right_type), type_to_string(left_type));
        print_type_error(msg);
    }
}

void check_condition_type(data_type_t cond_type) {
    if (!is_numeric_type(cond_type)) {
        char msg[256];
        sprintf(msg, "Condition must be numeric type, got '%s'", type_to_string(cond_type));
        print_type_error(msg);
    }
}

void check_pointer_dereference(data_type_t type) {
    if (!is_pointer_type(type) && !is_array_type(type)) {
        char msg[256];
        sprintf(msg, "Cannot dereference non-pointer type '%s'",
                type_to_string(type));
        print_type_error(msg);
    }
}

#line 205 "y.tab.c"

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
    LOWER_THAN_ELSE = 317,         /* LOWER_THAN_ELSE  */
    UNARY_MINUS = 318,             /* UNARY_MINUS  */
    UNARY_PLUS = 319               /* UNARY_PLUS  */
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
#define LOWER_THAN_ELSE 317
#define UNARY_MINUS 318
#define UNARY_PLUS 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 135 "parse.y"

    int int_val;
    float float_val;
    char* string_val;
    int type_val;
    struct {
        data_type_t type;
        int is_lvalue;
    } expr_info;

#line 397 "y.tab.c"

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
  YYSYMBOL_LOWER_THAN_ELSE = 62,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_UNARY_MINUS = 63,               /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 64,                /* UNARY_PLUS  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_program = 66,                   /* program  */
  YYSYMBOL_67_1 = 67,                      /* $@1  */
  YYSYMBOL_translation_unit = 68,          /* translation_unit  */
  YYSYMBOL_external_declaration = 69,      /* external_declaration  */
  YYSYMBOL_70_2 = 70,                      /* $@2  */
  YYSYMBOL_external_declaration_tail = 71, /* external_declaration_tail  */
  YYSYMBOL_72_3 = 72,                      /* $@3  */
  YYSYMBOL_opt_parameter_list = 73,        /* opt_parameter_list  */
  YYSYMBOL_global_declarator_list = 74,    /* global_declarator_list  */
  YYSYMBOL_global_declarator = 75,         /* global_declarator  */
  YYSYMBOL_init_declarator_list = 76,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 77,           /* init_declarator  */
  YYSYMBOL_declarator = 78,                /* declarator  */
  YYSYMBOL_function_tail = 79,             /* function_tail  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_data_type = 81,                 /* data_type  */
  YYSYMBOL_parameter_list = 82,            /* parameter_list  */
  YYSYMBOL_parameter = 83,                 /* parameter  */
  YYSYMBOL_compound_statement = 84,        /* compound_statement  */
  YYSYMBOL_statement_list = 85,            /* statement_list  */
  YYSYMBOL_statement = 86,                 /* statement  */
  YYSYMBOL_declaration_statement = 87,     /* declaration_statement  */
  YYSYMBOL_88_5 = 88,                      /* $@5  */
  YYSYMBOL_expression_statement = 89,      /* expression_statement  */
  YYSYMBOL_selection_statement = 90,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 91,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 92,            /* jump_statement  */
  YYSYMBOL_expression = 93,                /* expression  */
  YYSYMBOL_assignment_expr = 94,           /* assignment_expr  */
  YYSYMBOL_ternary_expr = 95,              /* ternary_expr  */
  YYSYMBOL_logical_or_expr = 96,           /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 97,          /* logical_and_expr  */
  YYSYMBOL_bit_or_expr = 98,               /* bit_or_expr  */
  YYSYMBOL_bit_xor_expr = 99,              /* bit_xor_expr  */
  YYSYMBOL_bit_and_expr = 100,             /* bit_and_expr  */
  YYSYMBOL_equality_expr = 101,            /* equality_expr  */
  YYSYMBOL_relational_expr = 102,          /* relational_expr  */
  YYSYMBOL_shift_expr = 103,               /* shift_expr  */
  YYSYMBOL_additive_expr = 104,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 105,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 106,               /* unary_expr  */
  YYSYMBOL_unary_operator = 107,           /* unary_operator  */
  YYSYMBOL_postfix_expr = 108,             /* postfix_expr  */
  YYSYMBOL_argument_list = 109,            /* argument_list  */
  YYSYMBOL_primary_expr = 110              /* primary_expr  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   325

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   203,   203,   203,   212,   213,   217,   217,   222,   222,
     231,   237,   238,   241,   242,   245,   252,   260,   275,   293,
     294,   297,   298,   302,   309,   324,   341,   343,   343,   351,
     352,   353,   354,   358,   359,   362,   369,   387,   389,   394,
     395,   399,   400,   401,   402,   403,   404,   408,   408,   415,
     417,   422,   427,   435,   440,   442,   444,   452,   454,   459,
     461,   465,   467,   473,   480,   487,   494,   501,   510,   512,
     525,   527,   534,   536,   543,   545,   552,   554,   561,   563,
     570,   572,   577,   584,   586,   591,   596,   601,   608,   610,
     615,   622,   624,   629,   636,   638,   643,   648,   655,   657,
     665,   673,   685,   686,   687,   688,   691,   693,   706,   712,
     718,   726,   736,   737,   740,   754,   759,   764,   770
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
  "LOWER_THAN_ELSE", "UNARY_MINUS", "UNARY_PLUS", "$accept", "program",
  "$@1", "translation_unit", "external_declaration", "$@2",
  "external_declaration_tail", "$@3", "opt_parameter_list",
  "global_declarator_list", "global_declarator", "init_declarator_list",
  "init_declarator", "declarator", "function_tail", "$@4", "data_type",
  "parameter_list", "parameter", "compound_statement", "statement_list",
  "statement", "declaration_statement", "$@5", "expression_statement",
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

#define YYPACT_NINF (-148)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-9)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -148,     6,   148,  -148,  -148,  -148,  -148,  -148,   148,  -148,
    -148,  -148,    14,   -25,  -148,   -44,  -148,   278,     2,   -34,
    -148,    16,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
     278,   278,   278,  -148,  -148,   -24,   -10,    39,    41,    45,
      94,   133,    95,   153,   142,    73,   278,    52,  -148,    34,
    -148,   148,   -26,  -148,  -148,  -148,     4,  -148,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,   278,   278,   278,   278,   278,   278,   278,
     278,   278,   278,  -148,  -148,  -148,   236,   278,  -148,    46,
      84,    54,  -148,  -148,   278,   -10,  -148,   -39,    39,    41,
      45,    94,   133,   133,    95,    95,    95,    95,   153,   153,
     142,   142,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,    63,    18,   -22,    70,    55,   148,  -148,   278,
    -148,   278,  -148,  -148,  -148,    77,    89,  -148,  -148,    63,
      75,  -148,  -148,   112,   125,   181,   131,   188,  -148,  -148,
    -148,  -148,   130,  -148,  -148,  -148,  -148,  -148,  -148,   122,
     278,   229,   185,   278,  -148,   128,   187,  -148,  -148,  -148,
      19,   229,   165,    21,  -148,   168,   154,  -148,   183,   181,
     272,   278,   181,     5,  -148,   187,   278,  -148,   181,    50,
      53,   210,   171,  -148,  -148,  -148,  -148,   181,   173,   181,
    -148,  -148,  -148,  -148
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    29,    30,    31,    32,     3,     5,
       6,     4,     0,    15,     7,     0,    14,     0,     0,     0,
      10,     0,   114,   117,   115,   116,   102,   103,   104,   105,
       0,     0,     0,    16,    61,    68,    70,    72,    74,    76,
      78,    80,    83,    88,    91,    94,     0,    98,   106,     0,
      18,    12,    15,    13,    99,   100,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,   110,   111,     0,     0,    17,     0,
       0,    11,    34,   118,     0,    71,    94,     0,    73,    75,
      77,    79,    81,    82,    84,    85,    86,    87,    89,    90,
      92,    93,    95,    96,    97,    62,    63,    64,    65,    66,
      67,   108,   113,     0,     0,    27,    35,     0,    60,     0,
     109,     0,   107,    26,     9,     0,     0,    33,    69,   112,
       0,    28,    36,     0,     0,     0,     0,     0,    38,    50,
      47,    43,     0,    40,    41,    42,    44,    45,    46,     0,
       0,     0,     0,     0,    58,     0,     0,    37,    39,    49,
       0,     0,     0,     0,    57,    23,     0,    20,    21,     0,
       0,     0,     0,     0,    48,     0,     0,    53,     0,     0,
       0,    51,     0,    25,    19,    22,    54,     0,     0,     0,
      24,    55,    56,    52
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,  -148,  -148,   219,  -148,  -148,  -148,  -148,  -148,
     208,  -148,    48,  -148,  -148,  -148,     0,  -148,   109,   102,
    -148,  -129,  -148,  -148,  -147,  -148,  -148,  -148,   -31,   -17,
     110,  -148,   180,   195,   179,   186,   193,   145,    99,   143,
     144,   -27,  -148,  -148,  -148,  -148
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    12,    14,    19,    89,    15,
      16,   176,   177,   178,   134,   135,   150,    91,    92,   151,
     152,   153,   154,   166,   155,   156,   157,   158,   159,    57,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,   123,    48
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    56,    10,    54,    55,    58,     3,   129,    10,    20,
      21,    17,    17,    51,   171,    94,   162,    49,    60,    83,
     192,    59,    -8,   168,   180,    18,    18,    13,    97,    52,
     132,    96,    94,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,   112,   113,   114,
     187,    90,    93,   191,    50,   122,   124,   193,    94,   196,
     115,   116,   117,   118,   119,   120,   130,   179,   201,   182,
     203,    61,   131,    94,    62,    94,    63,   128,     4,     5,
       6,     7,   143,   144,   145,   146,    88,   147,    22,    23,
      24,    25,    26,    27,   125,    84,    85,   126,   197,    86,
     139,   198,    96,    87,    94,    28,   136,    94,   127,    29,
      77,    78,    79,    80,    81,    82,   165,    94,    30,    31,
      64,    65,    32,   133,   140,   148,   140,    90,   149,   170,
      70,    71,   173,     4,     5,     6,     7,   143,   144,   145,
     146,   142,   147,    22,    23,    24,    25,    26,    27,   189,
     190,     4,     5,     6,     7,    66,    67,    68,    69,   160,
      28,    74,    75,    76,    29,   104,   105,   106,   107,   195,
      72,    73,   161,    30,    31,   169,    94,    32,   163,   140,
     167,   174,    94,   149,     4,     5,     6,     7,   143,   144,
     145,   146,   172,   147,    22,    23,    24,    25,    26,    27,
     175,    22,    23,    24,    25,    26,    27,   184,   185,   102,
     103,    28,   181,   108,   109,    29,   110,   111,    28,   183,
     186,   199,    29,   200,    30,    31,   202,    11,    32,    53,
     140,    30,    31,   194,   149,    32,   137,   141,    95,   138,
      99,   164,    22,    23,    24,    25,    26,    27,   100,    22,
      23,    24,    25,    26,    27,    98,   101,     0,     0,    28,
       0,     0,     0,    29,     0,     0,    28,     0,     0,     0,
      29,     0,    30,    31,     0,     0,    32,     0,     0,    30,
      31,     0,   149,    32,   121,    22,    23,    24,    25,    26,
      27,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,    28,     0,     0,     0,    29,     0,    28,     0,
       0,     0,    29,     0,     0,    30,    31,     0,     0,    32,
     188,    30,    31,     0,     0,    32
};

static const yytype_int16 yycheck[] =
{
      17,    32,     2,    30,    31,    29,     0,    46,     8,    53,
      54,    37,    37,    47,   161,    54,   145,    15,    28,    46,
      15,    45,    47,   152,   171,    51,    51,    13,    59,    13,
      52,    58,    54,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
     179,    51,    48,   182,    52,    86,    87,    52,    54,   188,
      77,    78,    79,    80,    81,    82,    48,    48,   197,    48,
     199,    32,    54,    54,    33,    54,    31,    94,     3,     4,
       5,     6,     7,     8,     9,    10,    52,    12,    13,    14,
      15,    16,    17,    18,    48,    43,    44,    13,    48,    47,
     131,    48,   129,    51,    54,    30,    51,    54,    54,    34,
      37,    38,    39,    40,    41,    42,   147,    54,    43,    44,
      26,    27,    47,    53,    49,    50,    49,   127,    53,   160,
      35,    36,   163,     3,     4,     5,     6,     7,     8,     9,
      10,    52,    12,    13,    14,    15,    16,    17,    18,   180,
     181,     3,     4,     5,     6,    22,    23,    24,    25,    47,
      30,    19,    20,    21,    34,    66,    67,    68,    69,   186,
      17,    18,    47,    43,    44,    53,    54,    47,    47,    49,
      50,    53,    54,    53,     3,     4,     5,     6,     7,     8,
       9,    10,     7,    12,    13,    14,    15,    16,    17,    18,
      13,    13,    14,    15,    16,    17,    18,    53,    54,    64,
      65,    30,    47,    70,    71,    34,    72,    73,    30,    51,
      37,    11,    34,    52,    43,    44,    53,     8,    47,    21,
      49,    43,    44,   185,    53,    47,   127,   135,    58,   129,
      61,    53,    13,    14,    15,    16,    17,    18,    62,    13,
      14,    15,    16,    17,    18,    60,    63,    -1,    -1,    30,
      -1,    -1,    -1,    34,    -1,    -1,    30,    -1,    -1,    -1,
      34,    -1,    43,    44,    -1,    -1,    47,    -1,    -1,    43,
      44,    -1,    53,    47,    48,    13,    14,    15,    16,    17,
      18,    13,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    34,    -1,    30,    -1,
      -1,    -1,    34,    -1,    -1,    43,    44,    -1,    -1,    47,
      48,    43,    44,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,    67,     0,     3,     4,     5,     6,    68,    69,
      81,    69,    70,    13,    71,    74,    75,    37,    51,    72,
      53,    54,    13,    14,    15,    16,    17,    18,    30,    34,
      43,    44,    47,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   110,    15,
      52,    47,    13,    75,   106,   106,    93,    94,    29,    45,
      28,    32,    33,    31,    26,    27,    22,    23,    24,    25,
      35,    36,    17,    18,    19,    20,    21,    37,    38,    39,
      40,    41,    42,   106,    43,    44,    47,    51,    52,    73,
      81,    82,    83,    48,    54,    97,   106,    93,    98,    99,
     100,   101,   102,   102,   103,   103,   103,   103,   104,   104,
     105,   105,   106,   106,   106,    94,    94,    94,    94,    94,
      94,    48,    93,   109,    93,    48,    13,    54,    94,    46,
      48,    54,    52,    53,    79,    80,    51,    83,    95,    93,
      49,    84,    52,     7,     8,     9,    10,    12,    50,    53,
      81,    84,    85,    86,    87,    89,    90,    91,    92,    93,
      47,    47,    86,    47,    53,    93,    88,    50,    86,    53,
      93,    89,     7,    93,    53,    13,    76,    77,    78,    48,
      89,    47,    48,    51,    53,    54,    37,    86,    48,    93,
      93,    86,    15,    52,    77,    94,    86,    48,    48,    11,
      52,    86,    53,    86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    67,    66,    68,    68,    70,    69,    72,    71,
      71,    73,    73,    74,    74,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    79,    80,    79,    81,
      81,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    86,    86,    86,    86,    88,    87,    89,
      89,    90,    90,    91,    91,    91,    91,    92,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   101,   102,   102,   102,   102,   102,   103,   103,
     103,   104,   104,   104,   105,   105,   105,   105,   106,   106,
     106,   106,   107,   107,   107,   107,   108,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   110,   110
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     0,     3,     0,     6,
       2,     1,     0,     3,     1,     1,     3,     4,     3,     3,
       1,     1,     3,     1,     4,     3,     1,     0,     2,     1,
       1,     1,     1,     3,     1,     2,     4,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     2,
       1,     5,     7,     5,     6,     7,     7,     3,     2,     1,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     4,     3,     4,
       2,     2,     3,     1,     1,     1,     1,     1,     3
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
#line 203 "parse.y"
         { init_symbol_table(); }
#line 1667 "y.tab.c"
    break;

  case 3: /* program: $@1 translation_unit  */
#line 204 "parse.y"
         {
           print_syntax_success("C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1678 "y.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 217 "parse.y"
                                {
                       current_type = token_to_type((yyvsp[0].type_val));
                     }
#line 1686 "y.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 222 "parse.y"
                                  {
                            if (!add_symbol((yyvsp[0].string_val), current_type, SCOPE_GLOBAL, line_number, 1)) {
                                error_count++;
                            }
                            free((yyvsp[0].string_val));
                          }
#line 1697 "y.tab.c"
    break;

  case 9: /* external_declaration_tail: ID_TOK $@3 LPAREN_TOK opt_parameter_list RPAREN_TOK function_tail  */
#line 228 "parse.y"
                          {
                            print_syntax_success("Function declaration");
                          }
#line 1705 "y.tab.c"
    break;

  case 10: /* external_declaration_tail: global_declarator_list SEMICOLON_TOK  */
#line 232 "parse.y"
                          {
                            print_syntax_success("Global variable declaration");
                          }
#line 1713 "y.tab.c"
    break;

  case 15: /* global_declarator: ID_TOK  */
#line 246 "parse.y"
                  {
                    if (!add_symbol((yyvsp[0].string_val), current_type, SCOPE_GLOBAL, line_number, 0)) {
                        error_count++;
                    }
                    free((yyvsp[0].string_val));
                  }
#line 1724 "y.tab.c"
    break;

  case 16: /* global_declarator: ID_TOK ASSIGN_TOK assignment_expr  */
#line 253 "parse.y"
                  {
                    if (!add_symbol((yyvsp[-2].string_val), current_type, SCOPE_GLOBAL, line_number, 0)) {
                        error_count++;
                    }
                    free((yyvsp[-2].string_val));
                    print_syntax_success("Variable initialization");
                  }
#line 1736 "y.tab.c"
    break;

  case 17: /* global_declarator: ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK  */
#line 261 "parse.y"
                  {
                    data_type_t array_type;
                    switch(current_type) {
                        case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                        case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                        case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                        default: array_type = current_type; break;
                    }
                    if (!add_symbol_with_attrs((yyvsp[-3].string_val), array_type, SCOPE_GLOBAL,
                                              line_number, 0, 1, (yyvsp[-1].int_val), 0)) {
                        error_count++;
                    }
                    free((yyvsp[-3].string_val));
                  }
#line 1755 "y.tab.c"
    break;

  case 18: /* global_declarator: ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 276 "parse.y"
                  {
                    data_type_t array_type;
                    switch(current_type) {
                        case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                        case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                        case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                        default: array_type = current_type; break;
                    }
                    if (!add_symbol_with_attrs((yyvsp[-2].string_val), array_type, SCOPE_GLOBAL,
                                              line_number, 0, 1, 0, 0)) {
                        error_count++;
                    }
                    free((yyvsp[-2].string_val));
                  }
#line 1774 "y.tab.c"
    break;

  case 22: /* init_declarator: declarator ASSIGN_TOK assignment_expr  */
#line 299 "parse.y"
                 { print_syntax_success("Variable initialization"); }
#line 1780 "y.tab.c"
    break;

  case 23: /* declarator: ID_TOK  */
#line 303 "parse.y"
           {
             if (!add_symbol((yyvsp[0].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free((yyvsp[0].string_val));
           }
#line 1791 "y.tab.c"
    break;

  case 24: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK  */
#line 310 "parse.y"
           {
             data_type_t array_type;
             switch(current_type) {
                 case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                 case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                 case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                 default: array_type = current_type; break;
             }
             if (!add_symbol_with_attrs((yyvsp[-3].string_val), array_type, get_current_scope_type(),
                                       line_number, 0, 1, (yyvsp[-1].int_val), 0)) {
                 error_count++;
             }
             free((yyvsp[-3].string_val));
           }
#line 1810 "y.tab.c"
    break;

  case 25: /* declarator: ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 325 "parse.y"
           {
             data_type_t array_type;
             switch(current_type) {
                 case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                 case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                 case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                 default: array_type = current_type; break;
             }
             if (!add_symbol_with_attrs((yyvsp[-2].string_val), array_type, get_current_scope_type(),
                                       line_number, 0, 1, 0, 0)) {
                 error_count++;
             }
             free((yyvsp[-2].string_val));
           }
#line 1829 "y.tab.c"
    break;

  case 26: /* function_tail: SEMICOLON_TOK  */
#line 342 "parse.y"
               { /* Function prototype */ }
#line 1835 "y.tab.c"
    break;

  case 27: /* $@4: %empty  */
#line 343 "parse.y"
               { enter_scope(); }
#line 1841 "y.tab.c"
    break;

  case 28: /* function_tail: $@4 compound_statement  */
#line 344 "parse.y"
               {
                 /* Function definition */
                 exit_scope();
               }
#line 1850 "y.tab.c"
    break;

  case 29: /* data_type: INT_TOK  */
#line 351 "parse.y"
                   { (yyval.type_val) = INT_TOK; }
#line 1856 "y.tab.c"
    break;

  case 30: /* data_type: FLOAT_TOK  */
#line 352 "parse.y"
                     { (yyval.type_val) = FLOAT_TOK; }
#line 1862 "y.tab.c"
    break;

  case 31: /* data_type: CHAR_TOK  */
#line 353 "parse.y"
                    { (yyval.type_val) = CHAR_TOK; }
#line 1868 "y.tab.c"
    break;

  case 32: /* data_type: VOID_TOK  */
#line 354 "parse.y"
                    { (yyval.type_val) = VOID_TOK; }
#line 1874 "y.tab.c"
    break;

  case 35: /* parameter: data_type ID_TOK  */
#line 363 "parse.y"
          {
            if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free((yyvsp[0].string_val));
          }
#line 1885 "y.tab.c"
    break;

  case 36: /* parameter: data_type ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 370 "parse.y"
          {
            data_type_t array_type;
            switch(token_to_type((yyvsp[-3].type_val))) {
                case TYPE_INT: array_type = TYPE_INT_ARRAY; break;
                case TYPE_FLOAT: array_type = TYPE_FLOAT_ARRAY; break;
                case TYPE_CHAR: array_type = TYPE_CHAR_ARRAY; break;
                default: array_type = token_to_type((yyvsp[-3].type_val)); break;
            }
            if (!add_symbol_with_attrs((yyvsp[-2].string_val), array_type, SCOPE_FUNCTION,
                                      line_number, 0, 1, 0, 0)) {
                error_count++;
            }
            free((yyvsp[-2].string_val));
          }
#line 1904 "y.tab.c"
    break;

  case 37: /* compound_statement: LBRACE_TOK statement_list RBRACE_TOK  */
#line 388 "parse.y"
                   { print_syntax_success("Compound statement"); }
#line 1910 "y.tab.c"
    break;

  case 38: /* compound_statement: LBRACE_TOK RBRACE_TOK  */
#line 390 "parse.y"
                   { print_syntax_success("Empty compound statement"); }
#line 1916 "y.tab.c"
    break;

  case 47: /* $@5: %empty  */
#line 408 "parse.y"
                                 {
                        current_type = token_to_type((yyvsp[0].type_val));
                      }
#line 1924 "y.tab.c"
    break;

  case 48: /* declaration_statement: data_type $@5 init_declarator_list SEMICOLON_TOK  */
#line 411 "parse.y"
                      { print_syntax_success("Local variable declaration"); }
#line 1930 "y.tab.c"
    break;

  case 49: /* expression_statement: expression SEMICOLON_TOK  */
#line 416 "parse.y"
                     { print_syntax_success("Expression statement"); }
#line 1936 "y.tab.c"
    break;

  case 50: /* expression_statement: SEMICOLON_TOK  */
#line 418 "parse.y"
                     { print_syntax_success("Empty statement"); }
#line 1942 "y.tab.c"
    break;

  case 51: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 423 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("If statement");
                    }
#line 1951 "y.tab.c"
    break;

  case 52: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement  */
#line 428 "parse.y"
                    {
                      check_condition_type((yyvsp[-4].expr_info).type);
                      print_syntax_success("If-else statement");
                    }
#line 1960 "y.tab.c"
    break;

  case 53: /* iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 436 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("While loop");
                    }
#line 1969 "y.tab.c"
    break;

  case 54: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement  */
#line 441 "parse.y"
                    { print_syntax_success("For loop"); }
#line 1975 "y.tab.c"
    break;

  case 55: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement  */
#line 443 "parse.y"
                    { print_syntax_success("For loop with increment"); }
#line 1981 "y.tab.c"
    break;

  case 56: /* iteration_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK  */
#line 445 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("Do-while loop");
                    }
#line 1990 "y.tab.c"
    break;

  case 57: /* jump_statement: RETURN_TOK expression SEMICOLON_TOK  */
#line 453 "parse.y"
               { print_syntax_success("Return statement with value"); }
#line 1996 "y.tab.c"
    break;

  case 58: /* jump_statement: RETURN_TOK SEMICOLON_TOK  */
#line 455 "parse.y"
               { print_syntax_success("Return statement"); }
#line 2002 "y.tab.c"
    break;

  case 59: /* expression: assignment_expr  */
#line 460 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2008 "y.tab.c"
    break;

  case 60: /* expression: expression COMMA_TOK assignment_expr  */
#line 462 "parse.y"
           { (yyval.expr_info).type = (yyvsp[0].expr_info).type; (yyval.expr_info).is_lvalue = 0; }
#line 2014 "y.tab.c"
    break;

  case 61: /* assignment_expr: ternary_expr  */
#line 466 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2020 "y.tab.c"
    break;

  case 62: /* assignment_expr: unary_expr ASSIGN_TOK assignment_expr  */
#line 468 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2030 "y.tab.c"
    break;

  case 63: /* assignment_expr: unary_expr ADD_ASSIGN_TOK assignment_expr  */
#line 474 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2041 "y.tab.c"
    break;

  case 64: /* assignment_expr: unary_expr SUB_ASSIGN_TOK assignment_expr  */
#line 481 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2052 "y.tab.c"
    break;

  case 65: /* assignment_expr: unary_expr MUL_ASSIGN_TOK assignment_expr  */
#line 488 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2063 "y.tab.c"
    break;

  case 66: /* assignment_expr: unary_expr DIV_ASSIGN_TOK assignment_expr  */
#line 495 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2074 "y.tab.c"
    break;

  case 67: /* assignment_expr: unary_expr MOD_ASSIGN_TOK assignment_expr  */
#line 502 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2085 "y.tab.c"
    break;

  case 68: /* ternary_expr: logical_or_expr  */
#line 511 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2091 "y.tab.c"
    break;

  case 69: /* ternary_expr: logical_or_expr TERNARY_TOK expression COLON_TOK ternary_expr  */
#line 513 "parse.y"
             {
               if (!are_types_compatible((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type)) {
                 char msg[256];
                 sprintf(msg, "Type mismatch in ternary operator: '%s' and '%s' are not compatible",
                         type_to_string((yyvsp[-2].expr_info).type), type_to_string((yyvsp[0].expr_info).type));
                 print_type_error(msg);
               }
               (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2106 "y.tab.c"
    break;

  case 70: /* logical_or_expr: logical_and_expr  */
#line 526 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2112 "y.tab.c"
    break;

  case 71: /* logical_or_expr: logical_or_expr OR_TOK logical_and_expr  */
#line 528 "parse.y"
                {
                  (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "||");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2121 "y.tab.c"
    break;

  case 72: /* logical_and_expr: bit_or_expr  */
#line 535 "parse.y"
                 { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2127 "y.tab.c"
    break;

  case 73: /* logical_and_expr: logical_and_expr AND_TOK bit_or_expr  */
#line 537 "parse.y"
                 {
                   (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&&");
                   (yyval.expr_info).is_lvalue = 0;
                 }
#line 2136 "y.tab.c"
    break;

  case 74: /* bit_or_expr: bit_xor_expr  */
#line 544 "parse.y"
            { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2142 "y.tab.c"
    break;

  case 75: /* bit_or_expr: bit_or_expr BIT_OR_TOK bit_xor_expr  */
#line 546 "parse.y"
            {
              (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "|");
              (yyval.expr_info).is_lvalue = 0;
            }
#line 2151 "y.tab.c"
    break;

  case 76: /* bit_xor_expr: bit_and_expr  */
#line 553 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2157 "y.tab.c"
    break;

  case 77: /* bit_xor_expr: bit_xor_expr BIT_XOR_TOK bit_and_expr  */
#line 555 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "^");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2166 "y.tab.c"
    break;

  case 78: /* bit_and_expr: equality_expr  */
#line 562 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2172 "y.tab.c"
    break;

  case 79: /* bit_and_expr: bit_and_expr BIT_AND_TOK equality_expr  */
#line 564 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2181 "y.tab.c"
    break;

  case 80: /* equality_expr: relational_expr  */
#line 571 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2187 "y.tab.c"
    break;

  case 81: /* equality_expr: equality_expr EQ_TOK relational_expr  */
#line 573 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "==");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2196 "y.tab.c"
    break;

  case 82: /* equality_expr: equality_expr NEQ_TOK relational_expr  */
#line 578 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "!=");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2205 "y.tab.c"
    break;

  case 83: /* relational_expr: shift_expr  */
#line 585 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2211 "y.tab.c"
    break;

  case 84: /* relational_expr: relational_expr LT_TOK shift_expr  */
#line 587 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2220 "y.tab.c"
    break;

  case 85: /* relational_expr: relational_expr GT_TOK shift_expr  */
#line 592 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2229 "y.tab.c"
    break;

  case 86: /* relational_expr: relational_expr LE_TOK shift_expr  */
#line 597 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2238 "y.tab.c"
    break;

  case 87: /* relational_expr: relational_expr GE_TOK shift_expr  */
#line 602 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2247 "y.tab.c"
    break;

  case 88: /* shift_expr: additive_expr  */
#line 609 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2253 "y.tab.c"
    break;

  case 89: /* shift_expr: shift_expr BIT_LSHIFT_TOK additive_expr  */
#line 611 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<<");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2262 "y.tab.c"
    break;

  case 90: /* shift_expr: shift_expr BIT_RSHIFT_TOK additive_expr  */
#line 616 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">>");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2271 "y.tab.c"
    break;

  case 91: /* additive_expr: multiplicative_expr  */
#line 623 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2277 "y.tab.c"
    break;

  case 92: /* additive_expr: additive_expr ADD_TOK multiplicative_expr  */
#line 625 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2286 "y.tab.c"
    break;

  case 93: /* additive_expr: additive_expr SUB_TOK multiplicative_expr  */
#line 630 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2295 "y.tab.c"
    break;

  case 94: /* multiplicative_expr: unary_expr  */
#line 637 "parse.y"
                    { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2301 "y.tab.c"
    break;

  case 95: /* multiplicative_expr: multiplicative_expr MUL_TOK unary_expr  */
#line 639 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2310 "y.tab.c"
    break;

  case 96: /* multiplicative_expr: multiplicative_expr DIV_TOK unary_expr  */
#line 644 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2319 "y.tab.c"
    break;

  case 97: /* multiplicative_expr: multiplicative_expr MOD_TOK unary_expr  */
#line 649 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2328 "y.tab.c"
    break;

  case 98: /* unary_expr: postfix_expr  */
#line 656 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2334 "y.tab.c"
    break;

  case 99: /* unary_expr: INC_TOK unary_expr  */
#line 658 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Increment operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2346 "y.tab.c"
    break;

  case 100: /* unary_expr: DEC_TOK unary_expr  */
#line 666 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Decrement operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2358 "y.tab.c"
    break;

  case 101: /* unary_expr: unary_operator unary_expr  */
#line 674 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Unary operator requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2372 "y.tab.c"
    break;

  case 106: /* postfix_expr: primary_expr  */
#line 692 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2378 "y.tab.c"
    break;

  case 107: /* postfix_expr: postfix_expr LBRACKET_TOK expression RBRACKET_TOK  */
#line 694 "parse.y"
             {
               if (!is_array_type((yyvsp[-3].expr_info).type) && !is_pointer_type((yyvsp[-3].expr_info).type)) {
                 check_pointer_dereference((yyvsp[-3].expr_info).type);
               }
               if (!is_numeric_type((yyvsp[-1].expr_info).type)) {
                 char msg[256];
                 sprintf(msg, "Array index must be numeric type, got '%s'", type_to_string((yyvsp[-1].expr_info).type));
                 print_type_error(msg);
               }
               (yyval.expr_info).type = get_base_type((yyvsp[-3].expr_info).type);
               (yyval.expr_info).is_lvalue = 1;
             }
#line 2395 "y.tab.c"
    break;

  case 108: /* postfix_expr: postfix_expr LPAREN_TOK RPAREN_TOK  */
#line 707 "parse.y"
              {
                print_syntax_success("Function call");
                (yyval.expr_info).type = TYPE_INT;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2405 "y.tab.c"
    break;

  case 109: /* postfix_expr: postfix_expr LPAREN_TOK argument_list RPAREN_TOK  */
#line 713 "parse.y"
              {
                print_syntax_success("Function call with arguments");
                (yyval.expr_info).type = TYPE_INT;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2415 "y.tab.c"
    break;

  case 110: /* postfix_expr: postfix_expr INC_TOK  */
#line 719 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Increment operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2427 "y.tab.c"
    break;

  case 111: /* postfix_expr: postfix_expr DEC_TOK  */
#line 727 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Decrement operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2439 "y.tab.c"
    break;

  case 114: /* primary_expr: ID_TOK  */
#line 741 "parse.y"
             {
               if (!is_variable_declared((yyvsp[0].string_val))) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, (yyvsp[0].string_val));
                   error_count++;
                   (yyval.expr_info).type = TYPE_UNKNOWN;
                   (yyval.expr_info).is_lvalue = 0;
               } else {
                   symbol_node_t* sym = lookup_symbol((yyvsp[0].string_val));
                   (yyval.expr_info).type = sym->type;
                   (yyval.expr_info).is_lvalue = !sym->is_array;
               }
               free((yyvsp[0].string_val));
             }
#line 2457 "y.tab.c"
    break;

  case 115: /* primary_expr: INTCONST_TOK  */
#line 755 "parse.y"
             {
               (yyval.expr_info).type = TYPE_INT;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2466 "y.tab.c"
    break;

  case 116: /* primary_expr: FLOATCONST_TOK  */
#line 760 "parse.y"
             {
               (yyval.expr_info).type = TYPE_FLOAT;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2475 "y.tab.c"
    break;

  case 117: /* primary_expr: STRING_TOK  */
#line 765 "parse.y"
             {
               free((yyvsp[0].string_val));
               (yyval.expr_info).type = TYPE_CHAR_PTR;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2485 "y.tab.c"
    break;

  case 118: /* primary_expr: LPAREN_TOK expression RPAREN_TOK  */
#line 771 "parse.y"
             {
               (yyval.expr_info) = (yyvsp[-1].expr_info);
             }
#line 2493 "y.tab.c"
    break;


#line 2497 "y.tab.c"

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

#line 776 "parse.y"


#include "lex.yy.c"

data_type_t token_to_type(int token) {
    switch(token) {
        case INT_TOK: return TYPE_INT;
        case FLOAT_TOK: return TYPE_FLOAT;
        case CHAR_TOK: return TYPE_CHAR;
        case VOID_TOK: return TYPE_VOID;
        default: return TYPE_UNKNOWN;
    }
}

int main() {
    printf("=== C COMPILER: LEXICAL + SYNTAX + TYPE CHECKING ===\n");
    printf("Parsing input...\n\n");

    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Errors found at line %d\n", line_number);
    }

    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}
