#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
    TOKEN_KEYWORD,
    TOKEN_ARITHMETIC_OP,    
    TOKEN_RELATIONAL_OP,    
    TOKEN_LOGICAL_OP,       // &&, ||, !
    TOKEN_BITWISE_OP,       // &, |, ^, ~, <<, >>
    TOKEN_ASSIGNMENT_OP,    // =, +=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=
    TOKEN_LPAREN,           // (
    TOKEN_RPAREN,           // )
    TOKEN_LBRACE,           // {
    TOKEN_RBRACE,           // }
    TOKEN_SEMICOLON,        // ;
    TOKEN_ERROR
} TokenType;

extern char *yytext;
extern int yyleng;
extern int yylineno;
extern FILE *yyin;

// Function declarations
TokenType yylex(void);
void init_lexer(FILE *input);
void cleanup_lexer(void);
const char* token_type_to_string(TokenType type);
int is_keyword(const char *str);
void print_token(TokenType type);

#endif
