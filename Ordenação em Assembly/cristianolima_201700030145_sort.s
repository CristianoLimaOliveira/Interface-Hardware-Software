.intel_syntax noprefix

.section .data
    ptrFileNameInput: .space 8
    ptrFileNameOutput: .space 8
    ptrFileInput: .space 8
    ptrFileOutput: .space 8
    countVector: .8byte 8
    countSizeVector: .8byte 8
    dados: .8byte 8

.section .text
.global main

formatacao:
    .asciz "%s\n"

formatacao_read:
    .string "%ld"

formatacao_write:
    .string "%ld\n"

arquivo_modo_r:
    .string "r"

arquivo_modo_a:
    .string "a"

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
    lea rsi, [rip+arquivo_modo_r]
    xor rax, rax
    call fopen

    mov [rip+ptrFileInput], rax

    mov rdi, [rip+ptrFileNameOutput]
    lea rsi, [rip+arquivo_modo_a]
    xor rax, rax
    call fopen

    mov [rip+ptrFileOutput], rax

    mov rdi, [rip+ptrFileInput]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+countVector]
    xor rax, rax
    call fscanf

    lea rdi, [rip+formatacao_write]
    mov rsi, [rip+countVector]
    xor rax, rax
    call printf

loop_order_all_vector:
    mov rdi, [rip+ptrFileInput]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+countSizeVector]
    xor rax, rax
    call fscanf
    lea rdi, [rip+formatacao_write]
    mov rsi, [rip+countSizeVector]
    xor rax, rax
    call printf
    mov rbx, [rip+countSizeVector]

load_elements_array:
    mov rdi, [rip+ptrFileInput]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+dados]
    xor rax, rax
    call fscanf
    mov rdi, [rip+ptrFileOutput]
    lea rsi, [rip+formatacao_write]
    mov rdx, [rip+dados]
    xor rax, rax
    call fprintf
    sub rbx, 1
    cmp rbx, 0
    jnz load_elements_array
    
    mov r12, [rip+countVector]
    sub r12,1
    mov [rip+countVector], r12
    cmp r12,0
    jnz loop_order_all_vector

#write_elements_file_output:
    #mov r12, rbx
    #imul r12, 8
    #sub rsp, r12
    #mov rdi, [rip+ptrFileOutput]
    #lea rsi, [rip+formatacao]
    #mov rdx, [rsp]
    #xor rax, rax
    #call fprintf
    #add rsp, r12
    #sub rbx, 1
    #cmp rbx, 0
    #jnz write_elements_file_output
    #call loop_order_all_vector

    pop rbp
