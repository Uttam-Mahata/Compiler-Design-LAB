#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_REGS 4          // Number of general-purpose registers (AX, BX, CX, DX)
#define MAX_QUADS 1000      // Maximum three-address instructions
#define MAX_NAME_LEN 32     // Maximum length of variable/temp names
#define MAX_VARS 100        // Maximum number of variables

//Quadruple structure for three-address code
typedef struct {
    int label;
    char op[16];
    char arg1[16];
    char arg2[16];
    char result[16];
} Quadruple;

// Register descriptor 
typedef struct {
    char name[8];           // Register name (AX, BX, CX, DX)
    bool is_free;           // Is the register available
    char contains[MAX_NAME_LEN]; //  variable/temp is in this register
    bool dirty;             // Has value been modified (needs to be stored)
} RegisterDescriptor;

// Address descriptor 
typedef struct {
    char var_name[MAX_NAME_LEN]; // Variable/temp name
    bool in_memory;         // Is it in memory
    int reg_num;            // Which register (-1 if not in register)
    bool live;              // Is the variable live after this statement?
} AddressDescriptor;

// Three-address code instruction
typedef struct {
    Quadruple quad;
    bool processed;
} Instruction;

// Global variables
extern RegisterDescriptor registers[MAX_REGS];
extern AddressDescriptor address_desc[MAX_VARS];
extern Instruction instructions[MAX_QUADS];
extern int num_instructions;
extern int num_vars;
extern FILE *output_file;

// Function declarations

// Initialization and cleanup
void init_code_generator();
void close_code_generator();

// Register management
void init_registers();
int get_reg(char *var, char *arg1, char *arg2, int next_use[]);
void free_register(int reg_num);
int find_register(char *var);
bool is_register_free(int reg_num);
void mark_register_dirty(int reg_num);
void mark_register_clean(int reg_num);

// Address descriptor management
void init_address_descriptors();
int get_address_descriptor(char *var);
void update_address_descriptor(char *var, int reg_num, bool in_mem);
void set_variable_live(char *var, bool live);
bool is_variable_live(char *var);

// Code generation
void generate_code(char *op, char *arg1, char *arg2, char *result);
void gen_assignment(char *result, char *arg1);
void gen_arithmetic(char *op, char *result, char *arg1, char *arg2);
void gen_unary(char *op, char *result, char *arg1);
void gen_label(char *label);
void gen_conditional_jump(char *condition, char *label);
void gen_unconditional_jump(char *label);

// Helper functions
void emit(char *instruction);
void emit_load(int reg_num, char *var);
void emit_store(char *var, int reg_num);
void emit_arithmetic_op(char *op, int dest_reg, int src1_reg, int src2_reg);
void spill_register(int reg_num);
bool is_temporary(char *name);
bool is_constant(char *name);
void print_register_state();
void print_address_descriptors();

// Three-address code parsing
int read_three_address_code(char *filename);
void parse_quadruple(char *line, Quadruple *quad);
void process_instructions();

#endif
