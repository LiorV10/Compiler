// PushdownMachine.c

#include "PushdownMachine.h"

void InitPushdownMachine(PushdownMachine *pushdownMachine)
{
    pushdownMachine->stack = malloc(sizeof(Stack));
    
    InitCircularLinearLinkedList(&pushdownMachine->statesManager);
    InitStack(pushdownMachine->stack);
}

PushdownState *AddPushdownState(PushdownMachine *stateMachine)
{
    PushdownState *newState = malloc(sizeof(PushdownState));

    InitCircularLinearLinkedList(&newState->transitionsManager);
    InitCircularLinearLinkedList(&newState->lrItems);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertEndCircularLinearLinkedList(&stateMachine->statesManager);

    newState->isAccepting = FALSE;
    stateMachine->statesManager->info = newState;

    return (newState);
}

void AddPushdownTransition(PushdownMachine *stateMachine, PushdownState *source, PushdownState *dest, SYMBOL_TYPE symbol)
{
    PushdownTransition *transition = malloc(sizeof(PushdownTransition));

    !source->transitionsManager ? 
        InsertLastCircularLinearLinkedList(&source->transitionsManager) :
        InsertEndCircularLinearLinkedList(&source->transitionsManager);

    transition->dest = dest;
    transition->symbol = symbol;
    source->transitionsManager->info = transition;
}

PushdownState *FinalPushdownState(PushdownMachine *stateMachine)
{
    return (stateMachine->statesManager->info);
}

PushdownState *InitialPushdownState(PushdownMachine *stateMachine)
{
    return (stateMachine->statesManager->nextNode->info);
}

void EmptyItems(CircularLinearLinkedListNode **items)
{
    CircularLinearLinkedListNode *ptr = *items;

    do
    {
        free(ptr->info);
        ptr = ptr->nextNode;
    }
    while (ptr != *items);

    EmptyCircularLinearLinkedList(items);
}

void EmptyPushdownState(PushdownState *state)
{
    state->transitionsManager ? EmptyItems(&state->transitionsManager) : ZERO;
    state->lrItems ? EmptyItems(&state->lrItems) : ZERO;

    free(state);
}

void EmptyPushdownMachine(PushdownMachine *stateMachine)
{
    CircularLinearLinkedListNode *ptr = stateMachine->statesManager;

    do
    {
        EmptyPushdownState(ptr->info);
        ptr = ptr->nextNode;
    }   
    while (ptr != stateMachine->statesManager);

    while (!IsEmptyStack(stateMachine->stack))
    {
        PopStack(stateMachine->stack);
    }

    EmptyCircularLinearLinkedList(&stateMachine->statesManager);
    free(stateMachine->stack);
    free(stateMachine);
}
