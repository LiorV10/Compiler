// Parser.c

#include "Parser.h"

#define REDUCING_STATE_MASK 0b01
#define ACCEPTING_STATE_MASK 0b10

static const char** _types;

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

void PrintExpression(Expression *exp)
{
    if (exp->isTerminal)
        printf("%s ", _types[exp->value.terminal]);
    else
        printf("%s ", exp->value.nonTerminal->name);
}

void PrintRule(Rule *rule)
{
    LinearLinkedListNode *p = rule->expressions;

    for (; p; p = p->nextNode)
    {
        PrintExpression(p->info);
    }

    printf("\n\r\t");
}

void PrintGrammar(Grammar *grammar)
{
    LinearLinkedListNode *ptr = grammar->nonTerminals;
    LinearLinkedListNode *p;
    NonTerminal *current;

    for (; ptr; ptr = ptr->nextNode)
    {
        current = ptr->info;
        printf("%s ::= \n\r\t", current->name);

        for (p = current->rules; p; p = p->nextNode)
        {
            PrintRule(p->info);
        }

        printf("\r");
    }
}

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
    // return CompareItemKernels(first->nextNode->info, second->nextNode->info);
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
    return (PointerKey(item->rule) + PointerKey(item->dotPosition) + item->lookahead - ONE);
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
                if (firstset & ONE)
                {
                    if (!BIT_TEST(((Rule*)pRules->info)->visited, terminal))
                    //   if ((~((Rule*)pRules->info)->visited & ((unsigned long)ONE << terminal)))
                    {
                        temp = InitialItem(pRules->info, terminal);
                        BIT_SET(temp->rule->visited, terminal);
                        //temp->rule->visited |= ((unsigned long)ONE << terminal);
                        InsertEndCircularLinearLinkedList(items);
                        (*items)->info = temp;

                        if (!((Expression*)temp->dotPosition->info)->isTerminal)
                            PushStack(&closureStack, (*items)->info);
                    }
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
    PushdownTransition *tr = NULL;
    nextState = currentState;

    BOOL(*__ComapreExpressions)(ExpressionValue, ExpressionValue) = CompareTerminals;

    !expression->isTerminal ? __ComapreExpressions = CompareNonTerminals : NULL;

    if (nextState->transitionsManager)
    {
        tr = NextState(&nextState, expression->value, __ComapreExpressions);
    }

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

    if (!tr)
    AddPushdownTransition(machine, currentState, nextState, expression->value);
    else
    tr->dest = nextState;
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

void PrintFirst(LinearLinkedListNode *first)
{
    for (; first; first = first->nextNode)
    {
        printf("%s ", _types[((Expression*)first->info)->value.terminal]);
    }

    puts("\n");
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

        for (LinearLinkedListNode *p = parser->grammar->nonTerminals; p; p = p->nextNode)
        {
            for (LinearLinkedListNode *rp = ((NonTerminal*)p->info)->rules; rp; rp = rp->nextNode)
            {
                BIT_VEC_ZERO(((Rule*)rp->info)->visited, TOKENS_NUM);
                // ((Rule*)rp->info)->visited = FALSE;
            }
        }

        Closure(&currentState->lrItems);

        for (LinearLinkedListNode *p = parser->grammar->nonTerminals; p; p = p->nextNode)
        {
            for (LinearLinkedListNode *rp = ((NonTerminal*)p->info)->rules; rp; rp = rp->nextNode)
            {
                BIT_VEC_ZERO(((Rule*)rp->info)->visited, TOKENS_NUM);
                // ((Rule*)rp->info)->visited = FALSE;
            }
        }

        MakeGotoStates(parser, currentState, &queue, &visitedStates);
    }

    EmptyDictionary(&visitedStates, NULL);
}

void InitParser(Parser *parser, const char **types)
{
    _types = types;

    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);
    InitGrammar(parser->grammar);

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

void PrintItem(Item *item)
{
    LinearLinkedListNode *p = item->rule->expressions;

    printf("[%s-> ", item->rule->nonTerminal->name);

    for (; p; p = p->nextNode)
    {
        if (p == item->dotPosition) printf("•");
        PrintExpression(p->info);
    }

    if (!item->dotPosition) printf("•");

    printf("  |%s]\n\t", _types[item->lookahead]);
}

void PrintItems(CircularLinearLinkedListNode *items)
{
    CircularLinearLinkedListNode *p = items->nextNode;

    do
    {
        PrintItem(p->info);
        p = p->nextNode;
    }
    while (p != items->nextNode);

    puts("");
}

void PrintState(PushdownState *state)
{
    printf("Item #%p:\n\t", state);
    PrintItems(state->lrItems);
    printf("Transitions: [");

    CircularLinearLinkedListNode *tr = state->transitionsManager;
    
    if (tr) do
    {
        printf("%p:", ((PushdownTransition*)tr->info)->dest);

        if(((PushdownTransition*)tr->info)->symbol.terminal <= EOD)
        {
            printf("%s ", _types[((PushdownTransition*)tr->info)->symbol.terminal]);
        }
        else
        {
            printf("%s ", ((PushdownTransition*)tr->info)->symbol.nonTerminal->name);
        }

        //PrintExpression(((PushdownTransition*)tr->info)->symbol);
        printf(" ");
        tr = tr->nextNode;
    }
    while (tr != state->transitionsManager);

    puts("]");
}

void Shift(Stack *states, PushdownState *state, CircularLinearLinkedListNode **tokenPtr, Stack *semanticStack)
{
    AbstractSyntaxTreeNode *astNode;

    PushStack(states, state);

    MakeAbstractSyntaxTree(&astNode);
    PushStack(semanticStack, astNode);
    astNode->info = (*tokenPtr)->info;

    *tokenPtr = (*tokenPtr)->nextNode;
}

PushdownState* Reduce(Stack *states, Rule *rule, ScopeStack *scopeStack, Stack *semanticStack)
{
    LinearLinkedListNode *ptr;
    PushdownState *nextState;

    printf("Reduce by: %s -> ", rule->nonTerminal->name);
    PrintRule(rule);

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

void padding ( char ch, int n )
{
  int i;

  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void Traverse(AbstractSyntaxTreeNode *root, int level)
{
    // return;

    if (!root)
    {
        padding('\t', level);
        puts("~");
        return;
    }

    padding('\t', level);

    if (root->info)
    {
        if (root->info == (void*)(1))
        {
            puts("Return");
            // AbstractSyntaxTreeNode *returnValue = root->childrenManager->info;
            // printf("mov $%s, %%eax\n", ((Token*)returnValue->info)->lexeme);
        }
        else
        {
            printf("%s:%s\n", ((Symbol*)root->info)->name, _types[((Symbol*)root->info)->type]);
        }
    }
    else
    {
        printf("Program:%p\n", root->GenerationFunction);
    }

    if (root->childrenManager) 
    {
        CircularLinearLinkedListNode *p = root->childrenManager->nextNode;

        do
        {
            Traverse(p->info, level + 1);
            p = p->nextNode;
        }
        while (p != root->childrenManager->nextNode);
    }

    // for (LinearLinkedListNode *p = root->childrenManager; p; p = p->nextNode)
    // {
    //     Traverse(p->info, level + 1);
    // }
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

AbstractSyntaxTreeNode* Parse(Parser *parser, CircularLinearLinkedListNode *tokens)
{
    PushdownState *currentState = InitialPushdownState(parser->pushdownMachine);
    CircularLinearLinkedListNode *tokensPtr = tokens->nextNode;
    Stack semanticStack;
    ScopeStack scopeStack;

    InitScopeStack(&scopeStack);
    InitStack(&semanticStack);
    EnterScope(&scopeStack);

    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

    while (currentState && ~currentState->isAccepting & ACCEPTING_STATE_MASK)
    {
        if (((Token*)tokensPtr->info)->type == PLUS)
        {
            int x = 0;
        }

        currentState->isAccepting & REDUCING_STATE_MASK ? 
            currentState = Reduce(parser->pushdownMachine->stack, ((Item*)currentState->lrItems->info)->rule, &scopeStack, &semanticStack) : 
            Shift(parser->pushdownMachine->stack, currentState, &tokensPtr, &semanticStack);
        
        NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

        if (!currentState && ((Token*)tokensPtr->info)->type != EOD)
        {
            printf("Unexcpected token '%s'\n", ((Token*)tokensPtr->info)->lexeme);

            while (((Token*)tokensPtr->info)->type != SEMI_COLON) tokensPtr = tokensPtr->nextNode;
            void *temp = tokensPtr;
            tokensPtr = tokensPtr->nextNode;

            // PopStack(parser->pushdownMachine->stack);
            // PopStack(&semanticStack);

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
            // currentState = sync(parser->pushdownMachine->stack, &tokensPtr, &semanticStack);
            // NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);
        }
    }

    AbstractSyntaxTreeNode *res;

    if (currentState)
    {
        Traverse((res = PopStack(&semanticStack)), ZERO);
        ExitScope(&scopeStack);
    }
    else
    {
        printf("Unexcpected token '%s'\n", ((Token*)tokensPtr->info)->lexeme);
    }

    return res;
}

void FreeParser(Parser *parser)
{
    FreeGrammar(parser->grammar);
    EmptyPushdownMachine(parser->pushdownMachine);
}