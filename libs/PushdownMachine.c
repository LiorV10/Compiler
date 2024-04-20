// PushdownMachine.c

#include "PushdownMachine.h"

void InitPushdownMachine(PushdownMachine *pushdownMachine)
{
    pushdownMachine->stack = malloc(sizeof(Stack));
    
    InitCircularLinearLinkedList(&pushdownMachine->statesManager);
    InitStack(pushdownMachine->stack);
}