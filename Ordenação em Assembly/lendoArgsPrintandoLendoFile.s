.intel_syntax noprefix

.section .data
    dados: .space 5
    dadox: .space 5

.section .text
.global main

formatacao:
    .asciz "%s\n"

formatacao_read:
    .asciz "%s"

arquivo_modo:
    .asciz "r"

main:
    push rbp
    mov     r12, rsi    # O rsi contém o endereço da primeira posição de um array de endereços na memória, onde cada endereço aponta para um argumento. Estou passando esse endereço para o registrador r12.

    lea rdi, [rip+formatacao]   # Faço rdi apontar para o endereço de memória da label que faz a formatação para printar na tela, equivalente a "%s", "%d" "Número é: %d", ... da chamada da função printf em C.
    mov rsi, [r12+8]    # O registrador rsi recebe o endereço de memória apontado por r12 de onde está o primeiro argumento (após o nome do arquivo ./lendoArgs...), para então a função printf conseguir pegar o nome do argumento que seria o nome do arquivo que devemos fazer a leitura.
    xor rax, rax
    call printf

    mov rdi, [r12+16]   # O registrador rdi recebe o endereço de memória apontado por r12 de onde está o segundo argumento (após o nome do arquivo ./lendoArgs...), para então a função puts conseguir pegar o nome do argumento.
    xor rax, rax
    call puts

    mov rdi, [r12+8]    # O registrador rdi recebe o endereço de memória apontado por r12 de onde está o primeiro argumento (após o nome do arquivo ./lendoArgs...), para então a função fopen conseguir pegar o nome do argumento que seria o nome do arquivo que devemos fazer a leitura.
    lea rsi, [rip+arquivo_modo] # Faço rsi apontar para o endereço de memória da label que faz a formatação para identificar o modo que quero abrir o arquivo, equivalente a "r", "a", "w", ... da chamada da função fopen em C.
    xor rax, rax
    call fopen

    mov r13, rax    # Salvo no registrador r13 o file descriptor retornado da chamada da função fopen através do registrador rax

    mov rdi, r13    # Uso o file descriptor para fazer a leitura do arquivo usando a função fscanf
    lea rsi, [rip+formatacao_read]  # Faço rsi apontar para o endereço de memória da label que faz a formatação para ler os dados do arquivo, equivalente a "%s", "%d" "%f", ... da chamada da função fscanf em C.
    lea rdx, [rip+dados]    # Faço rdx apontar para o endereço de memória da variável que eu quero armazenar a informação lida do arquivo.
    xor rax, rax
    call fscanf

    lea rdi, [rip+dados]    # O registrador rdi recebe o endereço de memória apontado por [rip+dados] de onde está armazenado o dado dentro da variável dados.
    xor rax, rax
    call puts

    mov rdi, r13    # Uso o file descriptor para fazer a leitura do próximo dado do arquivo usando a função fscanf
    lea rsi, [rip+formatacao_read]  # Faço rsi apontar para o endereço de memória da label que faz a formatação para ler os dados do arquivo, equivalente a "%s", "%d" "%f", ... da chamada da função fscanf em C.
    lea rdx, [rip+dadox]    # Faço rdx apontar para o endereço de memória da variável que eu quero armazenar a segunda informação lida do arquivo.
    xor rax, rax
    call fscanf

    lea rdi, [rip+dadox]    # O registrador rdi recebe o endereço de memória apontado por [rip+dadox] de onde está armazenado o dado dentro da variável dadox.
    xor rax, rax
    call puts

    pop rbp
