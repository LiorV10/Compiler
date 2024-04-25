// Grammar.h

#define _GRAMMAR_H

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _TOKEN_H
    #include "Token.h"
#endif

typedef struct
{
    BOOL visited;
    char name;
    LinearLinkedListNode *rules;
} NonTerminal;

typedef union
{
    NonTerminal *nonTerminal;
    TokenType terminal;
} ExpressionValue;

typedef struct
{
    BOOL visited;
    BOOL isTerminal;
    ExpressionValue value;
    void *node;
} Expression;

typedef struct
{
    NonTerminal *nonTerminal;
    LinearLinkedListNode *expressions;
    void(*semanticAction)();
} Rule;

typedef struct
{
    Rule *rule;
    LinearLinkedListNode *dotPosition;
    TokenType lookahead;
} Item;

typedef struct
{
    LinearLinkedListNode *nonTerminals;
} Grammar;

NonTerminal* InitialNonTerminal(Grammar *grammar);
BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second);
BOOL CompareTerminals(ExpressionValue first, ExpressionValue second);
void FreeGrammar(Grammar *grammar);