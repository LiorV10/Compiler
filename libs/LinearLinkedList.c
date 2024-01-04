// LinearLinkedList.c

#ifndef _LINEAR_LINKED_LIST_H
#include "LinearLinkedList.h"
#endif

//-----------------------------------------------------------------------------
//                              Init Linear Linked List									
//                              -----------------------									
//																				
// General      : The function initializes a linear linked list.									
//																				
// Parameters   :																
//      manager - Pointer to the manager of the list (I/O)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void InitLinearLinkedList(LinearLinkedListNode **manager)
{
    // Code section

    *manager = NULL;
}

//-----------------------------------------------------------------------------
//                              Is Empty Linear Linked List									
//                              ---------------------------									
//																				
// General      : The function checks whether a linear linked list is empty.									
//																				
// Parameters   :																
//      manager - The manager of the list (In)											
//																				
// Return Value : Whether the list is empty.				
//																				
//-----------------------------------------------------------------------------
BOOL IsEmptyLinearLinkedList(LinearLinkedListNode *manager)
{
    // Code section
    
    return (!manager);
}

//-----------------------------------------------------------------------------
//                              Push Linear Linked List									
//                              -----------------------									
//																				
// General      : The function pushes a node into linear linked list.									
//																				
// Parameters   :																
//      manager - Pointer to the manager of the list (I/O)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void PushLinearLinkedList(LinearLinkedListNode **manager)
{
    // Variable definition
    LinearLinkedListNode *newNode = 
        (LinearLinkedListNode*)malloc(sizeof(LinearLinkedListNode));

    // Code section

    newNode->nextNode = *manager;
    *manager = newNode;
}

//-----------------------------------------------------------------------------
//                              Add after Linear Linked List									
//                              ----------------------------								
//																				
// General      : The function adds a node after a given node
//                in a linear linked list.									
//																				
// Parameters   :																
//      node - the node to add after (In)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void AddAfterLinearLinkedList(LinearLinkedListNode *node)
{
    // Variable definition
    LinearLinkedListNode *newNode = 
        (LinearLinkedListNode*)malloc(sizeof(LinearLinkedListNode));

    // Code section
    
    newNode->nextNode = node->nextNode;
    node->nextNode = newNode;
}

//-----------------------------------------------------------------------------
//                              Pop Linear Linked List									
//                              ----------------------								
//																				
// General      : The function pops a node into linear linked list.									
//																				
// Parameters   :																
//      manager - Pointer to the manager of the list (I/O)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void PopLinearLinkedList(LinearLinkedListNode **manager)
{
    // Variable definition
    LinearLinkedListNode *temp = *manager;

    // Code section

    *manager = temp->nextNode;
    free(temp);
}

//-----------------------------------------------------------------------------
//                              Delete after Linear Linked List									
//                              -------------------------------							
//																				
// General      : The function deletes a node after a given node
//                in a linear linked list.									
//																				
// Parameters   :																
//      node - the node to delete after (In)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void DeleteAfterLinearLinkedList(LinearLinkedListNode *node)
{
    // Variable definition
    LinearLinkedListNode *temp = node->nextNode;

    // Code section

    node->nextNode = temp->nextNode;
    free(temp);
}

//-----------------------------------------------------------------------------
//                              Reverse Linear Linked List									
//                              --------------------------						
//																				
// General      : The function reverses a linear linked list.									
//																				
// Parameters   :																
//      manager - Pointer to the manager of the list (I/O)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void ReverseLinearLinkedList(LinearLinkedListNode **manager)
{
    // Variable definition
    LinearLinkedListNode *ptr       = *manager;
    LinearLinkedListNode *previous  = NULL;
    LinearLinkedListNode *next;

    // Code section

    // Running through all nodes
    while (ptr)
    {
        next = ptr->nextNode;
        ptr->nextNode = previous;
        previous = ptr;
        ptr = next;
    }

    *manager = previous;
}

void ClearLinearLinkedList(LinearLinkedListNode **manager)
{
    while (*manager)
    {
        PopLinearLinkedList(manager);
    }

    *manager = NULL;
}

// void UniteLinearLinkedLists(LinearLinkedListNode *first, LinearLinkedListNode *second)
// {
//     LinearLinkedListNode *ptrFirst = first;

//     while ((ptrFirst = ptrFirst->nextNode)->nextNode);

//     ptrFirst->nextNode = second;
// }

// void DeleteAllOccurencesLinearLinkedList(LinearLinkedListNode **manager, LINEAR_LINKED_LIST_NODE_TYPE info)
// {
//     LinearLinkedListNode *ptr = *manager;

//     while (ptr->info == info)
//     {
//         PopLinearLinkedList(manager);
//         ptr = ptr->nextNode;
//     }

//     while (ptr->nextNode)
//     {
//         ptr->nextNode->info == info ? DeleteAfterLinearLinkedList(ptr) : ZERO;
//         ptr = ptr->nextNode;
//     }
// }

// LinearLinkedListNode* GetLastNodeLinearLinkedList(LinearLinkedListNode* manager)
// {
//     LinearLinkedListNode *ptr = manager;

//     while (ptr->nextNode)
//     {
//         ptr = ptr->nextNode;
//     }

//     return (ptr);
// }

// LinearLinkedListNode* FindNaturalPlaceLinearLinkedList(LinearLinkedListNode *manager, LINEAR_LINKED_LIST_NODE_TYPE info)
// {
//     LinearLinkedListNode *ptr = manager;

//     while (ptr->nextNode && ptr->nextNode->info < info)
//     {
//         ptr = ptr->nextNode;
//     }

//     return (ptr);
// }

// void AddToNaturalPlaceLinearLinkedList(LinearLinkedListNode **manager, LINEAR_LINKED_LIST_NODE_TYPE info)
// {
//     LinearLinkedListNode *ptr = FindNaturalPlaceLinearLinkedList(*manager, info);

//     ptr == *manager && ptr->info > info ? 
//         (PushLinearLinkedList(manager), ptr = *manager) : 
//         (AddAfterLinearLinkedList(ptr), ptr = ptr->nextNode);

//     ptr->info = info;
// }

// void main(void)
// {
//     LinearLinkedListNode *manager1;
//     InitLinearLinkedList(&manager1);

//     PushLinearLinkedList(&manager1);
//     manager1->info = 9;

//     PushLinearLinkedList(&manager1);
//     manager1->info = 7;

//     PushLinearLinkedList(&manager1);
//     manager1->info = 6;

//     PushLinearLinkedList(&manager1);
//     manager1->info = 4;

//     AddToNaturalPlaceLinearLinkedList(&manager1, 10);

//     puts("||");
// }