; Multiboot-compliant boot entry
section .multiboot
align 4
dd 0x1BADB002        ; magic
dd 0x0               ; flags
dd -(0x1BADB002 + 0x0) ; checksum

section .text
global _start
extern _kernel_main
_start:
    mov esp, stack_top
    call _kernel_main
    cli
.halt:
    hlt
    jmp .halt

section .bss
stack: resb 16384
stack_top: