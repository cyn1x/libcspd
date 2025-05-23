#define LIBCSPD_EXPORTS

#include "binary_search_tree.h"
#include <stdlib.h>
#include <string.h>

void balance(bstree_t *bstree, bstnode_t *root, bstnode_t *node);

void bstree_init(bstree_t *bstree, size_t data_size)
{
    bstree->root      = NULL;
    bstree->data_size = data_size;
}

static bstnode_t *bstnode_init(void *data, size_t data_size)
{
    bstnode_t *node = malloc(sizeof(bstnode_t));

    node->data      = malloc(sizeof(data_size));
    node->left      = NULL;
    node->right     = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

bstnode_t *bstree_add(bstree_t *bstree, void *data)
{
    bstnode_t *node = bstnode_init(data, bstree->data_size);

    if (bstree->root == NULL) {
        bstree->root = node;

        return bstree->root;
    }

    bstnode_t *leaf = bstree->root;

    return node;
}

void balance(bstree_t *bstree, bstnode_t *root, bstnode_t *node)
{
    int cmp = bstree->_cmp(root->data, node->data);

    // TODO: implementation
}
