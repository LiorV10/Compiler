// Regex.c

#include "Regex.h"

#define PREDEFINED_PATTERNS {[LTETTERS_CHAR] = LETTERS_PATTERN, [DIGIT_CHAR] = DIGIT_PATTERN}

struct ThompsonExecutor
{
    StateMachine* (*operatorFunctionPtr)();
    void (*typeFunctionPtr)();
};

StateMachine *ThompsonConstruction(char *pattern);

void ApplyPredefinedPattern(Stack *machines, StateMachine* (*function)(), char *pattern)
{
    char *patterns[] = PREDEFINED_PATTERNS;

    PushStack(machines, function(patterns[*pattern]));
}

void ApplyUnaryOperator(Stack *machines, StateMachine* (*function)(), char *pattern)
{
    PushStack(machines, function(PopStack(machines)));
}

void ApplyBinaryOperator(Stack *machines, StateMachine* (*function)(), char *pattern)
{
    PushStack(machines, function(PopStack(machines), PopStack(machines)));
}

void ApplySymbol(Stack *machines, StateMachine* (*function)(), char *pattern)
{
    PushStack(machines, function(*pattern));
}

void ExecuteThompsonExecutor(Stack *stack, char *pattern, struct ThompsonExecutor *thompsonExecutor)
{
    thompsonExecutor->typeFunctionPtr(stack, thompsonExecutor->operatorFunctionPtr, pattern);
}

//-----------------------------------------------------------------------------
//                                      Thompson Construction                                     
//                                      ---------------------                             
//                                                                             
// General      : The function constructs a NFA from a given regex, according
//                to the thompson's algorithm.                                                    
//                                                                             
// Parameters   :                                                             
//       pattern - The regex pattern (In)						                                        
//                                                                             
// Return Value : The NFA.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
StateMachine* ThompsonConstruction(char *pattern)
{
    Stack stack;

    struct ThompsonExecutor thompsonExecutors[] =
    {
        [ANY_SYMBOL] = {.operatorFunctionPtr = FromSymbol, .typeFunctionPtr = ApplySymbol},
        [LTETTERS_CHAR] = {.operatorFunctionPtr = ThompsonConstruction, .typeFunctionPtr = ApplyPredefinedPattern},
        [DIGIT_CHAR] = {.operatorFunctionPtr = ThompsonConstruction, .typeFunctionPtr = ApplyPredefinedPattern},
        [CONCAT_CHAR] = {.operatorFunctionPtr = ConcatWithTransition, .typeFunctionPtr = ApplyBinaryOperator},
        [STAR_OPERATOR] = {.operatorFunctionPtr = Star, .typeFunctionPtr = ApplyUnaryOperator},
        [ALTERNATION_OPERATOR] = {.operatorFunctionPtr = Alternate, .typeFunctionPtr = ApplyUnaryOperator},
        [UNION_OPERATOR] = {.operatorFunctionPtr = Union, .typeFunctionPtr = ApplyBinaryOperator},
        [PLUS_OPERATOR] = {.operatorFunctionPtr = OneOrMore, .typeFunctionPtr = ApplyUnaryOperator},
        [MAX_OPERATOR + ONE] = {.operatorFunctionPtr = FromSymbol, .typeFunctionPtr = ApplySymbol}
    };

    InitStack(&stack);

    for (; *pattern; pattern++)
    {
        ExecuteThompsonExecutor(&stack, pattern, thompsonExecutors + MIN(*pattern, MAX_OPERATOR + ONE));
    }

    return (PopStack(&stack));
}

//-----------------------------------------------------------------------------
//                                      Regex To NFA                                     
//                                      ------------                                  
//                                                                             
// General      : The function constructs a NFA from regex pattern and type.                                                           
//                                                                             
// Parameters   :                                                              
//       pattern - The regex pattern (In)						                                        
//       matchType - The pattern's type (In)						                                        
//                                                                             
// Return Value : The NFA.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
StateMachine *RegexToNFA(char *pattern, unsigned short matchType)
{
    StateMachine *nfa = ThompsonConstruction(pattern);

    FinalState(nfa)->info = matchType;

    return (nfa);
}

//-----------------------------------------------------------------------------
//                                      Find Accepting State                                     
//                                      -----                                  
//                                                                             
// General      : The function attempts to find an accepting state in a list
//                of states.                                 
//                                                                             
// Parameters   :                                                              
//       states - The list of states (In)						                                        
//                                                                             
// Return Value : The accepting state, if found.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
State* FindAcceptingState(CircularLinearLinkedListNode *states)
{
    CircularLinearLinkedListNode *ptr = states;
    State *acceptingState = ptr->info;

    do
    {
        ((State*)ptr->info)->info > acceptingState->info ?
            acceptingState = ptr->info : ZERO;

        ptr = ptr->nextNode;
    } 
    while (ptr != states);

    return (acceptingState->info ? acceptingState : NULL);
}

//-----------------------------------------------------------------------------
//                                      Make Match                                     
//                                      -----                                  
//                                                                             
// General      : The function makes a match from a substring and pattern type.                                                           
//                                                                             
// Parameters   :                                                              
//       start - The start of the substring (In)						                                        
//       end - The end of the substring (In)						                                        
//       matchType - The pattern's type (In)						                                        
//                                                                             
// Return Value : The match.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//                                      Init States List                                     
//                                      -----                                  
//                                                                             
// General      : The function initializes a states list with the initial state.                                                           
//                                                                             
// Parameters   :                                                              
//       states - The list of states (In)						                                        
//       state - The initial state (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void InitStatesList(CircularLinearLinkedListNode **states, State *state)
{
    InitCircularLinearLinkedList(states);
    InsertLastCircularLinearLinkedList(states);
    (*states)->info = state;
}

//-----------------------------------------------------------------------------
//                                      Execute Regex                                     
//                                      -----                                  
//                                                                             
// General      : The function matches a string to a regex pattern.                                                           
//                                                                             
// Parameters   :                                                              
//       nfa - The regex pattern as NFA (In)
//       input - The string to match (In)						                                        
//                                                                             
// Return Value : The match, if found.             
//-----------------------------------------------------------------------------
// T(n) = c1 * n + c2 * m + d -> O(n + m)
//-----------------------------------------------------------------------------
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

    match = (acceptingState = FindAcceptingState(currentStates)) ?
        MakeMatch(inputStart, input, acceptingState->info) :
        NULL;

    SetAllVisited(currentStates, FALSE);

    EmptyCircularLinearLinkedList(&currentStates, NULL);
    nextStates ? EmptyCircularLinearLinkedList(&nextStates, NULL) : ZERO;

    return (match);
}