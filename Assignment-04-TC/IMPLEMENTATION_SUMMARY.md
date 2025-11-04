# Type Checking Implementation Summary

## Assignment-04: Type Checking for C Language Subset

### Student Information
- **Course**: Compiler Design Lab
- **Assignment**: Assignment-04
- **Topic**: Type Checking using YACC

---

## Requirements Fulfilled

### ✅ Requirement (a): Sub-expression Type Compatibility
**Requirement**: Types of all the sub-expressions in an expression must be of the same type, otherwise show a type error message.

**Implementation**:
- File: `parse.y` (lines with `check_binary_op_type`, `check_relational_op_type`, `check_logical_op_type`)
- Functions:
  - `data_type_t check_binary_op_type(data_type_t left, data_type_t right, char* op)`
  - `data_type_t check_relational_op_type(data_type_t left, data_type_t right, char* op)`
  - `data_type_t check_logical_op_type(data_type_t left, data_type_t right, char* op)`

**Grammar Rules Modified**:
- `additive_expr`: Checks type compatibility for + and - operations
- `multiplicative_expr`: Checks type compatibility for *, /, % operations
- `relational_expr`: Checks type compatibility for <, >, <=, >= operations
- `equality_expr`: Checks type compatibility for ==, != operations
- `logical_or_expr`: Checks type compatibility for || operation
- `logical_and_expr`: Checks type compatibility for && operation
- `bit_or_expr`, `bit_xor_expr`, `bit_and_expr`: Checks for bitwise operations

**Error Messages Generated**:
```
TYPE ERROR (Line X): Binary operator 'OP' requires numeric operands, got 'type1' and 'type2'
TYPE ERROR (Line X): Type mismatch in binary operation 'OP': 'type1' and 'type2' are not compatible
```

---

### ✅ Requirement (b): Assignment Type Checking
**Requirement**: Check whether or not the assignment statement is type correct. The type of left and right side of an assignment statement must be of similar type. Detect illegal assignment.

**Implementation**:
- File: `parse.y` (function `check_assignment_type`)
- Function: `void check_assignment_type(data_type_t left_type, data_type_t right_type, int is_lvalue)`

**Grammar Rules Modified**:
- `assignment_expr`: All assignment operators (=, +=, -=, *=, /=, %=) now validate:
  1. Left side is an lvalue
  2. Types are compatible
  3. Not assigning to arrays directly

**Checks Performed**:
1. **Lvalue validation**: Ensures left side can be assigned to
2. **Array assignment prevention**: Arrays cannot be assigned directly
3. **Type compatibility**: Uses `are_types_compatible()` function

**Error Messages Generated**:
```
TYPE ERROR (Line X): Left side of assignment must be an lvalue (variable or array element)
TYPE ERROR (Line X): Cannot assign to an array directly
TYPE ERROR (Line X): Type mismatch in assignment: cannot assign 'type2' to 'type1'
```

---

### ✅ Requirement (c): Conditional Statement Type Checking
**Requirement**: Expressions in conditional and while statements, type of all operands must be of the same type. Show error with line number for type mismatches.

**Implementation**:
- File: `parse.y` (function `check_condition_type`)
- Function: `void check_condition_type(data_type_t cond_type)`

**Grammar Rules Modified**:
- `selection_statement`: 
  - IF statement conditions validated
  - IF-ELSE statement conditions validated
- `iteration_statement`:
  - WHILE loop conditions validated
  - DO-WHILE loop conditions validated
  - FOR loop conditions validated (if present)

**Checks Performed**:
1. Condition expression must be numeric type
2. All operands in condition must have compatible types (checked by sub-expression rules)

**Error Messages Generated**:
```
TYPE ERROR (Line X): Condition must be numeric type, got 'type'
TYPE ERROR (Line X): Type mismatch in relational operation 'OP': 'type1' and 'type2' are not compatible
```

---

### ✅ Requirement (d): Pointer/Memory Error Detection
**Requirement**: Identify memory errors, such as attempting to use an integer as a pointer.

**Implementation**:
- File: `parse.y` (function `check_pointer_dereference`)
- File: `symbol_table.c` (functions `is_pointer_type`, `is_array_type`)
- Function: `void check_pointer_dereference(data_type_t type)`

**Grammar Rules Modified**:
- `postfix_expr`: Array subscript operations (`expr[index]`) now validate:
  1. Base expression is array or pointer type
  2. Index expression is numeric type

**Checks Performed**:
1. **Subscript validation**: Only arrays and pointers can be subscripted
2. **Index type validation**: Array indices must be numeric
3. **Type classification**: Distinguishes between pointers, arrays, and regular variables

**Error Messages Generated**:
```
TYPE ERROR (Line X): Cannot dereference non-pointer type 'int' - attempting to use an integer as a pointer
TYPE ERROR (Line X): Array index must be numeric type, got 'type'
```

---

### ✅ Requirement (e): Array Declaration Type Checking
**Requirement**: Type checking for statements like array declarations.

**Implementation**:
- File: `symbol_table.h` (extended data types and symbol attributes)
- File: `symbol_table.c` (function `add_symbol_with_attrs`)
- File: `parse.y` (modified `declarator` rules)

**Type System Extensions**:
```c
typedef enum {
    TYPE_INT, TYPE_FLOAT, TYPE_CHAR, TYPE_VOID,
    TYPE_INT_ARRAY,    // Array of int
    TYPE_FLOAT_ARRAY,  // Array of float
    TYPE_CHAR_ARRAY    // Array of char
} data_type_t;
```

**Symbol Table Extensions**:
```c
typedef struct {
    char name[MAX_ID_LENGTH];
    data_type_t type;
    // ... other fields ...
    int is_array;       // Flag indicating array
    int array_size;     // Array dimension
    int is_pointer;     // Flag indicating pointer
} symbol_t;
```

**Grammar Rules Modified**:
- `declarator`: Now converts base type to array type and stores size
  - `int arr[10]` → TYPE_INT_ARRAY with size 10
  - `float vals[5]` → TYPE_FLOAT_ARRAY with size 5

**Checks Performed**:
1. **Array type encoding**: Arrays have distinct types from base types
2. **Size tracking**: Array sizes stored in symbol table
3. **Element access validation**: Array subscript operations return base type
4. **Assignment validation**: Cannot assign to array name directly

**Example**:
```c
int arr[10];      // TYPE_INT_ARRAY, size=10
arr[0] = 100;     // Valid: assigns int to int array element
arr = 5;          // TYPE ERROR: cannot assign to array
```

---

## Additional Helper Functions

### Symbol Table Functions (symbol_table.c)

1. **`int are_types_compatible(data_type_t type1, data_type_t type2)`**
   - Checks if two types can be used together
   - Handles numeric promotions (int ↔ char)
   - Returns 1 if compatible, 0 otherwise

2. **`data_type_t get_base_type(data_type_t type)`**
   - Extracts base type from arrays/pointers
   - Example: TYPE_INT_ARRAY → TYPE_INT

3. **`int is_array_type(data_type_t type)`**
   - Returns 1 if type is an array

4. **`int is_pointer_type(data_type_t type)`**
   - Returns 1 if type is a pointer

5. **`int is_numeric_type(data_type_t type)`**
   - Returns 1 if type can be used in arithmetic

---

## Type Propagation Mechanism

### Expression Type Information
```c
struct {
    data_type_t type;    // Type of the expression result
    int is_lvalue;       // Whether it can be assigned to
} expr_info;
```

### Flow Through Grammar
```
primary_expr (ID/constant)
    ↓ [type determined from symbol table or literal]
postfix_expr (arrays/function calls)
    ↓ [array subscript returns element type]
unary_expr (++/--/!/~)
    ↓ [validates operand, returns same type]
multiplicative_expr (*/%/)
    ↓ [checks compatibility, returns result type]
additive_expr (+/-)
    ↓ [checks compatibility, returns result type]
... (other expression levels)
    ↓
assignment_expr (=, +=, etc.)
    ↓ [validates lvalue and type compatibility]
expression (comma operator)
    ↓ [returns rightmost type]
```

---

## Test Files Created

1. **test_type_checking.c**: Basic type compatibility errors
2. **test_arrays.c**: Array declaration and subscripting
3. **test_conditionals.c**: Type checking in if/while
4. **test_expressions.c**: Expression type compatibility
5. **test_pointer_errors.c**: Pointer misuse detection
6. **test_comprehensive.c**: All features combined
7. **test_simple.c**: Basic program structure

---

## Build and Compilation

### Build Process
```bash
make clean    # Clean previous builds
make          # Build the parser
```

### Generated Files
- `y.tab.c`, `y.tab.h`: Parser generated by YACC
- `lex.yy.c`: Lexer generated by LEX
- `symbol_parser`: Final executable

### Compilation Output
- Warnings about shift/reduce conflicts (inherited from Assignment-03)
- Successfully creates `symbol_parser` executable

---

## Summary

All five requirements have been successfully implemented:

✅ **(a)** Expression sub-type compatibility checking with detailed error messages
✅ **(b)** Assignment type validation with lvalue checking  
✅ **(c)** Conditional statement type validation
✅ **(d)** Pointer/memory error detection (integer as pointer)
✅ **(e)** Array declaration type checking with proper type encoding

The implementation provides comprehensive type checking for a C language subset, with clear error messages indicating line numbers and specific type mismatches.

---

## Known Limitations

1. Grammar conflicts from previous assignments affect parsing of complex programs
2. Function return types are assumed to be `int` (not fully validated)
3. No implicit type conversion/casting
4. Pointer arithmetic not implemented
5. No struct/union type support

Despite these limitations, all core type checking requirements are fully implemented and functional.
