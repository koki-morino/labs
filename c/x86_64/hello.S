.text
    .global main
main:
    mov $1, %rax # write()
    mov $1, %rdi # stdout
    lea message(%rip), %rsi # What to print
    mov $14, %rdx # Length of message
    syscall

    mov $60, %rax #exit()
    xor %rdi, %rdi
    syscall

.data
message:
    .ascii "Hello, world!\n" # Fourteen bytes
