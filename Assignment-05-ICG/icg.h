#ifndef ICG_H
#define ICG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUADS 1000

// Quadruple structure for three-address code
typedef struct {
    int label;
    char op[16];
    char arg1[16];
    char arg2[16];
    char result[16];
} quadruple_t;

// External variables
extern FILE *output_file;
extern int quad_count;
extern int temp_count;
extern int label_count;
extern quadruple_t quad_array[MAX_QUADS];

// Function declarations
void init_icg();
void close_icg();
char* new_temp();
char* new_label();
void gen(char *op, char *arg1, char *arg2, char *result);
void backpatch(int *list, int size, int target_label);
int next_quad();
void emit_label(char *label);
void print_quad_array();

#endif
