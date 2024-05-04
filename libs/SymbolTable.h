// SymbolTable.h

#define _SYMBOL_TABLE_H

#ifndef _TERNARY_TREE_H
    #include "TernaryTree.h"
#endif

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _TOKEN_H
    #include "Token.h"
#endif

#define MAX_SIZE 32

typedef struct
{
    char *name;
    TokenType type;
} Symbol;

typedef struct
{
    TernaryTreeNode *buckets[MAX_SIZE];
} SymbolTable;

typedef struct
{
    LinearLinkedListNode *symbolTables;
} ScopeStack;

void MakeSymbol(Symbol **symbol);
void InitScopeStack(ScopeStack *scopeStack);
void EnterScope(ScopeStack *scopeStack);
void ExitScope(ScopeStack *scopeStack);
void InsertSymbol(ScopeStack *scopeStack, Symbol *symbol);
Symbol* LookupSymbol(ScopeStack *scopeStack, char *name);