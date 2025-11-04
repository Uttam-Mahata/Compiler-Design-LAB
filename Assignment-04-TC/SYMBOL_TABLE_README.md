# Symbol Table Implementation with Linked List & Hash Table

## Data Structure Design

### Overview
The symbol table uses a **hybrid approach** combining:
1. **Hash Table** for O(1) average lookup time
2. **Linked List** for ordered iteration and scope management

### Structure

```
Hash Table (size 211) - Prime number for better distribution
    ├── Bucket[0] → symbol_node → symbol_node → NULL
    ├── Bucket[1] → symbol_node → NULL
    ├── ...
    └── Bucket[210] → NULL

Global Linked List (for iteration)
    head → symbol_node ↔ symbol_node ↔ ... ↔ tail
```

## Key Features

### 1. Fast Lookup - O(1) Average Case
- Uses djb2 hash function
- Hash table size: 211 (prime number)
- Collision resolution: Chaining with linked list

### 2. Efficient Insertion - O(1)
- Add to hash bucket (constant time)
- Append to global linked list (constant time with tail pointer)
- Total: O(1) insertion time

### 3. Scope Management
- Hierarchical scope levels (0=global, 1=function, 2+=block)
- Symbol lookup searches from current scope down to global
- Scope exit removes all symbols at current level

### 4. Operations Supported

#### Insert
```c
add_symbol(name, type, scope, line_no, is_function)
add_symbol_with_attrs(name, type, scope, line_no, is_function, is_array, array_size, is_pointer)
```

#### Lookup
```c
lookup_symbol(name)                    // Search from current scope to global
lookup_symbol_in_scope(name, level)    // Search in specific scope only
```

#### Scope Management
```c
enter_scope()    // Increment scope level
exit_scope()     // Remove all symbols in current scope and decrement
```

## Implementation Details

### Hash Function (djb2 Algorithm)
```c
hash = 5381
for each character c:
    hash = (hash * 33) + c
return hash % TABLE_SIZE
```

### Symbol Node Structure
```c
typedef struct symbol_node {
    char name[MAX_ID_LENGTH];
    data_type_t type;
    scope_type_t scope;
    int scope_level;
    int line_declared;
    int is_function;
    int is_array;
    int array_size;
    int is_pointer;
    struct symbol_node* next;  // For hash bucket chain
    struct symbol_node* prev;  // For easy deletion
} symbol_node_t;
```

### Complexity Analysis

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Insert | O(1) average | O(n) |
| Lookup | O(1) average | - |
| Delete (scope exit) | O(k) where k = symbols in scope | - |
| Print All | O(n) | - |

## Advantages

1. **Fast Lookup**: O(1) average vs O(n) for linear search
2. **Efficient Memory**: Only allocated space for actual symbols
3. **Easy Iteration**: Global linked list maintains insertion order
4. **Scope Management**: Clean removal of scope-specific symbols
5. **Collision Handling**: Chaining handles hash collisions gracefully

## Disadvantages

1. **Memory Overhead**: Extra pointers (next, prev) per node
2. **Cache Locality**: Scattered memory access vs array-based approach
3. **Fixed Table Size**: Hash table size predetermined (211 buckets)

## Usage Example

```c
// Initialize
init_symbol_table();

// Add symbols
add_symbol("x", TYPE_INT, SCOPE_GLOBAL, 1, 0);
add_symbol("main", TYPE_INT, SCOPE_GLOBAL, 3, 1);

// Enter function scope
enter_scope();
add_symbol("local_var", TYPE_FLOAT, SCOPE_FUNCTION, 4, 0);

// Lookup
symbol_node_t* sym = lookup_symbol("x");
if (sym) {
    printf("Found: %s, Type: %s\n", sym->name, type_to_string(sym->type));
}

// Exit scope (removes local_var)
exit_scope();

// Print table
print_symbol_table();
```

## Hash Distribution Statistics

With 211 buckets and good hash function:
- Expected chain length: n/211 where n = total symbols
- For 50 symbols: ~0.24 symbols per bucket average
- For 200 symbols: ~0.95 symbols per bucket average

## Conclusion

This implementation follows best practices for symbol table management in compilers:
- ✅ Fast lookup (O(1) average)
- ✅ Easy to implement
- ✅ Handles scopes properly
- ✅ Memory efficient (dynamic allocation)
- ✅ Ordered iteration capability
