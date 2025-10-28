# Visual Guide: Array vs Linked List Symbol Table

## 📊 Data Structure Visualization

### Array Implementation

```
Symbol Table (Array-based):
┌─────────────────────────────────────────┐
│ sym_table                               │
├─────────────────────────────────────────┤
│ count: 5                                │
│ current_scope_level: 1                  │
│ symbols[1000]:                          │
│   ┌─────────────────────────────────┐   │
│   │ [0] name: "main"                │   │
│   │     type: TYPE_INT              │   │
│   │     scope_level: 0              │   │
│   ├─────────────────────────────────┤   │
│   │ [1] name: "x"                   │   │
│   │     type: TYPE_INT              │   │
│   │     scope_level: 1              │   │
│   ├─────────────────────────────────┤   │
│   │ [2] name: "y"                   │   │
│   │     type: TYPE_FLOAT            │   │
│   │     scope_level: 1              │   │
│   ├─────────────────────────────────┤   │
│   │ [3] name: "z"                   │   │
│   │     type: TYPE_CHAR             │   │
│   │     scope_level: 1              │   │
│   ├─────────────────────────────────┤   │
│   │ [4] name: "temp"                │   │
│   │     type: TYPE_INT              │   │
│   │     scope_level: 1              │   │
│   ├─────────────────────────────────┤   │
│   │ [5] EMPTY                       │   │
│   │ ...                             │   │
│   │ [999] EMPTY                     │   │
│   └─────────────────────────────────┘   │
└─────────────────────────────────────────┘

Memory Layout: CONTIGUOUS
[symbol0][symbol1][symbol2][symbol3][symbol4][EMPTY...EMPTY]
```

### Linked List Implementation

```
Symbol Table (Linked List):
┌──────────────────────────────────────────┐
│ sym_table                                │
├──────────────────────────────────────────┤
│ count: 5                                 │
│ current_scope_level: 1                   │
│ head: ──┐                                │
└─────────┼────────────────────────────────┘
          │
          ▼
    ┌──────────────────┐
    │ SymbolNode       │
    ├──────────────────┤
    │ name: "temp"     │◄─── Most recently added (head)
    │ type: TYPE_INT   │
    │ scope_level: 1   │
    │ next: ──┐        │
    └─────────┼────────┘
              │
              ▼
         ┌──────────────────┐
         │ SymbolNode       │
         ├──────────────────┤
         │ name: "z"        │
         │ type: TYPE_CHAR  │
         │ scope_level: 1   │
         │ next: ──┐        │
         └─────────┼────────┘
                   │
                   ▼
              ┌──────────────────┐
              │ SymbolNode       │
              ├──────────────────┤
              │ name: "y"        │
              │ type: TYPE_FLOAT │
              │ scope_level: 1   │
              │ next: ──┐        │
              └─────────┼────────┘
                        │
                        ▼
                   ┌──────────────────┐
                   │ SymbolNode       │
                   ├──────────────────┤
                   │ name: "x"        │
                   │ type: TYPE_INT   │
                   │ scope_level: 1   │
                   │ next: ──┐        │
                   └─────────┼────────┘
                             │
                             ▼
                        ┌──────────────────┐
                        │ SymbolNode       │
                        ├──────────────────┤
                        │ name: "main"     │◄─── First added
                        │ type: TYPE_INT   │
                        │ scope_level: 0   │
                        │ next: NULL       │
                        └──────────────────┘

Memory Layout: FRAGMENTED
Node1 ──→ Node2 ──→ Node3 ──→ Node4 ──→ Node5 ──→ NULL
(Random heap locations, not contiguous)
```

## 🔄 Operation Visualizations

### INSERT Operation

#### Array Insert (Append)
```
Before: count = 3
┌───┬───┬───┬─────┬─────┐
│ A │ B │ C │     │     │
└───┴───┴───┴─────┴─────┘
            ▲
            count

Step 1: Check duplicates (scan [0..2])
Step 2: symbols[3] = newSymbol
Step 3: count++

After: count = 4
┌───┬───┬───┬───┬─────┐
│ A │ B │ C │ D │     │
└───┴───┴───┴───┴─────┘
                ▲
                count

Time: O(n) for duplicate check + O(1) append = O(n)
```

#### Linked List Insert (Prepend)
```
Before:
head ──→ [C] ──→ [B] ──→ [A] ──→ NULL

Step 1: Check duplicates (traverse entire list)
Step 2: new_node = malloc(...)
Step 3: new_node->next = head
Step 4: head = new_node

After:
head ──→ [D] ──→ [C] ──→ [B] ──→ [A] ──→ NULL
         ▲
         New!

Time: O(n) for duplicate check + O(1) prepend = O(n)
```

### LOOKUP Operation

#### Array Lookup (Scope Resolution)
```
Looking for "x" at scope_level = 2

level=2: Scan [0..count-1] for name="x" AND level=2
┌───────┬───────┬───────┬───────┐
│ main  │ var_a │  x    │  x    │
│ lvl=0 │ lvl=1 │ lvl=1 │ lvl=2 │ ← FOUND!
└───────┴───────┴───────┴───────┘

If not found in level=2, search level=1
If not found in level=1, search level=0
Return NULL if not found anywhere

Time: O(n × levels)
```

#### Linked List Lookup (Scope Resolution)
```
Looking for "x" at scope_level = 2

level=2: Traverse list, find first node with name="x" AND level=2

head ──→ [x,2] ──→ [y,2] ──→ [x,1] ──→ [a,1] ──→ [main,0]
         ▲
         FOUND!

If not found in level=2, traverse again for level=1
If not found, traverse for level=0

Time: O(n × levels)
```

### SCOPE EXIT Operation

#### Array Scope Exit (Compaction)
```
Exiting scope level 2:
Before: count = 6
┌────────┬──────┬──────┬──────┬──────┬──────┐
│  main  │  a   │  b   │  x   │  y   │  z   │
│ lvl=0  │ lvl=1│ lvl=1│ lvl=2│ lvl=2│ lvl=2│
└────────┴──────┴──────┴──────┴──────┴──────┘

Step 1: Iterate through array
Step 2: Keep symbols with level < 2
Step 3: Shift remaining symbols left

After: count = 3
┌────────┬──────┬──────┬─────┬─────┬─────┐
│  main  │  a   │  b   │     │     │     │
│ lvl=0  │ lvl=1│ lvl=1│     │     │     │
└────────┴──────┴──────┴─────┴─────┴─────┘
                        ▲
                        count

Time: O(n) - single pass with compaction
```

#### Linked List Scope Exit (Unlink)
```
Exiting scope level 2:

Before:
head ──→ [z,2] ──→ [y,2] ──→ [x,2] ──→ [b,1] ──→ [a,1] ──→ [main,0]
         Remove    Remove    Remove    Keep      Keep      Keep

Step 1: Traverse list
Step 2: If node.level == 2, unlink and free
Step 3: Update pointers

After:
head ──→ [b,1] ──→ [a,1] ──→ [main,0]

Freed: [z], [y], [x]

Time: O(n) - single traversal
```

## 💾 Memory Comparison

### Array Memory Usage
```
Size per symbol: sizeof(symbol_t) = ~80 bytes
Total allocation: 1000 × 80 = 80,000 bytes (always)

For 10 symbols:
Used:   10 × 80  =    800 bytes
Wasted: 990 × 80 = 79,200 bytes
Efficiency: 1%

For 500 symbols:
Used:   500 × 80  = 40,000 bytes
Wasted: 500 × 80  = 40,000 bytes
Efficiency: 50%

For 1000 symbols:
Used:   1000 × 80 = 80,000 bytes
Wasted:             0 bytes
Efficiency: 100%
```

### Linked List Memory Usage
```
Size per node:
  - symbol_t data: ~80 bytes
  - next pointer:   8 bytes
  - malloc overhead: ~16 bytes
  Total per node: ~104 bytes

For 10 symbols:
Used: 10 × 104 = 1,040 bytes
Overhead: 24 bytes/symbol (30%)

For 500 symbols:
Used: 500 × 104 = 52,000 bytes
Overhead: 24 bytes/symbol (30%)

For 1000 symbols:
Used: 1000 × 104 = 104,000 bytes
Overhead: 24 bytes/symbol (30%)
```

## 🏃 Performance Characteristics

### Cache Performance

#### Array (Good Cache Locality)
```
CPU Cache Line (64 bytes):
┌──────────────────────────────────────────┐
│ [symbol_0][symbol_1][part of symbol_2]   │ ← Loaded together
└──────────────────────────────────────────┘

Sequential access = Cache hits ✅
Iterating 1000 symbols: ~16 cache misses
```

#### Linked List (Poor Cache Locality)
```
CPU Cache:
Node 1: [data] at address 0x1234  ← Cache miss
Node 2: [data] at address 0x7890  ← Cache miss
Node 3: [data] at address 0x3456  ← Cache miss

Random memory locations = Cache misses ❌
Iterating 1000 symbols: ~1000 cache misses
```

## 📈 Scalability Analysis

```
Number of Symbols vs Performance:

Lookup Time:
    Array: ████████████████████████  (linear)
    List:  ████████████████████████  (linear, slightly slower)

Insert Time:
    Array: ████████████              (O(n) duplicate check)
    List:  ████████████              (O(n) duplicate check)

Scope Exit Time:
    Array: ████████                  (compaction)
    List:  ██████                    (unlink)

Memory Usage:
    Array: ████████████████████████  (constant 80KB)
    List:  ████                      (grows linearly)
           (10 symbols)
           ████████████████          (500 symbols)
           (scales with usage)
```

## 🎯 Decision Matrix

```
Choose ARRAY if:
├─ Program size: < 1000 symbols ✅
├─ Performance: Cache locality matters ✅
├─ Simplicity: Easy to understand/debug ✅
├─ Memory: Can afford 80KB overhead ✅
└─ Use case: Educational/Lab assignment ✅

Choose LINKED LIST if:
├─ Program size: Unknown or very large ✅
├─ Memory: Limited, pay-per-use ✅
├─ Flexibility: Need dynamic growth ✅
├─ Learning: Study data structures ✅
└─ Production: Real compiler backend ✅
```

## 🔍 Visual Comparison Summary

| Aspect | Array | Linked List |
|--------|-------|-------------|
| **Memory Layout** | `[██████████████]` Contiguous | `[█]→[█]→[█]→[█]` Fragmented |
| **Insertion Point** | End (append) | Head (prepend) |
| **Cache Hits** | `████████` High | `██` Low |
| **Code Complexity** | `██` Simple | `████` Moderate |
| **Memory Waste** | `████` Constant | `█` Variable |
| **Scalability** | `██` Fixed | `████` Unlimited |

---

**Recommendation for Assignment-04:** Use **Array** ✅  
**Recommendation for Learning:** Study **Both** 📚
