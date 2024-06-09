/// CodeGenerator.c

#include "CodeGenerator.h"

#include <stdarg.h>

#define EAX 0
#define EBX 1
#define ECX 2
#define R10D 3
#define R11D 4
#define R12D 5
#define R13D 6
#define R14D 7
#define R15D 8
#define REGISTER_NAMES {"eax", "ebx", "ecx", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d", \
                        "rax", "rbx", "rcx", "r10", "r11", "r12", "r13", "r14", "r15", \
                        "al", "bl", "cl", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b"}
#define REGISTERS_NUM 9

#define FULL_REGISTER(reg) ((((Register)(reg)) % REGISTERS_NUM) + REGISTERS_NUM)
#define MIN_REGISTER(reg) (FULL_REGISTER(reg) + REGISTERS_NUM)

typedef unsigned short Register;

typedef struct
{
    Stack *availableRegisters;
    LinearLinkedListNode *usedRegisters;
    char *registers[sizeof((char*[])REGISTER_NAMES) / sizeof(char*)];
    short currentMemoryOffset;
    void (*Emit)(void *stream, char *buffer, va_list args);
    void *stream;
} CodeGenerator;


int LabelAst(AbstractSyntaxTreeNode *astRoot, BOOL left);
void GenerateAst_2(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, BOOL left);

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

    generator->availableRegisters = malloc(sizeof(Stack));
    InitStack(generator->availableRegisters);

    InitLinearLinkedList(&generator->usedRegisters);

    for (currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    {
        PushStack(generator->availableRegisters, (void *)currentRegister);
    }

    generator->currentMemoryOffset = ZERO;
}

Register GetRegister(CodeGenerator *generator)
{
    PushLinearLinkedList(&generator->usedRegisters);

    return ((Register)(generator->usedRegisters->info = PopStack(generator->availableRegisters)));
}

void FreeRegister(CodeGenerator *generator, Register reg)
{
    reg %= REGISTERS_NUM;

    PushStack(generator->availableRegisters, (void *)reg);
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
    if (node->reg != -ONE)
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

char* F(Type *tt)
{
    TypeKind t = tt->type;
    
    if (t == INTEGER_TYPE) return "Integer";
    if (t == FLOAT_TYPE) return "Float";
    if (t == POINTER_TYPE) return "Pointer";
    if (t == VOID_TYPE) return "Void";

    return "Error";
}

Register CastBySize(Register reg, unsigned char size)
{
    unsigned char offsets[8] = {18, 0, 0, 0, 0, 0, 0, 9};

    return (((reg % 9) + offsets[size - 1]));
}

void GenerateStringLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    int label = GetLabel(codeGenerator);

    Emit(codeGenerator, ".section .rodata\n");
    EmitLabel(codeGenerator, label);//EmitLabel(codeGenerator, currentBranchNum, "");
    Emit(codeGenerator, ".string %s\n.text\n", ((Symbol*)astNode->info)->name);
    Emit(codeGenerator, "leaq .AG%d(%%rip), ", label);
    EmitRegister(codeGenerator, astNode->reg = FULL_REGISTER(astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator)));
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
    EmitRegister(codeGenerator, astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator));
    Emit(codeGenerator, "\n");

}

void GenerateIntegerLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator);

    astNode->reg = CastBySize(astNode->reg, ((Type*)((Symbol*)astNode->info)->_type)->size);

    Emit(codeGenerator, "mov $%s, ", ((Symbol*)astNode->info)->name);
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void GenerateSymbol(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    if (((Type*)((Symbol*)astNode->info)->_type)->type == ARRAY_TYPE)
    {
        Emit(codeGenerator, "leaq %d(%%rbp), ", ((Symbol*)astNode->info)->memoryAddress);
    }
    else
    {
        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, astNode);
        Emit(codeGenerator, ", ");
    }

    astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator);

    if (astNode->type && (((Type*)astNode->type)->size == 8 || ((Type*)astNode->type)->type == ARRAY_TYPE))
    {
        astNode->reg = FULL_REGISTER(astNode->reg);
    }

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
    AbstractSyntaxTreeNode *init = NULL;
    if (astNode->childrenManager)
        init = astNode->childrenManager->info;

    Symbol *decl = astNode->info;
    Type *type = astNode->type;

    if (init)
        init->GenerationFunction(codeGenerator, init);

    decl->memoryAddress = ((CodeGenerator *)codeGenerator)->currentMemoryOffset;   

    ((CodeGenerator *)codeGenerator)->currentMemoryOffset += type->size;

    if (init)
    {
        init->reg = CastBySize(init->reg, type->size);

        if (init->lvalue)
        {
            Load(codeGenerator, init);
        }

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

#define IS_FULL_REGISTER(reg) (!((((Register)reg) % REGISTERS_NUM) == (reg)))

void Cast(Register *first, Register *second)
{
    Register temp = *second;

    if (IS_FULL_REGISTER(*first)) *second = FULL_REGISTER(*second);
    if (IS_FULL_REGISTER(temp)) *first = FULL_REGISTER(*first);
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
        Emit(codeGenerator, "leaq (");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, FULL_REGISTER(right->reg));
        ((Type*)left->type)->baseType->size == 5 ? Emit(codeGenerator, ", %d), ", 8) :
        Emit(codeGenerator, ", %d), ", ((Type*)left->type)->baseType->size);
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, "\n");
    }
    else
    {
        if (right->reg != -ONE)
            Cast(&right->reg, &left->reg);


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

    Register temp = left->reg;
    Register temp2 = right->reg;

    if (left->lvalue)
    {
        Load(codeGenerator, left);
    }

    if (right->lvalue)
    {
        Load(codeGenerator, right);
    }

    if (right->reg != -ONE)
        Cast(&right->reg, &left->reg);

    if (right->reg != temp2)
    {
        Emit(codeGenerator, "movsx ");
        EmitRegister(codeGenerator, temp2);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, right->reg);
        Emit(codeGenerator, "\n");
    }

    Emit(codeGenerator, "sub ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = temp;
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

    Emit(codeGenerator, "imul ");
    EmitRegister(codeGenerator, FULL_REGISTER(right->reg));
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
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

void GenerateIndexing(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    return;
    AbstractSyntaxTreeNode *ptr = astRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *offset = astRoot->childrenManager->info;
    
    // if (ptr->reg == -ONE)
    //     ptr->GenerationFunction(generator, ptr);
    
    // if (offset->reg == -ONE)
    //     ptr->GenerationFunction(generator, offset);

    Emit(generator, "leaq (");
    EmitRegister(generator, FULL_REGISTER(ptr->reg));
    Emit(generator, ", ");
    EmitRegister(generator, FULL_REGISTER(offset->reg));
    Emit(generator, ", %d), ", ((Type*)ptr->type)->baseType->size);
    EmitRegister(generator, FULL_REGISTER(ptr->reg));
    Emit(generator, "\n");

    // GenerateAddition(generator, astRoot);

    astRoot->type = ((Type*)ptr->type)->baseType;
    astRoot->reg = ptr->reg;

    if (!astRoot->lvalue)
    {
        if (astRoot->type && ((Type*)astRoot->type)->size == 8)
            astRoot->reg = FULL_REGISTER(astRoot->reg);

        Emit(generator, "mov (");
        EmitRegister(generator, astRoot->reg);

        if (astRoot->type && ((Type*)astRoot->type)->size == 1)
            astRoot->reg = MIN_REGISTER(astRoot->reg);

        Emit(generator, "), ");
        EmitRegister(generator, astRoot->reg);
        Emit(generator, "\n");

        if (astRoot->reg >= 18)
        {
            Emit(generator, "movsbl ");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, ", ");
            EmitRegister(generator, (Register)astRoot->reg - 18);
            Emit(generator, "\n");
            Emit(generator, "movsx ");
            EmitRegister(generator, (Register)astRoot->reg - 18);
            Emit(generator, ", ");
            EmitRegister(generator, ((astRoot->reg = FULL_REGISTER(astRoot->reg))));
            Emit(generator, "\n");
        }
        
        if (((Type*)astRoot->type)->type == INTEGER_TYPE)
        {
            Emit(generator, "movsx ");
            EmitRegister(generator, (Register)astRoot->reg % REGISTERS_NUM);
            Emit(generator, ", ");
            EmitRegister(generator, ((astRoot->reg = FULL_REGISTER(astRoot->reg))));
            Emit(generator, "\n");         
        }
    }
    else
    {
        if (((Type*)astRoot->type)->size == 8)
            astRoot->reg = FULL_REGISTER(astRoot->reg);

        if (ptr->lvalue)
        if (ptr->GenerationFunction == GenerateIndexing)
        {
            Emit(generator, "mov (");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, "), ");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, "\n");
        }
    }

    FreeRegister(generator, offset->reg);
}

void GenerateDereference(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    AbstractSyntaxTreeNode *operand = astRoot->childrenManager->info;

    // operand->GenerationFunction(generator, operand);

    //if (!operand->type) operand->type = ((AbstractSyntaxTreeNode*)operand->childrenManager->info)->type;
    
    // astRoot->type = ((Type*)operand->type)->baseType;

    if (((Type*)operand->type)->baseType->type == ARRAY_TYPE) astRoot->lvalue = TRUE;

    if (!astRoot->lvalue && ((Type*)operand->type)->baseType->size < 10)
    {
        astRoot->reg = operand->reg;//GetRegister(generator);

        Emit(generator, "mov (");
        EmitRegister(generator, FULL_REGISTER(operand->reg));

        astRoot->reg = CastBySize(astRoot->reg, ((Type*)operand->type)->size);

        if (operand->type && ((Type*)operand->type)->size == 1)
            astRoot->reg = MIN_REGISTER(astRoot->reg);

        Emit(generator, "), ");
        EmitRegister(generator, astRoot->reg);
        Emit(generator, "\n");

        if (astRoot->reg >= 18)
        {
            Emit(generator, "movsbl ");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, ", ");
            EmitRegister(generator, (Register)astRoot->reg - 18);
            Emit(generator, "\n");
            Emit(generator, "movsx ");
            EmitRegister(generator, (Register)astRoot->reg - 18);
            Emit(generator, ", ");
            EmitRegister(generator, ((astRoot->reg = FULL_REGISTER(astRoot->reg))));
            Emit(generator, "\n");
        }
    }
    else
    {
        astRoot->reg = operand->reg;//GetRegister(generator);

        if (operand->info)
            if (((Type*)((Symbol*)operand->info)->_type)->size == 8 || ((Type*)((Symbol*)operand->info)->_type)->baseType->size == 8)
                astRoot->reg = FULL_REGISTER(astRoot->reg);
        else
            if (((Type*)operand->type)->size == 8)
                astRoot->reg = FULL_REGISTER(astRoot->reg);

        if (operand->lvalue
          && (operand->GenerationFunction == GenerateDereference || 
            (operand->GenerationFunction == GenerateStructAccess && 
        ((AbstractSyntaxTreeNode*)operand->childrenManager->nextNode->info)->GenerationFunction == GenerateDereference)))
        {
            Emit(generator, "mov (");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, "), ");
            EmitRegister(generator, astRoot->reg);
            Emit(generator, "\n");
        }
    }

    // astRoot->reg = operand->reg;
}

void GenerateArithmeticExpression(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *expression = astNode->childrenManager->info;

    if (expression->GenerationFunction == GenerateAssignment)
    {
        // ((AbstractSyntaxTreeNode*)expression->childrenManager->info)->lvalue = FALSE;
        // ((AbstractSyntaxTreeNode*)expression->childrenManager->nextNode->info)->lvalue = TRUE;
        //    MakeLvalue(expression->childrenManager->info, FALSE);
        //    MakeLvalue(expression->childrenManager->nextNode->info, TRUE);
    }

    GenerateExpression(codeGenerator, expression);
    astNode->reg = expression->reg;
    astNode->lvalue = expression->lvalue;
}

void GenerateExpression(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    LabelAst(astRoot, FALSE);
    GenerateAst_2(generator, astRoot, FALSE);

    if (astRoot->reg != -ONE && (Register)astRoot->reg % REGISTERS_NUM != EAX)
        FreeRegister(generator, (Register)astRoot->reg % REGISTERS_NUM);

    // while (!IsEmptyStack(((CodeGenerator*)generator)->availableRegisters))
    // {
    //     PopStack(((CodeGenerator*)generator)->availableRegisters);
    // }

    // for (Register currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    // {
    //     PushStack(((CodeGenerator*)generator)->availableRegisters, (void *)currentRegister);
    // }
}

void MakeLvalue(AbstractSyntaxTreeNode *root, BOOL lvalue)
{
    if (!root->childrenManager)
    {
        root->lvalue = lvalue;
        return;
    }

    root->lvalue = lvalue;
    CircularLinearLinkedListNode *child = root->childrenManager;

    do
    {
        MakeLvalue(child->info, lvalue);
        child = child->nextNode;
    } 
    while (child != root->childrenManager);
}

void Load(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    if (astNode->GenerationFunction == GenerateArithmeticExpression)
        astNode = astNode->childrenManager->info;
    
    if (astNode->GenerationFunction != GenerateDereference &&
        !(astNode->GenerationFunction == GenerateStructAccess && 
        ((AbstractSyntaxTreeNode*)astNode->childrenManager->nextNode->info)->GenerationFunction == GenerateDereference))
    {
        return;
    }

    if (((Type*)astNode->type)->type == STRUCT_TYPE ||
        ((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        return;
    }

    astNode->reg = CastBySize(astNode->reg, ((Type*)astNode->type)->size);

    Emit(codeGenerator, "mov (");
    EmitRegister(codeGenerator, FULL_REGISTER(astNode->reg));
    Emit(codeGenerator, "), ");
    EmitRegister(codeGenerator, (astNode->reg));
    Emit(codeGenerator, "\n");

    if (astNode->reg >= 18)
    {
        Emit(codeGenerator, "movsbl ");
        EmitRegister(codeGenerator, astNode->reg);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, (Register)astNode->reg - 18);
        Emit(codeGenerator, "\n");
        Emit(codeGenerator, "movsx ");
        EmitRegister(codeGenerator, (Register)astNode->reg - 18);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, ((astNode->reg = FULL_REGISTER(astNode->reg))));
        Emit(codeGenerator, "\n");
    }
}

void GenerateAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    if (((Type*)left->type)->type == STRUCT_TYPE &&
        ((Type*)right->type)->type == STRUCT_TYPE)
    {
        Emit(codeGenerator, "push %%rcx\nmov $%d, %%rcx\ncld\n", ((Type*)right->type)->size);
        Emit(codeGenerator, "lea %d(%%rbp), %%rsi\n", ((Symbol*)right->info)->memoryAddress);
        Emit(codeGenerator, "lea %d(%%rbp), %%rdi\n", ((Symbol*)left->info)->memoryAddress);
        Emit(codeGenerator, "rep movsb\npop %%rcx\n");

        FreeRegister(codeGenerator, right->reg);
        astNode->reg = left->reg;

        return;
    }

    Type *temp = left->type;

    if (left->info && temp->size == 4 && right->reg != -ONE)
    {
        right->reg = (Register)right->reg % REGISTERS_NUM;
    }

    if (left->info && temp->size == 8)
    {
        right->reg = FULL_REGISTER(right->reg);
    }

    if (right->lvalue)
    {
       Load(codeGenerator, right);
    }

    Emit(codeGenerator, "mov ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    
    if (left->GenerationFunction == GenerateDereference || 
        (left->GenerationFunction == GenerateStructAccess && 
            ((AbstractSyntaxTreeNode*)left->childrenManager->nextNode->info)->GenerationFunction == GenerateDereference))
        {Emit(codeGenerator, "("); EmitRegister(codeGenerator, FULL_REGISTER(left->reg)); Emit(codeGenerator, ")");}
    else
        EmitMemoryAddress(codeGenerator, ((Symbol*)left->info)->memoryAddress);
    
    Emit(codeGenerator, "\n");

    if (left->reg != -ONE)
    {
        if (right->reg != -ONE)
            Cast(&left->reg, &right->reg);

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

    // operand->GenerationFunction(generator, operand);
    astNode->reg = FULL_REGISTER(operand->reg);
    
    if (operand->GenerationFunction == GenerateIndexing)
        return;

    Emit(generator, "leaq %d(%%rbp), ", ((Symbol*)operand->info)->memoryAddress);
    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");

    // Emit(generator, "mov $%d, ", ((Symbol*)operand->info)->memoryAddress);
    // EmitRegister(generator, astNode->reg);
    // Emit(generator, "\nadd %%rbp, ");
    // EmitRegister(generator, astNode->reg);
    // Emit(generator, "\n");

    // FreeRegister(generator, operand->reg);
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

    Emit(codeGenerator, "movsx ");
    EmitRegister(codeGenerator, (Register)left->reg % REGISTERS_NUM);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, "\n");

    if (right->reg != -ONE) 
    {
        right->reg = FULL_REGISTER(right->reg);

        Emit(codeGenerator, "movsx ");
        EmitRegister(codeGenerator, (Register)right->reg % REGISTERS_NUM);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, right->reg);
        Emit(codeGenerator, "\n");
    }

    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, ", %%rax\ncqo\nidiv ");

    EmitRegisterOrAddress(codeGenerator, right);

    Emit(codeGenerator, "\nmov %%rax, ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
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

    // Emit(codeGenerator, "mov %d(%%rbp), ", ((Symbol*)astNode->info)->memoryAddress);
    // EmitRegister(codeGenerator, structNode->reg);
    // Emit(codeGenerator, "\n");

    // AbstractSyntaxTreeNode *structNode = astNode->childrenManager->info;
    // Type *type = structNode->type;

    // Field *field = astNode->field;// FindField(type, ((Symbol*)astNode->info)->name);MM)
    // ((Symbol*)astNode->info)->memoryAddress = ((Symbol*)structNode->info)->memoryAddress + field->offset;
    astNode->type = field->type;

    if (structNode->GenerationFunction == GenerateDereference)
    {
        if (((AbstractSyntaxTreeNode*)structNode->childrenManager->info)->GenerationFunction == GenerateStructAccess)
        {   
            Load(codeGenerator, structNode);
        }

        if (1)
        //if (structNode->lvalue)
        {
            Emit(codeGenerator, "lea %d(", field->offset);
            EmitRegister(codeGenerator, (structNode->reg));
            Emit(codeGenerator, ")");
        }
        else
        {
            Emit(codeGenerator, "mov %d(", field->offset);
            EmitRegister(codeGenerator, (structNode->reg));
            Emit(codeGenerator, ")");
        }
    }
    else
    {
        Emit(codeGenerator, "mov ");
        EmitMemoryAddress(codeGenerator, ((Symbol*)astNode->info)->memoryAddress);
            astNode->lvalue = FALSE;

    }

    Emit(codeGenerator, ", ");

    astNode->reg = structNode->reg; //astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator);

    if (field->type->size == 8)
    {
        astNode->reg = FULL_REGISTER(astNode->reg);   
    }

    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");

}

void GenerateReturn(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Register result = EAX;
    AbstractSyntaxTreeNode *value;
    
    if (astNode->childrenManager)
    {
        value = astNode->childrenManager->info;
        value->GenerationFunction(codeGenerator, value);

        if (value->reg != -ONE)
            Cast(&value->reg, &result);

        if (value->lvalue)
            Load(codeGenerator, value);

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

void GenerateAst_2(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, BOOL left)
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
        GenerateAst_2(generator, astRoot->childrenManager->nextNode->info, TRUE);

        if (astRoot->childrenManager != astRoot->childrenManager->nextNode && 
            ((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction)
                ((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction(generator, astRoot->childrenManager->info);

        astRoot->GenerationFunction(generator, astRoot);

        return;
    }

    AbstractSyntaxTreeNode *maxT = leftT->label > rightT->label ? leftT : rightT;
    
    GenerateAst_2(generator, maxT, (maxT == leftT));

    if (leftT != rightT)
        GenerateAst_2(generator, (maxT == leftT ? rightT : leftT), (maxT != leftT));

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

    stackSize %= 16;

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

            Emit(generator, "movq ");
            EmitRegister(generator, FULL_REGISTER(currentParameter->reg));
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

    Emit(generator, "mov %%rax, ");
    EmitRegister(generator, FULL_REGISTER(astRoot->reg));
    Emit(generator, "\n");
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
    Emit(generator, "\nsetz %%al\nmovzbl %%al, ");
    EmitRegister(generator, (Register)operand->reg % REGISTERS_NUM);
    Emit(generator, "\n");

    astNode->reg = operand->reg;
}

void GenerateLT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(generator, "cmp ");
    EmitRegister(generator, FULL_REGISTER(right->reg));
    Emit(generator, ", ");
    EmitRegister(generator, FULL_REGISTER(left->reg));
    Emit(generator, "\nsetl %%al\nmovzbl %%al, ");
    EmitRegister(generator, (Register)left->reg % REGISTERS_NUM);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateGT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetg %%al\nmovzbl %%al, ");
    EmitRegister(generator, (Register)left->reg % REGISTERS_NUM);
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
        left->reg = CastBySize(left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, (Register)left->reg);
    Emit(generator, "\nsete %%al\nmovzbl %%al, ");
    EmitRegister(generator, (Register)left->reg % REGISTERS_NUM);
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

unsigned int Align(unsigned int size)
{
    return ((size / 16 + !!(size % 16)) * 16);
}

void GenerateFunctions(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    // generate function for each child

    CircularLinearLinkedListNode *p = astRoot->childrenManager->nextNode;
    short memoryOffset = generator->currentMemoryOffset;
    unsigned int currentFunctionSize = 0;
    unsigned char currentFunction = ZERO;

    do
    {
        if (((AbstractSyntaxTreeNode*)p->info)->childrenManager)
        {
            currentFunctionSize = Align(AnalyzeFunctionSize(p->info, currentFunction));
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

void GenerateAst(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    GenerateFunctions(generator, astRoot);
    // if (!astRoot)
    // {
    //     return;
    // }

    // if (astRoot->GenerationFunction)
    // {
    //  //   printf("\n%d\n", LabelAst(astRoot, FALSE));
    //     //LabelAst(astRoot, FALSE);
    //     astRoot->GenerationFunction(generator, astRoot);
    //     //GenerateAst_2(generator, astRoot, FALSE);

    //     // while (!IsEmptyStack(generator->availableRegisters))
    //     // {
    //     //     PopStack(generator->availableRegisters);
    //     // }

    //     return;
    // }

    // if (astRoot->childrenManager)
    // {
    //     CircularLinearLinkedListNode *p = astRoot->childrenManager->nextNode;

    //     do
    //     {
    //         GenerateAst(generator, p->info);
    //         p = p->nextNode;
    //     }
    //     while (p != astRoot->childrenManager->nextNode);
    // }

    // for (LinearLinkedListNode *p = astRoot->childrenManager->nextNode; p; p = p->nextNode)
    // {
    //     GenerateAst(p->info, EmitFunc, stream);
    // }
}

void GenerateCode(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    GenerateAst(generator, astRoot);
}