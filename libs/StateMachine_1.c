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
        printf("%p:", ((Vertex *)ptr)->info);
        PrintList(((Vertex *)ptr->info)->edgesManager);
        ptr = ptr->nextNode;
    } while (ptr != graph->verticesManager->nextNode);

    puts("");
}

typedef Vertex State;
typedef Edge Transition;
typedef Graph StateMachine;

void InitStateMachine(StateMachine *stateMachine)
{
    InitGraph(stateMachine, NULL);
}

State *AddState(StateMachine *stateMachine, BOOL isAccepting)
{
    return (AddVertex(stateMachine, isAccepting));
}

void AddTransition(StateMachine *stateMachine, State *source, State *target, void *symbol)
{
    JoinWeight(stateMachine, source, target, symbol);
}

void MakeAccepting(State *state)
{
    state->info = TRUE;
}

BOOL IsAccepting(State *state)
{
    return (state->info == TRUE);
}

StateMachine *fromSymbol(char symbol)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitGraph(stateMachine, NULL);

    State *start = AddState(stateMachine, FALSE);
    State *end = AddState(stateMachine, TRUE);

    AddTransition(stateMachine, start, end, symbol);

    return (stateMachine);
}

StateMachine *concat(StateMachine *first, StateMachine *second, BOOL applyTransition)
{
    CircularLinearLinkedListNode *firstStart = first->verticesManager->nextNode;
    State *firstEnd = first->verticesManager->info;
    State *secondStart = second->verticesManager->nextNode->info;

    first->verticesManager->nextNode = second->verticesManager->nextNode;
    second->verticesManager->nextNode = firstStart;
    first = second;
    firstEnd->info = FALSE;

    applyTransition ? AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION) : ZERO;

    return (first);
}

StateMachine *union_(StateMachine *first, StateMachine *second)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitGraph(stateMachine, NULL);

    State *start = AddState(stateMachine, FALSE);
    State *secondStart = second->verticesManager->nextNode->info;
    State *secondEnd = second->verticesManager->info;
    State *end;

    stateMachine = concat(stateMachine, first, TRUE);
    stateMachine = concat(stateMachine, second, FALSE);
    AddTransition(stateMachine, start, secondStart, EPSILON_TRANSITION);

    end = AddState(stateMachine, TRUE);
    AddTransition(stateMachine, first->verticesManager->info, end, EPSILON_TRANSITION);
    AddTransition(stateMachine, secondEnd, end, EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *closure(StateMachine *previous)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitGraph(newStart, NULL);

    State *start = AddState(newStart, FALSE);
    State *end = previous->verticesManager->info;

    end->info = FALSE;
    AddTransition(previous, end, AddState(previous, TRUE), EPSILON_TRANSITION);
    end = previous->verticesManager->info;
    AddTransition(previous, end, previous->verticesManager->nextNode->info, EPSILON_TRANSITION);
    newStart = concat(newStart, previous, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}

StateMachine *alternate(StateMachine *previous)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitGraph(newStart, NULL);

    State *start = AddState(newStart, FALSE);
    State *end = previous->verticesManager->info;

    end->info = FALSE;
    AddTransition(previous, end, AddState(previous, TRUE), EPSILON_TRANSITION);
    end = previous->verticesManager->info;
    newStart = concat(newStart, previous, TRUE);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
}

StateMachine *OneOrMore(StateMachine *previous)
{
    State *start = previous->verticesManager->nextNode->info;
    State *end = previous->verticesManager->info;
    State *newEnd = AddState(previous, TRUE);

    AddTransition(previous, end, newEnd, EPSILON_TRANSITION);
    AddTransition(previous, newEnd, start, EPSILON_TRANSITION);

    return (previous);
}

StateMachine* RegexToNFA(char *pattern)
{
    Stack stack;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case '*':
                PushStack(&stack, closure(PopStack(&stack)));
                break;
            case '?':
                PushStack(&stack, alternate(PopStack(&stack)));
                break;
            case '|':
                PushStack(&stack, union_(PopStack(&stack), PopStack(&stack)));
                break;
            case '+':
                PushStack(&stack, OneOrMore(PopStack(&stack)));
                break;
            case '.':
                PushStack(&stack, concat(PopStack(&stack), PopStack(&stack), TRUE));
                break;
            default:
                PushStack(&stack, fromSymbol(*pattern));
                break;
        }
    }

    return PopStack(&stack);
}

BOOL IsExists(LinearLinkedListNode *lst, State *st)
{
    LinearLinkedListNode *ptr = lst;
    BOOL isExists;

    while (ptr && !isExists)
    {
        isExists = ptr->info == st;
        ptr = ptr->nextNode;
    }

    return (isExists);
}

static int iter = 0;

void AddNextState(State *start, Stack *nextStates)
{
    LinearLinkedListNode *visited;
    CircularLinearLinkedListNode *transitions;
    Stack states;
    State *currentNext;
    State *current = start;

    InitStack(&states);
    InitCircularLinearLinkedList(&visited);
    PushStack(&states, current);

    while (!IsEmptyStack(&states))
    {
        current = PopStack(&states);

        if (!current->edgesManager)
        {
            PushStack(nextStates, current);
            continue;
        }

        transitions = current->edgesManager->nextNode;

        do
        {
            //((Transition*)transitions->info)->dest;
            currentNext = ((Transition*)transitions->info)->dest;

            if (((Transition*)transitions->info)->weight == EPSILON_TRANSITION &&
                !IsExists(visited, currentNext))
            {
                PushLinearLinkedList(&visited);
                visited->info = currentNext;
                PushStack(&states, currentNext);
            }
            else
            {
                PushStack(nextStates, current);
            }

            transitions = transitions->nextNode;
        }
        while (transitions != current->edgesManager->nextNode);
    }
}

BOOL Match(StateMachine *nfa, char *input)
{
    Stack currentStates;
    State *nextState = NULL;
    BOOL match = FALSE;

    InitStack(&currentStates);
    AddNextState(nfa->verticesManager->nextNode->info, &currentStates);

    for (; *input; input++)
    {
        Stack nextStates;
        InitStack(&nextStates);

        while (!IsEmptyStack(&currentStates))
        {
            State *current = PopStack(&currentStates);

            CircularLinearLinkedListNode *transitions = current->edgesManager->nextNode;

            do
            {
                nextState = ((Transition*)transitions->info)->weight == *input ? 
                    ((Transition*)transitions->info)->dest : nextState;

                nextState ? match |= nextState->info == TRUE : ZERO;
                printf("%p\n", nextState);
                transitions = transitions->nextNode;
            }
            while (transitions != current->edgesManager->nextNode);

            nextState ? AddNextState(nextState, &nextStates) : ZERO;
        }

        currentStates = nextStates;
    }

    while (!IsEmptyStack(&currentStates))
    {
        State *t = PopStack(&currentStates);
        printf("%p\n", t);
        match |= ((State*)t)->info == TRUE;
    }

    puts("");

    return (match);
}

BOOL Match_(StateMachine *nfa, char *input)
{
    State *currentVertex;
    Edge *currentAdjacent;
    CircularLinearLinkedListNode *adjacents;
    Queue nextLevel;
    CircularLinearLinkedListNode *visited;
    BOOL isMatch = FALSE;

    InitCircularLinearLinkedList(&visited);
    InitQueue(&nextLevel);
    InsertQueue(&nextLevel, (currentVertex = nfa->verticesManager->nextNode->info));
    InsertQueue(&nextLevel, NULL);
    InsertLastCircularLinearLinkedList(&visited);
    visited->info = currentVertex;

    while (!IsEmptyQueue(&nextLevel) && !(isMatch = currentVertex->info == TRUE))
    {
        currentVertex = RemoveQueue(&nextLevel);

        if (!currentVertex)
        {
            input += currentAdjacent->weight != EPSILON_TRANSITION;
            if (IsEmptyQueue(&nextLevel))
                continue;

            currentVertex = RemoveQueue(&nextLevel);
            InsertQueue(&nextLevel, NULL);
        }

        if (!currentVertex->edgesManager)
            continue;

        adjacents = currentVertex->edgesManager->nextNode;

        do
        {
            currentAdjacent = adjacents->info;
            if ((currentAdjacent->weight == *input) || currentAdjacent->weight == EPSILON_TRANSITION)
            {
                //input += currentAdjacent->weight == *input;
                InsertQueue(&nextLevel, currentAdjacent->dest);
            }
            iter++;
            adjacents = adjacents->nextNode;
        }
        while (adjacents != currentVertex->edgesManager->nextNode);
    }

    return (isMatch);
}

void main(void)
{
    //"ab.a.b.ab.b.b.|"
    char *pattern = "ab*.";//"a?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.";//"ab*.c.";
    char *strings[] = {"abab", "abbb", "cbbb", "ab"};//{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};//{"dac", "abc", "abcd", "abbbc", "a", "abbabbbc", "abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbc"};
    int strings_count = sizeof(strings) / sizeof(strings[0]);

    struct timeval stop, start;

    StateMachine *nfa = RegexToNFA(pattern);
    PrintGraph(nfa);

    gettimeofday(&start, NULL);
    puts("\n");

    for (int i = 0; i < strings_count; i++)
    {
        if (Match_(nfa, strings[i]))
        {
            printf("%s\t\tmatches %s\n", strings[i], pattern);
        }
        else
        {
            printf("%s\t\tdoes not match %s\n", strings[i], pattern);
        }
        printf("%d\n\n", iter);
        iter = 0;
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    printf("took %lu s\n", stop.tv_sec - start.tv_sec); 
}