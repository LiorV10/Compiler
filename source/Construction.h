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
    #define GRAMMAR_RULES "grammar/grammar_rules"
    #define SEMANTICS_FILE "grammar/semantics.c"
    #define SEMANTICS_H_FILE "grammar/semantics.h"
#else
    #define GRAMMAR_DEFINITIONS "../grammar/grammar_definitions"
    #define GRAMMAR_RULES "../grammar/grammar_rules"
    #define SEMANTICS_FILE "../grammar/semantics.c"
    #define SEMANTICS_H_FILE "../grammar/semantics.h"
#endif

#define UPDATE_HEADER TRUE

#if !UPDATE_HEADER
    #undef SEMANTICS_H_FILE
    #define SEMANTICS_H_FILE ""
#endif

void BuildGrammarFromFile(Grammar *grammar);