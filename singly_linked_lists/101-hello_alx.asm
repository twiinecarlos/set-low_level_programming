global main
extern printf

section .data
    msg db "Hello, ALX", 10, 0

section .text
main:
    ; align stack for 64-bit ABI
    sub rsp, 8

    ; call printf(msg)
    mov rdi, msg
    xor rax, rax
    call printf

    ; restore stack and return
    add rsp, 8
    mov eax, 0
    ret
