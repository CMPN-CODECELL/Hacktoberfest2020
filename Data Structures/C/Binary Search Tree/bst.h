
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

typedef union NodeInfo {
    int intValue;
    char *stringValue;
    double realValue;
    void *pointerValue;
} NodeInfo;

typedef int BstKey;
typedef NodeInfo BstValue;

typedef struct TreeData {
    BstKey key;
    BstValue value;
} TreeData;

typedef struct TreeNode {
    TreeData info;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

TreeNode* bst_create(BstKey key, NodeInfo rootData);

void bst_insert(TreeNode *root, BstKey key, BstValue data);

BstValue bst_find(TreeNode *root, BstKey key);

BstValue bst_findMax(TreeNode *root);

BstValue bst_findMin(TreeNode *rooy);

void bst_remove(TreeNode *root, BstKey key);

void bst_removeWithChilds(TreeNode *root, BstKey key);

void bst_removeTree(TreeNode **root);

int bst_containsKey(TreeNode *root, BstKey key);

void bst_output(TreeNode *root);

#endif //BINARYSEARCHTREE_H
