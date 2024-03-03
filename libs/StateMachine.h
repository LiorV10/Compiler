// StateMachine.h

#define _STATE_MACHINE_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "CircularLinearLinkedList.h"
#endif

#define EPSILON_TRANSITION '\000'
#define ANY_SYMBOL '\001'

typedef struct
{
    BOOL isAccepting;
    BOOL visited;
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
void SetAccepting(State *state);
BOOL IsAccepting(State *state);
void SetVisited(State *state, BOOL isVisited);
BOOL IsVisited(State *state);
State *FinalState(StateMachine *stateMachine);
State *InitialState(StateMachine *stateMachine);
void SetAllVisited(StateMachine *stateMachine, BOOL visited);
void ConcatStateMachines(StateMachine *first, StateMachine *second);