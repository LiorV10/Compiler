// SemanticAnalyzer.c

#include "SemanticAnalyzer.h"

typedef enum {PLUS_OP, MINUS_OP, STAR_SLASH_OP, MOD_OP, LOGICAL_OP, BITWISE_OP, RELATIONAL_OP, ASSIGNMENT_OP, OPERATORS_COUNT} Operator;

#define ERROR_TYPE TYPES_COUNT
#define OPERATOR_NAMES {"addition", "subtraction", "multiplication", "mod", "logical", "bitwise", "relational", "assignment"}
#define TYPE_NAMES {"char", "short", "integer", "long", "float", "double", "void", NULL, "pointer", "array", "struct"}

TypeKind typesMatrix[TYPES_COUNT][TYPES_COUNT][OPERATORS_COUNT] = 
{
    // +-        */        %         logical    bitwise    relational   assignment

    [CHAR_TYPE] = 
    {
        [CHAR_TYPE] =       {CHAR_TYPE, CHAR_TYPE, CHAR_TYPE,  CHAR_TYPE, CHAR_TYPE, CHAR_TYPE, CHAR_TYPE, CHAR_TYPE},
        [SHORT_TYPE] =      {SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, CHAR_TYPE},
        [INTEGER_TYPE] =    {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, CHAR_TYPE},
        [LONG_TYPE] =       {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, CHAR_TYPE},
        [FLOAT_TYPE] =      {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, CHAR_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, CHAR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, CHAR_TYPE},
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, CHAR_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [SHORT_TYPE] = 
    {
        [CHAR_TYPE] =       {SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE},
        [SHORT_TYPE] =      {SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE},
        [INTEGER_TYPE] =    {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, SHORT_TYPE},
        [LONG_TYPE] =       {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, SHORT_TYPE},
        [FLOAT_TYPE] =      {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, SHORT_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, SHORT_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, SHORT_TYPE},
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, SHORT_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [INTEGER_TYPE] = 
    {
        [CHAR_TYPE] =       {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE},
        [SHORT_TYPE] =      {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE},
        [INTEGER_TYPE] =    {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE},
        [LONG_TYPE] =       {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, INTEGER_TYPE},
        [FLOAT_TYPE] =      {FLOAT_TYPE, FLOAT_LITERAL, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, INTEGER_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, INTEGER_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, INTEGER_TYPE},
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, INTEGER_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [LONG_TYPE] = 
    {
        [CHAR_TYPE] =       {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE},
        [SHORT_TYPE] =      {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE},
        [INTEGER_TYPE] =    {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE},
        [LONG_TYPE] =       {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE},
        [FLOAT_TYPE] =      {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, LONG_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, LONG_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, LONG_TYPE},
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, LONG_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [FLOAT_TYPE] = 
    {
        [CHAR_TYPE] =       {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [SHORT_TYPE] =      {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [INTEGER_TYPE] =    {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [LONG_TYPE] =       {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [FLOAT_TYPE] =      {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, FLOAT_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [DOUBLE_TYPE] = 
    {
        [CHAR_TYPE] =       {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [SHORT_TYPE] =      {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [INTEGER_TYPE] =    {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [LONG_TYPE] =       {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [FLOAT_TYPE] =      {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [DOUBLE_TYPE] =     {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [VOID_TYPE] = 
    {
        [CHAR_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [SHORT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [INTEGER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [LONG_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [FLOAT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [DOUBLE_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [POINTER_TYPE] = 
    {
        [CHAR_TYPE] =       {POINTER_TYPE, POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [SHORT_TYPE] =      {POINTER_TYPE, POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [INTEGER_TYPE] =    {POINTER_TYPE, POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [LONG_TYPE] =       {POINTER_TYPE, POINTER_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [FLOAT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [DOUBLE_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, LONG_TYPE, ERROR_TYPE, CHAR_TYPE, POINTER_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [ARRAY_TYPE] = 
    {
        [CHAR_TYPE] =       {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [SHORT_TYPE] =      {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [INTEGER_TYPE] =    {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [LONG_TYPE] =       {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [FLOAT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [DOUBLE_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    },

    [STRUCT_TYPE] = 
    {
        [CHAR_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [SHORT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [INTEGER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [LONG_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [FLOAT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [DOUBLE_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [STRUCT_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    }
};

//-----------------------------------------------------------------------------
//                              Analyze Struct Access                                     
//                              ---------------------                                  
//                                                                             
// General      : The function analyzes semantics of struct access expression.                                                           
//                                                                             
// Parameters   :                                                              
//      astNode - The ast represnting the expression (In)						                                        
//      errors - The errors handler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void AnalyzeStructAccess(AbstractSyntaxTreeNode **astNode, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *structNode = (*astNode)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *fieldNode = (*astNode)->childrenManager->info;

    (*astNode)->type = ((Field*)fieldNode->field)->type;
    (*astNode)->lvalue = TRUE;
}

//-----------------------------------------------------------------------------
//                              Analyze Reference                                     
//                              -----------------                                 
//                                                                             
// General      : The function analyzes semantics of reference expression.                                                           
//                                                                             
// Parameters   :                                                              
//      astNode - The ast represnting the expression (In)						                                        
//      errors - The errors handler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void AnalyzeReference(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    (*astRoot)->lvalue = FALSE;

    if (!operand->lvalue) 
    { MakeError(errors, "Expression must be lvalue"); return;}

    if (operand->AnalysisFunction == AnalyzeDereference)
    {
        *astRoot = operand->childrenManager->info;
    }

    Type *type = malloc(sizeof(Type));
    type->type = POINTER_TYPE;
    type->size = ((unsigned short[])TYPE_SIZES)[POINTER_TYPE];

    if (operand->type)
        type->baseType = operand->type;
    else
        type->baseType = ((Symbol*)operand->info)->type;

    (*astRoot)->type = type;
}

//-----------------------------------------------------------------------------
//                              Analyze Dereference                                     
//                              -------------------                                 
//                                                                             
// General      : The function analyzes semantics of dereference expression.                                                           
//                                                                             
// Parameters   :                                                              
//      astNode - The ast represnting the expression (In)						                                        
//      errors - The errors handler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void AnalyzeDereference(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    (*astRoot)->lvalue = TRUE;
    operand->lvalue = TRUE;

    if (operand->AnalysisFunction == AnalyzeReference)
    {
        *astRoot = operand->childrenManager->info;
    }

    (*astRoot)->type = operand->type;

    !((Type*)(*astRoot)->type)->baseType || !((Type*)(*astRoot)->type)->baseType->size ?
        MakeError(errors, "`%s` must be a pointer to a complete type", ((Symbol*)operand->info)->name) :
        ((*astRoot)->type = ((Type*)operand->type)->baseType);
}

//-----------------------------------------------------------------------------
//                                      Analyze Types                                     
//                                      -----                                  
//                                                                             
// General      : The function analyzes correctnes of simple expression.                                                           
//                                                                             
// Parameters   :                                                              
//      left - The type of the left operand (In)						                                        
//      right - The type of the right operand (In)						                                        
//      operator - The operator (In)						                                        
//      errors - The errors handler context (In)						                                        					                                        
//                                                                             
// Return Value : The result type.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
TypeKind AnalyzeTypes(TypeKind left, TypeKind right, Operator operator, ErrorHandler *errors)
{
    TypeKind resultType;
    char *typeNames[] = TYPE_NAMES;
    char *operatorNames[] = OPERATOR_NAMES;

    resultType = typesMatrix[left][right][operator];

    resultType == ERROR_TYPE ?
        MakeError(errors, "%s operator can't be used between %s and %s", 
            operatorNames[operator], typeNames[left], typeNames[right]) : ZERO;
}

//-----------------------------------------------------------------------------
//                                      Analyze Operators                                     
//                                      -----------------                                 
//                                                                             
// General      : The following functions analyzes semantics
//                of specific operators.                                                            
//                                                                             
// Parameters   :                                                               
//      astNode - The ast represnting the expression (In)						                                        
//      errors - The errors handler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
#pragma region AnalyzeOperators

Type* AnalyzeBinaryOperator(AbstractSyntaxTreeNode *astRoot, Operator operator, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *left = astRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astRoot->childrenManager->info;

    TypeKind resultType;

    right->GenerationFunction == GenerateArithmeticExpression ? 
        right = right->childrenManager->info : ZERO;

    left->GenerationFunction == GenerateArithmeticExpression ? 
        left = left->childrenManager->info : ZERO;
    
    resultType = AnalyzeTypes(((Type*)left->type)->type, ((Type*)right->type)->type, operator, errors);

    astRoot->type = left->type;
    ((Type*)right->type)->type == resultType ? astRoot->type = right->type : ZERO;

    return (astRoot->type);
}

void AnalyzeAssignment(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *left = (*astRoot)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = (*astRoot)->childrenManager->info;
    
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, ASSIGNMENT_OP, errors);

    if (!left->lvalue)
        MakeError(errors, "`%s` is not a modifiable lvalue", ((Symbol*)left->info)->name);
}

void AnalyzeDeclaration(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *left = (*astRoot)->childrenManager->nextNode->info;

    left->type = (*astRoot)->type;

    if (left != (*astRoot)->childrenManager->info)
        AnalyzeAssignment(astRoot, errors);
}

void AnalyzeAddition(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, PLUS_OP, errors);
}

void AnalyzeSubtraction(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, MINUS_OP, errors);
}

void AnalyzeMultDiv(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, STAR_SLASH_OP, errors);
}

void AnalyzeMod(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, MOD_OP, errors);
}

void AnalyzeRelational(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, RELATIONAL_OP, errors);
}

void AnalyzeBitwise(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, BITWISE_OP, errors);
}

void AnalyzeLogical(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, LOGICAL_OP, errors);
}

void AnalyzeNeg(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    TypeKind type = typesMatrix[((Type*)operand->type)->type][((Type*)operand->type)->type][MINUS_OP];

    if (type == ((Type*)operand->type)->type)
        (*astRoot)->type = operand->type;
    else
        MakeError(errors, "Illegal operation");
}

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Analyze Semantics                                     
//                                      -----------------                                  
//                                                                             
// General      : The function analyzes semantics of a given ast.                                                            
//                                                                             
// Parameters   :                                                              
//      astNode - The ast represnting the expression (In)						                                        
//      errors - The errors handler context (In)							                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = k * T(n/k) + O(1) -> O(n)
//-----------------------------------------------------------------------------
void AnalyzeSemantics(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    if (!(*astRoot)->childrenManager)
    {
        return;
    }

    CircularLinearLinkedListNode *child = (*astRoot)->childrenManager->nextNode;

    do
    {
        AnalyzeSemantics(&child->info, errors);
        child = child->nextNode;
    }
    while (child != (*astRoot)->childrenManager->nextNode);

    errors->currentLine = (*astRoot)->label;

    if ((*astRoot)->AnalysisFunction)
        (*astRoot)->AnalysisFunction(astRoot, errors);
}