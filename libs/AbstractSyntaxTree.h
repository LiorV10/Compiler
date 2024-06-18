// AbstractSyntaxTree.h

#define _ABSTRACT_SYNTAX_TREE_H

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

#ifndef _SYMBOL_TABLE_H
    #include "SymbolTable.h"
#endif

typedef struct AbstractSyntaxTreeNode AbstractSyntaxTreeNode;

struct AbstractSyntaxTreeNode
{
    unsigned short reg;
    void *info;
    BOOL lvalue;
    BOOL evaluateAsExpression;
    unsigned short label;
    void *type;
    void *field;
    void (*GenerationFunction)(void *codeGenerator, AbstractSyntaxTreeNode *astRoot);
    void (*AnalysisFunction)(AbstractSyntaxTreeNode *astRoot, void *errors);
    CircularLinearLinkedListNode *childrenManager;
};

void MakeAbstractSyntaxTree(AbstractSyntaxTreeNode **root);
AbstractSyntaxTreeNode** SetAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node);
void FreeAbstractSyntaxTree(AbstractSyntaxTreeNode *astRoot);