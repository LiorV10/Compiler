// Stack.h

#define _STACK_H

#ifndef _COMMON_MACROS_H
#include "CommonMacros.h"
#endif

#ifndef _LINEAR_LINKED_LIST_H
#include "LinearLinkedList.h"
#endif

#define STACK_TYPE LINEAR_LINKED_LIST_NODE_TYPE

// Type definition
typedef struct
{
    LinearLinkedListNode *topOfStack;
} Stack;

// Function prototypes
void InitStack(Stack *iopstkStack);
BOOL IsEmptyStack(Stack *ipstkStack);
void PushStack(Stack *iopstkStack, STACK_TYPE itItem);
STACK_TYPE PopStack(Stack *iopstkStack);