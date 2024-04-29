// Parser.c

#include "Parser.h"

#define REDUCING_STATE_MASK 0b01
#define ACCEPTING_STATE_MASK 0b10

BOOL CompareItems(Item *first, Item *second);

#pragma region Not In Use

BOOL CompareItem(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition && first->rule == second->rule && first->lookahead == second->lookahead);
}
BOOL Compare(CircularLinearLinkedListNode *first, CircularLinearLinkedListNode *second)
{
    CircularLinearLinkedListNode *f = first;
    CircularLinearLinkedListNode *s = second;

    Item *ff;
    Item *ss;

    do
    {
        ff = f->info;
        ss = s->info;

        if (!CompareItem(ff, ss))
        {
            return FALSE;
        }

        f = f->nextNode;
        s = s->nextNode;
    }
    while (f != first && s != second);

    return (f == first && s == second);
}

#pragma endregion

static const char** _types;

LinearLinkedListNode *FromVector(void *arr[], unsigned short size)
{
    LinearLinkedListNode *lst;

    InitLinearLinkedList(&lst);
    
    for(; size; )
    {
        PushLinearLinkedList(&lst);
        lst->info = arr[--size];
    }

    return (lst);
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

Item* NextItem(Item *item)
{
    Item *next = malloc(sizeof(Item));

    next->rule = item->rule;
    next->lookahead = item->lookahead;
    next->dotPosition = item->dotPosition->nextNode;

    return (next);
}

Item* InitialItem(Rule *rule, TokenType lookahead)
{
    Item *item = malloc(sizeof(Item));

    item->rule = rule;
    item->dotPosition = rule->expressions;
    item->lookahead = lookahead;

    return (item);
}

LinearLinkedListNode *FirstSet(NonTerminal *nonTerminal)
{
    Stack st;
    Stack _st;
    LinearLinkedListNode *result;
    NonTerminal *current;

    InitLinearLinkedList(&result);
    InitStack(&st);
    InitStack(&_st);

    PushStack(&st, nonTerminal);

    while (!IsEmptyStack(&st))
    {
        current = PopStack(&st);

        for (LinearLinkedListNode *p = current->rules; p; p = p->nextNode)
        {
            if (!((Expression*)((Rule*)p->info)->expressions->info)->visited)
            {
                ((Expression*)((Rule*)p->info)->expressions->info)->visited = TRUE;
                PushStack(&_st, ((Expression*)((Rule*)p->info)->expressions->info));
                !((Expression*)((Rule*)p->info)->expressions->info)->isTerminal ? 
                    PushStack(&st, ((Expression*)((Rule*)p->info)->expressions->info)->value.nonTerminal) : 
                    ((PushLinearLinkedList(&result)), (result->info = ((Rule*)p->info)->expressions->info));
            }
        }
    }

    while (!IsEmptyStack(&_st))
    {
        ((Expression*)PopStack(&_st))->visited = FALSE;
    }

    return (result);
    
}

LinearLinkedListNode* FollowSet(LinearLinkedListNode *dotPosition, TokenType lookahead)
{
    LinearLinkedListNode *result;
    Expression *exp;

    InitLinearLinkedList(&result);

    if (!dotPosition)
    {
        PushLinearLinkedList(&result);
        Expression *none = malloc(sizeof(Expression));
        none->isTerminal = TRUE;
        none->value.terminal = lookahead;
        none->visited = FALSE;
        result->info = none;
    }
    else
    {
        exp = dotPosition->info;

        if (exp->isTerminal)
        {
            PushLinearLinkedList(&result);
            result->info = exp;
        }
        else
        {
            result = FirstSet(exp->value.nonTerminal);
        }
    }

    return (result);
}   

CircularLinearLinkedListNode *KernelEnd(CircularLinearLinkedListNode *lrItems)
{
    CircularLinearLinkedListNode *ptr = lrItems->nextNode;
    CircularLinearLinkedListNode *ptr2;
    BOOL f = TRUE;

    do
    {
        f &= ((Item*)ptr->info)->dotPosition != ((Item*)ptr->info)->rule->expressions;
        ptr2 = ptr;
        ptr = ptr->nextNode;
    }
    while (ptr != lrItems->nextNode && f);

    return (ptr2);
}

BOOL CompareStates2(PushdownState* first, CircularLinearLinkedListNode *second)
{
    CircularLinearLinkedListNode *p2 = first->lrItems->nextNode;
    CircularLinearLinkedListNode *p1 = second->nextNode;

    CircularLinearLinkedListNode *e1 = KernelEnd(p1);
    CircularLinearLinkedListNode *e2 = KernelEnd(p2);

    BOOL f = TRUE;

    do
    {
        f &= CompareItems(p1->info, p2->info);

        p1 = p1->nextNode;
        p2 = p2->nextNode;
    }
    while (p1 != e1 && p2 != e2 && f);

    return f;
}

unsigned long Key(Item *item)
{
    return (unsigned long)((long)item->rule + (long)item->dotPosition + item->lookahead);
}

BOOL CompareItems(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition &&
            first->lookahead == second->lookahead &&
            first->rule == second->rule);
}

CircularLinearLinkedListNode* Closure(CircularLinearLinkedListNode **items)
{
    Item *current;
    Stack st;
    NonTerminal *next;
    CircularLinearLinkedListNode *p = (*items)->nextNode;
    LinearLinkedListNode *allItems = NULL;
    Dictionary visited;

    InitDictionary(&visited);
    InitStack(&st);

    do
    {
        PushStack(&st, p->info);
        p = p->nextNode;
    }
    while (p != (*items)->nextNode);

    while (!IsEmptyStack(&st))
    {
        current = PopStack(&st);

        if (current->dotPosition && !((Expression*)current->dotPosition->info)->isTerminal)
        {
            next = ((Expression*)current->dotPosition->info)->value.nonTerminal;

            for (LinearLinkedListNode *pRules = next->rules; pRules; pRules = pRules->nextNode)
            {
                Item *temp;
                LinearLinkedListNode *pf = FollowSet(current->dotPosition->nextNode, current->lookahead);
                LinearLinkedListNode *ptf = pf;

                for (; ptf; ptf = ptf->nextNode)
                {
                    temp = InitialItem(pRules->info, ((Expression*)ptf->info)->value.terminal);

                    if (!LookupDictionary(&visited, temp, Key, CompareItems))
                    {
                        InsertDictionary(&visited, temp, Key);
                        InsertEndCircularLinearLinkedList(items);
                        (*items)->info = temp;
                        PushStack(&st, (*items)->info);
                    }
                    else
                    {
                        free(temp);
                    }
                }

                if (!current->dotPosition->nextNode) for (ptf = pf; ptf; ptf = ptf->nextNode)
                {
                    free(ptf->info);
                }

                EmptyLinearLinkedList(&pf, NULL);
            }
        }
    }

    EmptyDictionary(&visited, NULL);
    CircularLinearLinkedListNode *ptr = *items;

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

    CircularLinearLinkedListNode *e = KernelEnd(state->lrItems);
    CircularLinearLinkedListNode *s = state->lrItems;

    do
    {
        key += Key(s->info);
        s = s->nextNode;
    }
    while (s != state->lrItems);
    
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

    AddPushdownTransition(parser->pushdownMachine, currentState, reducingState, (ExpressionValue)item->lookahead);
}

void MakeGotoState(PushdownMachine *machine, PushdownState *currentState, 
                   Expression *expression, Queue *nextStates, Dictionary *visitedStates)
{
    PushdownState *nextState;
    CircularLinearLinkedListNode *gotoItems = expression->node;

    if (!(nextState = LookupDictionary(visitedStates, gotoItems, KeyState, CompareStates2)))
    {
        nextState = AddPushdownState(machine);
        nextState->isAccepting = FALSE;
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

void f(PushdownState *state)
{
    //EmptyCircularLinearLinkedList(&state->lrItems, free);
}

void BuildLRStates(Parser *parser)
{
    PushdownState* initialState = AddPushdownState(parser->pushdownMachine);
    PushdownState *currentState;
    Queue queue;
    Dictionary visited;

    InitDictionary(&visited);
    InitQueue(&queue);
    InsertLastCircularLinearLinkedList(&initialState->lrItems);
    initialState->lrItems->info = InitialItem(InitialNonTerminal(parser->grammar)->rules->info, EOD);

    InsertQueue(&queue, initialState);
    initialState->isAccepting = FALSE;

    while (!IsEmptyQueue(&queue))
    {
        currentState = RemoveQueue(&queue);

        Closure(&currentState->lrItems);
        MakeGotoStates(parser, currentState, &queue, &visited);
    }

    EmptyDictionary(&visited, f);
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

void Shift(Stack *states, PushdownState *state, CircularLinearLinkedListNode **tokenPtr)
{
    PushStack(states, state);
    *tokenPtr = (*tokenPtr)->nextNode;
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

PushdownState* Reduce(Stack *states, Rule *rule)
{
    LinearLinkedListNode *ptr;
    PushdownState *nextState;

    //printf("Reduce by: %s -> ", rule->nonTerminal->name);
    //PrintRule(rule);

    for (ptr = rule->expressions; ptr; ptr = ptr->nextNode)
    {
        PopStack(states);
    }

    PushStack(states, (nextState = PopStack(states)));
    NextState(&nextState, (ExpressionValue)rule->nonTerminal, CompareNonTerminals);
    PushStack(states, nextState);

    return (nextState);
}

void Parse(Parser *parser, CircularLinearLinkedListNode *tokens)
{
    PushdownState *currentState = InitialPushdownState(parser->pushdownMachine);
    CircularLinearLinkedListNode *tokensPtr = tokens->nextNode;

    PushStack(parser->pushdownMachine->stack, currentState);
    NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);

    while (currentState && ~currentState->isAccepting & ACCEPTING_STATE_MASK)
    {
        currentState->isAccepting & REDUCING_STATE_MASK ? 
            currentState = Reduce(parser->pushdownMachine->stack, ((Item*)currentState->lrItems->info)->rule) : 
            Shift(parser->pushdownMachine->stack, currentState, &tokensPtr);

        NextState(&currentState, (ExpressionValue)((Token*)tokensPtr->info)->type, CompareTerminals);
    }

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