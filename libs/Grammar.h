// Grammar.h

#define _GRAMMAR_H

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _TOKEN_H
    #include "Token.h"
#endif

#ifndef _ABSTRACT_SYNTAX_TREE_H
    #include "AbstractSyntaxTree.h"
#endif

#ifndef _STACK_H
    #include "Stack.h"
#endif

#ifndef _DICTIONARY_H
    #include "Dictionary.h"
#endif

typedef struct
{
    BOOL visited;
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
    BOOL visited;
    BOOL isTerminal;
    ExpressionValue value;
    void *node;
} Expression;

typedef struct
{
    NonTerminal *nonTerminal;
    LinearLinkedListNode *expressions;
    void*(*semanticAction)();
} Rule;

typedef struct
{
    Rule *rule;
    LinearLinkedListNode *dotPosition;
    Expression *lookahead;
} Item;

typedef struct
{
    LinearLinkedListNode *nonTerminals;
    LinearLinkedListNode *expressions;
} Grammar;

AbstractSyntaxTreeNode* DefaultSemanticAction(void *scopeStack, Stack *semanticStack);
void InitGrammar(Grammar *grammar);
NonTerminal* InitialNonTerminal(Grammar *grammar);
Rule* InitialRule(Grammar *grammar);
Expression* EODTerminal(Grammar *grammar);
BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second);
BOOL CompareTerminals(ExpressionValue first, ExpressionValue second);
Dictionary* GrammarFirstSet(Grammar *grammar);
LinearLinkedListNode *LookupFirstSet(Dictionary *firstSets, Expression *expression);
Item* NextItem(Item *item);
Item* InitialItem(Rule *rule, Expression *lookahead);
void FreeFirstSets(Dictionary *firstSets);
void FreeGrammar(Grammar *grammar);