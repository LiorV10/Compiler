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

    if (!astRoot->childrenManager || !astRoot->evaluateAsExpression)
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

//-----------------------------------------------------------------------------
//                                      Cast By Size                                     
//                                      -----                                  
//                                                                             
// General      : The function widens a register to fit a given size.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      reg - The register to widen (In)						                                        
//      size - The desired size (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//                                      Generate Symbol                                     
//                                      ---------------                                 
//                                                                             
// General      : The function generates code for loading a variable.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)				                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void GenerateSymbol(void *generator, AbstractSyntaxTreeNode *astNode)
{
    unsigned short typeSize = ((Type*)astNode->type)->size;

    if (((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        Emit(generator, "leaq %d(%%rbp), ", ((Symbol*)astNode->info)->memoryAddress);
        typeSize = QWORD_SIZE;
    }
    else
    {
        Emit(generator, "mov ");
        EmitRegisterOrAddress(generator, astNode);
        Emit(generator, ", ");
    }

    astNode->reg = astNode->reg ? astNode->reg : GetRegister(generator);
    astNode->reg = REGSITER_BY_SIZE(astNode->reg, MIN(typeSize, QWORD_SIZE));

    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

//-----------------------------------------------------------------------------
//                                  Generate Declaration                                     
//                                  --------------------                            
//                                                                             
// General      : The function generates code for variable declaration.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)				                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void GenerateDeclaration(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *init = astNode->childrenManager ? astNode->childrenManager->info : NULL;

    Symbol *decl = astNode->info;
    Type *type = astNode->type;

    if (init)
        init->GenerationFunction(generator, init);

    decl->memoryAddress = ((CodeGenerator *)generator)->currentMemoryOffset;   

    ((CodeGenerator *)generator)->currentMemoryOffset += type->size;

    if (init)
    {
        Load(generator, init);
        CastBySize(generator, &init->reg, type->size);

        Emit(generator, "mov ");
        EmitRegister(generator, init->reg);
        Emit(generator, ", ");
        EmitMemoryAddress(generator, decl->memoryAddress);
        Emit(generator, "\n");

        astNode->reg = init->reg;
    }
}

//-----------------------------------------------------------------------------
//                              Generate Arithmetic Expression                                     
//                              ------------------------------                                  
//                                                                             
// General      : The function generates code for an arithmetic expression.                                                            
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)							                                        
//                                                                             
// Return Value : The result of the operator and the two operands.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
void GenerateArithmeticExpression(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *expression = astNode->childrenManager->info;

    GenerateExpression(generator, expression);
    astNode->reg = expression->reg;
    astNode->lvalue = expression->lvalue;
    astNode->type = expression->type;
}

//-----------------------------------------------------------------------------
//                                  Generate Expression                                     
//                                  -------------------                                  
//                                                                             
// General      : The function generates an expression.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)							                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
void GenerateExpression(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    LabelAst(astRoot);
    SethiUllman(generator, astRoot);
    FreeRegister(generator, astRoot->reg);
}

//-----------------------------------------------------------------------------
//                                      Load                                     
//                                      ----                                  
//                                                                             
// General      : The function loads a pointer.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)					                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
void Load(void *generator, AbstractSyntaxTreeNode *astNode)
{
    astNode = astNode->GenerationFunction == GenerateArithmeticExpression ?
        astNode->childrenManager->info : astNode;
    
    if (astNode->GenerationFunction != GenerateDereference || 
        ((Type*)astNode->type)->type == STRUCT_TYPE ||
        ((Type*)astNode->type)->type == ARRAY_TYPE)
    {
        return;
    }

    Emit(generator, "mov (");
    EmitRegister(generator, astNode->reg);
    Emit(generator, "), ");

    CastBySize(generator, &astNode->reg, ((Type*)astNode->type)->size);

    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

//-----------------------------------------------------------------------------
//                                      Store                                     
//                                      -----                                  
//                                                                             
// General      : The function stores a register in memory.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      source - The ast represnting the source expression (In)							                                        
//      dest - The ast represnting the dest memory (In)							                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void Store(void *generator, AbstractSyntaxTreeNode *source, AbstractSyntaxTreeNode *dest)
{
    CastBySize(generator, &source->reg, ((Type*)dest->type)->size);

    Emit(generator, "mov ");
    EmitRegister(generator, source->reg);
    Emit(generator, ", ");

    if (dest->GenerationFunction == GenerateDereference)
    {
        Emit(generator, "("); 
        EmitRegister(generator, FULL_REGISTER(dest->reg)); 
        Emit(generator, ")");
    }
    else
    {
        EmitMemoryAddress(generator, ((Symbol*)dest->info)->memoryAddress);
    }

    Emit(generator, "\n");
}

//-----------------------------------------------------------------------------
//                                      Statements                                     
//                                      ----------                                 
//                                                                             
// General      : The following functions generate code for statements.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)					                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region Statements

void GenerateFor(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *init = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *step = astNode->childrenManager->nextNode->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->info;

    int bodyLabel = GetLabel(generator);
    int endLabel = GetLabel(generator);

    if (init->GenerationFunction)
        init->GenerationFunction(generator, init);

    EmitLabel(generator, bodyLabel);
    condition->GenerationFunction(generator, condition);

    Load(generator, condition);
    condition->reg = REGSITER_BY_SIZE(condition->reg, ((Type*)condition->type)->size);

    Emit(generator, "test ");
    EmitRegister(generator, condition->reg);
    Emit(generator, ", ");
    EmitRegister(generator, condition->reg);
    Emit(generator, "\n");

    Emit(generator, "jz .AG%d\n", endLabel);
    body->GenerationFunction(generator, body);

    if (step != body)
        step->GenerationFunction(generator, step);

    Emit(generator, "jmp .AG%d\n", bodyLabel);
    EmitLabel(generator, endLabel);
}

void GenerateWhile(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *body = astNode->childrenManager->info;
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;

    int bodyLabel = GetLabel(generator);
    int endLabel = GetLabel(generator);

    EmitLabel(generator, bodyLabel);
    condition->GenerationFunction(generator, condition);

    Load(generator, condition);
    condition->reg = REGSITER_BY_SIZE(condition->reg, ((Type*)condition->type)->size);

    Emit(generator, "test ");
    EmitRegister(generator, condition->reg);
    Emit(generator, ", ");
    EmitRegister(generator, condition->reg);
    Emit(generator, "\n");

    Emit(generator, "jz .AG%d\n", endLabel);
    body->GenerationFunction(generator, body);

    Emit(generator, "jmp .AG%d\n", bodyLabel);
    EmitLabel(generator, endLabel);
}

void GenerateIf(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *condition = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *body = astNode->childrenManager->nextNode->nextNode->info;
    AbstractSyntaxTreeNode *elseBody = astNode->childrenManager->info;

    condition->GenerationFunction(generator, condition);

    Load(generator, condition);

    Emit(generator, "test ");
    EmitRegister(generator, condition->reg);
    Emit(generator, ", ");
    EmitRegister(generator, condition->reg);
    Emit(generator, "\n");

    int falseLabel = GetLabel(generator);
    int continueLabel = GetLabel(generator);
    
    if (elseBody != body)
    {
        Emit(generator, "jz .AG%d\n", falseLabel);
        body->GenerationFunction(generator, body);
        Emit(generator, "jmp .AG%d\n", continueLabel);
        EmitLabel(generator, falseLabel);
        elseBody->GenerationFunction(generator, elseBody);
    }
    else
    {
        Emit(generator, "jz .AG%d\n", continueLabel);
        body->GenerationFunction(generator, body);
    }

    EmitLabel(generator, continueLabel);
}

void GenerateBlock(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    short offset = ((CodeGenerator*)generator)->currentMemoryOffset;

    GenerateStatements(generator, astRoot);

    ((CodeGenerator*)generator)->currentMemoryOffset = offset;
}

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Binary Operators                                     
//                                      ----------------                                 
//                                                                             
// General      : The following functions generate code for binary operators.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region BinaryOperators

void GenerateAssignment(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Type *leftType = left->type;

    Load(generator, right);
    Store(generator, right, left);

    if (left->reg)
    {
        CastBySize(generator, &right->reg, leftType->size);
        left->reg = REGSITER_BY_SIZE(left->reg, leftType->size);

        Emit(generator, "mov ");
        EmitRegister(generator, right->reg);
        Emit(generator, ", ");
        EmitRegister(generator, left->reg);
        Emit(generator, "\n");
    }

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateAddition(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    if (((Type*)left->type)->baseType)
    {
        CastBySize(generator, &right->reg, QWORD_SIZE);

        GenerateOffsetCalculation(generator, right, ((Type*)left->type)->baseType);
        Emit(generator, "leaq (");
        EmitRegister(generator, FULL_REGISTER(left->reg));
        Emit(generator, ", ");
        EmitRegister(generator, right->reg);
        Emit(generator, "), ");
        EmitRegister(generator, FULL_REGISTER(left->reg));
        Emit(generator, "\n");
    }
    else
    {
        CastBySize(generator, &right->reg, ((Type*)left->type)->size);
        left->reg = REGSITER_BY_SIZE(left->reg, ((Type*)left->type)->size);

        Emit(generator, "add ");
        EmitRegister(generator, right->reg);
        Emit(generator, ", ");
        EmitRegister(generator, left->reg);
        Emit(generator, "\n");
    }

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateSubtraction(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    if (((Type*)left->type)->baseType)
    {
        Emit(generator, "neg ");
        EmitRegister(generator, FULL_REGISTER(right->reg));
        Emit(generator, "\nleaq (");
        EmitRegister(generator, FULL_REGISTER(left->reg));
        Emit(generator, ", ");
        EmitRegister(generator, FULL_REGISTER(right->reg));
        Emit(generator, ", %d), ", ((Type*)left->type)->baseType->size);
        EmitRegister(generator, FULL_REGISTER(left->reg));
        Emit(generator, "\n");
    }
    else
    {
        CastBySize(generator, &right->reg, ((Type*)left->type)->size);
        left->reg = REGSITER_BY_SIZE(left->reg, ((Type*)left->type)->size);

        Emit(generator, "sub ");
        EmitRegister(generator, right->reg);
        Emit(generator, ", ");
        EmitRegister(generator, left->reg);
        Emit(generator, "\n");
    }

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateMult(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &right->reg, QWORD_SIZE);

    Emit(generator, "imul ");
    EmitRegister(generator, right->reg);
    Emit(generator, ", ");
    EmitRegister(generator, REGSITER_BY_SIZE(left->reg, QWORD_SIZE));
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateDivision(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, QWORD_SIZE);

    Emit(generator, "mov ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", %%rax\ncqo\nidiv ");

    EmitRegisterOrAddress(generator, right);

    Emit(generator, "\nmov %%rax, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateMod(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, QWORD_SIZE);

    Emit(generator, "mov ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", %%rax\ncqo\nidiv ");

    EmitRegisterOrAddress(generator, right);

    Emit(generator, "\nmov %%rdx, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateStructAccess(void *generator, AbstractSyntaxTreeNode *astNode)
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

        Emit(generator, "lea %d(", field->offset);
        EmitRegister(generator, structNode->reg);
        Emit(generator, ")");
    }
    else
    {
        astNode->reg = REGSITER_BY_SIZE(structNode->reg, field->type->size);

        Emit(generator, "mov ");
        EmitMemoryAddress(generator, ((Symbol*)astNode->info)->memoryAddress);
    }

    Emit(generator, ", ");
    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

void GenerateLT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

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

void GenerateLSHIFT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "shlx ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateRSHIFT(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "sarx ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateLE(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetle %%al\nmovsx %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateGE(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetge %%al\nmovsx %%al, ");
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

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "cmp ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nsetne %%al\nmovsx %%al, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateAnd(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &right->reg, QWORD_SIZE);
    CastBySize(generator, &left->reg, QWORD_SIZE);

    Emit(generator, "and ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

void GenerateLogicalAnd(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;
    int endLabel = GetLabel(generator);

    GenerateExpression(generator, left);
    Load(generator, left);

    Emit(generator, "test ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nmov $0, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nje .AG%d\n", endLabel);

    GenerateExpression(generator, right);
    Load(generator, right);

    Emit(generator, "test ");
    EmitRegister(generator, right->reg);
    Emit(generator, ", ");
    EmitRegister(generator, right->reg);
    Emit(generator, "\nmov $0, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\nje .AG%d", endLabel);
    Emit(generator, "\nmov $1, ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    EmitLabel(generator, endLabel);

    astNode->reg = REGSITER_BY_SIZE(GetRegister(generator), ((Type*)left->type)->size);

    Emit(generator, "mov ");
    EmitRegister(generator, left->reg);
    Emit(generator, ", ");
    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

void GenerateXor(void *generator, AbstractSyntaxTreeNode *astNode)
{
    AbstractSyntaxTreeNode *left = astNode->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astNode->childrenManager->info;

    Load(generator, left);
    Load(generator, right);

    CastBySize(generator, &left->reg, ((Type*)right->type)->size);

    Emit(generator, "xor ");
    EmitRegisterOrAddress(generator, right);
    Emit(generator, ", ");
    EmitRegister(generator, left->reg);
    Emit(generator, "\n");

    FreeRegister(generator, right->reg);
    astNode->reg = left->reg;
}

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Unary Operators                                     
//                                      ---------------                                 
//                                                                             
// General      : The following functions generate code for unary operators.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region UnaryOperators

void GenerateOffsetCalculation(void *generator, AbstractSyntaxTreeNode *astNode, Type *type)
{
    for (; type; type = type->baseType)
    {
        Emit(generator, "imul $%d, ", type->size);
        EmitRegister(generator, astNode->reg);
        Emit(generator, "\n");
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

void GenerateLogicalNot(void *generator, AbstractSyntaxTreeNode *astNode)
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

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Constants                                     
//                                      ---------                                 
//                                                                             
// General      : The following functions generate code for literal constants.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region Constants

void GenerateStringLiteral(void *generator, AbstractSyntaxTreeNode *astNode)
{
    int label = GetLabel(generator);

    astNode->reg = astNode->reg ? FULL_REGISTER(astNode->reg) : FULL_REGISTER(GetRegister(generator));

    Emit(generator, ".section .rodata\n");
    EmitLabel(generator, label);
    Emit(generator, ".string %s\n.text\n", ((Symbol*)astNode->info)->name);
    Emit(generator, "leaq .AG%d(%%rip), ", label);
    EmitRegister(generator, astNode->reg);
    Emit(generator, "\n");
}

void GenerateFloatLiteral(void *generator, AbstractSyntaxTreeNode *astNode)
{
    // NOT IMPLEMENTED
}

void GenerateIntegerLiteral(void *generator, AbstractSyntaxTreeNode *astNode)
{
    astNode->reg = astNode->reg ? astNode->reg : GetRegister(generator);

    Emit(generator, "mov $%s, ", ((Symbol*)astNode->info)->name);
    EmitRegister(generator, (astNode->reg = REGSITER_BY_SIZE(astNode->reg, ((Type*)astNode->type)->size)));
    Emit(generator, "\n");
}

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Functions                                     
//                                      ---------                              
//                                                                             
// General      : The following functions generate code for
//                function definitions and calls.                                                            
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)							                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region Functions

void GenerateReturn(void *generator, AbstractSyntaxTreeNode *astNode)
{
    Register result = REGSITER_BY_SIZE(EAX, QWORD_SIZE);
    AbstractSyntaxTreeNode *value;
    
    if (astNode->childrenManager)
    {
        value = astNode->childrenManager->info;
        value->GenerationFunction(generator, value);

        Load(generator, value);
        CastBySize(generator, &value->reg, QWORD_SIZE);

        Emit(generator, "mov ");
        EmitRegisterOrAddress(generator, value);
        Emit(generator, ", ");
        EmitRegister(generator, result);
        Emit(generator, "\n");
    }

    Emit(generator, "jmp RET_%d\n", astNode->label);
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

void GenerateCallWithoutParams(void *generator, AbstractSyntaxTreeNode *astRoot)
{
    Symbol *function = astRoot->info;
    LinearLinkedListNode *usedRegistersPtr;

    unsigned int stackSize = ZERO;

    Stack usedRegisters; 

    InitStack(&usedRegisters);

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
    
    Emit(generator, "call %s\n", function->name);
    
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

//-----------------------------------------------------------------------------
//                                      Generate Code                                     
//                                      -------------                                  
//                                                                             
// General      : The function generates code for a given ast.                                                           
//                                                                             
// Parameters   :                                                              
//      generator - The code generator context (In)						                                        
//      astNode - The ast represnting the expressions (In)							                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void GenerateCode(CodeGenerator *generator, AbstractSyntaxTreeNode *astRoot)
{
    GenerateFunctions(generator, astRoot);
}