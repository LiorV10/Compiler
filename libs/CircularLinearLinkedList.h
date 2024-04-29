// CircularLinearLinkedList.h

#define _CIRCULAR_LINEAR_LINKED_LIST_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#define CIRCULAR_LINEAR_LINKED_LIST_NODE_TYPE void*

typedef struct CircularLinearLinkedListNode
{
    CIRCULAR_LINEAR_LINKED_LIST_NODE_TYPE info;
    struct CircularLinearLinkedListNode *nextNode;
} CircularLinearLinkedListNode;

void InitCircularLinearLinkedList(CircularLinearLinkedListNode **manager);
void InsertAfterCircularLinearLinkedList(CircularLinearLinkedListNode *node);
void InsertLastCircularLinearLinkedList(CircularLinearLinkedListNode **manager);
void InsertEndCircularLinearLinkedList(CircularLinearLinkedListNode **manager);
void DeleteAfterCircularLinearLinkedList(CircularLinearLinkedListNode *node);
void DeleteLastCircularLinearLinkedList(CircularLinearLinkedListNode **manager);
void DeleteEndCircularLinearLinkedList(CircularLinearLinkedListNode **manager);
void ConcatCircularLinearLinkedLists(CircularLinearLinkedListNode **first,
                                     CircularLinearLinkedListNode *second);
void EmptyCircularLinearLinkedList(CircularLinearLinkedListNode **manager, void(*Free)(void *));