.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
movabs $0x40cccccd, %rax
movq %rax, %xmm0
cvttss2si %xmm0, %ebx
mov %ebx, -4(%rbp)
mov -4(%rbp), %ebx
mov %ebx, -8(%rbp)
movabs $0x3f4ccccd, %rax
movq %rax, %xmm0
cvttss2si %xmm0, %ebx
mov %ebx, -12(%rbp)
mov $4, %ebx
mov %ebx, -16(%rbp)
mov $2, %ebx
mov %ebx, -20(%rbp)
mov $0, %ebx
mov %ebx, -24(%rbp)
mov -8(%rbp), %ebx
mov -12(%rbp), %ecx
add %ecx,%ebx
mov %ebx, -28(%rbp)
mov -28(%rbp), %ebx
mov %ebx, %eax
popq %rbp
ret
