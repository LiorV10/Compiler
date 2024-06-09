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
mov -20(%rbp), %rcx
lea 0(%rcx), %rcx
mov (%rbx), %rbx
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
mov %rcx, -24(%rbp)
mov -24(%rbp), %rcx
lea 8(%rcx), %rcx
mov (%rcx), %ecx
mov %ecx, -16(%rbp)
mov -32(%rbp), %rcx
mov (%rcx), %rcx
lea 0(%rcx), %rcx
mov -32(%rbp), %rbx
mov (%rcx), %rcx
mov %rcx, (%rbx)
mov %rcx, %rbx
mov -24(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rbx
mov -16(%rbp), %ebx
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
.globl print_list_iter
.type print_list_iter, @function
print_list_iter:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
mov %rdi, -32(%rbp)
mov %rsi, -24(%rbp)
mov -16(%rbp), %rbx
mov -32(%rbp), %rcx
mov %rcx, -16(%rbp)
mov %rcx, %rbx
.AG0:
mov -16(%rbp), %rbx
test %rbx, %rbx
jz .AG1
mov -16(%rbp), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movq %rbx, %rsi
.section .rodata
.AG2:
.string "%d->"
.text
leaq .AG2(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -24(%rbp), %rbx
mov $1, %rcx
mov (%rbx), %ebx
add %rcx, %rbx
mov -24(%rbp), %rcx
mov %ebx, (%rcx)
mov %rbx, %rcx
mov -16(%rbp), %rcx
lea 0(%rcx), %rcx
mov -16(%rbp), %rbx
mov (%rcx), %rcx
mov %rcx, -16(%rbp)
mov %rcx, %rbx
jmp .AG0
.AG1:
.section .rodata
.AG3:
.string "||"
.text
leaq .AG3(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
RET_4:
addq $32, %rsp
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
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call is_empty
mov %rax, %rbx
test %ebx, %ebx
jz .AG5
.section .rodata
.AG6:
.string "||"
.text
leaq .AG6(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx

jmp RET_5
.AG5:
mov -16(%rbp), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movq %rbx, %rsi
.section .rodata
.AG7:
.string "%d->"
.text
leaq .AG7(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -16(%rbp), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_rec
mov %rax, %rbx
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
subq $608, %rsp
mov $3, %rbx
mov %ebx, -608(%rbp)
mov -604(%rbp), %ebx
mov -536(%rbp), %rbx
mov $3, %rcx
mov %rcx, -536(%rbp)
mov %rcx, %rbx
mov -604(%rbp), %ebx
mov -536(%rbp), %rbx
leaq -536(%rbp), %rbx
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov %rbx, -544(%rbp)
mov %rbx, %rcx
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov -604(%rbp), %ebx
mov -552(%rbp), %rbx
mov %rcx, -552(%rbp)
mov %rcx, %rbx
mov -604(%rbp), %ebx
mov -556(%rbp), %ebx
mov $7, %rcx
mov %ecx, -556(%rbp)
mov %ecx, %ebx
mov -604(%rbp), %ebx
mov -560(%rbp), %ebx
mov $8, %rcx
mov %ecx, -560(%rbp)
mov %ecx, %ebx
mov -604(%rbp), %ebx
mov -556(%rbp), %ebx
leaq -556(%rbp), %rbx
mov -604(%rbp), %ecx
mov -568(%rbp), %rcx
mov %rbx, -568(%rbp)
mov %rbx, %rcx
mov -604(%rbp), %ecx
mov -568(%rbp), %rcx
leaq -568(%rbp), %rcx
mov -604(%rbp), %ebx
mov -576(%rbp), %rbx
mov %rcx, -576(%rbp)
mov %rcx, %rbx
mov -604(%rbp), %ebx
mov -576(%rbp), %rbx
leaq -576(%rbp), %rbx
mov -604(%rbp), %ecx
mov -584(%rbp), %rcx
mov %rbx, -584(%rbp)
mov %rbx, %rcx
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
mov -604(%rbp), %ebx
mov -588(%rbp), %ebx
mov %ecx, -588(%rbp)
mov %ecx, %ebx
mov -604(%rbp), %ebx
mov -588(%rbp), %ebx
leaq -588(%rbp), %rbx
mov -604(%rbp), %ecx
mov -596(%rbp), %rcx
mov %rbx, -596(%rbp)
mov %rbx, %rcx
mov -604(%rbp), %ecx
mov -588(%rbp), %ecx
mov -604(%rbp), %ebx
mov -604(%rbp), %rbx
mov %rcx, -604(%rbp)
mov %rcx, %rbx
mov $777, %rbx
mov %ebx, -452(%rbp)
mov -452(%rbp), %ebx
leaq -452(%rbp), %rbx
mov %rbx, -448(%rbp)
mov -448(%rbp), %rbx
leaq -448(%rbp), %rbx
mov %rbx, -440(%rbp)
mov -440(%rbp), %rbx
mov (%rbx), %rbx
mov $888, %rcx
mov %ecx, (%rbx)
mov %rcx, %rbx
mov -432(%rbp), %ebx
mov -344(%rbp), %ebx
mov -452(%rbp), %ecx
mov %ecx, -344(%rbp)
mov %ecx, %ebx
mov -440(%rbp), %rbx
mov (%rbx), %rbx
mov -432(%rbp), %ecx
mov -348(%rbp), %ecx
mov (%rbx), %ebx
mov %ebx, -348(%rbp)
mov %ebx, %ecx
mov -440(%rbp), %rcx
leaq -440(%rbp), %rcx
mov -528(%rbp), %ebx
mov -508(%rbp), %rbx
mov %rcx, -508(%rbp)
mov %rcx, %rbx
mov -604(%rbp), %ebx
mov -560(%rbp), %ebx
leaq -560(%rbp), %rbx
mov -604(%rbp), %ecx
mov -568(%rbp), %rcx
mov %rbx, -568(%rbp)
mov %rbx, %rcx
mov -604(%rbp), %ecx
mov -556(%rbp), %ecx
mov -604(%rbp), %ebx
mov -560(%rbp), %ebx
add %ecx, %ebx
mov -604(%rbp), %ecx
mov -560(%rbp), %ecx
mov %ebx, -560(%rbp)
mov %ebx, %ecx
mov -432(%rbp), %ecx
mov -348(%rbp), %ecx
mov -432(%rbp), %ebx
mov -344(%rbp), %ebx
imul %rcx, %rbx
movq %rbx, %rsi
.section .rodata
.AG8:
.string "%d is moshe!\n"
.text
leaq .AG8(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -604(%rbp), %ebx
mov -544(%rbp), %rbx
mov -608(%rbp), %ecx
mov (%rbx), %rbx
mov %rbx, -608(%rbp)
mov %rbx, %rcx
mov -608(%rbp), %ecx
movq %rcx, %rsi
.section .rodata
.AG9:
.string "malloc'd value: %d\n"
.text
leaq .AG9(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
.section .rodata
.AG10:
.string "Result:\t%d\t%d\t%d\t%d\t%d\n"
.text
leaq .AG10(%rip), %rcx
mov %rcx, -340(%rbp)
.section .rodata
.AG11:
.string "hello, world!"
.text
leaq .AG11(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call strdup
mov %rax, %rcx
mov %rcx, -332(%rbp)
mov -332(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
mov -332(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rcx
mov -332(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
.section .rodata
.AG12:
.string "\n"
.text
leaq .AG12(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -604(%rbp), %ecx
mov -596(%rbp), %rcx
mov (%rcx), %ecx
movq %rcx, %r9
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
movq %rcx, %r8
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
movq %rcx, %xmm14
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
movq %rcx, %xmm15
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
movq %rcx, %rsi
mov -340(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -604(%rbp), %ecx
mov -596(%rbp), %rcx
mov (%rcx), %ecx
movq %rcx, %r9
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
movq %rcx, %r8
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
movq %rcx, %xmm14
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
movq %rcx, %xmm15
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
movq %rcx, %rsi
mov -340(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -604(%rbp), %ecx
mov -584(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov -604(%rbp), %ebx
mov -544(%rbp), %rbx
mov (%rcx), %ecx
mov (%rbx), %rbx
add %rbx, %rcx
mov -340(%rbp), %rbx
leaq (%rbx, %rcx, 1), %rbx
mov -604(%rbp), %ecx
mov -556(%rbp), %ecx
mov $2, %r10
imul %rcx, %r10
mov -604(%rbp), %ecx
mov -568(%rbp), %rcx
mov (%rcx), %ecx
sub %r10, %rcx
mov -340(%rbp), %r10
leaq (%r10, %rcx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
mov (%rbx), %bl
movsbl %bl, %ebx
movsx %ebx, %rbx
sub %rbx, %r10
mov -604(%rbp), %ebx
mov -536(%rbp), %rbx
mov $1, %rcx
add %rcx, %rbx
sub %rbx, %r10
mov -604(%rbp), %ebx
mov -536(%rbp), %rbx
mov -340(%rbp), %rcx
leaq (%rcx, %rbx, 1), %rcx
leaq (%rcx, %r10, 1), %rcx
mov (%rcx), %cl
movsbl %cl, %ecx
movsx %ecx, %rcx
movq %rcx, %r9
mov -604(%rbp), %ecx
mov -584(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov -604(%rbp), %r10d
mov -544(%rbp), %r10
mov (%rcx), %ecx
mov (%r10), %r10
add %r10, %rcx
mov -340(%rbp), %r10
leaq (%r10, %rcx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %r8
mov -604(%rbp), %r10d
mov -536(%rbp), %r10
mov -340(%rbp), %rcx
leaq (%rcx, %r10, 1), %rcx
mov (%rcx), %cl
movsbl %cl, %ecx
movsx %ecx, %rcx
movq %rcx, %xmm14
mov -604(%rbp), %ecx
mov -556(%rbp), %ecx
mov $2, %r10
imul %rcx, %r10
mov -604(%rbp), %ecx
mov -568(%rbp), %rcx
mov (%rcx), %ecx
sub %r10, %rcx
mov -340(%rbp), %r10
leaq (%r10, %rcx, 1), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %xmm15
mov -340(%rbp), %r10
mov (%r10), %r10b
movsbl %r10b, %r10d
movsx %r10d, %r10
movq %r10, %rsi
.section .rodata
.AG13:
.string "Char:\t%c\t%c\t%c\t%c\t%c\n"
.text
leaq .AG13(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -528(%rbp), %r10d
mov -508(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movq %r10, %r9
mov -604(%rbp), %r10d
mov -544(%rbp), %r10
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
mov (%r10), %r10
movsx %r10d, %r10
movsx %ecx, %rcx
mov %r10, %rax
cqo
idiv %rcx
mov %rax, %r10
movq %r10, %r8
mov -604(%rbp), %r10d
mov -536(%rbp), %r10
movq %r10, %xmm14
mov -604(%rbp), %r10d
mov -556(%rbp), %r10d
movq %r10, %xmm15
mov -604(%rbp), %r10d
mov -568(%rbp), %r10
mov -604(%rbp), %ecx
mov -560(%rbp), %ecx
mov (%r10), %r10d
add %ecx, %r10d
movq %r10, %rsi
mov -340(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -604(%rbp), %r10d
mov -584(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movq %r10, %r9
mov -604(%rbp), %r10d
mov -584(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov -604(%rbp), %ecx
mov -536(%rbp), %rcx
mov (%r10), %r10d
imul %r10, %rcx
mov -604(%rbp), %r10d
mov -544(%rbp), %r10
mov (%r10), %r10
imul %r10, %rcx
movq %rcx, %r8
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
movq %rcx, %xmm14
mov -604(%rbp), %ecx
mov -544(%rbp), %rcx
mov (%rcx), %rcx
neg %rcx
movq %rcx, %xmm15
mov -604(%rbp), %ecx
mov -584(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
neg %ecx
mov -604(%rbp), %r10d
mov -576(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10d
neg %r10d
movsx %ecx, %rcx
movsx %r10d, %r10
mov %rcx, %rax
cqo
idiv %r10
mov %rax, %rcx
neg %ecx
movq %rcx, %rsi
mov -340(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
.section .rodata
.AG14:
.string "\n"
.text
leaq .AG14(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -432(%rbp), %ecx
mov -424(%rbp), %ecx
mov -604(%rbp), %r10d
push %rcx
mov $76, %rcx
cld
lea -604(%rbp), %rsi
lea -424(%rbp), %rdi
rep movsb
pop %rcx
mov -604(%rbp), %ecx
leaq -604(%rbp), %rcx
mov -432(%rbp), %r10d
mov -432(%rbp), %r10
mov %rcx, -432(%rbp)
mov %rcx, %r10
mov -432(%rbp), %r10d
mov -424(%rbp), %r10d
leaq -424(%rbp), %r10
mov %r10, -324(%rbp)
mov -432(%rbp), %r10d
mov -432(%rbp), %r10
mov %r10, -316(%rbp)
mov -432(%rbp), %r10d
mov -424(%rbp), %r10d
mov -404(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov -608(%rbp), %ecx
mov (%r10), %r10d
mov %r10d, -608(%rbp)
mov %r10d, %ecx
mov -316(%rbp), %rcx
lea 60(%rcx), %rcx
mov (%rcx), %rcx
mov -608(%rbp), %r10d
mov (%rcx), %rcx
add %rcx, %r10
mov -608(%rbp), %ecx
mov %r10d, -608(%rbp)
mov %r10d, %ecx
mov $80, %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
mov %rax, %rcx
mov %rcx, -308(%rbp)
mov -308(%rbp), %rcx
lea 68(%rcx), %rcx
mov -608(%rbp), %r10d
mov %r10, (%rcx)
mov %r10, %rcx
mov -308(%rbp), %rcx
lea 68(%rcx), %rcx
mov (%rcx), %rcx
movq %rcx, %rsi
.section .rodata
.AG15:
.string "AA:%d\n"
.text
leaq .AG15(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -308(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rcx
mov -324(%rbp), %rcx
lea 68(%rcx), %rcx
mov -608(%rbp), %r10d
mov (%rcx), %rcx
cmp %r10d, %ecx
sete %al
movzbl %al, %ecx
test %ecx, %ecx
jz .AG16
mov -608(%rbp), %ecx
movq %rcx, %xmm15
mov -324(%rbp), %rcx
lea 68(%rcx), %rcx
mov (%rcx), %rcx
movq %rcx, %rsi
.section .rodata
.AG18:
.string "%d = %d\n"
.text
leaq .AG18(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
jmp .AG17
.AG16:
mov -608(%rbp), %ecx
movq %rcx, %xmm15
mov -324(%rbp), %rcx
lea 68(%rcx), %rcx
mov (%rcx), %rcx
movq %rcx, %rsi
.section .rodata
.AG19:
.string "%d != %d\n"
.text
leaq .AG19(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
.AG17:
mov $0, %rcx
mov %ecx, -292(%rbp)
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call init
mov %rax, %rcx
mov $3, %rcx
movq %rcx, %rsi
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rcx
mov $5, %rcx
movq %rcx, %rsi
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rcx
mov $7, %rcx
movq %rcx, %rsi
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rcx
mov $9, %rcx
movq %rcx, %rsi
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rcx
mov -292(%rbp), %ecx
leaq -292(%rbp), %rcx
movq %rcx, %rsi
mov -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_iter
mov %rax, %rcx
mov -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_rec
mov %rax, %rcx
.AG20:
mov -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call is_empty
mov %rax, %rcx
test %ecx, %ecx
setz %al
movzbl %al, %ecx
test %ecx, %ecx
jz .AG21
mov -300(%rbp), %rcx
leaq -300(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call pop
mov %rax, %rcx
movq %rcx, %rsi
.section .rodata
.AG22:
.string "%d->"
.text
leaq .AG22(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
jmp .AG20
.AG21:
.section .rodata
.AG23:
.string "||"
.text
leaq .AG23(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
mov -292(%rbp), %ecx
movq %rcx, %rsi
.section .rodata
.AG24:
.string "length: %d\n"
.text
leaq .AG24(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
mov -604(%rbp), %ecx
mov -584(%rbp), %rcx
mov (%rcx), %rcx
mov (%rcx), %rcx
mov (%rcx), %ecx
mov %ecx, -88(%rbp)
mov $2, %rcx
mov -608(%rbp), %r10d
imul %r10, %rcx
leaq -248(%rbp), %r10
leaq (%r10, %rcx, 4), %r10
mov -608(%rbp), %ecx
mov $4, %rbx
imul %rbx, %rcx
leaq (%r10, %rcx, 4), %r10
mov $100, %rcx
mov %rcx, (%r10)
mov %rcx, %r10
leaq -288(%rbp), %r10
mov $0, %rcx
leaq (%r10, %rcx, 4), %r10
mov -608(%rbp), %ecx
mov -608(%rbp), %ebx
add %ebx, %ecx
mov %ecx, (%r10)
mov %rcx, %r10
leaq -288(%rbp), %r10
mov $0, %rcx
leaq (%r10, %rcx, 4), %r10
mov $2, %rcx
mov -608(%rbp), %ebx
imul %rbx, %rcx
mov (%r10), %r10d
sub %rcx, %r10
leaq -288(%rbp), %rcx
mov -608(%rbp), %ebx
leaq (%rcx, %rbx, 4), %rcx
mov %r10, (%rcx)
mov %r10, %rcx
leaq -288(%rbp), %rcx
mov -608(%rbp), %r10d
leaq (%rcx, %r10, 4), %rcx
leaq -288(%rbp), %r10
mov (%rcx), %ecx
leaq (%r10, %rcx, 4), %r10
mov -608(%rbp), %ecx
mov (%r10), %r10d
mov %r10d, -608(%rbp)
mov %r10d, %ecx
mov -88(%rbp), %r10d
mov %ecx, -88(%rbp)
mov %ecx, %r10d
mov -608(%rbp), %r10d
mov $2, %rcx
movsx %r10d, %r10
movsx %ecx, %rcx
mov %r10, %rax
cqo
idiv %rcx
mov %rax, %r10
leaq -288(%rbp), %rcx
leaq (%rcx, %r10, 4), %rcx
leaq -288(%rbp), %r10
mov (%rcx), %ecx
leaq (%r10, %rcx, 4), %r10
mov -608(%rbp), %ecx
mov (%r10), %r10d
add %r10d, %ecx
mov -608(%rbp), %r10d
mov %ecx, -608(%rbp)
mov %ecx, %r10d
leaq -248(%rbp), %r10
mov -608(%rbp), %ecx
leaq (%r10, %rcx, 4), %r10
mov -88(%rbp), %ecx
leaq (%r10, %rcx, 4), %r10
leaq -248(%rbp), %rcx
mov -608(%rbp), %ebx
leaq (%rcx, %rbx, 4), %rcx
mov -88(%rbp), %ebx
leaq (%rcx, %rbx, 4), %rcx
mov (%rcx), %ecx
mov (%r10), %r10d
cmp %r10d, %ecx
sete %al
movzbl %al, %ecx
movq %rcx, %rsi
.section .rodata
.AG25:
.string "%d\n"
.text
leaq .AG25(%rip), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rcx
leaq -248(%rbp), %rcx
mov -608(%rbp), %r10d
leaq (%rcx, %r10, 4), %rcx
mov -88(%rbp), %r10d
leaq (%rcx, %r10, 4), %rcx
mov (%rcx), %ecx
mov %rcx, %rax
jmp RET_6
RET_6:
addq $608, %rsp
popq %rbp
ret
