// Queue.h

#define _QUEUE_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

#define QUEUE_TYPE CIRCULAR_LINEAR_LINKED_LIST_NODE_TYPE

// Type definition

typedef struct
{
    CircularLinearLinkedListNode *rear;
} Queue;

// Function prototypes
void InitQueue(Queue *iopqQueue);
void InsertQueue(Queue *iopqQueue, QUEUE_TYPE itItem);
QUEUE_TYPE RemoveQueue(Queue *iopqQueue);
BOOL IsEmptyQueue(Queue *ipqQueue);
QUEUE_TYPE Peek(Queue *ipqQueue);