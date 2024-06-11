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
mov %ebx, %ecx
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
movsx %ebx, %rbx
mov %rbx, %rax
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
test %rbx, %rbx
sete %al
movsx %al, %rbx
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
mov -24(%rbp), %rbx
mov $0, %rcx
mov %ecx, (%rbx)
mov %ecx, %ebx
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
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG2:
.string "[%d]->"
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
add %ecx, %ebx
mov -24(%rbp), %rcx
mov %ebx, (%rcx)
mov %ebx, %ecx
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
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG7:
.string "[%d]->"
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
subq $640, %rsp
mov $3, %rbx
mov %ebx, -640(%rbp)
mov -568(%rbp), %rbx
mov $3, %rcx
mov %rcx, -568(%rbp)
mov %rcx, %rbx
mov -568(%rbp), %rbx
leaq -568(%rbp), %rbx
mov -576(%rbp), %rcx
mov %rbx, -576(%rbp)
mov %rbx, %rcx
mov -576(%rbp), %rcx
mov -584(%rbp), %rbx
mov %rcx, -584(%rbp)
mov %rcx, %rbx
mov -588(%rbp), %ebx
mov $7, %rcx
mov %ecx, -588(%rbp)
mov %ecx, %ebx
mov -592(%rbp), %ebx
mov $8, %rcx
mov %ecx, -592(%rbp)
mov %ecx, %ebx
mov -588(%rbp), %ebx
leaq -588(%rbp), %rbx
mov -600(%rbp), %rcx
mov %rbx, -600(%rbp)
mov %rbx, %rcx
mov -600(%rbp), %rcx
leaq -600(%rbp), %rcx
mov -608(%rbp), %rbx
mov %rcx, -608(%rbp)
mov %rcx, %rbx
mov -608(%rbp), %rbx
leaq -608(%rbp), %rbx
mov -616(%rbp), %rcx
mov %rbx, -616(%rbp)
mov %rbx, %rcx
mov -568(%rbp), %rcx
mov -620(%rbp), %ebx
mov %ecx, -620(%rbp)
mov %ecx, %ebx
mov -620(%rbp), %ebx
leaq -620(%rbp), %rbx
mov -628(%rbp), %rcx
mov %rbx, -628(%rbp)
mov %rbx, %rcx
mov -620(%rbp), %ecx
mov -636(%rbp), %rbx
movsx %ecx, %rcx
mov %rcx, -636(%rbp)
mov %rcx, %rbx
mov $777, %rbx
mov %ebx, -484(%rbp)
mov -484(%rbp), %ebx
leaq -484(%rbp), %rbx
mov %rbx, -480(%rbp)
mov -480(%rbp), %rbx
leaq -480(%rbp), %rbx
mov %rbx, -472(%rbp)
mov -472(%rbp), %rbx
mov (%rbx), %rbx
mov $888, %rcx
mov %ecx, (%rbx)
mov %ecx, %ebx
mov -376(%rbp), %ebx
mov -484(%rbp), %ecx
mov %ecx, -376(%rbp)
mov %ecx, %ebx
mov -472(%rbp), %rbx
mov (%rbx), %rbx
mov -380(%rbp), %ecx
mov (%rbx), %ebx
mov %ebx, -380(%rbp)
mov %ebx, %ecx
mov -472(%rbp), %rcx
leaq -472(%rbp), %rcx
mov -540(%rbp), %rbx
mov %rcx, -540(%rbp)
mov %rcx, %rbx
mov -592(%rbp), %ebx
leaq -592(%rbp), %rbx
mov -600(%rbp), %rcx
mov %rbx, -600(%rbp)
mov %rbx, %rcx
mov -588(%rbp), %ecx
mov -592(%rbp), %ebx
add %ecx, %ebx
mov -592(%rbp), %ecx
mov %ebx, -592(%rbp)
mov %ebx, %ecx
mov -380(%rbp), %ecx
mov -376(%rbp), %ebx
movsx %ecx, %rcx
imul %rcx, %rbx
movsx %ebx, %rbx
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
mov -576(%rbp), %rbx
mov -640(%rbp), %ecx
mov (%rbx), %rbx
mov %ebx, -640(%rbp)
mov %ebx, %ecx
mov -640(%rbp), %ecx
movsx %ecx, %rcx
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
mov %rcx, -372(%rbp)
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
mov %rcx, -364(%rbp)
mov -364(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rcx
mov -364(%rbp), %rcx
movq %rcx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call strlen
mov %rax, %rcx
mov $2, %rbx
sub %rbx, %rcx
mov -364(%rbp), %rbx
leaq (%rbx, %rcx, 1), %rbx
mov -372(%rbp), %rcx
mov $1, %r10
leaq (%rcx, %r10, 1), %rcx
mov (%rcx), %cl
mov (%rbx), %bl
sub %bl, %cl
mov -372(%rbp), %rbx
movsx %cl, %rcx
leaq (%rbx, %rcx, 1), %rbx
mov (%rbx), %bl
movsx %bl, %rbx
movq %rbx, %xmm14
mov -372(%rbp), %rbx
mov $0, %rcx
leaq (%rbx, %rcx, 1), %rbx
mov (%rbx), %bl
movsx %bl, %rbx
movq %rbx, %xmm15
.section .rodata
.AG12:
.string "hello, world"
.text
leaq .AG12(%rip), %rbx
mov $2, %rcx
leaq (%rbx, %rcx, 1), %rbx
mov (%rbx), %bl
movsx %bl, %rbx
movq %rbx, %rsi
.section .rodata
.AG13:
.string "%c:%c:%c\n"
.text
leaq .AG13(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
.section .rodata
.AG14:
.string "\n"
.text
leaq .AG14(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -628(%rbp), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %r9
mov -576(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %r8
mov -568(%rbp), %rbx
movq %rbx, %xmm14
mov -576(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm15
mov -568(%rbp), %rbx
movq %rbx, %rsi
mov -372(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -628(%rbp), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %r9
mov -576(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %r8
mov -568(%rbp), %rbx
movq %rbx, %xmm14
mov -576(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm15
mov -568(%rbp), %rbx
movq %rbx, %rsi
mov -372(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -616(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov -576(%rbp), %rcx
mov (%rbx), %ebx
mov (%rcx), %rcx
add %ecx, %ebx
mov -372(%rbp), %rcx
movsx %ebx, %rbx
leaq (%rcx, %rbx, 1), %rcx
mov -588(%rbp), %ebx
mov $2, %r10
movsx %ebx, %rbx
imul %rbx, %r10
mov -600(%rbp), %rbx
mov (%rbx), %ebx
sub %r10d, %ebx
mov -372(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
mov (%rcx), %cl
sub %cl, %r10b
mov -568(%rbp), %rcx
mov $1, %rbx
add %rbx, %rcx
sub %cl, %r10b
mov -568(%rbp), %rcx
mov -372(%rbp), %rbx
leaq (%rbx, %rcx, 1), %rbx
movsx %r10b, %r10
leaq (%rbx, %r10, 1), %rbx
mov (%rbx), %bl
movsx %bl, %rbx
movq %rbx, %r9
mov -616(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov -576(%rbp), %r10
mov (%rbx), %ebx
mov (%r10), %r10
add %r10d, %ebx
mov -372(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsx %r10b, %r10
movq %r10, %r8
mov -568(%rbp), %r10
mov -372(%rbp), %rbx
leaq (%rbx, %r10, 1), %rbx
mov (%rbx), %bl
movsx %bl, %rbx
movq %rbx, %xmm14
mov -588(%rbp), %ebx
mov $2, %r10
movsx %ebx, %rbx
imul %rbx, %r10
mov -600(%rbp), %rbx
mov (%rbx), %ebx
sub %r10d, %ebx
mov -372(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 1), %r10
mov (%r10), %r10b
movsx %r10b, %r10
movq %r10, %xmm15
mov -372(%rbp), %r10
mov (%r10), %r10b
movsx %r10b, %r10
movq %r10, %rsi
.section .rodata
.AG15:
.string "Char:\t%c\t%c\t%c\t%c\t%c\n"
.text
leaq .AG15(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -540(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movsx %r10d, %r10
movq %r10, %r9
mov -576(%rbp), %r10
mov -568(%rbp), %rbx
mov (%r10), %r10
mov %r10, %rax
cqo
idiv %rbx
mov %rax, %r10
movq %r10, %r8
mov -568(%rbp), %r10
movq %r10, %xmm14
mov -588(%rbp), %r10d
movsx %r10d, %r10
movq %r10, %xmm15
mov -600(%rbp), %r10
mov -592(%rbp), %ebx
mov (%r10), %r10d
add %ebx, %r10d
movsx %r10d, %r10
movq %r10, %rsi
mov -372(%rbp), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
mov -616(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov (%r10), %r10d
movsx %r10d, %r10
movq %r10, %r9
mov -616(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov -568(%rbp), %rbx
mov (%r10), %r10d
movsx %r10d, %r10
imul %r10, %rbx
mov -576(%rbp), %r10
mov (%r10), %r10
imul %r10, %rbx
movq %rbx, %r8
mov -576(%rbp), %rbx
mov (%rbx), %rbx
movq %rbx, %xmm14
mov -576(%rbp), %rbx
mov (%rbx), %rbx
neg %rbx
movq %rbx, %xmm15
mov -616(%rbp), %rbx
mov (%rbx), %rbx
mov (%rbx), %rbx
mov (%rbx), %ebx
neg %ebx
mov -608(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10d
neg %r10d
movsx %ebx, %rbx
mov %rbx, %rax
cqo
idiv %r10d
mov %rax, %rbx
neg %rbx
movq %rbx, %rsi
mov -372(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
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
mov -456(%rbp), %ebx
movsx %r10b, %r10d
mov %r10d, %ebx
push %rcx
mov $76, %rcx
cld
lea -636(%rbp), %rsi
lea -456(%rbp), %rdi
rep movsb
pop %rcx
mov %r10d, %ebx
leaq -636(%rbp), %rbx
mov -464(%rbp), %r10
mov %rbx, -464(%rbp)
mov %rbx, %r10
mov -456(%rbp), %r10d
leaq -456(%rbp), %r10
mov %r10, -356(%rbp)
mov -464(%rbp), %r10
mov %r10, -348(%rbp)
mov -456(%rbp), %r10d
mov -436(%rbp), %r10
mov (%r10), %r10
mov (%r10), %r10
mov -640(%rbp), %ebx
mov (%r10), %r10d
mov %r10d, -640(%rbp)
mov %r10d, %ebx
mov -348(%rbp), %rbx
lea 60(%rbx), %rbx
mov (%rbx), %rbx
mov -640(%rbp), %r10d
mov (%rbx), %rbx
add %ebx, %r10d
mov -640(%rbp), %ebx
mov %r10d, -640(%rbp)
mov %r10d, %ebx
mov $80, %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call malloc
mov %rax, %rbx
mov %rbx, -340(%rbp)
mov -340(%rbp), %rbx
lea 68(%rbx), %rbx
mov -640(%rbp), %r10d
movsx %r10d, %r10
mov %r10, (%rbx)
mov %r10, %rbx
mov -340(%rbp), %rbx
lea 68(%rbx), %rbx
mov (%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG17:
.string "AA:%d\n"
.text
leaq .AG17(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -340(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call free
mov %rax, %rbx
mov -356(%rbp), %rbx
lea 60(%rbx), %rbx
mov (%rbx), %rbx
mov -640(%rbp), %r10d
mov (%rbx), %rbx
cmp %r10d, %ebx
sete %al
movsx %al, %ebx
test %ebx, %ebx
jz .AG18
mov -640(%rbp), %ebx
movsx %ebx, %rbx
movq %rbx, %xmm15
mov -356(%rbp), %rbx
lea 68(%rbx), %rbx
mov (%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG20:
.string "%d = %d\n"
.text
leaq .AG20(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
jmp .AG19
.AG18:
mov -640(%rbp), %ebx
movsx %ebx, %rbx
movq %rbx, %xmm15
mov -356(%rbp), %rbx
lea 68(%rbx), %rbx
mov (%rbx), %rbx
movq %rbx, %rsi
.section .rodata
.AG21:
.string "%d != %d\n"
.text
leaq .AG21(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
.AG19:
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call init
mov %rax, %rbx
mov $3, %rbx
movq %rbx, %rsi
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov $5, %rbx
neg %rbx
movq %rbx, %rsi
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov $7, %rbx
neg %rbx
neg %rbx
movq %rbx, %rsi
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov $9, %rbx
movq %rbx, %rsi
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call push
mov %rax, %rbx
mov -332(%rbp), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG22:
.string "[%d]->"
.text
leaq .AG22(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -332(%rbp), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG23:
.string "[%d]->"
.text
leaq .AG23(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -332(%rbp), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG24:
.string "[%d]->"
.text
leaq .AG24(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -332(%rbp), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 0(%rbx), %rbx
mov (%rbx), %rbx
lea 8(%rbx), %rbx
mov (%rbx), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG25:
.string "[%d]->||\n"
.text
leaq .AG25(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -324(%rbp), %ebx
leaq -324(%rbp), %rbx
movq %rbx, %rsi
mov -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_iter
mov %rax, %rbx
mov -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call print_list_rec
mov %rax, %rbx
.AG26:
mov -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call is_empty
mov %rax, %rbx
test %ebx, %ebx
sete %al
movsx %al, %ebx
test %ebx, %ebx
jz .AG27
mov -332(%rbp), %rbx
leaq -332(%rbp), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call pop
mov %rax, %rbx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG28:
.string "[%d]->"
.text
leaq .AG28(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
jmp .AG26
.AG27:
.section .rodata
.AG29:
.string "||"
.text
leaq .AG29(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call puts
mov %rax, %rbx
mov -324(%rbp), %ebx
movsx %ebx, %rbx
movq %rbx, %rsi
.section .rodata
.AG30:
.string "length: %d\n"
.text
leaq .AG30(%rip), %rbx
movq %rbx, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %rbx
mov -640(%rbp), %ebx
mov $6, %r10
movsx %ebx, %rbx
mov %rbx, %rax
cqo
idiv %r10
mov %rax, %rbx
mov %ebx, -80(%rbp)
mov -640(%rbp), %ebx
mov -80(%rbp), %r10d
add %r10d, %ebx
mov %ebx, -76(%rbp)
mov -640(%rbp), %ebx
mov $3, %r10
movsx %ebx, %rbx
mov %rbx, %rax
cqo
idiv %r10
mov %rax, %rbx
leaq -240(%rbp), %r10
leaq (%r10, %rbx, 4), %r10
mov -640(%rbp), %ebx
mov $9, %rcx
movsx %ebx, %rbx
mov %rbx, %rax
cqo
idiv %rcx
mov %rax, %rbx
leaq (%r10, %rbx, 4), %r10
mov -76(%rbp), %ebx
mov %ebx, (%r10)
mov %ebx, %r10d
mov -640(%rbp), %r10d
mov -640(%rbp), %ebx
xor %ebx, %r10d
leaq -320(%rbp), %rbx
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
mov -640(%rbp), %r10d
mov %r10d, (%rbx)
mov %r10d, %ebx
mov -640(%rbp), %ebx
test %ebx, %ebx
sete %al
movsx %al, %ebx
leaq -320(%rbp), %r10
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov -640(%rbp), %ebx
mov (%r10), %r10d
sub %ebx, %r10d
leaq -320(%rbp), %rbx
mov -640(%rbp), %ecx
movsx %ecx, %rcx
leaq (%rbx, %rcx, 4), %rbx
mov %r10d, (%rbx)
mov %r10d, %ebx
leaq -320(%rbp), %rbx
mov -640(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
leaq -320(%rbp), %r10
mov (%rbx), %ebx
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov $9, %rbx
mov (%r10), %r10d
movsx %r10d, %r10
mov %r10, %rax
cqo
idiv %rbx
mov %rax, %r10
mov -640(%rbp), %ebx
mov %r10d, -640(%rbp)
mov %r10d, %ebx
mov -80(%rbp), %r10d
mov %ebx, -80(%rbp)
mov %ebx, %r10d
mov $3, %r10
mov -80(%rbp), %ebx
movsx %ebx, %rbx
imul %rbx, %r10
mov -640(%rbp), %ebx
mov %r10d, -640(%rbp)
mov %r10d, %ebx
leaq -240(%rbp), %rbx
mov -640(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
mov -80(%rbp), %r10d
movsx %r10d, %r10
leaq (%rbx, %r10, 4), %rbx
leaq -240(%rbp), %r10
mov -640(%rbp), %ecx
movsx %ecx, %rcx
leaq (%r10, %rcx, 4), %r10
mov -80(%rbp), %ecx
movsx %ecx, %rcx
leaq (%r10, %rcx, 4), %r10
mov (%r10), %r10d
mov (%rbx), %ebx
cmp %ebx, %r10d
sete %al
movsx %al, %r10d
movsx %r10d, %r10
movq %r10, %rsi
.section .rodata
.AG31:
.string "%d\n"
.text
leaq .AG31(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
leaq -240(%rbp), %r10
mov -640(%rbp), %ebx
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov -80(%rbp), %ebx
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov (%r10), %r10d
movsx %r10d, %r10
movq %r10, %rsi
.section .rodata
.AG32:
.string "Val:%d\n"
.text
leaq .AG32(%rip), %r10
movq %r10, %rdi
movq %xmm14, %rcx
movq %xmm15, %rdx
call printf
mov %rax, %r10
leaq -240(%rbp), %r10
mov -640(%rbp), %ebx
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov -80(%rbp), %ebx
movsx %ebx, %rbx
leaq (%r10, %rbx, 4), %r10
mov (%r10), %r10d
mov %r10, %rax
jmp RET_6
RET_6:
addq $640, %rsp
popq %rbp
ret
