// CodeGenerator.h

#ifndef _ABSTRACT_SYNTAX_TREE_H
    #include "../libs/AbstractSyntaxTree.h"
#endif

#ifndef _STACK_H
    #include "../libs/Stack.h"
#endif

#ifndef _TYPE_SYSTEM_H
    #include "../libs/TypeSystem.h"
#endif

#ifndef _STDARG_H
    #include <stdarg.h>
#endif

#define REGISTER_NAMES {NULL, \ 
                        "al",   "bl",   "cl",   "r10b", "r11b", "r12b", "r13b", "r14b", "r15b", \
                        "ax",   "bx",   "cx",   "r10w", "r11w", "r12w", "r13w", "r14w", "r15w", \
                        "eax",  "ebx",  "ecx",  "r10d", "r11d", "r12d", "r13d", "r14d", "r15d", \
                        "rax",  "rbx",  "rcx",  "r10",  "r11",  "r12",  "r13",  "r14",  "r15"}
#define REGISTERS_NUM 9

typedef struct
{
    Stack *availableRegisters;
    LinearLinkedListNode *usedRegisters;
    char *registers[sizeof((char*[])REGISTER_NAMES) / sizeof(char*)];
    short currentMemoryOffset;
    void (*Emit)(void *stream, char *buffer, va_list args);
    void *stream;
} CodeGenerator;