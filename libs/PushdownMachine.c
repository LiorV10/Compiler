// PushdownMachine.c

#include "PushdownMachine.h"

static int __numOfStates = 0;

void InitPushdownMachine(PushdownMachine *pushdownMachine)
{
    pushdownMachine->stack = malloc(sizeof(Stack));
    
    InitCircularLinearLinkedList(&pushdownMachine->statesManager);
    InitStack(pushdownMachine->stack);
}

PushdownState *AddPushdownState(PushdownMachine *stateMachine)
{
    __numOfStates++;
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

void EmptyPushdownState(PushdownState *state)
{
    state->transitionsManager ? EmptyCircularLinearLinkedList(&state->transitionsManager, free) : ZERO;
    state->lrItems ? EmptyCircularLinearLinkedList(&state->lrItems, free) : ZERO;

    free(state);
}

void EmptyPushdownMachine(PushdownMachine *stateMachine)
{
    printf("\nNum of States: %d\n", __numOfStates);

    while (!IsEmptyStack(stateMachine->stack))
    {
        PopStack(stateMachine->stack);
    }

    EmptyCircularLinearLinkedList(&stateMachine->statesManager, EmptyPushdownState);
    free(stateMachine->stack);
    free(stateMachine);
}
