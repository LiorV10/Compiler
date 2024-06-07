.text
.globl init
.type init, @function
init:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
mov %rdi, -16(%rbp)
mov -16(%rbp), %rbx
mov $0, %rcx
mov %rcx, (%rbx)
RET_0:
addq $16, %rsp
popq %rbp
ret
.text
.globl push
.type push, @function
push:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
mov %rdi, -32(%rbp)
mov %rsi, -24(%rbp)
mov $12, %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
mov %rax, %rbx
mov %rbx, -20(%rbp)
mov -20(%rbp), %rbx
lea 0(%rbx), %rbx
mov -32(%rbp), %rcx
mov (%rcx), %rcx
mov %rcx, (%rbx)
mov -20(%rbp), %rbx
lea 8(%rbx), %rbx
mov -24(%rbp), %ecx
mov %ecx, (%rbx)
mov -32(%rbp), %rbx
mov -20(%rbp), %rcx
mov %rcx, (%rbx)
RET_1:
addq $32, %rsp
popq %rbp
ret
.text
.globl pop
.type pop, @function
pop:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
mov %rdi, -32(%rbp)
mov -32(%rbp), %rbx
mov (%rbx), %rbx
mov 8(%rbx), %rbx
mov %ebx, -24(%rbp)
mov -32(%rbp), %rbx
mov (%rbx), %rbx
mov %rbx, -20(%rbp)
mov -32(%rbp), %rbx
mov -32(%rbp), %rcx
mov (%rcx), %rcx
mov 0(%rcx), %rcx
mov %rcx, (%rbx)
mov -20(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rbx
mov -24(%rbp), %ebx
mov %ebx, %eax
jmp RET_2
RET_2:
addq $32, %rsp
popq %rbp
ret
.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $320, %rsp
mov $3, %rbx
mov %ebx, -320(%rbp)
mov -316(%rbp), %ebx
mov -248(%rbp), %rbx
mov $3, %rcx
mov %rcx, -248(%rbp)
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov -316(%rbp), %ecx
mov -248(%rbp), %rcx
mov $-248, %rax
add %rbp, %rax
mov %rax, -256(%rbp)
mov -316(%rbp), %ebx
mov -264(%rbp), %rbx
mov -316(%rbp), %ecx
mov -256(%rbp), %rcx
mov %rcx, -264(%rbp)
mov -316(%rbp), %ebx
mov -268(%rbp), %ebx
mov $7, %rcx
mov %ecx, -268(%rbp)
mov -316(%rbp), %ebx
mov -272(%rbp), %ebx
mov $8, %rcx
mov %ecx, -272(%rbp)
mov -316(%rbp), %ebx
mov -280(%rbp), %rbx
mov -316(%rbp), %ecx
mov -268(%rbp), %ecx
mov $-268, %rax
add %rbp, %rax
mov %rax, -280(%rbp)
mov -316(%rbp), %ebx
mov -288(%rbp), %rbx
mov -316(%rbp), %ecx
mov -280(%rbp), %rcx
mov $-280, %rax
add %rbp, %rax
mov %rax, -288(%rbp)
mov -316(%rbp), %ebx
mov -296(%rbp), %rbx
mov -316(%rbp), %ecx
mov -288(%rbp), %rcx
mov $-288, %rax
add %rbp, %rax
mov %rax, -296(%rbp)
mov -316(%rbp), %ebx
mov -300(%rbp), %ebx
mov -316(%rbp), %ecx
mov -248(%rbp), %rcx
mov %ecx, -300(%rbp)
mov -316(%rbp), %ebx
mov -308(%rbp), %rbx
mov -316(%rbp), %ecx
mov -300(%rbp), %ecx
mov $-300, %rax
add %rbp, %rax
mov %rax, -308(%rbp)
mov -316(%rbp), %ebx
mov -316(%rbp), %rbx
mov -316(%rbp), %ecx
mov -300(%rbp), %ecx
mov %rcx, -316(%rbp)
mov $777, %rbx
mov %ebx, -164(%rbp)
mov -164(%rbp), %ebx
mov $-164, %rax
add %rbp, %rax
mov %rax, -160(%rbp)
mov -160(%rbp), %rbx
mov $-160, %rax
add %rbp, %rax
mov %rax, -152(%rbp)
mov -152(%rbp), %rbx
mov (%rbx), %rbx
mov $888, %rcx
mov %ecx, (%rbx)
mov -144(%rbp), %ebx
mov -56(%rbp), %ebx
mov -164(%rbp), %ecx
mov %ecx, -56(%rbp)
mov -144(%rbp), %ebx
mov -60(%rbp), %ebx
mov -152(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
mov %ecx, -60(%rbp)
mov -240(%rbp), %ebx
mov -220(%rbp), %rbx
mov -152(%rbp), %rcx
mov $-152, %rax
add %rbp, %rax
mov %rax, -220(%rbp)
mov -316(%rbp), %ebx
mov -280(%rbp), %rbx
mov -316(%rbp), %ecx
mov -272(%rbp), %ecx
mov $-272, %rax
add %rbp, %rax
mov %rax, -280(%rbp)
mov -316(%rbp), %ebx
mov -272(%rbp), %ebx
mov -316(%rbp), %ecx
mov -268(%rbp), %ecx
mov $-268, %rax
add %rbp, %rax
mov (%rax), %ecx
mov $-268, %rax
add %rbp, %rax
mov (%rax), %ecx
mov $-268, %rax
add %rbp, %rax
mov (%rax), %ecx
mov -316(%rbp), %r10d
mov -272(%rbp), %r10d
add %ecx, %r10d
mov %r10d, -272(%rbp)
.section .rodata
.AG0:
.string "%d is moshe!\n"
.text
leaq .AG0(%rip), %rbx
movq %rbx, %rdi
mov -144(%rbp), %ebx
mov -60(%rbp), %ebx
mov -144(%rbp), %r10d
mov -56(%rbp), %r10d
mov %r10, %rax
imul %ebx
mov %rax, %r10
movq %r10, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -320(%rbp), %r10d
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov $-256, %rax
add %rbp, %rax
mov (%rax), %rbx
mov (%rbx), %rbx
mov %ebx, -320(%rbp)
.section .rodata
.AG1:
.string "malloc'd value: %d\n"
.text
leaq .AG1(%rip), %r10
movq %r10, %rdi
mov -320(%rbp), %r10d
movq %r10, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -316(%rbp), %r10d
mov -316(%rbp), %r10
mov $1, %rbx
add %rbx, %r10
test %r10, %r10
setz %al
movzbl %al, %r10d
test %r10, %r10
jz .AG2
.section .rodata
.AG4:
.string "%lu is max!\n"
.text
leaq .AG4(%rip), %r10
movq %r10, %rdi
mov -316(%rbp), %r10d
mov -316(%rbp), %r10
movq %r10, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
jmp .AG3
.AG2:
.section .rodata
.AG5:
.string "%lu is not max\n"
.text
leaq .AG5(%rip), %r10
movq %r10, %rdi
mov -316(%rbp), %r10d
mov -316(%rbp), %r10
movq %r10, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
.AG3:
.section .rodata
.AG6:
.string "Result:\t%d\t%d\t%d\t%d\t%d\n"
.text
leaq .AG6(%rip), %r10
mov %r10, -52(%rbp)
.section .rodata
.AG7:
.string "hello, world!"
.text
leaq .AG7(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call strdup
mov %rax, %r10
mov %r10, -44(%rbp)
mov -44(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %r10
mov -44(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %r10
mov -44(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %r10
.section .rodata
.AG8:
.string "\n"
.text
leaq .AG8(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -52(%rbp), %r10
movq %r10, %rdi
mov -316(%rbp), %r10d
mov -248(%rbp), %r10
movq %r10, %rsi
mov -316(%rbp), %r10d
mov -256(%rbp), %r10
mov (%r10), %r10
movq %r10, %xmm15
mov -316(%rbp), %r10d
mov -248(%rbp), %r10
mov $-248, %rax
add %rbp, %rax
mov (%rax), %r10
movq %r10, %xmm14
mov -316(%rbp), %r10d
mov -256(%rbp), %r10
mov $-256, %rax
add %rbp, %rax
mov (%rax), %r10
mov (%r10), %r10
movq %r10, %r8
mov -316(%rbp), %r10d
mov -308(%rbp), %r10
mov (%r10), %r10d
movq %r10, %r9
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
.section .rodata
.AG9:
.string "Char:\t%c\t%c\t%c\t%c\t%c\n"
.text
leaq .AG9(%rip), %r10
movq %r10, %rdi
mov -52(%rbp), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %rsi
mov -316(%rbp), %r10d
mov -268(%rbp), %r10d
mov $2, %rbx
mov %rbx, %rax
imul %r10d
mov %rax, %rbx
mov -316(%rbp), %r10d
mov -280(%rbp), %r10
mov (%r10), %r10d
sub %rbx, %r10
mov -52(%rbp), %rbx
movsx %r10d, %r10
add %r10, %rbx
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
movq %rbx, %xmm15
mov -316(%rbp), %ebx
mov -248(%rbp), %rbx
mov -52(%rbp), %r10
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %xmm14
mov -316(%rbp), %r10d
mov -296(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov (%rbx), %rbx
add %rbx, %r10
mov -52(%rbp), %rbx
leaq (%rbx, %r10, 1), %rbx
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
movq %rbx, %r8
mov -316(%rbp), %ebx
mov -296(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
mov -316(%rbp), %r10d
mov -256(%rbp), %r10
mov (%r10), %r10
add %r10, %rbx
mov -52(%rbp), %r10
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
mov -316(%rbp), %ebx
mov -268(%rbp), %ebx
mov $2, %rcx
mov %rcx, %rax
imul %ebx
mov %rax, %rcx
mov -316(%rbp), %ebx
mov -280(%rbp), %rbx
mov (%rbx), %ebx
sub %rcx, %rbx
mov -52(%rbp), %rcx
leaq (%rcx, %rbx, 1), %rcx
mov (%rcx), %cl
movsbl %cl, %ecx
movsx %ecx, %rcx
sub %r10, %rcx
mov -316(%rbp), %r10d
mov -248(%rbp), %r10
mov $1, %rbx
add %rbx, %r10
sub %r10, %rcx
mov -316(%rbp), %r10d
mov -248(%rbp), %r10
mov -52(%rbp), %rbx
add %r10, %rbx
leaq (%rbx, %rcx, 1), %rbx
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
movq %rbx, %r9
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -52(%rbp), %rbx
movq %rbx, %rdi
mov -316(%rbp), %ebx
mov -280(%rbp), %rbx
mov (%rbx), %ebx
mov -316(%rbp), %ecx
mov -272(%rbp), %ecx
add %ecx, %ebx
movq %rbx, %rsi
mov -316(%rbp), %ebx
mov -268(%rbp), %ebx
movq %rbx, %xmm15
mov -316(%rbp), %ebx
mov -248(%rbp), %rbx
movq %rbx, %xmm14
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov (%rbx), %rbx
mov -316(%rbp), %ecx
mov -248(%rbp), %rcx
movsx %ebx, %rbx
movsx %ecx, %rcx
mov %rbx, %rax
cqo
idiv %rcx
mov %rax, %rbx
movq %rbx, %r8
mov -240(%rbp), %ebx
mov -220(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
movq %rbx, %r9
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -52(%rbp), %rbx
movq %rbx, %rdi
mov -316(%rbp), %ebx
mov -296(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
neg %ebx
mov -316(%rbp), %ecx
mov -288(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
neg %ecx
movsx %ebx, %rbx
movsx %ecx, %rcx
mov %rbx, %rax
cqo
idiv %rcx
mov %rax, %rbx
neg %ebx
movq %rbx, %rsi
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov (%rbx), %rbx
neg %rbx
movq %rbx, %xmm15
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm14
mov -316(%rbp), %ebx
mov -296(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
mov -316(%rbp), %ecx
mov -248(%rbp), %rcx
mov $-248, %rax
add %rbp, %rax
mov (%rax), %rcx
mov %rcx, %rax
imul %ebx
mov %rax, %rcx
mov -316(%rbp), %ebx
mov -256(%rbp), %rbx
mov (%rbx), %rbx
mov %rcx, %rax
imul %rbx
mov %rax, %rcx
movq %rcx, %r8
mov -316(%rbp), %ecx
mov -296(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
movq %rcx, %r9
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
.section .rodata
.AG10:
.string "\n"
.text
leaq .AG10(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -144(%rbp), %ecx
mov -136(%rbp), %ecx
mov -316(%rbp), %ebx
xor %rax, %rax
.AG11:
lea -316(%rax, %rbp), %rdi
lea -136(%rax, %rbp), %rsi
mov (%rdi), %dl
mov %dl, (%rsi)
inc %rax
cmp $76, %rax
jnz .AG11
mov -144(%rbp), %ebx
mov -144(%rbp), %rbx
mov -316(%rbp), %r10d
mov $-316, %rax
add %rbp, %rax
mov %rax, -144(%rbp)
mov -144(%rbp), %ebx
mov -136(%rbp), %ebx
mov $-136, %rax
add %rbp, %rax
mov %rax, -36(%rbp)
mov -144(%rbp), %ebx
mov -144(%rbp), %rbx
mov %rbx, -28(%rbp)
mov -320(%rbp), %ebx
mov -144(%rbp), %r10d
mov -136(%rbp), %r10d
mov -116(%rbp), %r10
mov $-116, %rax
add %rbp, %rax
mov (%rax), %r10
mov $-116, %rax
add %rbp, %rax
mov (%rax), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
mov %r10d, -320(%rbp)
mov -320(%rbp), %ebx
mov -28(%rbp), %r10
mov 60(%r10), %r10
mov (%r10), %r10
mov -320(%rbp), %r11d
add %r10, %r11
mov %r11d, -320(%rbp)
pushq %rcx
subq $8, %rsp
mov $80, %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov %rbx, -20(%rbp)
mov -20(%rbp), %rbx
lea 68(%rbx), %rbx
mov -320(%rbp), %r11d
mov %r11, (%rbx)
pushq %rcx
subq $8, %rsp
.section .rodata
.AG12:
.string "AA:%d\n"
.text
leaq .AG12(%rip), %rbx
movq %rbx, %rdi
mov -20(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
pushq %rcx
subq $8, %rsp
mov -20(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov -36(%rbp), %rbx
mov 68(%rbx), %rbx
mov -320(%rbp), %r11d
cmp %r11d, %ebx
sete %al
movzbl %al, %ebx
test %rbx, %rbx
jz .AG13
pushq %rcx
subq $8, %rsp
.section .rodata
.AG15:
.string "%d = %d\n"
.text
leaq .AG15(%rip), %rbx
movq %rbx, %rdi
mov -36(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
mov -320(%rbp), %ebx
movq %rbx, %xmm15
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
jmp .AG14
.AG13:
pushq %rcx
subq $8, %rsp
.section .rodata
.AG16:
.string "%d != %d\n"
.text
leaq .AG16(%rip), %rbx
movq %rbx, %rdi
mov -36(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
mov -320(%rbp), %ebx
movq %rbx, %xmm15
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
.AG14:
pushq %rcx
subq $8, %rsp
mov -12(%rbp), %rbx
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call init
add $8, %rsp
popq %rcx
mov %rax, %rbx
pushq %rcx
subq $8, %rsp
mov -12(%rbp), %rbx
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
mov $5, %rbx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
add $8, %rsp
popq %rcx
mov %rax, %rbx
pushq %rcx
subq $8, %rsp
mov -12(%rbp), %rbx
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
mov $7, %rbx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
add $8, %rsp
popq %rcx
mov %rax, %rbx
pushq %rcx
subq $8, %rsp
mov -12(%rbp), %rbx
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
mov $9, %rbx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov -320(%rbp), %ebx
pushq %rbx
pushq %rcx
mov -12(%rbp), %r11
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call pop
popq %rcx
popq %rbx
mov %rax, %r11
mov %r11d, -320(%rbp)
pushq %rcx
subq $8, %rsp
.section .rodata
.AG17:
.string "%d\n"
.text
leaq .AG17(%rip), %rbx
movq %rbx, %rdi
mov -320(%rbp), %ebx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov -320(%rbp), %ebx
pushq %rbx
pushq %rcx
mov -12(%rbp), %r11
mov $-12, %rax
add %rbp, %rax
movq %rax, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call pop
popq %rcx
popq %rbx
mov %rax, %r11
mov %r11d, -320(%rbp)
pushq %rcx
subq $8, %rsp
.section .rodata
.AG18:
.string "%d\n"
.text
leaq .AG18(%rip), %rbx
movq %rbx, %rdi
mov -320(%rbp), %ebx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov -320(%rbp), %ebx
mov -12(%rbp), %r11
mov 8(%r11), %r11
mov %r11d, -320(%rbp)
pushq %rcx
subq $8, %rsp
.section .rodata
.AG19:
.string "%d\n"
.text
leaq .AG19(%rip), %rbx
movq %rbx, %rdi
mov -320(%rbp), %ebx
movq %rbx, %rsi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
add $8, %rsp
popq %rcx
mov %rax, %rbx
mov -320(%rbp), %ebx
mov %ebx, %eax
jmp RET_3
RET_3:
addq $320, %rsp
popq %rbp
ret
