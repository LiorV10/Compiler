// AbstractSyntaxTree.c

#include "AbstractSyntaxTree.h"

//-----------------------------------------------------------------------------
//                              Make Abstract Syntax Tree                                  
//                              -------------------------                                 
//                                                                             
// General      : The function makes an abstract syntax tree root.                                 
//                                                                             
// Parameters   :                                                              
//      root - The new root (Out)       
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
void MakeAbstractSyntaxTree(AbstractSyntaxTreeNode **root)
{
    *root = malloc(sizeof(AbstractSyntaxTreeNode));
    InitCircularLinearLinkedList(&(*root)->childrenManager);

    (*root)->info = NULL;
    (*root)->reg = -ONE;
    (*root)->GenerationFunction = NULL;
    (*root)->label = ZERO;
}

//-----------------------------------------------------------------------------
//                      Set Abstract Syntax Tree Node Child                                     
//                      -----------------------------------                                  
//                                                                             
// General      : The function sets a new child for the current node.                                 
//                                                                             
// Parameters   :                                                              
//      node - The AST node (In)       
//                                                                             
// Return Value : The new child.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
AbstractSyntaxTreeNode** SetAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node)
{
    node->childrenManager ?
        InsertEndCircularLinearLinkedList(&node->childrenManager) : 
        InsertLastCircularLinearLinkedList(&node->childrenManager);

    return (&node->childrenManager->info);
}

AbstractSyntaxTreeNode** SetFirstAbstractSyntaxTreeNodeChild(AbstractSyntaxTreeNode *node)
{
    InsertAfterCircularLinearLinkedList(node->childrenManager);

    return (&node->childrenManager->nextNode->info);
}