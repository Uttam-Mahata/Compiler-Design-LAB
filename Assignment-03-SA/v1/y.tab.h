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
