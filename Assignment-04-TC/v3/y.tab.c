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
    // Check if both operands are numeric
    if (!is_numeric_type(left) || !is_numeric_type(right)) {
        char msg[256];
        sprintf(msg, "Binary operator '%s' requires numeric operands, got '%s' and '%s'",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    // Check type compatibility
    if (!are_types_compatible(left, right)) {
        char msg[256];
        sprintf(msg, "Type mismatch in binary operation '%s': '%s' and '%s' are not compatible",
                op, type_to_string(left), type_to_string(right));
        print_type_error(msg);
        return TYPE_UNKNOWN;
    }
    
    // Return the result type (promote to float if either operand is float)
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
    
    return TYPE_INT; // Relational operators return boolean (represented as int)
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
    
    // Arrays cannot be assigned directly
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
        sprintf(msg, "Cannot dereference non-pointer type '%s' - attempting to use an integer as a pointer",
                type_to_string(type));
        print_type_error(msg);
    }
}

#line 211 "y.tab.c"

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
#line 141 "parse.y"

    int int_val;
    float float_val;
    char* string_val;
    int type_val;
    struct {
        data_type_t type;
        int is_lvalue;
    } expr_info;

#line 401 "y.tab.c"

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
  YYSYMBOL_translation_unit = 67,          /* translation_unit  */
  YYSYMBOL_external_declaration = 68,      /* external_declaration  */
  YYSYMBOL_declaration = 69,               /* declaration  */
  YYSYMBOL_70_2 = 70,                      /* $@2  */
  YYSYMBOL_function_definition = 71,       /* function_definition  */
  YYSYMBOL_72_3 = 72,                      /* $@3  */
  YYSYMBOL_73_4 = 73,                      /* $@4  */
  YYSYMBOL_74_5 = 74,                      /* $@5  */
  YYSYMBOL_75_6 = 75,                      /* $@6  */
  YYSYMBOL_function_body = 76,             /* function_body  */
  YYSYMBOL_77_7 = 77,                      /* $@7  */
  YYSYMBOL_78_8 = 78,                      /* $@8  */
  YYSYMBOL_data_type = 79,                 /* data_type  */
  YYSYMBOL_declarator_list = 80,           /* declarator_list  */
  YYSYMBOL_declarator = 81,                /* declarator  */
  YYSYMBOL_parameter_list = 82,            /* parameter_list  */
  YYSYMBOL_parameter = 83,                 /* parameter  */
  YYSYMBOL_compound_statement = 84,        /* compound_statement  */
  YYSYMBOL_statement_list = 85,            /* statement_list  */
  YYSYMBOL_statement = 86,                 /* statement  */
  YYSYMBOL_declaration_statement = 87,     /* declaration_statement  */
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
  YYSYMBOL_unary_operator = 106,           /* unary_operator  */
  YYSYMBOL_postfix_expr = 107,             /* postfix_expr  */
  YYSYMBOL_argument_list = 108,            /* argument_list  */
  YYSYMBOL_primary_expr = 109              /* primary_expr  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   718

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  150
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

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
       0,   207,   207,   207,   216,   217,   221,   222,   226,   226,
     228,   234,   240,   249,   249,   259,   259,   269,   269,   279,
     279,   292,   292,   298,   298,   307,   308,   309,   310,   314,
     315,   316,   322,   330,   338,   355,   372,   378,   387,   388,
     389,   395,   403,   411,   423,   427,   431,   437,   446,   447,
     451,   452,   453,   454,   455,   456,   457,   466,   470,   472,
     474,   483,   488,   493,   499,   505,   514,   519,   521,   523,
     528,   534,   543,   545,   547,   553,   562,   564,   566,   573,
     582,   584,   590,   597,   604,   611,   618,   625,   631,   639,
     641,   652,   658,   664,   672,   674,   681,   683,   690,   692,
     699,   701,   708,   710,   717,   719,   724,   731,   733,   738,
     743,   748,   755,   757,   762,   769,   771,   776,   783,   785,
     790,   795,   802,   804,   812,   820,   832,   833,   834,   835,
     838,   840,   854,   861,   868,   874,   880,   887,   894,   902,
     912,   913,   914,   920,   928,   945,   950,   955,   961,   965,
     973
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
  "UNARY_MINUS", "UNARY_PLUS", "$accept", "program", "$@1",
  "translation_unit", "external_declaration", "declaration", "$@2",
  "function_definition", "$@3", "$@4", "$@5", "$@6", "function_body",
  "$@7", "$@8", "data_type", "declarator_list", "declarator",
  "parameter_list", "parameter", "compound_statement", "statement_list",
  "statement", "declaration_statement", "expression_statement",
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

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-143)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -128,    23,   264,  -128,    35,  -128,  -128,  -128,  -128,    21,
    -128,  -128,  -128,    16,    70,     8,  -128,  -128,    79,   142,
      35,   132,   228,    35,  -128,    27,  -128,    76,    87,    98,
     108,    10,    35,   119,     1,  -128,  -128,  -128,  -128,    91,
     159,   102,   159,  -128,  -128,  -128,  -128,   120,   175,    17,
    -128,   172,    46,  -128,   157,   159,   181,   301,   162,  -128,
     172,   173,  -128,  -128,  -128,  -128,   385,   177,  -128,  -128,
      94,   230,   231,   385,   140,   407,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,   671,   671,   451,   232,  -128,  -128,
      29,  -128,   283,  -128,  -128,  -128,  -128,  -128,  -128,    38,
    -128,  -128,    66,   255,   262,   270,   281,   -20,   249,   218,
     243,   237,   178,   671,   208,  -128,  -128,  -128,   473,   627,
     309,   671,   495,   271,  -128,    51,  -128,  -128,   277,    54,
     -12,  -128,   334,  -128,  -128,   671,  -128,   517,   671,   671,
     539,   671,   671,   671,   671,   671,   671,   671,   671,   671,
     671,   671,   671,   671,   671,   671,   671,   671,   671,   561,
     671,   671,   671,   671,   671,  -128,  -128,  -128,   429,   583,
     280,    68,   627,   282,    88,   286,    92,  -128,   671,  -128,
    -128,   671,  -128,  -128,    94,  -128,  -128,  -128,  -128,    55,
     255,  -128,   285,    97,   262,   270,   281,   -20,   249,   249,
     218,   218,   218,   218,   243,   243,   237,   237,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   297,
    -128,   124,   126,   302,   129,   385,   385,   385,   649,   671,
     671,   385,   385,   385,   385,   671,   671,   671,   671,  -128,
     671,  -128,   605,  -128,   671,  -128,  -128,  -128,   305,  -128,
     385,   128,   136,  -128,  -128,  -128,   344,  -128,  -128,    96,
    -128,   137,  -128,   174,  -128,   385,   303,   385,  -128,  -128,
    -128
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,    25,    26,    27,    28,     0,
       5,     6,     7,     0,    33,     0,    30,     4,     0,    33,
       0,     0,     0,     0,    12,     0,    11,     0,     0,     0,
       0,     0,    10,     0,     0,    35,    31,    32,    29,     0,
       0,     0,     0,     9,    37,    36,    34,     0,     0,     0,
      39,     0,     0,    14,    42,     0,     0,     0,    21,    18,
       0,     0,    40,    16,    41,    38,     0,     0,    20,    43,
       0,     0,     0,     0,     0,     0,   144,   147,   145,   146,
     126,   127,   128,   129,     0,     0,     0,     0,    59,    57,
       0,    52,     0,    49,    50,    51,    53,    54,    55,     0,
      76,    80,     0,    94,    96,    98,   100,   102,   104,   107,
     112,   115,     0,     0,   122,   130,    24,    56,     0,     0,
       0,     0,     0,     0,    73,     0,   123,   124,     0,     0,
       0,    45,     0,    22,    48,    60,    58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   125,   138,   139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,    74,    72,
     150,   149,   148,    47,    46,    44,    78,    79,    77,     0,
      95,   118,     0,     0,    97,    99,   101,   103,   105,   106,
     108,   109,   110,   111,   113,   114,   116,   117,   119,   120,
     121,    87,    88,    81,    82,    83,    84,    85,    86,     0,
     134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
     136,   135,     0,   133,   132,   131,    71,    70,    76,    66,
       0,     0,     0,    65,    64,    63,    61,    93,    92,    80,
      90,     0,   143,     0,    67,     0,     0,     0,    68,    69,
      62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -128,  -128,  -128,   348,   122,  -128,  -128,  -128,  -128,
    -128,  -128,   298,  -128,  -128,     3,     0,   103,   317,    58,
    -128,   273,   -73,  -128,  -115,  -128,  -128,  -128,   -72,  -127,
      73,  -128,   222,   221,   223,   220,   225,   118,   171,   163,
     169,   -69,  -128,  -128,  -128,  -128
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     9,    10,    89,    20,    12,    27,    28,
      29,    30,    59,    66,    67,    90,    15,    16,    49,    50,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   222,   115
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     120,    14,    45,   125,   172,    13,   145,   146,   186,    23,
     188,    23,    13,    21,   129,   126,   127,    18,    55,   134,
      31,    -3,     4,     3,     5,     6,     7,     8,    37,    19,
      18,   211,   213,   214,   215,   216,   217,   218,   183,   135,
      14,   117,    14,    48,   165,    48,   171,    55,    14,   174,
     176,   186,   178,    46,   186,   181,   230,   228,    48,   134,
      48,    24,    25,    43,    25,    56,   189,   138,   193,   226,
     191,    57,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   208,   209,   210,   230,
      21,   136,   137,   233,    60,   139,   221,   224,   237,   248,
      57,   235,   182,   186,   179,   137,   248,    14,   137,   137,
     186,   140,   -89,    62,   -89,    65,   227,   186,   -89,   -89,
     -89,    22,   137,    39,    11,   230,    36,   240,    38,   230,
     244,    11,    26,    32,    40,    36,   231,   230,   230,    47,
     234,   121,   137,   238,   -91,    41,   137,   117,   -91,   -91,
      51,   137,   246,   247,   249,    42,   251,   252,   253,   254,
     255,   256,     5,     6,     7,     8,   191,   191,   261,   191,
     263,    44,  -141,    53,   241,   230,   265,   264,   137,   158,
     242,   245,   137,   137,   266,  -142,    25,   122,    54,   -13,
     137,   137,   268,    22,   270,  -118,  -118,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,    61,  -118,
    -118,  -118,   -23,  -118,  -118,   159,   160,   161,   162,   163,
     164,    58,  -140,  -118,  -118,    69,  -118,   116,   137,    33,
    -118,  -118,  -118,   130,    63,     5,     6,     7,     8,    71,
      72,    73,    74,    34,    75,    76,    77,    78,    79,    80,
      81,   166,   167,   151,   152,   168,   155,   156,   157,   169,
     153,   154,    82,   198,   199,     4,    83,     5,     6,     7,
       8,   147,   148,   149,   150,    84,    85,   118,   119,    86,
      35,    87,   131,   141,    70,    88,     5,     6,     7,     8,
      71,    72,    73,    74,   142,    75,    76,    77,    78,    79,
      80,    81,    64,   143,     5,     6,     7,     8,   257,   258,
     259,   260,   144,    82,   204,   205,   173,    83,   200,   201,
     202,   203,   206,   207,   177,   180,    84,    85,   225,   229,
      86,   236,    87,   133,   232,   184,    88,     5,     6,     7,
       8,    71,    72,    73,    74,   239,    75,    76,    77,    78,
      79,    80,    81,   -78,   243,   267,   269,    17,    68,    52,
     132,   190,   194,   196,    82,   195,     0,     0,    83,   197,
       0,     0,     0,     0,     0,     0,     0,    84,    85,     0,
       0,    86,     0,    87,   185,     0,    70,    88,     5,     6,
       7,     8,    71,    72,    73,    74,     0,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,     0,   123,     0,
       0,     0,     0,     0,     0,    82,     0,     0,     0,    83,
      76,    77,    78,    79,    80,    81,     0,     0,    84,    85,
     219,     0,    86,     0,    87,     0,     0,    82,    88,     0,
       0,    83,    76,    77,    78,    79,    80,    81,     0,     0,
      84,    85,   128,     0,    86,     0,     0,     0,     0,    82,
     124,     0,     0,    83,    76,    77,    78,    79,    80,    81,
       0,     0,    84,    85,   170,     0,    86,   220,     0,     0,
       0,    82,     0,     0,     0,    83,    76,    77,    78,    79,
      80,    81,     0,     0,    84,    85,   175,     0,    86,     0,
       0,     0,     0,    82,     0,     0,     0,    83,    76,    77,
      78,    79,    80,    81,     0,     0,    84,    85,   187,     0,
      86,     0,     0,     0,     0,    82,     0,     0,     0,    83,
      76,    77,    78,    79,    80,    81,     0,     0,    84,    85,
     192,     0,    86,     0,     0,     0,     0,    82,     0,     0,
       0,    83,    76,    77,    78,    79,    80,    81,     0,     0,
      84,    85,   212,     0,    86,     0,     0,     0,     0,    82,
       0,     0,     0,    83,    76,    77,    78,    79,    80,    81,
       0,     0,    84,    85,   223,     0,    86,     0,     0,     0,
       0,    82,     0,     0,     0,    83,    76,    77,    78,    79,
      80,    81,     0,     0,    84,    85,   262,     0,    86,     0,
       0,     0,     0,    82,     0,     0,     0,    83,    76,    77,
      78,    79,    80,    81,     0,     0,    84,    85,     0,     0,
      86,     0,     0,     0,     0,    82,     0,     0,     0,    83,
      76,    77,    78,    79,    80,    81,     0,     0,    84,    85,
       0,     0,    86,     0,     0,     0,     0,    82,     0,     0,
       0,    83,    76,    77,    78,    79,    80,    81,     0,     0,
      84,    85,     0,     0,    86,     0,     0,     0,     0,    82,
      88,     0,     0,    83,    76,    77,    78,    79,    80,    81,
       0,     0,    84,    85,     0,     0,    86,   250,     0,     0,
       0,    82,     0,     0,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,    84,    85,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
      73,    13,     1,    75,   119,     2,    26,    27,   135,     1,
     137,     1,     9,    13,    86,    84,    85,     1,     1,    92,
      20,     0,     1,     0,     3,     4,     5,     6,     1,    13,
       1,   158,   159,   160,   161,   162,   163,   164,    50,     1,
      13,    53,    13,    40,   113,    42,   118,     1,    13,   121,
     122,   178,     1,    52,   181,     1,     1,   172,    55,   132,
      57,    53,    54,    53,    54,    48,   138,     1,   140,     1,
     139,    54,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,     1,
      90,    53,    54,     1,    48,    29,   168,   169,     1,   226,
      54,    46,    48,   230,    53,    54,   233,    13,    54,    54,
     237,    45,    46,    55,    48,    57,    48,   244,    52,    53,
      54,    51,    54,    47,     2,     1,    23,     1,    25,     1,
       1,     9,    53,     1,    47,    32,    48,     1,     1,    48,
      48,     1,    54,    46,    48,    47,    54,    53,    52,    53,
      48,    54,   225,   226,   227,    47,   228,   229,   231,   232,
     233,   234,     3,     4,     5,     6,   235,   236,   240,   238,
     242,    52,    48,    53,    48,     1,    48,   250,    54,     1,
      54,    52,    54,    54,    48,    48,    54,    47,    13,    47,
      54,    54,   265,    51,   267,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    51,    31,
      32,    33,    50,    35,    36,    37,    38,    39,    40,    41,
      42,    49,    48,    45,    46,    52,    48,    50,    54,     1,
      52,    53,    54,     1,    53,     3,     4,     5,     6,     7,
       8,     9,    10,    15,    12,    13,    14,    15,    16,    17,
      18,    43,    44,    35,    36,    47,    19,    20,    21,    51,
      17,    18,    30,   145,   146,     1,    34,     3,     4,     5,
       6,    22,    23,    24,    25,    43,    44,    47,    47,    47,
      52,    49,    50,    28,     1,    53,     3,     4,     5,     6,
       7,     8,     9,    10,    32,    12,    13,    14,    15,    16,
      17,    18,     1,    33,     3,     4,     5,     6,   235,   236,
     237,   238,    31,    30,   151,   152,     7,    34,   147,   148,
     149,   150,   153,   154,    53,    48,    43,    44,    48,    47,
      47,    46,    49,    50,    48,     1,    53,     3,     4,     5,
       6,     7,     8,     9,    10,    48,    12,    13,    14,    15,
      16,    17,    18,    48,    52,    11,    53,     9,    60,    42,
      87,   139,   141,   143,    30,   142,    -1,    -1,    34,   144,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    47,    -1,    49,    50,    -1,     1,    53,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,
      13,    14,    15,    16,    17,    18,    -1,    -1,    43,    44,
       1,    -1,    47,    -1,    49,    -1,    -1,    30,    53,    -1,
      -1,    34,    13,    14,    15,    16,    17,    18,    -1,    -1,
      43,    44,     1,    -1,    47,    -1,    -1,    -1,    -1,    30,
      53,    -1,    -1,    34,    13,    14,    15,    16,    17,    18,
      -1,    -1,    43,    44,     1,    -1,    47,    48,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    13,    14,    15,    16,
      17,    18,    -1,    -1,    43,    44,     1,    -1,    47,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    13,    14,
      15,    16,    17,    18,    -1,    -1,    43,    44,     1,    -1,
      47,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,
      13,    14,    15,    16,    17,    18,    -1,    -1,    43,    44,
       1,    -1,    47,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    13,    14,    15,    16,    17,    18,    -1,    -1,
      43,    44,     1,    -1,    47,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    34,    13,    14,    15,    16,    17,    18,
      -1,    -1,    43,    44,     1,    -1,    47,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    13,    14,    15,    16,
      17,    18,    -1,    -1,    43,    44,     1,    -1,    47,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    13,    14,
      15,    16,    17,    18,    -1,    -1,    43,    44,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    34,
      13,    14,    15,    16,    17,    18,    -1,    -1,    43,    44,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    34,    13,    14,    15,    16,    17,    18,    -1,    -1,
      43,    44,    -1,    -1,    47,    -1,    -1,    -1,    -1,    30,
      53,    -1,    -1,    34,    13,    14,    15,    16,    17,    18,
      -1,    -1,    43,    44,    -1,    -1,    47,    48,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,    66,     0,     1,     3,     4,     5,     6,    67,
      68,    69,    71,    79,    13,    80,    81,    68,     1,    13,
      70,    80,    51,     1,    53,    54,    53,    72,    73,    74,
      75,    80,     1,     1,    15,    52,    81,     1,    81,    47,
      47,    47,    47,    53,    52,     1,    52,    48,    79,    82,
      83,    48,    82,    53,    13,     1,    48,    54,    49,    76,
      48,    51,    83,    53,     1,    83,    77,    78,    76,    52,
       1,     7,     8,     9,    10,    12,    13,    14,    15,    16,
      17,    18,    30,    34,    43,    44,    47,    49,    53,    69,
      79,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   109,    50,    53,    47,    47,
      86,     1,    47,     1,    53,    92,   105,   105,     1,    92,
       1,    50,    85,    50,    86,     1,    53,    54,     1,    29,
      45,    28,    32,    33,    31,    26,    27,    22,    23,    24,
      25,    35,    36,    17,    18,    19,    20,    21,     1,    37,
      38,    39,    40,    41,    42,   105,    43,    44,    47,    51,
       1,    92,    88,     7,    92,     1,    92,    53,     1,    53,
      48,     1,    48,    50,     1,    50,    93,     1,    93,    92,
      96,   105,     1,    92,    97,    98,    99,   100,   101,   101,
     102,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     105,    93,     1,    93,    93,    93,    93,    93,    93,     1,
      48,    92,   108,     1,    92,    48,     1,    48,    88,    47,
       1,    48,    48,     1,    48,    46,    46,     1,    46,    48,
       1,    48,    54,    52,     1,    52,    86,    86,    93,    86,
      48,    92,    92,    86,    86,    86,    86,    94,    94,    94,
      94,    92,     1,    92,    86,    48,    48,    11,    86,    53,
      86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    66,    65,    67,    67,    68,    68,    70,    69,
      69,    69,    69,    72,    71,    73,    71,    74,    71,    75,
      71,    77,    76,    78,    76,    79,    79,    79,    79,    80,
      80,    80,    80,    81,    81,    81,    81,    81,    82,    82,
      82,    82,    83,    83,    84,    84,    84,    84,    85,    85,
      86,    86,    86,    86,    86,    86,    86,    87,    88,    88,
      88,    89,    89,    89,    89,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    91,    92,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    94,    94,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
     101,   101,   102,   102,   102,   103,   103,   103,   104,   104,
     104,   104,   105,   105,   105,   105,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     108,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     6,     0,     7,     0,     6,     0,
       7,     0,     4,     0,     3,     1,     1,     1,     1,     3,
       1,     3,     3,     1,     4,     3,     4,     4,     3,     1,
       3,     3,     2,     4,     3,     2,     3,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       2,     5,     7,     5,     5,     5,     5,     6,     7,     7,
       5,     5,     3,     2,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       5,     5,     5,     5,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     4,     4,     4,     3,     4,     4,     4,     2,     2,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     3,
       3
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
#line 207 "parse.y"
         { init_symbol_table(); }
#line 1780 "y.tab.c"
    break;

  case 3: /* program: $@1 translation_unit  */
#line 208 "parse.y"
         { 
           print_syntax_success("C program");
           printf("\n=== PARSING COMPLETED SUCCESSFULLY ===\n");
           printf("Total syntax errors: %d\n", error_count);
           print_symbol_table();
         }
#line 1791 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 226 "parse.y"
                       { current_type = token_to_type((yyvsp[0].type_val)); }
#line 1797 "y.tab.c"
    break;

  case 9: /* declaration: data_type $@2 declarator_list SEMICOLON_TOK  */
#line 227 "parse.y"
            { print_syntax_success("Variable declaration"); }
#line 1803 "y.tab.c"
    break;

  case 10: /* declaration: data_type declarator_list error  */
#line 229 "parse.y"
            {
              printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after variable declaration\n", line_number);
              error_count++;
              yyerrok;
            }
#line 1813 "y.tab.c"
    break;

  case 11: /* declaration: data_type error SEMICOLON_TOK  */
#line 235 "parse.y"
            {
              printf("SYNTAX ERROR (Line %d): Invalid variable declarator list\n", line_number);
              error_count++;
              yyerrok;
            }
#line 1823 "y.tab.c"
    break;

  case 12: /* declaration: error declarator_list SEMICOLON_TOK  */
#line 241 "parse.y"
            {
              printf("SYNTAX ERROR (Line %d): Invalid or missing data type in declaration\n", line_number);
              error_count++;
              yyerrok;
            }
#line 1833 "y.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 249 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                     }
#line 1844 "y.tab.c"
    break;

  case 14: /* function_definition: data_type ID_TOK $@3 LPAREN_TOK RPAREN_TOK SEMICOLON_TOK  */
#line 255 "parse.y"
                     { 
                       print_syntax_success("Function declaration");
                       free((yyvsp[-4].string_val));
                     }
#line 1853 "y.tab.c"
    break;

  case 15: /* $@4: %empty  */
#line 259 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                     }
#line 1864 "y.tab.c"
    break;

  case 16: /* function_definition: data_type ID_TOK $@4 LPAREN_TOK parameter_list RPAREN_TOK SEMICOLON_TOK  */
#line 265 "parse.y"
                     { 
                       print_syntax_success("Function declaration with parameters");
                       free((yyvsp[-5].string_val));
                     }
#line 1873 "y.tab.c"
    break;

  case 17: /* $@5: %empty  */
#line 269 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                     }
#line 1884 "y.tab.c"
    break;

  case 18: /* function_definition: data_type ID_TOK $@5 LPAREN_TOK RPAREN_TOK function_body  */
#line 275 "parse.y"
                     { 
                       print_syntax_success("Function definition");
                       free((yyvsp[-4].string_val));
                     }
#line 1893 "y.tab.c"
    break;

  case 19: /* $@6: %empty  */
#line 279 "parse.y"
                                      {
                      // Add function to symbol table
                      if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_GLOBAL, line_number, 1)) {
                          error_count++;
                      }
                     }
#line 1904 "y.tab.c"
    break;

  case 20: /* function_definition: data_type ID_TOK $@6 LPAREN_TOK parameter_list RPAREN_TOK function_body  */
#line 285 "parse.y"
                     { 
                       print_syntax_success("Function definition with parameters");
                       free((yyvsp[-5].string_val));
                     }
#line 1913 "y.tab.c"
    break;

  case 21: /* $@7: %empty  */
#line 292 "parse.y"
                          {
                enter_scope();
              }
#line 1921 "y.tab.c"
    break;

  case 22: /* function_body: LBRACE_TOK $@7 statement_list RBRACE_TOK  */
#line 295 "parse.y"
              {
                exit_scope();
              }
#line 1929 "y.tab.c"
    break;

  case 23: /* $@8: %empty  */
#line 298 "parse.y"
                          {
                enter_scope();
              }
#line 1937 "y.tab.c"
    break;

  case 24: /* function_body: LBRACE_TOK $@8 RBRACE_TOK  */
#line 301 "parse.y"
              {
                exit_scope();
              }
#line 1945 "y.tab.c"
    break;

  case 25: /* data_type: INT_TOK  */
#line 307 "parse.y"
                   { (yyval.type_val) = INT_TOK; }
#line 1951 "y.tab.c"
    break;

  case 26: /* data_type: FLOAT_TOK  */
#line 308 "parse.y"
                     { (yyval.type_val) = FLOAT_TOK; }
#line 1957 "y.tab.c"
    break;

  case 27: /* data_type: CHAR_TOK  */
#line 309 "parse.y"
                    { (yyval.type_val) = CHAR_TOK; }
#line 1963 "y.tab.c"
    break;

  case 28: /* data_type: VOID_TOK  */
#line 310 "parse.y"
                    { (yyval.type_val) = VOID_TOK; }
#line 1969 "y.tab.c"
    break;

  case 31: /* declarator_list: declarator_list error declarator  */
#line 317 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Missing comma ',' between variable declarations\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1979 "y.tab.c"
    break;

  case 32: /* declarator_list: declarator_list COMMA_TOK error  */
#line 323 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid declarator after comma\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 1989 "y.tab.c"
    break;

  case 33: /* declarator: ID_TOK  */
#line 331 "parse.y"
           {
             // Add variable to symbol table
             if (!add_symbol((yyvsp[0].string_val), current_type, get_current_scope_type(), line_number, 0)) {
                 error_count++;
             }
             free((yyvsp[0].string_val));
           }
#line 2001 "y.tab.c"
    break;

  case 34: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK RBRACKET_TOK  */
#line 339 "parse.y"
           {
             // Add array to symbol table with proper array type
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
             printf("SYNTAX OK: Array declaration '%s[%d]'\n", (yyvsp[-3].string_val), (yyvsp[-1].int_val));
             free((yyvsp[-3].string_val));
           }
#line 2022 "y.tab.c"
    break;

  case 35: /* declarator: ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 356 "parse.y"
           {
             // Add array without size
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
             printf("SYNTAX OK: Array declaration '%s[]'\n", (yyvsp[-2].string_val));
             free((yyvsp[-2].string_val));
           }
#line 2043 "y.tab.c"
    break;

  case 36: /* declarator: ID_TOK LBRACKET_TOK INTCONST_TOK error  */
#line 373 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Missing closing bracket ']' in array declaration\n", line_number);
             error_count++;
             yyerrok;
           }
#line 2053 "y.tab.c"
    break;

  case 37: /* declarator: ID_TOK LBRACKET_TOK error RBRACKET_TOK  */
#line 379 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Invalid array size\n", line_number);
             error_count++;
             yyerrok;
           }
#line 2063 "y.tab.c"
    break;

  case 40: /* parameter_list: parameter_list error parameter  */
#line 390 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Missing comma ',' between parameters\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2073 "y.tab.c"
    break;

  case 41: /* parameter_list: parameter_list COMMA_TOK error  */
#line 396 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Invalid parameter after comma\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2083 "y.tab.c"
    break;

  case 42: /* parameter: data_type ID_TOK  */
#line 404 "parse.y"
          {
            // Add parameter to symbol table
            if (!add_symbol((yyvsp[0].string_val), token_to_type((yyvsp[-1].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            free((yyvsp[0].string_val));
          }
#line 2095 "y.tab.c"
    break;

  case 43: /* parameter: data_type ID_TOK LBRACKET_TOK RBRACKET_TOK  */
#line 412 "parse.y"
          {
            // Add array parameter to symbol table
            if (!add_symbol((yyvsp[-2].string_val), token_to_type((yyvsp[-3].type_val)), SCOPE_FUNCTION, line_number, 0)) {
                error_count++;
            }
            printf("SYNTAX OK: Array parameter '%s[]'\n", (yyvsp[-2].string_val));
            free((yyvsp[-2].string_val));
          }
#line 2108 "y.tab.c"
    break;

  case 44: /* compound_statement: LBRACE_TOK statement_list RBRACE_TOK  */
#line 424 "parse.y"
                   { 
                     print_syntax_success("Compound statement");
                   }
#line 2116 "y.tab.c"
    break;

  case 45: /* compound_statement: LBRACE_TOK RBRACE_TOK  */
#line 428 "parse.y"
                   { 
                     print_syntax_success("Empty compound statement");
                   }
#line 2124 "y.tab.c"
    break;

  case 46: /* compound_statement: LBRACE_TOK statement_list error  */
#line 432 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Missing closing brace '}'\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 2134 "y.tab.c"
    break;

  case 47: /* compound_statement: LBRACE_TOK error RBRACE_TOK  */
#line 438 "parse.y"
                   {
                     printf("SYNTAX ERROR (Line %d): Invalid statement inside compound statement\n", line_number);
                     error_count++;
                     yyerrok;
                   }
#line 2144 "y.tab.c"
    break;

  case 56: /* statement: error SEMICOLON_TOK  */
#line 458 "parse.y"
          {
            printf("SYNTAX ERROR (Line %d): Invalid statement\n", line_number);
            error_count++;
            yyerrok;
          }
#line 2154 "y.tab.c"
    break;

  case 58: /* expression_statement: expression SEMICOLON_TOK  */
#line 471 "parse.y"
                     { print_syntax_success("Expression statement"); }
#line 2160 "y.tab.c"
    break;

  case 59: /* expression_statement: SEMICOLON_TOK  */
#line 473 "parse.y"
                     { print_syntax_success("Empty statement"); }
#line 2166 "y.tab.c"
    break;

  case 60: /* expression_statement: expression error  */
#line 475 "parse.y"
                     {
                       printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after expression\n", line_number);
                       error_count++;
                       yyerrok;
                     }
#line 2176 "y.tab.c"
    break;

  case 61: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 484 "parse.y"
                    { 
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("If statement"); 
                    }
#line 2185 "y.tab.c"
    break;

  case 62: /* selection_statement: IF_TOK LPAREN_TOK expression RPAREN_TOK statement ELSE_TOK statement  */
#line 489 "parse.y"
                    { 
                      check_condition_type((yyvsp[-4].expr_info).type);
                      print_syntax_success("If-else statement"); 
                    }
#line 2194 "y.tab.c"
    break;

  case 63: /* selection_statement: IF_TOK LPAREN_TOK expression error statement  */
#line 494 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in if condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2204 "y.tab.c"
    break;

  case 64: /* selection_statement: IF_TOK LPAREN_TOK error RPAREN_TOK statement  */
#line 500 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid expression in if condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2214 "y.tab.c"
    break;

  case 65: /* selection_statement: IF_TOK error expression RPAREN_TOK statement  */
#line 506 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing opening parenthesis '(' in if statement\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2224 "y.tab.c"
    break;

  case 66: /* iteration_statement: WHILE_TOK LPAREN_TOK expression RPAREN_TOK statement  */
#line 515 "parse.y"
                    { 
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("While loop"); 
                    }
#line 2233 "y.tab.c"
    break;

  case 67: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement RPAREN_TOK statement  */
#line 520 "parse.y"
                    { print_syntax_success("For loop"); }
#line 2239 "y.tab.c"
    break;

  case 68: /* iteration_statement: FOR_TOK LPAREN_TOK expression_statement expression_statement expression RPAREN_TOK statement  */
#line 522 "parse.y"
                    { print_syntax_success("For loop with increment"); }
#line 2245 "y.tab.c"
    break;

  case 69: /* iteration_statement: DO_TOK statement WHILE_TOK LPAREN_TOK expression RPAREN_TOK SEMICOLON_TOK  */
#line 524 "parse.y"
                    { 
                      check_condition_type((yyvsp[-2].expr_info).type);
                      print_syntax_success("Do-while loop"); 
                    }
#line 2254 "y.tab.c"
    break;

  case 70: /* iteration_statement: WHILE_TOK LPAREN_TOK expression error statement  */
#line 529 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2264 "y.tab.c"
    break;

  case 71: /* iteration_statement: WHILE_TOK LPAREN_TOK error RPAREN_TOK statement  */
#line 535 "parse.y"
                    {
                      printf("SYNTAX ERROR (Line %d): Invalid expression in while condition\n", line_number);
                      error_count++;
                      yyerrok;
                    }
#line 2274 "y.tab.c"
    break;

  case 72: /* jump_statement: RETURN_TOK expression SEMICOLON_TOK  */
#line 544 "parse.y"
               { print_syntax_success("Return statement with value"); }
#line 2280 "y.tab.c"
    break;

  case 73: /* jump_statement: RETURN_TOK SEMICOLON_TOK  */
#line 546 "parse.y"
               { print_syntax_success("Return statement"); }
#line 2286 "y.tab.c"
    break;

  case 74: /* jump_statement: RETURN_TOK expression error  */
#line 548 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Missing semicolon ';' after return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2296 "y.tab.c"
    break;

  case 75: /* jump_statement: RETURN_TOK error SEMICOLON_TOK  */
#line 554 "parse.y"
               {
                 printf("SYNTAX ERROR (Line %d): Invalid expression in return statement\n", line_number);
                 error_count++;
                 yyerrok;
               }
#line 2306 "y.tab.c"
    break;

  case 76: /* expression: assignment_expr  */
#line 563 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2312 "y.tab.c"
    break;

  case 77: /* expression: expression COMMA_TOK assignment_expr  */
#line 565 "parse.y"
           { (yyval.expr_info).type = (yyvsp[0].expr_info).type; (yyval.expr_info).is_lvalue = 0; }
#line 2318 "y.tab.c"
    break;

  case 78: /* expression: expression error assignment_expr  */
#line 567 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Missing comma ',' between expressions\n", line_number);
             error_count++;
             yyerrok;
             (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
           }
#line 2329 "y.tab.c"
    break;

  case 79: /* expression: expression COMMA_TOK error  */
#line 574 "parse.y"
           {
             printf("SYNTAX ERROR (Line %d): Invalid expression after comma\n", line_number);
             error_count++;
             yyerrok;
             (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
           }
#line 2340 "y.tab.c"
    break;

  case 80: /* assignment_expr: ternary_expr  */
#line 583 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2346 "y.tab.c"
    break;

  case 81: /* assignment_expr: unary_expr ASSIGN_TOK assignment_expr  */
#line 585 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2356 "y.tab.c"
    break;

  case 82: /* assignment_expr: unary_expr ADD_ASSIGN_TOK assignment_expr  */
#line 591 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2367 "y.tab.c"
    break;

  case 83: /* assignment_expr: unary_expr SUB_ASSIGN_TOK assignment_expr  */
#line 598 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2378 "y.tab.c"
    break;

  case 84: /* assignment_expr: unary_expr MUL_ASSIGN_TOK assignment_expr  */
#line 605 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2389 "y.tab.c"
    break;

  case 85: /* assignment_expr: unary_expr DIV_ASSIGN_TOK assignment_expr  */
#line 612 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2400 "y.tab.c"
    break;

  case 86: /* assignment_expr: unary_expr MOD_ASSIGN_TOK assignment_expr  */
#line 619 "parse.y"
                {
                  check_assignment_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, (yyvsp[-2].expr_info).is_lvalue);
                  check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                  (yyval.expr_info).type = (yyvsp[-2].expr_info).type;
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2411 "y.tab.c"
    break;

  case 87: /* assignment_expr: unary_expr error assignment_expr  */
#line 626 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 2421 "y.tab.c"
    break;

  case 88: /* assignment_expr: unary_expr ASSIGN_TOK error  */
#line 632 "parse.y"
                {
                  printf("SYNTAX ERROR (Line %d): Invalid expression after assignment operator\n", line_number);
                  error_count++;
                  yyerrok;
                }
#line 2431 "y.tab.c"
    break;

  case 89: /* ternary_expr: logical_or_expr  */
#line 640 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2437 "y.tab.c"
    break;

  case 90: /* ternary_expr: logical_or_expr TERNARY_TOK expression COLON_TOK ternary_expr  */
#line 642 "parse.y"
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
#line 2452 "y.tab.c"
    break;

  case 91: /* ternary_expr: logical_or_expr TERNARY_TOK expression error ternary_expr  */
#line 653 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Missing ':' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2462 "y.tab.c"
    break;

  case 92: /* ternary_expr: logical_or_expr TERNARY_TOK error COLON_TOK ternary_expr  */
#line 659 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Invalid expression in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2472 "y.tab.c"
    break;

  case 93: /* ternary_expr: logical_or_expr error expression COLON_TOK ternary_expr  */
#line 665 "parse.y"
             {
               printf("SYNTAX ERROR (Line %d): Missing '?' in ternary operator\n", line_number);
               error_count++;
               yyerrok;
             }
#line 2482 "y.tab.c"
    break;

  case 94: /* logical_or_expr: logical_and_expr  */
#line 673 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2488 "y.tab.c"
    break;

  case 95: /* logical_or_expr: logical_or_expr OR_TOK logical_and_expr  */
#line 675 "parse.y"
                {
                  (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "||");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2497 "y.tab.c"
    break;

  case 96: /* logical_and_expr: bit_or_expr  */
#line 682 "parse.y"
                 { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2503 "y.tab.c"
    break;

  case 97: /* logical_and_expr: logical_and_expr AND_TOK bit_or_expr  */
#line 684 "parse.y"
                 {
                   (yyval.expr_info).type = check_logical_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&&");
                   (yyval.expr_info).is_lvalue = 0;
                 }
#line 2512 "y.tab.c"
    break;

  case 98: /* bit_or_expr: bit_xor_expr  */
#line 691 "parse.y"
            { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2518 "y.tab.c"
    break;

  case 99: /* bit_or_expr: bit_or_expr BIT_OR_TOK bit_xor_expr  */
#line 693 "parse.y"
            {
              (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "|");
              (yyval.expr_info).is_lvalue = 0;
            }
#line 2527 "y.tab.c"
    break;

  case 100: /* bit_xor_expr: bit_and_expr  */
#line 700 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2533 "y.tab.c"
    break;

  case 101: /* bit_xor_expr: bit_xor_expr BIT_XOR_TOK bit_and_expr  */
#line 702 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "^");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2542 "y.tab.c"
    break;

  case 102: /* bit_and_expr: equality_expr  */
#line 709 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2548 "y.tab.c"
    break;

  case 103: /* bit_and_expr: bit_and_expr BIT_AND_TOK equality_expr  */
#line 711 "parse.y"
             {
               (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "&");
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2557 "y.tab.c"
    break;

  case 104: /* equality_expr: relational_expr  */
#line 718 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2563 "y.tab.c"
    break;

  case 105: /* equality_expr: equality_expr EQ_TOK relational_expr  */
#line 720 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "==");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2572 "y.tab.c"
    break;

  case 106: /* equality_expr: equality_expr NEQ_TOK relational_expr  */
#line 725 "parse.y"
              {
                (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "!=");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2581 "y.tab.c"
    break;

  case 107: /* relational_expr: shift_expr  */
#line 732 "parse.y"
                { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2587 "y.tab.c"
    break;

  case 108: /* relational_expr: relational_expr LT_TOK shift_expr  */
#line 734 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2596 "y.tab.c"
    break;

  case 109: /* relational_expr: relational_expr GT_TOK shift_expr  */
#line 739 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2605 "y.tab.c"
    break;

  case 110: /* relational_expr: relational_expr LE_TOK shift_expr  */
#line 744 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2614 "y.tab.c"
    break;

  case 111: /* relational_expr: relational_expr GE_TOK shift_expr  */
#line 749 "parse.y"
                {
                  (yyval.expr_info).type = check_relational_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">=");
                  (yyval.expr_info).is_lvalue = 0;
                }
#line 2623 "y.tab.c"
    break;

  case 112: /* shift_expr: additive_expr  */
#line 756 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2629 "y.tab.c"
    break;

  case 113: /* shift_expr: shift_expr BIT_LSHIFT_TOK additive_expr  */
#line 758 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "<<");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2638 "y.tab.c"
    break;

  case 114: /* shift_expr: shift_expr BIT_RSHIFT_TOK additive_expr  */
#line 763 "parse.y"
           {
             (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, ">>");
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2647 "y.tab.c"
    break;

  case 115: /* additive_expr: multiplicative_expr  */
#line 770 "parse.y"
              { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2653 "y.tab.c"
    break;

  case 116: /* additive_expr: additive_expr ADD_TOK multiplicative_expr  */
#line 772 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "+");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2662 "y.tab.c"
    break;

  case 117: /* additive_expr: additive_expr SUB_TOK multiplicative_expr  */
#line 777 "parse.y"
              {
                (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "-");
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2671 "y.tab.c"
    break;

  case 118: /* multiplicative_expr: unary_expr  */
#line 784 "parse.y"
                    { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2677 "y.tab.c"
    break;

  case 119: /* multiplicative_expr: multiplicative_expr MUL_TOK unary_expr  */
#line 786 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "*");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2686 "y.tab.c"
    break;

  case 120: /* multiplicative_expr: multiplicative_expr DIV_TOK unary_expr  */
#line 791 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "/");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2695 "y.tab.c"
    break;

  case 121: /* multiplicative_expr: multiplicative_expr MOD_TOK unary_expr  */
#line 796 "parse.y"
                    {
                      (yyval.expr_info).type = check_binary_op_type((yyvsp[-2].expr_info).type, (yyvsp[0].expr_info).type, "%");
                      (yyval.expr_info).is_lvalue = 0;
                    }
#line 2704 "y.tab.c"
    break;

  case 122: /* unary_expr: postfix_expr  */
#line 803 "parse.y"
           { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2710 "y.tab.c"
    break;

  case 123: /* unary_expr: INC_TOK unary_expr  */
#line 805 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Increment operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2722 "y.tab.c"
    break;

  case 124: /* unary_expr: DEC_TOK unary_expr  */
#line 813 "parse.y"
           {
             if (!(yyvsp[0].expr_info).is_lvalue) {
               print_type_error("Decrement operator requires an lvalue");
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2734 "y.tab.c"
    break;

  case 125: /* unary_expr: unary_operator unary_expr  */
#line 821 "parse.y"
           {
             if (!is_numeric_type((yyvsp[0].expr_info).type)) {
               char msg[256];
               sprintf(msg, "Unary operator requires numeric operand, got '%s'", type_to_string((yyvsp[0].expr_info).type));
               print_type_error(msg);
             }
             (yyval.expr_info).type = (yyvsp[0].expr_info).type;
             (yyval.expr_info).is_lvalue = 0;
           }
#line 2748 "y.tab.c"
    break;

  case 130: /* postfix_expr: primary_expr  */
#line 839 "parse.y"
             { (yyval.expr_info) = (yyvsp[0].expr_info); }
#line 2754 "y.tab.c"
    break;

  case 131: /* postfix_expr: postfix_expr LBRACKET_TOK expression RBRACKET_TOK  */
#line 841 "parse.y"
             {
               // Array subscripting
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
#line 2772 "y.tab.c"
    break;

  case 132: /* postfix_expr: postfix_expr LBRACKET_TOK expression error  */
#line 855 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing bracket ']'\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
              }
#line 2783 "y.tab.c"
    break;

  case 133: /* postfix_expr: postfix_expr LBRACKET_TOK error RBRACKET_TOK  */
#line 862 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid array index expression\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
              }
#line 2794 "y.tab.c"
    break;

  case 134: /* postfix_expr: postfix_expr LPAREN_TOK RPAREN_TOK  */
#line 869 "parse.y"
              { 
                print_syntax_success("Function call");
                (yyval.expr_info).type = TYPE_INT; // Assume int return type
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2804 "y.tab.c"
    break;

  case 135: /* postfix_expr: postfix_expr LPAREN_TOK argument_list RPAREN_TOK  */
#line 875 "parse.y"
              { 
                print_syntax_success("Function call with arguments");
                (yyval.expr_info).type = TYPE_INT; // Assume int return type
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2814 "y.tab.c"
    break;

  case 136: /* postfix_expr: postfix_expr LPAREN_TOK argument_list error  */
#line 881 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')' in function call\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
              }
#line 2825 "y.tab.c"
    break;

  case 137: /* postfix_expr: postfix_expr LPAREN_TOK error RPAREN_TOK  */
#line 888 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid function arguments\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN; (yyval.expr_info).is_lvalue = 0;
              }
#line 2836 "y.tab.c"
    break;

  case 138: /* postfix_expr: postfix_expr INC_TOK  */
#line 895 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Increment operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2848 "y.tab.c"
    break;

  case 139: /* postfix_expr: postfix_expr DEC_TOK  */
#line 903 "parse.y"
             {
               if (!(yyvsp[-1].expr_info).is_lvalue) {
                 print_type_error("Decrement operator requires an lvalue");
               }
               (yyval.expr_info).type = (yyvsp[-1].expr_info).type;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2860 "y.tab.c"
    break;

  case 142: /* argument_list: argument_list error expression  */
#line 915 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing comma ',' between function arguments\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2870 "y.tab.c"
    break;

  case 143: /* argument_list: argument_list COMMA_TOK error  */
#line 921 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression after comma in argument list\n", line_number);
                error_count++;
                yyerrok;
              }
#line 2880 "y.tab.c"
    break;

  case 144: /* primary_expr: ID_TOK  */
#line 929 "parse.y"
             {
               // Check if variable is declared before use
               if (!is_variable_declared((yyvsp[0].string_val))) {
                   printf("ERROR (Line %d): Variable '%s' used before declaration\n", line_number, (yyvsp[0].string_val));
                   error_count++;
                   (yyval.expr_info).type = TYPE_UNKNOWN;
                   (yyval.expr_info).is_lvalue = 0;
               } else {
                   symbol_t* sym = lookup_symbol((yyvsp[0].string_val));
                   printf("VARIABLE USE: '%s' (Type: %s, Scope: %s)\n", 
                          (yyvsp[0].string_val), type_to_string(sym->type), scope_to_string(sym->scope));
                   (yyval.expr_info).type = sym->type;
                   (yyval.expr_info).is_lvalue = !sym->is_array; // Arrays are not lvalues directly
               }
               free((yyvsp[0].string_val));
             }
#line 2901 "y.tab.c"
    break;

  case 145: /* primary_expr: INTCONST_TOK  */
#line 946 "parse.y"
             {
               (yyval.expr_info).type = TYPE_INT;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2910 "y.tab.c"
    break;

  case 146: /* primary_expr: FLOATCONST_TOK  */
#line 951 "parse.y"
             {
               (yyval.expr_info).type = TYPE_FLOAT;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2919 "y.tab.c"
    break;

  case 147: /* primary_expr: STRING_TOK  */
#line 956 "parse.y"
             { 
               free((yyvsp[0].string_val));
               (yyval.expr_info).type = TYPE_CHAR_PTR;
               (yyval.expr_info).is_lvalue = 0;
             }
#line 2929 "y.tab.c"
    break;

  case 148: /* primary_expr: LPAREN_TOK expression RPAREN_TOK  */
#line 962 "parse.y"
             {
               (yyval.expr_info) = (yyvsp[-1].expr_info);
             }
#line 2937 "y.tab.c"
    break;

  case 149: /* primary_expr: LPAREN_TOK expression error  */
#line 966 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Missing closing parenthesis ')'\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2949 "y.tab.c"
    break;

  case 150: /* primary_expr: LPAREN_TOK error RPAREN_TOK  */
#line 974 "parse.y"
              {
                printf("SYNTAX ERROR (Line %d): Invalid expression inside parentheses\n", line_number);
                error_count++;
                yyerrok;
                (yyval.expr_info).type = TYPE_UNKNOWN;
                (yyval.expr_info).is_lvalue = 0;
              }
#line 2961 "y.tab.c"
    break;


#line 2965 "y.tab.c"

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

#line 983 "parse.y"


#include "lex.yy.c"

// Define token_to_type function after tokens are defined
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
    printf("=== C LANGUAGE SUBSET PARSER WITH TYPE CHECKING ===\n");
    printf("Parsing input...\n\n");
    
    if (yyparse() == 0) {
        printf("\n=== PARSING SUCCESSFUL ===\n");
        if (error_count == 0) {
            printf("No syntax or type errors found!\n");
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
