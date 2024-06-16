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

#define VARIABLE_KIND_MASK 0
#define FUNCTION_KIND_MASK 1
#define STRUCT_KIND_MASK 2
#define TYPE_KIND_MASK 3
#define KINDS_COUNT 4

typedef struct
{
    char *name;
    short memoryAddress;
    BIT_VEC(kind, KINDS_COUNT);
    void *type;
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
Symbol* LookupSymbolInCurrentScope(ScopeStack *scopeStack, char *name);