// SymbolTable.h

#define _SYMBOL_TABLE_H

#ifndef _STRINGS_DICTIONARY_H
    #include "StringsDictionary.h"
#endif

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#ifndef _TOKEN_H
    #include "Token.h"
#endif

typedef struct
{
    char *name;
    unsigned short type;
    short memoryAddress;
    void *_type;
} Symbol;

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