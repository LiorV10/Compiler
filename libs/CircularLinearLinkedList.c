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

void EmptyCircularLinearLinkedList(CircularLinearLinkedListNode **manager)
{
    CircularLinearLinkedListNode *ptr = *manager;

    while (ptr->nextNode != *manager)
    {
        DeleteAfterCircularLinearLinkedList(ptr);
    }

    DeleteLastCircularLinearLinkedList(manager);
}