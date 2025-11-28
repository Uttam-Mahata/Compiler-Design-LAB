# Assignment 05: Intermediate Code Generation (ICG)

## Overview

This assignment implements **Syntax-Directed Translation** for converting C source code into **three-address code** using **quadruple records**. This intermediate representation bridges the gap between high-level source code and low-level machine code.

## Key Concepts

### Three-Address Code

Three-address code (TAC) uses at most three addresses per instruction:

```
result = operand1 op operand2
```

### Quadruple Representation

Each TAC instruction is stored as a quadruple:

| Field | Description |
|-------|-------------|
| **Label** | Instruction number (0, 1, 2, ...) |
| **Op** | Operation (+, -, *, /, =, goto, etc.) |
| **Arg1** | First operand |
| **Arg2** | Second operand |
| **Result** | Destination |

### Example Quadruples

For `c = a + b * 2`:

```
Label  Op    Arg1  Arg2  Result
--------------------------------
0      *     b     2     T0
1      +     a     T0    T1
2      =     T1          c
```

## Supported Constructs

### 1. Assignment Statements

```c
c = a + b * 2;
```

**Generated TAC:**
```
0  *  b  2  T0
1  +  a  T0  T1
2  =  T1     c
```

### 2. Unary Operators

```c
d = b * -c + a;
```

**Generated TAC:**
```
0  uminus  c     T0
1  *       b  T0 T1
2  +       T1 a  T2
3  =       T2    d
```

### 3. If Statements

```c
if (x) {
    y = 20;
}
```

**Generated TAC:**
```
0  ifFalse x     L0
1  =       20    y
2  label_end     L0
```

### 4. If-Else Statements

```c
if (x) {
    y = 100;
} else {
    y = 200;
}
```

**Generated TAC:**
```
0  ifFalse x      L0
1  =       100    y
2  goto           L1
3  label_else     L0
4  =       200    y
5  label_end      L1
```

### 5. While Loops

```c
while (i) {
    sum = sum + i;
    i = i - 1;
}
```

**Generated TAC:**
```
0  label_begin     L0
1  ifFalse   i     L1
2  +         sum i T0
3  =         T0    sum
4  -         i  1  T1
5  =         T1    i
6  goto            L0
7  label_end       L1
```

## Code Generation Functions

### Core Functions

| Function | Purpose |
|----------|---------|
| `init_icg()` | Initialize code generation system |
| `gen(op, arg1, arg2, result)` | Generate a single quadruple |
| `new_temp()` | Create new temporary (T0, T1, ...) |
| `new_label()` | Create new label (L0, L1, ...) |
| `emit_label(label)` | Emit a label marker |
| `close_icg()` | Finalize and close output file |

### Generation Process

```
C Source Code
     │
     ▼
┌─────────────────┐
│  Lexer (Flex)   │ ──► Tokens
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Parser (Bison)  │ ──► Parse Tree
│ + Semantic Acts │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ ICG Module      │ ──► Three-Address Code
│ (Quadruples)    │
└─────────────────┘
```

## Syntax-Directed Translation

### Expression Translation

For grammar rule: `E → E₁ + T`

```yacc
expression
    : expression PLUS term
        {
            $$ = new_temp();
            gen("+", $1, $3, $$);
        }
    ;
```

### Assignment Translation

For grammar rule: `S → id = E`

```yacc
assignment_statement
    : ID ASSIGN expression SEMICOLON
        {
            gen("=", $3, "", $1);
        }
    ;
```

### Control Flow Translation

For `if (E) S`:

```yacc
if_statement
    : IF LPAREN expression RPAREN
        {
            $<label>$ = new_label();
            gen("ifFalse", $3, "", $<label>$);
        }
      statement
        {
            emit_label($<label>5);
        }
    ;
```

## Building and Running

### Build

```bash
cd Assignment-05-ICG
make clean
make
```

### Run

```bash
# With test file
./icg_compiler < test_comprehensive.c

# View generated code
cat three_address_code.txt
```

### Make Targets

```bash
make test_assign    # Test assignments
make test_if        # Test if statements
make test_ifelse    # Test if-else
make test_while     # Test while loops
make test           # Run all tests
```

## Output Format

### Console Output

```
=== Intermediate Code Generation ===
Parsing input...

0  =       10      a
1  =       20      b
2  *       b   2   T0
3  +       a   T0  T1
4  =       T1      c

Total quadruples generated: 5
```

### File Output (three_address_code.txt)

```
=== THREE ADDRESS CODE (Quadruples) ===

Label  Op           Arg1         Arg2         Result      
------------------------------------------------------------
0      =            10                        a           
1      =            20                        b           
2      *            b            2            T0          
3      +            a            T0           T1          
4      =            T1                        c           
------------------------------------------------------------
```

## Test Files

| File | Tests |
|------|-------|
| `test_assignment.c` | Variable assignments |
| `test_expression.c` | Complex expressions |
| `test_if.c` | If statement |
| `test_ifelse.c` | If-else statement |
| `test_while.c` | While loop |
| `test_comprehensive.c` | All constructs |

## Files

| File | Description |
|------|-------------|
| `icg.h` | ICG module header |
| `icg.c` | Intermediate code generation |
| `parse.y` | YACC grammar with SDT actions |
| `lex.l` | Lexical analyzer |
| `symbol_table.c/h` | Symbol table |
| `Makefile` | Build configuration |

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ Three-address code representation
- ✅ Quadruple data structure
- ✅ Syntax-directed translation schemes
- ✅ Temporary variable management
- ✅ Label management for control flow
- ✅ Code generation for control structures

## Related Pages

- [Assignment 04: Type Checking](Assignment-04-Type-Checking)
- [Assignment 06: Target Code Generation](Assignment-06-TCG)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Previous:** [Assignment 04: Type Checking](Assignment-04-Type-Checking)
**Next:** [Assignment 06: Target Code Generation](Assignment-06-TCG)
