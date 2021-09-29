.intel_syntax noprefix

.section .data
    ptrFileNameInput: .space 8
    ptrFileNameOutput: .space 8
    ptrFile: .space 8
    dados: .space 8
    dadox: .space 8

.section .text
.global main

formatacao:
    .asciz "%s\n"

formatacao_read:
    .string "%s"

arquivo_modo:
    .string "r"

main:
    push rbp
    
    mov r12, [rsi+8]
    mov r13, [rsi+16]
    mov [rip+ptrFileNameInput], r12
    mov [rip+ptrFileNameOutput], r13

    lea rdi, [rip+formatacao]
    mov rsi, [rip+ptrFileNameInput]
    xor rax, rax
    call printf

    mov rdi, [rip+ptrFileNameOutput]
    xor rax, rax
    call puts

    mov rdi, [rip+ptrFileNameInput]
    lea rsi, [rip+arquivo_modo]
    xor rax, rax
    call fopen

    mov [rip+ptrFile], rax

    mov rdi, [rip+ptrFile]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+dados]
    xor rax, rax
    call fscanf

    lea rdi, [rip+dados]
    xor rax, rax
    call puts

    mov rdi, [rip+ptrFile]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+dadox]
    xor rax, rax
    call fscanf

    lea rdi, [rip+dadox]
    xor rax, rax
    call puts

    #mov rax, 0x2
    #mov rdi, [rip+ptrFileNameInput]
    #mov rsi, 0x0
    #mov rdx, 0777
    #syscall

    #mov r13, rax

    #sub rsp, 0x5

    #mov rdi, [rip+ptrFile]
    #lea rsi, [rip+formatacao_read]
    #lea rdx, [rsp]
    #xor rax, rax
    #call fscanf

    pop rbp
