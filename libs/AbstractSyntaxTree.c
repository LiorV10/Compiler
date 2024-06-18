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
    (*root)->reg = ZERO;
    (*root)->GenerationFunction = NULL;
    (*root)->AnalysisFunction = NULL;
    (*root)->label = ZERO;
    (*root)->type = NULL;
    (*root)->lvalue = FALSE;
    (*root)->evaluateAsExpression = TRUE;
    (*root)->field = NULL;
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

void FreeNode(AbstractSyntaxTreeNode *astRoot)
{
    EmptyCircularLinearLinkedList(&astRoot->childrenManager, NULL);
    free(astRoot);
}

void FreeAbstractSyntaxTree(AbstractSyntaxTreeNode *astRoot)
{
    if (!astRoot) return;
    
    if (!astRoot->childrenManager)
    {
        FreeNode(astRoot);
        return;
    }

    CircularLinearLinkedListNode *child = astRoot->childrenManager->nextNode;

    do
    {
        FreeAbstractSyntaxTree(child->info);
        child = child->nextNode;
    } 
    while (child != astRoot->childrenManager->nextNode);
    
    FreeNode(astRoot);
}