#define CSPD_EXPORTS

#include "cspd_bst.h"
#include "cspd_mem.h"

/**
 * @internal
 *
 * @brief
 *
 *
 * @param
 */
static cspd_bstnode *new_node(void *data, usize data_size);

/**
 * @internal
 *
 * @brief
 *
 *
 * @param
 */
static void balance(cspd_bst *bst, cspd_bstnode *root, cspd_bstnode *node,
                    cspd_cmp cmp);

/**
 * @internal
 *
 * @brief Recursively deletes all nodes from the binary search tree.
 *
 * Recursively deletes all nodes from the given node. All nodes are deleted
 * using depth-first search, where the nodes will be deleted from the bottom-up.
 *
 * @param node Pointer to the node to recursively delete.
 */
static void recursive_delete(cspd_bstnode *node);

/**
 * @internal
 *
 * @brief Deletes a node from the binary search tree.
 *
 * Deletes a node from the binary search tree after setting the node's `left`
 * and `right` pointers to `NULL`.
 *
 * @param node
 */
static void delete_node(cspd_bstnode *node);

void cspd_bst_init(cspd_bst *bst, usize data_size)
{
    bst->root      = NULL;
    bst->data_size = data_size;
}

cspd_bstnode *cspd_bst_add(cspd_bst *bst, void *data)
{
    cspd_bstnode *node = new_node(data, bst->data_size);

    if (bst->root == NULL) {
        bst->root = node;

        return bst->root;
    }

    cspd_bstnode *leaf = bst->root;

    (void)leaf;

    return node;
}

void cspd_bst_clear(cspd_bst *bst)
{
    recursive_delete(bst->root);

    bst->root      = NULL;
    bst->data_size = 0;
}

static cspd_bstnode *new_node(void *data, usize data_size)
{
    cspd_bstnode *node = cspd_malloc(sizeof(cspd_bstnode));

    node->data         = cspd_malloc(sizeof(data_size));
    node->left         = NULL;
    node->right        = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

static void balance(cspd_bst *bst, cspd_bstnode *root, cspd_bstnode *node,
                    cspd_cmp cmp)
{
    int result = cmp(root->data, node->data);

    // TODO: #0008 - Binary search tree implementation

    (void)result;
    (void)bst;
}

static void recursive_delete(cspd_bstnode *node)
{
    if (!node) {
        return;
    }

    recursive_delete(node->left);
    recursive_delete(node->right);

    delete_node(node);
}

static void delete_node(cspd_bstnode *node)
{
    node->left  = NULL;
    node->right = NULL;
    cspd_free(node->data);
    cspd_free(node);
}
