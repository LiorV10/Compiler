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
                        "rax", "rbx", "rcx", "r10", "r11", "r12", "r13", "r14", "r15"}
#define REGISTERS_NUM 9

#define FULL_REGISTER(reg) (reg + REGISTERS_NUM)

typedef unsigned short Register;

typedef struct
{
    Stack *availableRegisters;
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

    va_start(args, generator);

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

    for (currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    {
        PushStack(generator->availableRegisters, (void *)currentRegister);
    }

    generator->currentMemoryOffset = ZERO;
}

Register GetRegister(CodeGenerator *generator)
{
    return ((Register)PopStack(generator->availableRegisters));
}

void FreeRegister(CodeGenerator *generator, Register reg)
{
    PushStack(generator->availableRegisters, (void *)reg);
}

void EmitMemoryAddress(CodeGenerator *generator, short memoryAddress)
{
    Emit(generator, "%d(%%rbp)", memoryAddress);
}

void EmitRegister(CodeGenerator *generator, Register reg)
{
    Emit(generator, "%%%s", generator->registers[reg]);
}

void EmitRegisterOrAddress(CodeGenerator *generator, AbstractSyntaxTreeNode *node)
{
    if (node->reg != -ONE)
    {
        EmitRegister(generator, node->reg);
    }
    else
    {
        if (!((Symbol *)node->info)->memoryAddress)
            Emit(generator, "$%s", ((Symbol *)node->info)->name);
        else
            EmitMemoryAddress(generator, ((Symbol *)node->info)->memoryAddress);
    }
}
static int currentBranchNum = 0;

int EmitLabel(CodeGenerator *generator, int id, char *extra)
{
    Emit(generator, "AG%d_%s:\n", id != -1 ? id : currentBranchNum, extra);

    return (currentBranchNum++);
}

/*

void GenerateIntegerLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Emit(codeGenerator, "movl $");

    EmitFunc("movl $", stream);
    EmitFunc(((Symbol*)additionRoot->info)->name, stream);
    EmitFunc(", %%", stream);
    EmitFunc(((struct Register*)(additionRoot->reg = GetRegister()))->name, stream);
    EmitFunc("\n", stream);
}

void GenerateSymbol(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    EmitFunc("movl ", stream);
    EmitRegOrAddress(additionRoot, EmitFunc, stream);
    EmitFunc(", %%", stream);
    EmitFunc(((struct Register*)(additionRoot->reg = GetRegister()))->name, stream);
    EmitFunc("\n", stream);
}

void GenerateDeclaration(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Symbol *decl = additionRoot->info;
    stackPosition -= 4; // width of variable type
    decl->memoryAddress = stackPosition;
}

void GenerateAddition(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = additionRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = additionRoot->childrenManager->info;

    EmitFunc("addl ", stream);
    EmitRegOrAddress(right, EmitFunc, stream);
    EmitFunc(", %%", stream);
    EmitFunc(((struct Register*)left->reg)->name, stream);
    EmitFunc("\n", stream);

    FreeRegister(findReg(right));
    additionRoot->reg = left->reg;
}

void GenerateMult(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = additionRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = additionRoot->childrenManager->info;

    if (((struct Register*)left->reg)->name[1] != 'a')
    EmitFunc("pushq %%rax\n", stream);
    EmitFunc("movl %%", stream);
    EmitFunc(((struct Register*)left->reg)->name, stream);
    EmitFunc(", %%eax\n", stream);
    EmitFunc("imull ", stream);
    EmitRegOrAddress(right, EmitFunc, stream);
    EmitFunc("\n", stream);
    EmitFunc("movl %%eax, %%", stream);
    EmitFunc(((struct Register*)left->reg)->name, stream);
    EmitFunc("\n", stream);
    if (((struct Register*)left->reg)->name[1] != 'a')
    EmitFunc("popq %%rax\n", stream);

    FreeRegister(findReg(right));
    additionRoot->reg = left->reg;
}

void GenerateAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
   AbstractSyntaxTreeNode *left = additionRoot->childrenManager->nextNode->info;
   AbstractSyntaxTreeNode *right = additionRoot->childrenManager->info;

    struct Register *reg = findReg(right);

    EmitFunc("movl ", stream);
    EmitRegOrAddress(right, EmitFunc, stream);
    EmitFunc(", ", stream);
    EmitMemoryAddress(((Symbol*)left->info)->memoryAddress, EmitFunc, stream);
    EmitFunc("\n", stream);
    FreeRegister(reg);
    additionRoot->reg = left->reg;
}

void GenerateAdditionAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = additionRoot->childrenManager->nextNode->info;
   AbstractSyntaxTreeNode *right = additionRoot->childrenManager->info;

    struct Register *reg = findReg(right);

    EmitFunc("addl ", stream);
    EmitRegOrAddress(right, EmitFunc, stream);
    EmitFunc(", ", stream);

    EmitMemoryAddress(((Symbol*)left->info)->memoryAddress, EmitFunc, stream);
    EmitFunc("\n", stream);

    FreeRegister(reg);
    additionRoot->reg = left->reg;
}

void GenerateDivision(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = additionRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = additionRoot->childrenManager->info;

    EmitFunc("divl ", stream);
    EmitRegOrAddress(right, EmitFunc, stream);
    EmitFunc(", %%", stream);
    EmitFunc(((struct Register*)left->reg)->name, stream);
    EmitFunc("\n", stream);

    FreeRegister(findReg(right));
    additionRoot->reg = left->reg;
}

*/

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

void GenerateIf(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->info;

    GenerateExpression(codeGenerator, condition);
    //condition->GenerationFunction(codeGenerator, condition);

    Emit(codeGenerator, "test ");
    EmitRegisterOrAddress(codeGenerator, condition);
    Emit(codeGenerator, ", ");
    EmitRegisterOrAddress(codeGenerator, condition);
    Emit(codeGenerator, "\n");
    Emit(codeGenerator, "jnz AG%d_true\n", currentBranchNum);
    Emit(codeGenerator, "jmp AG%d_false\n", currentBranchNum);
    int next = EmitLabel(codeGenerator, -1, "true");
    body->GenerationFunction(codeGenerator, body);
    EmitLabel(codeGenerator, next, "false");
}

#ifndef _TYPE_SYSTEM_H
    #include "../libs/TypeSystem.h"
#endif

char* F(Type t)
{
    if (t == INTEGER_TYPE) return "Integer";
    if (t == FLOAT_TYPE) return "Float";
    if (t == POINTER_TYPE) return "Pointer";
    if (t == VOID_TYPE) return "Void";

    return "Error";
}

void GenerateFloatLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    float val = strtof(((Symbol*)astNode->info)->name, NULL);

    /*
        movabs $0x40200000, %rax
        movq %rax, %xmm0
        cvttss2si %xmm0, %ebx
    */

    Emit(codeGenerator, "movabs $0x%08x, %%rax\n", *((unsigned int*)&val));
    Emit(codeGenerator, "movq %%rax, %%xmm0\ncvttss2si %%xmm0, ");
    EmitRegister(codeGenerator, astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator));
    Emit(codeGenerator, "\n");

}

void GenerateIntegerLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Emit(codeGenerator, "mov $%s, ", ((Symbol*)astNode->info)->name);
    EmitRegister(codeGenerator, astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator));
    Emit(codeGenerator, "\n");
}

void GenerateSymbol(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Emit(codeGenerator, "mov ");
    EmitRegisterOrAddress(codeGenerator, astNode);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, (astNode->reg = astNode->reg != -ONE ? astNode->reg : GetRegister(codeGenerator)));
    Emit(codeGenerator, "\n");
}

void GenerateDeclaration(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    CircularLinearLinkedListNode *p = astNode->childrenManager->nextNode;
    AbstractSyntaxTreeNode *currentChild;

    do
    {
        currentChild = p->info;
        currentChild->GenerationFunction(codeGenerator, currentChild);

        p = p->nextNode;
    } 
    while (p != astNode->childrenManager->nextNode);
}

void GenerateAddition(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "add ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ",");
    EmitRegister(codeGenerator, left->reg);
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateMult(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, ", %%rax\nimull ");

    EmitRegisterOrAddress(codeGenerator, right);

    Emit(codeGenerator, "\nmov %%rax, ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateExpression(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    LabelAst(astRoot, FALSE);
    GenerateAst_2(generator, astRoot, FALSE);

    while (!IsEmptyStack(((CodeGenerator*)generator)->availableRegisters))
    {
        PopStack(((CodeGenerator*)generator)->availableRegisters);
    }

    for (Register currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    {
        PushStack(((CodeGenerator*)generator)->availableRegisters, (void *)currentRegister);
    }
}

void GenerateAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    // left->GenerationFunction(codeGenerator, left);


    Symbol *decl = left->info;
    ((CodeGenerator *)codeGenerator)->currentMemoryOffset -= 4; // width of variable type
    decl->memoryAddress = ((CodeGenerator *)codeGenerator)->currentMemoryOffset;

    GenerateExpression(codeGenerator, right);

    Emit(codeGenerator, "mov ");
    EmitRegisterOrAddress(codeGenerator, right);
    Emit(codeGenerator, ", ");
    EmitMemoryAddress(codeGenerator, ((Symbol*)left->info)->memoryAddress);
    Emit(codeGenerator, "\n");

    if (left->reg != -ONE)
    {
        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, right);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, left->reg);
        Emit(codeGenerator, "\n");
    }

    astNode->reg = left->reg;
}

void GenerateAdditionAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{

}

void GenerateDivision(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Emit(codeGenerator, "xor %%edx, %%edx\n");
    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, ", %%rax\nidivl ");

    EmitRegisterOrAddress(codeGenerator, right);

    Emit(codeGenerator, "\nmov %%rax, ");
    EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateReturn(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *value = astNode->childrenManager->info;

    GenerateExpression(codeGenerator, value);

    Emit(codeGenerator, "mov ");
    EmitRegisterOrAddress(codeGenerator, value);
    Emit(codeGenerator, ", %%eax\n");
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
        astRoot->GenerationFunction(generator, astRoot);
        return;
    }


    if (astRoot->childrenManager && !((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->childrenManager)
    {
        GenerateAst_2(generator, astRoot->childrenManager->nextNode->info, TRUE);

        if (((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction)
        ((AbstractSyntaxTreeNode *)astRoot->childrenManager->info)->GenerationFunction(generator, astRoot->childrenManager->info);
        astRoot->GenerationFunction(generator, astRoot);

        return;
    }

    AbstractSyntaxTreeNode *leftT = astRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *rightT = astRoot->childrenManager->info;
    AbstractSyntaxTreeNode *maxT = leftT->label > rightT->label ? leftT : rightT;

    GenerateAst_2(generator, maxT, (maxT == leftT));
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
        p = p->nextNode;
    } while (p != astRoot->childrenManager->nextNode);
}

void EmitFunctionStart(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;

    Emit(generator, ".text\n.globl %s\n.type %s, @function\n%s:\n", function->name, function->name, function->name);
    Emit(generator, "pushq %rbp\nmovq %rsp, %rbp\n");
}

void EmitFunctionEnd(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;

    Emit(generator, "popq %rbp\nret\n");

}

void GenerateCall(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;
    AbstractSyntaxTreeNode *parameters;
    
    if (astRoot->childrenManager)
    {
        parameters = astRoot->childrenManager->info;

        GenerateExpression(generator, parameters);

        Emit(generator, "push ");
        EmitRegister(generator, FULL_REGISTER(parameters->reg));
        Emit(generator, "\n");
    }

    Emit(generator, "call %s\n", function->name);

    astRoot->reg = GetRegister(generator);

    Emit(generator, "mov %%eax, ");
    EmitRegister(generator, astRoot->reg);
    Emit(generator, "\n");
}

void GenerateFunctions(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    // generate function for each child

    CircularLinearLinkedListNode *p = astRoot->childrenManager->nextNode;

    do
    {
        EmitFunctionStart(generator, p->info);
        GenerateStatements(generator, p->info);
        EmitFunctionEnd(generator, p->info);
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