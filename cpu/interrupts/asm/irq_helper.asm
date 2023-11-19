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
global software_interrupt

[extern handle_interrupt]
[extern syscall]

irq0:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 0
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq1:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 1
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq2:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 2
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq3:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 3
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq4:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 4
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq5:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 5
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq6:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 6
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq7:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 7
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq8:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 8
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq9:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 9
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq10:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 10
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq11:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 11
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq12:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 12
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq13:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 13
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq14:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 14
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

irq15:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

	mov rdi, 15
	call handle_interrupt

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq

software_interrupt:
	push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

    mov rdi, rax
    mov rsi, rdi
    mov rdx, rsi
    mov r10, rdx
    mov r8, r9

	call syscall

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    iretq