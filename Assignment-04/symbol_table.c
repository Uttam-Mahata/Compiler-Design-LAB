#include "symbol_table.h"

symbol_table_t sym_table;
int current_scope = 0;

void init_symbol_table() {
    sym_table.count = 0;
    sym_table.current_scope_level = 0;
    printf("Symbol table initialized\n");
}

int add_symbol(char* name, data_type_t type, scope_type_t scope, int line_no, int is_function) {
    return add_symbol_with_attrs(name, type, scope, line_no, is_function, 0, 0, 0);
}

int add_symbol_with_attrs(char* name, data_type_t type, scope_type_t scope, int line_no, 
                          int is_function, int is_array, int array_size, int is_pointer) {
    if (sym_table.count >= MAX_SYMBOLS) {
        printf("ERROR: Symbol table overflow\n");
        return 0;
    }
    
    // Check if symbol already exists in current scope
    symbol_t* existing = lookup_symbol_in_scope(name, sym_table.current_scope_level);
    if (existing != NULL) {
        printf("ERROR (Line %d): Variable '%s' already declared in current scope (previously declared at line %d)\n", 
               line_no, name, existing->line_declared);
        return 0;
    }
    
    // Add new symbol
    strcpy(sym_table.symbols[sym_table.count].name, name);
    sym_table.symbols[sym_table.count].type = type;
    sym_table.symbols[sym_table.count].scope = scope;
    sym_table.symbols[sym_table.count].scope_level = sym_table.current_scope_level;
    sym_table.symbols[sym_table.count].line_declared = line_no;
    sym_table.symbols[sym_table.count].is_function = is_function;
    sym_table.symbols[sym_table.count].is_array = is_array;
    sym_table.symbols[sym_table.count].array_size = array_size;
    sym_table.symbols[sym_table.count].is_pointer = is_pointer;
    
    printf("SYMBOL TABLE: Added '%s' - Type: %s, Scope: %s (Level %d), Line: %d%s%s\n", 
           name, type_to_string(type), scope_to_string(scope), 
           sym_table.current_scope_level, line_no,
           is_array ? " [Array]" : "",
           is_pointer ? " [Pointer]" : "");
    
    sym_table.count++;
    return 1;
}

symbol_t* lookup_symbol(char* name) {
    // Search from current scope downward to global scope
    for (int level = sym_table.current_scope_level; level >= 0; level--) {
        for (int i = 0; i < sym_table.count; i++) {
            if (strcmp(sym_table.symbols[i].name, name) == 0 && 
                sym_table.symbols[i].scope_level == level) {
                return &sym_table.symbols[i];
            }
        }
    }
    return NULL;
}

symbol_t* lookup_symbol_in_scope(char* name, int scope_level) {
    for (int i = 0; i < sym_table.count; i++) {
        if (strcmp(sym_table.symbols[i].name, name) == 0 && 
            sym_table.symbols[i].scope_level == scope_level) {
            return &sym_table.symbols[i];
        }
    }
    return NULL;
}

void enter_scope() {
    sym_table.current_scope_level++;
    printf("SCOPE: Entering scope level %d\n", sym_table.current_scope_level);
}

void exit_scope() {
    printf("SCOPE: Exiting scope level %d\n", sym_table.current_scope_level);
    
    // Remove symbols from current scope
    int new_count = 0;
    for (int i = 0; i < sym_table.count; i++) {
        if (sym_table.symbols[i].scope_level < sym_table.current_scope_level) {
            if (new_count != i) {
                sym_table.symbols[new_count] = sym_table.symbols[i];
            }
            new_count++;
        } else {
            printf("SYMBOL TABLE: Removing '%s' from scope level %d\n", 
                   sym_table.symbols[i].name, sym_table.symbols[i].scope_level);
        }
    }
    sym_table.count = new_count;
    
    if (sym_table.current_scope_level > 0) {
        sym_table.current_scope_level--;
    }
}

void print_symbol_table() {
    printf("\n=== SYMBOL TABLE ===\n");
    printf("%-15s %-10s %-12s %-8s %-8s %-10s\n", 
           "Name", "Type", "Scope", "Level", "Line", "Function");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < sym_table.count; i++) {
        printf("%-15s %-10s %-12s %-8d %-8d %-10s\n",
               sym_table.symbols[i].name,
               type_to_string(sym_table.symbols[i].type),
               scope_to_string(sym_table.symbols[i].scope),
               sym_table.symbols[i].scope_level,
               sym_table.symbols[i].line_declared,
               sym_table.symbols[i].is_function ? "Yes" : "No");
    }
    printf("------------------------------------------------------------------------\n");
    printf("Total symbols: %d\n\n", sym_table.count);
}

char* type_to_string(data_type_t type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        case TYPE_INT_PTR: return "int*";
        case TYPE_FLOAT_PTR: return "float*";
        case TYPE_CHAR_PTR: return "char*";
        case TYPE_INT_ARRAY: return "int[]";
        case TYPE_FLOAT_ARRAY: return "float[]";
        case TYPE_CHAR_ARRAY: return "char[]";
        default: return "unknown";
    }
}

char* scope_to_string(scope_type_t scope) {
    switch (scope) {
        case SCOPE_GLOBAL: return "global";
        case SCOPE_FUNCTION: return "function";
        case SCOPE_BLOCK: return "block";
        default: return "unknown";
    }
}

int is_variable_declared(char* name) {
    symbol_t* sym = lookup_symbol(name);
    return (sym != NULL);
}

// Check if two types are compatible for operations
int are_types_compatible(data_type_t type1, data_type_t type2) {
    if (type1 == type2) return 1;
    
    // Get base types for comparison
    data_type_t base1 = get_base_type(type1);
    data_type_t base2 = get_base_type(type2);
    
    // Numeric promotions: int and char are compatible
    if ((base1 == TYPE_INT || base1 == TYPE_CHAR) && 
        (base2 == TYPE_INT || base2 == TYPE_CHAR)) return 1;
    
    // Float is only compatible with float
    if (base1 == TYPE_FLOAT && base2 == TYPE_FLOAT) return 1;
    
    return 0;
}

// Get base type from array/pointer type
data_type_t get_base_type(data_type_t type) {
    switch (type) {
        case TYPE_INT_PTR:
        case TYPE_INT_ARRAY:
            return TYPE_INT;
        case TYPE_FLOAT_PTR:
        case TYPE_FLOAT_ARRAY:
            return TYPE_FLOAT;
        case TYPE_CHAR_PTR:
        case TYPE_CHAR_ARRAY:
            return TYPE_CHAR;
        default:
            return type;
    }
}

// Check if type is an array type
int is_array_type(data_type_t type) {
    return (type == TYPE_INT_ARRAY || type == TYPE_FLOAT_ARRAY || type == TYPE_CHAR_ARRAY);
}

// Check if type is a pointer type
int is_pointer_type(data_type_t type) {
    return (type == TYPE_INT_PTR || type == TYPE_FLOAT_PTR || type == TYPE_CHAR_PTR);
}

// Check if type is a numeric type (for arithmetic operations)
int is_numeric_type(data_type_t type) {
    data_type_t base = get_base_type(type);
    return (base == TYPE_INT || base == TYPE_FLOAT || base == TYPE_CHAR);
}