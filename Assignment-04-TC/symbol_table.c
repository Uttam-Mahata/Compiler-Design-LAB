#include "symbol_table.h"

symbol_table_t sym_table;
int current_scope = 0;

// Hash function using djb2 algorithm
unsigned int hash(const char* name) {
    unsigned int hash_value = 5381;
    int c;
    while ((c = *name++)) {
        hash_value = ((hash_value << 5) + hash_value) + c; // hash * 33 + c
    }
    return hash_value % HASH_TABLE_SIZE;
}

void init_symbol_table() {
    // Initialize hash table buckets to NULL
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        sym_table.hash_table[i] = NULL;
    }
    
    sym_table.head = NULL;
    sym_table.tail = NULL;
    sym_table.count = 0;
    sym_table.current_scope_level = 0;
    printf("Symbol table initialized (Hash Table Size: %d)\n", HASH_TABLE_SIZE);
}

int add_symbol(char* name, data_type_t type, scope_type_t scope, int line_no, int is_function) {
    return add_symbol_with_attrs(name, type, scope, line_no, is_function, 0, 0, 0);
}

int add_symbol_with_attrs(char* name, data_type_t type, scope_type_t scope, int line_no, 
                          int is_function, int is_array, int array_size, int is_pointer) {
    
    // Check if symbol already exists in current scope
    symbol_node_t* existing = lookup_symbol_in_scope(name, sym_table.current_scope_level);
    if (existing != NULL) {
        printf("ERROR (Line %d): Variable '%s' already declared in current scope (previously declared at line %d)\n", 
               line_no, name, existing->line_declared);
        return 0;
    }
    
    // Create new symbol node
    symbol_node_t* new_node = (symbol_node_t*)malloc(sizeof(symbol_node_t));
    if (new_node == NULL) {
        printf("ERROR: Memory allocation failed for symbol '%s'\n", name);
        return 0;
    }
    
    // Fill in symbol information
    strncpy(new_node->name, name, MAX_ID_LENGTH - 1);
    new_node->name[MAX_ID_LENGTH - 1] = '\0';
    new_node->type = type;
    new_node->scope = scope;
    new_node->scope_level = sym_table.current_scope_level;
    new_node->line_declared = line_no;
    new_node->is_function = is_function;
    new_node->is_array = is_array;
    new_node->array_size = array_size;
    new_node->is_pointer = is_pointer;
    new_node->hash_next = NULL;
    new_node->next = NULL;
    new_node->prev = NULL;

    // Insert into hash table for fast lookup
    unsigned int hash_index = hash(name);
    new_node->hash_next = sym_table.hash_table[hash_index];
    sym_table.hash_table[hash_index] = new_node;
    
    // Also maintain a global linked list for iteration/printing
    if (sym_table.head == NULL) {
        sym_table.head = new_node;
        sym_table.tail = new_node;
    } else {
        sym_table.tail->next = new_node;
        new_node->prev = sym_table.tail;
        sym_table.tail = new_node;
    }
    
    sym_table.count++;
    
    printf("SYMBOL TABLE: Added '%s' - Type: %s, Scope: %s (Level %d), Line: %d%s%s (Hash: %u)\n", 
           name, type_to_string(type), scope_to_string(scope), 
           sym_table.current_scope_level, line_no,
           is_array ? " [Array]" : "",
           is_pointer ? " [Pointer]" : "",
           hash_index);
    
    return 1;
}

// Fast lookup using hash table - O(1) average case
symbol_node_t* lookup_symbol(char* name) {
    unsigned int hash_index = hash(name);
    symbol_node_t* current = sym_table.hash_table[hash_index];

    // Search from current scope downward to global scope
    for (int level = sym_table.current_scope_level; level >= 0; level--) {
        symbol_node_t* temp = current;
        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0 && temp->scope_level == level) {
                return temp;
            }
            temp = temp->hash_next;
        }
    }

    return NULL;
}

// Lookup in a specific scope - O(1) average case
symbol_node_t* lookup_symbol_in_scope(char* name, int scope_level) {
    unsigned int hash_index = hash(name);
    symbol_node_t* current = sym_table.hash_table[hash_index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && current->scope_level == scope_level) {
            return current;
        }
        current = current->hash_next;
    }

    return NULL;
}

void enter_scope() {
    sym_table.current_scope_level++;
    printf("SCOPE: Entering scope level %d\n", sym_table.current_scope_level);
}

void exit_scope() {
    printf("SCOPE: Exiting scope level %d\n", sym_table.current_scope_level);

    // Remove symbols from current scope - iterate carefully to avoid corruption
    symbol_node_t* current = sym_table.head;
    symbol_node_t* next_node;

    while (current != NULL) {
        next_node = current->next;  // Save next pointer before potential deletion

        if (current->scope_level == sym_table.current_scope_level) {
            printf("SYMBOL TABLE: Removing '%s' from scope level %d\n",
                   current->name, current->scope_level);

            // Remove from hash table - find it in the chain
            unsigned int hash_index = hash(current->name);
            symbol_node_t* hash_current = sym_table.hash_table[hash_index];
            symbol_node_t* hash_prev = NULL;

            while (hash_current != NULL) {
                if (hash_current == current) {
                    if (hash_prev == NULL) {
                        // First in hash chain
                        sym_table.hash_table[hash_index] = hash_current->hash_next;
                    } else {
                        // Middle or end of hash chain
                        hash_prev->hash_next = hash_current->hash_next;
                    }
                    break;
                }
                hash_prev = hash_current;
                hash_current = hash_current->hash_next;
            }

            // Remove from global linked list
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                // This is the head
                sym_table.head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                // This is the tail
                sym_table.tail = current->prev;
            }

            free(current);
            sym_table.count--;
        }

        current = next_node;
    }

    if (sym_table.current_scope_level > 0) {
        sym_table.current_scope_level--;
    }
}

void print_symbol_table() {
    printf("\n=== SYMBOL TABLE (Linked List Implementation) ===\n");
    printf("%-15s %-12s %-12s %-8s %-8s %-10s %-10s\n", 
           "Name", "Type", "Scope", "Level", "Line", "Function", "Array/Ptr");
    printf("---------------------------------------------------------------------------------\n");
    
    symbol_node_t* current = sym_table.head;
    while (current != NULL) {
        char extra_info[20] = "";
        if (current->is_array) {
            if (current->array_size > 0) {
                sprintf(extra_info, "Array[%d]", current->array_size);
            } else {
                sprintf(extra_info, "Array[]");
            }
        } else if (current->is_pointer) {
            sprintf(extra_info, "Pointer");
        } else {
            sprintf(extra_info, "-");
        }
        
        printf("%-15s %-12s %-12s %-8d %-8d %-10s %-10s\n",
               current->name,
               type_to_string(current->type),
               scope_to_string(current->scope),
               current->scope_level,
               current->line_declared,
               current->is_function ? "Yes" : "No",
               extra_info);
        
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------\n");
    printf("Total symbols: %d | Hash table size: %d\n\n", sym_table.count, HASH_TABLE_SIZE);
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
    symbol_node_t* sym = lookup_symbol(name);
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