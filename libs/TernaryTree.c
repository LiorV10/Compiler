// TernaryTree.c

#include "TernaryTree.h"

//-----------------------------------------------------------------------------
//                                  Make Ternary Tree									
//                                  -----------------									
//																				
// General      : The function makes a new ternary tree root.									
//																				
// Parameters   :																
//      manager - The manager of the tree (In)											
//																				
// Return Value : None.				
//-----------------------------------------------------------------------------
// T(n) = d														
//-----------------------------------------------------------------------------
void MakeTernaryTree(TernaryTreeNode **manager)
{
    // Code section

    *manager = malloc(sizeof(TernaryTreeNode));
    (*manager)->wordData = NULL;
    (*manager)->leftSubTree = NULL;
    (*manager)->middleSubTree = NULL;
    (*manager)->rightSubTree = NULL;
}

//-----------------------------------------------------------------------------
//                                  Set Left Ternary Tree									
//                                  ---------------------									
//																				
// General      : The function sets the left child of a given ternary tree root.									
//																				
// Parameters   :																
//      root - The ternary tree root (In)												
//																				
// Return Value : The left child.				
//-----------------------------------------------------------------------------
// T(n) = d														
//-----------------------------------------------------------------------------
TernaryTreeNode* SetLeftTernaryTree(TernaryTreeNode *root)
{
    // Code section

    MakeTernaryTree(&root->leftSubTree);

    return (root->leftSubTree);
}

//-----------------------------------------------------------------------------
//                                  Set Middle Ternary Tree									
//                                  -----------------------									
//																				
// General      : The function sets the middle child of a given ternary tree root.									
//																				
// Parameters   :																
//      root - The ternary tree root (In)												
//																				
// Return Value : The middle child.				
//-----------------------------------------------------------------------------
// T(n) = d														
//-----------------------------------------------------------------------------
TernaryTreeNode* SetMiddleTernaryTree(TernaryTreeNode *root)
{
    // Code section

    MakeTernaryTree(&root->middleSubTree);

    return (root->middleSubTree);
}

//-----------------------------------------------------------------------------
//                                  Set Right Ternary Tree									
//                                  ----------------------								
//																				
// General      : The function sets the right child of a given ternary tree root.									
//																				
// Parameters   :																
//      root - The ternary tree root (In)												
//																				
// Return Value : The right child.				
//-----------------------------------------------------------------------------
// T(n) = d														
//-----------------------------------------------------------------------------
TernaryTreeNode* SetRightTernaryTree(TernaryTreeNode *root)
{
    // Code section

    MakeTernaryTree(&root->rightSubTree);

    return (root->rightSubTree);
}

//-----------------------------------------------------------------------------
//                                  Is Leaf Trenary Tree									
//                                  --------------------									
//																				
// General      : The function determines whether a give ternary tree node
//                is a leaf.									
//																				
// Parameters   :																
//      node - The ternary tree node (In)												
//																				
// Return Value : Whether the given node is a leaf.				
//-----------------------------------------------------------------------------
// T(n) = d																	
//-----------------------------------------------------------------------------
BOOL IsLeafTernaryTree(TernaryTreeNode *node)
{
    // Code section

    return (!node->leftSubTree && !node->rightSubTree && !node->middleSubTree);
}

void InsertToTernarySearchTree(TernaryTreeNode **root, char *word, void *wordData)
{
    if (!*word)
    {
        (*root)->wordData = wordData;
        return;
    }

    !*root ? MakeTernaryTree(root), (*root)->info = *word : ZERO;

    if (*word != (*root)->info)
    {
        root = *word < (*root)->info ? &(*root)->leftSubTree : &(*root)->rightSubTree;
        InsertToTernarySearchTree(root, word, wordData);
    }
	else 
    {
        root = *(word + ONE) ? &(*root)->middleSubTree : root;
        InsertToTernarySearchTree(root, word + ONE, wordData);
	}
}

void *SerchInTernarySearchTree(TernaryTreeNode *root, char *word)
{
    if (!root)
    {
        return NULL;
    }

    if (*word != root->info)
    {
        root = *word > root->info ? root->rightSubTree : root->leftSubTree;
        return SerchInTernarySearchTree(root, word);
    }
    else
    {
        return *(++word) ? SerchInTernarySearchTree(root->middleSubTree, word) : root->wordData;
    }
}

void EmptyTernarySearchTree(TernaryTreeNode *root)
{
    if (!root)
    {
        return;
    }

    EmptyTernarySearchTree(root->rightSubTree);
    EmptyTernarySearchTree(root->middleSubTree);
    EmptyTernarySearchTree(root->leftSubTree);
    free(root);
}