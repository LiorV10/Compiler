// TernaryTree.h

#define _TERNARY_TREE_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "CommonMacros.h"
#endif

typedef struct TernaryTreeNode
{
    char info;
    void *wordData;
    struct TernaryTreeNode *leftSubTree;
    struct TernaryTreeNode *middleSubTree;
    struct TernaryTreeNode *rightSubTree;
} TernaryTreeNode;

void MakeTernaryTree(TernaryTreeNode **manager);
TernaryTreeNode* SetLeftTernaryTree(TernaryTreeNode *root);
TernaryTreeNode* SetMiddleTernaryTree(TernaryTreeNode *root);
TernaryTreeNode* SetRightTernaryTree(TernaryTreeNode *root);
BOOL IsLeafTernaryTree(TernaryTreeNode *node);
void InsertToTernarySearchTree(TernaryTreeNode **root, char *word, void *wordData);
void *SerchInTernarySearchTree(TernaryTreeNode *root, char *word);
void EmptyTernarySearchTree(TernaryTreeNode *root);