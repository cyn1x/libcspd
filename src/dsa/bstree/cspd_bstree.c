#define CSPD_EXPORTS

#include "cspd_bstree.h"
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
static void balance(cspd_bstree *bstree, cspd_bstnode *root, cspd_bstnode *node,
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

void cspd_bstree_init(cspd_bstree *bstree, usize data_size)
{
    bstree->root      = NULL;
    bstree->data_size = data_size;
}

cspd_bstnode *cspd_bstree_add(cspd_bstree *bstree, void *data)
{
    cspd_bstnode *node = new_node(data, bstree->data_size);

    if (bstree->root == NULL) {
        bstree->root = node;

        return bstree->root;
    }

    cspd_bstnode *leaf = bstree->root;

    (void)leaf;

    return node;
}

void cspd_bstree_clear(cspd_bstree *bstree)
{
    recursive_delete(bstree->root);

    bstree->root      = NULL;
    bstree->data_size = 0;
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

static void balance(cspd_bstree *bstree, cspd_bstnode *root, cspd_bstnode *node,
                    cspd_cmp cmp)
{
    int result = cmp(root->data, node->data);

    // TODO: #0008 - Binary search tree implementation

    (void)result;
    (void)bstree;
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
