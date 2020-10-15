#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

#define true 1
#define false 0
/*
 * If the key type changes, the following comparison functions should be changed:
 */

 /**
  * Return 1(true) if key1 > key2, 0 if key1 <= key2
  * @param key1 First key
  * @param key2 Second key
  * @return 1(true) if key1 > key2, 0 if key1 <= key2
  */
 int bst_isKeyAbove(BstKey key1, BstKey key2) {
     return key1 > key2 ? 1 : 0;
 }

/**
* Return 1(true) if key1 < key2, 0 if key1 >= key2
* @param key1 First key
* @param key2 Second key
* @return 1(true) if key1 < key2, 0 if key1 >= key2
*/
int bst_isKeyBelow(BstKey key1, BstKey key2) {
    return key1 < key2 ? 1 : 0;
}


/**
* Return 1(true) if key1 == key2, 0 if key1 != key2
* @param key1 First key
* @param key2 Second key
* @return 1(true) if key1 == key2, 0 if key1 != key2
*/
int bst_isKeyEquals(BstKey key1, BstKey key2) {
    return key1 == key2 ? 1 : 0;
}


/**
 * Returns a pointer to a node with a specific key.
 * @param root - Pointer to the root of the tree
 * @param key - Specific key.
 * @return pointer to a node with a specific key.
 */
TreeNode* bst_getPointerByKey(TreeNode *root, BstKey key) {
    TreeNode *tmp = root;
    while(tmp) {
        if(bst_isKeyEquals(key, tmp->info.key)) {
            return tmp;
        }
        if(bst_isKeyAbove(key, tmp->info.key)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }

    return NULL;
}

/**
 * Creating the item of the binary search tree and getting its address
 * @param parent - Pointer to the parent of the leaf of the tree
 * @param key - Key of the item being created
 * @param data - The data element of the tree being created
 * @return addres of created tree item
 */
TreeNode* bts_createItem(TreeNode* parent, BstKey key, BstValue data) {
    TreeData treeData;

    treeData.value = data;
    treeData.key = key;

    TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
    node->info = treeData;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
}

/**
 * Creating the root of the binary search tree and getting its address
 * @param rootData
 * @param key - Root key
 * @return address of root
 */
TreeNode* bst_create(BstKey key, NodeInfo rootData) {
    bts_createItem(NULL, key, rootData);
}


/**
 * Inserts the necessary data with a specific id into the binary search tree
 * @note - If the key already exists, its value is replaced with a new one.
 * @param root - Pointer to the root of the tree
 * @param key - insert item key
 * @param data - insert item data
 */
void bst_insert(TreeNode *root, BstKey key, NodeInfo data) {
    TreeNode *tmp = root;
    while(tmp) {

        // IF KEY > TMP->INFO.KEY:
        if(bst_isKeyAbove(key, tmp->info.key)) {
            if(tmp->right == NULL) {
                tmp->right = bts_createItem(tmp, key, data);
                return;
            }
            tmp = tmp->right;

            // ELSE IF KEY < TMP->INFO.KEY
        } else if(bst_isKeyBelow(key, tmp->info.key)){
            if(tmp->left == NULL) {
                tmp->left = bts_createItem(tmp, key, data);
                return;
            }
            tmp = tmp->left;
        } else {
            tmp->info.value = data;
            return;
        }
    }
}

/**
 * Returns 1(true) if the tree contains the specified key, otherwise - 0(false)
 * @param root -  Pointer to the root of the tree
 * @param key - key whose presence in this map is to be tested
 * @return 1(true) if this tree contains the specified key
 */
int bst_containsKey(TreeNode *root, BstKey key) {
    return bst_getPointerByKey(root, key) == NULL ? false : true;
}

/**
 * Returns the value associated with the key in the tree.
 * @param root - Pointer to the root of the tree
 * @param key - The key whose associated value is to be found.
 * @warning Before calling, you need to check the existence of a key through bst_containsKey(TreeNode *root, BstKey key). In case of an invalid key, the program will be urgently completed with the code -1
 * @return - Value associated with the key in the tree.
 */
BstValue bst_find(TreeNode *root, BstKey key) {

    TreeNode *tmp = root;

    while(tmp) {
        if(bst_isKeyEquals(key, tmp->info.key)) {
            return tmp->info.value;
        }
        if(bst_isKeyAbove(key, tmp->info.key)) {
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        }
    }

    exit(-1);
}

/**
 * Searches for a node with a maximum key
 * @param root - Pointer to the root of the tree
 * @return Pointer to the node with maximum key
 */
TreeNode *getMaxNode(TreeNode *root) {
    TreeNode *tmp = root;
    while (tmp->right) {
        tmp = tmp->right;
    }
    return tmp;
}

/**
 * Searches for a node with a minimum key
 * @param root
 * @return Pointer to the node with minumum key
 */
TreeNode *getMinNode(TreeNode *root) {
    TreeNode *tmp = root;
    while (tmp->left) {
        tmp = tmp->left;
    }
    return tmp;
}

/**
 * Searches for a node with a maximum key and return the value of this key
 * @param root - Pointer to the root of the tree
 * @return Pointer to the value with maximum key
 */
BstValue bst_findMax(TreeNode *root){
    return getMaxNode(root)->info.value;
}

/**
 * Searches for a node with a minimum key and return the value of this key
 * @param root - Pointer to the root of the tree
 * @return Pointer to the value with minimum key
 */
BstValue bst_findMin(TreeNode *root){
    return getMinNode(root)->info.value;
}

/**
 * Removes the node with the specified address.
 * @param node - address of node
 */
void bst_removeByPointer(TreeNode* node) {
    if (node->left && node->right) {
        TreeNode *localMax = getMaxNode(node->left);
        node->info = localMax->info;
        bst_removeByPointer(localMax);
        return;
    } else if (node->left) {
        if (node == node->parent->left) {
            node->parent->left = node->left;
        } else {
            node->parent->right = node->left;
        }
    } else if (node->right) {
        if (node == node->parent->right) {
            node->parent->right = node->right;
        } else {
            node->parent->left = node->right;
        }
    } else {
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
    }
    free(node);
}

/**
 * Removes a node at the specified address and all children of this node.
 * @param node Node address (pointer)
 */
void bst_removeByPointerWithChilds(TreeNode *node) {
    if(node == NULL) {
        return;
    }
    bst_removeByPointerWithChilds(node->left);
    bst_removeByPointerWithChilds(node->right);
    if(node->parent != NULL)
        bst_removeByPointer(node);
    free(node);
}

/**
 * Removes the node with the specified key.
 * @param root - Pointer to the root of the tree
 * @param key - The key to which the node is attached, which must be removed
 * @warning Cannot delete root
 */
void bst_remove(TreeNode *root, BstKey key) {
    TreeNode *target = bst_getPointerByKey(root, key);
    if(target == root) exit(-1);

    bst_removeByPointer(target);
}

/**
 * Removes a node at the specified key and all children of this node.
 * @param root - Pointer to the root of the tree
 * @param key - The key to which the node is attached, which must be removed
 */
void bst_removeWithChilds(TreeNode *root, BstKey key) {
    TreeNode *node = bst_getPointerByKey(root, key);
    node->parent = NULL;
    bst_removeByPointerWithChilds(node);
}

/**
 * Complete tree removal
 * @param root - Pointer to the root of the tree
 */
void bst_removeTree(TreeNode **root) {
    bst_removeByPointerWithChilds((*root));
    (*root) = NULL;
}

/**
 * Iteration of tree output
 * @param item - Pointer to the item
 * @param iteration - iteration number
 */
void bst_outIter(TreeNode *item, int iteration) {
    for(int i = 0; i <= iteration; i++) {
        printf(" ");
    }
    printf("%d : %d\n", item->info.key, item->info.value);
    if(item->right != NULL) bst_outIter(item->right, iteration + 1);
    if(item->left != NULL) bst_outIter(item->left, iteration + 1);
}

/**
 * Tree output
 * @param root - Pointer to the root of the tree
 */
void bst_output(TreeNode *root) {
    bst_outIter(root, 0);
}