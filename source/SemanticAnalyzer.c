// SemanticAnalyzer.c

#include "SemanticAnalyzer.h"

typedef enum {PLUS_OP, MINUS_OP, STAR_SLASH_OP, MOD_OP, LOGICAL_OP, BITWISE_OP, RELATIONAL_OP, ASSIGNMENT_OP, OPERATORS_COUNT} Operator;

#define ERROR_TYPE TYPES_COUNT
#define OPERATOR_NAMES {"addition", "subtraction", "multiplication", "mod", "conditional", "bitwise", "relational", "assignment"}
#define TYPE_NAMES {"char", "short", "integer", "long", "float", "double", "void", NULL, "pointer", "array"}

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
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, CHAR_TYPE}
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
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, SHORT_TYPE}
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
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, INTEGER_TYPE}
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
        [ARRAY_TYPE] =      {ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, LONG_TYPE}
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
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, FLOAT_TYPE}
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
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, DOUBLE_TYPE}
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
        [ARRAY_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
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
        [POINTER_TYPE] =    {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, POINTER_TYPE}
    },

    [ARRAY_TYPE] = 
    {
        [CHAR_TYPE] =       {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [SHORT_TYPE] =      {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [INTEGER_TYPE] =    {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [LONG_TYPE] =       {ARRAY_TYPE, ARRAY_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [FLOAT_TYPE] =      {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [DOUBLE_TYPE] =     {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [VOID_TYPE] =       {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] =    {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [ARRAY_TYPE] =      {ERROR_TYPE, LONG_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE}
    }
};

void AnalyzeStructAccess(AbstractSyntaxTreeNode **astNode, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *structNode = (*astNode)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *fieldNode = (*astNode)->childrenManager->info;

    (*astNode)->type = ((Field*)fieldNode->field)->type;
    (*astNode)->lvalue = TRUE;
}

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

void AnalyzeDereference(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    (*astRoot)->lvalue = TRUE;
    operand->lvalue = TRUE;

    if (operand->AnalysisFunction == AnalyzeReference)
    {
        *astRoot = operand->childrenManager->info;
    }

    (*astRoot)->type = ((Type*)operand->type)->baseType;

    !(*astRoot)->type ?
        MakeError(errors, "`%s` must be a pointer", ((Symbol*)operand->info)->name) : ZERO;
}

Type* AnalyzeBinaryOperator(AbstractSyntaxTreeNode *astRoot, ErrorHandler *errors, Operator operator)
{
    AbstractSyntaxTreeNode *left = astRoot->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = astRoot->childrenManager->info;

    char *typeNames[] = TYPE_NAMES;
    char *operatorNames[] = OPERATOR_NAMES;

    right->GenerationFunction == GenerateArithmeticExpression ? 
        right = right->childrenManager->info : ZERO;

    Type *leftType = left->type;
    Type *rightType = right->type;
    
    TypeKind t;

    if (leftType && rightType)
    {
        t = typesMatrix[leftType->type][rightType->type][operator];
    }

    if (t == ERROR_TYPE)
    {
        if (leftType && rightType)
        MakeError(errors, "%s operator can't be used between %s and %s", 
            operatorNames[operator], typeNames[leftType->type], typeNames[rightType->type]);
    }

    astRoot->type = leftType;

    if (rightType && rightType->type == t) astRoot->type = rightType;

    return astRoot->type;
}

void AnalyzeAssignment(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    AbstractSyntaxTreeNode *left = (*astRoot)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = (*astRoot)->childrenManager->info;
    
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, errors, ASSIGNMENT_OP);

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
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, errors, PLUS_OP);
}

void AnalyzeSubtraction(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, errors, MINUS_OP);
}

void AnalyzeMultDiv(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, errors, STAR_SLASH_OP);
}

void AnalyzeMod(AbstractSyntaxTreeNode **astRoot, ErrorHandler *errors)
{
    (*astRoot)->type = AnalyzeBinaryOperator(*astRoot, errors, MOD_OP);
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