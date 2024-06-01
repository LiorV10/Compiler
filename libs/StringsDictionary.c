// StringDictionary.c

#include "StringsDictionary.h"

#define HASH_VALUE 5381

void InitStringsDictionary(StringsDictionary *stringsDictionary)
{
    *stringsDictionary = (StringsDictionary){.buckets = {NULL}};
}

unsigned short HashSymbol(char *str)
{
    unsigned long hash = HASH_VALUE;

    while (*str)
    {
        hash = ((hash << FIVE) + hash) + *str++;
    }

    return (hash & (MAX_SIZE - ONE));
}

void InsertStringsDictionary(StringsDictionary *stringsDictionary, char *string, void *data)
{
    TernaryTreeNode **bucket = stringsDictionary->buckets + HashSymbol(string);
    InsertToTernarySearchTree(bucket, string, data);
}

void* LookupStringsDictionary(StringsDictionary *stringsDictionary, char *string)
{
    TernaryTreeNode *bucket = stringsDictionary->buckets[HashSymbol(string)];
    
    return SerchInTernarySearchTree(bucket, string);
}

void EmptyStringsDictionary(StringsDictionary *stringsDictionary)
{
    TernaryTreeNode **start = stringsDictionary->buckets;
    TernaryTreeNode **end = stringsDictionary->buckets + MAX_SIZE;

    for (; start != end; start++)
    {
        EmptyTernarySearchTree(*start);
    }

    free(stringsDictionary);
}