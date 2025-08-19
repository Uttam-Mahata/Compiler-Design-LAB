#include "lex.h"

char *yytext = NULL;
int yyleng = 0;
int yylineno = 1;
FILE *yyin = NULL;

static char token_buffer[256];
static int buffer_index = 0;

static const char *keywords[] = {
    "int", "float", "char", "for", "while", "if", "else",
    NULL
};

// Initialize lexer
void init_lexer(FILE *input) {
    yyin = input;
    yylineno = 1;
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
    }
    return c;
}

// Put character back to input
static void unget_char(int c) {
    if (c != EOF) {
        ungetc(c, yyin);
        if (c == '\n') {
            yylineno--;
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
    yytext = malloc(strlen(token_buffer) + 1);
    if (yytext) {
        strcpy(yytext, token_buffer);
    }
    yyleng = buffer_index;
    buffer_index = 0;
}

// Main lexical analyzer function
TokenType yylex(void) {
    int c;
    buffer_index = 0;

    // Skip whitespace and newlines
    while ((c = get_char()) != EOF && (c == ' ' || c == '\t' || c == '\n')) {
    }

    if (c == EOF) {
        if (yytext) {
            free(yytext);
        }
        yytext = malloc(1);
        if (yytext) {
            yytext[0] = '\0';
        }
        yyleng = 0;
        return TOKEN_EOF;
    }

    /* Handle identifiers and keywords */
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

    // Handle integer constants
    if (isdigit(c)) {
        add_to_buffer(c);
        while ((c = get_char()) != EOF && isdigit(c)) {
            add_to_buffer(c);
        }
        unget_char(c);
        finalize_token();
        return TOKEN_INTEGER;
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
        case ';':
            finalize_token();
            return TOKEN_SEMICOLON;
        
        // Arithmetic operators
        case '+':
            c = get_char();
            if (c == '+' || c == '=') {
                add_to_buffer(c);
                finalize_token();
                return c == '=' ? TOKEN_ASSIGNMENT_OP : TOKEN_ARITHMETIC_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_ARITHMETIC_OP;
            }
            
        case '-':
            c = get_char();
            if (c == '-' || c == '=') {
                add_to_buffer(c);
                finalize_token();
                return c == '=' ? TOKEN_ASSIGNMENT_OP : TOKEN_ARITHMETIC_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_ARITHMETIC_OP;
            }
            
        case '*':
        case '/':
        case '%':
            c = get_char();
            if (c == '=') {
                add_to_buffer(c);
                finalize_token();
                return TOKEN_ASSIGNMENT_OP;
            } else {
                unget_char(c);
                finalize_token();
                return TOKEN_ARITHMETIC_OP;
            }

        /* Assignment and relational operators */
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

        /* Logical operators */
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

        default:
            finalize_token();
            return TOKEN_ERROR;
    }
}

/*Convert token type to string*/
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_INTEGER: return "INTEGER";
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
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

/*Print token information*/
void print_token(TokenType type) {
    printf("Line %d: %-15s '%s'\n", yylineno, token_type_to_string(type), yytext);
}
