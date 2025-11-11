# Assignment-04: Type Checking for C Language Subset

## Overview
This assignment extends the previous parser (Assignment-03) with comprehensive type checking capabilities for a subset of the C programming language.

## Implemented Features

### 1. Type System Enhancement
- **Extended Type Support**: Added support for arrays and pointers
  - `TYPE_INT_ARRAY`, `TYPE_FLOAT_ARRAY`, `TYPE_CHAR_ARRAY`
  - `TYPE_INT_PTR`, `TYPE_FLOAT_PTR`, `TYPE_CHAR_PTR`
  
- **Symbol Table Extensions**:
  - `is_array`: Flag to indicate array variables
  - `array_size`: Store array dimensions
  - `is_pointer`: Flag to indicate pointer variables

### 2. Type Checking Features Implemented

#### a) Expression Type Checking
**Requirement**: Types of all sub-expressions in an expression must be of the same type

**Implementation**:
- `check_binary_op_type()`: Validates operands in binary operations (+, -, *, /, %, etc.)
- `check_relational_op_type()`: Validates operands in comparison operations (<, >, <=, >=, ==, !=)
- `check_logical_op_type()`: Validates operands in logical operations (&&, ||)
- Type propagation through expression grammar rules

**Example Errors Detected**:
```c
int a = 10;
float x = 3.14;
int c = a + x;  // TYPE ERROR: incompatible types int and float
```

#### b) Assignment Type Checking
**Requirement**: Check whether assignment statement is type correct

**Implementation**:
- `check_assignment_type()`: Validates left and right side type compatibility
- `is_lvalue` tracking: Ensures left side is a valid lvalue
- Prevents array direct assignment
- Checks type compatibility using `are_types_compatible()`

**Example Errors Detected**:
```c
int a;
float x = 3.14;
a = x;  // TYPE ERROR: cannot assign 'float' to 'int'

int arr[10];
arr = a;  // TYPE ERROR: cannot assign to an array directly
```

#### c) Conditional Statement Type Checking
**Requirement**: Expressions in conditional and while statements must have compatible operand types

**Implementation**:
- `check_condition_type()`: Validates condition expressions in if/while/for statements
- Ensures conditions are numeric types
- Checks operand type compatibility within conditions

**Example Errors Detected**:
```c
int a = 10;
float x = 3.14;

if (a < x) {  // TYPE ERROR: type mismatch in relational operation
    // ...
}

while (a && x) {  // TYPE ERROR: incompatible types in logical operation
    // ...
}
```

#### d) Pointer/Memory Error Detection
**Requirement**: Identify memory errors such as attempting to use an integer as a pointer

**Implementation**:
- `check_pointer_dereference()`: Validates pointer/array subscript operations
- `is_pointer_type()`, `is_array_type()`: Type classification functions
- Array subscript validation in postfix expressions

**Example Errors Detected**:
```c
int a = 10;
a[0] = 50;  // TYPE ERROR: Cannot dereference non-pointer type 'int' 
            // - attempting to use an integer as a pointer
```

#### e) Array Declaration Type Checking
**Requirement**: Type checking for array declarations

**Implementation**:
- Array type encoding in symbol table
- Array size tracking
- Type-specific array types (int[], float[], char[])
- Array element type checking on subscript operations

**Example**:
```c
int arr[10];       // Stored as TYPE_INT_ARRAY, size=10
float vals[5];     // Stored as TYPE_FLOAT_ARRAY, size=5

arr[0] = 100;      // Valid: int to int[]
vals[0] = 3.14;    // Valid: float to float[]
arr[0] = 3.14;     // TYPE ERROR: float to int[] mismatch
```

## Documentation

This assignment includes several detailed documentation files:

- **[HASHTABLE_LINKEDLIST_IMPLEMENTATION.md](HASHTABLE_LINKEDLIST_IMPLEMENTATION.md)** - Comprehensive guide to the hybrid hashtable + doubly linked list symbol table implementation, including detailed explanations of data structures, algorithms, performance analysis, and examples.
- **[DOC.md](DOC.md)** - Interaction between lexical analyzer, parser, and symbol table
- **[IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md)** - Summary of type checking implementation
- **[CODE_FLOW_EXPLANATION.md](CODE_FLOW_EXPLANATION.md)** - Detailed code flow and execution examples
- **[SYMBOL_TABLE_README.md](SYMBOL_TABLE_README.md)** - Basic symbol table overview

## File Structure

```
Assignment-04/
├── lex.l                                        # Lexical analyzer (from Assignment-02)
├── parse.y                                      # Parser with type checking rules
├── symbol_table.h                               # Enhanced symbol table header
├── symbol_table.c                               # Symbol table implementation with type checking
├── Makefile                                     # Build configuration
├── README.md                                    # This file
├── HASHTABLE_LINKEDLIST_IMPLEMENTATION.md       # Detailed hashtable + linked list docs
├── DOC.md                                       # Component interaction documentation
├── IMPLEMENTATION_SUMMARY.md                    # Type checking summary
├── CODE_FLOW_EXPLANATION.md                     # Code flow and execution
├── SYMBOL_TABLE_README.md                       # Symbol table overview
├── test_type_checking.c                         # Test: basic type compatibility
├── test_arrays.c                                # Test: array type checking
├── test_conditionals.c                          # Test: conditional type checking
├── test_expressions.c                           # Test: expression type checking
├── test_pointer_errors.c                        # Test: pointer error detection
├── test_comprehensive.c                         # Test: comprehensive scenarios
└── test_simple.c                                # Test: simple program structure
```

## Building the Project

```bash
# Clean previous builds
make clean

# Build the parser
make

# This creates the executable: symbol_parser
```

## Usage

```bash
# Test with a file
./symbol_parser < test_file.c

# Test with inline input
echo "int main() { int x; x = 10; return 0; }" | ./symbol_parser
```

## Type Checking Functions

### Core Functions in symbol_table.c

1. **`are_types_compatible(type1, type2)`**
   - Checks if two types can be used together in operations
   - Handles numeric promotions (int/char compatibility)
   - Returns 1 if compatible, 0 otherwise

2. **`get_base_type(type)`**
   - Extracts base type from array/pointer types
   - Example: `TYPE_INT_ARRAY` → `TYPE_INT`

3. **`is_array_type(type)`**
   - Returns 1 if type is an array type

4. **`is_pointer_type(type)`**
   - Returns 1 if type is a pointer type

5. **`is_numeric_type(type)`**
   - Returns 1 if type can be used in arithmetic operations

### Type Checking Functions in parse.y

1. **`check_binary_op_type(left, right, op)`**
   - Validates binary arithmetic/bitwise operations
   - Returns result type or TYPE_UNKNOWN on error

2. **`check_relational_op_type(left, right, op)`**
   - Validates relational operations
   - Always returns TYPE_INT (boolean result)

3. **`check_logical_op_type(left, right, op)`**
   - Validates logical operations (&&, ||)
   - Returns TYPE_INT

4. **`check_assignment_type(left_type, right_type, is_lvalue)`**
   - Validates assignment statements
   - Checks lvalue requirement
   - Checks type compatibility

5. **`check_condition_type(cond_type)`**
   - Validates conditional expressions
   - Ensures numeric type

6. **`check_pointer_dereference(type)`**
   - Validates pointer/array subscript operations
   - Detects illegal use of integers as pointers

## Type Propagation

The parser uses a union type `expr_info` to propagate type information through expressions:

```c
struct {
    data_type_t type;    // Type of the expression
    int is_lvalue;       // Whether it's an lvalue (can be assigned to)
} expr_info;
```

This information flows through:
- `primary_expr` → `postfix_expr` → `unary_expr` → ...
- ... → `additive_expr` → ... → `assignment_expr` → `expression`

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

## Known Issues

1. **Grammar Conflicts**: The parser has shift/reduce and reduce/reduce conflicts that may cause parsing issues with complex programs. This is inherited from Assignment-03 and would require grammar restructuring to fully resolve.

2. **Limited Testing**: Due to grammar conflicts, full end-to-end testing of all type checking features in complex programs is limited. Individual type checking functions are correctly implemented.

3. **Function Return Types**: Function return type checking is not fully implemented - functions are assumed to return `int`.

## Testing Strategy

Each test file focuses on specific type checking aspects:

1. **test_type_checking.c**: Basic type mixing errors
2. **test_arrays.c**: Array declaration and subscripting
3. **test_conditionals.c**: Type checking in if/while statements
4. **test_expressions.c**: Expression type compatibility
5. **test_pointer_errors.c**: Pointer misuse detection
6. **test_comprehensive.c**: All features combined

## References

- Assignment-03: Parser with error recovery
- Assignment-02: Lexical analyzer with error detection
- Symbol table implementation with scope management
- C type system and type compatibility rules

## Future Enhancements

1. Resolve grammar conflicts for better parsing
2. Add pointer arithmetic type checking
3. Implement function return type validation
4. Add struct/union type support
5. Implement implicit type casting rules
6. Add more detailed error messages with suggestions
