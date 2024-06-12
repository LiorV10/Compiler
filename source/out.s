.text
.globl print_vec
.type print_vec, @function
print_vec:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
mov %rdi, -16(%rbp)
mov %rsi, -8(%rbp)
mov -4(%rbp), %ebx
mov $0, %rcx
mov %ecx, -4(%rbp)
mov %ecx, %ebx
.AG0:
mov -4(%rbp), %ebx
mov -8(%rbp), %ecx
cmp %ecx, %ebx
setl %al
movsx %al, %ebx
test %ebx, %ebx
jz .AG1
mov -16(%rbp), %rbx
mov -4(%rbp), %ecx
movsx %ecx, %rcx
imul $4, %rcx
leaq (%rbx, %rcx), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG2:
.string "%d\t"
.text
leaq .AG2(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -4(%rbp), %ebx
mov $1, %rcx
add %ecx, %ebx
mov -4(%rbp), %ecx
mov %ebx, -4(%rbp)
mov %ebx, %ecx
jmp .AG0
.AG1:
.section .rodata
.AG3:
.string ""
.text
leaq .AG3(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
RET_0:
addq $16, %rsp
popq %rbp
ret
.text
.globl print_mat
.type print_mat, @function
print_mat:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
mov %rdi, -32(%rbp)
mov %rsi, -24(%rbp)
mov %rdx, -20(%rbp)
mov -16(%rbp), %ecx
mov $0, %rbx
mov %ebx, -16(%rbp)
mov %ebx, %ecx
.AG4:
mov -16(%rbp), %ecx
mov -24(%rbp), %ebx
cmp %ebx, %ecx
setl %al
movsx %al, %ecx
test %ecx, %ecx
jz .AG5
mov -20(%rbp), %ecx
movsx %ecx, %rcx
movq %rcx, %rsi
mov -32(%rbp), %rcx
mov -16(%rbp), %ebx
movsx %ebx, %rbx
imul $3, %rbx
imul $4, %rbx
leaq (%rcx, %rbx), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_vec
mov %rax, %rcx
mov -16(%rbp), %ecx
mov $1, %rbx
add %ebx, %ecx
mov -16(%rbp), %ebx
mov %ecx, -16(%rbp)
mov %ecx, %ebx
jmp .AG4
.AG5:
.section .rodata
.AG6:
.string ""
.text
leaq .AG6(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
RET_1:
addq $32, %rsp
popq %rbp
ret
.text
.globl sum_mat
.type sum_mat, @function
sum_mat:
pushq %rbp
movq %rsp, %rbp
subq $64, %rsp
mov %rdi, -64(%rbp)
mov %rsi, -56(%rbp)
mov %rdx, -52(%rbp)
mov -56(%rbp), %ebx
mov -52(%rbp), %ecx
movsx %ecx, %rcx
imul %rcx, %rbx
mov %ebx, -44(%rbp)
mov $0, %rbx
mov %ebx, -40(%rbp)
mov -64(%rbp), %rbx
mov %rbx, -36(%rbp)
mov -64(%rbp), %rbx
mov $0, %rcx
imul $3, %rcx
imul $4, %rcx
leaq (%rbx, %rcx), %rbx
mov $0, %rcx
imul $4, %rcx
leaq (%rbx, %rcx), %rbx
mov -36(%rbp), %rcx
cmp %rbx, %rcx
sete %al
movsx %al, %rcx
movq %rcx, %rsi
.section .rodata
.AG7:
.string "Same #1: %d\n"
.text
leaq .AG7(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -64(%rbp), %rcx
mov $0, %rbx
imul $3, %rbx
imul $4, %rbx
leaq (%rcx, %rbx), %rcx
mov $4, %rbx
imul $4, %rbx
leaq (%rcx, %rbx), %rcx
mov -36(%rbp), %rbx
mov $4, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov (%rbx), %ebx
mov (%rcx), %ecx
cmp %ecx, %ebx
sete %al
movsx %al, %ebx
mov -64(%rbp), %rcx
mov $1, %r10
imul $3, %r10
imul $4, %r10
leaq (%rcx, %r10), %rcx
mov $1, %r10
imul $4, %r10
leaq (%rcx, %r10), %rcx
mov -36(%rbp), %r10
mov $4, %r11
imul $4, %r11
leaq (%r10, %r11), %r10
mov (%r10), %r10d
mov (%rcx), %ecx
cmp %ecx, %r10d
sete %al
movsx %al, %r10d
and %ebx, %r10d
movsx %r10d, %r10
movq %r10, %rsi
.section .rodata
.AG8:
.string "Same #2: %d\n"
.text
leaq .AG8(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -48(%rbp), %r10d
mov $0, %rbx
mov %ebx, -48(%rbp)
mov %ebx, %r10d
.AG9:
mov -48(%rbp), %r10d
mov -44(%rbp), %ebx
cmp %ebx, %r10d
setl %al
movsx %al, %r10d
test %r10d, %r10d
jz .AG10
mov -36(%rbp), %r10
mov -48(%rbp), %ebx
movsx %ebx, %rbx
imul $4, %rbx
leaq (%r10, %rbx), %r10
mov -40(%rbp), %ebx
mov (%r10), %r10d
add %r10d, %ebx
mov -40(%rbp), %r10d
mov %ebx, -40(%rbp)
mov %ebx, %r10d
mov -48(%rbp), %r10d
mov $1, %rbx
add %ebx, %r10d
mov -48(%rbp), %ebx
mov %r10d, -48(%rbp)
mov %r10d, %ebx
jmp .AG9
.AG10:
mov -40(%rbp), %ebx
movsx %ebx, %rbx
mov %rbx, %rax
jmp RET_2
RET_2:
addq $64, %rsp
popq %rbp
ret
.text
.globl dummy
.type dummy, @function
dummy:
pushq %rbp
movq %rsp, %rbp
subq $0, %rsp
.section .rodata
.AG11:
.string "hello, world!"
.text
leaq .AG11(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
RET_3:
addq $0, %rsp
popq %rbp
ret
.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $80, %rsp
mov $2, %r10
mov %r10d, %bl
push %rcx
mov $8, %rcx
cld
lea 0(%rbp), %rsi
lea 0(%rbp), %rdi
rep movsb
pop %rcx
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $0, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $0, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $0, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $0, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $3, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $1, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $0, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $4, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $1, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $5, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $1, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $6, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $2, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $0, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $7, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $2, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $8, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $2, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $9, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $3, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $0, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $10, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $3, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $11, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -80(%rbp), %rbx
mov $3, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $12, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
mov $3, %rbx
movq %rbx, %xmm15
mov $4, %rbx
movq %rbx, %rsi
leaq -80(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_mat
mov %rax, %rbx
mov $3, %rbx
movq %rbx, %xmm15
mov $4, %rbx
movq %rbx, %rsi
leaq -80(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call sum_mat
mov %rax, %rbx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG12:
.string "Sum: %d\n\n"
.text
leaq .AG12(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -32(%rbp), %ebx
mov $0, %r10
mov %r10d, -32(%rbp)
mov %r10d, %ebx
.AG13:
mov -32(%rbp), %ebx
mov $4, %r10
movsx %ebx, %rbx
cmp %r10, %rbx
setl %al
movsx %al, %rbx
test %rbx, %rbx
jz .AG14
mov -28(%rbp), %ebx
mov $0, %r10
mov %r10d, -28(%rbp)
mov %r10d, %ebx
.AG15:
mov -28(%rbp), %ebx
mov $3, %r10
movsx %ebx, %rbx
cmp %r10, %rbx
setl %al
movsx %al, %rbx
test %rbx, %rbx
jz .AG16
leaq -80(%rbp), %rbx
mov -32(%rbp), %r10d
movsx %r10d, %r10
imul $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov -28(%rbp), %r10d
movsx %r10d, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov -32(%rbp), %r10d
mov -28(%rbp), %ecx
add %ecx, %r10d
mov %r10d, (%rbx)
mov %r10d, %ebx
mov -28(%rbp), %ebx
mov $1, %r10
add %r10d, %ebx
mov -28(%rbp), %r10d
mov %ebx, -28(%rbp)
mov %ebx, %r10d
jmp .AG15
.AG16:
mov -32(%rbp), %r10d
mov $1, %rbx
add %ebx, %r10d
mov -32(%rbp), %ebx
mov %r10d, -32(%rbp)
mov %r10d, %ebx
jmp .AG13
.AG14:
mov $3, %rbx
movq %rbx, %xmm15
mov $4, %rbx
movq %rbx, %rsi
leaq -80(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_mat
mov %rax, %rbx
leaq -24(%rbp), %rbx
mov $0, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $1, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -24(%rbp), %rbx
mov $1, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $2, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -24(%rbp), %rbx
mov $2, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $3, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -24(%rbp), %rbx
mov $3, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $4, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -24(%rbp), %rbx
mov $4, %r10
imul $4, %r10
leaq (%rbx, %r10), %rbx
mov $5, %r10
mov %r10d, (%rbx)
mov %r10d, %ebx
mov $5, %rbx
movq %rbx, %rsi
leaq -24(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_vec
mov %rax, %rbx
mov $1, %rbx
mov %rbx, %rax
jmp RET_4
RET_4:
addq $80, %rsp
popq %rbp
ret
