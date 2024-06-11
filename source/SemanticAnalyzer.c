// SemanticAnalyzer.c

#include "SemanticAnalyzer.h"

typedef enum {PLUS_OP, MINUS_OP, STAR_OP, SLASH_OP, OPERATORS_COUNT} Operator;

#define ERROR_TYPE TYPES_COUNT

TypeKind typesMatrix[TYPES_COUNT][TYPES_COUNT][OPERATORS_COUNT] = 
{
    //   +  -  *  /

    [CHAR_TYPE] = 
    {
        [CHAR_TYPE] = {CHAR_TYPE, CHAR_TYPE, CHAR_TYPE, CHAR_TYPE},
        [SHORT_TYPE] = {SHORT_TYPE, SHORT_TYPE, SHORT_TYPE, SHORT_TYPE},
        [INTEGER_TYPE] = {INTEGER_TYPE, INTEGER_TYPE, INTEGER_TYPE ,INTEGER_TYPE},
        [LONG_TYPE] = {LONG_TYPE, LONG_TYPE, LONG_TYPE, LONG_TYPE},
        [FLOAT_TYPE] = {FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE, FLOAT_TYPE},
        [DOUBLE_TYPE] = {DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE, DOUBLE_TYPE},
        [VOID_TYPE] = {ERROR_TYPE, ERROR_TYPE, ERROR_TYPE, ERROR_TYPE},
        [POINTER_TYPE] = {POINTER_TYPE, POINTER_TYPE, ERROR_TYPE, ERROR_TYPE},
        [ARRAY_TYPE] = {},
    },

    [INTEGER_TYPE] = 
    {
        [INTEGER_TYPE] = {INTEGER_TYPE, INTEGER_TYPE},
        [LONG_TYPE] = {LONG_TYPE, LONG_TYPE}
    },

    [LONG_TYPE] = 
    {
        [INTEGER_TYPE] = {LONG_TYPE, LONG_TYPE}  
    },

    [POINTER_TYPE] = 
    {
        [INTEGER_TYPE] = {POINTER_TYPE, POINTER_TYPE},
        [LONG_TYPE] = {POINTER_TYPE, POINTER_TYPE},
        [CHAR_TYPE] = {POINTER_TYPE, POINTER_TYPE}
    },
};

void AnalyzeStructAccess(AbstractSyntaxTreeNode **astNode)
{
    AbstractSyntaxTreeNode *structNode = (*astNode)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *fieldNode = (*astNode)->childrenManager->info;

    (*astNode)->type = ((Field*)fieldNode->field)->type;
    (*astNode)->lvalue = TRUE;
}

void AnalyzeReference(AbstractSyntaxTreeNode **astRoot)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    operand->lvalue = TRUE;
    (*astRoot)->lvalue = FALSE;

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
        type->baseType = ((Symbol*)operand->info)->_type;

    (*astRoot)->type = type;
}

void AnalyzeDereference(AbstractSyntaxTreeNode **astRoot)
{
    AbstractSyntaxTreeNode *operand = (*astRoot)->childrenManager->info;
    (*astRoot)->lvalue = TRUE;
    operand->lvalue = TRUE;

    if (operand->AnalysisFunction == AnalyzeReference)
    {
        *astRoot = operand->childrenManager->info;
    }

    if (operand->type)
        (*astRoot)->type = ((Type*)operand->type)->baseType;
    else 
        {(*astRoot)->type = ((Type*)((Field*)operand->field)->type)->baseType;}

}

void AnalyzeAddition(AbstractSyntaxTreeNode **astRoot)
{
    AbstractSyntaxTreeNode *left = (*astRoot)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = (*astRoot)->childrenManager->info;

    Type *leftType = left->type;
    Type *rightType = right->type;

    TypeKind t;

    if (leftType && rightType)
    {
        t = typesMatrix[leftType->type][rightType->type][PLUS_OP];
    }

    (*astRoot)->type = leftType;

    if (rightType && rightType->type == t) (*astRoot)->type = rightType;
}

void AnalyzeSubtraction(AbstractSyntaxTreeNode **astRoot)
{
    AbstractSyntaxTreeNode *left = (*astRoot)->childrenManager->nextNode->info;
    AbstractSyntaxTreeNode *right = (*astRoot)->childrenManager->info;

    Type *leftType = left->type;
    Type *rightType = right->type;

    TypeKind t;

    if (leftType && rightType)
    {
        t = typesMatrix[leftType->type][rightType->type][MINUS_OP];
        int a = 0;
    }

    (*astRoot)->type = leftType;

    if (rightType && rightType->type == t) (*astRoot)->type = rightType;
}

void Semantics(AbstractSyntaxTreeNode **astRoot)
{
    if (!(*astRoot)->childrenManager)
    {
        return;
    }

    CircularLinearLinkedListNode *child = (*astRoot)->childrenManager->nextNode;

    do
    {
        Semantics(&child->info);
        child = child->nextNode;
    }
    while (child != (*astRoot)->childrenManager->nextNode);

    if ((*astRoot)->AnalysisFunction)
        (*astRoot)->AnalysisFunction(astRoot);
}