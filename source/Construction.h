#include <stdio.h>
#include <string.h>

#ifndef _GRAMMAR_H
    #include "../libs/Grammar.h"
#endif  

#ifndef _STRINGS_DICTIONARY_H
    #include "../libs/StringsDictionary.h"
#endif

#ifdef DDEBUG
    #define GRAMMAR_DEFINITIONS "grammar/grammar_definitions"
    #define GRAMMAR_RULES "grammar/grammar_rules_copy"
    #define SEMANTICS_FILE "grammar/semantics.c"
#else
    #define GRAMMAR_DEFINITIONS "../grammar/grammar_definitions"
    #define GRAMMAR_RULES "../grammar/grammar_rules_copy"
    #define SEMANTICS_FILE "../grammar/semantics.c"
#endif

Grammar BUILD();