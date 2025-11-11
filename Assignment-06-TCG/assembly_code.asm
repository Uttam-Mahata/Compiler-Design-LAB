; Assembly Code Generated from Three-Address Code
; Target Architecture: Intel 8086
; Instruction Set: x86 (8086 compatible)
; Registers used: AX, BX, CX, DX (16-bit general purpose)

.MODEL SMALL
.STACK 100h

.DATA
    ; Variable declarations will be added here

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Generated code starts here

; Three-Address Code to Assembly Translation
; Total Instructions: 20


; = 10, , a
    MOV AX, 10        ; Load constant 10

; = 20, , b
    MOV BX, 20        ; Load constant 20

; * b, 2, T0
    MOV CX, 2        ; Load constant 2
    MOV DX, BX        ; Copy operand
    IMUL DX, CX       ; DX = BX * CX

; + a, T0, T1
    MOV CX, AX        ; Copy operand
    ADD CX, DX        ; CX = AX + DX

; = T1, , c
    MOV [T0], DX      ; Store DX to T0
    MOV DX, CX        ; c = T1

; ifFalse c, , L0
    CMP DX, 0         ; Compare c with 0
    JE L0             ; Jump to L0 if equal (false)

; - c, 5, T2
    MOV [T1], CX      ; Store CX to T1
    MOV CX, 5        ; Load constant 5
    MOV [a], AX      ; Store AX to a
    MOV AX, DX        ; Copy operand
    SUB AX, CX        ; AX = DX - CX

; = T2, , result
    MOV CX, AX        ; result = T2

; goto , , L1
    JMP L1            ; Unconditional jump to L1

; label_end , , L0
L0:

; = 0, , result
    MOV CX, 0        ; Load constant 0

; label_end , , L1
L1:

; label_begin , , L2
L2:

; ifFalse a, , L3
    MOV [T2], AX      ; Store AX to T2
    MOV AX, [a]      ; Load a into AX
    CMP AX, 0         ; Compare a with 0
    JE L3             ; Jump to L3 if equal (false)

; - a, 1, T3
    MOV [b], BX      ; Store BX to b
    MOV BX, 1        ; Load constant 1
    MOV [result], CX      ; Store CX to result
    MOV CX, AX        ; Copy operand
    SUB CX, BX        ; CX = AX - BX

; = T3, , a
    MOV AX, CX        ; a = T3

; + result, a, T4
    MOV BX, [result]      ; Load result into BX
    MOV [T3], CX      ; Store CX to T3
    MOV CX, BX        ; Copy operand
    ADD CX, AX        ; CX = BX + AX

; = T4, , result
    MOV BX, CX        ; result = T4

; goto , , L2
    JMP L2            ; Unconditional jump to L2

; label_end , , L3
L3:

; Store all modified values back to memory
    MOV [a], AX      ; Store AX to a
    MOV [result], BX      ; Store BX to result
    MOV [T4], CX      ; Store CX to T4
    MOV [c], DX      ; Store DX to c

    ; Program termination
    MOV AH, 4Ch      ; DOS exit function
    INT 21h          ; Call DOS interrupt
MAIN ENDP
END MAIN
