// Parser.h

#ifndef _PUSHDOWN_MACHINE_H
    #include "../libs/PushdownMachine.h"
#endif

#ifndef _GRAMMAR_H
    #include "../libs/Grammar.h"
#endif

typedef struct
{
    Grammar *grammar;
    PushdownMachine *pushdownMachine;
} Parser;

void InitParser(Parser *parser, const char **);