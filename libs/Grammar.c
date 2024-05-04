// Grammar.c

#include "Grammar.h"

struct ExpressionFirstSet
{
    Expression *expression;
    LinearLinkedListNode *firstSet;
};

#include "../grammar/GrammarConstruction.c"

NonTerminal* InitialNonTerminal(Grammar *grammar)
{
    return (grammar->nonTerminals->info);
}

Rule* InitialRule(Grammar *grammar)
{
    return (InitialNonTerminal(grammar)->rules->info);
}

Expression* EODTerminal(Grammar *grammar)
{
    return (grammar->expressions->info);
}

BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.nonTerminal == second.nonTerminal);
}

BOOL CompareTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.terminal == second.terminal);
}

unsigned long ExpressionKey(Expression *expression)
{
    return ((unsigned long)expression);
}

BOOL CompareExpressions(Expression *first, Expression *second)
{
    return (first == second);
}

unsigned long ExpressionFirstSetKey(struct ExpressionFirstSet *expression)
{
    return ExpressionKey(expression->expression);
}

BOOL CompareExpressionsFirstSet(struct ExpressionFirstSet *first, Expression *second)
{
    return CompareExpressions(first->expression, second);
}

LinearLinkedListNode* TerminalFirstSet(Expression *terminal)
{
    LinearLinkedListNode *firstSet;

    InitLinearLinkedList(&firstSet);
    PushLinearLinkedList(&firstSet);

    firstSet->info = terminal;

    return (firstSet);
}

void CurrentFirst(NonTerminal *current, Stack *nextNonTerminals, Dictionary *visitedExpressions, LinearLinkedListNode **firstSet)
{
    Expression *currentExpression;
    LinearLinkedListNode *rulesPtr;

    for (rulesPtr = current->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
    {
        currentExpression = ((Rule*)rulesPtr->info)->expressions->info;

        if (!LookupDictionary(visitedExpressions, currentExpression, ExpressionKey, CompareExpressions))
        {
            InsertDictionary(visitedExpressions, currentExpression, ExpressionKey);

            currentExpression->isTerminal ?
                (PushLinearLinkedList(firstSet), (*firstSet)->info = currentExpression) :
                PushStack(nextNonTerminals, currentExpression->value.nonTerminal);
        }
    }
}

LinearLinkedListNode* NonTerminalFirstSet(NonTerminal *nonTerminal)
{
    Stack nonTerminalsStack;
    LinearLinkedListNode *firstSet;
    Dictionary visitedExpressions;
    Expression *currentExpression;

    InitStack(&nonTerminalsStack);
    InitLinearLinkedList(&firstSet);
    InitDictionary(&visitedExpressions);
    
    PushStack(&nonTerminalsStack, nonTerminal);

    while (!IsEmptyStack(&nonTerminalsStack))
    {
        CurrentFirst(PopStack(&nonTerminalsStack), &nonTerminalsStack, &visitedExpressions, &firstSet);
    }

    EmptyDictionary(&visitedExpressions, NULL);

    return (firstSet);
}

void ExpressionFirstSet(Expression *expression, Dictionary *expressionFirstSets)
{
    LinearLinkedListNode *firstSet = expression->isTerminal ? 
        TerminalFirstSet(expression) : NonTerminalFirstSet(expression->value.nonTerminal);

    struct ExpressionFirstSet *item = malloc(sizeof(struct ExpressionFirstSet));
    *item = (struct ExpressionFirstSet){.expression = expression, .firstSet = firstSet};

    InsertDictionary(expressionFirstSets, item, ExpressionFirstSetKey);
}

Dictionary* GrammarFirstSet(Grammar *grammar)
{
    LinearLinkedListNode *ptr;
    Dictionary *expressionFirstSets = malloc(sizeof(Dictionary)); 

    InitDictionary(expressionFirstSets);

    for (ptr = grammar->expressions; ptr; ptr = ptr->nextNode)
    {
        ExpressionFirstSet(ptr->info, expressionFirstSets);
    }

    return (expressionFirstSets);
}

LinearLinkedListNode *LookupFirstSet(Dictionary *firstSets, Expression *expression)
{
    return ((struct ExpressionFirstSet*)LookupDictionary(firstSets,expression, ExpressionKey, CompareExpressionsFirstSet))->firstSet;
}

Item* NextItem(Item *item)
{
    Item *next = malloc(sizeof(Item));

    next->rule = item->rule;
    next->lookahead = item->lookahead;
    next->dotPosition = item->dotPosition->nextNode;

    return (next);
}

Item* InitialItem(Rule *rule, Expression *lookahead)
{
    Item *item = malloc(sizeof(Item));

    item->rule = rule;
    item->dotPosition = rule->expressions;
    item->lookahead = lookahead;

    return (item);
}

void FreeFirstSet(struct ExpressionFirstSet *firstSet)
{
    EmptyLinearLinkedList(&firstSet->firstSet, NULL);
}

void FreeFirstSets(Dictionary *firstSets)
{
    EmptyDictionary(firstSets, FreeFirstSet);
    free(firstSets);
}

void FreeRule(Rule *rule)
{
    EmptyLinearLinkedList(&rule->expressions, NULL);
    free(rule);
}

void FreeNonTerminal(NonTerminal *nonTerminal)
{
    EmptyLinearLinkedList(&nonTerminal->rules, FreeRule);
    free(nonTerminal);
}

void FreeGrammar(Grammar *grammar)
{
    EmptyLinearLinkedList(&grammar->nonTerminals, FreeNonTerminal);
    EmptyLinearLinkedList(&grammar->expressions, free);
    free(grammar);
}