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
    char name;
    LinearLinkedListNode *rules;
} NonTerminal;

typedef struct
{
    BOOL isTerminal;
    union
    {
        NonTerminal *nonTerminal;
        TokenType terminal;
    } value;
    void *node;
} Expression;

typedef struct
{
    LinearLinkedListNode *expressions;
    void(*semanticAction)();
} Rule;

typedef struct
{
    NonTerminal *nonTerminal;
    Rule *rule;
    LinearLinkedListNode *dotPosition;
    TokenType lookahead;
} Item;

typedef struct
{
    LinearLinkedListNode *nonTerminals;
} Grammar;