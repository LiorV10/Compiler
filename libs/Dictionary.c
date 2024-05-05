// Dictionary.c

#include "Dictionary.h"

void InitDictionary(Dictionary *dictionary)
{
    *dictionary = (Dictionary){.buckets = {NULL}};
}

unsigned short Hash(unsigned long value)
{
    value ^= value >> 33;
    value *= 0xff51afd7ed558ccd;
    value ^= value >> 33;
    value *= 0xc4ceb9fe1a85ec53;
    value ^= value >> 33;

    return (value % (MAX_DICTIONARY_SIZE - ONE));
}

void InsertDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item))
{
    LinearLinkedListNode **bucket = dictionary->buckets + Hash(Key(item));

    PushLinearLinkedList(bucket);
    (*bucket)->info = item;
}

void* LookupDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item),
                      BOOL(*Compare)(void *firstItem, void *secondItem))
{
    LinearLinkedListNode *bucket = dictionary->buckets[Hash(Key(item))];

    while (bucket && !Compare(bucket->info, item))
    {
        bucket = bucket->nextNode;
    }

    return (bucket ? bucket->info : NULL);
}

void EmptyDictionary(Dictionary *dictionary, void(*Free)(void *))
{
    LinearLinkedListNode **start = dictionary->buckets;
    LinearLinkedListNode **end = dictionary->buckets + MAX_DICTIONARY_SIZE;

    for (; start != end; start++)
    {
        EmptyLinearLinkedList(start, Free);
    }
}