// Regex.h

#define _REGEX_H

#ifndef _STATE_MACHINE_H
    #include "StateMachine.h"
#endif

#ifndef _STACK_H
    #include "Stack.h"
#endif

#define CONCAT_CHAR '\002'
#define ASCII_LTETTERS_CHAR '\003'
#define DIGIT_CHAR '\004'
#define ASCII_LETTERS_PATTERN "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ|||||||||||||||||||||||||||||||||||||||||||||||||||"
#define DIGIT_PATTERN "0123456789|||||||||"

typedef struct
{
    char *start;
    char *end;
} MatchType;

StateMachine *RegexToNFA(char *pattern);
MatchType* Match(StateMachine *nfa, char *input);