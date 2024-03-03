// Regex.c

#include "Regex.h"

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
    State *secondStart = InitialState(second);//second->verticesManager->nextNode->info;
    State *secondEnd = FinalState(second);//second->verticesManager->info;
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
    State *start = InitialState(previous);//previous->verticesManager->nextNode->info;
    State *end = FinalState(previous);//previous->verticesManager->info;

    AddTransition(previous, end, start, EPSILON_TRANSITION);

    return (previous);
}
StateMachine *Start(StateMachine *previous)
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
    State *end = FinalState(previous);//previous->verticesManager->info;

    AddTransition(previous, end, AddState(previous), EPSILON_TRANSITION);
    end = FinalState(previous);
    newStart = Concat(newStart, previous, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}
StateMachine *RegexToNFARec(char *pattern)
{
    Stack stack;
    StateMachine *nfa;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case '\003':
                PushStack(&stack, RegexToNFARec(ASCII_LETTERS_PATTERN));
                break;
            case '\004':
                PushStack(&stack, RegexToNFARec(DIGIT_PATTERN));
                break;
            case '*':
                PushStack(&stack, Start(PopStack(&stack)));
                break;
            case '?':
                PushStack(&stack, Alternate(PopStack(&stack)));
                break;
            case '|':
                PushStack(&stack, Union(PopStack(&stack), PopStack(&stack)));
                break;
            case '+':
                PushStack(&stack, OneOrMore(PopStack(&stack)));
                break;
            case CONCAT_CHAR:
                PushStack(&stack, Concat(PopStack(&stack), PopStack(&stack), TRUE));
                break;
            default:
                PushStack(&stack, FromSymbol(*pattern));
                break;
        }
    }

    return (PopStack(&stack));
}
StateMachine* RegexToNFA(char *pattern)
{
    StateMachine *nfa = RegexToNFARec(pattern);
    SetAccepting(FinalState(nfa));

    return (nfa);
}

BOOL SelectNextTransitions(CircularLinearLinkedListNode *transitions,
                           CircularLinearLinkedListNode **nextStates,
                           BOOL (*Condition)(Transition *, char),
                           char symbol)
{
    Transition *currentTransition;
    BOOL foundAcceptingState = FALSE;
    CircularLinearLinkedListNode *ptr = transitions->nextNode;

    do
    {
        currentTransition = ptr->info;

        if (!currentTransition->dest->visited && Condition(currentTransition, symbol))
        {
            *nextStates ? 
                InsertEndCircularLinearLinkedList(nextStates) : 
                InsertLastCircularLinearLinkedList(nextStates);

            (*nextStates)->info = currentTransition->dest;
            foundAcceptingState |= currentTransition->dest->isAccepting;
            currentTransition->dest->visited = TRUE;
        }

        ptr = ptr->nextNode;
    } 
    while (ptr != transitions->nextNode);

    return (foundAcceptingState);
}

BOOL IsSymbolTransition(Transition *transition, char symbol)
{
    return (transition->symbol == symbol);
}

BOOL IsPossibleTransition(Transition *transition, char symbol)
{
    return (IsSymbolTransition(transition, symbol) || 
            ((IsSymbolTransition(transition, ANY_SYMBOL))));
}

void MakeTransitions(CircularLinearLinkedListNode *currentStates,
                     CircularLinearLinkedListNode **nextStates,
                     char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *currentStatesPtr = currentStates->nextNode;
    CircularLinearLinkedListNode *transitions;

    do
    {
        transitions = ((State *)currentStatesPtr->info)->transitionsManager;

        transitions ? 
            SelectNextTransitions(transitions, nextStates, IsPossibleTransition, symbol) :
            FALSE;

        currentStatesPtr = currentStatesPtr->nextNode;
    }
    while (currentStatesPtr != currentStates->nextNode);
}

BOOL EpsilonClosure(CircularLinearLinkedListNode **states)
{
    CircularLinearLinkedListNode *statesPtr = (*states)->nextNode;
    CircularLinearLinkedListNode *epsilonStates;

    InitCircularLinearLinkedList(&epsilonStates);

    do
    {
        epsilonStates = NULL;
        MakeTransitions(statesPtr, &epsilonStates, EPSILON_TRANSITION);
        epsilonStates ? ConcatCircularLinearLinkedLists(states, epsilonStates) : ZERO;
    }
    while (epsilonStates);
}

BOOL CompareLists(CircularLinearLinkedListNode *first,
                  CircularLinearLinkedListNode *second)
{
    CircularLinearLinkedListNode *p1 = first->nextNode;
    CircularLinearLinkedListNode *p2 = second->nextNode;

    while (p1 != first && p2 != second && p1->info == p2->info)
    {
        p1 = p1->nextNode;
        p2 = p2->nextNode;
    }

    return (p1 == first && p2 == second && p1->info == p2->info);
}

State *FindAcceptingState(CircularLinearLinkedListNode *currentStates)
{
    BOOL isMatch = FALSE;
    State *s = NULL;
    CircularLinearLinkedListNode *c;
    for (c = currentStates->nextNode; c != currentStates; c = c->nextNode)
    {
        ((State *)c->info)->isAccepting ? s = c->info : ZERO;
    }

    ((State *)c->info)->isAccepting ? s = c->info : ZERO;

    return s;
}

BOOL IsTerminated(CircularLinearLinkedListNode *currentStates)
{
    State *accepting = FindAcceptingState(currentStates);

    return (accepting ? !accepting->transitionsManager : FALSE);
}

CircularLinearLinkedListNode *InitStatesList(State *state, char symbol)
{
    CircularLinearLinkedListNode *states;

    InitCircularLinearLinkedList(&states);
    InsertLastCircularLinearLinkedList(&states);
    states->info = state;
    EpsilonClosure(&states);

    return (states);
}

MatchType* Match(StateMachine *nfa, char *input)
{
    CircularLinearLinkedListNode *currentStates;
    CircularLinearLinkedListNode *nextStates;
    MatchType *result = NULL;
    char *ptr = input;

    nextStates = currentStates = InitStatesList(InitialState(nfa), *input);
    MakeTransitions(currentStates, &nextStates, *input);
    nextStates = CompareLists(currentStates, nextStates) ? NULL : nextStates;
    
    while (*input && nextStates && !IsTerminated(currentStates))
    {
        EpsilonClosure(&nextStates);

        currentStates = nextStates;
        nextStates = NULL;

        SetAllVisited(nfa, FALSE);
        MakeTransitions(currentStates, &nextStates, *++input);
    }

    if (!!FindAcceptingState(currentStates))
    {
        result = malloc(sizeof(MatchType));
        *result = (MatchType){.start = ptr, .end = input};
    }
    
    SetAllVisited(nfa, FALSE);
    EmptyCircularLinearLinkedList(&currentStates);

    return (result);
}