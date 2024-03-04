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

StateMachine *FromSymbol(char symbol)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine);
    State *end = AddState(stateMachine);

    AddTransition(stateMachine, start, end, symbol);

    return (stateMachine);
}

StateMachine *Concat(StateMachine *first, StateMachine *second, BOOL applyTransition)
{
    State *firstEnd = FinalState(first);
    State *secondStart = InitialState(second);
    ConcatStateMachines(first, second);
    applyTransition ? AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION) : ZERO;

    return (first);
}

StateMachine *Union(StateMachine *first, StateMachine *second)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine);
    State *secondStart = InitialState(second);
    State *secondEnd = FinalState(second);
    State *end;

    stateMachine = Concat(stateMachine, first, TRUE);
    stateMachine = Concat(stateMachine, second, FALSE);
    AddTransition(stateMachine, start, secondStart, EPSILON_TRANSITION);
    end = AddState(stateMachine);
    AddTransition(stateMachine, FinalState(first), end, EPSILON_TRANSITION);
    AddTransition(stateMachine, secondEnd, end, EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *OneOrMore(StateMachine *previous)
{
    State *start = InitialState(previous);
    State *end = FinalState(previous);

    AddTransition(previous, end, start, EPSILON_TRANSITION);

    return (previous);
}

StateMachine *Star(StateMachine *previous)
{
    previous = OneOrMore(previous);

    AddTransition(previous, FinalState(previous), InitialState(previous), EPSILON_TRANSITION);
    AddTransition(previous, InitialState(previous), FinalState(previous), EPSILON_TRANSITION);

    return (previous);
}

StateMachine *Alternate(StateMachine *previous)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitStateMachine(newStart);

    State *start = AddState(newStart);
    State *end = FinalState(previous);

    AddTransition(previous, end, AddState(previous), EPSILON_TRANSITION);
    end = FinalState(previous);
    newStart = Concat(newStart, previous, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}