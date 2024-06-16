/// CodeGenerator.c

#include "CodeGenerator.h"

#include <stdarg.h>

#define EAX 1

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

//-----------------------------------------------------------------------------
//                                      LabelAst                                     
//                                      --------                               
//                                                                             
// General      : The function labels the ast according to the minimum number
//                of registers needed.                                 
//                                                                             
// Parameters   :                                                              
//      astRoot - The ast (In)                                     
//                                                                             
// Return Value : The label (minimum registers needed).             
//-----------------------------------------------------------------------------
// T(n) = T(k) + T(n - k) + O(1) -> O(n) 
//-----------------------------------------------------------------------------
unsigned char LabelAst(AbstractSyntaxTreeNode *astRoot)
{
    unsigned char leftL = ZERO;
    unsigned char rightL = ZERO;

    if (!astRoot->childrenManager)
    {
        return (astRoot->label = (astRoot->GenerationFunction == GenerateSymbol));
    }

    leftL = LabelAst(astRoot->childrenManager->nextNode->info);
    rightL = LabelAst(astRoot->childrenManager->info);

    astRoot->label = MAX(leftL, rightL) + leftL == rightL;

    return (astRoot->label);
}

//-----------------------------------------------------------------------------
//                                      SethiUllman                                     
//                                      -----------                           
//                                                                             
// General      : The function runs the sethi-ullman algorithm on a given ast.                                 
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)
//      astRoot   - The ast (In)                                   
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = T(k) + T(n - k) + O(1) -> O(n)
//-----------------------------------------------------------------------------
void SethiUllman(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    AbstractSyntaxTreeNode *left;
    AbstractSyntaxTreeNode *right;
    AbstractSyntaxTreeNode *max;

    if (!astRoot->childrenManager || astRoot->GenerationFunction == GenerateCall)
    {
        astRoot->GenerationFunction ?
            astRoot->GenerationFunction(generator, astRoot) : ZERO;

        return;
    }

    left = astRoot->childrenManager->nextNode->info;
    right = astRoot->childrenManager->info;
    max = left->label > right->label ? left : right;

    SethiUllman(generator, max);

    left != right ?
        SethiUllman(generator, (max == left ? right : left)) : ZERO;

    astRoot->GenerationFunction ?
        astRoot->GenerationFunction(generator, astRoot) : ZERO;
}

//-----------------------------------------------------------------------------
//                                      Init Code Generator                                     
//                                      -------------------                    
//                                                                             
// General      : The function initializer the code generator.                                 
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)
//      Emit      - The emission function (In)
//      stream    - The stream to which the code is emitted (In)                                   
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void InitCodeGenerator(CodeGenerator *generator, void (*Emit)(char *buffer, void *stream), void *stream)
{
    Register currentRegister;

    *generator = (CodeGenerator){.registers = REGISTER_NAMES};

    generator->Emit = Emit;
    generator->stream = stream;
    generator->currentMemoryOffset = ZERO;
    generator->currentLabel = ZERO;

    generator->availableRegisters = malloc(sizeof(Stack));
    InitStack(generator->availableRegisters);

    InitLinearLinkedList(&generator->usedRegisters);

    for (currentRegister = REGISTERS_NUM; currentRegister != EAX; currentRegister--)
    {
        PushStack(generator->availableRegisters, (void *)currentRegister);
    }
}

//-----------------------------------------------------------------------------
//                                      Free Code Generator                                     
//                                      -------------------                                 
//                                                                             
// General      : The function frees the code generator.                                 
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)                                   
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
void FreeCodeGenerator(CodeGenerator *generator)
{
    while (!IsEmptyStack(generator->availableRegisters))
    {
        PopStack(generator->availableRegisters);
    }

    EmptyLinearLinkedList(&generator->usedRegisters, NULL);

    free(generator->availableRegisters);
}

//-----------------------------------------------------------------------------
//                                      Emit                                     
//                                      ----                                  
//                                                                             
// General      : The function emits a given buffer into the stream.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)
//      buffer    - The buffer to emit (In)
//      ...       - Extra parameters for buffer format (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void Emit(CodeGenerator *generator, char *buffer, ...)
{
    va_list args;

    va_start(args, buffer);

    generator->Emit(generator->stream, buffer, args);

    va_end(args);
}

//-----------------------------------------------------------------------------
//                                      Get Register                                     
//                                      ------------                                 
//                                                                             
// General      : The function finds an available register.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)					                                        
//                                                                             
// Return Value : The register.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
Register GetRegister(CodeGenerator *generator)
{
    PushLinearLinkedList(&generator->usedRegisters);

    return ((Register)(generator->usedRegisters->info = PopStack(generator->availableRegisters)));
}

//-----------------------------------------------------------------------------
//                                      Free Register                                     
//                                      -------------                                 
//                                                                             
// General      : The function returns a register to the system.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)
//      reg       - The register to free (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void FreeRegister(CodeGenerator *generator, Register reg)
{
    reg = BASE_REGISTER(reg);

    PushStack(generator->availableRegisters, reg);
    PopLinearLinkedList(&generator->usedRegisters);
}

//-----------------------------------------------------------------------------
//                                      Emit Memory Address                                     
//                                      -------------------                    
//                                                                             
// General      : The function emits a given memory address.                                                           
//                                                                             
// Parameters   :  
//      generator - The code generator context (In)
//      memoryAddress - The address to emit (In)                         
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void EmitMemoryAddress(CodeGenerator *generator, short memoryAddress)
{
    Emit(generator, "%d(%%rbp)", memoryAddress);
}

//-----------------------------------------------------------------------------
//                                      Emit Register                                     
//                                      -------------               
//                                                                             
// General      : The function emits a given register.                                                           
//                                                                             
// Parameters   :  
//      generator - The code generator context (In)
//      reg       - The register to emit (In)                         
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void EmitRegister(CodeGenerator *generator, Register reg)
{
    Emit(generator, "%%%s", generator->registers[reg]);
}

//-----------------------------------------------------------------------------
//                          Emit Register Or Memory Address                                     
//                          -------------------------------                    
//                                                                             
// General      : The function emits either a register or memory address,
//                with priority to a register.                                                           
//                                                                             
// Parameters   :  
//      generator - The code generator context (In)
//      astNode   - The node to choose register/address from (In)                         
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void EmitRegisterOrAddress(CodeGenerator *generator, AbstractSyntaxTreeNode *astNode)
{
    astNode->reg ?
        EmitRegister(generator, astNode->reg) : 
        EmitMemoryAddress(generator, ((Symbol *)astNode->info)->memoryAddress);
}

//-----------------------------------------------------------------------------
//                                      Get Label                                     
//                                      ---------                                  
//                                                                             
// General      : The function takes control of the next available label.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)					                                        
//                                                                             
// Return Value : The label taken.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
int GetLabel(CodeGenerator *generator)
{
    return (generator->currentLabel++);
}

//-----------------------------------------------------------------------------
//                                      Emit Label                                     
//                                      ----------                                 
//                                                                             
// General      : The function emits a given label.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)
//      label     - The label to emit (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
void EmitLabel(CodeGenerator *generator, int label)
{
    Emit(generator, ".AG%d:\n", label);
}

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

void GenerateSymbol(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    unsigned short typeSize = ((Type*)astNode->type)->size;

    if (((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        Emit(codeGenerator, "leaq %d(%%rbp), ", ((Symbol*)astNode->info)->memoryAddress);
        typeSize = QWORD_SIZE;
    }
    else
    {
        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, astNode);
        Emit(codeGenerator, ", ");
    }

    astNode->reg = astNode->reg ? astNode->reg : GetRegister(codeGenerator);
    astNode->reg = REGSITER_BY_SIZE(astNode->reg, MIN(typeSize, QWORD_SIZE));

    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
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
        Load(codeGenerator, init);
        CastBySize(codeGenerator, &init->reg, type->size);

        Emit(codeGenerator, "mov ");
        EmitRegister(codeGenerator, init->reg);
        Emit(codeGenerator, ", ");
        EmitMemoryAddress(codeGenerator, decl->memoryAddress);
        Emit(codeGenerator, "\n");

        astNode->reg = init->reg;
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
    LabelAst(astRoot);
    SethiUllman(generator, astRoot);
    FreeRegister(generator, astRoot->reg);
}

void Load(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    astNode = astNode->GenerationFunction == GenerateArithmeticExpression ?
        astNode->childrenManager->info : astNode;
    
    if (astNode->GenerationFunction != GenerateDereference || 
        ((Type*)astNode->type)->type == STRUCT_TYPE ||
        ((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        return;
    }

    Emit(codeGenerator, "mov (");
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "), ");

    CastBySize(codeGenerator, &astNode->reg, ((Type*)astNode->type)->size);

    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void Store(void *codeGenerator, AbstractSyntaxTreeNode *source, AbstractSyntaxTreeNode *dest)
{
    CastBySize(codeGenerator, &source->reg, ((Type*)dest->type)->size);

    Emit(codeGenerator, "mov ");
    EmitRegister(codeGenerator, source->reg);
    Emit(codeGenerator, ", ");

    if (dest->GenerationFunction == GenerateDereference)
    {
        Emit(codeGenerator, "("); 
        EmitRegister(codeGenerator, FULL_REGISTER(dest->reg)); 
        Emit(codeGenerator, ")");
    }
    else
    {
        EmitMemoryAddress(codeGenerator, ((Symbol*)dest->info)->memoryAddress);
    }

    Emit(codeGenerator, "\n");
}

#pragma region Statements

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

    Load(codeGenerator, condition);
    if (condition->type) // REMOVE AFTER SEMANTIC ANALYSIS IS DONE!!!
    condition->reg = REGSITER_BY_SIZE(condition->reg, ((Type*)condition->type)->size);

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

void GenerateWhile(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *body = astNode->childrenManager->info;
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;

    int bodyLabel = GetLabel(codeGenerator);
    int endLabel = GetLabel(codeGenerator);

    EmitLabel(codeGenerator, bodyLabel);
    condition->GenerationFunction(codeGenerator, condition);

    Load(codeGenerator, condition);
    if (condition->type) // REMOVE AFTER SEMANTIC ANALYSIS IS DONE!!!
    condition->reg = REGSITER_BY_SIZE(condition->reg, ((Type*)condition->type)->size);

    Emit(codeGenerator, "test ");
    EmitRegister(codeGenerator, condition->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, condition->reg);
    Emit(codeGenerator, "\n");

    Emit(codeGenerator, "jz .AG%d\n", endLabel);
    body->GenerationFunction(codeGenerator, body);

    Emit(codeGenerator, "jmp .AG%d\n", bodyLabel);
    EmitLabel(codeGenerator, endLabel);
}


void GenerateIf(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *elseBody = astNode->childrenManager->info;

    condition->GenerationFunction(codeGenerator, condition);

    Load(codeGenerator, condition);

    Emit(codeGenerator, "test ");
    EmitRegister(codeGenerator, condition->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, condition->reg);
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

void GenerateBlock(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    short offset = ((CodeGenerator*)generator)->currentMemoryOffset;

    GenerateStatements(generator, astRoot);

    ((CodeGenerator*)generator)->currentMemoryOffset = offset;
}

#pragma endregion

#pragma region BinaryOperators

void GenerateAssignment(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Type *leftType = left->type;

    Load(codeGenerator, right);
    Store(codeGenerator, right, left);

    if (left->reg)
    {
        CastBySize(codeGenerator, &right->reg, leftType->size);
        left->reg = REGSITER_BY_SIZE(left->reg, leftType->size);

        Emit(codeGenerator, "mov ");
        EmitRegister(codeGenerator, right->reg);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, left->reg);
        Emit(codeGenerator, "\n");
    }

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateAddition(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(codeGenerator, left);
    Load(codeGenerator, right);

    if (((Type*)left->type)->baseType)
    {
        CastBySize(codeGenerator, &right->reg, QWORD_SIZE);

        GenerateOffsetCalculation(codeGenerator, right, ((Type*)left->type)->baseType);
        Emit(codeGenerator, "leaq (");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, right->reg);
        Emit(codeGenerator, "), ");
        EmitRegister(codeGenerator, FULL_REGISTER(left->reg));
        Emit(codeGenerator, "\n");
    }
    else
    {
        CastBySize(codeGenerator, &right->reg, ((Type*)left->type)->size);
        left->reg = REGSITER_BY_SIZE(left->reg, ((Type*)left->type)->size);

        Emit(codeGenerator, "add ");
        EmitRegister(codeGenerator, right->reg);
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

    Load(codeGenerator, left);
    Load(codeGenerator, right);

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
        CastBySize(codeGenerator, &right->reg, ((Type*)left->type)->size);
        left->reg = REGSITER_BY_SIZE(left->reg, ((Type*)left->type)->size);

        Emit(codeGenerator, "sub ");
        EmitRegister(codeGenerator, right->reg);
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

    Load(codeGenerator, left);
    Load(codeGenerator, right);

    CastBySize(codeGenerator, &right->reg, QWORD_SIZE);

    Emit(codeGenerator, "imul ");
    EmitRegister(codeGenerator, right->reg);
    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, REGSITER_BY_SIZE(left->reg, QWORD_SIZE));
    Emit(codeGenerator, "\n");

    FreeRegister(codeGenerator, right->reg);
    astNode->reg = left->reg;
}

void GenerateDivision(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(codeGenerator, left);
    Load(codeGenerator, right);

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
    }

    Emit(codeGenerator, ", ");
    EmitRegister(codeGenerator, astNode->reg);
    Emit(codeGenerator, "\n");
}

void GenerateLT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

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

    Load(generator, left);
    Load(generator, right);

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

    Load(generator, left);
    Load(generator, right);

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

    Load(codeGenerator, left);
    Load(codeGenerator, right);

    CastBySize(codeGenerator, &right->reg, QWORD_SIZE);
    CastBySize(codeGenerator, &left->reg, QWORD_SIZE);

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

#pragma endregion

#pragma region UnaryOperators

void GenerateOffsetCalculation(void *codeGenerator, AbstractSyntaxTreeNode *astNode, Type *type)
{
    for (; type; type = type->baseType)
    {
        Emit(codeGenerator, "imul $%d, ", type->size);
        EmitRegister(codeGenerator, astNode->reg);
        Emit(codeGenerator, "\n");
    }
}

void GenerateDereference(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    AbstractSyntaxTreeNode *operand = astRoot->childrenManager->info;

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

    Emit(generator, "neg ");
    EmitRegister(generator, operand->reg);
    Emit(generator, "\n");

    astNode->reg = operand->reg;
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

#pragma endregion

#pragma region Constants

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
    // NOT IMPLEMENTED
}

void GenerateIntegerLiteral(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    astNode->reg = astNode->reg ? astNode->reg : GetRegister(codeGenerator);

    Emit(codeGenerator, "mov $%s, ", ((Symbol*)astNode->info)->name);
    EmitRegister(codeGenerator, (astNode->reg = REGSITER_BY_SIZE(astNode->reg, ((Type*)astNode->type)->size)));
    Emit(codeGenerator, "\n");
}

#pragma endregion

#pragma region Functions

void GenerateReturn(void *codeGenerator, AbstractSyntaxTreeNode *astNode)
{
    Register result = REGSITER_BY_SIZE(EAX, QWORD_SIZE);
    AbstractSyntaxTreeNode *value;
    
    if (astNode->childrenManager)
    {
        value = astNode->childrenManager->info;
        value->GenerationFunction(codeGenerator, value);

        Load(codeGenerator, value);
        CastBySize(codeGenerator, &value->reg, QWORD_SIZE);

        Emit(codeGenerator, "mov ");
        EmitRegisterOrAddress(codeGenerator, value);
        Emit(codeGenerator, ", ");
        EmitRegister(codeGenerator, result);
        Emit(codeGenerator, "\n");
    }

    Emit(codeGenerator, "jmp RET_%d\n", astNode->label);
}

void GenerateCall(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;
    AbstractSyntaxTreeNode *currentParameter;
    AbstractSyntaxTreeNode *parametersList = astRoot->childrenManager->info;
    CircularLinearLinkedListNode *parameters = parametersList->childrenManager->nextNode;
    LinearLinkedListNode *usedRegistersPtr;

    char *paramsRegisters[] = {"rdi", "rsi", "xmm15", "xmm14", "r8", "r9"};
    char **currentRegister = paramsRegisters;
    unsigned int stackSize = ZERO;
    char *reg;

    Stack usedRegisters; 
    Stack parameterRegisters; 

    InitStack(&usedRegisters);
    InitStack(&parameterRegisters);

    for (usedRegistersPtr = ((CodeGenerator*)generator)->usedRegisters;
         usedRegistersPtr; 
         usedRegistersPtr = usedRegistersPtr->nextNode)
    {
        Emit(generator, "pushq ");
        EmitRegister(generator, FULL_REGISTER(usedRegistersPtr->info));
        Emit(generator, "\n");

        PushStack(&usedRegisters, usedRegistersPtr->info);
        stackSize += QWORD_SIZE;
    }

    stackSize %= STACK_ALIGNMENT;

    stackSize ?
        Emit(generator, "subq $%d, %%rsp\n", stackSize) : ZERO;
    
    if (parameters) do
    {
        currentParameter = parameters->info;
        PushStack(&parameterRegisters, currentParameter);
        parameters = parameters->nextNode;
        currentRegister++;
    }
    while (parameters != parametersList->childrenManager->nextNode);    

    while (!IsEmptyStack(&parameterRegisters))
    {
        currentParameter = PopStack(&parameterRegisters);
        GenerateExpression(generator, currentParameter);

        Load(generator, currentParameter);
        reg = *--currentRegister;

        CastBySize(generator, &currentParameter->reg, QWORD_SIZE);
        Emit(generator, "movq ");
        EmitRegister(generator, currentParameter->reg);
        Emit(generator, ", %%%s\n", reg);
    }

    Emit(generator, "movq %%xmm14, %%rcx\nmovq %%xmm15, %%rdx\ncall %s\n", function->name);
    
    stackSize ? 
        Emit(generator, "add $%d, %%rsp\n", stackSize) : ZERO;

    while (!IsEmptyStack(&usedRegisters))
    {
        Emit(generator, "popq ");
        EmitRegister(generator, FULL_REGISTER(PopStack(&usedRegisters)));
        Emit(generator, "\n");
    }

    astRoot->reg = REGSITER_BY_SIZE(GetRegister(generator), ((Type*)astRoot->type)->size);

    Emit(generator, "mov %%rax, ");
    EmitRegister(generator, FULL_REGISTER(astRoot->reg));
    Emit(generator, "\n");
}

void GenerateStatements(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    CircularLinearLinkedListNode *statements = astRoot->childrenManager->nextNode;
    AbstractSyntaxTreeNode *currentStatement;

    do
    {
        currentStatement = statements->info;

        currentStatement->GenerationFunction ? 
            currentStatement->GenerationFunction(generator, statements->info) : ZERO;

        statements = statements->nextNode;
    } 
    while (statements != astRoot->childrenManager->nextNode);
}

void GenerateParameters(void *generator, AbstractSyntaxTreeNode *astNode, char **parameterRegisters)
{
    CircularLinearLinkedListNode *parameters = astNode->childrenManager->nextNode;
    AbstractSyntaxTreeNode *currentParameter;

    do
    {
        currentParameter = parameters->info;
        
        GenerateDeclaration(generator, currentParameter);

        Emit(generator, "mov ");
        Emit(generator, "%%%s, ", *parameterRegisters++);
        EmitMemoryAddress(generator, ((Symbol*)currentParameter->info)->memoryAddress);
        Emit(generator, "\n");

        parameters = parameters->nextNode;
    }
    while (parameters != astNode->childrenManager->nextNode);
}

void EmitFunctionStart(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, unsigned int size)
{
    AbstractSyntaxTreeNode *parametersList = astRoot->childrenManager->nextNode->info;
    Symbol *function = astRoot->info;

    Emit(generator, ".text\n.globl %s\n.type %s, @function\n%s:\n", function->name, function->name, function->name);
    Emit(generator, "pushq %%rbp\nmovq %%rsp, %%rbp\nsubq $%d, %%rsp\n", size);

    char *paramsRegisters[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    char **currentRegister = paramsRegisters;

    astRoot->childrenManager != astRoot->childrenManager->nextNode ?
        GenerateParameters(generator, parametersList, currentRegister) : ZERO;
}

void EmitFunctionEnd(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, unsigned char currentFunction, unsigned int size)
{
    Symbol *function = astRoot->info;

    Emit(generator, "RET_%d:\naddq $%d, %%rsp\npopq %%rbp\nret\n", currentFunction, size);
}

unsigned int AnalyzeFunctionSize(AbstractSyntaxTreeNode *astRoot, unsigned char functionNum)
{
    unsigned int size = ZERO;

    if (!astRoot)
    {
        return ZERO;
    }

    astRoot->GenerationFunction == GenerateDeclaration ? 
        size += (((Type*)((Symbol*)astRoot->info)->type)->size) : ZERO;

    astRoot->GenerationFunction == GenerateReturn ? 
        astRoot->label = functionNum : ZERO;

    CircularLinearLinkedListNode *child = astRoot->childrenManager;

    if (child) do
    {
        size += AnalyzeFunctionSize(child->info, functionNum);
        child = child->nextNode;
    } 
    while (child != astRoot->childrenManager);

    return (size);
}

void GenerateFunction(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot, unsigned short functionId)
{
    unsigned int functionSize = ZERO;
    
    functionSize = AnalyzeFunctionSize(astRoot, functionId);
    functionSize = ALIGN(functionSize, STACK_ALIGNMENT);

    astRoot->label = functionSize;
    generator->currentMemoryOffset = -functionSize;

    EmitFunctionStart(generator, astRoot, functionSize);
    GenerateStatements(generator, astRoot);
    EmitFunctionEnd(generator, astRoot, functionId, functionSize);
}

void GenerateFunctions(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    CircularLinearLinkedListNode *currentFunction = astRoot->childrenManager->nextNode;
    short memoryOffset = generator->currentMemoryOffset;
    unsigned int currentFunctionSize = ZERO;
    unsigned char currentFunctionId = ZERO;

    do
    {
        ((AbstractSyntaxTreeNode*)currentFunction->info)->childrenManager ? 
            GenerateFunction(generator, currentFunction->info, currentFunctionId++) : ZERO;

        generator->currentMemoryOffset = memoryOffset;
        currentFunction = currentFunction->nextNode;
    } 
    while (currentFunction != astRoot->childrenManager->nextNode);
}

#pragma endregion

void GenerateCode(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    GenerateFunctions(generator, astRoot);
}