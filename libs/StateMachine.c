// StateMachine.c

#ifndef _STATE_MACHINE_H
    #include "StateMachine.h"
#endif

void InitStateMachine(StateMachine *stateMachine)
{
    InitCircularLinearLinkedList(&stateMachine->statesManager);
}

State *AddState(StateMachine *stateMachine)
{
    State *newState = malloc(sizeof(State));

    InitCircularLinearLinkedList(&newState->transitionsManager);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertEndCircularLinearLinkedList(&stateMachine->statesManager);

    newState->info = ZERO;
    newState->visited = FALSE;
    
    stateMachine->statesManager->info = newState;

    return (newState);
}

void AddTransition(StateMachine *stateMachine, State *source, State *dest, char symbol)
{
    Transition *transition = malloc(sizeof(Transition));

    !source->transitionsManager ? 
        InsertLastCircularLinearLinkedList(&source->transitionsManager) :
        InsertEndCircularLinearLinkedList(&source->transitionsManager);

    transition->dest = dest;
    transition->symbol = symbol;
    source->transitionsManager->info = transition;
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
        ((State*)states->info)->visited = visited;
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

State* PushState(StateMachine *stateMachine)
{
    State *newState = malloc(sizeof(State));

    InitCircularLinearLinkedList(&newState->transitionsManager);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertAfterCircularLinearLinkedList(stateMachine->statesManager);

    newState->info = ZERO;
    newState->visited = FALSE;
    
    stateMachine->statesManager->nextNode->info = newState;

    return (newState);
}

StateMachine *Union(StateMachine *first, StateMachine *second)
{
    State *firstStart = InitialState(first);
    State *firstEnd = FinalState(first);

    State *secondStart = InitialState(second);
    State *secondEnd = FinalState(second);

    State *temp = PushState(first);

    first = Concat(first, second, FALSE);
    AddTransition(first, temp, firstStart, EPSILON_TRANSITION);
    AddTransition(first, temp, secondStart, EPSILON_TRANSITION);
    
    temp = AddState(first);
    AddTransition(first, firstEnd, temp, EPSILON_TRANSITION);
    AddTransition(first, secondEnd, temp, EPSILON_TRANSITION);

    return (first);
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

    AddTransition(stateMachine, InitialState(stateMachine), FinalState(stateMachine), EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *Alternate(StateMachine *stateMachine)
{
    AddTransition(stateMachine, InitialState(stateMachine), FinalState(stateMachine), EPSILON_TRANSITION);

    return (stateMachine);
}

void InsertState(CircularLinearLinkedListNode **states, State *state)
{
    *states ? 
        InsertEndCircularLinearLinkedList(states) : 
        InsertLastCircularLinearLinkedList(states);

    state->visited = TRUE;
    (*states)->info = state;
}

void SelectNextTransitions(CircularLinearLinkedListNode *transitions,
                           CircularLinearLinkedListNode **nextStates,
                           char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *ptr = transitions->nextNode;

    do
    {
        currentTransition = ptr->info;

        !currentTransition->dest->visited && currentTransition->symbol == symbol ?
            InsertState(nextStates, currentTransition->dest) : 
            ZERO;

        ptr = ptr->nextNode;
    } 
    while (ptr != transitions->nextNode);
}

void SelectSymbolTransitions(CircularLinearLinkedListNode *currentStates,
                           CircularLinearLinkedListNode *startPtr,
                           CircularLinearLinkedListNode **nextStates,
                           char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *currentStatesPtr = startPtr;
    CircularLinearLinkedListNode *transitions;

    do
    {
        transitions = ((State *)currentStatesPtr->info)->transitionsManager;

        transitions ? 
            SelectNextTransitions(transitions, nextStates, symbol) :
            ZERO;

        currentStatesPtr = currentStatesPtr->nextNode;
    } 
    while (currentStatesPtr != currentStates->nextNode);
}

void SelectAllTransitions(CircularLinearLinkedListNode *currentStates,
                        CircularLinearLinkedListNode **nextStates,
                        char symbol)
{
    SelectSymbolTransitions(currentStates, currentStates->nextNode, nextStates, symbol);
    !*nextStates ? SelectSymbolTransitions(currentStates, currentStates->nextNode, nextStates, ANY_SYMBOL) : ZERO;
}

void EpsilonClosure(CircularLinearLinkedListNode **states)
{
    CircularLinearLinkedListNode *epsilonStates;
    CircularLinearLinkedListNode *previousEpsilonStates;

    InitCircularLinearLinkedList(&epsilonStates);
    SelectSymbolTransitions(*states, (*states)->nextNode, &epsilonStates, EPSILON_TRANSITION);

    while (epsilonStates)
    {
        previousEpsilonStates = epsilonStates->nextNode;
        ConcatCircularLinearLinkedLists(states, epsilonStates);
        epsilonStates = NULL;
        SelectSymbolTransitions(*states, previousEpsilonStates, &epsilonStates, EPSILON_TRANSITION);
    }
}

BOOL Exists(CircularLinearLinkedListNode *l, void *v)
{
    if (!l) return FALSE;

    CircularLinearLinkedListNode *p = l;
    do
    {
        if (p->info == v) return TRUE;

        p = p->nextNode;
    }
    while (p != l);

    return FALSE;
}

void f(StateMachine *nfa,
                   CircularLinearLinkedListNode **currentStates, 
                   CircularLinearLinkedListNode **nextStates,
                   char symbol)
{
        CircularLinearLinkedListNode *ppp = *nextStates;

    do
    {
        !*currentStates ? 
            InsertLastCircularLinearLinkedList(currentStates) : 
            InsertEndCircularLinearLinkedList(currentStates);

        (*currentStates)->info = ppp->info;

        ppp = ppp->nextNode;
    }
    while (ppp != *nextStates);

    CircularLinearLinkedListNode *s = (*currentStates)->nextNode;
    CircularLinearLinkedListNode *e = s;

    do
    {
        CircularLinearLinkedListNode *p = ((State*)s->info)->ec;

        if (p) do
        {
            InsertEndCircularLinearLinkedList(nextStates);
            (*nextStates)->info = p->info;

            p = p->nextNode;
        }
        while (p != ((State*)s->info)->ec);
        
        s = s->nextNode;
    }
    while (s != e);

    EpsilonClosure(currentStates);

    ppp = *currentStates;

    do
    {
        int a = Exists(*nextStates, ppp->info); 

        if (!a)
        {
            puts("moshe");
            SWAP(*nextStates, *currentStates, CircularLinearLinkedListNode*);
            break;
        }

        ppp = ppp->nextNode;
    }
    while (ppp != *currentStates);

    EmptyCircularLinearLinkedList(currentStates, NULL);
}

void SelectNextStates(StateMachine *nfa,
                   CircularLinearLinkedListNode **currentStates, 
                   CircularLinearLinkedListNode **nextStates,
                   char symbol)
{
    EmptyCircularLinearLinkedList(currentStates, NULL);
    EpsilonClosure(nextStates);
    
    SWAP(*nextStates, *currentStates, CircularLinearLinkedListNode*);

    // SetAllVisited(nfa, FALSE);

    CircularLinearLinkedListNode *states = *currentStates;

    do
    {
        ((State*)states->info)->visited = FALSE;
        states = states->nextNode;
    } 
    while (states != *currentStates);

    SelectAllTransitions(*currentStates, nextStates, symbol);
}

void EmptyState(State *state)
{
    state->transitionsManager ? EmptyCircularLinearLinkedList(&state->transitionsManager, free) : ZERO;
    free(state);
}

void EmptyStateMachine(StateMachine *stateMachine)
{
    EmptyCircularLinearLinkedList(&stateMachine->statesManager, EmptyState);
    free(stateMachine);
}