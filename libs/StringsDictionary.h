// StringDictionary.h

#define _STRINGS_DICTIONARY_H

#ifndef _TERNARY_TREE_H
    #include "TernaryTree.h"
#endif

#define MAX_SIZE 32

typedef struct
{
    TernaryTreeNode *buckets[MAX_SIZE];
} StringsDictionary;

void InitStringsDictionary(StringsDictionary *stringsDictionary);
void InsertStringsDictionary(StringsDictionary *stringsDictionary, char *string, void *data);
void* LookupStringsDictionary(StringsDictionary *stringsDictionary, char *string);
void EmptyStringsDictionary(StringsDictionary *stringsDictionary);