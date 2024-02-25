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

/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/
/*-----------------------------FIX NAMES-----------------------------*/


//-----------------------------------------------------------------------------
//                                  Empty Stack									
//                                  -----------								
//																				
// General      : The function empties a stack.									
//																				
// Parameters   :																
//      stack - The stack (I/O)												
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void EmptyStack(Stack *stack)
{
    // Code section
    
    // Popping all items
    while (!IsEmptyStack(stack))
    {
        PopStack(stack);
    }
}

//-----------------------------------------------------------------------------
//                                  Copy Stack									
//                                  ----------									
//																				
// General      : The function creates a copy of a stack.									
//																				
// Parameters   :																
//      source - The original stack (In)									
//      target - The target stack (Out)											
//																				
// Return Value : None.		
//																				
//-----------------------------------------------------------------------------
void CopyStack(Stack *source, Stack *target)
{
    // Variable definition
    Stack temp;
    STACK_TYPE  item;

    // Code section

    InitStack(&temp);

    // Running through original stack items
    while (!IsEmptyStack(source))
    {
        PushStack(&temp, PopStack(source));
    }

    // Running through the items and pushing them to the target stack
    while (!IsEmptyStack(&temp))
    {
        item = PopStack(&temp);
        PushStack(target, item);
        PushStack(source, item);
    }
}

//-----------------------------------------------------------------------------
//                                  Reverse Stack									
//                                  -------------									
//																				
// General      : The function reverses a stack.									
//																				
// Parameters   :																
//      stack - The stack to reverse (I/O)												
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void ReverseStack(Stack *stack)
{
    // Variable definition
    Stack copy;

    // Code section

    InitStack(&copy);
    CopyStack(stack, &copy);
    EmptyStack(stack);

    // Running through stack items
    while (!IsEmptyStack(&copy))
    {
        PushStack(stack, PopStack(&copy));
    }
}

//-----------------------------------------------------------------------------
//                              Copy Part Of Stack									
//                              ------------------									
//																				
// General      : The function copies part of the stack.									
//																				
// Parameters   :																
//      source  - The source stack (In)									
//      target  - The target stack (I/O)									
//      start   - The start index to copy from (In)
//      end     - The end index to copy to (In)
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void CopyPartOfStack(Stack *source, Stack *target, unsigned short start, unsigned short end)
{
    // Variable definition
    Stack temp;
    STACK_TYPE  item;
    unsigned short index = -ONE;

    // Code section
    InitStack(&temp);

    // Running through stack items
    while (!IsEmptyStack(source))
    {
        PushStack(&temp, PopStack(source));
    }

    // Running through stack items to push them in the correct order
    while (!IsEmptyStack(&temp))
    {
        item = PopStack(&temp);
        ++index >= start && index < end ? PushStack(target, item) : ZERO;
        PushStack(source, item);
    }
}

//-----------------------------------------------------------------------------
//                              Push To Start Of Stack									
//                              ----------------------						
//																				
// General      : The function pushes an item to the bottom of the stack.									
//																				
// Parameters   :																
//      stack - The stack (I/O)									
//      value - The item to push (In)												
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void PushToStartStack(Stack *stack, STACK_TYPE value)
{
    // Variable definition
    Stack temp;

    // Code section

    InitStack(&temp);

    // Running through stack items
    while (!IsEmptyStack(stack))
    {
        PushStack(&temp, PopStack(stack));
    }

    PushStack(stack, value);

    // Pushing the originals item on the top of the new item
    while (!IsEmptyStack(&temp))
    {
        PushStack(stack, PopStack(&temp));
    }
}

//-----------------------------------------------------------------------------
//                                  Is Exists In Stack									
//                                  ------------------									
//																				
// General      : The function checks whether an items exists in the stack.									
//																				
// Parameters   :																
//      stack   - The stack (In)									
//      item    - The item (In)												
//																				
// Return Value : Whether the stack contains the given item.				
//																				
//-----------------------------------------------------------------------------
// BOOL IsExistsInStack(Stack *stack, STACK_TYPE item)
// {
//     // Variable definition
//     Stack temp;

//     // Code section

//     InitStack(&temp);
//     CopyStack(stack, &temp);
//     PushToStartStack(&temp, item);

//     // Running until finding the item
//     while (PopStack(&temp) != item);

//     return (IsEmptyStack(&temp));
// }

//-----------------------------------------------------------------------------
//                                  Max In Stack									
//                                  ------------								
//																				
// General      : The function finds the max value in the stack.									
//																				
// Parameters   :																
//      stack - The stack (In)											
//																				
// Return Value : The max value found.				
//																				
//-----------------------------------------------------------------------------
// STACK_TYPE MaxInStack(Stack *stack)
// {
//     // Variable definition
//     Stack temp;
//     STACK_TYPE max;
//     STACK_TYPE current;

//     // Code section

//     InitStack(&temp);
//     CopyStack(stack, &temp);
//     current = max = PopStack(&temp);

//     // Running through stack items
//     while (!IsEmptyStack(&temp))
//     {
//         current = PopStack(&temp);
//         max = MAX(max, current);
//     }

//     return max;
// }

//-----------------------------------------------------------------------------
//                              Remove Duplicates In Stack									
//                              --------------------------									
//																				
// General      : The function removes duplicates from the stack.									
//																				
// Parameters   :																
//      stack - The stack (I/O)												
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
// void RemoveDuplicatesInStack(Stack *stack)
// {
//     // Variable definition
//     BOOL *visited;
//     STACK_TYPE current;
//     Stack temp;

//     // Code section

//     InitStack(&temp);
//     visited = (BOOL*)calloc(MaxInStack(stack), sizeof(BOOL));

//     // Saving only non-duplicates items
//     while (!IsEmptyStack(stack))
//     {
//         current = PopStack(stack);
//         !visited[*(int*)current] ? PushStack(&temp, current) : ZERO;
//         visited[*(int*)current] = TRUE;
//     }

//     // Pushing the non-duplicates back to the stack
//     while (!IsEmptyStack(&temp))
//     {
//         PushStack(stack, PopStack(&temp));
//     }

//     free(visited);
// }

//-----------------------------------------------------------------------------
//                                  Combine Stacks									
//                                  --------------									
//																				
// General      : The function combines two stacks onto the first one.									
//																				
// Parameters   :																
//      first  - The first stack (I/O)									
//      second - The second stack (In)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void CombineStacks(Stack *first, Stack *second)
{
    // Code section

    ReverseStack(second);

    // Running through second stack items
    while (!IsEmptyStack(second))
    {
        PushStack(first, PopStack(second));
    }
}

//-----------------------------------------------------------------------------
//                              Build Duplicates Stack									
//                              ----------------------									
//																				
// General      : The function builds a stack from duplicates values only.									
//																				
// Parameters   :																
//      stack  - The source stack (In)									
//      target - The target stack (In)			
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
// void BuildDuplicatesStack(Stack *stack, Stack *target)
// {
//     // Variable definition
//     BOOL *visited;
//     STACK_TYPE current;

//     visited = (BOOL*)calloc(MaxInStack(stack), sizeof(BOOL));

//     // Running through stack items
//     while (!IsEmptyStack(stack))
//     {
//         current = PopStack(stack);
//         visited[*(int*)current] ? PushStack(target, current) : ZERO;
//         visited[*(int*)current] = TRUE;
//     }

//     free(visited);
// }

//-----------------------------------------------------------------------------
//                                  Size Of Stack									
//                                  -------------								
//																				
// General      : The function calculates the size of the stack.									
//																				
// Parameters   :																
//      stack - The stack (In)		
//																				
// Return Value : The size of the stack.				
//																				
//-----------------------------------------------------------------------------
unsigned short SizeOfStack(Stack *stack)
{
    // Variable definition
    unsigned short size = ZERO;
    Stack temp;
    
    // Code section

    InitStack(&temp);
    CopyStack(stack, &temp);

    // Running through stack items
    while (!IsEmptyStack(&temp))
    {
        PopStack(&temp);
        size++;
    }

    return (size);
}

//-----------------------------------------------------------------------------
//                                  Min In Stack									
//                                  ------------								
//																				
// General      : The function finds the min value in the stack.									
//																				
// Parameters   :																
//      stack - The stack (In)											
//																				
// Return Value : The min value found.				
//																				
//-----------------------------------------------------------------------------
// STACK_TYPE MinInStack(Stack *stack)
// {
//     // Variable definition
//     Stack temp;
//     STACK_TYPE min;
//     STACK_TYPE current;

//     // Code section

//     InitStack(&temp);
//     CopyStack(stack, &temp);
//     current = min = PopStack(&temp);

//     // Running through stack items
//     while (!IsEmptyStack(&temp))
//     {
//         current = PopStack(&temp);
//         min = MIN(min, current);
//     }

//     return min;
// }

//-----------------------------------------------------------------------------
//                                  Split Stack									
//                                  -----------									
//																				
// General      : The function splits a stack into two stacks according
//                to given condition.									
//																				
// Parameters   :																
//      stack  - The source stack (In)									
//      stack1 - The first part (Out)									
//      stack2 - The second part(Out)
//      Condition - The condition to split according to
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
void SplitStack(Stack *stack, Stack *stack1, Stack *stack2, BOOL(*Condition)(STACK_TYPE current, STACK_TYPE previous))
{
    // Variable definition
    STACK_TYPE current;
    STACK_TYPE prev;

    // Code section

    // Running through stack items
    while (!IsEmptyStack(stack))
    {
        prev = current;
        current = PopStack(stack);
        Condition(current, prev) ? PushStack(stack1, current) : PushStack(stack2, current);
    }
}

//-----------------------------------------------------------------------------
//                                  Print Stack									
//                                  -----------									
//																				
// General      : The function prints a stack.									
//																				
// Parameters   :																
//      stack - The stack (In)											
//																				
// Return Value : None.				
//																				
//-----------------------------------------------------------------------------
// void PrintStack(Stack *stack)
// {
//     Stack temp;
//     STACK_TYPE *item;

//     InitStack(&temp);

//     while (!IsEmptyStack(stack))
//     {
//         item = PopStack(stack);
//         PushStack(&temp, item);
//         printf("%c->", *(char*)item);
//     }

//     puts("|");

//     while (!IsEmptyStack(&temp))
//     {
//         PushStack(stack, PopStack(&temp));
//     }
// }

//-----------------------------------------------------------------------------
//                                  Equal Stacks									
//                                  ------------								
//																				
// General      : The function checks whether two stacks are equal.									
//																				
// Parameters   :																
//      first   - The first stack (In)									
//      second  - The second stack (In)												
//																				
// Return Value : Whether the stack are eual.				
//																				
//-----------------------------------------------------------------------------
// BOOL EqualStacks(Stack *first, Stack *second)
// {
//     while (!IsEmptyStack(first) && PopStack(first) == PopStack(second));

//     return (IsEmptyStack(first) && IsEmptyStack(second));
// }