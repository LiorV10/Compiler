// Grammar.c

#include "Grammar.h"

void InitGrammar(Grammar *grammar)
{
    InitLinearLinkedList(&grammar->nonTerminals);
    InitLinearLinkedList(&grammar->expressions);

    #include "../grammar/GrammarConstruction.c"
}

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