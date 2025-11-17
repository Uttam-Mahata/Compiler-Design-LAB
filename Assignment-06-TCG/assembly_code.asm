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
; Total Instructions: 7


; = 10, , a
    MOV AX, 10        ; Load constant 10

; = 20, , b
    MOV BX, 20        ; Load constant 20

; uminus b, , T0
    MOV CX, BX        ; Copy operand
    NEG CX            ; T0 = -b

; = 5, , c
    MOV DX, 5        ; Load constant 5

; * a, T0, T1
    MOV [b], BX      ; Store BX to b
    MOV BX, AX        ; Copy operand
    IMUL BX, CX       ; BX = AX * CX

; + T1, c, T2
    MOV [T0], CX      ; Store CX to T0
    MOV CX, BX        ; Copy operand
    ADD CX, DX        ; CX = BX + DX

; = T2, , d
    MOV [T1], BX      ; Store BX to T1
    MOV BX, CX        ; d = T2

; Store all modified values back to memory
    MOV [a], AX      ; Store AX to a
    MOV [d], BX      ; Store BX to d
    MOV [T2], CX      ; Store CX to T2
    MOV [c], DX      ; Store DX to c

    ; Program termination
    MOV AH, 4Ch      ; DOS exit function
    INT 21h          ; Call DOS interrupt
MAIN ENDP
END MAIN
