.intel_syntax noprefix
.section .text
.global main

main:
    push rbp
    mov rsp, rbp
    
    mov rax, 0x0
    mov rdi, 0x0
    lea rsi, [rip+numOne]
    mov rdx, 0xa
    syscall

    mov rax, 0x1
    mov rdi, 0x1
    lea rsi, [rip+numOne]
    mov rdx, 0xa
    syscall

    mov rax, 0x3c
    mov rdi, 0x0
    syscall

    mov rbp, rsp
    pop rbp
    ret

.section .data
    numOne: .space 4
    numTwo: .space 4
