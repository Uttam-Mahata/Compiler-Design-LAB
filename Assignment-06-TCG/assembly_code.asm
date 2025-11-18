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
; Total Instructions: 14


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

; - c, 5, T2
    MOV [T1], CX      ; Store CX to T1
    MOV CX, 5        ; Load constant 5
    MOV [a], AX      ; Store AX to a
    MOV AX, DX        ; Copy operand
    SUB AX, CX        ; AX = DX - CX

; = T2, , result
    MOV CX, AX        ; result = T2

; = 0, , result
    MOV CX, 0        ; Load constant 0

; - a, 1, T3
    MOV [T2], AX      ; Store AX to T2
    MOV AX, [a]      ; Load a into AX
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

; + result, b, T5
    MOV [T4], CX      ; Store CX to T4
    MOV CX, [b]      ; Load b into CX
    MOV [a], AX      ; Store AX to a
    MOV AX, BX        ; Copy operand
    ADD AX, CX        ; AX = BX + CX

; = T5, , c
    MOV DX, AX        ; c = T5

; Store all modified values back to memory
    MOV [T5], AX      ; Store AX to T5
    MOV [result], BX      ; Store BX to result
    MOV [c], DX      ; Store DX to c

    ; Program termination
    MOV AH, 4Ch      ; DOS exit function
    INT 21h          ; Call DOS interrupt
MAIN ENDP
END MAIN
