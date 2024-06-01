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

    // InitDictionary(&newState->transitions);
    InitCircularLinearLinkedList(&newState->transitionsManager);
    InitCircularLinearLinkedList(&newState->lrItems);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertEndCircularLinearLinkedList(&stateMachine->statesManager);

    newState->isAccepting = FALSE;
    newState->key = ZERO;
    stateMachine->statesManager->info = newState;

    return (newState);
}

unsigned long TransitionKey1(PushdownTransition *transition)
{
    return (transition->symbol.nonTerminal);
}

unsigned long TransitionKey2(PushdownTransition *transition)
{
    return (transition->symbol.terminal);
}

unsigned long Expression1(ExpressionValue *e)
{
    return (e->nonTerminal);
}

unsigned long Expression2(ExpressionValue *e)
{
    return (e->terminal);
}

BOOL CompareTransitions1(PushdownTransition *first, ExpressionValue *expressionValue)
{
    return first->symbol.nonTerminal == expressionValue->nonTerminal;
}

BOOL CompareTransitions2(PushdownTransition *first, ExpressionValue *expressionValue)
{
    return first->symbol.terminal == expressionValue->terminal;
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
    // EmptyDictionary(&state->transitions, NULL);
    state->transitionsManager ? EmptyCircularLinearLinkedList(&state->transitionsManager, free) : ZERO;
    state->lrItems ? EmptyCircularLinearLinkedList(&state->lrItems, free) : ZERO;

    free(state);
}

void EmptyPushdownMachine(PushdownMachine *stateMachine)
{
    while (!IsEmptyStack(stateMachine->stack))
    {
        PopStack(stateMachine->stack);
    }

    EmptyCircularLinearLinkedList(&stateMachine->statesManager, EmptyPushdownState);
    free(stateMachine->stack);
    free(stateMachine);
}
