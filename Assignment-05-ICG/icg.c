/* Write the YACC program to implement the Syntax-Directed definition for translating
assignment statements, if statements, if-else statements, while statements to three-
address code. The assignment statements need to be type checked. Use quadruple-record
structure for the representation of three address code. The three address statements have to be
sent to an output file. Quadruple is a record structure with four fields for the three-address
statements.
Quadruple is a record structure with four fields for the three-address statements.
As for example: a = b * - c

Label Op Arg1 Arg2 Result
00 uminus c T1
01 * b T1 T2
02 = T2 a

*/

#include "icg.h"

FILE *output_file = NULL;
int quad_count = 0;
int temp_count = 0;
int label_count = 0;

quadruple_t quad_array[MAX_QUADS];

void init_icg() {
    output_file = fopen("three_address_code.txt", "w");
    if (output_file == NULL) {
        printf("ERROR: Cannot open output file for three-address code\n");
        exit(1);
    }
    quad_count = 0;
    temp_count = 0;
    label_count = 0;
    fprintf(output_file, "=== THREE ADDRESS CODE (Quadruples) ===\n\n");
    fprintf(output_file, "%-6s %-12s %-12s %-12s %-12s\n", "Label", "Op", "Arg1", "Arg2", "Result");
    fprintf(output_file, "------------------------------------------------------------\n");
    printf("\n=== INTERMEDIATE CODE GENERATION INITIALIZED ===\n");
}

void close_icg() {
    if (output_file != NULL) {
        fprintf(output_file, "\n------------------------------------------------------------\n");
        fprintf(output_file, "Total quadruples generated: %d\n", quad_count);
        fclose(output_file);
        printf("\n=== THREE ADDRESS CODE WRITTEN TO 'three_address_code.txt' ===\n");
        printf("Total quadruples: %d\n", quad_count);
    }
}

char* new_temp() {
    char* temp = (char*)malloc(10 * sizeof(char));
    sprintf(temp, "T%d", temp_count++);
    return temp;
}

char* new_label() {
    char* label = (char*)malloc(10 * sizeof(char));
    sprintf(label, "L%d", label_count++);
    return label;
}

void gen(char *op, char *arg1, char *arg2, char *result) {
    if (quad_count >= MAX_QUADS) {
        printf("ERROR: Maximum quadruple limit reached\n");
        return;
    }
    
    quadruple_t *quad = &quad_array[quad_count];
    quad->label = quad_count;
    
    // Copy strings safely
    strncpy(quad->op, op ? op : "", 15);
    quad->op[15] = '\0';
    
    strncpy(quad->arg1, arg1 ? arg1 : "", 15);
    quad->arg1[15] = '\0';
    
    strncpy(quad->arg2, arg2 ? arg2 : "", 15);
    quad->arg2[15] = '\0';
    
    strncpy(quad->result, result ? result : "", 15);
    quad->result[15] = '\0';
    
    // Write to output file
    fprintf(output_file, "%-6d %-12s %-12s %-12s %-12s\n", 
            quad->label, quad->op, quad->arg1, quad->arg2, quad->result);
    
    // Also print to console for debugging
    printf("ICG: %02d: %s %s %s %s\n", 
           quad->label, quad->op, quad->arg1, quad->arg2, quad->result);
    
    quad_count++;
}

void backpatch(int *list, int size, int target_label) {
    char target[10];
    sprintf(target, "L%d", target_label);
    
    for (int i = 0; i < size; i++) {
        int quad_index = list[i];
        if (quad_index < quad_count) {
            strncpy(quad_array[quad_index].result, target, 15);
            quad_array[quad_index].result[15] = '\0';
        }
    }
}

int next_quad() {
    return quad_count;
}

void emit_label(char *label) {
    gen("label", "", "", label);
}

void print_quad_array() {
    printf("\n=== GENERATED QUADRUPLES ===\n");
    printf("%-6s %-12s %-12s %-12s %-12s\n", "Label", "Op", "Arg1", "Arg2", "Result");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < quad_count; i++) {
        printf("%-6d %-12s %-12s %-12s %-12s\n",
               quad_array[i].label,
               quad_array[i].op,
               quad_array[i].arg1,
               quad_array[i].arg2,
               quad_array[i].result);
    }
    printf("------------------------------------------------------------\n");
}
