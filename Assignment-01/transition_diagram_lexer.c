#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_IDENTIFIER,
    TOKEN_INTEGER,
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
    TOKEN_SEMICOLON,
    TOKEN_ERROR
} TokenType;

// States for transition diagram
typedef enum {
    STATE_START = 0,
    STATE_IDENTIFIER,
    STATE_INTEGER,
    STATE_PLUS,
    STATE_MINUS,
    STATE_MULTIPLY,
    STATE_DIVIDE,
    STATE_MODULO,
    STATE_ASSIGN,
    STATE_LESS,
    STATE_GREATER,
    STATE_NOT,
    STATE_AND,
    STATE_OR,
    STATE_XOR,
    STATE_LSHIFT,
    STATE_RSHIFT,
    STATE_FINAL
} State;

// Global variables (yylex style)
char *yytext = NULL;
int yyleng = 0;
int yylineno = 1;
FILE *yyin = NULL;

// Buffer for building tokens
static char token_buffer[256];
static int buffer_index = 0;
static int current_char;

// Keywords table
static const char *keywords[] = {
    "int", "float", "char", "for", "while", "if", "else", "return",
    NULL
};

// Function prototypes
void init_lexer(FILE *input);
void cleanup_lexer(void);
int get_char(void);
void unget_char(int c);
void add_to_buffer(int c);
void finalize_token(void);
int is_keyword(const char *str);
TokenType transition_diagram_lexer(void);
const char* token_type_to_string(TokenType type);
const char* state_to_string(State state);
void print_token(TokenType type);
void print_state_transition(State from, State to, char input);

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

// Get next character from input
int get_char(void) {
    int c = fgetc(yyin);
    if (c == '\n') {
        yylineno++;
    }
    return c;
}

// Put character back to input
void unget_char(int c) {
    if (c != EOF) {
        ungetc(c, yyin);
        if (c == '\n') {
            yylineno--;
        }
    }
}

// Add character to token buffer
void add_to_buffer(int c) {
    if (buffer_index < sizeof(token_buffer) - 1) {
        token_buffer[buffer_index++] = c;
    }
}

// Finalize token
void finalize_token(void) {
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

// Check if string is a keyword
int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Convert state to string
const char* state_to_string(State state) {
    switch (state) {
        case STATE_START: return "START";
        case STATE_IDENTIFIER: return "IDENTIFIER";
        case STATE_INTEGER: return "INTEGER";
        case STATE_PLUS: return "PLUS";
        case STATE_MINUS: return "MINUS";
        case STATE_MULTIPLY: return "MULTIPLY";
        case STATE_DIVIDE: return "DIVIDE";
        case STATE_MODULO: return "MODULO";
        case STATE_ASSIGN: return "ASSIGN";
        case STATE_LESS: return "LESS";
        case STATE_GREATER: return "GREATER";
        case STATE_NOT: return "NOT";
        case STATE_AND: return "AND";
        case STATE_OR: return "OR";
        case STATE_XOR: return "XOR";
        case STATE_LSHIFT: return "LSHIFT";
        case STATE_RSHIFT: return "RSHIFT";
        case STATE_FINAL: return "FINAL";
        default: return "UNKNOWN";
    }
}

// Print state transition for debugging/visualization
void print_state_transition(State from, State to, char input) {
    if (input == '\n') {
        printf("%s --(\\n)--> %s\n", state_to_string(from), state_to_string(to));
    } else if (input == '\t') {
        printf("%s --(\\t)--> %s\n", state_to_string(from), state_to_string(to));
    } else if (input == ' ') {
        printf("%s --(space)--> %s\n", state_to_string(from), state_to_string(to));
    } else {
        printf("%s --(%c)--> %s\n", state_to_string(from), input, state_to_string(to));
    }
}

// Main transition diagram lexer
TokenType transition_diagram_lexer(void) {
    State current_state = STATE_START;
    buffer_index = 0;
    
    printf("\n=== Transition Diagram Execution ===\n");
    
    while (1) {
        switch (current_state) {
            case STATE_START:
                current_char = get_char();
                
                // Skip whitespace
                while (current_char == ' ' || current_char == '\t' || current_char == '\n') {
                    if (current_char == EOF) break;
                    current_char = get_char();
                }
                
                if (current_char == EOF) {
                    printf("START --(EOF)--> FINAL\n");
                    finalize_token();
                    return TOKEN_EOF;
                }
                
                // Transition based on input character
                if (isalpha(current_char) || current_char == '_') {
                    print_state_transition(STATE_START, STATE_IDENTIFIER, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_IDENTIFIER;
                }
                else if (isdigit(current_char)) {
                    print_state_transition(STATE_START, STATE_INTEGER, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_INTEGER;
                }
                else if (current_char == '+') {
                    print_state_transition(STATE_START, STATE_PLUS, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_PLUS;
                }
                else if (current_char == '-') {
                    print_state_transition(STATE_START, STATE_MINUS, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_MINUS;
                }
                else if (current_char == '*') {
                    print_state_transition(STATE_START, STATE_MULTIPLY, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_MULTIPLY;
                }
                else if (current_char == '/') {
                    print_state_transition(STATE_START, STATE_DIVIDE, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_DIVIDE;
                }
                else if (current_char == '%') {
                    print_state_transition(STATE_START, STATE_MODULO, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_MODULO;
                }
                else if (current_char == '=') {
                    print_state_transition(STATE_START, STATE_ASSIGN, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_ASSIGN;
                }
                else if (current_char == '<') {
                    print_state_transition(STATE_START, STATE_LESS, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_LESS;
                }
                else if (current_char == '>') {
                    print_state_transition(STATE_START, STATE_GREATER, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_GREATER;
                }
                else if (current_char == '!') {
                    print_state_transition(STATE_START, STATE_NOT, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_NOT;
                }
                else if (current_char == '&') {
                    print_state_transition(STATE_START, STATE_AND, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_AND;
                }
                else if (current_char == '|') {
                    print_state_transition(STATE_START, STATE_OR, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_OR;
                }
                else if (current_char == '^') {
                    print_state_transition(STATE_START, STATE_XOR, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_XOR;
                }
                // Single character tokens
                else if (current_char == '(') {
                    printf("START --(%c)--> FINAL\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_LPAREN;
                }
                else if (current_char == ')') {
                    printf("START --(%c)--> FINAL\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RPAREN;
                }
                else if (current_char == '{') {
                    printf("START --(%c)--> FINAL\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_LBRACE;
                }
                else if (current_char == '}') {
                    printf("START --(%c)--> FINAL\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RBRACE;
                }
                else if (current_char == ';') {
                    printf("START --(%c)--> FINAL\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_SEMICOLON;
                }
                else {
                    printf("START --(%c)--> ERROR\n", current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ERROR;
                }
                break;
                
            case STATE_IDENTIFIER:
                current_char = get_char();
                if (isalnum(current_char) || current_char == '_') {
                    print_state_transition(STATE_IDENTIFIER, STATE_IDENTIFIER, current_char);
                    add_to_buffer(current_char);
                }
                else {
                    printf("IDENTIFIER --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    if (is_keyword(yytext)) {
                        return TOKEN_KEYWORD;
                    }
                    return TOKEN_IDENTIFIER;
                }
                break;
                
            case STATE_INTEGER:
                current_char = get_char();
                if (isdigit(current_char)) {
                    print_state_transition(STATE_INTEGER, STATE_INTEGER, current_char);
                    add_to_buffer(current_char);
                }
                else {
                    printf("INTEGER --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_INTEGER;
                }
                break;
                
            case STATE_PLUS:
                current_char = get_char();
                if (current_char == '+') {
                    print_state_transition(STATE_PLUS, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                else if (current_char == '=') {
                    print_state_transition(STATE_PLUS, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("PLUS --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                break;
                
            case STATE_MINUS:
                current_char = get_char();
                if (current_char == '-') {
                    print_state_transition(STATE_MINUS, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                else if (current_char == '=') {
                    print_state_transition(STATE_MINUS, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("MINUS --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                break;
                
            case STATE_MULTIPLY:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_MULTIPLY, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("MULTIPLY --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                break;
                
            case STATE_DIVIDE:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_DIVIDE, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("DIVIDE --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                break;
                
            case STATE_MODULO:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_MODULO, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("MODULO --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ARITHMETIC_OP;
                }
                break;
                
            case STATE_ASSIGN:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_ASSIGN, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                else {
                    printf("ASSIGN --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                break;
                
            case STATE_LESS:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_LESS, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                else if (current_char == '<') {
                    print_state_transition(STATE_LESS, STATE_LSHIFT, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_LSHIFT;
                }
                else {
                    printf("LESS --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                break;
                
            case STATE_GREATER:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_GREATER, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                else if (current_char == '>') {
                    print_state_transition(STATE_GREATER, STATE_RSHIFT, current_char);
                    add_to_buffer(current_char);
                    current_state = STATE_RSHIFT;
                }
                else {
                    printf("GREATER --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                break;
                
            case STATE_LSHIFT:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_LSHIFT, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("LSHIFT --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_BITWISE_OP;
                }
                break;
                
            case STATE_RSHIFT:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_RSHIFT, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("RSHIFT --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_BITWISE_OP;
                }
                break;
                
            case STATE_NOT:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_NOT, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_RELATIONAL_OP;
                }
                else {
                    printf("NOT --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_LOGICAL_OP;
                }
                break;
                
            case STATE_AND:
                current_char = get_char();
                if (current_char == '&') {
                    print_state_transition(STATE_AND, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_LOGICAL_OP;
                }
                else if (current_char == '=') {
                    print_state_transition(STATE_AND, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("AND --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_BITWISE_OP;
                }
                break;
                
            case STATE_OR:
                current_char = get_char();
                if (current_char == '|') {
                    print_state_transition(STATE_OR, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_LOGICAL_OP;
                }
                else if (current_char == '=') {
                    print_state_transition(STATE_OR, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("OR --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_BITWISE_OP;
                }
                break;
                
            case STATE_XOR:
                current_char = get_char();
                if (current_char == '=') {
                    print_state_transition(STATE_XOR, STATE_FINAL, current_char);
                    add_to_buffer(current_char);
                    finalize_token();
                    return TOKEN_ASSIGNMENT_OP;
                }
                else {
                    printf("XOR --(other)--> FINAL\n");
                    unget_char(current_char);
                    finalize_token();
                    return TOKEN_BITWISE_OP;
                }
                break;
                
            default:
                finalize_token();
                return TOKEN_ERROR;
        }
    }
}

// Convert token type to string
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

// Print token information
void print_token(TokenType type) {
    printf("\nResult: Line %d: %-15s '%s'\n", yylineno, token_type_to_string(type), yytext);
}

// Main function
int main(int argc, char *argv[]) {
    FILE *input_file;
    TokenType token;

    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }

    init_lexer(input_file);

    printf("=== TRANSITION DIAGRAM BASED LEXICAL ANALYZER ===\n");
    printf("Analyzing file: %s\n", argv[1]);
    printf("===================================================\n");

    do {
        token = transition_diagram_lexer();
        if (token != TOKEN_EOF) {
            print_token(token);
        }
    } while (token != TOKEN_EOF);

    printf("===================================================\n");
    printf("Lexical analysis completed.\n");

    cleanup_lexer();
    fclose(input_file);
    
    return 0;
}
