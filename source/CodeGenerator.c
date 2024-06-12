/// CodeGenerator.c

#include "CodeGenerator.h"

#include <stdarg.h>

#define NONE 0
#define EAX 1
#define EBX 2
#define ECX 3
#define R10D 4
#define R11D 5
#define R12D 6
#define R13D 7
#define R14D 8
#define R15D 9

#define BYTE_SIZE 1
#define WORD_SIZE 2
#define DWORD_SIZE 4
#define QWORD_SIZE 8

#define BASE_REGISTER(reg) (((Register)reg) % REGISTERS_NUM)
#define REGSITER_BY_SIZE(reg, size) (BASE_REGISTER(reg) + REGISTERS_NUM * __builtin_ctzl(size))

#define FULL_REGISTER(reg) (REGSITER_BY_SIZE(reg, QWORD_SIZE))

#define ALIGN(n, base) ((base) * ((n) / (base) + !!((n) % ((base)))))
#define STACK_ALIGNMENT 16

typedef unsigned short Register;


int LabelAst(AbstractSyntaxTreeNode *astRoot, BOOL left);
void SethiUllman(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, BOOL left);

void Emit(CodeGenerator *generator, char *buffer, ...)
{
    va_list args;

    va_start(args, buffer);

    generator->Emit(generator->stream, buffer, args);

    va_end(args);
}

void InitCodeGenerator(CodeGenerator *generator, void (*Emit)(char *buffer, void *stream), void *stream)
{
    Register currentRegister;

    *generator = (CodeGenerator){.registers = REGISTER_NAMES};

    generator->Emit = Emit;
    generator->stream = stream;
    generator->currentMemoryOffset = ZERO;

    generator->availableRegisters = malloc(sizeof(Stack));
    InitStack(generator->availableRegisters);

    InitLinearLinkedList(&generator->usedRegisters);

    for (currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    {
        PushStack(generator->availableRegisters, (void *)currentRegister);
    }
}

void FreeCodeGenerator(CodeGenerator *generator)
{
    while (!IsEmptyStack(generator->availableRegisters))
    {
        PopStack(generator->availableRegisters);
    }

    EmptyLinearLinkedList(&generator->usedRegisters, NULL);

    free(generator->availableRegisters);
}

Register GetRegister(CodeGenerator *generator)
{
    PushLinearLinkedList(&generator->usedRegisters);

    return ((Register)(generator->usedRegisters->info = PopStack(generator->availableRegisters)));
}

void FreeRegister(CodeGenerator *generator, Register reg)
{
    reg = BASE_REGISTER(reg);

    PushStack(generator->availableRegisters, reg);
    PopLinearLinkedList(&generator->usedRegisters);
}

void EmitMemoryAddress(CodeGenerator *generator, short memoryAddress)
{
    Emit(generator, "%d(%%rbp)", memoryAddress);
}

void EmitRegister(CodeGenerator *generator, Register reg)
{
    Emit(generator, "%%%s", generator->registers[reg]);
}

BOOL EmitRegisterOrAddress(CodeGenerator *generator, AbstractSyntaxTreeNode *node)
{
    if (node->reg)
    {
        EmitRegister(generator, node->reg);
        return (node->reg >= REGISTERS_NUM);
    }
    else
    {
        if (!((Symbol *)node->info)->memoryAddress)
            Emit(generator, "$%s", ((Symbol *)node->info)->name);
        else
            EmitMemoryAddress(generator, ((Symbol *)node->info)->memoryAddress);

        return (((Symbol*)node->info)->_type && !!((Type*)((Symbol*)node->info)->_type)->baseType);
    }
}
static int currentBranchNum = 0;

int GetLabel(CodeGenerator *generator)
{
    return currentBranchNum++;
}

void EmitLabel(CodeGenerator *generator, int id)
{
    Emit(generator, ".AG%d:\n", id);
}

void GenerateIncrement(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *expression = astNode->childrenManager->nextNode->info;

    expression->GenerationFunction(codeGenerator, expression);

    Emit(codeGenerator, "mov ");
    EmitMemoryAddress(codeGenerator, ((Symbol*)expression->info)->memoryAddress);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, expression->reg);
    Emit(codeGenerator, "\n");

    Emit(codeGenerator, "incl ");
    EmitMemoryAddress(codeGenerator, ((Symbol*)expression->info)->memoryAddress);
    Emit(codeGenerator, "\n");

    astNode->reg = expression->reg;
}

void GenerateFor(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *init = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *step = astNode->childrenManager->nextNode->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->info;

    int bodyLabel = GetLabel(codeGenerator);
    int endLabel = GetLabel(codeGenerator);

    if (init->GenerationFunction)
        init->GenerationFunction(codeGenerator, init);

    EmitLabel(codeGenerator, bodyLabel);
    condition->GenerationFunction(codeGenerator, condition);

    Emit(codeGenerator, "test ");
    EmitRegister(codeGenerator, condition->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, condition->reg);
    Emit(codeGenerator, "\n");

    Emit(codeGenerator, "jz .AG%d\n", endLabel);
    body->GenerationFunction(codeGenerator, body);

    if (step != body)
        step->GenerationFunction(codeGenerator, step);

    Emit(codeGenerator, "jmp .AG%d\n", bodyLabel);
    EmitLabel(codeGenerator, endLabel);
}

void GenerateIf(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *elseBody = astNode->childrenManager->info;

    condition->GenerationFunction(codeGenerator, condition);

    Emit(codeGenerator, "test ");
    EmitRegisterOrAddress(codeGenerator, condition);
    Emit(codeGenerator, ", ");
    EmitRegisterOrAddress(codeGenerator, condition);
    Emit(codeGenerator, "\n");

    int falseLabel = GetLabel(codeGenerator);
    int continueLabel = GetLabel(codeGenerator);
    
    if (elseBody != body)
    {
        Emit(codeGenerator, "jz .AG%d\n", falseLabel);
        body->GenerationFunction(codeGenerator, body);
        Emit(codeGenerator, "jmp .AG%d\n", continueLabel);
        EmitLabel(codeGenerator, falseLabel);
        elseBody->GenerationFunction(codeGenerator, elseBody);
    }
    else
    {
        Emit(codeGenerator, "jz .AG%d\n", continueLabel);
        body->GenerationFunction(codeGenerator, body);
    }

    EmitLabel(codeGenerator, continueLabel);
}

#ifndef _TYPE_SYSTEM_H
    #include "../libs/TypeSystem.h"
#endif

void CastBySize(CodeGenerator *generator, Register *reg, unsigned char size)
{
    Register new = REGSITER_BY_SIZE(*reg, size);

    if (new > *reg)
    {
        Emit(generator, "movsx ");
        EmitRegister(generator, *reg);
        Emit(generator, ", ");
        EmitRegister(generator, new);
        Emit(generator, "\n");
    }

    *reg = new;
}

void GenerateStringLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    int label = GetLabel(codeGenerator);

    astNode->reg = astNode->reg ? FULL_REGISTER(astNode->reg) : FULL_REGISTER(GetRegister(codeGenerator));

    Emit(codeGenerator, ".section .rodata\n");
    EmitLabel(codeGenerator, label);
    Emit(codeGenerator, ".string %s\n.text\n", ((Symbol*)astNode->info)->name);
    Emit(codeGenerator, "leaq .AG%d(%%rip), ", label);
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void GenerateFloatLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    float val = atof(((Symbol*)astNode->info)->name);

    /*
        movabs $0x40200000, %rax
        movq %rax, %xmm0
        cvttss2si %xmm0, %ebx
    */

    Emit(codeGenerator, "mov $0x%08x, ", *((unsigned int*)&val));
    // Emit(codeGenerator, "movq %%rax, %%xmm0\ncvttss2si %%xmm0, ");
    EmitRegister(codeGenerator, astNode->reg = astNode->reg ? astNode->reg : GetRegister(codeGenerator));
    Emit(codeGenerator, "\n");

}

void GenerateIntegerLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    astNode->reg = astNode->reg ? astNode->reg : GetRegister(codeGenerator);

    // astNode->reg = CastBySize(astNode->reg, ((Type*)((Symbol*)astNode->info)->_type)->size);

    Emit(codeGenerator, "mov $%s, ", ((Symbol*)astNode->info)->name);
    EmitRegister(codeGenerator, (astNode->reg = REGSITER_BY_SIZE(astNode->reg, ((Type*)astNode->type)->size)));
    Emit(codeGenerator, "\n");
}

void GenerateSymbol(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    if (((Type*)astNode->type)->type == STRUCT_TYPE)
    {
        astNode->reg = GetRegister(codeGenerator);
        return;
    }

    if (((Type*)((Symbol*)astNode->info)->_type)->type == ARRAY_TYPE)
    {
        Emit(codeGenerator, "leaq %d(%%rbp), ", ((Symbol*)astNode->info)->memoryAddress);
    }
    else
    {
        Emit(codeGenerator, "mov ");

        if (!strcmp(((Symbol*)astNode->info)->name, "sum_mat"))
            Emit(codeGenerator, "sum_mat(%%rip)");
        else
            EmitRegisterOrAddress(codeGenerator, astNode);

        Emit(codeGenerator, ", ");
    }

    astNode->reg = astNode->reg ? astNode->reg : GetRegister(codeGenerator);

    if (((Type*)astNode->type)->type != ARRAY_TYPE)
        astNode->reg = REGSITER_BY_SIZE(astNode->reg, ((Type*)astNode->type)->size);
    else
        astNode->reg = FULL_REGISTER(astNode->reg);

    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void GenerateParameter(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Symbol *decl = astNode->info;
    Type *type = decl->_type;

    decl->memoryAddress = ((CodeGenerator *)codeGenerator)->currentMemoryOffset;   

    ((CodeGenerator *)codeGenerator)->currentMemoryOffset += type->size;
}

void GenerateDeclaration(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *init = astNode->childrenManager ? astNode->childrenManager->info : NULL;

    Symbol *decl = astNode->info;
    Type *type = astNode->type;

    if (init)
        init->GenerationFunction(codeGenerator, init);

    decl->memoryAddress = ((CodeGenerator *)codeGenerator)->currentMemoryOffset;   

    ((CodeGenerator *)codeGenerator)->currentMemoryOffset += type->size;

    if (init)
    {
        if (init->lvalue)
        {
            Load(codeGenerator, init);
        }

        CastBySize(codeGenerator, &init->reg, type->size);

        Emit(codeGenerator, "mov ");
        EmitRegister(codeGenerator, init->reg);
        Emit(codeGenerator, ", ");
        EmitMemoryAddress(codeGenerator, decl->memoryAddress);
        Emit(codeGenerator, "\n");

        astNode->reg = init->reg;
    }
    // if (decl->_type && ((Type*)decl->_type)->baseType)
    // {
    //     ((CodeGenerator *)codeGenerator)->currentMemoryOffset += 4;
    // }
}

void GenerateAddition(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(codeGenerator, left);
    }

    if (right->lvalue)
    {
        Load(codeGenerator, right);
    }

    if (((Type*)left->type)->baseType)
    {
        Type *base;

        CastBySize(codeGenerator, &right->reg, QWORD_SIZE);

        for (base = ((Type*)left->type)->baseType; base; base = base->baseType)
        {
            Emit(codeGenerator, "imul $%d, ", base->size);
            EmitRegister(codeGenerator, right->reg);
            Emit(codeGenerator, "\n");
        }

        Emit(codeGenerator, "leaq (");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, right->reg);
        Emit(codeGenerator, "), ");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, "\n");

        // Emit(codeGenerator, "leaq (");
        // EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        // Emit(codeGenerator, ", ");
        // EmitRegister(codeGenerator, right->reg);
        // Emit(codeGenerator, ", %d), ", ((Type*)left->type)->baseType->size);
        // EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        // Emit(codeGenerator, "\n");
    }
    else
    {
        if (right->reg)
            CastBySize(codeGenerator, &right->reg, ((Type*)left->type)->size);

        Emit(codeGenerator, "add ");
        EmitRegisterOrAddress(codeGenerator, right);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, left->reg);
        Emit(codeGenerator, "\n");
    }

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateSubtraction(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(codeGenerator, left);
    }

    if (right->lvalue)
    {
        Load(codeGenerator, right);
    }

    if (((Type*)left->type)->baseType)
    {
        Emit(codeGenerator, "neg ");
        EmitRegister(codeGenerator, FULL_REGISTER(right->reg));
        Emit(codeGenerator, "\nleaq (");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, FULL_REGISTER(right->reg));
        Emit(codeGenerator, ", %d), ", ((Type*)left->type)->baseType->size);
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, "\n");
    }
    else
    {
        if (right->reg)
            CastBySize(codeGenerator, &right->reg, ((Type*)left->type)->size);

        Emit(codeGenerator, "sub ");
        EmitRegisterOrAddress(codeGenerator, right);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, left->reg);
        Emit(codeGenerator, "\n");
    }

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateMult(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(codeGenerator, left);
    }

    if (right->lvalue)
    {
        Load(codeGenerator, right);
    }

    if (right->reg)
        CastBySize(codeGenerator, &right->reg, QWORD_SIZE);

    Emit(codeGenerator, "imul ");
    EmitRegister(codeGenerator, right->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, REGSITER_BY_SIZE(left->reg, QWORD_SIZE));
    Emit(codeGenerator, "\n");


    // Emit(codeGenerator, "mov ");
    // EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    // Emit(codeGenerator, ", %%rax\nimul ");

    // EmitRegisterOrAddress(codeGenerator, right);

    // Emit(codeGenerator, "\nmov %%rax, ");
    // EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    // Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateDereference(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    AbstractSyntaxTreeNode *operand = astRoot->childrenManager->info;

    if (((Type*)operand->type)->baseType->type == ARRAY_TYPE) astRoot->lvalue = TRUE;

    astRoot->reg = REGSITER_BY_SIZE(operand->reg, QWORD_SIZE);

    if (operand->GenerationFunction == GenerateDereference)
    {
        Emit(generator, "mov (");
        EmitRegister(generator, astRoot->reg);
        Emit(generator, "), ");
        EmitRegister(generator, astRoot->reg);
        Emit(generator, "\n");
    }
    
}

void GenerateArithmeticExpression(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *expression = astNode->childrenManager->info;

    GenerateExpression(codeGenerator, expression);
    astNode->reg = expression->reg;
    astNode->lvalue = expression->lvalue;
    astNode->type = expression->type;
}

void GenerateExpression(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    LabelAst(astRoot, FALSE);
    SethiUllman(generator, astRoot, FALSE);
    FreeRegister(generator, astRoot->reg);
}

void Load(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    astNode = astNode->GenerationFunction == GenerateArithmeticExpression ?
        astNode->childrenManager->info : astNode;
    
    if (astNode->GenerationFunction != GenerateDereference)
    {
        return;
    }

    if (((Type*)astNode->type)->type == STRUCT_TYPE ||
        ((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        return;
    }

    Emit(codeGenerator, "mov (");
    EmitRegister(codeGenerator, astNode->reg);

    CastBySize(codeGenerator, &astNode->reg, ((Type*)astNode->type)->size);

    Emit(codeGenerator, "), ");
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void Store(void *codeGenerator, AbstractSyntaxTreeNode *source, AbstractSyntaxTreeNode *dest)
{
    if (source->reg)
        CastBySize(codeGenerator, &source->reg, ((Type*)dest->type)->size);

    Emit(codeGenerator, "mov ");
    EmitRegisterOrAddress(codeGenerator, source);
    Emit(codeGenerator, ", ");

    if (dest->GenerationFunction == GenerateDereference)
    {
        Emit(codeGenerator, "("); 
        EmitRegister(codeGenerator, FULL_REGISTER(dest->reg)); 
        Emit(codeGenerator, ")");
    }
    else if (((Type*)dest->type)->type == STRUCT_TYPE)
    {
        EmitRegisterOrAddress(codeGenerator, dest);
        Emit(codeGenerator, "\npush %%rcx\nmov $%d, %%rcx\ncld\n", ((Type*)source->type)->size);
        Emit(codeGenerator, "lea %d(%%rbp), %%rsi\n", ((Symbol*)source->info)->memoryAddress);
        Emit(codeGenerator, "lea %d(%%rbp), %%rdi\n", ((Symbol*)dest->info)->memoryAddress);
        Emit(codeGenerator, "rep movsb\npop %%rcx");
    }
    else
    {
        EmitMemoryAddress(codeGenerator, ((Symbol*)dest->info)->memoryAddress);
    }

    Emit(codeGenerator, "\n");
}

void GenerateAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Type *temp = left->type;

    Load(codeGenerator, right);
    Store(codeGenerator, right, left);

    if (left->reg)
    {
        if (right->reg)
            CastBySize(codeGenerator, &right->reg, temp->size);

        left->reg = REGSITER_BY_SIZE(left->reg, temp->size);

        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, right);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, left->reg);
        Emit(codeGenerator, "\n");
    }

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateReference(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *operand = astNode->childrenManager->info;

    astNode->reg = FULL_REGISTER(operand->reg);
    
    Emit(generator, "leaq %d(%%rbp), ", ((Symbol*)operand->info)->memoryAddress);
    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

void GenerateNeg(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *operand = astNode->childrenManager->info;

    if (operand->lvalue)
    {
        Load(generator, operand);
    }
    
    if (operand->type && ((Type*)operand->type)->type == FLOAT_TYPE)
    {
        Emit(generator, "xor $0x80000000, ");
        EmitRegister(generator, operand->reg);
        Emit(generator, "\n");
    }
    else
    {
        Emit(generator, "neg ");
        EmitRegister(generator, operand->reg);
        Emit(generator, "\n");
    }
    // if (!IS_FULL_REGISTER(operand->reg))
    // {
    //     Emit(generator, "movsx ");
    //     EmitRegister(generator, operand->reg);
    //     Emit(generator, ", ");
    //     EmitRegister(generator, FULL_REGISTER(operand->reg));
    //     Emit(generator, "\n");
    // }

    astNode->reg = operand->reg;
}

void GenerateAdditionAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{

}

void GenerateDivision(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(codeGenerator, left);
    }

    if (right->lvalue)
    {
        Load(codeGenerator, right);
    }

    CastBySize(codeGenerator, &left->reg, QWORD_SIZE);

    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, ", %%rax\ncqo\nidiv ");

    EmitRegisterOrAddress(codeGenerator, right);

    Emit(codeGenerator, "\nmov %%rax, ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateStructAccess(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *structNode = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *fieldNode = astNode->childrenManager->info;

    Field *field = fieldNode->field;
    ((Symbol*)astNode->info)->memoryAddress = ((Symbol*)structNode->info)->memoryAddress + field->offset;

    astNode->type = field->type;

    if (structNode->GenerationFunction == GenerateDereference)
    {
        astNode->reg = structNode->reg;
        astNode->GenerationFunction = GenerateDereference;
        Emit(codeGenerator, "lea %d(", field->offset);
        EmitRegister(codeGenerator, structNode->reg);
        Emit(codeGenerator, ")");
    }
    else
    {
        astNode->reg = REGSITER_BY_SIZE(structNode->reg, field->type->size);
        Emit(codeGenerator, "mov ");
        EmitMemoryAddress(codeGenerator, ((Symbol*)astNode->info)->memoryAddress);
        astNode->lvalue = FALSE;
    }

    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void GenerateReturn(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Register result = REGSITER_BY_SIZE(EAX, QWORD_SIZE);
    AbstractSyntaxTreeNode *value;
    
    if (astNode->childrenManager)
    {
        value = astNode->childrenManager->info;
        value->GenerationFunction(codeGenerator, value);

        if (value->lvalue)
            Load(codeGenerator, value);

        if (value->reg)
            CastBySize(codeGenerator, &value->reg, QWORD_SIZE);

        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, value);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, result);
    }

    Emit(codeGenerator, "\njmp RET_%d\n", astNode->label);
}

int LabelAst(AbstractSyntaxTreeNode *astRoot, BOOL left)
{
    int leftL = 0;
    int rightL = 0;

    if (!astRoot->childrenManager)
    {
        astRoot->label = left;
        return left;
    }

    // for (LinearLinkedListNode *p = astRoot->childrenManager->nextNode; p; p = p->nextNode)
    {
        leftL = LabelAst(astRoot->childrenManager->nextNode->info, TRUE);

        if (astRoot->childrenManager)
            rightL = LabelAst(astRoot->childrenManager->info, FALSE);

        astRoot->label = MAX(leftL, rightL);
        astRoot->label += leftL == rightL;
    }

    return astRoot->label;
}

void GenerateCall(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;

    char *paramsRegisters[] = {"rdi", "rsi", "xmm15", "xmm14", "r8", "r9"};
    char *floatRegisters[] = {"xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7"};
    char **currentRegister = paramsRegisters;
    char **currentFloatRegister = floatRegisters;
    char *reg;
    unsigned int stackSize = ZERO;

    CodeGenerator *gen = generator;

    Stack temp; InitStack(&temp);
    Stack params; InitStack(&params);

    for (LinearLinkedListNode *ptr = gen->usedRegisters; ptr; ptr = ptr->nextNode)
    {
        Emit(generator, "pushq ");
        EmitRegister(generator, FULL_REGISTER(ptr->info));
        Emit(generator, "\n");

        PushStack(&temp, ptr->info);
        stackSize += 8;
    }

    stackSize %= STACK_ALIGNMENT;

    if (stackSize)
        Emit(generator, "subq $%d, %%rsp\n", stackSize);
    
    if (astRoot->childrenManager)
    {
        CircularLinearLinkedListNode *parameters = ((AbstractSyntaxTreeNode*)astRoot->childrenManager->info)->childrenManager->nextNode;
        AbstractSyntaxTreeNode *currentParameter;

        do
        {
            currentParameter = parameters->info;
            PushStack(&params, currentParameter);
            parameters = parameters->nextNode;
            currentRegister++;
        }
        while (parameters != ((AbstractSyntaxTreeNode*)astRoot->childrenManager->info)->childrenManager->nextNode);

        while (!IsEmptyStack(&params))
        {
            currentParameter = PopStack(&params);
            GenerateExpression(generator, currentParameter);

            if (currentParameter->lvalue)
                Load(generator, currentParameter);

            if (currentParameter->type && ((Type*)currentParameter->type)->type == FLOAT_TYPE)
            {
                reg = *(currentFloatRegister++);
            }
            else
            {
                reg = *(--currentRegister);
            }

            CastBySize(generator, &currentParameter->reg, QWORD_SIZE);
            Emit(generator, "movq ");
            EmitRegister(generator, currentParameter->reg);
            Emit(generator, ", %%%s\n", reg);

            if (currentParameter->type && ((Type*)currentParameter->type)->type == FLOAT_TYPE)
            {
                Emit(generator, "cvtss2sd %%%s, %%%s\n", reg, reg);
            }
        }
        
    }

    Emit(generator, "movq %%xmm14, %%rcx\nmovq %%xmm15, %%rdx\ncall %s\n", function->name);
    
    if (stackSize)
        Emit(generator, "add $%d, %%rsp\n", stackSize);

    while (!IsEmptyStack(&temp))
    //for (LinearLinkedListNode *ptr = gen->usedRegisters; ptr; ptr = ptr->nextNode)
    {
        Emit(generator, "popq ");
        EmitRegister(generator, FULL_REGISTER(PopStack(&temp)));
        Emit(generator, "\n");
    }

    astRoot->reg = GetRegister(generator);
    astRoot->reg = REGSITER_BY_SIZE(astRoot->reg, ((Type*)astRoot->type)->size);

    Emit(generator, "mov %%rax, ");
    EmitRegister(generator, FULL_REGISTER(astRoot->reg));
    Emit(generator, "\n");
}

void SethiUllman(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, BOOL left)
{
    if (!astRoot->childrenManager)
    {
        if (astRoot->GenerationFunction)
            astRoot->GenerationFunction(generator, astRoot);
        return;
    }

    AbstractSyntaxTreeNode *leftT = astRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *rightT = astRoot->childrenManager->info;

    if (astRoot->GenerationFunction == GenerateCall)
    {
        astRoot->GenerationFunction(generator, astRoot);
        return;
    }

    if (astRoot->childrenManager && !((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->childrenManager)
    {
        SethiUllman(generator, astRoot->childrenManager->nextNode->info, TRUE);

        if (astRoot->childrenManager != astRoot->childrenManager->nextNode && 
            ((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction)
                ((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction(generator, astRoot->childrenManager->info);

        astRoot->GenerationFunction(generator, astRoot);

        return;
    }

    AbstractSyntaxTreeNode *maxT = leftT->label > rightT->label ? leftT : rightT;
    
    SethiUllman(generator, maxT, (maxT == leftT));

    if (leftT != rightT)
        SethiUllman(generator, (maxT == leftT ? rightT : leftT), (maxT != leftT));

    if (astRoot->GenerationFunction)
        astRoot->GenerationFunction(generator, astRoot);
}

void GenerateStatements(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    CircularLinearLinkedListNode *p = astRoot->childrenManager->nextNode;

    do
    {
        if (((AbstractSyntaxTreeNode *)p->info)->GenerationFunction)
            ((AbstractSyntaxTreeNode *)p->info)->GenerationFunction(generator, p->info);

        if (((AbstractSyntaxTreeNode *)p->info)->GenerationFunction == GenerateCall)
            FreeRegister(generator, ((AbstractSyntaxTreeNode *)p->info)->reg);

        p = p->nextNode;
    } while (p != astRoot->childrenManager->nextNode);
}

void EmitFunctionStart(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, unsigned int size)
{
    Symbol *function = astRoot->info;

    Emit(generator, ".text\n.globl %s\n.type %s, @function\n%s:\n", function->name, function->name, function->name);
    Emit(generator, "pushq %%rbp\nmovq %%rsp, %%rbp\nsubq $%d, %%rsp\n", size);

    char *paramsRegisters[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    char **currentRegister = paramsRegisters;

    if (astRoot->childrenManager != astRoot->childrenManager->nextNode)
    {
        CircularLinearLinkedListNode *parameters = ((AbstractSyntaxTreeNode*)astRoot->childrenManager->nextNode->info)->childrenManager->nextNode;
        AbstractSyntaxTreeNode *currentParameter;

        do
        {
            currentParameter = parameters->info;
            
            GenerateParameter(generator, currentParameter);

            Emit(generator, "mov ");
            Emit(generator, "%%%s, ", *currentRegister);
            EmitMemoryAddress(generator, ((Symbol*)currentParameter->info)->memoryAddress);
            Emit(generator, "\n");

            parameters = parameters->nextNode;
            currentRegister++;
        }
        while (parameters != ((AbstractSyntaxTreeNode*)astRoot->childrenManager->nextNode->info)->childrenManager->nextNode);
    }
}

void EmitFunctionEnd(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, unsigned char currentFunction, unsigned int size)
{
    Symbol *function = astRoot->info;

    Emit(generator, "RET_%d:\naddq $%d, %%rsp\npopq %%rbp\nret\n", currentFunction, size);
}

void GenerateMod(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "xor %%rdx, %%rdx\n");
    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, ", %%rax\nidiv ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, "\nmov %%rdx, ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateLogNot(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *operand = astNode->childrenManager->nextNode->info;

    Emit(generator, "test ");
    EmitRegister(generator, operand->reg);
    Emit(generator, ", ");
    EmitRegister(generator, operand->reg);
    Emit(generator, "\nsete %%al\nmovsx %%al, ");
    EmitRegister(generator, operand->reg);
    Emit(generator, "\n");

    astNode->reg = operand->reg;
}

void GenerateLT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(generator, left);
    }

    if (right->lvalue)
    {
        Load(generator, right);
    }

    if (right->type)
        CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegister(generator, right->reg);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetl %%al\nmovsx %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateGT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(generator, left);
    }

    if (right->lvalue)
    {
        Load(generator, right);
    }

    if (right->type)
        CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegister(generator, right->reg);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetg %%al\nmovsx %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateLSHIFT(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "shlx ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateRSHIFT(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "sarx ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateLE(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetle %%al\nmovzbl %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateGE(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetge %%al\nmovzbl %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateEEQ(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (left->lvalue)
    {
        Load(generator, left);
    }

    if (right->lvalue)
    {
        Load(generator, right);
    }

    if (right->type)
        CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsete %%al\nmovsx %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateNEQ(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetne %%al\nmovzbl %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateAnd(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "and ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateXor(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "xor ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

unsigned int AnalyzeFunctionSize(AbstractSyntaxTreeNode *astRoot, unsigned char functionNum)
{
    unsigned int size = ZERO;

    if (!astRoot)
    {
        return ZERO;
    }

    if (astRoot->GenerationFunction == GenerateDeclaration)
    {
        size += ((Type*)((Symbol*)astRoot->info)->_type)->size;
    }

    if (astRoot->GenerationFunction == GenerateReturn)
    {
        astRoot->label = functionNum;
    }

    CircularLinearLinkedListNode *p = astRoot->childrenManager;

    if (p) do
    {
        size += AnalyzeFunctionSize(p->info, functionNum);
        p = p->nextNode;
    } 
    while (p != astRoot->childrenManager);

    return size;
}

void GenerateFunctions(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    CircularLinearLinkedListNode *p = astRoot->childrenManager->nextNode;
    short memoryOffset = generator->currentMemoryOffset;
    unsigned int currentFunctionSize = ZERO;
    unsigned char currentFunction = ZERO;

    do
    {
        if (((AbstractSyntaxTreeNode*)p->info)->childrenManager)
        {
            currentFunctionSize = AnalyzeFunctionSize(p->info, currentFunction);
            currentFunctionSize = ALIGN(currentFunctionSize, STACK_ALIGNMENT);

            ((AbstractSyntaxTreeNode*)p->info)->label = currentFunctionSize;
            generator->currentMemoryOffset = -currentFunctionSize;

            EmitFunctionStart(generator, p->info, currentFunctionSize);
            GenerateStatements(generator, p->info);
            EmitFunctionEnd(generator, p->info, currentFunction, currentFunctionSize);

            generator->currentMemoryOffset = memoryOffset;
            currentFunction++;
        }

        p = p->nextNode;
    } 
    while (p != astRoot->childrenManager->nextNode);
}

void GenerateCode(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    GenerateFunctions(generator, astRoot);
}