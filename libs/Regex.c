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

void SelectNextTransitions(CircularLinearLinkedListNode *transitions,
                           CircularLinearLinkedListNode **nextStates,
                           BOOL (*Condition)(Transition *, char),
                           char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *ptr = transitions->nextNode;

    do
    {
        currentTransition = ptr->info;

        !currentTransition->dest->visited && Condition(currentTransition, symbol) ?
            InsertState(nextStates, currentTransition->dest) : 
            ZERO;

        ptr = ptr->nextNode;
    } 
    while (ptr != transitions->nextNode);
}

BOOL IsSymbolTransition(Transition *transition, char symbol)
{
    return (transition->symbol == symbol);
}

BOOL IsPossibleTransition(Transition *transition, char symbol)
{
    return (IsSymbolTransition(transition, symbol) ||
            (IsSymbolTransition(transition, ANY_SYMBOL)));
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
            ZERO;

        currentStatesPtr = currentStatesPtr->nextNode;
    } while (currentStatesPtr != currentStates->nextNode);
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
    } while (epsilonStates);
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

BOOL IsTerminated(CircularLinearLinkedListNode *currentStates)
{
    State *accepting = FindAcceptingState(currentStates);

    return (accepting ? !accepting->transitionsManager : FALSE);
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

    *ptr = '\0';
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
    !IsTerminated(*currentStates) ? MakeTransitions(*currentStates, nextStates, symbol) : ZERO;
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