// AbstractSyntaxTree.c

#include "AbstractSyntaxTree.h"

void MakeAbstractSyntaxTree(AbstractSyntaxTreeNode **root)
{
    *root = malloc(sizeof(AbstractSyntaxTreeNode));
    InitLinearLinkedList(&(*root)->childrenManager);
    (*root)->info = NULL;
}

AbstractSyntaxTreeNode** SetAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node)
{
    PushLinearLinkedList(&node->childrenManager);

    return (&node->childrenManager->info);
}