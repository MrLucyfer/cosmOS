.set IRQ_BASE, 0x20

.section .text

.extern _ZN6Kernel16InterruptManager15HandleInterruptEhj

.macro HandleInterruptException num
.global _ZN6Kernel16InterruptManager19HandleInterruptException\num\()Ev
_ZN6Kernel16InterruptManager19HandleInterruptException\num\()Ev:
    movb $\num, (interruptNumber)
    jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN6Kernel16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN6Kernel16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptNumber)
    jmp int_bottom
.endm

HandleInterruptException 0x00
HandleInterruptException 0x01

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs

    pushl %esp
    push (interruptNumber)
    call _ZN6Kernel16InterruptManager15HandleInterruptEhj
    movl %eax, %esp

    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

.global _ZN6Kernel16InterruptManager22IgnoreInterruptRequestEv
_ZN6Kernel16InterruptManager22IgnoreInterruptRequestEv:

    iret


.data
    interruptNumber: .byte 0
