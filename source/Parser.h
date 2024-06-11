// Parser.h

#ifndef _GRAMMAR_H
    #include "../libs/Grammar.h"
#endif

#ifndef _PUSHDOWN_MACHINE_H
    #include "../libs/PushdownMachine.h"
#endif

#ifndef _QUEUE_H
    #include "../libs/Queue.h"
#endif

#ifndef _DICTIONARY_H
    #include "../libs/Dictionary.h"
#endif

#ifndef _SYMBOL_TABLE_H
    #include "../libs/SymbolTable.h"
#endif

#ifndef _ABSTRACT_SYNTAX_TREE_H
    #include "../libs/AbstractSyntaxTree.h"
#endif

#ifndef _ERROR_HANDLER_H
    #include "ErrorHandler.h"
#endif

#define GENERATE_LALR TRUE

typedef struct
{
    Grammar *grammar;
    PushdownMachine *pushdownMachine;
} Parser;

void InitParser(Parser *parser, Grammar *grammar);
AbstractSyntaxTreeNode* Parse(Parser *parser, CircularLinearLinkedListNode *tokens, Stack *errors);