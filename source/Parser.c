// Parser.c

#include "Parser.h"

#define REDUCING_STATE_MASK 0b01
#define ACCEPTING_STATE_MASK 0b10

BOOL CompareItems(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition &&
            first->rule == second->rule && first->lookahead == second->lookahead);
}

#if GENERATE_LALR
    BOOL CompareItemKernels(Item *first, Item *second)
    {
        return (first->dotPosition == second->dotPosition && first->rule == second->rule);
    }
#else
    BOOL CompareItemKernels(Item *first, Item *second)
    {
        return CompareItems(first, second);
    }
#endif

CircularLinearLinkedListNode *KernelEnd(CircularLinearLinkedListNode *lrItems)
{
    CircularLinearLinkedListNode *ptr = lrItems->nextNode;
    BOOL isKernelItem = TRUE;

    do
    {
        isKernelItem = ((Item*)ptr->info)->dotPosition != ((Item*)ptr->info)->rule->expressions;
        ptr = ptr->nextNode;
    }
    while (ptr != lrItems->nextNode && isKernelItem);

    return (ptr);
}

BOOL CompareItemsLists(CircularLinearLinkedListNode *firstStart, CircularLinearLinkedListNode *secondStart,
                       CircularLinearLinkedListNode *firstEnd, CircularLinearLinkedListNode *secondEnd)
{
    BOOL areEqual = TRUE;

    do
    {
        areEqual = CompareItemKernels(firstStart->info, secondStart->info);

        firstStart = firstStart->nextNode;
        secondStart = secondStart->nextNode;
    }
    while (areEqual && firstStart != firstEnd && secondStart != secondEnd);

    return (areEqual);
}

BOOL CompareKernels(CircularLinearLinkedListNode *first, CircularLinearLinkedListNode *second)
{
    return CompareItemsLists(first->nextNode, second->nextNode, KernelEnd(first), KernelEnd(second));
}

BOOL StatesComparator(PushdownState* first, Expression *second)
{
    return first->key == second->nodeKey && CompareKernels(first->lrItems, second->node);
}

unsigned long PointerKey(void *ptr)
{
    return (unsigned long)ptr & sizeof(void*);
}

unsigned long ItemKey(Item *item)
{
    return (PointerKey(item->rule) + PointerKey(item->dotPosition) + item->lookahead);
}

unsigned long KeyState(PushdownState *state)
{
    return state->key;
}

//-----------------------------------------------------------------------------
//                                      Add Closure Item                                     
//                                      -----                                  
//                                                                             
// General      : The function adds the initial item from a given
//                rule and lookahead, into the closure items list.                                                          
//                                                                             
// Parameters   :                                                              
//      closureStack - The closure stack (In)						                                        
//      items - The closure items list (In)						                                        
//      rule - The rule to add (In)						                                        
//      terminal - The lookahead to attach to the item (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//----------------------------------------------------------------------------- 
void AddClosureItem(Stack *closureStack, CircularLinearLinkedListNode **items, Rule *rule, TokenType terminal)
{
    Item *newItem;

    newItem = InitialItem(rule, terminal);
    BIT_SET(newItem->rule->visited, terminal);

    InsertEndCircularLinearLinkedList(items);
    (*items)->info = newItem;


    !((Expression*)newItem->dotPosition->info)->isTerminal ?
        PushStack(closureStack, (*items)->info) : ZERO;

}

//-----------------------------------------------------------------------------
//                                      Current Rule Closure                                     
//                                      --------------------                                  
//                                                                             
// General      : The function adds the closure items from a given rule.                                                          
//                                                                             
// Parameters   :                                                              
//      closureStack - The closure stack (In)						                                        
//      items - The closure items list (In)						                                        
//      rule - The rule to add (In)							                                        
//      item - The item which points to the rule (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = |Σ| + d -> O(1)
//-----------------------------------------------------------------------------
void CurrentRuleClosure(Stack *closureStack, CircularLinearLinkedListNode **items, Rule *rule, Item *item)
{
    TokenType terminal = ZERO;

    unsigned long firstset = item->dotPosition->nextNode ? 
        ((Expression*)item->dotPosition->nextNode->info)->firstSet :
        ((unsigned long)ONE << item->lookahead);


    for (; firstset; firstset >>= ONE, terminal++)
    {
        for (; ~firstset & ONE; firstset >>= ONE, terminal++);

        !BIT_TEST(rule->visited, terminal) ?
            AddClosureItem(closureStack, items, rule, terminal) : ZERO;
    }
}

//-----------------------------------------------------------------------------
//                                      Closure                                     
//                                      -------                                
//                                                                             
// General      : The function performs the closure operation 
//                over list of items.                                                           
//                                                                             
// Parameters   :                                                              
//       items - The list of items (I/O)						                                        
//                                                                             
// Return Value : The result of the operator and the two operands.             
//-----------------------------------------------------------------------------
// T(n) = c * (|R| + |V|) + d -> O(|R| + |V|)
//-----------------------------------------------------------------------------
void Closure(CircularLinearLinkedListNode **items)
{
    Item *currentItem;
    Stack closureStack;
    NonTerminal *nextNonTerminal;
    CircularLinearLinkedListNode *itemsPtr = (*items)->nextNode;
    LinearLinkedListNode *rules;

    InitStack(&closureStack);

    do
    {
        ((Item*)itemsPtr->info)->dotPosition && !((Expression*)((Item*)itemsPtr->info)->dotPosition->info)->isTerminal ?
            PushStack(&closureStack, itemsPtr->info) : 
            ZERO;

        itemsPtr = itemsPtr->nextNode;
    }
    while (itemsPtr != (*items)->nextNode);

    while (!IsEmptyStack(&closureStack))
    {
        currentItem = PopStack(&closureStack);
        nextNonTerminal = ((Expression*)currentItem->dotPosition->info)->value.nonTerminal;

        for (rules = nextNonTerminal->rules; rules; rules = rules->nextNode)
            CurrentRuleClosure(&closureStack, items, rules->info, currentItem);
    }
}

//-----------------------------------------------------------------------------
//                                      Make Initial Goto Item                                     
//                                      -----                                  
//                                                                             
// General      : The function handles the first item in the
//                goto state of an expression.                                                           
//                                                                             
// Parameters   :                                                              
//       item - The item (In)						                                        
//       expressions - The visited expressions list (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//----------------------------------------------------------------------------- 
void MakeInitialGotoItem(Item *item, LinearLinkedListNode **expressions)
{
    Expression *expression = item->dotPosition->info;

    PushLinearLinkedList(expressions);
    (*expressions)->info = expression;

    InitCircularLinearLinkedList(&expression->node);
    InsertLastCircularLinearLinkedList(&expression->node);
}

//-----------------------------------------------------------------------------
//                                      Handle Next Item                                     
//                                      -----                                  
//                                                                             
// General      : The function adds the next item of a given
//                item to the goto state of its expression.                                                          
//                                                                             
// Parameters   :                                                              
//       item - The item to add (In)
//       expressions - The list of visited expressions (I/O)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
void HandleNextItem(Item *item, LinearLinkedListNode **expressions)
{
    Expression *expression = item->dotPosition->info;
    CircularLinearLinkedListNode *nextStateItems;
    PushdownState *currentState;
    Item *nextItem;

    !expression->node ?
        MakeInitialGotoItem(item, expressions) : 
        InsertEndCircularLinearLinkedList(&expression->node);

    nextItem = NextItem(item);
    
    ((CircularLinearLinkedListNode*)expression->node)->info = nextItem;
    expression->nodeKey += ItemKey(nextItem);
}

//-----------------------------------------------------------------------------
//                                      Handle Final Item                                     
//                                      -----                                  
//                                                                             
// General      : The function adds a reducing state for the
//                final item of a rule.                                                         
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)						                                        
//       currentState - The state before the new reducing state (In)						                                        
//       item - The item with dot position at its end (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void HandleFinalItem(Parser *parser, PushdownState *currentState, Item *item)
{
    PushdownState *reducingState = AddPushdownState(parser->pushdownMachine);
    Item* reducingItem;
    
    InsertLastCircularLinearLinkedList(&reducingState->lrItems);
    
    reducingItem = reducingState->lrItems->info = malloc(sizeof(Item));
    reducingItem->rule = item->rule;
    reducingItem->lookahead = item->lookahead;
    reducingItem->dotPosition = item->dotPosition;

    reducingState->isAccepting |= (REDUCING_STATE_MASK | 
        (ACCEPTING_STATE_MASK & (item->rule->nonTerminal == InitialNonTerminal(parser->grammar)) << ONE));

    AddPushdownTransition(parser->pushdownMachine, currentState, reducingState, (ExpressionValue)item->lookahead);
}

//-----------------------------------------------------------------------------
//                                      Make Goto State                                     
//                                      -----                                  
//                                                                             
// General      : The function constructs the goto state of
//                a given expression, from a give state.                                                          
//                                                                             
// Parameters   :                                                              
//       machine - The pushdown machine (In)						                                        
//       currentState - The state (In)						                                        
//       expression - The expression for the goto (In)						                                        
//       nextStates - The queue of next goto states (In)						                                        
//       visitedState - The already visited states (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//----------------------------------------------------------------------------- 
void MakeGotoState(PushdownMachine *machine, PushdownState *currentState, 
                   Expression *expression, Queue *nextStates, Dictionary *visitedStates)
{
    PushdownState *nextState;
    CircularLinearLinkedListNode *gotoItems = expression->node;

    nextState = currentState;

    if (!(nextState = LookupDictionary(visitedStates, expression, KeyState, StatesComparator)))
    {
        nextState = AddPushdownState(machine);
        nextState->lrItems = gotoItems;
        nextState->key = expression->nodeKey;
        InsertQueue(nextStates, nextState);
        InsertDictionary(visitedStates, nextState, KeyState);
    }
    else
    {
        EmptyCircularLinearLinkedList(&gotoItems, free);
    }

    AddPushdownTransition(machine, currentState, nextState, expression->value);
}

//-----------------------------------------------------------------------------
//                                      Make Goto States                                     
//                                      -----                                  
//                                                                             
// General      : The function constructs all goto states from a given state                                                           
//                                                                             
// Parameters   :                                                              
//      parser - The parser context (In)						                                        
//      currentState - The state (In)						                                        
//      nextStates - The queue of next goto states (In)						                                        
//      visitedStates - The already visited states (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
// n - num of items in the state 
//-----------------------------------------------------------------------------
void MakeGotoStates(Parser *parser, PushdownState *currentState, Queue *nextStates, Dictionary *visitedStates)
{
    CircularLinearLinkedListNode *ptr = currentState->lrItems->nextNode;
    PushdownState *nextState;
    LinearLinkedListNode* visitedExpressions;
    LinearLinkedListNode* expressionsPtr;

    InitLinearLinkedList(&visitedExpressions);

    do
    {
        BIT_VEC_ZERO(((Item*)ptr->info)->rule->visited, TOKENS_NUM);

        ((Item*)ptr->info)->dotPosition ?
            HandleNextItem(ptr->info, &visitedExpressions): 
            HandleFinalItem(parser, currentState, ptr->info);

        ptr = ptr->nextNode;
    }
    while (ptr != currentState->lrItems->nextNode);

    for (expressionsPtr = visitedExpressions; expressionsPtr; expressionsPtr = expressionsPtr->nextNode)
    {
        MakeGotoState(parser->pushdownMachine, currentState, expressionsPtr->info, nextStates, visitedStates);
        ((Expression*)expressionsPtr->info)->node = NULL;
        ((Expression*)expressionsPtr->info)->nodeKey = ZERO;
    }

    EmptyLinearLinkedList(&visitedExpressions, NULL);
}

//-----------------------------------------------------------------------------
//                                      Build LR States                                     
//                                      -----                                  
//                                                                             
// General      : The function builds the LR/LALR pushdown machine of a grammar.                                                           
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
// n - grammar size
//-----------------------------------------------------------------------------
void BuildLRStates(Parser *parser)
{
    PushdownState* initialState = AddPushdownState(parser->pushdownMachine);
    PushdownState *currentState;
    Dictionary visitedStates;
    Queue queue;

    GrammarFirstSet(parser->grammar);
    InitDictionary(&visitedStates);
    InitQueue(&queue);

    InsertLastCircularLinearLinkedList(&initialState->lrItems);
    initialState->lrItems->info = InitialItem(InitialRule(parser->grammar), EOD);

    InsertQueue(&queue, initialState);

    while (!IsEmptyQueue(&queue))
    {
        currentState = RemoveQueue(&queue);

        Closure(&currentState->lrItems);
        MakeGotoStates(parser, currentState, &queue, &visitedStates);
    }

    EmptyDictionary(&visitedStates, NULL);
}

//-----------------------------------------------------------------------------
//                                      Init Parser                                     
//                                      -----                                  
//                                                                             
// General      : The function initializer the parser context.                                                           
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)
//       grammar - The grammar to parse with (In)						                                        
//                                                                             
// Return Value : The result of the operator and the two operands.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d
//-----------------------------------------------------------------------------
void InitParser(Parser *parser, Grammar *grammar)
{
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = grammar;

    InitPushdownMachine(parser->pushdownMachine);
    BuildLRStates(parser);
}

//-----------------------------------------------------------------------------
//                                      Next State                                     
//                                      -----                                  
//                                                                             
// General      : The function finds the next state labeld with
//                given expression from a given state.                                                           
//                                                                             
// Parameters   :                                                              
//       current - The current state (I/O)
//       expression - The expression (In)
//       CompareExpressions - The expressions comparator (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void NextState(PushdownState **current, ExpressionValue expression, BOOL(*ComapreExpressions)(ExpressionValue, ExpressionValue))
{
    CircularLinearLinkedListNode *ptr = (*current)->transitionsManager;
    PushdownState *next = NULL;
    PushdownTransition *currentTransition;
    ExpressionValue symbol;

    do
    {
        currentTransition = ptr->info;

        ComapreExpressions(currentTransition->symbol, expression) ? 
            next = currentTransition->dest, currentTransition :
            ZERO;

        ptr = ptr->nextNode;
    }
    while (ptr != (*current)->transitionsManager);

    *current = next;
}

//-----------------------------------------------------------------------------
//                                      Next Non Line Token                                     
//                                      -----                                  
//                                                                             
// General      : The function updates the line number and
//                moves to the next token.                                                           
//                                                                             
// Parameters   :                                                              
//       tokensPtr - The tokens list (In)						                                        
//       currentLine - The line number (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void NextNonLineToken(CircularLinearLinkedListNode **tokensPtr, unsigned int *currentLine)
{
    (*tokensPtr) = (*tokensPtr)->nextNode;

    while (((Token*)(*tokensPtr)->info)->type == WHITESPACE)
    {
        (*currentLine)++;
        *tokensPtr = (*tokensPtr)->nextNode;
    }
}

//-----------------------------------------------------------------------------
//                                      Shift                                     
//                                      -----                                  
//                                                                             
// General      : The function shifts the current state.                                                           
//                                                                             
// Parameters   :                                                              
//       states - The pushdown machine stack (In)
//       state - The state to shift (In)						                                        
//       tokensPtr - The tokens list (In)						                                        
//       currentLine - The current line number (In)						                                        
//       semanticStack - The semantic stack (In)						                                        
//       unusedNodes - The stack of unused nodes (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
void Shift(Stack *states, PushdownState *state, CircularLinearLinkedListNode **tokenPtr, unsigned int *currentLine,
           Stack *semanticStack, Stack *unusedNodes)
{
    AbstractSyntaxTreeNode *astNode;

    PushStack(states, state);

    MakeAbstractSyntaxTree(&astNode);
    PushStack(semanticStack, astNode);
    PushStack(unusedNodes, astNode);
    astNode->info = (*tokenPtr)->info;
    astNode->label = *currentLine;

    NextNonLineToken(tokenPtr, currentLine);
}

//-----------------------------------------------------------------------------
//                                      Reduce                                     
//                                      -----                                  
//                                                                             
// General      : The function reduces a given rule.                                                           
//                                                                             
// Parameters   :                                                              
//      states - The pushdown machine stack (In)						                                        
//      rule - The rule to reduce (In)						                                        
//      scopeStack - The scope stack context (In)						                                        
//      semanticStack - The semantic stack (In)						                                        
//      errors - The error handler context (In)						                                        
//                                                                             
// Return Value : The goto state.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1)
//-----------------------------------------------------------------------------
PushdownState* Reduce(Stack *states, Rule *rule, ScopeStack *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
    LinearLinkedListNode *ptr;
    PushdownState *nextState;

    rule->semanticAction = rule->semanticAction ? rule->semanticAction : DefaultSemanticAction;
    PushStack(semanticStack, rule->semanticAction(scopeStack, semanticStack, errors));

    for (ptr = rule->expressions; ptr; ptr = ptr->nextNode)
    {
        PopStack(states);
    }

    PushStack(states, (nextState = PopStack(states)));
    NextState(&nextState, (ExpressionValue)rule->nonTerminal, CompareNonTerminals);
    PushStack(states, nextState);

    return (nextState);
}

//-----------------------------------------------------------------------------
//                                      Panic Mode                                     
//                                      -----                                  
//                                                                             
// General      : The function activates panic mode to recover
//                from syntax erorr.                                                           
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)						                                        
//       semanticStack - The semantic stack (In)						                                        
//       tokens - The tokens list (I/O)						                                        
//       errors - The errors handler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//----------------------------------------------------------------------------- 
void PanicMode(Parser *parser, Stack *semanticStack, CircularLinearLinkedListNode **tokens, ErrorHandler *errors)
{
    TokenType syncingTokensVec[SYNCING_TOKENS_NUM] = SYNCING_TOKENS;
    TokenType currentToken;
    PushdownState *currentState;
    PushdownState *nextState = NULL;

    BIT_VEC(syncingTokens, TOKENS_NUM);
    BIT_VEC_ZERO(syncingTokens, TOKENS_NUM);

    for (currentToken = ZERO; currentToken < SYNCING_TOKENS_NUM; currentToken++)
    {
        BIT_SET(syncingTokens, syncingTokensVec[currentToken]);
    }

    MakeError(errors, "Unexcpected token: `%s`", ((Token*)(*tokens)->info)->lexeme);

    while (!BIT_TEST(syncingTokens, ((Token*)(*tokens)->info)->type)) 
        NextNonLineToken(tokens, &errors->currentLine);
    
    NextNonLineToken(tokens, &errors->currentLine);

    while (!nextState && !IsEmptyStack(parser->pushdownMachine->stack))
    {
        nextState = currentState = PopStack(parser->pushdownMachine->stack);

        NextState(&nextState, (ExpressionValue)((Token*)(*tokens)->info)->type, CompareTerminals);

        !nextState ? FreeAbstractSyntaxTree(PopStack(semanticStack)) : ZERO;
    }

    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)(*tokens)->info)->type, CompareTerminals);
}

//-----------------------------------------------------------------------------
//                                      Parse                                     
//                                      -----                                  
//                                                                             
// General      : The function parses a list of tokens
//                according to a given gramar.                                                           
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)						                                        
//       tokens - The list of tokens (In)						                                        
//       errors - The error handler context (In)						                                        
//                                                                             
// Return Value : The built abstract syntax tree.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
AbstractSyntaxTreeNode* Parse(Parser *parser, CircularLinearLinkedListNode *tokens, ErrorHandler *errors)
{
    PushdownState *currentState = InitialPushdownState(parser->pushdownMachine);
    CircularLinearLinkedListNode *tokensPtr = tokens->nextNode;
    Stack semanticStack;
    Stack unusedStack;
    ScopeStack scopeStack;
    AbstractSyntaxTreeNode *node;
    
    errors->currentLine = ONE;

    InitScopeStack(&scopeStack);
    InitStack(&semanticStack);
    InitStack(&unusedStack);
    EnterScope(&scopeStack);
    InitTypeSystem(scopeStack.symbolTables->info);

    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

    while (currentState && ~currentState->isAccepting & ACCEPTING_STATE_MASK)
    {
        currentState->isAccepting & REDUCING_STATE_MASK ? 
            currentState = Reduce(parser->pushdownMachine->stack, 
                                  ((Item*)currentState->lrItems->info)->rule, &scopeStack, &semanticStack , errors) : 
            Shift(parser->pushdownMachine->stack, currentState, &tokensPtr, &errors->currentLine, &semanticStack, &unusedStack);

        NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

        !currentState && ((Token*)tokensPtr->info)->type != EOD ? 
            PanicMode(parser, &semanticStack, &tokensPtr, errors) : ZERO;
    }

    ExitScope(&scopeStack);

    while (!IsEmptyStack(&unusedStack))
    {
        node = PopStack(&unusedStack);

        !node->GenerationFunction && !node->info && !((Symbol*)node->info)->type ?
            free(node) : ZERO;
    }

    return (PopStack(&semanticStack));
}

//-----------------------------------------------------------------------------
//                                      Free Parser                                     
//                                      -----                                  
//                                                                             
// General      : The function empties the underlying
//                pushdown machine of the parser.                                                           
//                                                                             
// Parameters   :                                                              
//       parser - The parser context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
void FreeParser(Parser *parser)
{
    EmptyPushdownMachine(parser->pushdownMachine);
}