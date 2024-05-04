// Parser.c

#include "Parser.h"

#define REDUCING_STATE_MASK 0b01
#define ACCEPTING_STATE_MASK 0b10

static const char** _types;

BOOL CompareItems(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition &&
            first->rule == second->rule);
}

BOOL CompareItemKernels(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition &&
            first->rule == second->rule && first->lookahead == second->lookahead);
}

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
        isKernelItem &= ((Item*)ptr->info)->dotPosition != ((Item*)ptr->info)->rule->expressions;
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
        areEqual = CompareItems(firstStart->info, secondStart->info);

        firstStart = firstStart->nextNode;
        secondStart = secondStart->nextNode;
    }
    while (areEqual && firstStart != firstEnd && secondStart != secondEnd);

    return (areEqual);
}

BOOL CompareKernels(CircularLinearLinkedListNode *first, CircularLinearLinkedListNode *second)
{
    return CompareItems(first->nextNode->info, second->nextNode->info);
    return CompareItemsLists(first->nextNode, second->nextNode, first->nextNode->nextNode, second->nextNode->nextNode);
    return CompareItemsLists(first->nextNode, second->nextNode, KernelEnd(first), KernelEnd(second));
}

BOOL StatesComparator(PushdownState* first, CircularLinearLinkedListNode *second)
{
    return CompareKernels(first->lrItems, second);
}

unsigned int PointerKey(void *ptr)
{
    return (unsigned)ptr & sizeof(void*);
}

unsigned long ItemKey(Item *item)
{
    return (PointerKey(item->rule) + PointerKey(item->dotPosition) + item->lookahead->value.terminal);
}

CircularLinearLinkedListNode* Closure(CircularLinearLinkedListNode **items, Dictionary *firstSets)
{
    Item *currentItem;
    Stack closureStack;
    Dictionary visitedItems;
    NonTerminal *nextNonTerminal;
    CircularLinearLinkedListNode *itemsPtr = (*items)->nextNode;

    InitDictionary(&visitedItems);
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
            LinearLinkedListNode *ptf = currentItem->dotPosition->nextNode ?
                LookupFirstSet(firstSets, currentItem->dotPosition->nextNode->info) : 
                LookupFirstSet(firstSets, currentItem->lookahead);

            for (; ptf; ptf = ptf->nextNode)
            {
                temp = InitialItem(pRules->info, ptf->info);

                if (!LookupDictionary(&visitedItems, temp, ItemKey, CompareItemKernels))
                {
                    InsertDictionary(&visitedItems, temp, ItemKey);
                    InsertEndCircularLinearLinkedList(items);
                    (*items)->info = temp;
                    if (!((Expression*)temp->dotPosition->info)->isTerminal)
                    PushStack(&closureStack, (*items)->info);
                }
                else
                {
                    free(temp);
                }
            }
        }
    }

    EmptyDictionary(&visitedItems, NULL);

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
    unsigned long key = ZERO;

    CircularLinearLinkedListNode *startPtr = state->lrItems->nextNode;
    CircularLinearLinkedListNode *endPtr = KernelEnd(state->lrItems);

    do
    {
        key += ItemKey(startPtr->info);
        startPtr = startPtr->nextNode;
    }
    while (startPtr != endPtr);
    
    return (key);
}

void HandleNextItem(Item *item, LinearLinkedListNode **expressions)
{
    Expression *expression = item->dotPosition->info;
    CircularLinearLinkedListNode *nextStateItems;
    PushdownState *currentState;

    !expression->node ?
        MakeInitialGotoItem(item, expressions) : 
        InsertEndCircularLinearLinkedList(&expression->node);
    
    ((CircularLinearLinkedListNode*)expression->node)->info = NextItem(item);
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

    AddPushdownTransition(parser->pushdownMachine, currentState, reducingState, item->lookahead->value);
}

void MakeGotoState(PushdownMachine *machine, PushdownState *currentState, 
                   Expression *expression, Queue *nextStates, Dictionary *visitedStates)
{
    PushdownState *nextState;
    CircularLinearLinkedListNode *gotoItems = expression->node;

    if (!(nextState = LookupDictionary(visitedStates, gotoItems, KeyState, StatesComparator)))
    {
        nextState = AddPushdownState(machine);
        nextState->lrItems = gotoItems;
        InsertQueue(nextStates, nextState);
        InsertDictionary(visitedStates, nextState, KeyState);
    }
    else
    {
        EmptyCircularLinearLinkedList(&gotoItems, free);
    }

    AddPushdownTransition(machine, currentState, nextState, expression->value);

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
    Dictionary *firstSets = GrammarFirstSet(parser->grammar);
    PushdownState *currentState;
    Dictionary visited;
    Queue queue;

    InitDictionary(&visited);
    InitQueue(&queue);
    InsertLastCircularLinearLinkedList(&initialState->lrItems);
    initialState->lrItems->info = InitialItem(InitialRule(parser->grammar), EODTerminal(parser->grammar));

    InsertQueue(&queue, initialState);
    initialState->isAccepting = FALSE;

    while (!IsEmptyQueue(&queue))
    {
        currentState = RemoveQueue(&queue);

        Closure(&currentState->lrItems, firstSets);
        MakeGotoStates(parser, currentState, &queue, &visited);
    }

    FreeFirstSets(firstSets);
    EmptyDictionary(&visited, NULL);
}

void InitParser(Parser *parser, const char **types)
{
    _types = types;

    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);
    InitGrammar(parser->grammar);

    PrintGrammar(parser->grammar);

    BuildLRStates(parser);
}

void NextState(PushdownState **current, ExpressionValue expression, BOOL(*ComapreExpressions)(ExpressionValue, ExpressionValue))
{
    CircularLinearLinkedListNode *ptr = (*current)->transitionsManager;
    PushdownTransition *currentTransition;
    ExpressionValue symbol;

    PushdownState *next = NULL;

    do
    {
        currentTransition = ptr->info;

        ComapreExpressions(currentTransition->symbol, expression) ? 
            next = currentTransition->dest : 
            ZERO;

        ptr = ptr->nextNode;
    }
    while (ptr != (*current)->transitionsManager);

    *current = next;
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

    printf("  |%s]\n\t", _types[item->lookahead->value.terminal]);
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
    if (!root)
    {
        padding('\t', level);
        puts("~");
        return;
    }

    padding('\t', level);
    if (root->info)
    {
        printf("%s:%s\n", ((Symbol*)root->info)->name, _types[((Symbol*)root->info)->type]);
    }
    else
    {
        puts("Program");
    }

    for (LinearLinkedListNode *p = root->childrenManager; p; p = p->nextNode)
    {
        Traverse(p->info, level + 1);
    }
}

void Parse(Parser *parser, CircularLinearLinkedListNode *tokens)
{
    PushdownState *currentState = InitialPushdownState(parser->pushdownMachine);
    CircularLinearLinkedListNode *tokensPtr = tokens->nextNode;
    ScopeStack scopeStack;
    Stack semanticStack;

    InitStack(&semanticStack);
    InitScopeStack(&scopeStack);
    EnterScope(&scopeStack);
    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

    while (currentState && ~currentState->isAccepting & ACCEPTING_STATE_MASK)
    {
        currentState->isAccepting & REDUCING_STATE_MASK ? 
            currentState = Reduce(parser->pushdownMachine->stack, ((Item*)currentState->lrItems->info)->rule, &scopeStack, &semanticStack) : 
            Shift(parser->pushdownMachine->stack, currentState, &tokensPtr, &semanticStack);

        NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);
    }

    printf("\n\r");
    Traverse(semanticStack.topOfStack->info, 0);
    puts("");

    SymbolTable *t1 = scopeStack.symbolTables->info;

    printf("\n%p\n", LookupSymbol(&scopeStack, "c"));
    printf("\n%p\n", LookupSymbol(&scopeStack, "ptr"));

    ExitScope(&scopeStack);

    if (currentState)
    {
        puts("ACC");
    }
    else
    {
        printf("%s ", ((Token*)tokensPtr->info)->lexeme);
        puts("ERR");
    }
}

void FreeParser(Parser *parser)
{
    FreeGrammar(parser->grammar);
    EmptyPushdownMachine(parser->pushdownMachine);
}