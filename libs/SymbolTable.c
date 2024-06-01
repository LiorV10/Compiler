// SymbolTable.c

#include "SymbolTable.h"

void MakeSymbol(Symbol **symbol)
{
    *symbol = malloc(sizeof(Symbol));
    
    (*symbol)->name = NULL;
    (*symbol)->memoryAddress = ZERO;
}

void InitScopeStack(ScopeStack *scopeStack)
{
    InitLinearLinkedList(&scopeStack->symbolTables);
}

void EnterScope(ScopeStack *scopeStack)
{
    PushLinearLinkedList(&scopeStack->symbolTables);

    scopeStack->symbolTables->info = malloc(sizeof(StringsDictionary));
    InitStringsDictionary(scopeStack->symbolTables->info);
}

void ExitScope(ScopeStack *scopeStack)
{
    EmptyStringsDictionary(scopeStack->symbolTables->info);
    PopLinearLinkedList(&scopeStack->symbolTables);
}

void InsertSymbol(ScopeStack *scopeStack, Symbol *symbol)
{
    InsertStringsDictionary(scopeStack->symbolTables->info, symbol->name, symbol);
}

Symbol* LookupSymbol(ScopeStack *scopeStack, char *name)
{
    LinearLinkedListNode *ptr = scopeStack->symbolTables;
    Symbol *symbol = NULL;

    while (ptr && !symbol)
    {
        symbol = LookupStringsDictionary(ptr->info, name);
        ptr = ptr->nextNode;
    }

    return (symbol);
}