# Assignment 05: Intermediate Code Generation (ICG)

## Overview
This assignment implements a **Syntax-Directed Translation** scheme for converting C source code into **three-address code** using **quadruple records**. The compiler supports:
- Assignment statements with type checking
- If statements
- If-else statements
- While statements
- Complex expressions with arithmetic and unary operators

## Implementation Details

### Quadruple Structure
Each three-address instruction is represented as a quadruple with four fields:
- **Label**: Instruction number (0, 1, 2, ...)
- **Op**: Operation (=, +, -, *, /, uminus, ifFalse, goto, label, etc.)
- **Arg1**: First operand
- **Arg2**: Second operand
- **Result**: Result destination

### Files
- `icg.h` / `icg.c`: Intermediate code generation module
- `parse.y`: YACC grammar with syntax-directed translation actions
- `lex.l`: Lexical analyzer
- `symbol_table.h` / `symbol_table.c`: Symbol table management
- `Makefile`: Build configuration

### Key Features

#### 1. Assignment Statements
- Type checking ensures compatible types
- Generates three-address code with temporary variables
- Example: `c = a + b * 2`
  ```
  0  *  b  2  T0
  1  +  a  T0  T1
  2  =  T1     c
  ```

#### 2. Unary Operators
- Supports unary minus, logical NOT, bitwise NOT
- Example: `d = b * -c + a`
  ```
  0  uminus  c     T0
  1  *       b  T0 T1
  2  +       T1 a  T2
  3  =       T2    d
  ```

#### 3. If Statements
- Condition evaluation with false label
- Example: `if (x) { y = 20; }`
  ```
  0  =       10    x
  1  =       20    y
  2  ifFalse x     L0
  3  label         L0
  ```

#### 4. If-Else Statements
- Both branches generate proper code
- Example: `if (x) { y = 100; } else { y = 200; }`
  ```
  0  =  100  y     (if branch)
  1  =  200  y     (else branch)
  ```

#### 5. While Loops
- Label at loop beginning
- Conditional jump to exit
- Unconditional jump back to start
- Example: `while (i) { sum = sum + i; }`
  ```
  0  +           sum  i   T0
  1  =           T0        sum
  2  label_begin          L0
  3  ifFalse     i         L1
  4  goto                 L0
  5  label_end            L1
  ```

### Code Generation Functions

#### `init_icg()`
Initializes the intermediate code generation system:
- Opens output file `three_address_code.txt`
- Resets counters (temp_count, label_count, quad_count)

#### `gen(op, arg1, arg2, result)`
Generates a single quadruple:
- Stores in quad_array
- Writes to output file
- Prints to console for debugging

#### `new_temp()`
Creates a new temporary variable (T0, T1, T2, ...)

#### `new_label()`
Creates a new label (L0, L1, L2, ...)

#### `emit_label(label)`
Emits a label marker in the code

#### `close_icg()`
Finalizes code generation:
- Closes output file
- Prints summary statistics

## Building

```bash
make clean  # Clean previous build
make        # Compile the compiler
```

## Usage

### Run with test files:
```bash
./icg_compiler < test_assignment.c
./icg_compiler < test_expression.c
./icg_compiler < test_if.c
./icg_compiler < test_ifelse.c
./icg_compiler < test_while.c
./icg_compiler < test_comprehensive.c
```

### Or use make targets:
```bash
make test_assign
make test_if
make test_ifelse
make test_while
make test  # Run all tests
```

## Output

The compiler generates two outputs:

### 1. Console Output
Shows:
- Parsing progress
- Symbol table operations
- Type checking messages
- Generated quadruples in real-time

### 2. File Output (`three_address_code.txt`)
Contains:
- Formatted quadruple table
- All generated three-address instructions
- Summary statistics

## Example

### Input (`test_expression.c`):
```c
int main() {
    int a, b, c, d;
    a = 10;
    b = 20;
    c = -a;
    d = b * -c + a;
}
```

### Output (Quadruples):
```
Label  Op           Arg1         Arg2         Result      
------------------------------------------------------------
0      =            10                        a           
1      =            20                        b           
2      uminus       a                         T0          
3      =            T0                        c           
4      uminus       c                         T1          
5      *            b            T1           T2          
6      +            T2           a            T3          
7      =            T3                        d           
------------------------------------------------------------
```

## Type Checking

The compiler performs type checking for:
- Assignment compatibility
- Arithmetic operations (both operands must be numeric)
- Logical operations
- Unary operations
- Condition expressions in if/while statements

Type errors are reported with:
- Line number
- Error description
- Involved types

## Limitations

1. **Control Flow**: Current implementation generates simplified control flow code. Full backpatching would require maintaining jump lists.

2. **Optimization**: No optimization is performed on the generated code.

3. **Arrays/Pointers**: Array indexing and pointer arithmetic are parsed but not fully translated to three-address code.

4. **Functions**: Function calls are recognized but not translated to three-address code.

## Test Cases

### 1. `test_assignment.c`
Simple variable assignments and arithmetic

### 2. `test_expression.c`
Complex expressions with unary minus

### 3. `test_if.c`
If statement without else

### 4. `test_ifelse.c`
If-else statement

### 5. `test_while.c`
While loop

### 6. `test_comprehensive.c`
Combines all constructs: assignments, if-else, while, nested if

## References

- Aho, Sethi, Ullman - "Compilers: Principles, Techniques, and Tools" (Dragon Book)
- Chapter on Intermediate Code Generation
- Section on Syntax-Directed Translation

## Author
Compiler Design Lab - Assignment 05
