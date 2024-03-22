// Dictionary.c

#ifndef _DICTIONARY_H
    #include "Dictionary.h"
#endif

typedef struct
{
    LinearLinkedListNode **buckets;
    unsigned short size;
} Dictionary;

void InitDictionary(Dictionary *dictionary, unsigned short size)
{
    dictionary->buckets = calloc(size, sizeof(LinearLinkedListNode*));
    dictionary->size = size;
}

unsigned short Hash(Dictionary *dictionary, KEY_TYPE key)
{
    return (key) % dictionary->size;
}

void PutDictionary(Dictionary *dictionary, KEY_TYPE key, void *value)
{
    LinearLinkedListNode **bucket = dictionary->buckets + Hash(dictionary, key);

    PushLinearLinkedList(bucket);
    (*bucket)->info = value;
}

void* LookupDictionary(Dictionary *dictionary, KEY_TYPE key)
{
    LinearLinkedListNode *bucket = dictionary->buckets[Hash(dictionary, key)];

    
}