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

#ifndef _GRAMMAR_H
    #include "Grammar.h"
#endif

#ifndef _DICTIONARY_H
    #include "Dictionary.h"
#endif

#define SYMBOL_TYPE ExpressionValue

typedef struct
{
    BOOL isAccepting : TWO;
    CircularLinearLinkedListNode *lrItems;
    CircularLinearLinkedListNode *transitionsManager;
    // Dictionary transitions;
    unsigned long key;
} PushdownState;

typedef struct
{
    SYMBOL_TYPE symbol;
    PushdownState *dest;
} PushdownTransition;

typedef struct
{
    CircularLinearLinkedListNode *statesManager;
    Stack *stack;
} PushdownMachine;

void InitPushdownMachine(PushdownMachine *pushdownMachine);
PushdownState *AddPushdownState(PushdownMachine *stateMachine);
void AddPushdownTransition(PushdownMachine *stateMachine, PushdownState *source, PushdownState *dest, SYMBOL_TYPE symbol);
PushdownState *FinalPushdownState(PushdownMachine *stateMachine);
PushdownState *InitialPushdownState(PushdownMachine *stateMachine);
void EmptyPushdownMachine(PushdownMachine *stateMachine);