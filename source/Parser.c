// Parser.c

#include "Parser.h"

#define REDUCING_STATE_MASK 0b01
#define ACCEPTING_STATE_MASK 0b10

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
        printf("%c ", exp->value.nonTerminal->name);
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
        printf("%c ::= \n\r\t", current->name);

        for (p = current->rules; p; p = p->nextNode)
        {
            PrintRule(p->info);
        }

        printf("\r");
    }
}

void InitParser_1(Parser *parser, const char **types)
{
    #pragma region INIT
    
     _types = types;

    //InitLinearLinkedList(&parser->grammar->rulesManager);
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);

    // NonTerminals
    NonTerminal *S = malloc(sizeof(NonTerminal));
    NonTerminal *E = malloc(sizeof(NonTerminal));
    NonTerminal *B = malloc(sizeof(NonTerminal));

    S->name = 'A';
    E->name = 'E';
    B->name = 'B';

    S->visited = FALSE;
    E->visited = FALSE;
    B->visited = FALSE;

    NonTerminal *nonTerminals[] = {S, E, B};

    // Expression
    Expression *integerLiteralExpression = malloc(sizeof(Expression));
    integerLiteralExpression->isTerminal = TRUE;
    integerLiteralExpression->value.terminal = INTEGER_LITERAL;
    integerLiteralExpression->visited = FALSE;
    integerLiteralExpression->node = NULL;

    Expression *floatLiteralExpression = malloc(sizeof(Expression));
    floatLiteralExpression->isTerminal = TRUE;
    floatLiteralExpression->value.terminal = FLOAT_LITERAL;
    floatLiteralExpression->visited = FALSE;
    floatLiteralExpression->node = NULL;

    Expression* plusExpression = malloc(sizeof(Expression));
    plusExpression->isTerminal = TRUE;
    plusExpression->value.terminal = PLUS;
    plusExpression->visited = FALSE;
    plusExpression->node = NULL;

    Expression* starExpression = malloc(sizeof(Expression));
    starExpression->isTerminal = TRUE;
    starExpression->value.terminal = STAR;
    starExpression->visited = FALSE;
    starExpression->node = NULL;

    Expression *EExpression = malloc(sizeof(Expression));
    EExpression->isTerminal = FALSE;
    EExpression->value.nonTerminal = E;
    EExpression->visited = FALSE;
    EExpression->node = NULL;

    Expression *BExpression = malloc(sizeof(Expression));
    BExpression->isTerminal = FALSE;
    BExpression->value.nonTerminal = B;
    BExpression->visited = FALSE;
    BExpression->node = NULL;

    // Rules
    Rule *tempr = malloc(sizeof(Rule));
    Rule *tempr1 = malloc(sizeof(Rule));

   // tempr->visited = FALSE;
    //tempr1->visited = FALSE;
    
    void* e[] = {integerLiteralExpression};
    void* d[] = {floatLiteralExpression};

    tempr->expressions = FromVector(e, 1);
    tempr1->expressions = FromVector(d, 1);

    void *e2[] = {tempr, tempr1};
    tempr->nonTerminal = B;
    tempr1->nonTerminal = B;
    B->rules = FromVector(e2, 2);

    tempr = malloc(sizeof(Rule));

   // tempr->visited = FALSE;

    void *ee[] = {BExpression};

    tempr->expressions = FromVector(ee, 1);

    Rule* tempr2 = malloc(sizeof(Rule));

    //tempr2->visited = FALSE;

    void *eee[] = {EExpression, plusExpression, BExpression};

    tempr2->expressions = FromVector(eee, 3);

    Rule *tempr3 = malloc(sizeof(Rule));
    void *ddd[] = {EExpression, starExpression, BExpression};

    //tempr3->visited = FALSE;

    tempr3->expressions = FromVector(ddd, 3);

    void *eeeee[] = {tempr3, tempr2, tempr};

    tempr3->nonTerminal = E;
    tempr2->nonTerminal = E;
    tempr->nonTerminal = E;
    E->rules = FromVector(eeeee, 3);

    tempr1 = malloc(sizeof(Rule));

    //tempr1->visited = FALSE;

    void* e1[] = {EExpression};
    tempr1->expressions = FromVector(e1, 1);

    void *e21[] = {tempr1};

    tempr1->nonTerminal = S;
    S->rules = FromVector(e21, 1);

    parser->grammar->nonTerminals = FromVector(nonTerminals, 3);

    PrintGrammar(parser->grammar);

    #pragma endregion
}
void InitParser_2(Parser *parser, const char **types)
{
    #pragma region INIT
    
    _types = types;

    //InitLinearLinkedList(&parser->grammar->rulesManager);
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);

    // The language c*dc*d
    //    c: >
    //    d: <
    NonTerminal *A = malloc(sizeof(NonTerminal));
    NonTerminal *S = malloc(sizeof(NonTerminal));
    NonTerminal *C = malloc(sizeof(NonTerminal));

    A->name = 'A';
    S->name = 'S';
    C->name = 'C';

    A->visited = FALSE;
    S->visited = FALSE;
    C->visited = FALSE;

    // A
    Rule *ruleA_1 = malloc(sizeof(Rule));
    ruleA_1->nonTerminal = A;
  //  ruleA_1->visited = FALSE;

    Expression *ruleA_1_E1 = malloc(sizeof(Expression));
    ruleA_1_E1->visited = FALSE;
    ruleA_1_E1->isTerminal = FALSE;
    ruleA_1_E1->value.nonTerminal = S;

    Expression *expressionsA1[] = {ruleA_1_E1};

    ruleA_1->expressions = FromVector(expressionsA1, 1);

    Rule *rulesA[] = {ruleA_1};

    A->rules = FromVector(rulesA, 1);

    // S
    Rule *ruleS_1 = malloc(sizeof(Rule));
    ruleS_1->nonTerminal = S;
   // ruleS_1->visited = FALSE;

    Expression *ruleS_1_E1 = malloc(sizeof(Expression));
    ruleS_1_E1->visited = FALSE;
    ruleS_1_E1->isTerminal = FALSE;
    ruleS_1_E1->value.nonTerminal = C;

    Expression *ruleS_1_E2 = malloc(sizeof(Expression));
    ruleS_1_E2->visited = FALSE;
    ruleS_1_E2->isTerminal = FALSE;
    ruleS_1_E2->value.nonTerminal = C;

    Expression *expressionsS1[] = {ruleS_1_E1, ruleS_1_E2};

    ruleS_1->expressions = FromVector(expressionsS1, 2);

    Rule *rulesS[] = {ruleS_1};

    S->rules = FromVector(rulesS, 1);

    // C
    Rule *ruleC_1 = malloc(sizeof(Rule));
    ruleC_1->nonTerminal = C;
    //ruleC_1->visited = FALSE;

    Expression *ruleC_1_E1 = malloc(sizeof(Expression));
    ruleC_1_E1->visited = FALSE;
    ruleC_1_E1->isTerminal = TRUE;
    ruleC_1_E1->value.terminal = GT;

    Expression *ruleC_1_E2 = malloc(sizeof(Expression));
    ruleC_1_E2->visited = FALSE;
    ruleC_1_E2->isTerminal = FALSE;
    ruleC_1_E2->value.nonTerminal = C;

    Expression *expressionsC1[] = {ruleC_1_E1, ruleC_1_E2};

    ruleC_1->expressions = FromVector(expressionsC1, 2);

    Rule *ruleC_2 = malloc(sizeof(Rule));
    ruleC_2->nonTerminal = C;
    //ruleC_2->visited = FALSE;

    Expression *ruleC_2_E1 = malloc(sizeof(Expression));
    ruleC_2_E1->visited = FALSE;
    ruleC_2_E1->isTerminal = TRUE;
    ruleC_2_E1->value.terminal = LT;

    Expression *expressionsC2[] = {ruleC_2_E1};

    ruleC_2->expressions = FromVector(expressionsC2, 1);

    Rule *rulesC[] = {ruleC_1, ruleC_2};

    C->rules = FromVector(rulesC, 2);

    NonTerminal* nonTerminals[] = {A, S, C};
    parser->grammar->nonTerminals = FromVector(nonTerminals, 3);

    PrintGrammar(parser->grammar);

    #pragma endregion
}
void InitParser_3(Parser *parser, const char **types)
{
    #pragma region INIT
    
    _types = types;

    //InitLinearLinkedList(&parser->grammar->rulesManager);
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);

    // The language c*dc*d
    //    c: >
    //    d: <
    NonTerminal *S = malloc(sizeof(NonTerminal));
    NonTerminal *A = malloc(sizeof(NonTerminal));
    NonTerminal *B = malloc(sizeof(NonTerminal));
    NonTerminal *C = malloc(sizeof(NonTerminal));

    // Expressions
    Expression *expS = malloc(sizeof(Expression));
    expS->visited = FALSE;
    expS->isTerminal = FALSE;
    expS->value.nonTerminal = S;

    Expression *expA = malloc(sizeof(Expression));
    expA->visited = FALSE;
    expA->isTerminal = FALSE;
    expA->value.nonTerminal = A;

    Expression *expB = malloc(sizeof(Expression));
    expB->visited = FALSE;
    expB->isTerminal = FALSE;
    expB->value.nonTerminal = B;

    Expression *expa = malloc(sizeof(Expression));
    expa->visited = FALSE;
    expa->isTerminal = TRUE;
    expa->value.terminal = IF;

    Expression *expb = malloc(sizeof(Expression));
    expb->visited = FALSE;
    expb->isTerminal = TRUE;
    expb->value.terminal = GT;

    Expression *expc = malloc(sizeof(Expression));
    expc->visited = FALSE;
    expc->isTerminal = TRUE;
    expc->value.terminal = LT;

    Expression *expd = malloc(sizeof(Expression));
    expd->visited = FALSE;
    expd->isTerminal = TRUE;
    expd->value.terminal = EQ;

    S->name = 'S';
    A->name = 'A';
    B->name = 'B';
    C->name = 'C';

    A->visited = FALSE;
    S->visited = FALSE;
    B->visited = FALSE;
    C->visited = FALSE;

    // C
    Rule *ruleC_1 = malloc(sizeof(Rule));
    ruleC_1->nonTerminal = C;

    Expression *expressionsC1[] = {expS};

    ruleC_1->expressions = FromVector(expressionsC1, 1);

    Rule *rulesC[] = {ruleC_1};

    C->rules = FromVector(rulesC, 1);

    // S
    Rule *ruleS_1 = malloc(sizeof(Rule));
    ruleS_1->nonTerminal = S;

    Expression *expressionsS1[] = {expA, expa};

    ruleS_1->expressions = FromVector(expressionsS1, 2);

    Rule *ruleS_2 = malloc(sizeof(Rule));
    ruleS_2->nonTerminal = S;

    Expression *expressionsS2[] = {expb, expA, expc};

    ruleS_2->expressions = FromVector(expressionsS2, 3);

    Rule *ruleS_3 = malloc(sizeof(Rule));
    ruleS_3->nonTerminal = S;

    Expression *expressionsS3[] = {expB, expc};

    ruleS_3->expressions = FromVector(expressionsS3, 2);

    Rule *ruleS_4 = malloc(sizeof(Rule));
    ruleS_4->nonTerminal = S;

    Expression *expressionsS4[] = {expb, expB, expa};

    ruleS_4->expressions = FromVector(expressionsS4, 3);

    Rule *rulesS[] = {ruleS_1, ruleS_2, ruleS_3, ruleS_4};
    S->rules = FromVector(rulesS, 4);

    // A
    Rule *ruleA_1 = malloc(sizeof(Rule));
    ruleA_1->nonTerminal = A;

    Expression *expressionsA1[] = {expd};

    ruleA_1->expressions = FromVector(expressionsA1, 1);

    Rule *rulesA[] = {ruleA_1};

    A->rules = FromVector(rulesA, 1);

    // B
    Rule *ruleB_1 = malloc(sizeof(Rule));
    ruleB_1->nonTerminal = B;

    Expression *expressionsB1[] = {expd};

    ruleB_1->expressions = FromVector(expressionsB1, 1);

    Rule *rulesB[] = {ruleB_1};

    B->rules = FromVector(rulesB, 1);

    NonTerminal* nonTerminals[] = {C, S, A, B};
    parser->grammar->nonTerminals = FromVector(nonTerminals, 4);

    PrintGrammar(parser->grammar);

    #pragma endregion
}

void InitParser(Parser *parser, const char **types)
{
    #pragma region INIT
    
    InitParser_1(parser, types);

    #pragma endregion

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

CircularLinearLinkedListNode* Closure(CircularLinearLinkedListNode **items)
{
    Item *current;
    Stack st;
    NonTerminal *next;
    CircularLinearLinkedListNode *p = (*items)->nextNode;

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
                LinearLinkedListNode *pf = FollowSet(current->dotPosition->nextNode, current->lookahead);
                LinearLinkedListNode *ptf = pf;
                if (current->rule->nonTerminal != ((Expression*)((Rule*)pRules->info)->expressions->info)->value.nonTerminal)
                {
                    for (; ptf; ptf = ptf->nextNode)
                    {
                        InsertEndCircularLinearLinkedList(items);
                        (*items)->info = InitialItem(pRules->info, ((Expression*)ptf->info)->value.terminal);
                        PushStack(&st, (*items)->info);
                    }
                }
                else
                {

                    for (; ptf; ptf = ptf->nextNode)
                    {
                        InsertEndCircularLinearLinkedList(items);
                        (*items)->info = InitialItem(pRules->info, ((Expression*)ptf->info)->value.terminal);
                    }
                }

                if (!current->dotPosition->nextNode) for (ptf = pf; ptf; ptf = ptf->nextNode)
                {
                    free(ptf->info);
                }

                EmptyLinearLinkedList(&pf);
            }
        }
    }

    CircularLinearLinkedListNode *ptr = *items;

    return (*items);

    // CircularLinearLinkedListNode *closure;
    // CircularLinearLinkedListNode *ptr = (*items)->nextNode;
    // CircularLinearLinkedListNode *original = (*items)->nextNode;
    // Expression *nextNonTerminal;
    // LinearLinkedListNode *rules;
    // Item *currentItem;
    // Item *newItem;

    // CircularLinearLinkedListNode *epsilonStates;
    // CircularLinearLinkedListNode *previousEpsilonStates;

    // InitCircularLinearLinkedList(&epsilonStates);

    // currentItem = ptr->info;

    // if (currentItem->dotPosition)
    // {
    // nextNonTerminal = currentItem->dotPosition->info;

    // if (!nextNonTerminal->isTerminal)
    //     for (rules = nextNonTerminal->value.nonTerminal->rules; rules; rules = rules->nextNode)
    //     {
    //         epsilonStates ?
    //             InsertEndCircularLinearLinkedList(&epsilonStates) : 
    //             InsertLastCircularLinearLinkedList(&epsilonStates);
    //         epsilonStates->info = newItem = malloc(sizeof(Item));
    //         //newItem->nonTerminal = nextNonTerminal->value.nonTerminal;
    //         newItem->rule = rules->info;
    //         newItem->dotPosition = newItem->rule->expressions;
    //     }
    // }
    // while (epsilonStates)
    // {
    //     previousEpsilonStates = epsilonStates->nextNode;
    //     ConcatCircularLinearLinkedLists(items, epsilonStates);
    //     epsilonStates = NULL;

    //     currentItem = previousEpsilonStates->info;
    //     nextNonTerminal = currentItem->dotPosition->info;

    //     if (!nextNonTerminal->isTerminal)
    //         for (rules = nextNonTerminal->value.nonTerminal->rules; rules; rules = rules->nextNode)
    //         {
    //             epsilonStates ?
    //                 InsertEndCircularLinearLinkedList(&epsilonStates) : 
    //                 InsertLastCircularLinearLinkedList(&epsilonStates);
    //             epsilonStates->info = newItem = malloc(sizeof(Item));
    //             //newItem->nonTerminal = nextNonTerminal->value.nonTerminal;
    //             newItem->rule = rules->info;
    //             newItem->dotPosition = newItem->rule->expressions;
    //         }
    // }

    // return (*items);

    // do
    // {
    //     currentItem = ptr->info;
    //     nextNonTerminal = currentItem->dotPosition->info;

    //     if (!nextNonTerminal->isTerminal)
    //         for (rules = nextNonTerminal->value.nonTerminal->rules; rules; rules = rules->nextNode)
    //         {
    //             InsertEndCircularLinearLinkedList(items);
    //             (*items)->info = newItem = malloc(sizeof(Item));
    //             newItem->nonTerminal = nextNonTerminal->value.nonTerminal;
    //             newItem->rule = rules->info;
    //             newItem->dotPosition = newItem->rule->expressions;
    //         }

    //     ptr = ptr->nextNode;
    // }
    // while (ptr != original);
}

CircularLinearLinkedListNode* Goto(CircularLinearLinkedListNode *items, Expression *expression)
{
    CircularLinearLinkedListNode *gotoItems;
    CircularLinearLinkedListNode *ptr = items->nextNode;

    InitCircularLinearLinkedList(&gotoItems);

    do
    {
        if (((Item*)ptr->info)->dotPosition && ((Item*)ptr->info)->dotPosition->info == expression)
        {
            gotoItems ? 
                InsertEndCircularLinearLinkedList(&gotoItems) : 
                InsertLastCircularLinearLinkedList(&gotoItems);

            gotoItems->info = NextItem(ptr->info);
        }

        ptr = ptr->nextNode;
    }
    while (ptr != items->nextNode);

    return (Closure(&gotoItems));
}

void PrintItem(Item *item)
{
    LinearLinkedListNode *p = item->rule->expressions;

    printf("[%c-> ", item->rule->nonTerminal->name);

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
    printf("Item #%d:\n\t", state->isAccepting);
    PrintItems(state->lrItems);
    printf("Transitions: [");

    CircularLinearLinkedListNode *tr = state->transitionsManager;
    
    if (tr) do
    {
        printf("%d:", ((PushdownTransition*)tr->info)->dest->isAccepting);

        if(((PushdownTransition*)tr->info)->symbol.terminal <= EOD)
        {
            printf("%s ", _types[((PushdownTransition*)tr->info)->symbol.terminal]);
        }
        else
        {
            printf("%c ", ((PushdownTransition*)tr->info)->symbol.nonTerminal->name);
        }

        //PrintExpression(((PushdownTransition*)tr->info)->symbol);
        printf(" ");
        tr = tr->nextNode;
    }
    while (tr != state->transitionsManager);

    puts("]");
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

PushdownState* Reduce(Stack *states, Rule *rule)
{
    LinearLinkedListNode *ptr;
    PushdownState *nextState;

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
        puts("ERR");
    }
}

void PrintFirst(LinearLinkedListNode *first)
{
    for (; first; first = first->nextNode)
    {
        printf("%s ", _types[((Expression*)first->info)->value.terminal]);
    }
}

BOOL CompareItem(Item *first, Item *second)
{
    return (first->dotPosition == second->dotPosition && first->rule == second->rule);
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

void HandleNextItem(Queue *nextStates, PushdownState *c, PushdownMachine *machine, Item *item)
{
    Expression *expression = item->dotPosition->info;
    PushdownState *currentState = expression->node;
    CircularLinearLinkedListNode *nextStateItems;
    Item *nextItem = NextItem(item);
    BOOL f = TRUE;

    if (!expression->node)
    {
        if (!CompareItem(nextItem, c->lrItems->nextNode->info))
        {
            expression->node = currentState = AddPushdownState(machine);
            currentState->isAccepting = 0;
            InsertLastCircularLinearLinkedList(&currentState->lrItems);
            InsertQueue(nextStates, currentState);
        }
        else
        {
            free(nextItem);
            expression->node = c;
            currentState = c;
            f = FALSE;
        }

        AddPushdownTransition(machine, c, currentState, expression->value);
    }
    else
    {
        InsertEndCircularLinearLinkedList(&currentState->lrItems);
    }

    if (f)
    currentState->lrItems->info = nextItem;
}

void HandleFinalItem(Parser *parser, PushdownState *currentState, Item *item)
{
    PushdownState *reducingState = AddPushdownState(parser->pushdownMachine);
    Item* reducingItem;
    
    InsertLastCircularLinearLinkedList(&reducingState->lrItems);
    
    reducingItem = reducingState->lrItems->info = malloc(sizeof(Item));
    reducingItem->rule = item->rule;
    reducingItem->lookahead = item->lookahead;

    reducingState->isAccepting |= (REDUCING_STATE_MASK | 
        (ACCEPTING_STATE_MASK & (item->rule->nonTerminal == InitialNonTerminal(parser->grammar)) << ONE));

    AddPushdownTransition(parser->pushdownMachine, currentState, reducingState, (ExpressionValue)item->lookahead);
}

void MakeGotoState(Parser *parser, PushdownState *currentState, Queue *gotoStates)
{
    CircularLinearLinkedListNode *ptr = currentState->lrItems->nextNode;

    do
    {
        ((Item*)ptr->info)->dotPosition ?
            ((Expression*)(((Item*)ptr->info)->dotPosition->info))->node = NULL : 
            ZERO;

        ptr = ptr->nextNode;
    }
    while (ptr != currentState->lrItems->nextNode);

    do
    {
        ((Item*)ptr->info)->dotPosition ?
            HandleNextItem(gotoStates, currentState, parser->pushdownMachine, ptr->info): 
            HandleFinalItem(parser, currentState, ptr->info);

        ptr = ptr->nextNode;
    }
    while (ptr != currentState->lrItems->nextNode);

    do
    {
        ((Item*)ptr->info)->dotPosition ?
            ((Expression*)(((Item*)ptr->info)->dotPosition->info))->node = NULL : 
            ZERO;

        ptr = ptr->nextNode;
    }
    while (ptr != currentState->lrItems->nextNode);
}

void BuildLRStates(Parser *parser)
{
    PushdownState* initialState = AddPushdownState(parser->pushdownMachine);
    PushdownState *currentState;
    Queue queue;

    InitQueue(&queue);
    InsertLastCircularLinearLinkedList(&initialState->lrItems);
    initialState->lrItems->info = InitialItem(((NonTerminal*)parser->grammar->nonTerminals->info)->rules->info, EOD);
    
    InsertQueue(&queue, initialState);
    initialState->isAccepting = 0;

    while (!IsEmptyQueue(&queue))
    {
        currentState = RemoveQueue(&queue);

        Closure(&currentState->lrItems);
        MakeGotoState(parser, currentState, &queue);

        // CircularLinearLinkedListNode *p = currentState->lrItems->nextNode;

        // do
        // {
        //     Item *current = p->info;

        //     if (current->dotPosition)
        //     {
        //         Expression* currente = current->dotPosition->info;
        //         CircularLinearLinkedListNode *_goto;

        //         if (!currente->visited)
        //         {
        //             currente->visited = TRUE;
        //             _goto = Goto(currentState->lrItems, currente);
        //             PushdownState *temp = currentState;

        //             //if (!CompareItem(_goto->nextNode->info, currentState->lrItems->nextNode->info))
        //             {
        //                 temp = AddPushdownState(parser->pushdownMachine);
        //                 temp->isAccepting = 0;
        //                 temp->lrItems = _goto;
        //                 InsertQueue(&queue, temp);
        //             }

        //             AddPushdownTransition(parser->pushdownMachine, currentState, temp, currente->value);
        //         } 
        //     }
        //     else
        //     {
        //         PushdownState *t = AddPushdownState(parser->pushdownMachine);
        //         InsertLastCircularLinearLinkedList(&t->lrItems);
        //         Item* tt = t->lrItems->info = malloc(sizeof(Item));
        //         tt->rule = current->rule;
        //         tt->lookahead = current->lookahead;

        //         t->isAccepting |= ((REDUCING_STATE_MASK) | 
        //                            (ACCEPTING_STATE_MASK & (current->rule->nonTerminal == InitialNonTerminal(parser->grammar)) << ONE));

        //         AddPushdownTransition(parser->pushdownMachine, currentState, t, (ExpressionValue)current->lookahead);
        //     }

        //     p = p->nextNode;
        // }
        // while (p != currentState->lrItems->nextNode);

        // do
        // {
        //     if ((Expression*)((Item*)p->info)->dotPosition)
        //     ((Expression*)((Item*)p->info)->dotPosition->info)->visited = FALSE;
        //     p =  p->nextNode;
        // }
        // while (p != currentState->lrItems->nextNode);
        CircularLinearLinkedListNode *p = currentState->lrItems;

        do
        {
            free(p->info);
            p =  p->nextNode;
        }
        while (p != currentState->lrItems);

        EmptyCircularLinearLinkedList(&currentState->lrItems);
    }

    //
    CircularLinearLinkedListNode *ps = parser->pushdownMachine->statesManager->nextNode;

    if (0) do
    {
        PrintState(ps->info);
        puts("");
        ps = ps->nextNode;
    }
    while (ps != parser->pushdownMachine->statesManager->nextNode);

    // //
    // for (LinearLinkedListNode *p = parser->grammar->nonTerminals; p; p = p->nextNode)
    // {
    //     printf("%c: [", ((NonTerminal*)p->info)->name);
    //     PrintFirst(FirstSet(p->info));
    //     puts("]");
    // }
}

void FreeParser(Parser *parser)
{
    FreeGrammar(parser->grammar);
    EmptyPushdownMachine(parser->pushdownMachine);
}