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
    int flag;
    unsigned short info;
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
State *AddState(StateMachine *stateMachine);
void AddTransition(StateMachine *stateMachine, State *source, State *dest, char symbol);
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
void SelectNextStates(StateMachine *nfa,
                   CircularLinearLinkedListNode **currentStates, 
                   CircularLinearLinkedListNode **nextStates,
                   char symbol);
void MakeSymbolTransitions(CircularLinearLinkedListNode *currentStates,
                           CircularLinearLinkedListNode *startPtr,
                           CircularLinearLinkedListNode **nextStates,
                           char symbol);
void EmptyStateMachine(StateMachine *stateMachine);