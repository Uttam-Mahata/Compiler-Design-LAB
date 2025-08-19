#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

int main(int argc, char *argv[]) {
    FILE *input_file;
    TokenType token;

    // Check command line arguments
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open input file
    input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Cannot open file '%s'\n", argv[1]);
        return 1;
    }

    // Initialize lexer
    init_lexer(input_file);

    printf("=== SIMPLIFIED LEXICAL ANALYZER ===\n");
    printf("Analyzing file: %s\n", argv[1]);
    printf("=====================================\n");

    // Tokenize the input
    do {
        token = yylex();
        if (token != TOKEN_EOF) {
            print_token(token);
        }
    } while (token != TOKEN_EOF);

    printf("=====================================\n");
    printf("Lexical analysis completed.\n");

    // Cleanup
    cleanup_lexer();
    fclose(input_file);
    
    return 0;
}
