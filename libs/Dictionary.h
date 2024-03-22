// Dictionary.h

#define _DICTIONARY_H

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

#ifndef _LINEAR_LINKED_LIST_H
    #include "LinearLinkedList.h"
#endif

#define KEY_TYPE char

typedef struct
{
    LinearLinkedList *buckets[];
} Dictionary;