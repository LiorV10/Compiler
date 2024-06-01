// Dictionary.c

#include "Dictionary.h"

#define SHIFT_BY 33
#define FIRST_MUL_BY 0xff51afd7ed558ccd
#define SECOND_MUL_BY 0xc4ceb9fe1a85ec53

//-----------------------------------------------------------------------------
//                              Init Dictionary                                     
//                              ---------------                                  
//                                                                             
// General      : The function initializes a dictionary.                                 
//                                                                             
// Parameters   :                                                              
//      dictionary - The dictionary (Out)                                     
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
void InitDictionary(Dictionary *dictionary)
{
    *dictionary = (Dictionary){.buckets = {NULL}};
}

//-----------------------------------------------------------------------------
//                                      Hash                                     
//                                      ----                                  
//                                                                             
// General      : The function hashes a given key.                                 
//                                                                             
// Parameters   :                                                              
//      key - The key (In)                                     
//                                                                             
// Return Value : The hash value.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
unsigned short Hash(unsigned long value)
{
    value ^= value >> SHIFT_BY;
    value *= FIRST_MUL_BY;
    value ^= value >> SHIFT_BY;
    value *= SECOND_MUL_BY;
    value ^= value >> SHIFT_BY;

    return (value & (MAX_DICTIONARY_SIZE - ONE));
}

//-----------------------------------------------------------------------------
//                                  Insert Dictionary                                      
//                                  -----------------                                
//                                                                             
// General      : The function inserts a new item into a dictionary.                                 
//                                                                             
// Parameters   :                                                              
//      dictionary - The dictionary (In)                                     
//      item - The item to insert (In)   
//      Key - The key function (In)                                     
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
void InsertDictionary(Dictionary *dictionary, void *item, unsigned long(*Key)(void *item))
{
    LinearLinkedListNode **bucket = dictionary->buckets + Hash(Key(item));

    PushLinearLinkedList(bucket);
    (*bucket)->info = item;
}

//-----------------------------------------------------------------------------
//                                  Lookup Dictionary                                     
//                                  -----------------                                  
//                                                                             
// General      : The function lookups for an item in a dictionary.                                 
//                                                                             
// Parameters   :                                                              
//      dictionary - The dictionary (In)                                     
//      item - The item to look for (In)                                     
//      Key - The key function (In)                                     
//      Compare - The comparator (In)                                     
//                                                                             
// Return Value : The item found.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
//                                  Empty Dictionary                                     
//                                  ----------------                                  
//                                                                             
// General      : The function empties a dictionary.                                 
//                                                                             
// Parameters   :                                                              
//      dictionary - The dictionary (In)                                                                    
//      Free - The free function for each item (In)                                                                    
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c*n + d
//-----------------------------------------------------------------------------
void EmptyDictionary(Dictionary *dictionary, void(*Free)(void *))
{
    LinearLinkedListNode **start = dictionary->buckets;
    LinearLinkedListNode **end = dictionary->buckets + MAX_DICTIONARY_SIZE;

    for (; start != end; start++)
    {
        EmptyLinearLinkedList(start, Free);
    }
}