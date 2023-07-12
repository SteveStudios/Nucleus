; idt_asm.asm - Interrupt descriptor table exception catcher/finder
; Created 2023/7/11 by Stephen Byrne

global isr0
global isr1
global isr31

; --Exceptions--
; Division by Zero
isr0:
    PUSH byte 0
    PUSH byte 0
    jmp catch_e

; Debug Error
isr1:
    PUSH byte 0
    PUSH byte 1
    jmp catch_e

; Stack Fault
isr12:
    PUSH byte 12
    jmp catch_e

; Reserved
isr31:
    PUSH byte 0
    PUSH byte 31
    jmp catch_e

[extern print_e]

; Exception handler
catch_e:
    PUSH ax
    PUSH bx
    PUSH cx
    PUSH dx

    mov ax, ds
    PUSH rax

    ; Add parameters to print_e, which we are about to call
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    PUSH rsp

    ; Call it, using the parameters we have just pushed
    call print_e

    POP rax

    POP rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    PUSH ax
    PUSH bx
    PUSH cx
    PUSH dx

    add esp, 8
    iret

; IRQ Handler
global irq0
global irq7
global irq8
global irq15

irq0:
    push byte 0
    push byte 32
    jmp irq_e

irq7:
    push byte 7
    push byte 39
    jmp irq_e

irq8:
    push byte 8
    push byte 40
    jmp irq_e

irq15:
    push byte 15
    push byte 47
    jmp irq_e


[extern irq_handler]

; IRQ Handler
irq_e:
    PUSH ax
    PUSH bx
    PUSH cx
    PUSH dx

    mov ax, ds
    PUSH rax

    ; Add parameters to print_e, which we are about to call
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    PUSH rsp

    ; Call it, using the parameters we have just pushed
    call irq_handler

    POP rbx

    POP rax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    PUSH ax
    PUSH bx
    PUSH cx
    PUSH dx

    add esp, 8
    iret