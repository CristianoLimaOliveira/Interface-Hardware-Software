.intel_syntax noprefix

.section .data
    numOne: .space 4
    numTwo: .space 4

.section .text
.global main

main:
    mov rax, 0x0 # é para entrada de dados
    mov rdi, 0x0 # é o descritor de arquivo de entrada básico
    lea rsi, [rip+numOne] # rsi passa a apontar para o endereço de memória da variável
    mov rdx, 0x4 # quantos bytes foram alocados para a variável numOne
    syscall # chamada de sistema para alterar o controle de fluxo

    mov rax, 0x0 # é para entrada de dados
    mov rdi, 0x0 # é o descritor de arquivo de entrada básico
    lea rsi, [rip+numTwo] # rsi passa a apontar para o endereço de memória da variável
    mov rdx, 0x4 # quantos bytes foram alocados para a variável numTwo
    syscall # chamada de sistema para alterar o controle de fluxo

    mov rax, 0x1 # é para escrever
    mov rdi, 0x1 # é um descritor básico de gravação de arquivo
    lea rsi, [rip+numOne] # rsi passa a apontar para o endereço de memória da variável
    mov rdx, 0x4 # quantos bytes foram alocados para a variável que terá o conteúdo impresso na tela
    syscall # chamada de sistema para alterar o controle de fluxo

    mov rax, 0x3c # 60 é para indicar que é para sair
    mov rdi, 0x0 # retornar 0
    syscall # chamada de sistema para alterar o controle de fluxo
