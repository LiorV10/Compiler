// StateMachine.c

#ifndef _STATE_MACHINE_H
    #include "StateMachine.h"
#endif

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

    newState->info = NON_ACCEPTING;
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

    free(second);

    return (first);
}

StateMachine *Union(StateMachine *first, StateMachine *second)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine);
    State *secondStart = InitialState(second);
    State *secondEnd = FinalState(second);
    State *firstEnd = FinalState(first);
    State *end;

    stateMachine = Concat(stateMachine, first, TRUE);
    stateMachine = Concat(stateMachine, second, FALSE);
    AddTransition(stateMachine, start, secondStart, EPSILON_TRANSITION);
    
    end = AddState(stateMachine);
    AddTransition(stateMachine, firstEnd, end, EPSILON_TRANSITION);
    AddTransition(stateMachine, secondEnd, end, EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *OneOrMore(StateMachine *stateMachine)
{
    State *start = InitialState(stateMachine);
    State *end = FinalState(stateMachine);

    AddTransition(stateMachine, end, start, EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *Star(StateMachine *stateMachine)
{
    stateMachine = OneOrMore(stateMachine);

    AddTransition(stateMachine, FinalState(stateMachine), InitialState(stateMachine), EPSILON_TRANSITION);
    AddTransition(stateMachine, InitialState(stateMachine), FinalState(stateMachine), EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *Alternate(StateMachine *stateMachine)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitStateMachine(newStart);

    State *start = AddState(newStart);
    State *end = FinalState(stateMachine);

    AddTransition(stateMachine, end, AddState(stateMachine), EPSILON_TRANSITION);
    end = FinalState(stateMachine);
    newStart = Concat(newStart, stateMachine, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}

void EmptyTransitions(CircularLinearLinkedListNode **transitions)
{
    CircularLinearLinkedListNode *ptr = *transitions;

    do
    {
        free(ptr->info);
        ptr = ptr->nextNode;
    }
    while (ptr != *transitions);

    EmptyCircularLinearLinkedList(transitions);
}

void EmptyState(State *state)
{
    state->transitionsManager ? EmptyTransitions(&state->transitionsManager) : ZERO;
    free(state);
}

void EmptyStateMachine(StateMachine *stateMachine)
{
    CircularLinearLinkedListNode *ptr = stateMachine->statesManager;

    do
    {
        EmptyState(ptr->info);
        ptr = ptr->nextNode;
    }   
    while (ptr != stateMachine->statesManager);

    EmptyCircularLinearLinkedList(&stateMachine->statesManager);
    free(stateMachine);
}