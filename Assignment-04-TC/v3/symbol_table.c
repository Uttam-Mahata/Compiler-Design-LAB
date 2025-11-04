#include "symbol_table.h"

symbol_table_t sym_table;
int current_scope = 0;

void init_symbol_table() {
    sym_table.head = NULL;
    sym_table.count = 0;
    sym_table.current_scope_level = 0;
    printf("Symbol table (Linked List) initialized\n");
}

// Helper function to create a new node
SymbolNode* create_node(char* name, data_type_t type, scope_type_t scope, int line_no, 
                        int is_function, int is_array, int array_size, int is_pointer) {
    SymbolNode* node = (SymbolNode*)malloc(sizeof(SymbolNode));
    if (node == NULL) {
        printf("ERROR: Memory allocation failed\n");
        return NULL;
    }
    
    strcpy(node->data.name, name);
    node->data.type = type;
    node->data.scope = scope;
    node->data.scope_level = sym_table.current_scope_level;
    node->data.line_declared = line_no;
    node->data.is_function = is_function;
    node->data.is_array = is_array;
    node->data.array_size = array_size;
    node->data.is_pointer = is_pointer;
    node->next = NULL;
    
    return node;
}

int add_symbol(char* name, data_type_t type, scope_type_t scope, int line_no, int is_function) {
    return add_symbol_with_attrs(name, type, scope, line_no, is_function, 0, 0, 0);
}

int add_symbol_with_attrs(char* name, data_type_t type, scope_type_t scope, int line_no, 
                          int is_function, int is_array, int array_size, int is_pointer) {
    
    /* Check if symbol already exists in current scope */
    
    symbol_t* existing = lookup_symbol_in_scope(name, sym_table.current_scope_level);
    if (existing != NULL) {
        printf("ERROR (Line %d): Variable '%s' already declared in current scope (previously declared at line %d)\n", 
               line_no, name, existing->line_declared);
        return 0;
    }
    
    // Create new node
    SymbolNode* new_node = create_node(name, type, scope, line_no, is_function, is_array, array_size, is_pointer);
    if (new_node == NULL) {
        return 0;
    }
    
    // Insert at the beginning of the linked list (O(1) insertion)
    new_node->next = sym_table.head;
    sym_table.head = new_node;
    sym_table.count++;
    
    printf("SYMBOL TABLE (LL): Added '%s' - Type: %s, Scope: %s (Level %d), Line: %d%s%s\n", 
           name, type_to_string(type), scope_to_string(scope), 
           sym_table.current_scope_level, line_no,
           is_array ? " [Array]" : "",
           is_pointer ? " [Pointer]" : "");
    
    return 1;
}

symbol_t* lookup_symbol(char* name) {
    // Search from current scope downward to global scope
    for (int level = sym_table.current_scope_level; level >= 0; level--) {
        SymbolNode* current = sym_table.head;
        while (current != NULL) {
            if (strcmp(current->data.name, name) == 0 && 
                current->data.scope_level == level) {
                return &(current->data);
            }
            current = current->next;
        }
    }
    return NULL;
}

symbol_t* lookup_symbol_in_scope(char* name, int scope_level) {
    SymbolNode* current = sym_table.head;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0 && 
            current->data.scope_level == scope_level) {
            return &(current->data);
        }
        current = current->next;
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
    SymbolNode* current = sym_table.head;
    SymbolNode* prev = NULL;
    
    while (current != NULL) {
        if (current->data.scope_level == sym_table.current_scope_level) {
            // Remove this node
            printf("SYMBOL TABLE (LL): Removing '%s' from scope level %d\n", 
                   current->data.name, current->data.scope_level);
            
            SymbolNode* to_delete = current;
            
            if (prev == NULL) {
                // Removing head node
                sym_table.head = current->next;
                current = sym_table.head;
            } else {
                // Removing middle or end node
                prev->next = current->next;
                current = current->next;
            }
            
            free(to_delete);
            sym_table.count--;
        } else {
            // Keep this node
            prev = current;
            current = current->next;
        }
    }
    
    if (sym_table.current_scope_level > 0) {
        sym_table.current_scope_level--;
    }
}

void print_symbol_table() {
    printf("\n=== SYMBOL TABLE (Linked List) ===\n");
    printf("%-15s %-10s %-12s %-8s %-8s %-10s\n", 
           "Name", "Type", "Scope", "Level", "Line", "Function");
    printf("------------------------------------------------------------------------\n");
    
    SymbolNode* current = sym_table.head;
    while (current != NULL) {
        printf("%-15s %-10s %-12s %-8d %-8d %-10s\n",
               current->data.name,
               type_to_string(current->data.type),
               scope_to_string(current->data.scope),
               current->data.scope_level,
               current->data.line_declared,
               current->data.is_function ? "Yes" : "No");
        current = current->next;
    }
    printf("------------------------------------------------------------------------\n");
    printf("Total symbols: %d\n\n", sym_table.count);
}

void free_symbol_table() {
    SymbolNode* current = sym_table.head;
    while (current != NULL) {
        SymbolNode* to_delete = current;
        current = current->next;
        free(to_delete);
    }
    sym_table.head = NULL;
    sym_table.count = 0;
    printf("Symbol table freed\n");
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
