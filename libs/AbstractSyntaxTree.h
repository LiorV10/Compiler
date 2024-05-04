// AbstractSyntaxTree.h

#define _ABSTRACT_SYNTAX_TREE_H

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _SYMBOL_TABLE_H
    #include "SymbolTable.h"
#endif

typedef struct
{
    void *info;
    LinearLinkedListNode *childrenManager;
} AbstractSyntaxTreeNode;

void MakeAbstractSyntaxTree(AbstractSyntaxTreeNode **root);
AbstractSyntaxTreeNode** SetAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node);