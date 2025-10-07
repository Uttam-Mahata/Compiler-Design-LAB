#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LENGTH 32
#define MAX_SYMBOLS 1000

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_UNKNOWN
} data_type_t;

typedef enum {
    SCOPE_GLOBAL,
    SCOPE_FUNCTION,
    SCOPE_BLOCK
} scope_type_t;

typedef struct {
    char name[MAX_ID_LENGTH];
    data_type_t type;
    scope_type_t scope;
    int scope_level;
    int line_declared;
    int is_function;
} symbol_t;

typedef struct {
    symbol_t symbols[MAX_SYMBOLS];
    int count;
    int current_scope_level;
} symbol_table_t;

extern symbol_table_t sym_table;
extern int current_scope;

void init_symbol_table();
int add_symbol(char* name, data_type_t type, scope_type_t scope, int line_no, int is_function);
symbol_t* lookup_symbol(char* name);
symbol_t* lookup_symbol_in_scope(char* name, int scope_level);
void enter_scope();
void exit_scope();
void print_symbol_table();
char* type_to_string(data_type_t type);
char* scope_to_string(scope_type_t scope);
int is_variable_declared(char* name);

#endif