// StateMachine.c

#ifndef _STATE_MACHINE_H
    #include "StateMachine.h"
#endif

//-----------------------------------------------------------------------------
//                              Init State Machine                                     
//                              ------------------                                 
//                                                                             
// General      : The function initializes the state machine                                                           
//                                                                             
// Parameters   :                                                              
//       stateMachine - The state machine to initialize (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void InitStateMachine(StateMachine *stateMachine)
{
    InitCircularLinearLinkedList(&stateMachine->statesManager);
}

//-----------------------------------------------------------------------------
//                                      Add State                                     
//                                      ---------                                 
//                                                                             
// General      : The function adds a new state at the end.                                                           
//                                                                             
// Parameters   :                                                              
//       stateMachine - The state machine (In)						                                        						                                        
//                                                                             
// Return Value : The state added.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
State *AddState(StateMachine *stateMachine)
{
    State *newState = malloc(sizeof(State));

    InitCircularLinearLinkedList(&newState->transitionsManager);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertEndCircularLinearLinkedList(&stateMachine->statesManager);

    newState->info = ZERO;
    newState->visited = FALSE;
    
    stateMachine->statesManager->info = newState;

    return (newState);
}

//-----------------------------------------------------------------------------
//                                      Push State                                     
//                                      ----------                                 
//                                                                             
// General      : The function adds a new state at the start.                                                           
//                                                                             
// Parameters   :                                                              
//       stateMachine - The state machine to initialize (In)						                                        						                                        
//                                                                             
// Return Value : The state added.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
State* PushState(StateMachine *stateMachine)
{
    State *newState = malloc(sizeof(State));

    InitCircularLinearLinkedList(&newState->transitionsManager);

    !stateMachine->statesManager ? 
        InsertLastCircularLinearLinkedList(&stateMachine->statesManager) :
        InsertAfterCircularLinearLinkedList(stateMachine->statesManager);

    newState->info = ZERO;
    newState->visited = FALSE;
    
    stateMachine->statesManager->nextNode->info = newState;

    return (newState);
}

//-----------------------------------------------------------------------------
//                                      Add Transition                                     
//                                      --------------                                  
//                                                                             
// General      : The function adds a new weighted directed edge between two
//                given states.                                                      
//                                                                             
// Parameters   :                                                              
//       stateMachine - The state machine to initialize (In)						                                        
//       source - The source state (In)						                                        
//       dest - The dest state (In)						                                        
//       symbol - The weight of the edge (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) =  d -> O(1)
//-----------------------------------------------------------------------------
void AddTransition(StateMachine *stateMachine, State *source, State *dest, char symbol)
{
    Transition *transition = malloc(sizeof(Transition));

    !source->transitionsManager ? 
        InsertLastCircularLinearLinkedList(&source->transitionsManager) :
        InsertEndCircularLinearLinkedList(&source->transitionsManager);

    transition->dest = dest;
    transition->symbol = symbol;
    source->transitionsManager->info = transition;
}

//-----------------------------------------------------------------------------
//                                      Final State                                     
//                                      -----------                                  
//                                                                             
// General      : The function finds the final state of a state machine.                                                           
//                                                                             
// Parameters   :                                                              
//       source - The source state (In)						                                        						                                        
//                                                                             
// Return Value : The final state.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
State *FinalState(StateMachine *stateMachine)
{
    return (stateMachine->statesManager->info);
}

//-----------------------------------------------------------------------------
//                                      Initial State                                     
//                                      -------------                                  
//                                                                             
// General      : The function finds the final state of a state machine.                                                           
//                                                                             
// Parameters   :                                                              
//       source - The source state (In)						                                        						                                        
//                                                                             
// Return Value : The final state.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
State *InitialState(StateMachine *stateMachine)
{
    return (stateMachine->statesManager->nextNode->info);
}

//-----------------------------------------------------------------------------
//                                      Concat State Machines                                     
//                                      ---------------------                                 
//                                                                             
// General      : The function concats a source state machine into a dest.                                                           
//                                                                             
// Parameters   :                                                              
//      first - The dest state machine (In)						                                        
//      second - The source state machine (In)						                                        
//                                                                             
// Return Value : The None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
void ConcatStateMachines(StateMachine *first, StateMachine *second)
{
    ConcatCircularLinearLinkedLists(&first->statesManager, second->statesManager);
}

//-----------------------------------------------------------------------------
//                                      Thompson Construcions                                     
//                                      ---------------------                                 
//                                                                             
// General      : The following functions implement the
//                thompson construction algorithm.                                                           
//                                                                             
// Parameters   :                                                              
//       first - The left state machine (In)						                                        
//       second - The right state machine (In)
//       symbol - The symbol in the regex pattern (In)						                                        
//                                                                             
// Return Value : The state machine after applying the operator.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
#pragma region ThomsponConstructions

StateMachine *FromSymbol(char symbol)
{
    StateMachine *stateMachine = malloc(sizeof(StateMachine));
    InitStateMachine(stateMachine);

    State *start = AddState(stateMachine);
    State *end = AddState(stateMachine);

    AddTransition(stateMachine, start, end, symbol);

    return (stateMachine);
}

StateMachine* ConcatWithTransition(StateMachine *first, StateMachine *second)
{
    State *firstEnd = FinalState(first);
    State *secondStart = InitialState(second);

    ConcatStateMachines(first, second);
    AddTransition(first, firstEnd, secondStart, EPSILON_TRANSITION);

    free(second);

    return (first);
}

StateMachine* Concat(StateMachine *first, StateMachine *second)
{
    State *firstEnd = FinalState(first);
    State *secondStart = InitialState(second);

    ConcatStateMachines(first, second);

    free(second);

    return (first);
}

StateMachine *Union(StateMachine *first, StateMachine *second)
{
    State *firstStart = InitialState(first);
    State *firstEnd = FinalState(first);

    State *secondStart = InitialState(second);
    State *secondEnd = FinalState(second);

    State *temp = PushState(first);

    first = Concat(first, second);
    AddTransition(first, temp, firstStart, EPSILON_TRANSITION);
    AddTransition(first, temp, secondStart, EPSILON_TRANSITION);
    
    temp = AddState(first);
    AddTransition(first, firstEnd, temp, EPSILON_TRANSITION);
    AddTransition(first, secondEnd, temp, EPSILON_TRANSITION);

    return (first);
}

StateMachine *OneOrMore(StateMachine *stateMachine)
{
    State *start = InitialState(stateMachine);
    State *end = FinalState(stateMachine);

    AddTransition(stateMachine, end, start, EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *Star(StateMachine *stateMachine)
{
    stateMachine = OneOrMore(stateMachine);

    AddTransition(stateMachine, InitialState(stateMachine), FinalState(stateMachine), EPSILON_TRANSITION);

    return (stateMachine);
}

StateMachine *Alternate(StateMachine *stateMachine)
{
    AddTransition(stateMachine, InitialState(stateMachine), FinalState(stateMachine), EPSILON_TRANSITION);

    return (stateMachine);
}

#pragma endregion

//-----------------------------------------------------------------------------
//                                      Insert State                                     
//                                      -----                                  
//                                                                             
// General      : The function inserts a state to the closure list.                                                           
//                                                                             
// Parameters   :                                                              
//      states - The closure states list (In)						                                        
//      state - The state to insert (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void InsertState(CircularLinearLinkedListNode **states, State *state)
{
    *states ? 
        InsertEndCircularLinearLinkedList(states) : 
        InsertLastCircularLinearLinkedList(states);

    state->visited = TRUE;
    (*states)->info = state;
}

//-----------------------------------------------------------------------------
//                                      Select Next Transitions                                     
//                                      -----                                  
//                                                                             
// General      : The function selects the destination states of transitions
//                with a given symbol from list of transitions.                                                          
//                                                                             
// Parameters   :                                                              
//       transitions - The transitions list (In)						                                        
//       nextStates - The states selected (In)						                                        
//       symbol - The desired symbol (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void SelectNextTransitions(CircularLinearLinkedListNode *transitions,
                           CircularLinearLinkedListNode **nextStates,
                           char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *ptr = transitions->nextNode;

    do
    {
        currentTransition = ptr->info;

        !currentTransition->dest->visited && currentTransition->symbol == symbol ?
            InsertState(nextStates, currentTransition->dest) : 
            ZERO;

        ptr = ptr->nextNode;
    } 
    while (ptr != transitions->nextNode);
}

//-----------------------------------------------------------------------------
//                                      Select Symbol Transitions                                     
//                                      -----                                  
//                                                                             
// General      : The function selects the destination states of transitions
//                with a given symbol from list of states.                                                          
//                                                                             
// Parameters   :                                                              
//       currentStates - The states list (In)						                                        
//       startPtr - The start of the states list (In)						                                        
//       nextStates - The states selected (In)						                                        
//       symbol - The desired symbol (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n, m) = c1 * n + c2 * m + d -> O(n + m) 
//-----------------------------------------------------------------------------
void SelectSymbolTransitions(CircularLinearLinkedListNode *currentStates,
                           CircularLinearLinkedListNode *startPtr,
                           CircularLinearLinkedListNode **nextStates,
                           char symbol)
{
    Transition *currentTransition;
    CircularLinearLinkedListNode *currentStatesPtr = startPtr;
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

//-----------------------------------------------------------------------------
//                                      Select All transitions                                     
//                                      -----                                  
//                                                                             
// General      : The function attempts to select either destination states
//                of transitions with a given symbol, or, if not found, 
//                transitions labled as any symbol.                                                           
//                                                                             
// Parameters   :                                                              
//       currentStates - The list of current states (In)						                                        
//       nextState - The list of selected states (In)						                                        
//       symbol - The desired symbol (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n, m) = c1 * n + c2 * m + d -> O(n + m)
//-----------------------------------------------------------------------------
void SelectAllTransitions(CircularLinearLinkedListNode *currentStates,
                        CircularLinearLinkedListNode **nextStates,
                        char symbol)
{
    SelectSymbolTransitions(currentStates, currentStates->nextNode, nextStates, symbol);
    !*nextStates ? SelectSymbolTransitions(currentStates, currentStates->nextNode, nextStates, ANY_SYMBOL) : ZERO;
}

//-----------------------------------------------------------------------------
//                                      Epsilon Closure                                     
//                                      -----                                  
//                                                                             
// General      : The function finds the epsilon closure of a given
//                list of states.                                                           
//                                                                             
// Parameters   :                                                              
//       states - The list of states (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n, m) = c1 * n + c2 * m + d -> O(n + m)
//-----------------------------------------------------------------------------
void EpsilonClosure(CircularLinearLinkedListNode **states)
{
    CircularLinearLinkedListNode *epsilonStates;
    CircularLinearLinkedListNode *previousEpsilonStates;

    InitCircularLinearLinkedList(&epsilonStates);
    SelectSymbolTransitions(*states, (*states)->nextNode, &epsilonStates, EPSILON_TRANSITION);

    while (epsilonStates)
    {
        previousEpsilonStates = epsilonStates->nextNode;
        ConcatCircularLinearLinkedLists(states, epsilonStates);
        epsilonStates = NULL;
        SelectSymbolTransitions(*states, previousEpsilonStates, &epsilonStates, EPSILON_TRANSITION);
    }
}

//-----------------------------------------------------------------------------
//                                      Set All Visited                                     
//                                      -----                                  
//                                                                             
// General      : The function sets all states in a given list to a given 
//                visited mode.                                           
//                                                                             
// Parameters   :                                                              
//       statesList - The list of states (In)						                                        
//       visited - The desired visited mode (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void SetAllVisited(CircularLinearLinkedListNode *statesList, BOOL visited)
{
    CircularLinearLinkedListNode *states = statesList;

    do
    {
        ((State*)states->info)->visited = visited;
        states = states->nextNode;
    } 
    while (states != statesList);
}

//-----------------------------------------------------------------------------
//                                      Select Next States                                     
//                                      -----                                  
//                                                                             
// General      : The function selects all the reachable next states from a 
//                given list of states.                                                          
//                                                                             
// Parameters   :                                                              
//       nfa - The state machine (In)						                                        
//       currentStates - The list of current states (In)						                                        
//       nextStates - The list of selected states (In)						                                        
//       symbol - The desired symbol (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n, m) = c1 * n + c2 * m + d -> O(n + m)
//-----------------------------------------------------------------------------
void SelectNextStates(StateMachine *nfa,
                   CircularLinearLinkedListNode **currentStates, 
                   CircularLinearLinkedListNode **nextStates,
                   char symbol)
{
    EmptyCircularLinearLinkedList(currentStates, NULL);
    EpsilonClosure(nextStates);
    
    SWAP(*nextStates, *currentStates, CircularLinearLinkedListNode*);

    SetAllVisited(*currentStates, FALSE);

    SelectAllTransitions(*currentStates, nextStates, symbol);
}

void EmptyState(State *state)
{
    state->transitionsManager ? 
        EmptyCircularLinearLinkedList(&state->transitionsManager, free) : ZERO;
    free(state);
}

void EmptyStateMachine(StateMachine *stateMachine)
{
    EmptyCircularLinearLinkedList(&stateMachine->statesManager, EmptyState);
    free(stateMachine);
}