.intel_syntax noprefix

.section .text
.global main
main:
	lea rdi, [rip+parameter]
	call puts
	xor rax, rax
	ret

.section .rodata
parameter:
	.string "Hello world from assembly!"
    