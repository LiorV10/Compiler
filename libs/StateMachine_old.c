#include "CommonMacros.h"
#include "Graph.h"
#include "Stack.h"
#include <stdio.h>
#include <sys/time.h>

#define CONCAT_CHARACTER '\002'
#define EPSILON_TRANSITION '\000'
#define ANY_CHARACTER '\001'
#define ASCII_LETTERS_PATTERN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ|||||||||||||||||||||||||||||||||||||||||||||||||||"
#define DIGIT_PATTERN "0123456789|||||||||"


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
        printf("[%d][%d][%p]:", ((Vertex *)ptr->info)->isAccepting, ((Vertex *)ptr->info)->info, ((Vertex *)ptr->info));
        PrintList(((Vertex *)ptr->info)->edgesManager);
        ptr = ptr->nextNode;
    } while (ptr != graph->verticesManager->nextNode);

    puts("");
}

typedef Vertex State;
typedef Edge Transition;
typedef Graph StateMachine;

BOOL EpsilonClosure(CircularLinearLinkedListNode **states);
StateMachine *OneOrMore(StateMachine *previous);

void InitStateMachine(StateMachine *stateMachine)
{
    InitGraph(stateMachine);
}

State *AddState(StateMachine *stateMachine)
{
    return (AddVertex(stateMachine, NULL, FALSE));
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

State *FinalState(StateMachine *stateMachine)
{
    return (stateMachine->verticesManager->info);
}

State *InitialState(StateMachine *stateMachine)
{
    return (stateMachine->verticesManager->nextNode->info);
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
    CircularLinearLinkedListNode *firstStart = first->verticesManager->nextNode;
    State *firstEnd = first->verticesManager->info;
    State *secondStart = second->verticesManager->nextNode->info;

    first->verticesManager->nextNode = second->verticesManager->nextNode;
    second->verticesManager->nextNode = firstStart;
    first = second;

    applyTransition ? AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION) : ZERO;

    return (first);
}
StateMachine *Union(StateMachine *first, StateMachine *second)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine);
    State *secondStart = second->verticesManager->nextNode->info;
    State *secondEnd = second->verticesManager->info;
    State *end;

    stateMachine = Concat(stateMachine, first, TRUE);
    stateMachine = Concat(stateMachine, second, FALSE);
    AddTransition(stateMachine, start, secondStart, EPSILON_TRANSITION);
    end = AddState(stateMachine);
    AddTransition(stateMachine, first->verticesManager->info, end, EPSILON_TRANSITION);
    AddTransition(stateMachine, secondEnd, end, EPSILON_TRANSITION);

    return (stateMachine);
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
    State *end = previous->verticesManager->info;

    AddTransition(previous, end, AddState(previous), EPSILON_TRANSITION);
    end = previous->verticesManager->info;
    newStart = Concat(newStart, previous, TRUE);

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
    StateMachine *nfa;

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case '\004':
                PushStack(&stack, RegexToNFA(ASCII_LETTERS_PATTERN));
                break;
            case '\005':
                PushStack(&stack, RegexToNFA(DIGIT_PATTERN));
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
            case CONCAT_CHARACTER:
                PushStack(&stack, Concat(PopStack(&stack), PopStack(&stack), TRUE));
                break;
            default:
                PushStack(&stack, FromSymbol(*pattern));
                break;
        }
    }

    nfa = PopStack(&stack);
    MakeAccepting(FinalState(nfa));

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
    return (transition->weight == symbol);
}

BOOL IsPossibleTransition(Transition *transition, char symbol)
{
    return (IsSymbolTransition(transition, symbol) || 
            ((IsSymbolTransition(transition, ANY_CHARACTER))));
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
        transitions = ((State *)currentStatesPtr->info)->edgesManager;

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

    return (accepting ? !accepting->edgesManager : FALSE);
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

typedef struct
{
    char *start;
    char *end;
} MatchType;

MatchType* Match(StateMachine *stateMachine, char *input)
{
    CircularLinearLinkedListNode *currentStates;
    CircularLinearLinkedListNode *nextStates;
    MatchType *result = NULL;
    char *ptr = input;

    nextStates = currentStates = InitStatesList(InitialState(stateMachine), *input);
    MakeTransitions(currentStates, &nextStates, *input);
    nextStates = CompareLists(currentStates, nextStates) ? NULL : nextStates;
    
    while (*input && nextStates && !IsTerminated(currentStates))
    {
        EpsilonClosure(&nextStates);

        currentStates = nextStates;
        nextStates = NULL;

        SetAllVisited(stateMachine, FALSE);
        MakeTransitions(currentStates, &nextStates, *++input);
    }

    if (!!FindAcceptingState(currentStates))
    {
        result = malloc(sizeof(MatchType));
        *result = (MatchType){.start = ptr, .end = input};
    }
    
    SetAllVisited(stateMachine, FALSE);
    EmptyCircularLinearLinkedList(&currentStates);

    return (result);
}

/* TESTING */

#define PATTERNS_COUNT 7

void print_range(char *s, char *e)
{
    for (; s < e; s++)
    {
        printf("%c", *s);
    }
}

void main(void)
{
    MatchType *currentMatch;
    StateMachine *nfas[PATTERNS_NUM];

    char *patterns[PATTERNS_NUM] = 
    {
         // ".+"
        "\"\001+\002\"\002",         

        // int|float|[^a-zA-Z\d_]
        "in\002t\002fl\002o\002a\002t\002| \n|\002",
        
        // [_a-zA-Z][_a-zA-Z\d]*                                      
        "_\004|\004\005|*\002",//"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ||||||||||||||||||||||||||||||||||||||||||||||||||||+",
        
        // [;=]
        ";=.||",  

        // \d+.\d+                                                    
        "\005+.\002\005+\002",//"0123456789|||||||||+.\0010123456789|||||||||+\001",

        // \d+        
        "\005+",//"01|2|3|4|5|6|7|8|9|+",

         // \s+                                      
        " \n\r\t|||+"                                              
    };

    // char *patterns[PATTERNS_COUNT] = 
    // {
    //      // ".+"
    //     "\"\003+\001\"\001",         

    //     // int|float[^a-zA-Z\d_]
    //     "in\001t\001fl\001o\001a\001t\001| \n|\001",
        
    //     // [_a-zA-Z][_a-zA-Z\d]*                                      
    //     "_\004|\004\005|*\001",//"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ||||||||||||||||||||||||||||||||||||||||||||||||||||+",
        
    //     // [;=]
    //     ";=.||",  

    //     // \d+.\d+                                                    
    //     "0123456789|||||||||+.\0010123456789|||||||||+\001",

    //     // \d+        
    //     "01|2|3|4|5|6|7|8|9|+",

    //      // \s+                                      
    //     " \n\r\t|||+"                                              
    // };

    char *type[PATTERNS_NUM] = 
    {
        "string literal",
        "keyword",
        "identifier",
        "operator",
        "float literal",
        "integer literal",
        "whitespace"
    };

    char *code = "float x\n = 2343.33248;";

    for (int i = 0; i < PATTERNS_NUM; i++)
    {
        nfas[i] = RegexToNFA(patterns[i]);
    }

    while (*code)
    {
        for (int i = 0; i < PATTERNS_NUM; i++)
        {
            if ((currentMatch = Match(nfas[i], code)))
            {
                print_range(currentMatch->start, currentMatch->end);
                printf(" -> %s\n", type[i]);
                code = currentMatch->end;
                i = 0;
            }

            free(currentMatch);
        }
    }
}

/*
void main_(void)
{
    //"ab.a.b.ab.b.b.|"
    // 01|2|3|4|5|6|7|8|9

    char *single_line_comment = ""; //"/*.\2$`.*./.vo.i.d.ma.i.n. []|||||";
    char *pattern1 = SINGLE_LINE_COMMENT_PATTERN;//"\2$vo.i.d.ma.i.n. []|||||";
    //"abcd_||||+abcd012345_||||||||||*."; //"a?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.";
    // char *strings1[] =
    // {
    //     "void main(void)\n{\nprintf(\"hello world!\")\n}"
    // }; //{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    //int strings_count1 = sizeof(strings1) / sizeof(strings1[0]);

    char *pattern2 = "a?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.";
    //char *pattern2 = "?a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a?.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a.a"
    char *strings2[] =
    {
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}; //{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
    int strings_count2 = sizeof(strings2) / sizeof(strings2[0]);

    struct timeval stop, start;

    StateMachine *nfa1 = RegexToNFA(pattern1);
    StateMachine *nfa2 = RegexToNFA(pattern2);
    MatchType *current;

    CircularLinearLinkedListNode *vertices = nfa1->verticesManager->nextNode;
    int i = 0;

    // do
    // {
    //     ((State *)vertices->info)->info = i++;
    //     vertices = vertices->nextNode;
    // } while (vertices != nfa1->verticesManager->nextNode);

    PrintGraph(nfa1);
    //PrintGraph(nfa2);

    gettimeofday(&start, NULL);
    puts("\n");

    if (1)
    while ((current = Match(nfa1, ccode)) && current->end != current->start)
    {
        printf("matches -> \n#");

        for (; current->start < current->end; current->start++)
        {
            printf("%c", *current->start);
        }
        
        puts("#");
        ccode = current->end;
        free(current);
    }

    puts("");

    if (0)
    for (int i = 0; i < strings_count2; i++)
    {
        if ((current = Match(nfa2, strings2[i])))
        {
            printf("%s\t\tmatches [%s] -> ", strings2[i], pattern2);

            for (; current->start < current->end; current->start++)
            {
                printf("%c", *current->start);
            }
            puts("");
            free(current);
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
*/