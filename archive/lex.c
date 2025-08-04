
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "lex.h"

// Global variables
char *yytext = NULL;
int yyleng = 0;
int yylineno = 1;
int yycolumn = 1;
FILE *yyin = NULL;

// Buffer for building tokens
static char token_buffer[256];
static int buffer_index = 0;

// Keywords table
static const char *keywords[] = {
    "int", "float", "char", "double", "void",
    "if", "else", "for", "while", "do",
    "switch", "case", "default", "break", "continue",
    "return", "sizeof", "typedef", "struct", "union",
    "enum", "static", "extern", "auto", "register",
    "const", "volatile", "signed", "unsigned",
    NULL
};

// Initialize lexer
void init_lexer(FILE *input) {
    yyin = input;
    yylineno = 1;
    yycolumn = 1;
    buffer_index = 0;
    if (yytext) {
        free(yytext);
        yytext = NULL;
    }
}

// Cleanup lexer
void cleanup_lexer(void) {
    if (yytext) {
        free(yytext);
        yytext = NULL;
    }
}

// Check if string is a keyword
int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Get next character from input
static int get_char(void) {
    int c = fgetc(yyin);
    if (c == '\n') {
        yylineno++;
        yycolumn = 1;
    } else if (c != EOF) {
        yycolumn++;
    }
    return c;
}

// Put character back to input
static void unget_char(int c) {
    if (c != EOF) {
        ungetc(c, yyin);
        if (c == '\n') {
            yylineno--;
        } else {
            yycolumn--;
        }
    }
}

// Add character to token buffer
static void add_to_buffer(int c) {
    if (buffer_index < sizeof(token_buffer) - 1) {
        token_buffer[buffer_index++] = c;
    }
}

// Finalize token
static void finalize_token(void) {
    token_buffer[buffer_index] = '\0';
    if (yytext) {
        free(yytext);
    }
    yytext = strdup(token_buffer);
    yyleng = buffer_index;
    buffer_index = 0;
}

// Main lexical analyzer function
TokenType yylex(void) {
    int c;
    buffer_index = 0;

    // Skip whitespace (except newlines)
    while ((c = get_char()) != EOF && (c == ' ' || c == '\t')) {
        // Skip whitespace
    }

    if (c == EOF) {
        finalize_token();
        return TOKEN_EOF;
    }

    // Handle newlines
    if (c == '\n') {
        add_to_buffer(c);
        finalize_token();
        return TOKEN_NEWLINE;
    }

    // Handle preprocessor directives
    if (c == '#') {
        add_to_buffer(c);
        finalize_token();
        return TOKEN_PREPROCESSOR;
    }

    // Handle string literals
    if (c == '"') {
        add_to_buffer(c);
        while ((c = get_char()) != EOF && c != '"') {
            add_to_buffer(c);
            if (c == '\\') {
                // Handle escape sequences
                c = get_char();
                if (c != EOF) {
                    add_to_buffer(c);
                }
            }
        }
        if (c == '"') {
            add_to_buffer(c);
        }
        finalize_token();
        return TOKEN_STRING;
    }

    // Handle identifiers and keywords
    if (isalpha(c) || c == '_') {
        add_to_buffer(c);
        while ((c = get_char()) != EOF && (isalnum(c) || c == '_')) {
            add_to_buffer(c);
        }
        unget_char(c);
        finalize_token();
        
        if (is_keyword(yytext)) {
            return TOKEN_KEYWORD;
        }
        return TOKEN_IDENTIFIER;
    }

    // Handle numbers (integers, floats, and hex)
    if (isdigit(c)) {
        add_to_buffer(c);
        
        // Check for hexadecimal
        if (c == '0') {
            c = get_char();
            if (c == 'x' || c == 'X') {
                add_to_buffer(c);
                while ((c = get_char()) != EOF && (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) {
                    add_to_buffer(c);
                }
                unget_char(c);
                finalize_token();
                return TOKEN_INTEGER;
            } else {
                unget_char(c);
            }
        }
        
        int has_dot = 0;
        while ((c = get_char()) != EOF && (isdigit(c) || c == '.')) {
            if (c == '.') {
                if (has_dot) {
                    unget_char(c);
                    break;
                }
                has_dot = 1;
            }
            add_to_buffer(c);
        }
        unget_char(c);
        finalize_token();
        
        return has_dot ? TOKEN_FLOAT : TOKEN_INTEGER;
    }

    // Handle character constants
    if (c == '\'') {
        add_to_buffer(c);
        c = get_char();
        if (c != EOF) {
            add_to_buffer(c);
            if (c == '\\') {
                // Handle escape sequences
                c = get_char();
                if (c != EOF) {
                    add_to_buffer(c);
                }
            }
            c = get_char();
            if (c == '\'') {
                add_to_buffer(c);
            } else {
                unget_char(c);
            }
        }
        finalize_token();
        return TOKEN_CHARACTER;
    }

    // Handle operators and punctuation
    add_to_buffer(c);
    
    switch (c) {
        // Parentheses and braces
        case '(':
            finalize_token();
            return TOKEN_LPAREN;
        case ')':
            finalize_token();
            return TOKEN_RPAREN;
        case '{':
            finalize_token();
            return TOKEN_LBRACE;
        case '}':
            finalize_token();
            return TOKEN_RBRACE;
        case '[':
            finalize_token();
            return TOKEN_LBRACKET;
        case ']':
            finalize_token();
            return TOKEN_RBRACKET;
        
        // Arithmetic operators
        case '+':
            c = get_char();
            if (c == '+' || c == '=') {
                add_to_buffer(c);
            } else {
                unget_char(c);
            }
            finalize_token();
            return TOKEN_ARITHMETIC_OP;
            
        case '-':
            c = get_char();
            if (c == '-' || c == '=' || c == '>') {
                add_to_buffer(c);
            } else {
                unget_char(c);
            }
            finalize_token();
            return TOKEN_ARITHMETIC_OP;
            
        case '*':
        case '/':
        case '%':
            c = get_char();
            if (c == '=') {
                add_to_buffer(c);
            } else {
                unget_char(c);
            }
            finalize_token();
            return TOKEN_ARITHMETIC_OP;

        // Assignment operator
        case '=':
            c = get_char();
            if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_RELATIONAL_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_ASSIGNMENT_OP;
            }

        // Relational operators
        case '<':
        case '>':
            {
                char first_char = c;
                c = get_char();
                if (c == '=') {
                    add_to_buffer(c);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                } else if ((first_char == '<' && c == '<') || (first_char == '>' && c == '>')) {
                    add_to_buffer(c);
                    // Check for <<= or >>=
                    int next = get_char();
                    if (next == '=') {
                        add_to_buffer(next);
                        finalize_token();
                        return TOKEN_ASSIGNMENT_OP;
                    } else {
                        unget_char(next);
                        finalize_token();
                        return TOKEN_BITWISE_OP;
                    }
                } else {
                    unget_char(c);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
            }

        case '!':
            c = get_char();
            if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_RELATIONAL_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_LOGICAL_OP;
            }

        // Logical operators
        case '&':
            c = get_char();
            if (c == '&') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_LOGICAL_OP;
            } else if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_ASSIGNMENT_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_BITWISE_OP;
            }

        case '|':
            c = get_char();
            if (c == '|') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_LOGICAL_OP;
            } else if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_ASSIGNMENT_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_BITWISE_OP;
            }

        // Bitwise operators
        case '^':
            c = get_char();
            if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_ASSIGNMENT_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_BITWISE_OP;
            }

        case '~':
            finalize_token();
            return TOKEN_BITWISE_OP;

        // Punctuation
        case ';':
            finalize_token();
            return TOKEN_SEMICOLON;
        case ',':
            finalize_token();
            return TOKEN_COMMA;
        case '.':
            finalize_token();
            return TOKEN_DOT;
        case ':':
            finalize_token();
            return TOKEN_ERROR; // For now, treat colon as error since it's not in our token list

        default:
            finalize_token();
            return TOKEN_ERROR;
    }
}

// Convert token type to string
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_INTEGER: return "INTEGER";
        case TOKEN_FLOAT: return "FLOAT";
        case TOKEN_CHARACTER: return "CHARACTER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_KEYWORD: return "KEYWORD";
        case TOKEN_ARITHMETIC_OP: return "ARITHMETIC_OP";
        case TOKEN_RELATIONAL_OP: return "RELATIONAL_OP";
        case TOKEN_LOGICAL_OP: return "LOGICAL_OP";
        case TOKEN_BITWISE_OP: return "BITWISE_OP";
        case TOKEN_ASSIGNMENT_OP: return "ASSIGNMENT_OP";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_DOT: return "DOT";
        case TOKEN_PREPROCESSOR: return "PREPROCESSOR";
        case TOKEN_WHITESPACE: return "WHITESPACE";
        case TOKEN_NEWLINE: return "NEWLINE";
        case TOKEN_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

// Print token information
void print_token(TokenType type) {
    printf("Line %d, Column %d: %-15s '%s'\n", 
           yylineno, yycolumn - yyleng, 
           token_type_to_string(type), yytext);
}