global main
extern printf

section .data
    msg db "Hello, Holberton", 10, 0

section .text
main:
    sub rsp, 8

    mov rdi, msg
    xor rax, rax
    call printf

    add rsp, 8
    mov eax, 0
    ret
