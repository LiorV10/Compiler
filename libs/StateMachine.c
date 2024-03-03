// StateMachine.c

#include "StateMachine.h"

void InitStateMachine(StateMachine *stateMachine)
{
    InitCircularLinearLinkedList(&stateMachine->statesManager);
}

State *AddState(StateMachine *statemachine)
{
    State *newState = malloc(sizeof(State));
    InitCircularLinearLinkedList(&newState->transitionsManager);

    !statemachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&statemachine->statesManager) :
        InsertEndCircularLinearLinkedList(&statemachine->statesManager);

    newState->isAccepting = FALSE;
    newState->visited = FALSE;
    
    statemachine->statesManager->info = newState;

    return (newState);
}

void AddTransition(StateMachine *statemachine, State *source, State *dest, char symbol)
{
    Transition *transition = malloc(sizeof(Transition));

    !source->transitionsManager ? 
        InsertLastCircularLinearLinkedList(&source->transitionsManager) :
        InsertEndCircularLinearLinkedList(&source->transitionsManager);

    transition->dest = dest;
    transition->symbol = symbol;
    source->transitionsManager->info = transition;
}

void SetAccepting(State *state)
{
    state->isAccepting = TRUE;
}

BOOL IsAccepting(State *state)
{
    return (state->isAccepting == TRUE);
}

void SetVisited(State *state, BOOL isVisited)
{
    state->visited = isVisited;
}

BOOL IsVisited(State *state)
{
    return (state->visited == TRUE);
}

State *FinalState(StateMachine *stateMachine)
{
    return (stateMachine->statesManager->info);
}

State *InitialState(StateMachine *stateMachine)
{
    return (stateMachine->statesManager->nextNode->info);
}

void SetAllVisited(StateMachine *stateMachine, BOOL visited)
{
    CircularLinearLinkedListNode *states = stateMachine->statesManager;

    do
    {
        SetVisited(states->info, visited);
        states = states->nextNode;
    } 
    while (states != stateMachine->statesManager);
}

void ConcatStateMachines(StateMachine *first, StateMachine *second)
{
    ConcatCircularLinearLinkedLists(&first->statesManager, second->statesManager);
}