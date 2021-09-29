.intel_syntax noprefix

.section .data
    number: .int 60

.section .text
.global main

format:
    .asciz "%i\n" # https://cs.lmu.edu/~ray/notes/gasexamples/
exit:
    # https://stackoverflow-com.translate.goog/questions/53125140/how-to-rewrite-a-files-content-linux-x86-64-assembly-gas?_x_tr_sl=auto&_x_tr_tl=pt&_x_tr_hl=pt-BR&_x_tr_pto=nui,elem

    mov rax, 0x3c
    mov rdi, 0
    syscall
print_format:
    mov rax, 0x1
    lea rdi, [rip+format]
    mov rsi, r13
    xor rax, rax
    call printf
    ret
print:
    mov rax, 0x1
    mov rdi, 0x1
    mov rsi, r12
    mov rdx, 0x4
    syscall
    ret
reg_var:
    mov [rip+number], r13 # o valor 61 (0x3d) armazenado em r11 é atribuído para o local de memória destinada à variável file. Então a partir daí file vale 61
    lea r12, [rip+number] # é acessado o valor 61 (0x3d) da variável file através do seu endereço de memória armazenado em r12, e este valor é atribuído para r11
    call print_format
    call exit
soma:
    add r13, 0x1 # r11 que tem como valor atribuído 60, soma mais 1 e fica 61
    call reg_var
var_reg:
    lea r12, [rip+number] # r12 passa a apontar para o endereço de memória [rip+number]
    # mov r11, [r12] é acessado o valor 60 (0x3c) da variável file através do seu endereço de memória armazenado em r12, e este valor é atribuído para r11. OBS: Foi percebido que o registrador r11 é temporario, e nessa posição após o retorno do print ele simplesmente mudou de valor, apagando o valor 60 que estava armazenando. https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf
    mov r13, [r12]
    call print
    call soma
main:
    call var_reg
