.intel_syntax noprefix

.section .data
    hello: .string "Hello world\n"

.section .text
.global main

main:
    mov rax, 0x1 # é para escrever
    mov rdi, 0x1 # é um descritor básico de gravação de arquivo
    lea rsi, [rip+hello] # rsi passa a apontar para o endereço que contém a string "Hello world\n"
    mov rdx, 0xd # o tamanho da string, que nesse caso tem 13 bytes.
    syscall # chamada de sistema para alterar o controle de fluxo

    mov rax, 0x3c # 60 é para indicar que é para sair
    mov rdi, 0x0 # retornar 0
    syscall
