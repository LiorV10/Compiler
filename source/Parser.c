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
    //return CompareItemKernels(first->nextNode->info, second->nextNode->info);
    // return CompareItemsLists(first->nextNode, second->nextNode, first->nextNode, second->nextNode);
    return CompareItemsLists(first->nextNode, second->nextNode, KernelEnd(first), KernelEnd(second));
}

BOOL StatesComparator(PushdownState* first, Expression *second)
{
    // return first->key == second->nodeKey;
    return first->key == second->nodeKey && CompareKernels(first->lrItems, second->node);
}

unsigned long PointerKey(void *ptr)
{
    // return (unsigned long)ptr;

    return (unsigned long)ptr & sizeof(void*);
}

unsigned long ItemKey(Item *item)
{
    return (PointerKey(item->rule) + PointerKey(item->dotPosition) + item->lookahead);
}

CircularLinearLinkedListNode* Closure(CircularLinearLinkedListNode **items)
{
    Item *currentItem;
    Stack closureStack;
    NonTerminal *nextNonTerminal;
    CircularLinearLinkedListNode *itemsPtr = (*items)->nextNode;

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

        for (LinearLinkedListNode *pRules = nextNonTerminal->rules; pRules; pRules = pRules->nextNode)
        {
            Item *temp;

            unsigned long firstset = currentItem->dotPosition->nextNode ? 
                ((Expression*)currentItem->dotPosition->nextNode->info)->firstSet :
                ((unsigned long)ONE << currentItem->lookahead);

            TokenType terminal = ZERO;

            for (; firstset; firstset >>= ONE)
            {
                for (; ~firstset & ONE; firstset >>= ONE, terminal++);

                if (!BIT_TEST(((Rule*)pRules->info)->visited, terminal))
                {
                    temp = InitialItem(pRules->info, terminal);
                    BIT_SET(temp->rule->visited, terminal);
                    InsertEndCircularLinearLinkedList(items);
                    (*items)->info = temp;

                    if (!((Expression*)temp->dotPosition->info)->isTerminal)
                        PushStack(&closureStack, (*items)->info);
                }
                
                terminal++;
            }
        }
    }

    return (*items);   
}

void MakeInitialGotoItem(Item *item, LinearLinkedListNode **expressions)
{
    Expression *expression = item->dotPosition->info;

    PushLinearLinkedList(expressions);
    (*expressions)->info = expression;

    InitCircularLinearLinkedList(&expression->node);
    InsertLastCircularLinearLinkedList(&expression->node);
}

unsigned long KeyState(PushdownState *state)
{
    return state->key;
}

void HandleNextItem(Item *item, LinearLinkedListNode **expressions)
{
    Expression *expression = item->dotPosition->info;
    CircularLinearLinkedListNode *nextStateItems;
    PushdownState *currentState;
    Item *nextItem = NextItem(item);

    !expression->node ?
        MakeInitialGotoItem(item, expressions) : 
        InsertEndCircularLinearLinkedList(&expression->node);
    
    ((CircularLinearLinkedListNode*)expression->node)->info = nextItem;
    expression->nodeKey += ItemKey(nextItem);
}

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

PushdownTransition* NextState(PushdownState **current, ExpressionValue expression, BOOL(*ComapreExpressions)(ExpressionValue, ExpressionValue));

void MakeGotoState(PushdownMachine *machine, PushdownState *currentState, 
                   Expression *expression, Queue *nextStates, Dictionary *visitedStates)
{
    PushdownState *nextState;
    CircularLinearLinkedListNode *gotoItems = expression->node;
    // PushdownTransition *tr = NULL;
    nextState = currentState;

    // BOOL(*__ComapreExpressions)(ExpressionValue, ExpressionValue) = CompareTerminals;

    // !expression->isTerminal ? __ComapreExpressions = CompareNonTerminals : NULL;

    // if (nextState->transitionsManager)
    // {
        // tr = NextState(&nextState, expression->value, __ComapreExpressions);
    // }

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

    // if (!tr)
    AddPushdownTransition(machine, currentState, nextState, expression->value);
    // else
    // tr->dest = nextState;
}

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

void InitParser(Parser *parser, Grammar *grammar)
{
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = grammar;

    InitPushdownMachine(parser->pushdownMachine);

    // PrintGrammar(parser->grammar);

    BuildLRStates(parser);
}

PushdownTransition* NextState(PushdownState **current, ExpressionValue expression, BOOL(*ComapreExpressions)(ExpressionValue, ExpressionValue))
{
    CircularLinearLinkedListNode *ptr = (*current)->transitionsManager;
    PushdownTransition *currentTransition;
    ExpressionValue symbol;

    PushdownState *next = NULL;
    PushdownTransition *tr = NULL;

    do
    {
        currentTransition = ptr->info;

        ComapreExpressions(currentTransition->symbol, expression) ? 
            (next = currentTransition->dest, (tr = currentTransition)) : //(next = Prioritize(next, currentTransition->dest)) : 
            ZERO;

        ptr = ptr->nextNode;
    }
    while (ptr != (*current)->transitionsManager);

    *current = next;

    return tr;
    //*current = LookupTransition(*current, expression)->dest;
}

void _NextToken(CircularLinearLinkedListNode **tokensPtr, unsigned int *currentLine)
{
    (*tokensPtr) = (*tokensPtr)->nextNode;

    while (((Token*)(*tokensPtr)->info)->type == WHITESPACE)
    {
        (*currentLine)++;
        (*tokensPtr) = (*tokensPtr)->nextNode;
    }
}

void Shift(Stack *states, PushdownState *state, CircularLinearLinkedListNode **tokenPtr, unsigned int *currentLine,
           Stack *semanticStack, Stack *unusedNodes)
{
    AbstractSyntaxTreeNode *astNode;

    PushStack(states, state);

    MakeAbstractSyntaxTree(&astNode);
    PushStack(semanticStack, astNode);
    PushStack(unusedNodes, astNode);
    astNode->info = (*tokenPtr)->info;

    _NextToken(tokenPtr, currentLine);
    //*tokenPtr = (*tokenPtr)->nextNode;
}

PushdownState* Reduce(Stack *states, Rule *rule, ScopeStack *scopeStack, Stack *semanticStack)
{
    LinearLinkedListNode *ptr;
    PushdownState *nextState;

    // printf("Reduce by: %s -> ", rule->nonTerminal->name);
    // PrintRule(rule);

    rule->semanticAction = rule->semanticAction ? rule->semanticAction : DefaultSemanticAction;
    PushStack(semanticStack, rule->semanticAction(scopeStack, semanticStack));

    for (ptr = rule->expressions; ptr; ptr = ptr->nextNode)
    {
        PopStack(states);
    }

    PushStack(states, (nextState = PopStack(states)));
    NextState(&nextState, (ExpressionValue)rule->nonTerminal, CompareNonTerminals);
    PushStack(states, nextState);

    return (nextState);
}

PushdownState* sync(Stack *stack, CircularLinearLinkedListNode **tokens, void *a)
{
    CircularLinearLinkedListNode **t;

    while (((Token*)(*tokens)->info)->type != SEMI_COLON) *tokens = (*tokens)->nextNode;

    *tokens = (*tokens)->nextNode;

    t = tokens;

    while (!IsEmptyStack(stack))
    {
        PushdownState *state = PopStack(stack);
        PushdownState *temp = state;

        PopStack(a);

        NextState(&state, (ExpressionValue)((Token*)(*tokens)->info)->type, CompareTerminals);

        if (~state->isAccepting & REDUCING_STATE_MASK) { PushStack(stack, temp); return temp; }
    }
}

AbstractSyntaxTreeNode* Parse(Parser *parser, CircularLinearLinkedListNode *tokens, Stack *errors)
{
    PushdownState *currentState = InitialPushdownState(parser->pushdownMachine);
    CircularLinearLinkedListNode *tokensPtr = tokens->nextNode;
    Stack semanticStack;
    Stack unusedStack;
    ScopeStack scopeStack;
    Token *previousToken;
    unsigned int currentLine = ONE;

    BIT_VEC(syncingTokens, TOKENS_NUM);
    BIT_VEC_ZERO(syncingTokens, TOKENS_NUM);

    BIT_SET(syncingTokens, SEMI_COLON);
    BIT_SET(syncingTokens, LEFT_PAREN);
    BIT_SET(syncingTokens, LEFT_CURLY);
    BIT_SET(syncingTokens, LEFT_BRACKET);
    BIT_SET(syncingTokens, COMMA);

    InitScopeStack(&scopeStack);
    InitStack(&semanticStack);
    InitStack(&unusedStack);
    EnterScope(&scopeStack);
    InitTypeSystem(scopeStack.symbolTables->info);

    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

    while (currentState && ~currentState->isAccepting & ACCEPTING_STATE_MASK)
    {
        previousToken = tokensPtr->info;

        currentState->isAccepting & REDUCING_STATE_MASK ? 
            currentState = Reduce(parser->pushdownMachine->stack, ((Item*)currentState->lrItems->info)->rule, &scopeStack, &semanticStack) : 
            Shift(parser->pushdownMachine->stack, currentState, &tokensPtr, &currentLine, &semanticStack, &unusedStack);

        NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

        if (!currentState && ((Token*)tokensPtr->info)->type != EOD)
        {
            PushStack(errors, MakeError("Unexcpected token: %s`%s`%s", currentLine, 
                previousToken->lexeme, ((Token*)tokensPtr->info)->lexeme, ((Token*)tokensPtr->nextNode->info)->lexeme));

            while (!BIT_TEST(syncingTokens, ((Token*)tokensPtr->info)->type)) _NextToken(&tokensPtr, &currentLine);
            
            _NextToken(&tokensPtr, &currentLine);

            while (!IsEmptyStack(parser->pushdownMachine->stack))
            {
                PushdownState *ts;
                currentState = PopStack(parser->pushdownMachine->stack);

                ts = currentState;
                NextState(&ts, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

                if (ts) break;

                PopStack(&semanticStack);
            }

            PushStack(parser->pushdownMachine->stack, currentState);
            NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);
        }
    }

    ExitScope(&scopeStack);

    AbstractSyntaxTreeNode *finalAst = PopStack(&semanticStack);

    while (!IsEmptyStack(&unusedStack))
    {
        AbstractSyntaxTreeNode *node = PopStack(&unusedStack);

        if (!node->GenerationFunction && !node->type && !((Symbol*)node->info)->_type && !node->childrenManager)
        {
            free(node);
        }
    }

    return finalAst;
}

void FreeParser(Parser *parser)
{
    // FreeGrammar(parser->grammar);
    EmptyPushdownMachine(parser->pushdownMachine);
}