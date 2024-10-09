[BITS 16]

ORG 0x7C00

BOOT:
    CLI ; Prevent all IRQs.
    HLT ; Wait for next IRQ.

; Assembler replaces $$ with an address of first instruction.
; Assembler replaces $ with an address of current instruction.
; ($ - $$) is to be 2 bits.
; This results in putting 508 bits of zeros.
TIMES 510 - ($ - $$) DB 0

DW 0xAA55 ; Put word size data (2 bytes).
