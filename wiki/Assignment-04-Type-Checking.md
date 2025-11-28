# Assignment 04: Type Checking and Semantic Analysis

## Overview

This assignment extends the parser with comprehensive **type checking** capabilities for a subset of the C programming language, implementing semantic analysis through symbol table management.

## Key Concepts

### Type Systems

A type system is a set of rules that assigns types to program constructs and checks type compatibility.

**Key Properties:**
- **Type Safety**: Prevent type errors at compile time
- **Type Inference**: Deduce types when not explicitly stated
- **Type Compatibility**: Define which type combinations are valid

### Symbol Table

The symbol table stores information about identifiers:

```c
typedef struct {
    char name[64];          // Variable/function name
    data_type_t type;       // Type (int, float, array, pointer)
    int scope_level;        // Scope nesting level
    int is_array;           // Array flag
    int array_size;         // Size if array
    int is_pointer;         // Pointer flag
    int line_number;        // Declaration line
} SymbolEntry;
```

## Type Categories

### Basic Types

| Type | Description | Size |
|------|-------------|------|
| `TYPE_INT` | Integer | 4 bytes |
| `TYPE_FLOAT` | Floating point | 4 bytes |
| `TYPE_CHAR` | Character | 1 byte |
| `TYPE_VOID` | No type | - |

### Derived Types

| Type | Description |
|------|-------------|
| `TYPE_INT_ARRAY` | Array of integers |
| `TYPE_FLOAT_ARRAY` | Array of floats |
| `TYPE_INT_PTR` | Pointer to int |
| `TYPE_FLOAT_PTR` | Pointer to float |

## Type Checking Features

### 1. Expression Type Checking

Binary operations require compatible operand types:

```c
// Valid
int a = 10;
int b = 20;
int c = a + b;  // Both operands are int

// Invalid - Type Error
int a = 10;
float x = 3.14;
int c = a + x;  // TYPE ERROR: incompatible types int and float
```

### 2. Assignment Type Checking

Assignment statements must have compatible types:

```c
// Valid
int a;
a = 10;

// Invalid - Type Errors
int a;
float x = 3.14;
a = x;          // TYPE ERROR: cannot assign 'float' to 'int'

int arr[10];
arr = a;        // TYPE ERROR: cannot assign to array directly
```

### 3. Conditional Type Checking

Conditions must evaluate to numeric (boolean-like) types:

```c
int a = 10;
float x = 3.14;

// Invalid comparisons
if (a < x) {    // TYPE ERROR: type mismatch in relational operation
    // ...
}

while (a && x) { // TYPE ERROR: incompatible types in logical operation
    // ...
}
```

### 4. Pointer/Array Error Detection

Prevents using non-pointer types as pointers:

```c
int a = 10;
a[0] = 50;      // TYPE ERROR: Cannot dereference non-pointer type 'int'
                // Attempting to use an integer as a pointer
```

## Type Checking Functions

### Core Functions

| Function | Purpose |
|----------|---------|
| `are_types_compatible(t1, t2)` | Check if two types can be used together |
| `get_base_type(type)` | Extract base type from array/pointer |
| `is_array_type(type)` | Check if type is an array |
| `is_pointer_type(type)` | Check if type is a pointer |
| `is_numeric_type(type)` | Check if type supports arithmetic |

### Checking Functions

| Function | Purpose |
|----------|---------|
| `check_binary_op_type(left, right, op)` | Validate binary operations |
| `check_relational_op_type(left, right, op)` | Validate comparisons |
| `check_logical_op_type(left, right, op)` | Validate logical ops (&&, \|\|) |
| `check_assignment_type(left, right, is_lvalue)` | Validate assignments |
| `check_condition_type(type)` | Validate condition expressions |
| `check_pointer_dereference(type)` | Validate subscript operations |

## Type Propagation

Types flow through expressions using an expression info structure:

```c
struct expr_info {
    data_type_t type;    // Expression type
    int is_lvalue;       // Can be assigned to?
};
```

**Flow Example:**
```
primary_expr → postfix_expr → unary_expr → ... → expression
    (int)          (int)        (int)              (int)
```

## Building and Running

### Build

```bash
cd Assignment-04-TC
make clean
make
```

### Run

```bash
# Test with a file
./symbol_parser < test_type_checking.c

# Test with inline input
echo "int main() { int x; x = 10; return 0; }" | ./symbol_parser
```

## Example Output

```
=== C LANGUAGE SUBSET PARSER WITH TYPE CHECKING ===
Parsing input...

Symbol table initialized
SYMBOL TABLE: Added 'main' - Type: int, Scope: global (Level 0), Line: 1
SCOPE: Entering scope level 1
SYMBOL TABLE: Added 'a' - Type: int, Scope: block (Level 1), Line: 2
SYMBOL TABLE: Added 'x' - Type: float, Scope: block (Level 1), Line: 3
VARIABLE USE: 'a' (Type: int, Scope: block)
VARIABLE USE: 'x' (Type: float, Scope: block)
TYPE ERROR (Line 4): Type mismatch in binary operation '+': 'int' and 'float' are not compatible
...
```

## Test Files

| File | Tests |
|------|-------|
| `test_type_checking.c` | Basic type compatibility |
| `test_arrays.c` | Array declarations and subscripting |
| `test_conditionals.c` | Type checking in if/while |
| `test_expressions.c` | Expression type compatibility |
| `test_pointer_errors.c` | Pointer misuse detection |
| `test_comprehensive.c` | All features combined |

## Files

| File | Description |
|------|-------------|
| `lex.l` | Lexical analyzer |
| `parse.y` | Parser with type checking rules |
| `symbol_table.h` | Symbol table header |
| `symbol_table.c` | Symbol table implementation |
| `Makefile` | Build configuration |

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ Type system design and implementation
- ✅ Symbol table with scope management
- ✅ Type compatibility rules
- ✅ Semantic error detection
- ✅ Type propagation through AST

## Related Pages

- [Assignment 03: Syntax Analysis](Assignment-03-Syntax-Analysis)
- [Assignment 05: Intermediate Code Generation](Assignment-05-ICG)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Previous:** [Assignment 03: Syntax Analysis](Assignment-03-Syntax-Analysis)
**Next:** [Assignment 05: Intermediate Code Generation](Assignment-05-ICG)
