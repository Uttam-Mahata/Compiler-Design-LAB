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
#line 136 "parse.y"

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

#line 219 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
