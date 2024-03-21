// StateMachine.h

#define _STATE_MACHINE_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

#define NON_ACCEPTING ((void*)-ONE)
#define EPSILON_TRANSITION '\000'
#define ANY_SYMBOL '\001'

typedef struct
{
    BOOL visited;
    void *info;
    CircularLinearLinkedListNode *transitionsManager;
} State;

typedef struct
{
    char symbol;
    State *dest;
} Transition;

typedef struct
{
    CircularLinearLinkedListNode *statesManager;
} StateMachine;

void InitStateMachine(StateMachine *stateMachine);
State *AddState(StateMachine *statemachine);
void AddTransition(StateMachine *statemachine, State *source, State *dest, char symbol);
void SetVisited(State *state, BOOL isVisited);
BOOL IsVisited(State *state);
State *FinalState(StateMachine *stateMachine);
State *InitialState(StateMachine *stateMachine);
void SetAllVisited(StateMachine *stateMachine, BOOL visited);
void ConcatStateMachines(StateMachine *first, StateMachine *second);
StateMachine *FromSymbol(char symbol);
StateMachine *Concat(StateMachine *first, StateMachine *second, BOOL applyTransition);
StateMachine *Union(StateMachine *first, StateMachine *second);
StateMachine *OneOrMore(StateMachine *previous);
StateMachine *Star(StateMachine *previous);
StateMachine *Alternate(StateMachine *previous);
void EmptyStateMachine(StateMachine *stateMachine);