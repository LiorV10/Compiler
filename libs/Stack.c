// Stack.c

#ifndef _STACK_H
#include "Stack.h"
#endif

//-----------------------------------------------------------------------------
//                                  Init Stack									
//                                  ----------									
//																				
// General      : The function initializes a given stack.									
//																				
// Parameters   :																
//      stack - The stack to initialize (I/O)			
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void InitStack(Stack *stack)
{
    // Code section

    InitLinearLinkedList(&(stack->topOfStack));
}

//-----------------------------------------------------------------------------
//                                  Is Empty Stack									
//                                  --------------									
//																				
// General      : The function checks whether a given stack is empty.									
//																				
// Parameters   :																
//      stack - The stack (In)		
//																				
// Return Value : Whether the stack is empty.				
//																				
//-----------------------------------------------------------------------------
BOOL IsEmptyStack(Stack *stack)
{
    // Code section

    return (IsEmptyLinearLinkedList(stack->topOfStack));
}

//-----------------------------------------------------------------------------
//                                  Push Stack									
//                                  ----------									
//																				
// General      : The function pushes a given item into a given stack.									
//																				
// Parameters   :																
//      stack   - The stack to push into (I/O)									
//      item    - The item to push (In)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void PushStack(Stack *stack, STACK_TYPE item)
{
    // Code section

    PushLinearLinkedList(&stack->topOfStack);
    stack->topOfStack->info = item;
}

//-----------------------------------------------------------------------------
//                                  Pop Stack									
//                                  ---------									
//																				
// General      : The function pops the top of a given stack.									
//																				
// Parameters   :																
//      stack - The stack to pop from (I/O)											
//																				
// Return Value : The item popped.				
//																				
//-----------------------------------------------------------------------------
STACK_TYPE PopStack(Stack *stack)
{
    // Variable definition
    STACK_TYPE item;

    // Code section

    item = stack->topOfStack->info;
    PopLinearLinkedList(&stack->topOfStack);

    return (item);
}