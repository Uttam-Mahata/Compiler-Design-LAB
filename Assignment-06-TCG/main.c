#include "codegen.h"

/**
 * Parse a line from three-address code file
 * Format: Label  Op  Arg1  Arg2  Result
 * Handles variable-width spacing between columns
 */
void parse_quadruple(char *line, Quadruple *quad) {
    char *token;
    char *tokens[5] = {NULL};
    int token_count = 0;
    char line_copy[256];
    
    // Initialize quad
    quad->label = -1;
    quad->op[0] = '\0';
    quad->arg1[0] = '\0';
    quad->arg2[0] = '\0';
    quad->result[0] = '\0';
    
    // Skip empty lines and separator lines
    if (line[0] == '\0' || line[0] == '-' || line[0] == '=') {
        return;
    }
    
    // Skip header line
    if (strstr(line, "Label") && strstr(line, "Op")) {
        return;
    }
    
    // Skip summary line
    if (strstr(line, "Total quadruples")) {
        return;
    }
    
    // Make a copy to tokenize
    strncpy(line_copy, line, sizeof(line_copy));
    line_copy[sizeof(line_copy) - 1] = '\0';
    
    // Tokenize by whitespace
    token = strtok(line_copy, " \t\n\r");
    while (token != NULL && token_count < 5) {
        tokens[token_count++] = token;
        token = strtok(NULL, " \t\n\r");
    }
    
    // Need at least label and op
    if (token_count < 2) {
        return;
    }
    
    // Parse label
    quad->label = atoi(tokens[0]);
    strcpy(quad->op, tokens[1]);
    
    // Handle different instruction formats based on operation
    if (strcmp(quad->op, "=") == 0) {
        // Assignment: label = arg1 result
        if (token_count >= 3) strcpy(quad->arg1, tokens[2]);
        if (token_count >= 4) strcpy(quad->result, tokens[3]);
    }



else if (strcmp(quad->op, "uminus") == 0) {
        // Unary minus: label uminus arg1 result
        if (token_count >= 3) strcpy(quad->arg1, tokens[2]);
        if (token_count >= 4) strcpy(quad->result, tokens[3]);
    }



 else if (strcmp(quad->op, "label_begin") == 0 || strcmp(quad->op, "label_end") == 0) {
        // Label: label label_begin/label_end result_label
        if (token_count >= 3) strcpy(quad->result, tokens[2]);
    }



else if (strcmp(quad->op, "ifFalse") == 0) {
        // Conditional: label ifFalse condition target_label
        if (token_count >= 3) strcpy(quad->arg1, tokens[2]);
        if (token_count >= 4) strcpy(quad->result, tokens[3]);
    }



    else if (strcmp(quad->op, "goto") == 0) {
        // Goto: label goto target_label
        if (token_count >= 3) strcpy(quad->result, tokens[2]);
    }



    
    else {
        // Arithmetic: label op arg1 arg2 result
        if (token_count >= 3) strcpy(quad->arg1, tokens[2]);
        if (token_count >= 4) strcpy(quad->arg2, tokens[3]);
        if (token_count >= 5) strcpy(quad->result, tokens[4]);
    }
}

/**
 * Read three-address code from file
 */
int read_three_address_code(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }
    
    char line[256];
    num_instructions = 0;
    
    printf("\n=== Reading Three-Address Code ===\n");
    
    while (fgets(line, sizeof(line), fp) && num_instructions < MAX_QUADS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        Quadruple quad;
        parse_quadruple(line, &quad);
        
        // Skip invalid lines
        if (quad.label == -1) continue;
        
        // Store instruction
        instructions[num_instructions].quad = quad;
        instructions[num_instructions].processed = false;
        
        printf("%d: %s %s, %s, %s\n", 
               quad.label, quad.op, quad.arg1, quad.arg2, quad.result);
        
        num_instructions++;
    }
    
    fclose(fp);
    printf("Total instructions read: %d\n", num_instructions);
    return num_instructions;
}

/**
 * Process all instructions and generate assembly code
 */
void process_instructions() {
    printf("\n=== Generating Assembly Code ===\n\n");
    fprintf(output_file, "\n; Three-Address Code to Assembly Translation\n");
    fprintf(output_file, "; Total Instructions: %d\n\n", num_instructions);
    
    for (int i = 0; i < num_instructions; i++) {
        Quadruple *quad = &instructions[i].quad;
        
        printf("\nProcessing instruction %d: %s %s, %s, %s\n",
               quad->label, quad->op, quad->arg1, quad->arg2, quad->result);
        
        // Generate code for this instruction
        generate_code(quad->op, quad->arg1, quad->arg2, quad->result);
        
        instructions[i].processed = true;
    }
    
    // Store all dirty registers at the end
    printf("\n=== Final Register Cleanup ===\n");
    fprintf(output_file, "\n; Store all modified values back to memory\n");
    for (int i = 0; i < MAX_REGS; i++) {
        if (!registers[i].is_free && registers[i].dirty) {
            spill_register(i);
        }
    }
}

/**
 * Main function
 */
int main(int argc, char *argv[]) {
    char input_file[256] = "three_address_code.txt";
    
    printf("========================================\n");
    printf("  TARGET CODE GENERATOR\n");
    printf("  Assignment 06 - Compiler Design Lab\n");
    printf("========================================\n");
    
    // Check for command line argument
    if (argc > 1) {
        strcpy(input_file, argv[1]);
    }
    
    printf("\nInput file: %s\n", input_file);
    printf("Output file: assembly_code.asm\n");
    
    // Initialize code generator
    init_code_generator();
    
    // Read three-address code
    int count = read_three_address_code(input_file);
    if (count < 0) {
        fprintf(stderr, "Error reading input file\n");
        return 1;
    }
    
    if (count == 0) {
        fprintf(stderr, "No instructions found in input file\n");
        close_code_generator();
        return 1;
    }
    
    // Process instructions and generate code
    process_instructions();
    
    // Print final state
    print_register_state();
    print_address_descriptors();
    
    // Cleanup
    close_code_generator();
    
    printf("\n========================================\n");
    printf("  Code Generation Complete!\n");
    printf("========================================\n");
    
    return 0;
}
