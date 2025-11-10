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
#include "icg.h"

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
        char* place;  // For holding temporary variable or identifier name
    } expr_info;
    struct {
        int next_list[100];
        int next_count;
        int true_list[100];
        int true_count;
        int false_list[100];
        int false_count;
    } stmt_info;
    struct {
        char* label;
        int quad;
    } marker_info;

#line 410 "y.tab.c"

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
  YYSYMBOL_global_variable_declaration = 70, /* global_variable_declaration  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_init_declarator_list = 72,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 73,           /* init_declarator  */
  YYSYMBOL_declarator = 74,                /* declarator  */
  YYSYMBOL_function_declaration = 75,      /* function_declaration  */
  YYSYMBOL_76_3 = 76,                      /* $@3  */
  YYSYMBOL_77_4 = 77,                      /* $@4  */
  YYSYMBOL_function_tail = 78,             /* function_tail  */
  YYSYMBOL_79_5 = 79,                      /* $@5  */
  YYSYMBOL_data_type = 80,                 /* data_type  */
  YYSYMBOL_parameter_list = 81,            /* parameter_list  */
  YYSYMBOL_parameter = 82,                 /* parameter  */
  YYSYMBOL_compound_statement = 83,        /* compound_statement  */
  YYSYMBOL_statement_list = 84,            /* statement_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_declaration_statement = 86,     /* declaration_statement  */
  YYSYMBOL_87_6 = 87,                      /* $@6  */
  YYSYMBOL_expression_statement = 88,      /* expression_statement  */
  YYSYMBOL_selection_statement = 89,       /* selection_statement  */
  YYSYMBOL_iteration_statement = 90,       /* iteration_statement  */
  YYSYMBOL_jump_statement = 91,            /* jump_statement  */
  YYSYMBOL_expression = 92,                /* expression  */
  YYSYMBOL_assignment_expr = 93,           /* assignment_expr  */
  YYSYMBOL_ternary_expr = 94,              /* ternary_expr  */
  YYSYMBOL_logical_or_expr = 95,           /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 96,          /* logical_and_expr  */
  YYSYMBOL_bit_or_expr = 97,               /* bit_or_expr  */
  YYSYMBOL_bit_xor_expr = 98,              /* bit_xor_expr  */
  YYSYMBOL_bit_and_expr = 99,              /* bit_and_expr  */
  YYSYMBOL_equality_expr = 100,            /* equality_expr  */
  YYSYMBOL_relational_expr = 101,          /* relational_expr  */
  YYSYMBOL_shift_expr = 102,               /* shift_expr  */
  YYSYMBOL_additive_expr = 103,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 104,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 105,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 106,             /* postfix_expr  */
  YYSYMBOL_argument_list = 107,            /* argument_list  */
  YYSYMBOL_primary_expr = 108              /* primary_expr  */
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
#define YYLAST   377

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

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
       0,   216,   216,   216,   225,   226,   230,   231,   235,   235,
     241,   242,   245,   246,   250,   257,   272,   290,   290,   299,
     299,   310,   312,   312,   320,   321,   322,   323,   327,   328,
     331,   338,   356,   358,   363,   364,   368,   369,   370,   371,
     372,   373,   377,   377,   384,   386,   391,   403,   420,   438,
     440,   442,   454,   456,   463,   465,   469,   471,   481,   488,
     495,   502,   509,   518,   520,   533,   535,   542,   544,   551,
     553,   560,   562,   569,   571,   578,   580,   585,   592,   594,
     599,   604,   609,   616,   618,   623,   630,   632,   641,   652,
     654,   663,   672,   683,   685,   693,   701,   715,   726,   740,
     756,   758,   771,   777,   783,   791,   801,   802,   805,   821,
     831,   841,   847
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
  "$@1", "translation_unit", "external_declaration",
  "global_variable_declaration", "$@2", "init_declarator_list",
  "init_declarator", "declarator", "function_declaration", "$@3", "$@4",
  "function_tail", "$@5", "data_type", "parameter_list", "parameter",
  "compound_statement", "statement_list", "statement",
  "declaration_statement", "$@6", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "expression", "assignment_expr", "ternary_expr", "logical_or_expr",
  "logical_and_expr", "bit_or_expr", "bit_xor_expr", "bit_and_expr",
  "equality_expr", "relational_expr", "shift_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "postfix_expr", "argument_list",
  "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -159,    15,    60,  -159,  -159,  -159,  -159,  -159,    60,  -159,
    -159,  -159,    22,  -159,  -159,    25,    28,    53,   -29,    34,
    -159,    72,    49,    60,     9,  -159,    25,   330,    66,    93,
     -38,  -159,    97,  -159,  -159,  -159,  -159,  -159,  -159,   330,
     330,   330,   330,   330,   330,   330,  -159,  -159,   -20,   129,
     128,   130,   133,    69,    68,    86,   114,     7,    88,   -30,
    -159,  -159,  -159,   116,   115,    66,    60,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,   -25,  -159,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,   330,   330,   330,   330,   330,   330,   330,   330,   330,
     330,  -159,  -159,   288,   330,   138,  -159,   117,  -159,  -159,
    -159,   330,   129,  -159,   -35,   128,   130,   133,    69,    68,
      68,    86,    86,    86,    86,   114,   114,     7,     7,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,   113,
     -18,    32,   123,   124,   240,   126,    64,  -159,  -159,  -159,
    -159,   189,  -159,  -159,  -159,  -159,  -159,  -159,    50,  -159,
    -159,   330,  -159,   330,  -159,   330,   247,   167,   330,  -159,
      80,    25,  -159,  -159,  -159,  -159,   113,   -17,   247,   131,
     -14,  -159,    82,   240,   294,   330,   240,  -159,  -159,   240,
      14,    35,   164,  -159,   240,   127,   240,  -159,  -159,  -159
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    24,    25,    26,    27,     3,     5,
       6,     7,     0,     4,    17,     0,     0,     0,    14,     0,
      11,    12,     0,     0,     0,     9,     0,     0,    22,     0,
       0,    29,     0,    16,    10,   108,   111,   109,   110,     0,
       0,     0,     0,     0,     0,     0,    13,    56,    63,    65,
      67,    69,    71,    73,    75,    78,    83,    86,    89,    93,
     100,    21,    18,     0,    30,    22,     0,    15,    97,    96,
      98,    99,    94,    95,     0,    54,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,   105,     0,     0,     0,    23,     0,    20,    28,
     112,     0,    66,    89,     0,    68,    70,    72,    74,    76,
      77,    79,    80,    81,    82,    84,    85,    87,    88,    90,
      91,    92,    57,    58,    59,    60,    61,    62,   102,   107,
       0,     0,     0,     0,     0,     0,     0,    33,    45,    42,
      38,     0,    35,    36,    37,    39,    40,    41,     0,    31,
      55,     0,   103,     0,   101,     0,     0,     0,     0,    53,
       0,     0,    32,    34,    44,    64,   106,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,    43,    48,     0,
       0,     0,    46,    49,     0,     0,     0,    50,    51,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,  -159,   168,  -159,  -159,     6,   153,  -159,
    -159,  -159,  -159,   118,  -159,    10,  -159,   120,   121,  -159,
     -84,  -159,  -159,  -158,  -159,  -159,  -159,   -45,   -26,    39,
    -159,   132,   111,   134,   110,   135,    55,    29,    70,    71,
     -37,  -159,  -159,  -159
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    10,    15,    19,    20,    21,
      11,    16,    17,    62,    63,   149,    30,    31,   150,   151,
     152,   153,   171,   154,   155,   156,   157,   158,    75,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,   140,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      74,    46,    68,    69,    70,    71,    72,    73,   178,    76,
      65,   161,    12,   101,   102,     3,    66,   103,    12,   111,
     184,   104,    24,   110,    32,    77,    92,    93,    94,   111,
     162,   183,   114,    29,   186,    14,   163,   111,    18,   113,
     111,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   129,   130,   131,   139,   141,
     167,    33,   194,     4,     5,     6,     7,   173,   111,   132,
     133,   134,   135,   136,   137,    22,    29,    35,    36,    37,
      38,    39,    40,   195,   164,   160,   111,    25,    26,   111,
      84,    85,    86,    87,    41,    82,    83,    28,    42,   188,
      23,   170,   192,   174,   111,   193,    64,    43,    44,    27,
     197,    45,   199,   121,   122,   123,   124,   169,   176,    61,
     177,    88,    89,   180,   113,    95,    96,    97,    98,    99,
     100,    90,    91,   181,   111,   187,    26,   119,   120,   190,
     191,     4,     5,     6,     7,   142,   143,   144,   145,    67,
     146,    35,    36,    37,    38,    39,    40,    78,   125,   126,
      79,   127,   128,    80,    81,   105,   107,   111,    41,   159,
     165,   166,    42,   168,   179,   196,    13,   182,   185,    34,
     198,    43,    44,   108,   106,    45,   109,   105,   147,   115,
     117,   148,     4,     5,     6,     7,   142,   143,   144,   145,
     175,   146,    35,    36,    37,    38,    39,    40,   112,     0,
       0,     0,     0,   116,     0,     0,   118,     0,     0,    41,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,     0,     0,    45,     0,   105,   172,
       0,     0,   148,     4,     5,     6,     7,   142,   143,   144,
     145,     0,   146,    35,    36,    37,    38,    39,    40,     0,
      35,    36,    37,    38,    39,    40,     0,     0,     0,     0,
      41,     0,     0,     0,    42,     0,     0,    41,     0,     0,
       0,    42,     0,    43,    44,     0,     0,    45,     0,   105,
      43,    44,     0,   148,    45,     0,     0,     0,     0,     0,
     148,    35,    36,    37,    38,    39,    40,    35,    36,    37,
      38,    39,    40,     0,     0,     0,     0,     0,    41,     0,
       0,     0,    42,     0,    41,     0,     0,     0,    42,     0,
       0,    43,    44,     0,     0,    45,   138,    43,    44,     0,
       0,    45,   189,    35,    36,    37,    38,    39,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,     0,     0,    45
};

static const yytype_int16 yycheck[] =
{
      45,    27,    39,    40,    41,    42,    43,    44,   166,    29,
      48,    46,     2,    43,    44,     0,    54,    47,     8,    54,
     178,    51,    51,    48,    15,    45,    19,    20,    21,    54,
      48,    48,    77,    23,    48,    13,    54,    54,    13,    76,
      54,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,   103,   104,
     144,    52,    48,     3,     4,     5,     6,   151,    54,    95,
      96,    97,    98,    99,   100,    47,    66,    13,    14,    15,
      16,    17,    18,    48,    52,   111,    54,    53,    54,    54,
      22,    23,    24,    25,    30,    26,    27,    48,    34,   183,
      47,   146,   186,    53,    54,   189,    13,    43,    44,    37,
     194,    47,   196,    84,    85,    86,    87,    53,   163,    53,
     165,    35,    36,   168,   161,    37,    38,    39,    40,    41,
      42,    17,    18,    53,    54,    53,    54,    82,    83,   184,
     185,     3,     4,     5,     6,     7,     8,     9,    10,    52,
      12,    13,    14,    15,    16,    17,    18,    28,    88,    89,
      32,    90,    91,    33,    31,    49,    51,    54,    30,    52,
      47,    47,    34,    47,     7,    11,     8,   171,    47,    26,
      53,    43,    44,    65,    63,    47,    66,    49,    50,    78,
      80,    53,     3,     4,     5,     6,     7,     8,     9,    10,
     161,    12,    13,    14,    15,    16,    17,    18,    76,    -1,
      -1,    -1,    -1,    79,    -1,    -1,    81,    -1,    -1,    30,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    -1,    47,    -1,    49,    50,
      -1,    -1,    53,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    14,    15,    16,    17,    18,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    -1,    -1,    30,    -1,    -1,
      -1,    34,    -1,    43,    44,    -1,    -1,    47,    -1,    49,
      43,    44,    -1,    53,    47,    -1,    -1,    -1,    -1,    -1,
      53,    13,    14,    15,    16,    17,    18,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    34,    -1,    30,    -1,    -1,    -1,    34,    -1,
      -1,    43,    44,    -1,    -1,    47,    48,    43,    44,    -1,
      -1,    47,    48,    13,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,    67,     0,     3,     4,     5,     6,    68,    69,
      70,    75,    80,    69,    13,    71,    76,    77,    13,    72,
      73,    74,    47,    47,    51,    53,    54,    37,    48,    80,
      81,    82,    15,    52,    73,    13,    14,    15,    16,    17,
      18,    30,    34,    43,    44,    47,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     108,    53,    78,    79,    13,    48,    54,    52,   105,   105,
     105,   105,   105,   105,    92,    93,    29,    45,    28,    32,
      33,    31,    26,    27,    22,    23,    24,    25,    35,    36,
      17,    18,    19,    20,    21,    37,    38,    39,    40,    41,
      42,    43,    44,    47,    51,    49,    83,    51,    78,    82,
      48,    54,    96,   105,    92,    97,    98,    99,   100,   101,
     101,   102,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   105,    93,    93,    93,    93,    93,    93,    48,    92,
     107,    92,     7,     8,     9,    10,    12,    50,    53,    80,
      83,    84,    85,    86,    88,    89,    90,    91,    92,    52,
      93,    46,    48,    54,    52,    47,    47,    85,    47,    53,
      92,    87,    50,    85,    53,    94,    92,    92,    88,     7,
      92,    53,    72,    48,    88,    47,    48,    53,    85,    48,
      92,    92,    85,    85,    48,    48,    11,    85,    53,    85
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    67,    66,    68,    68,    69,    69,    71,    70,
      72,    72,    73,    73,    74,    74,    74,    76,    75,    77,
      75,    78,    79,    78,    80,    80,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    87,    86,    88,    88,    89,    89,    90,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     101,   101,   101,   102,   102,   102,   103,   103,   103,   104,
     104,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   106,   106,   106,   106,   107,   107,   108,   108,
     108,   108,   108
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     0,     4,
       3,     1,     1,     3,     1,     4,     3,     0,     6,     0,
       7,     1,     0,     2,     1,     1,     1,     1,     3,     1,
       2,     4,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     2,     1,     5,     7,     5,     6,
       7,     7,     3,     2,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     1,     5,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     2,     2,     2,     2,     2,     2,
       1,     4,     3,     4,     2,     2,     3,     1,     1,     1,
       1,     1,     3
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
#line 216 "parse.y"
         { init_symbol_table(); }
#line 1685 "y.tab.c"
    break;

  case 3: /* program: $@1 translation_unit  */
#line 217 "parse.y"
         {
           print_syntax_success("C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1696 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 235 "parse.y"
                                       {
                              current_type = token_to_type((yyvsp[0].type_val));
                            }
#line 1704 "y.tab.c"
    break;

  case 9: /* global_variable_declaration: data_type $@2 init_declarator_list SEMICOLON_TOK  */
#line 238 "parse.y"
                            { print_syntax_success("Global variable declaration"); }
#line 1710 "y.tab.c"
    break;

  case 13: /* init_declarator: declarator ASSIGN_TOK assignment_expr  */
#line 247 "parse.y"
                 { print_syntax_success("Variable initialization"); }
#line 1716 "y.tab.c"
    break;

  case 14: /* declarator: ID_TOK  */
#line 251 "parse.y"
           {
             if (!add_symbol((yyvsp[0].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free((yyvsp[0].string_val));
           }
#line 1727 "y.tab.c"
    break;

  case 15: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK  */
#line 258 "parse.y"
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
#line 1746 "y.tab.c"
    break;

  case 16: /* declarator: ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 273 "parse.y"
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
#line 1765 "y.tab.c"
    break;

  case 17: /* $@3: %empty  */
#line 290 "parse.y"
                                       {
                       if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free((yyvsp[0].string_val));
                     }
#line 1776 "y.tab.c"
    break;

  case 18: /* function_declaration: data_type ID_TOK $@3 LPAREN_TOK RPAREN_TOK function_tail  */
#line 296 "parse.y"
                     {
                       print_syntax_success("Function (no parameters)");
                     }
#line 1784 "y.tab.c"
    break;

  case 19: /* $@4: %empty  */
#line 299 "parse.y"
                                      {
                       if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                           error_count++;
                       }
                       free((yyvsp[0].string_val));
                     }
#line 1795 "y.tab.c"
    break;

  case 20: /* function_declaration: data_type ID_TOK $@4 LPAREN_TOK parameter_list RPAREN_TOK function_tail  */
#line 305 "parse.y"
                     {
                       print_syntax_success("Function (with parameters)");
                     }
#line 1803 "y.tab.c"
    break;

  case 21: /* function_tail: SEMICOLON_TOK  */
#line 311 "parse.y"
               { /* Function prototype */ }
#line 1809 "y.tab.c"
    break;

  case 22: /* $@5: %empty  */
#line 312 "parse.y"
               { enter_scope(); }
#line 1815 "y.tab.c"
    break;

  case 23: /* function_tail: $@5 compound_statement  */
#line 313 "parse.y"
               {
                 /* Function definition */
                 exit_scope();
               }
#line 1824 "y.tab.c"
    break;

  case 24: /* data_type: INT_TOK  */
#line 320 "parse.y"
                   { (yyval.type_val) = INT_TOK; }
#line 1830 "y.tab.c"
    break;

  case 25: /* data_type: FLOAT_TOK  */
#line 321 "parse.y"
                     { (yyval.type_val) = FLOAT_TOK; }
#line 1836 "y.tab.c"
    break;

  case 26: /* data_type: CHAR_TOK  */
#line 322 "parse.y"
                    { (yyval.type_val) = CHAR_TOK; }
#line 1842 "y.tab.c"
    break;

  case 27: /* data_type: VOID_TOK  */
#line 323 "parse.y"
                    { (yyval.type_val) = VOID_TOK; }
#line 1848 "y.tab.c"
    break;

  case 30: /* parameter: data_type ID_TOK  */
#line 332 "parse.y"
          {
            if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free((yyvsp[0].string_val));
          }
#line 1859 "y.tab.c"
    break;

  case 31: /* parameter: data_type ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 339 "parse.y"
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
#line 1878 "y.tab.c"
    break;

  case 32: /* compound_statement: LBRACE_TOK statement_list RBRACE_TOK  */
#line 357 "parse.y"
                   { print_syntax_success("Compound statement"); }
#line 1884 "y.tab.c"
    break;

  case 33: /* compound_statement: LBRACE_TOK RBRACE_TOK  */
#line 359 "parse.y"
                   { print_syntax_success("Empty compound statement"); }
#line 1890 "y.tab.c"
    break;

  case 42: /* $@6: %empty  */
#line 377 "parse.y"
                                 {
                        current_type = token_to_type((yyvsp[0].type_val));
                      }
#line 1898 "y.tab.c"
    break;

  case 43: /* declaration_statement: data_type $@6 init_declarator_list SEMICOLON_TOK  */
#line 380 "parse.y"
                      { print_syntax_success("Local variable declaration"); }
#line 1904 "y.tab.c"
    break;

  case 44: /* expression_statement: expression SEMICOLON_TOK  */
#line 385 "parse.y"
                     { print_syntax_success("Expression statement"); }
#line 1910 "y.tab.c"
    break;

  case 45: /* expression_statement: SEMICOLON_TOK  */
#line 387 "parse.y"
                     { print_syntax_success("Empty statement"); }
#line 1916 "y.tab.c"
    break;

  case 46: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 392 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("If statement");
                      
                      // Generate code: if (expr == 0) goto after_if
                      // Note: In a full implementation, labels would be generated
                      // with proper backpatching
                      char* false_label = new_label();
                      gen("ifFalse", (yyvsp[-2].expr_info).place, "", false_label);
                      emit_label(false_label);
                    }
#line 1932 "y.tab.c"
    break;

  case 47: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement  */
#line 404 "parse.y"
                    {
                      check_condition_type((yyvsp[-4].expr_info).type);
                      print_syntax_success("If-else statement");
                      
                      // Generate code for if-else
                      // Note: This is a simplified version
                      // Full implementation would generate:
                      // ifFalse expr goto L_else
                      // ... if_body ...
                      // goto L_end
                      // L_else: ... else_body ...
                      // L_end:
                    }
#line 1950 "y.tab.c"
    break;

  case 48: /* iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 421 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("While loop");
                      
                      // Generate while loop code
                      // Note: Full implementation would generate:
                      // L_begin: ifFalse expr goto L_end
                      // ... loop_body ...
                      // goto L_begin
                      // L_end:
                      char* begin_label = new_label();
                      char* end_label = new_label();
                      gen("label_begin", "", "", begin_label);
                      gen("ifFalse", (yyvsp[-2].expr_info).place, "", end_label);
                      gen("goto", "", "", begin_label);
                      gen("label_end", "", "", end_label);
                    }
#line 1972 "y.tab.c"
    break;

  case 49: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement  */
#line 439 "parse.y"
                    { print_syntax_success("For loop"); }
#line 1978 "y.tab.c"
    break;

  case 50: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement  */
#line 441 "parse.y"
                    { print_syntax_success("For loop with increment"); }
#line 1984 "y.tab.c"
    break;

  case 51: /* iteration_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK  */
#line 443 "parse.y"
                    {
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("Do-while loop");
                      
                      // Generate: do-while loop structure
                      char* begin_label = new_label();
                      gen("ifTrue", (yyvsp[-2].expr_info).place, "", begin_label);
                    }
#line 1997 "y.tab.c"
    break;

  case 52: /* jump_statement: RETURN_TOK expression SEMICOLON_TOK  */
#line 455 "parse.y"
               { print_syntax_success("Return statement with value"); }
#line 2003 "y.tab.c"
    break;

  case 53: /* jump_statement: RETURN_TOK SEMICOLON_TOK  */
#line 457 "parse.y"
               { print_syntax_success("Return statement"); }
#line 2009 "y.tab.c"
    break;

  case 54: /* expression: assignment_expr  */
#line 464 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2015 "y.tab.c"
    break;

  case 55: /* expression: expression COMMA_TOK assignment_expr  */
#line 466 "parse.y"
           { (yyval.expr_info).type = (yyvsp[0].expr_info).type; (yyval.expr_info).is_lvalue = 0; }
#line 2021 "y.tab.c"
    break;

  case 56: /* assignment_expr: ternary_expr  */
#line 470 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2027 "y.tab.c"
    break;

  case 57: /* assignment_expr: unary_expr ASSIGN_TOK assignment_expr  */
#line 472 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                  
                  // Generate three-address code: lhs = rhs
                  gen("=", (yyvsp[0].expr_info).place, "", (yyvsp[-2].expr_info).place);
                  (yyval.expr_info).place = (yyvsp[-2].expr_info).place;
                }
#line 2041 "y.tab.c"
    break;

  case 58: /* assignment_expr: unary_expr ADD_ASSIGN_TOK assignment_expr  */
#line 482 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2052 "y.tab.c"
    break;

  case 59: /* assignment_expr: unary_expr SUB_ASSIGN_TOK assignment_expr  */
#line 489 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2063 "y.tab.c"
    break;

  case 60: /* assignment_expr: unary_expr MUL_ASSIGN_TOK assignment_expr  */
#line 496 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2074 "y.tab.c"
    break;

  case 61: /* assignment_expr: unary_expr DIV_ASSIGN_TOK assignment_expr  */
#line 503 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2085 "y.tab.c"
    break;

  case 62: /* assignment_expr: unary_expr MOD_ASSIGN_TOK assignment_expr  */
#line 510 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2096 "y.tab.c"
    break;

  case 63: /* ternary_expr: logical_or_expr  */
#line 519 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2102 "y.tab.c"
    break;

  case 64: /* ternary_expr: logical_or_expr TERNARY_TOK expression COLON_TOK ternary_expr  */
#line 521 "parse.y"
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
#line 2117 "y.tab.c"
    break;

  case 65: /* logical_or_expr: logical_and_expr  */
#line 534 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2123 "y.tab.c"
    break;

  case 66: /* logical_or_expr: logical_or_expr OR_TOK logical_and_expr  */
#line 536 "parse.y"
                {
                  (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "||");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2132 "y.tab.c"
    break;

  case 67: /* logical_and_expr: bit_or_expr  */
#line 543 "parse.y"
                 { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2138 "y.tab.c"
    break;

  case 68: /* logical_and_expr: logical_and_expr AND_TOK bit_or_expr  */
#line 545 "parse.y"
                 {
                   (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&&");
                   (yyval.expr_info).is_lvalue = 0;
                 }
#line 2147 "y.tab.c"
    break;

  case 69: /* bit_or_expr: bit_xor_expr  */
#line 552 "parse.y"
            { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2153 "y.tab.c"
    break;

  case 70: /* bit_or_expr: bit_or_expr BIT_OR_TOK bit_xor_expr  */
#line 554 "parse.y"
            {
              (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "|");
              (yyval.expr_info).is_lvalue = 0;
            }
#line 2162 "y.tab.c"
    break;

  case 71: /* bit_xor_expr: bit_and_expr  */
#line 561 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2168 "y.tab.c"
    break;

  case 72: /* bit_xor_expr: bit_xor_expr BIT_XOR_TOK bit_and_expr  */
#line 563 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "^");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2177 "y.tab.c"
    break;

  case 73: /* bit_and_expr: equality_expr  */
#line 570 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2183 "y.tab.c"
    break;

  case 74: /* bit_and_expr: bit_and_expr BIT_AND_TOK equality_expr  */
#line 572 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2192 "y.tab.c"
    break;

  case 75: /* equality_expr: relational_expr  */
#line 579 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2198 "y.tab.c"
    break;

  case 76: /* equality_expr: equality_expr EQ_TOK relational_expr  */
#line 581 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "==");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2207 "y.tab.c"
    break;

  case 77: /* equality_expr: equality_expr NEQ_TOK relational_expr  */
#line 586 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "!=");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2216 "y.tab.c"
    break;

  case 78: /* relational_expr: shift_expr  */
#line 593 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2222 "y.tab.c"
    break;

  case 79: /* relational_expr: relational_expr LT_TOK shift_expr  */
#line 595 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2231 "y.tab.c"
    break;

  case 80: /* relational_expr: relational_expr GT_TOK shift_expr  */
#line 600 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2240 "y.tab.c"
    break;

  case 81: /* relational_expr: relational_expr LE_TOK shift_expr  */
#line 605 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2249 "y.tab.c"
    break;

  case 82: /* relational_expr: relational_expr GE_TOK shift_expr  */
#line 610 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2258 "y.tab.c"
    break;

  case 83: /* shift_expr: additive_expr  */
#line 617 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2264 "y.tab.c"
    break;

  case 84: /* shift_expr: shift_expr BIT_LSHIFT_TOK additive_expr  */
#line 619 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<<");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2273 "y.tab.c"
    break;

  case 85: /* shift_expr: shift_expr BIT_RSHIFT_TOK additive_expr  */
#line 624 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">>");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2282 "y.tab.c"
    break;

  case 86: /* additive_expr: multiplicative_expr  */
#line 631 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2288 "y.tab.c"
    break;

  case 87: /* additive_expr: additive_expr ADD_TOK multiplicative_expr  */
#line 633 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                (yyval.expr_info).is_lvalue = 0;
                
                // Generate: temp = arg1 + arg2
                (yyval.expr_info).place = new_temp();
                gen("+", (yyvsp[-2].expr_info).place, (yyvsp[0].expr_info).place, (yyval.expr_info).place);
              }
#line 2301 "y.tab.c"
    break;

  case 88: /* additive_expr: additive_expr SUB_TOK multiplicative_expr  */
#line 642 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                (yyval.expr_info).is_lvalue = 0;
                
                // Generate: temp = arg1 - arg2
                (yyval.expr_info).place = new_temp();
                gen("-", (yyvsp[-2].expr_info).place, (yyvsp[0].expr_info).place, (yyval.expr_info).place);
              }
#line 2314 "y.tab.c"
    break;

  case 89: /* multiplicative_expr: unary_expr  */
#line 653 "parse.y"
                    { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2320 "y.tab.c"
    break;

  case 90: /* multiplicative_expr: multiplicative_expr MUL_TOK unary_expr  */
#line 655 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                      (yyval.expr_info).is_lvalue = 0;
                      
                      // Generate: temp = arg1 * arg2
                      (yyval.expr_info).place = new_temp();
                      gen("*", (yyvsp[-2].expr_info).place, (yyvsp[0].expr_info).place, (yyval.expr_info).place);
                    }
#line 2333 "y.tab.c"
    break;

  case 91: /* multiplicative_expr: multiplicative_expr DIV_TOK unary_expr  */
#line 664 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                      (yyval.expr_info).is_lvalue = 0;
                      
                      // Generate: temp = arg1 / arg2
                      (yyval.expr_info).place = new_temp();
                      gen("/", (yyvsp[-2].expr_info).place, (yyvsp[0].expr_info).place, (yyval.expr_info).place);
                    }
#line 2346 "y.tab.c"
    break;

  case 92: /* multiplicative_expr: multiplicative_expr MOD_TOK unary_expr  */
#line 673 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                      (yyval.expr_info).is_lvalue = 0;
                      
                      // Generate: temp = arg1 % arg2
                      (yyval.expr_info).place = new_temp();
                      gen("%", (yyvsp[-2].expr_info).place, (yyvsp[0].expr_info).place, (yyval.expr_info).place);
                    }
#line 2359 "y.tab.c"
    break;

  case 93: /* unary_expr: postfix_expr  */
#line 684 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2365 "y.tab.c"
    break;

  case 94: /* unary_expr: INC_TOK unary_expr  */
#line 686 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Increment operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2377 "y.tab.c"
    break;

  case 95: /* unary_expr: DEC_TOK unary_expr  */
#line 694 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Decrement operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2389 "y.tab.c"
    break;

  case 96: /* unary_expr: SUB_TOK unary_expr  */
#line 702 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Unary minus requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
             
             // Generate: temp = - arg
             (yyval.expr_info).place = new_temp();
             gen("uminus", (yyvsp[0].expr_info).place, "", (yyval.expr_info).place);
           }
#line 2407 "y.tab.c"
    break;

  case 97: /* unary_expr: ADD_TOK unary_expr  */
#line 716 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Unary plus requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
             (yyval.expr_info).place = (yyvsp[0].expr_info).place;  // Unary plus doesn't change value
           }
#line 2422 "y.tab.c"
    break;

  case 98: /* unary_expr: NOT_TOK unary_expr  */
#line 727 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Logical NOT requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = TYPE_INT;
             (yyval.expr_info).is_lvalue = 0;
             
             // Generate: temp = ! arg
             (yyval.expr_info).place = new_temp();
             gen("!", (yyvsp[0].expr_info).place, "", (yyval.expr_info).place);
           }
#line 2440 "y.tab.c"
    break;

  case 99: /* unary_expr: BIT_NOT_TOK unary_expr  */
#line 741 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Bitwise NOT requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
             
             // Generate: temp = ~ arg
             (yyval.expr_info).place = new_temp();
             gen("~", (yyvsp[0].expr_info).place, "", (yyval.expr_info).place);
           }
#line 2458 "y.tab.c"
    break;

  case 100: /* postfix_expr: primary_expr  */
#line 757 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2464 "y.tab.c"
    break;

  case 101: /* postfix_expr: postfix_expr LBRACKET_TOK expression RBRACKET_TOK  */
#line 759 "parse.y"
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
#line 2481 "y.tab.c"
    break;

  case 102: /* postfix_expr: postfix_expr LPAREN_TOK RPAREN_TOK  */
#line 772 "parse.y"
              {
                print_syntax_success("Function call");
                (yyval.expr_info).type = TYPE_INT;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2491 "y.tab.c"
    break;

  case 103: /* postfix_expr: postfix_expr LPAREN_TOK argument_list RPAREN_TOK  */
#line 778 "parse.y"
              {
                print_syntax_success("Function call with arguments");
                (yyval.expr_info).type = TYPE_INT;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2501 "y.tab.c"
    break;

  case 104: /* postfix_expr: postfix_expr INC_TOK  */
#line 784 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Increment operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2513 "y.tab.c"
    break;

  case 105: /* postfix_expr: postfix_expr DEC_TOK  */
#line 792 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Decrement operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2525 "y.tab.c"
    break;

  case 108: /* primary_expr: ID_TOK  */
#line 806 "parse.y"
             {
               if (!is_variable_declared((yyvsp[0].string_val))) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, (yyvsp[0].string_val));
                   error_count++;
                   (yyval.expr_info).type = TYPE_UNKNOWN;
                   (yyval.expr_info).is_lvalue = 0;
                   (yyval.expr_info).place = strdup("unknown");
               } else {
                   symbol_node_t* sym = lookup_symbol((yyvsp[0].string_val));
                   (yyval.expr_info).type = sym->type;
                   (yyval.expr_info).is_lvalue = !sym->is_array;
                   (yyval.expr_info).place = strdup((yyvsp[0].string_val));  // Variable name is its place
               }
               free((yyvsp[0].string_val));
             }
#line 2545 "y.tab.c"
    break;

  case 109: /* primary_expr: INTCONST_TOK  */
#line 822 "parse.y"
             {
               (yyval.expr_info).type = TYPE_INT;
               (yyval.expr_info).is_lvalue = 0;
               
               // Integer constant - convert to string for place
               char* const_str = (char*)malloc(20);
               sprintf(const_str, "%d", (yyvsp[0].int_val));
               (yyval.expr_info).place = const_str;
             }
#line 2559 "y.tab.c"
    break;

  case 110: /* primary_expr: FLOATCONST_TOK  */
#line 832 "parse.y"
             {
               (yyval.expr_info).type = TYPE_FLOAT;
               (yyval.expr_info).is_lvalue = 0;
               
               // Float constant - convert to string for place
               char* const_str = (char*)malloc(20);
               sprintf(const_str, "%g", (yyvsp[0].float_val));
               (yyval.expr_info).place = const_str;
             }
#line 2573 "y.tab.c"
    break;

  case 111: /* primary_expr: STRING_TOK  */
#line 842 "parse.y"
             {
               (yyval.expr_info).type = TYPE_CHAR_PTR;
               (yyval.expr_info).is_lvalue = 0;
               (yyval.expr_info).place = (yyvsp[0].string_val);  // Use string literal as place
             }
#line 2583 "y.tab.c"
    break;

  case 112: /* primary_expr: LPAREN_TOK expression RPAREN_TOK  */
#line 848 "parse.y"
             {
               (yyval.expr_info) = (yyvsp[-1].expr_info);  // Parenthesized expression inherits everything
             }
#line 2591 "y.tab.c"
    break;


#line 2595 "y.tab.c"

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

#line 853 "parse.y"


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
    printf("=== C COMPILER: LEXICAL + SYNTAX + TYPE CHECKING + ICG ===\n");
    printf("Parsing input...\n\n");

    // Initialize intermediate code generation
    init_icg();

    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No errors found!\n");
        } else {
            printf("Parsing completed with %d error(s).\n", error_count);
        }
        
        // Close ICG and write to file
        close_icg();
        print_quad_array();
    } else {
        printf("\n=== PARSING FAILED ===\n");
        printf("Errors found at line %d\n", line_number);
        close_icg();
    }

    return 0;
}

void yyerror(char *s) {
    printf("SYNTAX ERROR (Line %d): %s near '%s'\n", line_number, s, yytext);
    error_count++;
}
