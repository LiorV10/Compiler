// Parser.h

#ifndef _PUSHDOWN_MACHINE_H
    #include "../libs/PushdownMachine.h"
#endif

#ifndef _GRAMMAR_H
    #include "../libs/Grammar.h"
#endif

#ifndef _QUEUE_H
    #include "../libs/Queue.h"
#endif

typedef struct
{
    Grammar *grammar;
    PushdownMachine *pushdownMachine;
} Parser;

void InitParser(Parser *parser, const char **);
void Parse(Parser *parser, CircularLinearLinkedListNode *tokens);