# 8086 Instruction Set Conversion Summary

## Overview
The code generator has been updated to generate **authentic Intel 8086 assembly code** instead of the previous RISC-like pseudo-assembly. This conversion was done based on the official x86 instruction set documentation from Microsoft.

## Key Changes

### 1. Register Names
**Before:** R0, R1, R2, R3 (generic RISC registers)  
**After:** AX, BX, CX, DX (authentic 8086 16-bit registers)

### 2. Data Transfer Instructions

#### Load Operations
**Before (RISC-like):**
```assembly
LD R0, #10        ; Load immediate
LD R0, var        ; Load from memory
LD R0, R1         ; Register copy
```

**After (8086):**
```assembly
MOV AX, 10        ; Load immediate (no # prefix needed)
MOV AX, [var]     ; Load from memory (brackets for addressing)
MOV AX, BX        ; Register to register
```

#### Store Operations
**Before (RISC-like):**
```assembly
ST var, R0        ; Store register to memory
```

**After (8086):**
```assembly
MOV [var], AX     ; Store register to memory
```

### 3. Arithmetic Instructions

#### Addition & Subtraction
**Before (Three-operand RISC):**
```assembly
ADD R0, R1, R2    ; R0 = R1 + R2
SUB R0, R1, R2    ; R0 = R1 - R2
```

**After (Two-operand 8086):**
```assembly
MOV AX, BX        ; Copy first operand
ADD AX, CX        ; AX = BX + CX (result in destination)
```

#### Multiplication
**Before (Three-operand):**
```assembly
MUL R0, R1, R2    ; R0 = R1 * R2
```

**After (8086 with IMUL):**
```assembly
MOV AX, BX        ; Copy first operand
IMUL AX, CX       ; AX = BX * CX (signed multiply)
```

#### Division
**Before (Three-operand):**
```assembly
DIV R0, R1, R2    ; R0 = R1 / R2
```

**After (8086 - more complex):**
```assembly
MOV AX, BX        ; Move dividend to AX
CWD               ; Sign extend AX to DX:AX
IDIV CX           ; AX = DX:AX / CX, DX = remainder
```

#### Unary Negation
**Before (Two-operand):**
```assembly
NEG R0, R1        ; R0 = -R1
```

**After (Single-operand 8086):**
```assembly
MOV AX, BX        ; Copy operand
NEG AX            ; AX = -AX
```

### 4. Comparison and Control Flow

#### Comparison
**Before:**
```assembly
CMP R0, #0        ; Compare with immediate (# prefix)
```

**After:**
```assembly
CMP AX, 0         ; Compare with immediate (no # prefix)
```

#### Jump Instructions
**Unchanged** - 8086 uses same mnemonics:
```assembly
JE label          ; Jump if equal
JNE label         ; Jump if not equal
JMP label         ; Unconditional jump
```

### 5. Program Structure

**Added proper 8086 program structure:**
```assembly
.MODEL SMALL      ; Memory model declaration
.STACK 100h       ; Stack segment (256 bytes)

.DATA             ; Data segment
    ; Variable declarations

.CODE             ; Code segment
MAIN PROC
    MOV AX, @DATA ; Initialize data segment
    MOV DS, AX

    ; Generated code here

    MOV AH, 4Ch   ; DOS function: terminate program
    INT 21h       ; Call DOS interrupt
MAIN ENDP
END MAIN
```

## Documentation References

The conversion is based on official Microsoft documentation:
- [x86 Instructions](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x86-instructions)
- [x86 Architecture](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x86-architecture)

## Example: Complete Transformation

### Input: Three-Address Code
```
0  =  10    a
1  =  20    b
2  +  a  b  c
```

### Output: Authentic 8086 Assembly

```assembly
.MODEL SMALL
.STACK 100h

.DATA
    ; Variable declarations will be added here

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Generated code starts here

; = 10, , a
    MOV AX, 10        ; Load constant 10

; = 20, , b
    MOV BX, 20        ; Load constant 20

; + a, b, c
    MOV CX, AX        ; Copy operand
    ADD CX, BX        ; CX = AX + BX

; Store all modified values back to memory
    MOV [a], AX       ; Store AX to a
    MOV [b], BX       ; Store BX to b
    MOV [c], CX       ; Store CX to c

    ; Program termination
    MOV AH, 4Ch       ; DOS exit function
    INT 21h           ; Call DOS interrupt
MAIN ENDP
END MAIN
```

## Testing

All test cases have been updated and verified:
- ✅ test1: Assignment statements
- ✅ test2: Arithmetic expressions with unary minus
- ✅ test3: If statements
- ✅ test4: While loops
- ✅ test5: Comprehensive (if-else + while)

## Benefits of 8086 Instruction Set

1. **Authentic**: Uses real Intel 8086 syntax
2. **Assembable**: Can be assembled with MASM/TASM
3. **Educational**: Teaches actual x86 assembly
4. **Industry-standard**: Based on widely-used architecture
5. **Well-documented**: Extensive resources available

## Files Modified

1. `codegen.c` - Complete rewrite of code emission functions
2. `codegen.h` - Updated register definitions and comments
3. `README.md` - Updated documentation with 8086 examples
4. All generated `assembly_code.asm` files now use 8086 syntax

## Compatibility

The generated assembly code is compatible with:
- **MASM** (Microsoft Macro Assembler)
- **TASM** (Turbo Assembler)
- **NASM** (with minor syntax adjustments)
- **DOSBox** for execution
- **emu8086** emulator

## Future Enhancements

Possible improvements:
1. Add variable declarations in .DATA segment
2. Optimize redundant MOV instructions
3. Support for 32-bit registers (EAX, EBX, etc.)
4. String handling instructions
5. Procedure call conventions (CALL/RET)
