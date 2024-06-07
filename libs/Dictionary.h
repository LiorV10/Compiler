// Dictionary.h

#define _DICTIONARY_H

#ifndef _LINEAR_LINKED_LIST_H
    #include "../libs/LinearLinkedList.h"
#endif

#define MAX_DICTIONARY_SIZE 128

typedef struct
{
    LinearLinkedListNode *buckets[MAX_DICTIONARY_SIZE];
} Dictionary;

void InitDictionary(Dictionary *dictionary);
void InsertDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item));
void* LookupDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item),
                      BOOL(*Compare)(void *firstItem, void *secondItem));
void EmptyDictionary(Dictionary *dictionary, void(*Free)(void *));