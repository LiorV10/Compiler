#include <stdlib.h>
#include "CommonMacros.h"
#include "Graph.h"
#include "Stack.h"

#define EPSILON_TRANSITION '\0'

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
        printf("[%d:%c]->", ((Edge*)ptr->info)->dest->info, ((Edge*)ptr->info)->weight);
        ptr = ptr->nextNode;
    }
    while (ptr != lst->nextNode);

    puts("");
}

void PrintGraph(Graph *graph)
{
    CircularLinearLinkedListNode* ptr = graph->verticesManager->nextNode;

    do
    {
        printf("%d:", ((Vertex*)ptr->info)->info);
        PrintList(((Vertex*)ptr->info)->edgesManager);
        ptr = ptr->nextNode;
    }
    while (ptr != graph->verticesManager->nextNode);

    puts("");
}

typedef Vertex State;
typedef Graph StateMachine;

void InitStateMachine(StateMachine *stateMachine)
{
    InitGraph(stateMachine, NULL);
}

State* AddState(StateMachine *stateMachine, BOOL isAccepting)
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

StateMachine* fromSymbol(char symbol)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitGraph(stateMachine, NULL);

    State *start = AddState(stateMachine, FALSE);
    State *end = AddState(stateMachine, TRUE);

    AddTransition(stateMachine, start, end, symbol);

    return (stateMachine);
}

StateMachine* concat(StateMachine *first, StateMachine *second)
{
    CircularLinearLinkedListNode *firstStart = first->verticesManager->nextNode;
    State *firstEnd = first->verticesManager->info;
    State *secondStart = second->verticesManager->nextNode->info;

    first->verticesManager->nextNode = second->verticesManager->nextNode;
    second->verticesManager->nextNode = firstStart;
    first = second;

    AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION);
    firstEnd->info = FALSE;

    return (first);
}

StateMachine* closure(StateMachine *previous)
{
    StateMachine *newStart = malloc(sizeof(StateMachine));
    InitGraph(newStart, NULL);

    State *start = AddState(newStart, FALSE);
    State *end = previous->verticesManager->info;

    end->info = FALSE;
    AddTransition(previous, end, AddState(previous, TRUE), EPSILON_TRANSITION);
    end = previous->verticesManager->info;
    AddTransition(previous, end, previous->verticesManager->nextNode->info, EPSILON_TRANSITION);
    newStart = concat(newStart, previous);

    AddTransition(newStart, start, end, EPSILON_TRANSITION);

    return (newStart);
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
                PushStack(&stack, closure(PopStack(&stack)));
                break;
            case '.':
                PushStack(&stack, concat(PopStack(&stack), PopStack(&stack)));
                break;
            default:
                PushStack(&stack, fromSymbol(*pattern));
                break;
        } 
    }

    return PopStack(&stack);
}

BOOL match(State *nfa, char *text) 
{
    if (!*(text)) 
    {
        return IsAccepting(nfa);
    }

    if (!nfa || !nfa->edgesManager) return FALSE;

    CircularLinearLinkedListNode *t = nfa->edgesManager;

    do
    {
        if (((Edge*)t->info)->weight == *text || ((Edge*)t->info)->weight == EPSILON_TRANSITION) 
        {
            if (match(((Edge*)t->info)->dest, text + (((Edge*)t->info)->weight == *text)))
            {
                return TRUE;
            }
        }

        t = t->nextNode;
    }
    while (t != nfa->edgesManager);

    return FALSE;
}

BOOL Match(StateMachine *nfa, char *input)
{
    
}

int main()
{
    char *pattern = "ab*.c.";
    char *strings[] = {"ac", "abc", "abcd", "abbbc", "a", "abbabbbc"};
    int strings_count = sizeof(strings) / sizeof(strings[0]);

    StateMachine *nfa = RegexToNFA(pattern);

    State *start = nfa->verticesManager->nextNode->info;
    
    PrintGraph(nfa);

    puts("\n");

    for (int i = 0; i < strings_count; i++)
    {
        if (match(start, strings[i]))
        {
            printf("%s\t\tmatches %s\n", strings[i], pattern);
        }
        else
        {
            printf("%s\t\tdoes not match %s\n", strings[i], pattern);
        }
    }

    return 0;
}