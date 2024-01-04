// LinearLinkedList.h

#define _LINEAR_LINKED_LIST_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#include "Token.c"

#define LINEAR_LINKED_LIST_NODE_TYPE Token

typedef struct Node
{
    LINEAR_LINKED_LIST_NODE_TYPE info;
    struct Node *nextNode;
} LinearLinkedListNode;

void InitLinearLinkedList(LinearLinkedListNode **manager);
BOOL IsEmptyLinearLinkedList(LinearLinkedListNode *manager);
void PushLinearLinkedList(LinearLinkedListNode **manager);
void AddAfterLinearLinkedList(LinearLinkedListNode *node);
void PopLinearLinkedList(LinearLinkedListNode **manager);
void DeleteAfterLinearLinkedList(LinearLinkedListNode *node);
void ReverseLinearLinkedList(LinearLinkedListNode **manager);
void ClearLinearLinkedList(LinearLinkedListNode **manager);