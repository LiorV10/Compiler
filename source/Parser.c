// Parser.c

#include "Parser.h"

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

/*
S -> E
E -> E + B | B
B -> int_lit
*/

Expression *integer_literal;

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

void InitParser(Parser *parser, const char **types)
{
    _types = types;

    //InitLinearLinkedList(&parser->grammar->rulesManager);
    parser->pushdownMachine = malloc(sizeof(PushdownMachine));
    parser->grammar = malloc(sizeof(Grammar));

    InitPushdownMachine(parser->pushdownMachine);

    // NonTerminals
    NonTerminal *S = malloc(sizeof(NonTerminal));
    NonTerminal *E = malloc(sizeof(NonTerminal));
    NonTerminal *B = malloc(sizeof(NonTerminal));

    S->name = 'S';
    E->name = 'E';
    B->name = 'B';

    NonTerminal *nonTerminals[] = {S, E, B};

    // Expression
    Expression *integerLiteralExpression = malloc(sizeof(Expression));
    integerLiteralExpression->isTerminal = TRUE;
    integerLiteralExpression->value.terminal = INTEGER_LITERAL;

    Expression* plusExpression = malloc(sizeof(Expression));
    plusExpression->isTerminal = TRUE;
    plusExpression->value.terminal = PLUS;

    Expression *EExpression = malloc(sizeof(Expression));
    EExpression->isTerminal = FALSE;
    EExpression->value.nonTerminal = E;

    Expression *BExpression = malloc(sizeof(Expression));
    BExpression->isTerminal = FALSE;
    BExpression->value.nonTerminal = B;

    integer_literal = BExpression;

    // Rules
    Rule *tempr = malloc(sizeof(Rule));
    
    void* e[] = {integerLiteralExpression};
    tempr->expressions = FromVector(e, 1);

    void *e2[] = {tempr};
    B->rules = FromVector(e2, 1);

    tempr = malloc(sizeof(Rule));

    void *ee[] = {BExpression};

    tempr->expressions = FromVector(ee, 1);

    Rule* tempr2 = malloc(sizeof(Rule));

    void *eee[] = {EExpression, plusExpression, BExpression};

    tempr2->expressions = FromVector(eee, 3);

    void *eeeee[] = {tempr, tempr2};

    E->rules = FromVector(eeeee, 2);

    Rule *tempr1 = malloc(sizeof(Rule));

    void* e1[] = {EExpression};
    tempr1->expressions = FromVector(e1, 1);

    void *e21[] = {tempr1};
    S->rules = FromVector(e21, 1);

    parser->grammar->nonTerminals = FromVector(nonTerminals, 3);

    PrintGrammar(parser->grammar);
}

void Closure(CircularLinearLinkedListNode **items)
{
    CircularLinearLinkedListNode *closure;
    CircularLinearLinkedListNode *ptr = (*items)->nextNode;
    CircularLinearLinkedListNode *original = (*items)->nextNode;
    Expression *nextNonTerminal;
    LinearLinkedListNode *rules;
    Item *currentItem;
    Item *newItem;

    CircularLinearLinkedListNode *epsilonStates;
    CircularLinearLinkedListNode *previousEpsilonStates;

    InitCircularLinearLinkedList(&epsilonStates);

    currentItem = ptr->info;
        nextNonTerminal = currentItem->dotPosition->info;

        if (!nextNonTerminal->isTerminal)
            for (rules = nextNonTerminal->value.nonTerminal->rules; rules; rules = rules->nextNode)
            {
                epsilonStates ?
                    InsertEndCircularLinearLinkedList(&epsilonStates) : 
                    InsertLastCircularLinearLinkedList(&epsilonStates);
                epsilonStates->info = newItem = malloc(sizeof(Item));
                newItem->nonTerminal = nextNonTerminal->value.nonTerminal;
                newItem->rule = rules->info;
                newItem->dotPosition = newItem->rule->expressions;
            }

    while (epsilonStates)
    {
        previousEpsilonStates = epsilonStates->nextNode;
        ConcatCircularLinearLinkedLists(items, epsilonStates);
        epsilonStates = NULL;

        currentItem = previousEpsilonStates->info;
        nextNonTerminal = currentItem->dotPosition->info;

        if (!nextNonTerminal->isTerminal)
            for (rules = nextNonTerminal->value.nonTerminal->rules; rules; rules = rules->nextNode)
            {
                epsilonStates ?
                    InsertEndCircularLinearLinkedList(&epsilonStates) : 
                    InsertLastCircularLinearLinkedList(&epsilonStates);
                epsilonStates->info = newItem = malloc(sizeof(Item));
                newItem->nonTerminal = nextNonTerminal->value.nonTerminal;
                newItem->rule = rules->info;
                newItem->dotPosition = newItem->rule->expressions;
            }
    }

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

Item* NextItem(Item *item)
{
    Item *next = malloc(sizeof(Item));

    next->rule = item->rule;
    next->nonTerminal = item->nonTerminal;
    next->lookahead = item->lookahead;
    next->dotPosition = item->dotPosition->nextNode;

    return (next);
}

CircularLinearLinkedListNode* Goto(CircularLinearLinkedListNode **items, Expression *expression)
{
    CircularLinearLinkedListNode *gotoItems;
    CircularLinearLinkedListNode *ptr = (*items)->nextNode;

    InitCircularLinearLinkedList(&gotoItems);

    do
    {
        if (((Item*)ptr->info)->dotPosition->info == expression)
        {
            gotoItems ? 
                InsertEndCircularLinearLinkedList(&gotoItems) : 
                InsertLastCircularLinearLinkedList(&gotoItems);

            gotoItems->info = NextItem(ptr->info);
        }

        ptr = ptr->nextNode;
    }
    while (ptr != (*items)->nextNode);

    return (gotoItems);
}

void PrintItem(Item *item)
{
    LinearLinkedListNode *p = item->rule->expressions;

    printf("[%c-> ", item->nonTerminal->name);

    for (; p; p = p->nextNode)
    {
        if (p == item->dotPosition) printf("⋅");
        PrintExpression(p->info);
    }

    if (!item->dotPosition) printf("⋅");

    printf("]\n\r");
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
}

CircularLinearLinkedListNode* BuildLRStates(Grammar *grammar)
{
    CircularLinearLinkedListNode *states;
    //

    Item *temp = malloc(sizeof(Item));
    temp->nonTerminal = grammar->nonTerminals->info;
    temp->rule = temp->nonTerminal->rules->info;
    temp->dotPosition = temp->rule->expressions;

    InitCircularLinearLinkedList(&states);
    InsertLastCircularLinearLinkedList(&states);
    states->info = temp;

    Closure(&states);
    PrintItems(states);
    puts("\n\n");
    PrintItems(Goto(&states, integer_literal));
}