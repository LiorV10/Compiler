// Lexer.h

#ifndef _REGEX_H
    #include "../libs/Regex.c"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "../libs/CircularLinearLinkedList.h"
#endif

#ifndef _SEMANTICS
    #include "../grammar/semantics.h"
#endif

#ifndef _TOKEN_H
    #include "../libs/Token.h"
#endif

#ifndef _STACK_H
    #include "../libs/Stack.h"
#endif

#ifndef _ERROR_HANDLER_H
    #include "ErrorHandler.h"
#endif

typedef struct
{
    StateMachine *nfa;
} Lexer;

void InitLexer(Lexer *lexer);
void FreeLexer(Lexer *lexer);
CircularLinearLinkedListNode* Tokenize(Lexer *lexer, char *source, ErrorHandler *errors);