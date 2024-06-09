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
mov %rcx, %rbx
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
mov -32(%rbp), %rbx
mov (%rbx), %rbx
mov -20(%rbp), %rcx
lea 0(%rcx), %rcx
mov %rbx, (%rcx)
mov %rbx, %rcx
mov -20(%rbp), %rcx
lea 8(%rcx), %rcx
mov -24(%rbp), %ebx
mov %ebx, (%rcx)
mov %rbx, %rcx
mov -32(%rbp), %rcx
mov -20(%rbp), %rbx
mov %rbx, (%rcx)
mov %rbx, %rcx
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
mov -32(%rbp), %rcx
mov (%rcx), %rcx
mov 8(%rcx), %rcx
mov %ecx, -24(%rbp)
mov -32(%rbp), %rcx
mov (%rcx), %rcx
mov %rcx, -20(%rbp)
mov -20(%rbp), %rcx
mov 0(%rcx), %rcx
mov -32(%rbp), %rbx
mov %rcx, (%rbx)
mov %rcx, %rbx
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
.globl is_empty
.type is_empty, @function
is_empty:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
mov %rdi, -16(%rbp)
mov -16(%rbp), %rbx
mov $0, %rcx
cmp %rcx, %rbx
sete %al
movzbl %al, %ebx
mov %rbx, %rax
jmp RET_3
RET_3:
addq $16, %rsp
popq %rbp
ret
.text
.globl print_list_rec
.type print_list_rec, @function
print_list_rec:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
mov %rdi, -16(%rbp)
mov -16(%rbp), %rbx
test %rbx, %rbx
setz %al
movzbl %al, %ebx
test %rbx, %rbx
jz .AG1
.section .rodata
.AG2:
.string "||"
.text
leaq .AG2(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx

jmp RET_4
.AG1:
mov -16(%rbp), %rbx
mov 8(%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG3:
.string "%d->"
.text
leaq .AG3(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -16(%rbp), %rbx
mov 0(%rbx), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_rec
mov %rax, %rbx
RET_4:
addq $16, %rsp
popq %rbp
ret
.text
.globl print_list_iter
.type print_list_iter, @function
print_list_iter:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
mov %rdi, -16(%rbp)
mov -8(%rbp), %rbx
mov -16(%rbp), %rcx
mov %rcx, -8(%rbp)
mov %rcx, %rbx
.AG4:
mov -8(%rbp), %rbx
test %rbx, %rbx
jz .AG5
mov -8(%rbp), %rbx
mov 8(%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG6:
.string "%d->"
.text
leaq .AG6(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -8(%rbp), %rbx
mov 0(%rbx), %rbx
mov -8(%rbp), %rcx
mov %rbx, -8(%rbp)
mov %rbx, %rcx
jmp .AG4
.AG5:
.section .rodata
.AG7:
.string "||"
.text
leaq .AG7(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
RET_5:
addq $16, %rsp
popq %rbp
ret
.text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $496, %rsp
mov $3, %rcx
mov %ecx, -496(%rbp)
mov -492(%rbp), %ecx
mov -424(%rbp), %rcx
mov $3, %rbx
mov %rbx, -424(%rbp)
mov %rbx, %rcx
mov -492(%rbp), %ecx
mov -424(%rbp), %rcx
leaq -424(%rbp), %rcx
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
mov %rcx, -432(%rbp)
mov %rcx, %rbx
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
mov -492(%rbp), %ecx
mov -440(%rbp), %rcx
mov %rbx, -440(%rbp)
mov %rbx, %rcx
mov -492(%rbp), %ecx
mov -444(%rbp), %ecx
mov $7, %rbx
mov %ebx, -444(%rbp)
mov %ebx, %ecx
mov -492(%rbp), %ecx
mov -448(%rbp), %ecx
mov $8, %rbx
mov %ebx, -448(%rbp)
mov %ebx, %ecx
mov -492(%rbp), %ecx
mov -444(%rbp), %ecx
leaq -444(%rbp), %rcx
mov -492(%rbp), %ebx
mov -456(%rbp), %rbx
mov %rcx, -456(%rbp)
mov %rcx, %rbx
mov -492(%rbp), %ebx
mov -456(%rbp), %rbx
leaq -456(%rbp), %rbx
mov -492(%rbp), %ecx
mov -464(%rbp), %rcx
mov %rbx, -464(%rbp)
mov %rbx, %rcx
mov -492(%rbp), %ecx
mov -464(%rbp), %rcx
leaq -464(%rbp), %rcx
mov -492(%rbp), %ebx
mov -472(%rbp), %rbx
mov %rcx, -472(%rbp)
mov %rcx, %rbx
mov -492(%rbp), %ebx
mov -424(%rbp), %rbx
mov -492(%rbp), %ecx
mov -476(%rbp), %ecx
mov %ebx, -476(%rbp)
mov %ebx, %ecx
mov -492(%rbp), %ecx
mov -476(%rbp), %ecx
leaq -476(%rbp), %rcx
mov -492(%rbp), %ebx
mov -484(%rbp), %rbx
mov %rcx, -484(%rbp)
mov %rcx, %rbx
mov -492(%rbp), %ebx
mov -476(%rbp), %ebx
mov -492(%rbp), %ecx
mov -492(%rbp), %rcx
mov %rbx, -492(%rbp)
mov %rbx, %rcx
mov $777, %rcx
mov %ecx, -340(%rbp)
mov -340(%rbp), %ecx
leaq -340(%rbp), %rcx
mov %rcx, -336(%rbp)
mov -336(%rbp), %rcx
leaq -336(%rbp), %rcx
mov %rcx, -328(%rbp)
mov -328(%rbp), %rcx
mov (%rcx), %rcx
mov $888, %rbx
mov %ebx, (%rcx)
mov %rbx, %rcx
mov -320(%rbp), %ecx
mov -232(%rbp), %ecx
mov -340(%rbp), %ebx
mov %ebx, -232(%rbp)
mov %ebx, %ecx
mov -328(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
mov -320(%rbp), %ebx
mov -236(%rbp), %ebx
mov %ecx, -236(%rbp)
mov %ecx, %ebx
mov -328(%rbp), %rbx
leaq -328(%rbp), %rbx
mov -416(%rbp), %ecx
mov -396(%rbp), %rcx
mov %rbx, -396(%rbp)
mov %rbx, %rcx
mov -492(%rbp), %ecx
mov -448(%rbp), %ecx
leaq -448(%rbp), %rcx
mov -492(%rbp), %ebx
mov -456(%rbp), %rbx
mov %rcx, -456(%rbp)
mov %rcx, %rbx
mov -492(%rbp), %ebx
mov -444(%rbp), %ebx
mov -492(%rbp), %ecx
mov -448(%rbp), %ecx
add %ebx, %ecx
mov -492(%rbp), %ebx
mov -448(%rbp), %ebx
mov %ecx, -448(%rbp)
mov %ecx, %ebx
mov -320(%rbp), %ebx
mov -236(%rbp), %ebx
mov -320(%rbp), %ecx
mov -232(%rbp), %ecx
mov %rcx, %rax
imul %ebx
mov %rax, %rcx
movq %rcx, %rsi
.section .rodata
.AG8:
.string "%d is moshe!\n"
.text
leaq .AG8(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -492(%rbp), %ecx
mov -432(%rbp), %rcx
leaq -432(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov -496(%rbp), %ebx
mov %ecx, -496(%rbp)
mov %ecx, %ebx
mov -496(%rbp), %ebx
movq %rbx, %rsi
.section .rodata
.AG9:
.string "malloc'd value: %d\n"
.text
leaq .AG9(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -492(%rbp), %ebx
mov -492(%rbp), %rbx
mov $1, %rcx
add %rcx, %rbx
test %rbx, %rbx
setz %al
movzbl %al, %ebx
test %rbx, %rbx
jz .AG10
mov -492(%rbp), %ebx
mov -492(%rbp), %rbx
movq %rbx, %rsi
.section .rodata
.AG12:
.string "%lu is max!\n"
.text
leaq .AG12(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
jmp .AG11
.AG10:
mov -492(%rbp), %ebx
mov -492(%rbp), %rbx
movq %rbx, %rsi
.section .rodata
.AG13:
.string "%lu is not max\n"
.text
leaq .AG13(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
.AG11:
.section .rodata
.AG14:
.string "Result:\t%d\t%d\t%d\t%d\t%d\n"
.text
leaq .AG14(%rip), %rbx
mov %rbx, -228(%rbp)
.section .rodata
.AG15:
.string "hello, world!"
.text
leaq .AG15(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call strdup
mov %rax, %rbx
mov %rbx, -220(%rbp)
mov -220(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
mov -220(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rbx
mov -220(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
.section .rodata
.AG16:
.string "\n"
.text
leaq .AG16(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -492(%rbp), %ebx
mov -484(%rbp), %rbx
mov (%rbx), %ebx
movq %rbx, %r9
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
leaq -432(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
movq %rbx, %r8
mov -492(%rbp), %ebx
mov -424(%rbp), %rbx
leaq -424(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm14
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm15
mov -492(%rbp), %ebx
mov -424(%rbp), %rbx
movq %rbx, %rsi
mov -228(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -492(%rbp), %ebx
mov -472(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
mov -492(%rbp), %ecx
mov -432(%rbp), %rcx
mov (%rcx), %rcx
add %rcx, %rbx
mov -228(%rbp), %rcx
movsx %ebx, %rbx
leaq (%rcx, %rbx, 1), %rcx
mov (%rcx), %cl
movsbl %cl, %ecx
movsx %ecx, %rcx
mov -492(%rbp), %ebx
mov -444(%rbp), %ebx
mov $2, %r10
mov %r10, %rax
imul %ebx
mov %rax, %r10
mov -492(%rbp), %ebx
mov -456(%rbp), %rbx
mov (%rbx), %ebx
sub %r10, %rbx
mov -228(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
sub %rcx, %r10
mov -492(%rbp), %ecx
mov -424(%rbp), %rcx
mov $1, %rbx
add %rbx, %rcx
sub %rcx, %r10
mov -492(%rbp), %ecx
mov -424(%rbp), %rcx
mov -228(%rbp), %rbx
leaq (%rbx, %rcx, 1), %rbx
leaq (%rbx, %r10, 1), %rbx
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
movq %rbx, %r9
mov -492(%rbp), %ebx
mov -472(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
mov -492(%rbp), %r10d
mov -432(%rbp), %r10
mov (%r10), %r10
add %r10, %rbx
mov -228(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %r8
mov -492(%rbp), %r10d
mov -424(%rbp), %r10
mov -228(%rbp), %rbx
leaq (%rbx, %r10, 1), %rbx
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
movq %rbx, %xmm14
mov -492(%rbp), %ebx
mov -444(%rbp), %ebx
mov $2, %r10
mov %r10, %rax
imul %ebx
mov %rax, %r10
mov -492(%rbp), %ebx
mov -456(%rbp), %rbx
mov (%rbx), %ebx
sub %r10, %rbx
mov -228(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %xmm15
mov -228(%rbp), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %rsi
.section .rodata
.AG17:
.string "Char:\t%c\t%c\t%c\t%c\t%c\n"
.text
leaq .AG17(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -416(%rbp), %r10d
mov -396(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movq %r10, %r9
mov -492(%rbp), %r10d
mov -432(%rbp), %r10
mov (%r10), %r10
mov -492(%rbp), %ebx
mov -424(%rbp), %rbx
movsx %r10d, %r10
movsx %ebx, %rbx
mov %r10, %rax
cqo
idiv %rbx
mov %rax, %r10
movq %r10, %r8
mov -492(%rbp), %r10d
mov -424(%rbp), %r10
movq %r10, %xmm14
mov -492(%rbp), %r10d
mov -444(%rbp), %r10d
movq %r10, %xmm15
mov -492(%rbp), %r10d
mov -456(%rbp), %r10
mov (%r10), %r10d
mov -492(%rbp), %ebx
mov -448(%rbp), %ebx
add %ebx, %r10d
movq %r10, %rsi
mov -228(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -492(%rbp), %r10d
mov -472(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movq %r10, %r9
mov -492(%rbp), %r10d
mov -472(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
mov -492(%rbp), %ebx
mov -424(%rbp), %rbx
leaq -424(%rbp), %rbx
mov (%rbx), %rbx
mov %rbx, %rax
imul %r10d
mov %rax, %rbx
mov -492(%rbp), %r10d
mov -432(%rbp), %r10
mov (%r10), %r10
mov %rbx, %rax
imul %r10
mov %rax, %rbx
movq %rbx, %r8
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm14
mov -492(%rbp), %ebx
mov -432(%rbp), %rbx
mov (%rbx), %rbx
neg %rbx
movq %rbx, %xmm15
mov -492(%rbp), %ebx
mov -472(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
neg %ebx
mov -492(%rbp), %r10d
mov -464(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10d
neg %r10d
movsx %ebx, %rbx
movsx %r10d, %r10
mov %rbx, %rax
cqo
idiv %r10
mov %rax, %rbx
neg %ebx
movq %rbx, %rsi
mov -228(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
.section .rodata
.AG18:
.string "\n"
.text
leaq .AG18(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -320(%rbp), %ebx
mov -312(%rbp), %ebx
mov -492(%rbp), %r10d
xor %rax, %rax
.AG19:
lea -492(%rax, %rbp), %rdi
lea -312(%rax, %rbp), %rsi
mov (%rdi), %dl
mov %dl, (%rsi)
inc %rax
cmp $76, %rax
jnz .AG19
mov -492(%rbp), %ebx
leaq -492(%rbp), %rbx
mov -320(%rbp), %r10d
mov -320(%rbp), %r10
mov %rbx, -320(%rbp)
mov %rbx, %r10
mov -320(%rbp), %r10d
mov -312(%rbp), %r10d
leaq -312(%rbp), %r10
mov %r10, -212(%rbp)
mov -320(%rbp), %r10d
mov -320(%rbp), %r10
mov %r10, -204(%rbp)
mov -320(%rbp), %r10d
mov -312(%rbp), %r10d
mov -292(%rbp), %r10
leaq -292(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
mov -496(%rbp), %ebx
mov %r10d, -496(%rbp)
mov %r10d, %ebx
mov -204(%rbp), %rbx
mov 60(%rbx), %rbx
mov (%rbx), %rbx
mov -496(%rbp), %r10d
add %rbx, %r10
mov -496(%rbp), %ebx
mov %r10d, -496(%rbp)
mov %r10d, %ebx
mov $80, %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
mov %rax, %rbx
mov %rbx, -196(%rbp)
mov -196(%rbp), %rbx
lea 68(%rbx), %rbx
mov -496(%rbp), %r10d
mov %r10, (%rbx)
mov %r10, %rbx
mov -196(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG20:
.string "AA:%d\n"
.text
leaq .AG20(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -196(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rbx
mov -212(%rbp), %rbx
mov 68(%rbx), %rbx
mov -496(%rbp), %r10d
cmp %r10d, %ebx
sete %al
movzbl %al, %ebx
test %ebx, %ebx
jz .AG21
mov -496(%rbp), %ebx
movq %rbx, %xmm15
mov -212(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG23:
.string "%d = %d\n"
.text
leaq .AG23(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
jmp .AG22
.AG21:
mov -496(%rbp), %ebx
movq %rbx, %xmm15
mov -212(%rbp), %rbx
mov 68(%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG24:
.string "%d != %d\n"
.text
leaq .AG24(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
.AG22:
mov -188(%rbp), %rbx
leaq -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call init
mov %rax, %rbx
mov $5, %rbx
movq %rbx, %rsi
mov -188(%rbp), %rbx
leaq -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov $7, %rbx
movq %rbx, %rsi
mov -188(%rbp), %rbx
leaq -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov $9, %rbx
movq %rbx, %rsi
mov -188(%rbp), %rbx
leaq -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_rec
mov %rax, %rbx
mov -188(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_iter
mov %rax, %rbx
mov $2, %rbx
mov %ebx, -173(%rbp)
leaq -176(%rbp), %rbx
mov -173(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 8), %rbx
mov -188(%rbp), %r10
mov %r10, (%rbx)
mov %r10, %rbx
.AG25:
leaq -176(%rbp), %rbx
mov -173(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 8), %rbx
mov (%rbx), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call is_empty
mov %rax, %rbx
test %ebx, %ebx
setz %al
movzbl %al, %ebx
test %ebx, %ebx
jz .AG26
leaq -176(%rbp), %rbx
mov -173(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 8), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call pop
mov %rax, %rbx
movq %rbx, %rsi
.section .rodata
.AG27:
.string "%d->"
.text
leaq .AG27(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
jmp .AG25
.AG26:
.section .rodata
.AG28:
.string "||"
.text
leaq .AG28(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
mov $80, %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
mov %rax, %rbx
mov %rbx, -169(%rbp)
mov -169(%rbp), %rbx
mov $0, %r10
leaq (%rbx, %r10, 4), %rbx
mov $2, %r10
mov -496(%rbp), %ecx
mov %r10, %rax
imul %ecx
mov %rax, %r10
mov %r10, (%rbx)
mov %r10, %rbx
leaq -161(%rbp), %rbx
mov -496(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
mov $0, %r10
mov %r10, (%rbx)
mov %r10, %rbx
leaq -161(%rbp), %rbx
mov -496(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
mov (%rbx), %ebx
mov -169(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov (%r10), %r10d
mov %r10d, %eax
jmp RET_6
RET_6:
addq $496, %rsp
popq %rbp
ret
