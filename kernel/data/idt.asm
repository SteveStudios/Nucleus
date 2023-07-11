; idt.asm - Interrupt descriptor table exception catcher/finder
; Created 2023/7/11 by Stephen Byrne

; SEE: https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh

global isr0
global isr1
global isr31

; Division by Zero
isr0:
    push byte 0
    push byte 0
    jmp catch_e

; Debug Error
isr1:
    push byte 0
    push byte 1
    jmp catch_e

; Stack Fault
isr12:
    push byte 12
    jmp catch_e

; Reserved
isr31:
    push byte 0
    push byte 31
    jmp catch_e

[extern print_e]

catch_e:
    pusha

    mov ax, ds
    push eax

    ; Add parameters to print_e, which we are about to call
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp

    ; Call it, using the parameters we have just pushed
    call print_e

    pop eax

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8
    iret