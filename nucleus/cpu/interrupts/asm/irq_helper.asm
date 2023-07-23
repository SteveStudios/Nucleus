; irq_helper.asm - IRQ handler helper
; Created 2023/7/21 by Stephen Byrne

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

[extern handle_interrupt]

irq0:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 0
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq1:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 1
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq2:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 2
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq3:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 3
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq4:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 4
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq5:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 5
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq6:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 6
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq7:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 7
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq8:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 8
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq9:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 9
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq10:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 10
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq11:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 11
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq12:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 12
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq13:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 13
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq14:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 14
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq

irq15:
	push ax
    push cx
    push dx
    push bx
    push bp
    push si
    push di

	mov rsi, 15
	call handle_interrupt

    pop ax
    pop cx
    pop dx
    pop bx
    pop bp
    pop si
    pop di

	iretq