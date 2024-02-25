// LinearLinkedList.h

#define _LINEAR_LINKED_LIST_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#define LINEAR_LINKED_LIST_NODE_TYPE void*

typedef struct LinearLinkedListNode
{
    LINEAR_LINKED_LIST_NODE_TYPE info;
    struct LinearLinkedListNode *nextNode;
} LinearLinkedListNode;

void InitLinearLinkedList(LinearLinkedListNode **manager);
BOOL IsEmptyLinearLinkedList(LinearLinkedListNode *manager);
void PushLinearLinkedList(LinearLinkedListNode **manager);
void AddAfterLinearLinkedList(LinearLinkedListNode *node);
void PopLinearLinkedList(LinearLinkedListNode **manager);
void DeleteAfterLinearLinkedList(LinearLinkedListNode *node);
void ReverseLinearLinkedList(LinearLinkedListNode **manager);
void ClearLinearLinkedList(LinearLinkedListNode **manager);
LinearLinkedListNode* BeforeMinInLinearLinkedList(LinearLinkedListNode *manager, 
                                            BOOL (*Compare)(void*, void*));
void AddToSortedLinearLinkedList(LinearLinkedListNode **manager, 
    LINEAR_LINKED_LIST_NODE_TYPE info, BOOL (*Compare)(void*, void*));
LinearLinkedListNode* FindNaturalPlaceLinearLinkedList(LinearLinkedListNode *manager, 
    LINEAR_LINKED_LIST_NODE_TYPE info, BOOL (*Compare)(void*, void*));