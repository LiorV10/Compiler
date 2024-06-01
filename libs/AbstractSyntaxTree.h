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
    void *reg;
    void *info;
    BOOL lvalue;
    unsigned char label;
    unsigned char type;
    void (*GenerationFunction)(void *codeGenerator, AbstractSyntaxTreeNode *astRoot);
    CircularLinearLinkedListNode *childrenManager;
};

void MakeAbstractSyntaxTree(AbstractSyntaxTreeNode **root);
AbstractSyntaxTreeNode** SetAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node);
AbstractSyntaxTreeNode** SetFirstAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node);