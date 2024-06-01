// Grammar.h

#define _GRAMMAR_H

typedef unsigned short TokenType;

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _ABSTRACT_SYNTAX_TREE_H
    #include "AbstractSyntaxTree.h"
#endif

typedef struct
{
    char *name;
    LinearLinkedListNode *rules;
} NonTerminal;

typedef union
{
    NonTerminal *nonTerminal;
    TokenType terminal;
} ExpressionValue;

typedef struct
{
    BOOL isTerminal;
    ExpressionValue value;
    void *node;
    unsigned long nodeKey;
    unsigned long firstSet;
} Expression;

typedef struct
{
    int id;
    unsigned long visited_;
    BIT_VEC(visited, 51);
    NonTerminal *nonTerminal;
    LinearLinkedListNode *expressions;
    void*(*semanticAction)();
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
    LinearLinkedListNode *expressions;
} Grammar;

#ifndef _STACK_H
    #include "Stack.h"
#endif

#ifndef _SEMANTICS
  #include "../grammar/semantics.h"
#endif

#ifndef _DICTIONARY_H
    #include "Dictionary.h"
#endif

AbstractSyntaxTreeNode *DefaultSemanticAction(void *scopeStack, Stack *semanticStack);
void AssignActions(Grammar *g);

void InitGrammar(Grammar *grammar);
NonTerminal* InitialNonTerminal(Grammar *grammar);
Rule* InitialRule(Grammar *grammar);
Expression* EODTerminal(Grammar *grammar);
BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second);
BOOL CompareTerminals(ExpressionValue first, ExpressionValue second);
void GrammarFirstSet(Grammar *grammar);
Item* NextItem(Item *item);
Item* InitialItem(Rule *rule, TokenType lookahead);
void FreeGrammar(Grammar *grammar);