# Symbol Table Implementation Comparison

## Overview

Assignment-04 now includes **two implementations** of the symbol table:
1. **Array-based** (original) - in root Assignment-04 directory
2. **Linked List-based** (new) - in v2 subdirectory

## Implementation Comparison

### Data Structure

| Aspect | Array Implementation | Linked List Implementation |
|--------|---------------------|---------------------------|
| **Storage** | Fixed-size array (1000 symbols) | Dynamic linked list |
| **Memory** | Contiguous, cache-friendly | Fragmented, pointer overhead |
| **Growth** | Fixed limit | Unlimited (heap permitting) |

### Operations Complexity

| Operation | Array | Linked List |
|-----------|-------|-------------|
| **Insert** | O(n) - duplicate check + append | O(n) - duplicate check + O(1) prepend |
| **Lookup** | O(n × levels) - linear search | O(n × levels) - list traversal |
| **Scope Exit** | O(n) - array compaction | O(n) - traverse and unlink |
| **Memory Free** | N/A (static array) | O(n) - free each node |

## Test Results

### Linked List Performance (1000 symbols):
```
Insert:      6.832 ms  (0.0068 ms per symbol)
Lookup:      6.985 ms  (0.0070 ms per symbol)
Scope Exit:  0.039 ms  (100 symbols)
```

### Key Findings

1. **Both are O(n) for lookups** - No significant algorithmic advantage
2. **Linked list has O(1) insert** at head vs array append
3. **Scope exit slightly faster** with linked list (pointer updates vs array compaction)
4. **Memory overhead** - Linked list uses ~16 extra bytes per symbol (2 pointers)

## Code Structure Comparison

### Array Version (`symbol_table.c`)

```c
typedef struct {
    symbol_t symbols[MAX_SYMBOLS];  // Static array
    int count;
    int current_scope_level;
} symbol_table_t;

// Insertion
symbols[count] = new_symbol;
count++;

// Scope exit (compaction)
for (int i = 0; i < count; i++) {
    if (symbols[i].scope_level < current_scope_level) {
        symbols[new_count++] = symbols[i];  // Shift elements
    }
}
```

### Linked List Version (`v2/symbol_table.c`)

```c
typedef struct SymbolNode {
    symbol_t data;
    struct SymbolNode* next;
} SymbolNode;

typedef struct {
    SymbolNode* head;
    int count;
    int current_scope_level;
} symbol_table_t;

// Insertion (at head)
new_node->next = head;
head = new_node;

// Scope exit (unlink nodes)
while (current) {
    if (current->data.scope_level == current_scope_level) {
        prev->next = current->next;  // Unlink
        free(current);               // Free memory
    }
}
```

## Advantages & Disadvantages

### Array Implementation ✅

**Advantages:**
- ✅ Simple, straightforward code (~100 lines)
- ✅ No memory leaks possible
- ✅ Better cache locality (sequential access)
- ✅ Lower memory overhead
- ✅ Easier to debug and understand

**Disadvantages:**
- ❌ Fixed size limit (1000 symbols)
- ❌ O(n) array compaction on scope exit
- ❌ Wastes memory if few symbols used

### Linked List Implementation 💡

**Advantages:**
- ✅ Dynamic size - no hard limit
- ✅ O(1) insertion at head
- ✅ Only allocates memory for symbols used
- ✅ O(1) node deletion (just unlink)

**Disadvantages:**
- ❌ More complex code (~150 lines)
- ❌ Pointer overhead (~16 bytes/symbol)
- ❌ Cache misses (random memory access)
- ❌ Potential memory leaks if not freed properly
- ❌ Memory fragmentation over time

## When to Use Each?

### Use Array Implementation (Original)
- ✅ **Educational purposes** - simpler to understand
- ✅ **Small to medium programs** (< 1000 symbols)
- ✅ **Predictable memory usage** required
- ✅ **Performance matters** (cache locality)
- ✅ **Compiler design lab assignments**

### Use Linked List Implementation (v2)
- ✅ **Very large programs** (thousands of symbols)
- ✅ **Unknown symbol count** at compile time
- ✅ **Learning data structures** (pointer manipulation)
- ✅ **Frequent scope changes** (many nested blocks)
- ✅ **Memory constraints** (only pay for what you use)

## Educational Value

### What Array Implementation Teaches:
1. Basic symbol table concepts
2. Scope management with levels
3. Linear search and lookup
4. Type checking integration
5. Simple memory management

### What Linked List Implementation Teaches:
1. Dynamic memory allocation (`malloc`/`free`)
2. Pointer manipulation
3. Linked list traversal
4. Memory leak prevention
5. Alternative data structure design

## Conclusion

**For Assignment-04 (Type Checking):**
- **Array implementation is RECOMMENDED** ✅
- Simpler, adequate performance, fewer bugs
- Focus stays on type checking, not data structures

**For Learning Purposes:**
- **Both implementations are valuable** 📚
- Array teaches fundamentals
- Linked list teaches advanced concepts
- Comparison teaches trade-off analysis

## Running the Tests

### Test Array Implementation:
```bash
cd Assignment-04
make clean && make
./symbol_parser < test_simple.c
```

### Test Linked List Implementation:
```bash
cd Assignment-04/v2
make clean && make
./test_linkedlist          # Comprehensive tests
./compare_performance       # Performance analysis
```

## Files

### Array Implementation:
- `symbol_table.h` - Header with array structure
- `symbol_table.c` - Array-based implementation
- `parse.y` - Parser using the symbol table

### Linked List Implementation:
- `v2/symbol_table.h` - Header with linked list structure
- `v2/symbol_table.c` - Linked list implementation
- `v2/test_linkedlist.c` - Comprehensive test suite (7 tests)
- `v2/compare_performance.c` - Performance benchmarks
- `v2/README.md` - Detailed documentation

## Performance Summary

Both implementations have:
- ✅ **Same time complexity** for core operations
- ✅ **Correct scope resolution** (shadowing support)
- ✅ **Full type checking** integration
- ✅ **Proper memory management**

The choice between them is about:
- **Simplicity** vs **Flexibility**
- **Fixed size** vs **Dynamic growth**
- **Cache efficiency** vs **Memory efficiency**
- **Learning goals** vs **Production needs**

---

**Recommendation:** Stick with the **array implementation** for the assignment, but study the **linked list version** to understand alternative approaches and trade-offs in compiler design! 🎓
