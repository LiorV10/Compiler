// Dictionary

#ifndef _LINEAR_LINKED_LIST_H
    #include "../libs/LinearLinkedList.h"
#endif

// #define MAX_SIZE 128

// typedef struct
// {
//     LinearLinkedListNode *buckets[MAX_SIZE];
// } Dictionary;

// void InitDictionary(Dictionary *dictionary)
// {
//     *dictionary = (Dictionary){.buckets = {NULL}};
// }

// unsigned short Hash(unsigned long value)
// {
//     value ^= value >> 33;
//     value *= 0xff51afd7ed558ccd;
//     value ^= value >> 33;
//     value *= 0xc4ceb9fe1a85ec53;
//     value ^= value >> 33;

//     return (value & (MAX_SIZE - ONE));
// }

// void InsertDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item))
// {
//     LinearLinkedListNode **bucket = dictionary->buckets + Hash(Key(item));

//     PushLinearLinkedList(bucket);
//     (*bucket)->info = item;
// }

// BOOL LookupDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item),
//                       BOOL(*Compare)(void *firstItem, void *secondItem))
// {
//     LinearLinkedListNode *bucket = dictionary->buckets[Hash(Key(item))];
    
//     while (bucket && !Compare(bucket->info, item))
//     {
//         bucket = bucket->nextNode;
//     }

//     return (!!bucket);
// }

// void EmptyDictionary(Dictionary *dictionary, void(*FreeItem)())
// {
//     LinearLinkedListNode **start = dictionary->buckets;
//     LinearLinkedListNode **end = dictionary->buckets + MAX_SIZE;

//     for (; start != end; start++)
//     {
//         EmptyLinearLinkedList(start, FreeItem);
//     }
// }

// // unsigned int hash2(unsigned int h)
// // {
// //     h ^= h >> 33;
// //     h *= 0xff51afd7ed558ccdL;
// //     h ^= h >> 33;
// //     h *= 0xc4ceb9fe1a85ec53L;
// //     h ^= h >> 33;

// //     return (h & (MAX_SIZE - ONE));
// // }

// // unsigned int joaat_hash(char *key)
// // {
// //     unsigned int hash = 0;
// //     size_t len = strlen(key);
// //     size_t i;

// //     for (i = 0; i < len; i++)
// //     {
// //         hash += key[i];
// //         hash += (hash << 10);
// //         hash ^= (hash >> 6);
// //     }

// //     hash += (hash << 3);
// //     hash ^= (hash >> 11);
// //     hash += (hash << 15);

// //     return hash & (MAX_SIZE - ONE);
// // }

// typedef struct
// {
//     int *first;
//     int second;
// } Pair;

// Pair* MakePair(int *first, int second)
// {
//     Pair *p = malloc(sizeof(Pair));
    
//     p->first = first;
//     p->second = second;

//     return (p);
// }

// unsigned long KeyValue(Pair *pair)
// {
//     return (unsigned long)(pair->first + pair->second);
// }

// BOOL Compare(Pair *first, Pair *second)
// {
//     return (first->first == second->first && first->second == second->second);
// }

// // void main(void)
// // {
// //     Dictionary dictionary;

// //     InitDictionary(&dictionary);

// //     int a;
// //     int b;
// //     int c;

// //     Pair *p1 = MakePair(&a, 5);
// //     Pair *p2 = MakePair(&a, 7);
// //     Pair *p3 = MakePair(&c, 6);
// //     Pair *p4 = MakePair(&b, 5);
// //     Pair *p5 = MakePair(&c, 6);

// //     InsertDictionary(&dictionary, p1, KeyValue);
// //     InsertDictionary(&dictionary, p2, KeyValue);
// //     InsertDictionary(&dictionary, p3, KeyValue);
// //     InsertDictionary(&dictionary, p4, KeyValue);
// //     //InsertDictionary(&dictionary, p5, KeyValue);

// //     printf("%d\n", LookupDictionary(&dictionary, p5, KeyValue, Compare));

// //     free(p1);
// //     free(p2);
// //     free(p3);
// //     free(p4);
// //     free(p5);

// //     EmptyDictionary(&dictionary);
// // }

void main(void)
{
    LinearLinkedListNode *temp = NULL;

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));

    PushLinearLinkedList(&temp);
    temp->info = a;

    PushLinearLinkedList(&temp);
    temp->info = b;

    PushLinearLinkedList(&temp);
    temp->info = c;

    EmptyLinearLinkedList(&temp, free);
}