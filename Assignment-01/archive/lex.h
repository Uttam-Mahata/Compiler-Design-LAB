// /home/uttam/Compiler-Design-LAB/lexical_analyzer.h
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_FLOAT,
    TOKEN_CHARACTER,
    TOKEN_STRING,
    TOKEN_KEYWORD,
    TOKEN_ARITHMETIC_OP,
    TOKEN_RELATIONAL_OP,
    TOKEN_LOGICAL_OP,
    TOKEN_BITWISE_OP,
    TOKEN_ASSIGNMENT_OP,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_PREPROCESSOR,
    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char *lexeme;
    int line_number;
    int column;
} Token;

// Global variables (similar to lex/yacc)
extern char *yytext;     // Current token text
extern int yyleng;       // Length of current token
extern int yylineno;     // Current line number
extern int yycolumn;     // Current column number
extern FILE *yyin;       // Input file pointer

// Function declarations
TokenType yylex(void);
void init_lexer(FILE *input);
void cleanup_lexer(void);
const char* token_type_to_string(TokenType type);
int is_keyword(const char *str);
void print_token(TokenType type);

#endif