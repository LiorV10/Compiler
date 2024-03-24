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
    FinalState(nfa)->isAccepting = TRUE;

    return (nfa);
}

State* HasAcceptingState(CircularLinearLinkedListNode *currentStates)
{
    CircularLinearLinkedListNode *ptr = currentStates->nextNode;
    State *acceptingState = NULL;

    do
    {
        ((State*)ptr->info)->isAccepting ? acceptingState = ptr->info : ZERO;
        ptr = ptr->nextNode;
    } 
    while (ptr != currentStates->nextNode);

    return (acceptingState);
}

Match* MakeMatch(char *start, char *end)
{
    char *ptr;
    Match *match = malloc(sizeof(Match));

    match->start = malloc(sizeof(char) * (end - start));
    ptr = match->start;

    for (; start != end;)
    {
        *ptr++ = *start++;
    }

    *ptr ^= *ptr;
    match->end = ptr;
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

    InitCircularLinearLinkedList(&currentStates);
    InitStatesList(&nextStates, InitialState(nfa));

    SelectNextStates(nfa, &currentStates, &nextStates, *input);

    while (*input && nextStates)
    {
        SelectNextStates(nfa, &currentStates, &nextStates, *++input);
    }

    match = HasAcceptingState(currentStates) ? MakeMatch(inputStart, input) : NULL;

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