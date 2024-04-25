// Grammar.c

#include "Grammar.h"

NonTerminal* InitialNonTerminal(Grammar *grammar)
{
    return (grammar->nonTerminals->info);
}

BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.nonTerminal == second.nonTerminal);
}

BOOL CompareTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.terminal == second.terminal);
}

void FreeRule(Rule *rule, LinearLinkedListNode **uniqueExpressions)
{
    LinearLinkedListNode *ptr = rule->expressions;

    for (; ptr; ptr = ptr->nextNode)
    {
        if (!((Expression*)ptr->info)->visited)
        {
            PushLinearLinkedList(uniqueExpressions);
            (*uniqueExpressions)->info = ptr->info;
            ((Expression*)ptr->info)->visited = TRUE;
        }
    }

    EmptyLinearLinkedList(&rule->expressions);
    free(rule);
}

void FreeNonTerminal(NonTerminal *nonTerminal, LinearLinkedListNode **uniqueExpressions)
{
    LinearLinkedListNode *ptr = nonTerminal->rules;

    for (; ptr; ptr = ptr->nextNode)
    {
        FreeRule(ptr->info, uniqueExpressions);
    }

    EmptyLinearLinkedList(&nonTerminal->rules);
    free(nonTerminal);
}

void FreeGrammar(Grammar *grammar)
{
    LinearLinkedListNode *ptr = grammar->nonTerminals;
    LinearLinkedListNode *expressions;

    InitLinearLinkedList(&expressions);

    for (; ptr; ptr = ptr->nextNode)
    {
        FreeNonTerminal(ptr->info, &expressions);
    }

    for (ptr = expressions; ptr; ptr = ptr->nextNode)
    {
        free(ptr->info);
    }

    EmptyLinearLinkedList(&expressions);
    EmptyLinearLinkedList(&grammar->nonTerminals);
    free(grammar);
}