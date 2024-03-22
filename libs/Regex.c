// Regex.c

#ifndef _REGEX_H
    #include "Regex.h"
#endif

StateMachine *RegexToNFARec(char *pattern)
{
    Stack stack;
    StateMachine *nfa;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case LTETTERS_CHAR:
                PushStack(&stack, RegexToNFARec(LETTERS_PATTERN));
                break;
            case DIGIT_CHAR:
                PushStack(&stack, RegexToNFARec(DIGIT_PATTERN));
                break;
            case CONCAT_CHAR:
                PushStack(&stack, Concat(PopStack(&stack), PopStack(&stack), TRUE));
                break;
            case STAR_OPERATOR:
                PushStack(&stack, Star(PopStack(&stack)));
                break;
            case ALTERNATION_OPERATOR:
                PushStack(&stack, Alternate(PopStack(&stack)));
                break;
            case UNION_OPERATOR:
                PushStack(&stack, Union(PopStack(&stack), PopStack(&stack)));
                break;
            case PLUS_OPERATOR:
                PushStack(&stack, OneOrMore(PopStack(&stack)));
                break;
            default:
                PushStack(&stack, FromSymbol(*pattern));
                break;
        }
    }

    return (PopStack(&stack));
}

StateMachine *RegexToNFA(char *pattern)
{
    StateMachine *nfa = RegexToNFARec(pattern);
    SetAccepting(FinalState(nfa));

    return (nfa);
}

void InsertState(CircularLinearLinkedListNode **states, State *state)
{
    *states ? 
        InsertEndCircularLinearLinkedList(states) : 
        InsertLastCircularLinearLinkedList(states);

    (*states)->info = state;
    state->visited = TRUE;
}

BOOL IsPossibleTransition(Transition *transition, char symbol)
{
    return (transition->symbol == symbol || transition->symbol == ANY_SYMBOL);
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

        !currentTransition->dest->visited && currentTransition->symbol == symbol ?//IsPossibleTransition(currentTransition, symbol) ?
            InsertState(nextStates, currentTransition->dest) : 
            ZERO;

        ptr = ptr->nextNode;
    } 
    while (ptr != transitions->nextNode);
}

void MakeSymbolTransitions(CircularLinearLinkedListNode *currentStates,
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
            SelectNextTransitions(transitions, nextStates, symbol) :
            ZERO;

        currentStatesPtr = currentStatesPtr->nextNode;
    } 
    while (currentStatesPtr != currentStates->nextNode);
}

void MakeAllTransitions(CircularLinearLinkedListNode *currentStates,
                        CircularLinearLinkedListNode **nextStates,
                        char symbol)
{
    MakeSymbolTransitions(currentStates, nextStates, symbol);
    !*nextStates ? MakeSymbolTransitions(currentStates, nextStates, ANY_SYMBOL) : ZERO;
}

BOOL EpsilonClosure(CircularLinearLinkedListNode **states)
{
    CircularLinearLinkedListNode *epsilonStates;

    InitCircularLinearLinkedList(&epsilonStates);
    MakeAllTransitions(*states, &epsilonStates, EPSILON_TRANSITION);

    while (epsilonStates)
    {
        ConcatCircularLinearLinkedLists(states, epsilonStates);
        epsilonStates = NULL;
        MakeAllTransitions(*states, &epsilonStates, EPSILON_TRANSITION);
    } 
}

State *FindAcceptingState(CircularLinearLinkedListNode *currentStates)
{
    CircularLinearLinkedListNode *ptr = currentStates->nextNode;
    State *acceptingState = NULL;

    do
    {
        ((State *)ptr->info)->isAccepting ? acceptingState = ptr->info : ZERO;
        ptr = ptr->nextNode;
    } while (ptr != currentStates->nextNode);

    return (acceptingState);
}

Match* MakeMatch(char *start, char *end)
{
    char *ptr;
    Match *match = malloc(sizeof(Match));

    match->start = malloc(sizeof(char) * (end - start + ONE));
    ptr = match->start;

    for (; start != end;)
    {
        *ptr++ = *start++;
    }

    *ptr ^= *ptr;
    match->end = ptr;
}

void SetNextStates(StateMachine *nfa,
                   CircularLinearLinkedListNode **currentStates, 
                   CircularLinearLinkedListNode **nextStates,
                   char symbol)
{
    EmptyCircularLinearLinkedList(currentStates);
    SetAllVisited(nfa, FALSE);
    EpsilonClosure(nextStates);

    *currentStates = *nextStates;
    *nextStates = NULL;

    SetAllVisited(nfa, FALSE);
    MakeAllTransitions(*currentStates, nextStates, symbol);
}

void InitStatesList(CircularLinearLinkedListNode **states, State *state)
{
    InitCircularLinearLinkedList(states);
    InsertLastCircularLinearLinkedList(states);
    (*states)->info = state;
}

Match* ExecuteRegex(StateMachine *nfa, char *input)
{
    CircularLinearLinkedListNode *currentStates;
    CircularLinearLinkedListNode *nextStates;
    char *inputStart = input;
    Match *match;

    InitStatesList(&nextStates, InitialState(nfa));
    InitStatesList(&currentStates, InitialState(nfa));
    
    SetNextStates(nfa, &currentStates, &nextStates, *input);

    while (*input && nextStates)
    {
        SetNextStates(nfa, &currentStates, &nextStates, *++input);
    }

    match = FindAcceptingState(currentStates) ? MakeMatch(inputStart, input) : NULL;

    SetAllVisited(nfa, FALSE);
    EmptyCircularLinearLinkedList(&currentStates);
    nextStates ? EmptyCircularLinearLinkedList(&nextStates) : ZERO;

    return (match);
}

void FreeMatch(Match *match)
{
    free(match->start);
    free(match);
}