// Regex.h

#define _REGEX_H

#ifndef _STATE_MACHINE_H
    #include "StateMachine.h"
#endif

#ifndef _STACK_H
    #include "Stack.h"
#endif

#define CONCAT_CHAR '\002'
#define LTETTERS_CHAR '\003'
#define DIGIT_CHAR '\004'
#define STAR_OPERATOR '\005'
#define PLUS_OPERATOR '\006'
#define ALTERNATION_OPERATOR '\007'
#define UNION_OPERATOR '\010'
#define LETTERS_PATTERN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010"
#define DIGIT_PATTERN "0123456789\010\010\010\010\010\010\010\010\010"

typedef struct
{
    char *start;
    char *end;
} Match;

StateMachine *RegexToNFA(char *pattern, void *finalStateInfo);
void* ExecuteRegex(StateMachine *nfa, char *input, Match **match);
void FreeMatch(Match *match);