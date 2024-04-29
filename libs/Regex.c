// Regex.c

#ifndef _REGEX_H
    #include "Regex.h"
#endif

StateMachine *RegexToENFA(char *pattern)
{
    Stack stack;
    StateMachine *nfa;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case LTETTERS_CHAR:
                PushStack(&stack, RegexToENFA(LETTERS_PATTERN));
                break;
            case DIGIT_CHAR:
                PushStack(&stack, RegexToENFA(DIGIT_PATTERN));
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

CircularLinearLinkedListNode* EpsilonClosureByState(State* state)
{
    CircularLinearLinkedListNode *states;
    CircularLinearLinkedListNode *epsilonStates;
    CircularLinearLinkedListNode *previousEpsilonStates;

    InitCircularLinearLinkedList(&states);
    InitCircularLinearLinkedList(&epsilonStates);

    InsertLastCircularLinearLinkedList(&states);
    states->info = state;

    MakeSymbolTransitions(states, states->nextNode, &epsilonStates, EPSILON_TRANSITION);

    while (epsilonStates)
    {
        previousEpsilonStates = epsilonStates->nextNode;
        ConcatCircularLinearLinkedLists(&states, epsilonStates);
        epsilonStates = NULL;
        MakeSymbolTransitions(states, previousEpsilonStates, &epsilonStates, EPSILON_TRANSITION);
    }

    return states;
}

StateMachine *ENFAToNFA(StateMachine *enfa)
{
    StateMachine *nfa = malloc(sizeof(StateMachine));
    CircularLinearLinkedListNode *sp = enfa->statesManager->nextNode;

    int x = 0;
    InitStateMachine(nfa);

    do
    {
        ((State*)sp->info)->flag = x++;
        sp = sp->nextNode;
    }
    while (sp != enfa->statesManager->nextNode);

    State *arr[x];

    do
    {
        State *current = AddState(nfa);
        arr[((State*)sp->info)->flag] = current;
        current->flag = ((State*)sp->info)->flag;
        current->visited = FALSE; 
        sp = sp->nextNode;
    }
    while (sp != enfa->statesManager->nextNode);

    do
    {
        SetAllVisited(enfa, FALSE);
        CircularLinearLinkedListNode *closure = EpsilonClosureByState(sp->info);
        CircularLinearLinkedListNode *sc = closure->nextNode;

        do
        {
            if (!arr[((State*)sp->info)->flag]->info)
                arr[((State*)sp->info)->flag]->info = ((State*)sc->info)->info;

            CircularLinearLinkedListNode *transitions = ((State*)sc->info)->transitionsManager;

            if (transitions) do
            {
                if (((Transition*)transitions->info)->symbol != EPSILON_TRANSITION)
                {
                    AddTransition(nfa, arr[((State*)sp->info)->flag], 
                        arr[((Transition*)transitions->info)->dest->flag], 
                        ((Transition*)transitions->info)->symbol);
                }

                transitions = transitions->nextNode;
            }
            while (transitions != ((State*)sc->info)->transitionsManager);

            sc = sc->nextNode;
        }
        while (sc != closure->nextNode);

        EmptyCircularLinearLinkedList(&closure, NULL);

        sp = sp->nextNode;
    }
    while (sp != enfa->statesManager->nextNode);

    EmptyStateMachine(enfa);

    return (nfa);
}

StateMachine *RegexToNFA(char *pattern, unsigned short matchType)
{
    StateMachine *enfa = RegexToENFA(pattern);
    FinalState(enfa)->info = ++matchType;
    
    //enfa = ENFAToNFA(enfa);

    return (enfa);
}

State* FindAcceptingState(CircularLinearLinkedListNode *currentStates, char *s, char *e)
{
    CircularLinearLinkedListNode *ptr = currentStates;
    State *acceptingState = ptr->info;

    do
    {
        ((State*)ptr->info)->info > acceptingState->info ? acceptingState = ptr->info : ZERO;
        ptr = ptr->nextNode;
    } 
    while (ptr != currentStates);

    return (acceptingState->info ? acceptingState : NULL);
}

struct Match* MakeMatch(char *start, char *end, unsigned short matchType)
{
    char *ptr;
    struct Match *match = malloc(sizeof(struct Match));

    match->start = malloc(sizeof(char) * (end - start));
    ptr = match->start;

    for (; start != end;)
    {
        *ptr++ = *start++;
    }

    *ptr ^= *ptr;
    match->end = ptr;
    match->matchType = --matchType;
}

void InitStatesList(CircularLinearLinkedListNode **states, State *state)
{
    InitCircularLinearLinkedList(states);
    InsertLastCircularLinearLinkedList(states);
    (*states)->info = state;
}

struct Match* ExecuteRegex(StateMachine *nfa, char *input)
{
    CircularLinearLinkedListNode *currentStates;
    CircularLinearLinkedListNode *nextStates;
    State *acceptingState;
    struct Match *match;
    char *inputStart = input;

    InitCircularLinearLinkedList(&currentStates);
    InitStatesList(&nextStates, InitialState(nfa));

    SelectNextStates(nfa, &currentStates, &nextStates, *input);

    while (*input && nextStates)
    {
        SelectNextStates(nfa, &currentStates, &nextStates, *++input);
    }

    match = (acceptingState = FindAcceptingState(currentStates, inputStart, input)) ?
        MakeMatch(inputStart, input, acceptingState->info) :
        NULL;

    SetAllVisited(nfa, FALSE);

    EmptyCircularLinearLinkedList(&currentStates, NULL);
    nextStates ? EmptyCircularLinearLinkedList(&nextStates, NULL) : ZERO;

    return (match);
}