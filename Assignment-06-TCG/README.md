# Assignment 06: Target Code Generation (TCG)

## Overview
This assignment implements a **Target Code Generator** that reads **three-address code (intermediate representation)** and generates **assembly code** for a RISC-like target machine with **register allocation** following the **Aho-Sethi-Ullman algorithm** (Compilers: Principles, Techniques, and Tools, pp 535-541).

## Complete Compilation Pipeline

```
┌─────────────┐
│  C Source   │
│  (test.c)   │
└──────┬──────┘
       │
       │ [lex.l + parse.y]
       ▼
┌─────────────┐
│ ICG Compiler│ ◄─── Assignment-05-ICG
│ (icg.c)     │
└──────┬──────┘
       │
       ▼
┌────────────────────────┐
│ Three-Address Code     │
│ (three_address_code.txt)│
│                        │
│ 0  =   10      a       │
│ 1  +   a   b   T0      │
│ 2  =   T0      c       │
└──────────┬─────────────┘
           │
           │ [This Assignment]
           ▼
┌─────────────────────┐
│  Code Generator     │ ◄─── Assignment-06-TCG
│  (codegen.c)        │
│  - Register Alloc   │
│  - getReg()         │
│  - Address Desc     │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Assembly Code      │
│  (assembly_code.asm)│
│                     │
│  LD R0, #10         │
│  ST a, R0           │
│  LD R0, a           │
│  LD R1, b           │
│  ADD R2, R0, R1     │
│  ST c, R2           │
│  HALT               │
└─────────────────────┘
```

## Features
- ✅ Reads three-address code (quadruples) from file
- ✅ Register allocation with 4 general-purpose registers (R0-R3)
- ✅ Implements getReg() algorithm for optimal register usage
- ✅ Generates assembly code for:
  - Assignment statements
  - Arithmetic expressions (+, -, *, /)
  - Unary operations (uminus)
  - If statements
  - If-else statements
  - While loops
- ✅ Register and address descriptor management
- ✅ Automatic register spilling when needed
- ✅ 8085/8086 compatible instruction set

## Target Machine Model

### Instruction Set
The target machine follows the **Intel 8086 architecture** with the following instructions:

#### Data Transfer Operations
```assembly
MOV dest, source    ; Move data: dest = source
                    ; - MOV AX, 10       (immediate to register)
                    ; - MOV AX, [var]    (memory to register)
                    ; - MOV [var], AX    (register to memory)
                    ; - MOV AX, BX       (register to register)
```

#### Arithmetic Operations
```assembly
ADD dest, source    ; dest = dest + source
SUB dest, source    ; dest = dest - source
IMUL dest, source   ; dest = dest * source (signed multiply)
IDIV source         ; AX = DX:AX / source (signed divide)
NEG dest            ; dest = -dest (two's complement)
INC dest            ; dest = dest + 1
DEC dest            ; dest = dest - 1
```

#### Comparison and Control Flow
```assembly
CMP operand1, operand2  ; Compare (sets flags)
JE label            ; Jump if equal (zero flag set)
JNE label           ; Jump if not equal
JMP label           ; Unconditional jump
label:              ; Label declaration
```

#### Program Structure
```assembly
.MODEL SMALL        ; Memory model
.STACK 100h         ; Stack size
.DATA               ; Data segment
.CODE               ; Code segment
INT 21h             ; DOS interrupt (program termination)
```

### Registers
- **AX, BX, CX, DX**: 16-bit general-purpose registers
- **4 registers total** - standard 8086 register subset
- Each register can be split into high/low bytes (AH/AL, BH/BL, etc.)

## Algorithm: Register Allocation (getReg)

The `get_reg()` function implements the Aho-Sethi-Ullman algorithm for register allocation:

### Priority Strategy
1. **Reuse**: If variable already in a register, return that register
2. **Free Register**: Allocate from available free registers
3. **Spill Selection**: When all registers are busy, select register to spill based on:
   - **Highest Priority**: Variable is dead (not live after this instruction)
   - **Medium Priority**: Register is clean (value matches memory)
   - **Low Priority**: Register contains temporary variable
   - **Never Spill**: Registers containing operands of current instruction (arg1, arg2)

### Pseudocode
```
function getReg(var, arg1, arg2):
    // Check if var already in register
    if var in some register Ri:
        return Ri
    
    // Find free register
    for each register Ri:
        if Ri is free:
            allocate Ri for var
            return Ri
    
    // All busy - select register to spill
    best_reg = -1
    best_priority = -1
    
    for each register Ri:
        if Ri contains arg1 or arg2:
            continue  // Don't spill operands
        
        priority = 0
        if Ri contains dead variable:
            priority = 1000
        else if Ri is clean:
            priority = 100
        else if Ri contains temporary:
            priority = 50
        
        if priority > best_priority:
            best_priority = priority
            best_reg = Ri
    
    spill(best_reg)
    allocate best_reg for var
    return best_reg
```

## Data Structures

### 1. Register Descriptor
Tracks what each register contains:
```c
typedef struct {
    char name[8];           // Register name (R0, R1, R2, R3)
    bool is_free;           // Is register available?
    char contains[32];      // What variable is in this register
    bool dirty;             // Modified but not stored to memory?
} RegisterDescriptor;
```

### 2. Address Descriptor
Tracks where each variable is located:
```c
typedef struct {
    char var_name[32];      // Variable/temp name
    bool in_memory;         // Is it in memory?
    int reg_num;            // Which register (-1 if not in register)
    bool live;              // Is variable live after this instruction?
} AddressDescriptor;
```

### 3. Quadruple (Three-Address Code)
```c
typedef struct {
    int label;              // Instruction number
    char op[16];            // Operation (+, -, *, /, =, etc.)
    char arg1[16];          // First operand
    char arg2[16];          // Second operand
    char result[16];        // Result destination
} Quadruple;
```

## Code Generation Examples

### Example 1: Assignment Statement
**Three-Address Code:**
```
0  =  10    a
1  =  20    b
2  +  a  b  T0
3  =  T0    c
```

**Generated 8086 Assembly:**
```assembly
.MODEL SMALL
.STACK 100h

.DATA
    ; Variable declarations

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

; = 10, , a
    MOV AX, 10        ; Load constant 10

; = 20, , b
    MOV BX, 20        ; Load constant 20

; + a, b, T0
    MOV CX, AX        ; Copy operand
    ADD CX, BX        ; CX = AX + BX

; = T0, , c
    MOV DX, CX        ; c = T0

; Store all values back to memory
    MOV [a], AX       ; Store AX to a
    MOV [b], BX       ; Store BX to b
    MOV [T0], CX      ; Store CX to T0
    MOV [c], DX       ; Store DX to c

    MOV AH, 4Ch       ; DOS exit
    INT 21h
MAIN ENDP
END MAIN
```

### Example 2: Arithmetic with Unary Minus
**Three-Address Code:**
```
0  =      10      a
1  =      20      b
2  uminus b       T0
3  =      5       c
4  *      a  T0   T1
5  +      T1 c    T2
6  =      T2      d
```

**Generated Assembly:**
```assembly
; = 10, , a
    LD R0, #10        ; Load constant 10

; = 20, , b
    LD R1, #20        ; Load constant 20

; uminus b, , T0
    LD R1, b          ; Load b into R1
    NEG R2, R1        ; R2 = -R1

; = 5, , c
    LD R1, #5         ; Load constant 5

; * a, T0, T1
    LD R0, a          ; Load a into R0
    LD R2, T0         ; Load T0 into R2
    MUL R3, R0, R2    ; R3 = R0 * R2

; + T1, c, T2
    LD R3, T1         ; Load T1 into R3
    LD R1, c          ; Load c into R1
    ADD R0, R3, R1    ; R0 = R3 + R1

; = T2, , d
    LD R0, T2         ; Load T2
    ST d, R0          ; Store R0 to d
```

### Example 3: If Statement
**Three-Address Code:**
```
0  =       10      x
1  =       20      y
2  ifFalse x       L0
3  +       y  5    T0
4  =       T0      y
5  label_end       L0
```

**Generated Assembly:**
```assembly
; = 10, , x
    LD R0, #10        ; Load constant 10

; = 20, , y
    LD R1, #20        ; Load constant 20

; ifFalse x, , L0
    LD R0, x          ; Load x into R0
    CMP R0, #0        ; Compare x with 0
    JE L0             ; Jump to L0 if equal (false)

; + y, 5, T0
    LD R1, y          ; Load y into R1
    LD R2, #5         ; Load constant 5
    ADD R3, R1, R2    ; R3 = R1 + R2

; = T0, , y
    LD R3, T0         ; Load T0
    ST y, R3          ; Store R3 to y

; label_end, , L0
L0:
```

### Example 4: While Loop
**Three-Address Code:**
```
0  =           0       sum
1  =           5       i
2  label_begin         L0
3  ifFalse    i        L1
4  +          sum i    T0
5  =          T0       sum
6  -          i   1    T1
7  =          T1       i
8  goto                L0
9  label_end           L1
```

**Generated Assembly:**
```assembly
; = 0, , sum
    LD R0, #0         ; Load constant 0
    ST sum, R0        ; Store R0 to sum

; = 5, , i
    LD R1, #5         ; Load constant 5
    ST i, R1          ; Store R1 to i

; label_begin, , L0
L0:

; ifFalse i, , L1
    LD R1, i          ; Load i into R1
    CMP R1, #0        ; Compare i with 0
    JE L1             ; Jump to L1 if equal (false)

; + sum, i, T0
    LD R0, sum        ; Load sum into R0
    LD R1, i          ; Load i into R1
    ADD R2, R0, R1    ; R2 = R0 + R1
    ST T0, R2         ; Store R2 to T0

; = T0, , sum
    LD R2, T0         ; Load T0
    ST sum, R2        ; Store R2 to sum

; - i, 1, T1
    LD R1, i          ; Load i into R1
    LD R3, #1         ; Load constant 1
    SUB R0, R1, R3    ; R0 = R1 - R3
    ST T1, R0         ; Store R0 to T1

; = T1, , i
    LD R0, T1         ; Load T1
    ST i, R0          ; Store R0 to i

; goto, , L0
    JMP L0            ; Unconditional jump to L0

; label_end, , L1
L1:

HALT
```

## Building the Project

### Compile
```bash
make clean    # Clean previous builds
make          # Compile both ICG compiler and code generator
```

This builds:
- **icg_compiler**: Generates three-address code from C source
- **codegen**: Generates assembly code from three-address code

### Run Options

#### Option 1: Full Pipeline (C source → TAC → Assembly)
```bash
# Run complete pipeline with test file
make pipeline

# Or manually:
./icg_compiler < test_comprehensive.c    # Generates three_address_code.txt
./codegen three_address_code.txt          # Generates assembly_code.asm
```

#### Option 2: Run Code Generator with Pre-generated TAC
```bash
# Run with default input file (three_address_code.txt)
./codegen

# Run with specific test file
./codegen test1_tac.txt
```

#### Option 3: Run ICG Compiler Only
```bash
make run_icg                              # Generate TAC from test_comprehensive.c
./icg_compiler < test_assignment.c        # Generate TAC from specific file
```

### Run Tests

#### Test with Pre-generated TAC Files
```bash
make test1        # Test assignment statements
make test2        # Test arithmetic expressions
make test3        # Test if statement
make test4        # Test while loop
make test5        # Test comprehensive (if-else + while)
make test_all     # Run all tests
```

#### Test with C Source Files (Full Pipeline)
```bash
make test_assignment      # C source → TAC → Assembly
make test_expression      # Test arithmetic expressions
make test_if              # Test if statements
make test_while           # Test while loops
make test_comprehensive   # Test comprehensive example
```

## File Structure

```
Assignment-06-TCG/
├── codegen.h              # Code generator header
├── codegen.c              # Register allocation & code generation
├── main.c                 # Code generator driver
├── icg.h                  # ICG module header
├── icg.c                  # Intermediate code generation
├── symbol_table.h         # Symbol table header
├── symbol_table.c         # Symbol table implementation
├── parse.y                # YACC parser (from Assignment-05)
├── lex.l                  # Flex lexer (from Assignment-05)
├── Makefile               # Build configuration
├── README.md              # This file
│
├── Test TAC Files (Pre-generated Three-Address Code):
│   ├── test1_tac.txt      # Assignment statements
│   ├── test2_tac.txt      # Arithmetic expressions
│   ├── test3_tac.txt      # If statement
│   ├── test4_tac.txt      # While loop
│   └── test5_tac.txt      # Comprehensive
│
├── Test C Source Files:
│   ├── test_assignment.c  # Simple assignments
│   ├── test_expression.c  # Arithmetic expressions
│   ├── test_if.c          # If statements
│   ├── test_ifelse.c      # If-else statements
│   ├── test_while.c       # While loops
│   └── test_comprehensive.c # Comprehensive test
│
├── Generated Files (after running):
│   ├── icg_compiler       # ICG executable
│   ├── codegen            # Code generator executable
│   ├── three_address_code.txt  # Generated TAC
│   └── assembly_code.asm  # Generated assembly
│
└── Code_Gen.pdf           # Assignment specification
```

## Input Format

The program reads three-address code in the following format:

```
=== THREE ADDRESS CODE (Quadruples) ===

Label  Op           Arg1         Arg2         Result      
------------------------------------------------------------
0      =            10                        a           
1      +            a            b            c           
2      ifFalse      x                         L0          
3      label_begin                            L1          
4      goto                                   L0          
------------------------------------------------------------
```

## Output Format

Generated assembly code in `assembly_code.asm`:

```assembly
; Assembly Code Generated from Three-Address Code
; Target Machine: RISC-like with 4 registers (R0-R3)
; Instruction Set: 8085/8086 compatible

; = 10, , a
    LD R0, #10        ; Load constant 10
    ST a, R0          ; Store R0 to a

; + a, b, c
    LD R0, a          ; Load a into R0
    LD R1, b          ; Load b into R1
    ADD R2, R0, R1    ; R2 = R0 + R1
    ST c, R2          ; Store R2 to c

HALT
```

## Key Implementation Features

### 1. Register Spilling
When all registers are occupied, the code generator automatically:
- Selects the best register to spill based on liveness and usage
- Stores the register's value back to memory
- Allocates the freed register for the new variable

### 2. Register Reuse
If a variable is already in a register, the code generator:
- Reuses that register instead of loading again
- Reduces redundant load/store operations
- Improves code efficiency

### 3. Dead Variable Elimination
Temporary variables that are no longer needed:
- Are identified automatically
- Their registers can be reused without spilling
- Reduces memory traffic

### 4. Address Descriptor Management
Tracks for each variable:
- Which register(s) contain it
- Whether it's in memory
- Whether it's live after current instruction

### 5. Register Descriptor Management
Tracks for each register:
- What variable/value it contains
- Whether it's free or occupied
- Whether it's dirty (modified but not stored)

## Optimizations Implemented

1. **Register Reuse**: If operand already in register, reuse it
2. **Dead Variable Handling**: Don't spill dead variables
3. **Clean Register Preference**: Prefer spilling clean registers
4. **Temporary Priority**: Prefer spilling temporaries over user variables
5. **Operand Protection**: Never spill registers containing current operands

## Limitations

1. **Fixed Register Set**: Uses exactly 4 registers (can be extended)
2. **Basic Instruction Set**: Limited to common arithmetic and control flow
3. **No Advanced Optimizations**: 
   - No common subexpression elimination
   - No dead code elimination
   - No loop optimization
4. **Static Allocation**: All variables assumed in static memory area
5. **No Arrays/Pointers**: Array indexing and pointer arithmetic not implemented

## Test Cases

### Test 1: Assignment Statements
```c
a = 10;
b = 20;
c = a + b;
```

### Test 2: Arithmetic Expressions with Unary Minus
```c
a = 10;
b = 20;
c = 5;
d = a * (-b) + c;
```

### Test 3: If Statement
```c
x = 10;
y = 20;
if (x) {
    y = y + 5;
}
```

### Test 4: While Loop
```c
sum = 0;
i = 5;
while (i) {
    sum = sum + i;
    i = i - 1;
}
```

### Test 5: Comprehensive (If-Else + While)
```c
a = 10;
b = 20;
c = a + b * 2;

if (c) {
    result = c - 5;
} else {
    result = 0;
}

while (a) {
    a = a - 1;
    result = result + a;
}
```

## References

1. **Aho, A. V., Sethi, R., Ullman, J. D.** - "Compilers: Principles, Techniques, and Tools" (Dragon Book)
   - Chapter 8: Code Generation
   - Section 8.6: A Simple Code Generator (pp 535-541)
   - Section 8.8: Register Allocation and Assignment

2. **8085/8086 Instruction Set**
   - Load/Store operations
   - Arithmetic operations
   - Control flow instructions

## Author
Compiler Design Lab - Assignment 06
Target Code Generation

## License
Educational purposes - Compiler Design course
