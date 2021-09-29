.intel_syntax noprefix

.section .data
    array: .8byte 7,2,5,4,3,6,1
    tamArray: .8byte 7

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
main:
    push rbp
    
    lea rdi, [rip+array]
    mov rsi, [rip+tamArray]
    mov rdx, 0x8
    lea rcx, [rip+compare]
    xor rax, rax
    call qsort

    pop rbp
