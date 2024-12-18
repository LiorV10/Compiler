// CircularLinearLinkedList.c

#include "CircularLinearLinkedList.h"

void InitCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    *manager = NULL;
}

void InsertAfterCircularLinearLinkedList(CircularLinearLinkedListNode *node)
{
    CircularLinearLinkedListNode *newNode = 
        (CircularLinearLinkedListNode*)malloc(sizeof(CircularLinearLinkedListNode));

    newNode->nextNode = node->nextNode;
    node->nextNode = newNode;
}

void InsertLastCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    CircularLinearLinkedListNode *newNode = 
        (CircularLinearLinkedListNode*)malloc(sizeof(CircularLinearLinkedListNode));

    newNode->nextNode = newNode;
    *manager = newNode;
}

void InsertEndCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    CircularLinearLinkedListNode *newNode = 
        (CircularLinearLinkedListNode*)malloc(sizeof(CircularLinearLinkedListNode));

    newNode->nextNode = (*manager)->nextNode;
    (*manager)->nextNode = newNode;
    *manager = newNode;
}

void DeleteAfterCircularLinearLinkedList(CircularLinearLinkedListNode *node)
{
    CircularLinearLinkedListNode *temp = node->nextNode;

    node->nextNode = temp->nextNode;
    free(temp);
}

void DeleteLastCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    free(*manager);
    *manager = NULL;
}

void DeleteEndCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    CircularLinearLinkedListNode *ptr = *manager;
    CircularLinearLinkedListNode *temp;

    while (ptr->nextNode != *manager)
    {
        ptr = ptr->nextNode;
    }   

    temp = ptr->nextNode;
    ptr->nextNode = temp->nextNode;
    *manager = ptr;
    free(temp);
}

void ConcatCircularLinearLinkedLists(CircularLinearLinkedListNode **first,
                                     CircularLinearLinkedListNode *second)
{
    CircularLinearLinkedListNode *ptr = (*first)->nextNode;

    (*first)->nextNode = second->nextNode;
    second->nextNode = ptr;

    *first = second;
}

void CircularLinearLinkedListEmptyFunction(void *_) {}

void EmptyCircularLinearLinkedList(CircularLinearLinkedListNode **manager, void(*Free)(void *))
{
    CircularLinearLinkedListNode *ptr = *manager;

    Free = Free ? Free : CircularLinearLinkedListEmptyFunction;

    while (ptr && ptr->nextNode != *manager)
    {
        Free(ptr->nextNode->info);
        DeleteAfterCircularLinearLinkedList(ptr);
    }

    ptr ? Free((*manager)->info) : ZERO;

    DeleteLastCircularLinearLinkedList(manager);
}