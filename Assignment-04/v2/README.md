# Linked List Implementation of Symbol Table

## Overview

This folder contains an alternative implementation of the symbol table using **linked lists** instead of arrays. This allows for direct comparison between the two data structures.

## Files

- `symbol_table.h` - Header file with linked list structure definitions
- `symbol_table.c` - Linked list-based implementation
- `test_linkedlist.c` - Comprehensive test suite for linked list implementation
- `compare_performance.c` - Performance comparison between array and linked list
- `Makefile` - Build configuration

## Key Differences from Array Implementation

### Data Structure

**Array Version (../symbol_table.c):**
```c
typedef struct {
    symbol_t symbols[MAX_SYMBOLS];  // Static array
    int count;
    int current_scope_level;
} symbol_table_t;
```

**Linked List Version (v2/symbol_table.c):**
```c
typedef struct SymbolNode {
    symbol_t data;
    struct SymbolNode* next;
} SymbolNode;

typedef struct {
    SymbolNode* head;      // Linked list head
    int count;
    int current_scope_level;
} symbol_table_t;
```

### Operations Comparison

| Operation | Array | Linked List |
|-----------|-------|-------------|
| **Insert** | O(n) - append + duplicate check | O(n) - insert at head + duplicate check |
| **Lookup** | O(n) - linear search | O(n) - traverse list |
| **Delete (Scope Exit)** | O(n) - array compaction | O(n) - traverse and unlink |
| **Memory** | Fixed size, contiguous | Dynamic, fragmented |

## Building and Running

### Build Tests
```bash
cd v2
make
```

### Run Linked List Tests
```bash
make run
# or
./test_linkedlist
```

### Run Performance Comparison
```bash
./compare_performance
```

## Test Suite

The `test_linkedlist.c` includes 7 comprehensive tests:

1. **Basic Insert and Lookup** - Tests fundamental operations
2. **Duplicate Detection** - Validates scope-based duplicate checking
3. **Scope Management and Shadowing** - Tests nested scopes and variable shadowing
4. **Arrays and Pointers** - Tests extended type system
5. **Type Compatibility** - Validates type checking rules
6. **Performance Test** - Measures insertion and lookup speed with 1000 symbols
7. **Memory Cleanup** - Ensures no memory leaks

## Implementation Highlights

### 1. Dynamic Node Creation
```c
SymbolNode* create_node(char* name, data_type_t type, ...) {
    SymbolNode* node = (SymbolNode*)malloc(sizeof(SymbolNode));
    // ... initialize fields
    node->next = NULL;
    return node;
}
```

### 2. Insert at Head (O(1))
```c
new_node->next = sym_table.head;
sym_table.head = new_node;
sym_table.count++;
```

### 3. Scope-Aware Lookup
```c
symbol_t* lookup_symbol(char* name) {
    for (int level = current_scope_level; level >= 0; level--) {
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
```

### 4. Scope Exit with Node Deletion
```c
void exit_scope() {
    SymbolNode* current = sym_table.head;
    SymbolNode* prev = NULL;
    
    while (current != NULL) {
        if (current->data.scope_level == current_scope_level) {
            // Remove node
            SymbolNode* to_delete = current;
            if (prev == NULL) {
                sym_table.head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_delete);  // Free memory
            sym_table.count--;
        } else {
            prev = current;
            current = current->next;
        }
    }
    current_scope_level--;
}
```

### 5. Memory Cleanup
```c
void free_symbol_table() {
    SymbolNode* current = sym_table.head;
    while (current != NULL) {
        SymbolNode* to_delete = current;
        current = current->next;
        free(to_delete);
    }
    sym_table.head = NULL;
    sym_table.count = 0;
}
```

## Performance Characteristics

### Advantages of Linked List
- ✅ O(1) insertion at head (no array shifting)
- ✅ O(1) node deletion (just update pointers)
- ✅ Dynamic memory - no fixed size limit
- ✅ More efficient for frequent scope changes

### Disadvantages of Linked List
- ❌ Pointer overhead (extra memory per node)
- ❌ Poor cache locality (random memory access)
- ❌ Memory fragmentation
- ❌ More complex code (pointer management)

## When to Use Each Implementation

### Use Array (Original)
- Educational purposes (simpler to understand)
- Small to medium programs (< 1000 symbols)
- Memory predictability is important
- Cache performance matters

### Use Linked List (v2)
- Very large programs (thousands of symbols)
- Frequent scope entry/exit
- Memory limits not known in advance
- Learning data structure implementation

## Example Output

```
========== TEST 3: Scope Management and Shadowing ==========
SCOPE: Entering scope level 1
SYMBOL TABLE (LL): Added 'x' - Type: float, Scope: function (Level 1)
SYMBOL TABLE (LL): Added 'y' - Type: char, Scope: function (Level 1)
✓ Function 'x' shadows global 'x'

SCOPE: Entering scope level 2
SYMBOL TABLE (LL): Added 'x' - Type: char, Scope: block (Level 2)
✓ Block 'x' shadows function 'x'

SCOPE: Exiting scope level 2
SYMBOL TABLE (LL): Removing 'x' from scope level 2
SYMBOL TABLE (LL): Removing 'z' from scope level 2
✓ After exiting block, found function 'x'
✓ Block variable 'z' removed
✓ TEST 3 PASSED
```

## Conclusion

Both implementations are **correct and functional**. The linked list version demonstrates:
- Dynamic memory management
- Pointer manipulation
- Alternative data structure design

However, for most compiler design educational purposes, the **array implementation is recommended** due to its simplicity and adequate performance for typical workloads.
