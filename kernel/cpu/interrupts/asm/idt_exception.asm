; idt_exception.asm Provided the IDT handler (See cpu/interrupts/idt.c) with the required information to generate a meaningful error message.
; Created 2023/7/20 by Stephen Byrne

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr15
global isr16
global isr17
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

[extern on_exception]
[extern reload_segment_registers]

; 0: Divide By Zero
isr0:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 0
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 1: Debug
isr1:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 1
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 2: Non Maskable Interrupt
isr2:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 2
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 3: Int 3
isr3:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 3
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 4: INTO
isr4:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 4
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 5: Out of Bounds
isr5:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 5
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 6: Invalid Opcode
isr6:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 6
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 7: Coprocessor Not Available
isr7:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 7
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 8: Double Fault
isr8:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 8
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 9: Coprocessor Segment Overrun
isr9:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 9
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 10: Bad TSS
isr10:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 10
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 11: Segment Not Present
isr11:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 11
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 12: Stack Fault
isr12:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 12
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 13: General Protection Fault
isr13:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 13
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 14: Page Fault
isr14:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 14
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 15: Reserved
isr15:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 15
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 16: Floating Point
isr16:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 16
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 17: Alignment Check
isr17:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 17
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; 18: Machine Check
isr18:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 18
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

; --Everything below here is reserved--

isr19:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 19
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr20:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 20
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr21:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 21
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq
    
isr22:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 22
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr23:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 23
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr24:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 24
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr25:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 25
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr26:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 26
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr27:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 27
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr28:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 28
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr29:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 29
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr30:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 30
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq

isr31:
    call reload_segment_registers

    push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

    mov rsi, 31
    call on_exception

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

    iretq