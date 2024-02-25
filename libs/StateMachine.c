#include <stdlib.h>
#include "CommonMacros.h"
#include "Graph.h"

#define EPSILON_TRANSITION '\0'

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

StateMachine *RegexToNFA(char *pattern) 
{
    StateMachine *nfa = malloc(sizeof(StateMachine));

    InitStateMachine(nfa);
    State *current = AddState(nfa, FALSE);

    for (; *pattern; pattern++)
    {
        State *s1 = AddState(nfa, FALSE);
        switch (*(pattern + ONE))
        {
            case '*':
                AddTransition(nfa, current, current, *pattern);
                AddTransition(nfa, s1, s1, *pattern);
                AddTransition(nfa, s1, s1, EPSILON_TRANSITION);
                pattern++;
                break;
            case '+':
                AddTransition(nfa, current, s1, *pattern);
                AddTransition(nfa, s1, s1, *pattern);
                current = s1;
                break;
            default:
                AddTransition(nfa, current, s1, *pattern);
                current = s1;
                break;
        }
    }

    MakeAccepting(current);
    return nfa;
}

BOOL match(State *nfa, char *text) 
{
    if (nfa == NULL) return FALSE;

    if (!*text) 
    {
        return IsAccepting(nfa);
    }

    CircularLinearLinkedListNode *t = nfa->edgesManager;

    do
    {
        if (((Edge*)t->info)->weight == *text || ((Edge*)t->info)->weight == EPSILON_TRANSITION) 
        {
            if (match(((Edge*)t->info)->dest, text + 1))
            {
                return TRUE;
            }
        }

        t = t->nextNode;
    }
    while (t != nfa->edgesManager);

    return FALSE;
}

int main()
{
    char *pattern = "ab*c*";
    char *strings[] = {"ac", "abc", "abbbc", "a", "abbabbbc"};
    int strings_count = sizeof(strings) / sizeof(strings[0]);

    StateMachine *nfa = RegexToNFA(pattern);
    State *start = nfa->verticesManager->nextNode;

    for (int i = 0; i < strings_count; i++)
    {
        if (match(start, strings[i]))
        {
            printf("%s matches %s\n", strings[i], pattern);
        } 
        else
        {
            printf("%s does not match %s\n", strings[i], pattern);
        }
    }

    return 0;
}