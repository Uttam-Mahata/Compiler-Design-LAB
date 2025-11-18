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
; Total Instructions: 10


; = 0, , sum
    MOV AX, 0        ; Load constant 0

; = 5, , i
    MOV BX, 5        ; Load constant 5

; label_begin , , L0
L0:

; ifFalse i, , L1
    CMP BX, 0         ; Compare i with 0
    JE L1             ; Jump to L1 if equal (false)

; + sum, i, T0
    MOV CX, AX        ; Copy operand
    ADD CX, BX        ; CX = AX + BX

; = T0, , sum
    MOV AX, CX        ; sum = T0

; - i, 1, T1
    MOV DX, 1        ; Load constant 1
    MOV [T0], CX      ; Store CX to T0
    MOV CX, BX        ; Copy operand
    SUB CX, DX        ; CX = BX - DX

; = T1, , i
    MOV BX, CX        ; i = T1

; goto , , L0
    JMP L0            ; Unconditional jump to L0

; label_end , , L1
L1:

; Store all modified values back to memory
    MOV [sum], AX      ; Store AX to sum
    MOV [i], BX      ; Store BX to i
    MOV [T1], CX      ; Store CX to T1

    ; Program termination
    MOV AH, 4Ch      ; DOS exit function
    INT 21h          ; Call DOS interrupt
MAIN ENDP
END MAIN
