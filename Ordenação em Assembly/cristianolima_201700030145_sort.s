.intel_syntax noprefix

.section .data
    ptrFileNameInput: .space 8
    ptrFileNameOutput: .space 8
    ptrFileInput: .space 8
    ptrFileOutput: .space 8
    countVector: .8byte 8
    countSizeVector: .8byte 8
    index: .8byte 0

.section .rodata
    formatacao:
        .asciz "%s\n"
    formatacao_read:
        .string "%ld"
    formatacao_write:
        .string "%ld\n"
    formatacao_write_index:
        .string "[%ld] "
    formatacao_write_vector:
        .string "%ld "
    formatacao_write_end_vector:
        .string "%ld\n"
    arquivo_modo_r:
        .string "r"
    arquivo_modo_w:
        .string "w"

.section .text
.global main

compare:
    mov rcx, [rdi]
    mov rdx, [rsi]

    cmp rcx, rdx
    jl if_less
    cmp rcx, rdx
    jg if_greater
if_equal:
    mov rax, 0
    ret
if_less:
    mov rax, -1
    ret
if_greater:
    mov rax, 1
    ret
func_qsort:    
    mov rdi, r14
    mov rsi, [rip+countSizeVector]
    mov rdx, 0x8
    lea rcx, [rip+compare]
    xor rax, rax
    call qsort
    mov rbx, 0x0
    ret

write_elements_file_output_format_index:
    mov rdi, [rip+ptrFileOutput]
    lea rsi, [rip+formatacao_write_index]
    mov rdx, [rip+index]
    xor rax, rax
    call fprintf

    add rbx, 1
    cmp rbx, [rip+countSizeVector]
    jnz write_elements_file_output
    ret
write_elements_file_output_format_vector:
    mov rdi, [rip+ptrFileOutput]
    lea rsi, [rip+formatacao_write_vector]
    mov rdx, [r14+8*rbx]
    xor rax, rax
    call fprintf

    add rbx, 1
    cmp rbx, [rip+countSizeVector]
    jnz write_elements_file_output
    ret
write_elements_file_output_format_end_vector:
    mov rdi, [rip+ptrFileOutput]
    lea rsi, [rip+formatacao_write_end_vector]
    mov rdx, [r14+8*rbx]
    xor rax, rax
    call fprintf

    add rbx, 1
    cmp rbx, [rip+countSizeVector]
    jnz write_elements_file_output
    ret

write_elements_file_output:
    cmp rbx, r15
    jl write_elements_file_output_format_vector
    cmp rbx, r15
    jz write_elements_file_output_format_end_vector
    ret

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
    lea rsi, [rip+arquivo_modo_w]
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
    mov rdi, [rip+ptrFileOutput]
    lea rsi, [rip+formatacao_write_index]
    mov rdx, [rip+index]
    xor rax, rax
    call fprintf
    mov rdi, [rip+ptrFileInput]
    lea rsi, [rip+formatacao_read]
    lea rdx, [rip+countSizeVector]
    xor rax, rax
    call fscanf
    lea rdi, [rip+formatacao_write]
    mov rsi, [rip+countSizeVector]
    xor rax, rax
    call printf
    mov rbx, 0x0
    mov r13, [rip+countSizeVector]
    imul r13, 8
    mov rdi, r13
    xor rax, rax
    call malloc
    mov r14, rax

load_elements_array:
    mov rdi, [rip+ptrFileInput]
    lea rsi, [rip+formatacao_read]
    lea rdx, [r14+8*rbx]
    xor rax, rax
    call fscanf
    #mov rdi, [rip+ptrFileOutput]
    #lea rsi, [rip+formatacao_write]
    #mov rdx, [r14+8*rbx]
    #xor rax, rax
    #call fprintf
    add rbx, 1
    cmp rbx, [rip+countSizeVector]
    jnz load_elements_array
    call func_qsort
    
free_memory:
    mov rbx, 0x0
    mov r15, [rip+countSizeVector]
    sub r15, 1
    call write_elements_file_output
    mov rdi, r14
    xor rax, rax
    call free

    mov r12, [rip+index]
    add r12,1
    mov [rip+index], r12
    mov r12, [rip+countVector]
    sub r12,1
    mov [rip+countVector], r12
    cmp r12,0
    jnz loop_order_all_vector

    pop rbp
