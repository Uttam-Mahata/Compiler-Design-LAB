# Assignment 06: Target Code Generation (TCG)

## Overview

This assignment implements a **Target Code Generator** that converts **three-address code** (intermediate representation) into **assembly code** for a RISC-like target machine, featuring **register allocation** using the **Aho-Sethi-Ullman algorithm**.

## Complete Compilation Pipeline

```
┌─────────────┐
│  C Source   │
│  (test.c)   │
└──────┬──────┘
       │
       │ [Lexer + Parser]
       ▼
┌─────────────┐
│ ICG Compiler│ ◄─── Assignment 05
│ (icg.c)     │
└──────┬──────┘
       │
       ▼
┌────────────────────────┐
│ Three-Address Code     │
│ (three_address_code.txt)│
└──────────┬─────────────┘
           │
           │ [This Assignment]
           ▼
┌─────────────────────┐
│  Code Generator     │ ◄─── Assignment 06
│  (codegen.c)        │
│  - Register Alloc   │
│  - getReg()         │
└──────────┬──────────┘
           │
           ▼
┌─────────────────────┐
│  Assembly Code      │
│  (assembly_code.asm)│
└─────────────────────┘
```

## Key Concepts

### Register Allocation

The code generator manages a limited set of registers efficiently:

- **4 general-purpose registers**: AX, BX, CX, DX (8086-like)
- **Register descriptors**: Track what each register contains
- **Address descriptors**: Track where each variable is located

### The getReg() Algorithm

The Aho-Sethi-Ullman algorithm for register allocation:

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
    select Ri with highest priority to spill
    spill(Ri)
    allocate Ri for var
    return Ri
```

### Spill Priority

When all registers are busy:

| Priority | Condition | Action |
|----------|-----------|--------|
| Highest | Variable is dead | No spill needed |
| High | Register is clean | Just deallocate |
| Medium | Contains temporary | Spill to memory |
| Low | Contains user variable | Spill to memory |
| Never | Contains current operands | Skip |

## Target Machine Model

### 8086-Compatible Instruction Set

#### Data Transfer
```assembly
MOV dest, source    ; Move data
                    ; MOV AX, 10      (immediate)
                    ; MOV AX, [var]   (memory)
                    ; MOV [var], AX   (store)
```

#### Arithmetic
```assembly
ADD dest, source    ; dest = dest + source
SUB dest, source    ; dest = dest - source
IMUL dest, source   ; dest = dest * source
IDIV source         ; AX = DX:AX / source
NEG dest            ; dest = -dest
```

#### Control Flow
```assembly
CMP op1, op2        ; Compare (sets flags)
JE label            ; Jump if equal
JNE label           ; Jump if not equal
JMP label           ; Unconditional jump
```

## Data Structures

### Register Descriptor

```c
typedef struct {
    char name[8];       // "AX", "BX", etc.
    bool is_free;       // Available?
    char contains[32];  // Variable name
    bool dirty;         // Modified?
} RegisterDescriptor;
```

### Address Descriptor

```c
typedef struct {
    char var_name[32];  // Variable name
    bool in_memory;     // In memory?
    int reg_num;        // Which register (-1 if none)
    bool live;          // Live after this instruction?
} AddressDescriptor;
```

## Code Generation Examples

### Example 1: Simple Assignment

**TAC:**
```
0  =  10    a
1  =  20    b
2  +  a  b  T0
3  =  T0    c
```

**Assembly:**
```assembly
    MOV AX, 10        ; a = 10
    MOV BX, 20        ; b = 20
    MOV CX, AX        ; Copy a
    ADD CX, BX        ; CX = a + b
    MOV DX, CX        ; c = T0
```

### Example 2: While Loop

**TAC:**
```
0  label_begin     L0
1  ifFalse   i     L1
2  +         sum i T0
3  =         T0    sum
4  goto            L0
5  label_end       L1
```

**Assembly:**
```assembly
L0:
    MOV AX, [i]
    CMP AX, 0
    JE L1
    
    MOV BX, [sum]
    ADD BX, AX
    MOV [sum], BX
    
    JMP L0
L1:
    ; End of loop
```

### Example 3: Unary Minus

**TAC:**
```
0  uminus  b       T0
1  *       a  T0   T1
```

**Assembly:**
```assembly
    MOV AX, [b]
    NEG AX            ; T0 = -b
    MOV BX, [a]
    IMUL BX, AX       ; T1 = a * (-b)
```

## Building and Running

### Build

```bash
cd Assignment-06-TCG
make clean
make
```

This creates:
- `icg_compiler`: Generates TAC from C source
- `codegen`: Generates assembly from TAC

### Run Complete Pipeline

```bash
# Generate TAC from C source
./icg_compiler < test_comprehensive.c

# Generate assembly from TAC
./codegen three_address_code.txt

# View generated assembly
cat assembly_code.asm
```

### Run with Pre-generated TAC

```bash
./codegen test1_tac.txt    # Assignment statements
./codegen test2_tac.txt    # Arithmetic
./codegen test3_tac.txt    # If statement
./codegen test4_tac.txt    # While loop
```

### Make Targets

```bash
make pipeline             # Full C → TAC → Assembly
make test_all            # Run all TAC tests
make test_comprehensive  # Full pipeline test
```

## Generated Assembly Format

```assembly
; Assembly Code Generated from Three-Address Code
; Target Machine: 8086-compatible
; Registers: AX, BX, CX, DX

.MODEL SMALL
.STACK 100h

.DATA
    ; Variable declarations

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Generated instructions here
    
    MOV AH, 4Ch       ; DOS exit
    INT 21h
MAIN ENDP
END MAIN
```

## Optimizations Implemented

| Optimization | Description |
|-------------|-------------|
| **Register Reuse** | Reuse registers when variable already loaded |
| **Dead Variable Handling** | Don't spill dead variables |
| **Clean Register Preference** | Prefer spilling clean registers |
| **Temporary Priority** | Prefer spilling temporaries |
| **Operand Protection** | Never spill current operands |

## Test Files

### TAC Test Files
| File | Tests |
|------|-------|
| `test1_tac.txt` | Assignment statements |
| `test2_tac.txt` | Arithmetic expressions |
| `test3_tac.txt` | If statement |
| `test4_tac.txt` | While loop |
| `test5_tac.txt` | Comprehensive |

### C Source Test Files
| File | Tests |
|------|-------|
| `test_assignment.c` | Simple assignments |
| `test_expression.c` | Arithmetic |
| `test_if.c` | If statements |
| `test_while.c` | While loops |
| `test_comprehensive.c` | All constructs |

## Files

| File | Description |
|------|-------------|
| `codegen.h` | Code generator header |
| `codegen.c` | Register allocation & code gen |
| `main.c` | Code generator driver |
| `icg.h/c` | ICG module |
| `parse.y` | YACC parser |
| `lex.l` | Flex lexer |
| `Makefile` | Build configuration |

## Learning Outcomes

After completing this assignment, you will understand:
- ✅ Register allocation algorithms
- ✅ Address and register descriptors
- ✅ Code generation strategies
- ✅ Spilling and register reuse
- ✅ Assembly code generation
- ✅ Complete compilation pipeline

## References

1. **Compilers: Principles, Techniques, and Tools** (Dragon Book)
   - Chapter 8: Code Generation
   - Section 8.6: A Simple Code Generator (pp 535-541)
   - Section 8.8: Register Allocation

2. **8086 Instruction Set Reference**

## Related Pages

- [Assignment 05: Intermediate Code Generation](Assignment-05-ICG)
- [Theory Index](Theory-Index)
- [Home](Home)

---

**Previous:** [Assignment 05: Intermediate Code Generation](Assignment-05-ICG)
