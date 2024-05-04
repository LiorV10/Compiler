// SymbolTable.c

#include "SymbolTable.h"

void MakeSymbol(Symbol **symbol)
{
    *symbol = malloc(sizeof(Symbol));
    
    (*symbol)->name = NULL;
}

void InitSymbolTable(SymbolTable *symbolTable)
{
    *symbolTable = (SymbolTable){.buckets = {NULL}};
}

unsigned short HashSymbol(char *str)
{
    unsigned long hash = 5381;

    while (*str)
    {
        hash = ((hash << 5) + hash) + *str++;
    }

    return (hash & (MAX_SIZE - ONE));
}

void InsertSymbolTable(SymbolTable *symbolTable, Symbol *symbol)
{
    TernaryTreeNode **bucket = symbolTable->buckets + HashSymbol(symbol->name);
    InsertToTernarySearchTree(bucket, symbol->name, symbol);
}

Symbol* LookupSymbolTable(SymbolTable *symbolTable, char *symbolName)
{
    TernaryTreeNode *bucket = symbolTable->buckets[HashSymbol(symbolName)];
    
    return SerchInTernarySearchTree(bucket, symbolName);
}

void EmptySymbolTable(SymbolTable *symbolTable)
{
    TernaryTreeNode **start = symbolTable->buckets;
    TernaryTreeNode **end = symbolTable->buckets + MAX_SIZE;

    for (; start != end; start++)
    {
        EmptyTernarySearchTree(*start);
    }

    free(symbolTable);
}

void InitScopeStack(ScopeStack *scopeStack)
{
    InitLinearLinkedList(&scopeStack->symbolTables);
}

void EnterScope(ScopeStack *scopeStack)
{
    PushLinearLinkedList(&scopeStack->symbolTables);

    scopeStack->symbolTables->info = malloc(sizeof(SymbolTable));
    InitSymbolTable(scopeStack->symbolTables->info);
}

void ExitScope(ScopeStack *scopeStack)
{
    EmptySymbolTable(scopeStack->symbolTables->info);
    PopLinearLinkedList(&scopeStack->symbolTables);
}

void InsertSymbol(ScopeStack *scopeStack, Symbol *symbol)
{
    InsertSymbolTable(scopeStack->symbolTables->info, symbol);
}

Symbol* LookupSymbol(ScopeStack *scopeStack, char *name)
{
    LinearLinkedListNode *ptr = scopeStack->symbolTables;
    Symbol *symbol = NULL;

    while (ptr && !symbol)
    {
        symbol = LookupSymbolTable(ptr->info, name);
        ptr = ptr->nextNode;
    }

    return (symbol);
}