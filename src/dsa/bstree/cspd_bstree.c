#define CSPD_EXPORTS

#include "cspd_bstree.h"
#include "cspd_mem.h"
#include <string.h>

static void balance(cspd_bstree *bstree, cspd_bstnode *root,
                    cspd_bstnode *node);

void        cspd_bstree_init(cspd_bstree *bstree, size_t data_size)
{
    bstree->root      = NULL;
    bstree->data_size = data_size;
}

static cspd_bstnode *cspd_bstnode_init(void *data, size_t data_size)
{
    cspd_bstnode *node = cspd_malloc(sizeof(cspd_bstnode));

    node->data         = cspd_malloc(sizeof(data_size));
    node->left         = NULL;
    node->right        = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

cspd_bstnode *cspd_bstree_add(cspd_bstree *bstree, void *data)
{
    cspd_bstnode *node = cspd_bstnode_init(data, bstree->data_size);

    if (bstree->root == NULL) {
        bstree->root = node;

        return bstree->root;
    }

    cspd_bstnode *leaf = bstree->root;

    return node;
}

static void balance(cspd_bstree *bstree, cspd_bstnode *root, cspd_bstnode *node)
{
    int cmp = bstree->_cmp(root->data, node->data);

    // TODO: implementation
}
