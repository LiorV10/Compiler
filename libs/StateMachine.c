#include "CommonMacros.h"
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include <sys/time.h>

#define EPSILON_TRANSITION (char)1

void PrintList(CircularLinearLinkedListNode *lst)
{
    if (!lst)
    {
        puts("");
        return;
    };

    CircularLinearLinkedListNode *ptr = lst->nextNode;

    do
    {
        printf("[%p:%c]->", ((Edge *)ptr->info)->dest, ((Edge *)ptr->info)->weight);
        ptr = ptr->nextNode;
    } while (ptr != lst->nextNode);

    puts("");
}

void PrintGraph(Graph *graph)
{
    CircularLinearLinkedListNode *ptr = graph->verticesManager->nextNode;

    do
    {
        printf("[%d][%p]:", ((Vertex *)ptr->info)->isAccepting, ((Vertex *)ptr->info));
        PrintList(((Vertex *)ptr->info)->edgesManager);
        ptr = ptr->nextNode;
    } while (ptr != graph->verticesManager->nextNode);

    puts("");
}

typedef Vertex State;
typedef Edge Transition;
typedef Graph StateMachine;

BOOL EpsilonClosure(CircularLinearLinkedListNode **states);

void InitStateMachine(StateMachine *stateMachine)
{
    InitGraph(stateMachine);
}

State *AddState(StateMachine *stateMachine, BOOL isAccepting)
{
    return (AddVertex(stateMachine, NULL, isAccepting));
}

void AddTransition(StateMachine *stateMachine, State *source, State *target, void *symbol)
{
    JoinWeight(stateMachine, source, target, symbol);
}

void MakeAccepting(State *state)
{
    state->isAccepting = TRUE;
}

BOOL IsAccepting(State *state)
{
    return (state->isAccepting == TRUE);
}

void SetAllVisited(StateMachine *stateMachine, BOOL visited)
{
    CircularLinearLinkedListNode *states = stateMachine->verticesManager;

    do
    {
        ((State *)states->info)->visited = visited;
        states = states->nextNode;
    } while (states != stateMachine->verticesManager);
}

StateMachine *StateMachineFromSymbol(char symbol)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine, FALSE);
    State *end = AddState(stateMachine, TRUE);

    AddTransition(stateMachine, start, end, symbol);

    return (stateMachine);
}

StateMachine *StateMachineConcat(StateMachine *first, StateMachine *second, BOOL applyTransition)
{
    CircularLinearLinkedListNode *firstStart = first->verticesManager->nextNode;
    State *firstEnd = first->verticesManager->info;
    State *secondStart = second->verticesManager->nextNode->info;

    first->verticesManager->nextNode = second->verticesManager->nextNode;
    second->verticesManager->nextNode = firstStart;
    first = second;
    firstEnd->isAccepting = FALSE;

    applyTransition ? AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION) : ZERO;

    return (first);
}

StateMachine *StateMachineUnion(StateMachine *first, StateMachine *second)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine, FALSE);
    State *secondStart = second->verticesManager->nextNode->info;
    State *secondEnd = second->verticesManager->info;
    State *end;

    stateMachine = StateMachineConcat(stateMachine, first, TRUE);
    stateMachine = StateMachineConcat(stateMachine, second, FALSE);
    AddTransition(stateMachine, start, secondStart, EPSILON_TRANSITION);
    secondEnd->isAccepting = FALSE;
    end = AddState(stateMachine, TRUE);
    AddTransition(stateMachine, first->verticesManager->info, end, EPSILON_TRANSITION);
    AddTransition(stateMachine, secondEnd, end, EPSILON_TRANSITION);

    return (stateMachine);
}
StateMachine *OneOrMore(StateMachine *previous);
StateMachine *StateMachineClosure(StateMachine *previous)
{
    // StateMachine *newStart = malloc(sizeof(StateMachine));
    // InitStateMachine(newStart);

    // State *start = AddState(newStart, FALSE);
    // State *end = previous->verticesManager->info;

    // end->isAccepting = FALSE;
    // AddTransition(previous, end, AddState(previous, TRUE), EPSILON_TRANSITION);
    // end = previous->verticesManager->info;
    // AddTransition(previous, end, previous->verticesManager->nextNode->info, EPSILON_TRANSITION);
    // newStart = StateMachineConcat(newStart, previous, TRUE);

    // AddTransition(newStart, start, end, EPSILON_TRANSITION);
    previous = OneOrMore(previous);
    ((State*)previous->verticesManager->info)->isAccepting = FALSE;
    AddTransition(previous, previous->verticesManager->info,
                  previous->verticesManager->nextNode->info, EPSILON_TRANSITION);

    AddTransition(previous, previous->verticesManager->nextNode->info,
                  previous->verticesManager->info, EPSILON_TRANSITION);

    return (previous);
}

StateMachine *StateMachineAlternate(StateMachine *previous)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitStateMachine(newStart);

    State *start = AddState(newStart, FALSE);
    State *end = previous->verticesManager->info;

    end->isAccepting = FALSE;
    AddTransition(previous, end, AddState(previous, TRUE), EPSILON_TRANSITION);
    end = previous->verticesManager->info;
    newStart = StateMachineConcat(newStart, previous, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}

StateMachine *OneOrMore(StateMachine *previous)
{
    State *start = previous->verticesManager->nextNode->info;
    State *end = previous->verticesManager->info;

    AddTransition(previous, end, start, EPSILON_TRANSITION);

    return (previous);
}

StateMachine *RegexToNFA(char *pattern)
{
    Stack stack;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
        case '*':
            PushStack(&stack, StateMachineClosure(PopStack(&stack)));
            break;
        case '?':
            PushStack(&stack, StateMachineAlternate(PopStack(&stack)));
            break;
        case '|':
            PushStack(&stack, StateMachineUnion(PopStack(&stack), PopStack(&stack)));
            break;
        case '+':
            PushStack(&stack, OneOrMore(PopStack(&stack)));
            break;
        case '.':
            PushStack(&stack, StateMachineConcat(PopStack(&stack), PopStack(&stack), TRUE));
            break;
        default:
            PushStack(&stack, StateMachineFromSymbol(*pattern));
            break;
        }
    }

    return PopStack(&stack);
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
            *nextStates ? InsertEndCircularLinearLinkedList(nextStates) : InsertLastCircularLinearLinkedList(nextStates);

            (*nextStates)->info = currentTransition->dest;
            foundAcceptingState |= currentTransition->dest->isAccepting;
            currentTransition->dest->visited = TRUE;
        }

        ptr = ptr->nextNode;
    } while (ptr != transitions->nextNode);

    return (foundAcceptingState);
}

BOOL IsSymbolTransition(Transition *transition, char symbol)
{
    return (transition->weight == symbol);
}

BOOL IsPossibleTransition(Transition *transition, char symbol)
{
    return (IsSymbolTransition(transition, symbol));// ||
            //IsSymbolTransition(transition, EPSILON_TRANSITION));
}

void MakeTransitions(CircularLinearLinkedListNode *currentStates,
                     CircularLinearLinkedListNode **nextStates,
                     char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *currentStatesPtr = currentStates->nextNode;
    CircularLinearLinkedListNode *transitions;
    // BOOL hasAcceptingState = FALSE;

    do
    {
        transitions = ((State *)currentStatesPtr->info)->edgesManager;

        (transitions ? SelectNextTransitions(transitions, nextStates, IsPossibleTransition, symbol) : FALSE);

        currentStatesPtr = currentStatesPtr->nextNode;
    } while (currentStatesPtr != currentStates->nextNode);

    // return (hasAcceptingState);
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
        //epsilonStates ? *states = epsilonStates : ZERO;
    } while (epsilonStates);
}

BOOL CompareLists(CircularLinearLinkedListNode *first,
                  CircularLinearLinkedListNode *second)
{
    CircularLinearLinkedListNode *p1 = first;
    CircularLinearLinkedListNode *p2 = second;

    do
    {
        if (p1->info != p2->info)
            return FALSE;
        
        p1 = p1->nextNode;
        p2 = p2->nextNode;

    } while (p1 != first && p2 != second);

    return (p1 == first && p2 == second);
}

State* IsMatch(CircularLinearLinkedListNode *currentStates)
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

CircularLinearLinkedListNode *InitStatesList(State *state, char symbol)
{
    CircularLinearLinkedListNode *states;

    InitCircularLinearLinkedList(&states);
    InsertLastCircularLinearLinkedList(&states);
    states->info = state;
    EpsilonClosure(&states);

    return (states);
}

BOOL Match(StateMachine *stateMachine, char *input)
{
    CircularLinearLinkedListNode *currentStates;
    CircularLinearLinkedListNode *nextStates;
    CircularLinearLinkedListNode *temp;
    BOOL isMatch = FALSE;

    InitCircularLinearLinkedList(&nextStates);
    currentStates = InitStatesList(stateMachine->verticesManager->nextNode->info, *input);
    nextStates = currentStates;

    char *p = input;

    for (; *input; input++)
    {
        MakeTransitions(currentStates, &nextStates, *input);

        if (nextStates)
        {
            //SetAllVisited(stateMachine, FALSE);
            EpsilonClosure(&nextStates);
            SetAllVisited(stateMachine, FALSE);

            if (CompareLists(currentStates, nextStates))
               break;

            SWAP(currentStates, nextStates, CircularLinearLinkedListNode *);

            if (IsMatch(currentStates))
                if (IsMatch(currentStates)->edgesManager == NULL)
                {
                    input++;
                    break;
                }
        }
        else
        {
            break;
        }

        //SetAllVisited(stateMachine, FALSE);
        nextStates = NULL;
    }

    IsMatch(currentStates) ? puts(input) : FALSE;
    SetAllVisited(stateMachine, FALSE);

    return (!!IsMatch(currentStates));
}

BOOL Simulate(StateMachine *stateMachine, char *input)
{
    Stack states;
    CircularLinearLinkedListNode *transitions;
    State *current;
    BOOL consumeChar = FALSE;
    char *currentSymbol;
    CircularLinearLinkedListNode *temp;

    InitStack(&states);
    InitCircularLinearLinkedList(&temp);
    PushStack(&states, stateMachine->verticesManager->nextNode->info);
    PushStack(&states, input);

    while (!IsEmptyStack(&states))
    {
        currentSymbol = PopStack(&states);
        current = PopStack(&states);

        if (!*currentSymbol || !current->edgesManager)
        {
            InsertLastCircularLinearLinkedList(&temp);
            temp->info = current;
            SetAllVisited(stateMachine, FALSE);
            EpsilonClosure(&temp);
            if (IsAccepting(current) || IsMatch(temp))
            {
                return TRUE;
            }
        }

        transitions = current->edgesManager;

        do
        {
            if (((Transition *)transitions->info)->weight == *currentSymbol ||
                ((Transition *)transitions->info)->weight == EPSILON_TRANSITION)
            {
                // consumeChar |= ((Transition*)transitions->info)->weight == *input;
                PushStack(&states, ((Transition *)transitions->info)->dest);
                PushStack(&states, currentSymbol +
                    (((Transition *)transitions->info)->weight == *currentSymbol));
            }
            transitions = transitions->nextNode;
        } while (transitions != current->edgesManager);

        // input += consumeChar;
        // consumeChar = FALSE;
    }

    return FALSE;
}
  
void main(void)
{
    //"ab.a.b.ab.b.b.|"
    // 01|2|3|4|5|6|7|8|9|
    char *pattern1 = "01|2|*~.";                                          //"a?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.";
    char *strings1[] = 
    {
        "abbbbbbc", "abc", "ac", "aaaa", "101", "102", "1035", "311",
        "10101~", "~", "101", "2~", "2012~~"
    }; //{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    int strings_count1 = sizeof(strings1) / sizeof(strings1[0]);

    char *pattern2 = "a?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.";
    char *strings2[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    int strings_count2 = sizeof(strings2) / sizeof(strings1[0]);

    struct timeval stop, start;

    StateMachine *nfa1 = RegexToNFA(pattern1);
    StateMachine *nfa2 = RegexToNFA(pattern2);

    PrintGraph(nfa1);
    //PrintGraph(nfa2);

    // return;

    gettimeofday(&start, NULL);
    puts("\n");

    if (1)
    for (int i = 0; i < strings_count1; i++)
    {
        if (Match(nfa1, strings1[i]))
        {
            printf("%s\t\tmatches %s\n", strings1[i], pattern1);
        }
        else
        {
            printf("%s\t\tdoes not match %s\n", strings1[i], pattern1);
        }
    }

    puts("");

    if (1)
    for (int i = 0; i < strings_count2; i++)
    {
        if (Match(nfa2, strings2[i]))
        {
            printf("%s\t\tmatches %s\n", strings2[i], pattern2);
        }
        else
        {
            printf("%s\t\tdoes not match %s\n", strings2[i], pattern2);
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf("took %lu s\n", stop.tv_sec - start.tv_sec);
}