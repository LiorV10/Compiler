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

    newNode->info = NULL;
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

    newNode->info = NULL;
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