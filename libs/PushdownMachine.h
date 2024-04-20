// PushdownMachine.h

#define _PUSHDOWN_MACHINE_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

#ifndef _STACK_H
    #include "Stack.h"
#endif

typedef struct
{
    BOOL isAccepting;
    CircularLinearLinkedListNode *lrItems;
    CircularLinearLinkedListNode *transitionsManager;
} PushdownState;

typedef struct
{
    void *symbol;
    PushdownState *dest;
} PushdownTransition;

typedef struct
{
    CircularLinearLinkedListNode *statesManager;
    Stack *stack;
} PushdownMachine;

void InitPushdownMachine(PushdownMachine *pushdownMachine);