; Assembly Code Generated from Three-Address Code
; Target Machine: RISC-like with 4 registers (R0-R3)
; Instruction Set: 8085/8086 compatible


; Three-Address Code to Assembly Translation
; Total Instructions: 20


; = 10, , a
    LD R0, #10        ; Load constant 10

; = 20, , b
    LD R1, #20        ; Load constant 20

; * b, 2, T0
    LD R2, #2        ; Load constant 2
    * R3, R1, R2      ; R3 = R1 * R2

; + a, T0, T1
    + R2, R0, R3      ; R2 = R0 + R3

; = T1, , c
    ST T0, R3         ; Store R3 to T0
    LD R3, R2         ; c = T1

; ifFalse c, , L0
    CMP R3, #0        ; Compare c with 0
    JE L0             ; Jump to L0 if equal (false)

; - c, 5, T2
    ST T1, R2         ; Store R2 to T1
    LD R2, #5        ; Load constant 5
    ST a, R0         ; Store R0 to a
    - R0, R3, R2      ; R0 = R3 - R2

; = T2, , result
    LD R2, R0         ; result = T2

; goto , , L1
    JMP L1            ; Unconditional jump to L1

; label_end , , L0
L0:

; = 0, , result
    LD R2, #0        ; Load constant 0

; label_end , , L1
L1:

; label_begin , , L2
L2:

; ifFalse a, , L3
    ST T2, R0         ; Store R0 to T2
    LD R0, a         ; Load a into R0
    CMP R0, #0        ; Compare a with 0
    JE L3             ; Jump to L3 if equal (false)

; - a, 1, T3
    ST b, R1         ; Store R1 to b
    LD R1, #1        ; Load constant 1
    ST result, R2         ; Store R2 to result
    - R2, R0, R1      ; R2 = R0 - R1

; = T3, , a
    LD R0, R2         ; a = T3

; + result, a, T4
    LD R1, result         ; Load result into R1
    ST T3, R2         ; Store R2 to T3
    + R2, R1, R0      ; R2 = R1 + R0

; = T4, , result
    LD R1, R2         ; result = T4

; goto , , L2
    JMP L2            ; Unconditional jump to L2

; label_end , , L3
L3:

; Store all modified values back to memory
    ST a, R0         ; Store R0 to a
    ST result, R1         ; Store R1 to result
    ST T4, R2         ; Store R2 to T4
    ST c, R3         ; Store R3 to c

HALT
