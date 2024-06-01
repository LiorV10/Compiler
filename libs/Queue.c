// Queue.c

#ifndef _QUEUE_H
#include "Queue.h"
#endif

//-----------------------------------------------------------------------------
//                                  Init Queue									
//                                  ----------									
//																				
// General      : The function initializes a given queue.									
//																				
// Parameters   :																
//      iopqQueue - The queue to initialize (I/O)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void InitQueue(Queue *iopqQueue)
{
    InitCircularLinearLinkedList(&iopqQueue->rear);
}

//-----------------------------------------------------------------------------
//                                  Insert Queue									
//                                  ------------								
//																				
// General      : The function inserts a given item into a given queue.									
//																				
// Parameters   :																
//      iopqQueue   - The queue to insert into (I/O)									
//      itItem      - The item to insert (In)												
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void InsertQueue(Queue *iopqQueue, QUEUE_TYPE item)
{
    !IsEmptyQueue(iopqQueue) ? 
        InsertEndCircularLinearLinkedList(&iopqQueue->rear) : 
        InsertLastCircularLinearLinkedList(&iopqQueue->rear);

    iopqQueue->rear->info = item;
}

//-----------------------------------------------------------------------------
//                                  Remove Queue									
//                                  ------------								
//																				
// General      : The function removes the front of a given queue.									
//																				
// Parameters   :																
//      iopqQueue - The queue to remove from (I/O)											
//																				
// Return Value : The item removed.				
//																				
//-----------------------------------------------------------------------------
QUEUE_TYPE RemoveQueue(Queue *iopqQueue)
{
    QUEUE_TYPE item;

    item = iopqQueue->rear->nextNode->info;

    iopqQueue->rear == iopqQueue->rear->nextNode ? 
        DeleteLastCircularLinearLinkedList(&(iopqQueue->rear)) : 
        DeleteAfterCircularLinearLinkedList(iopqQueue->rear);

    return (item);
}

//-----------------------------------------------------------------------------
//                                  Is Empty Queue									
//                                  --------------								
//																				
// General      : The function checks whether a given queue is empty.									
//																				
// Parameters   :																
//      ipqQueue - The queue (In)											
//																				
// Return Value : Whether the queue is empty.				
//																				
//-----------------------------------------------------------------------------
BOOL IsEmptyQueue(Queue *ipqQueue)
{
    return (!(ipqQueue->rear));
}
