#define CSPD_EXPORTS

#include "cspd_bintree.h"
#include "cspd_mem.h"

/**
 * @internal
 *
 * @brief Creates a new binary tree node.
 *
 * Creates a new binary tree node by allocating memory for the data before
 * copying it to memory. Memory also allocated for the node itself, with its
 * `left` and `right` pointers set to `NULL`.
 *
 * @param data The data to be copied to the new node.
 * @param data_size The size in bytes of the data type.
 *
 * @returns New binary tree node.
 */
static cspd_btnode *new_node(void *data, usize data_size);

/**
 * @internal
 *
 * @brief Recursively deletes all nodes from the binary tree.
 *
 * Recursively deletes all nodes from the given node. All nodes are deleted
 * using depth-first search, where the nodes will be deleted from the
 * bottom-up.
 *
 * @param node Pointer to the node to recursively delete.
 */
static void recursive_delete(cspd_btnode *node);

/**
 * @internal
 *
 * @brief Deletes a node from the binary tree.
 *
 * Deletes a node from the binary tree after setting the node's `left` and
 * `right` pointers to `NULL`.
 *
 * @param node
 */
static void delete_node(cspd_btnode *node);

void cspd_bintree_init(cspd_bintree *bintree, usize data_size)
{
    bintree->root      = NULL;
    bintree->data_size = data_size;
}

cspd_btnode *cspd_bintree_add(cspd_bintree *bintree, cspd_btnode **leaf,
                              void *data)
{
    cspd_btnode *node = new_node(data, bintree->data_size);

    if (bintree->root == NULL) {
        bintree->root = node;

        return bintree->root;
    }

    if (*leaf != NULL) {
        // TODO: handle overwrite violation
        delete_node(node);
        return NULL;
    }

    *leaf = node;

    return node;
}

cspd_btnode *cspd_bintree_insert(cspd_bintree *bintree, cspd_btnode **parent,
                                 void *data)
{
    (void)parent;
    (void)data;

    cspd_queue queue_t;
    cspd_queue_init(&queue_t, sizeof(cspd_btnode *));
    cspd_queue_enqueue(&queue_t, &bintree->root);
    cspd_lnode *curr = queue_t.front;

    while (curr) {
        cspd_btnode *btnode = *(cspd_btnode **)curr->data;
        cspd_btnode *left   = btnode->left;
        cspd_btnode *right  = btnode->right;

        if (btnode == (*parent)) {

            cspd_btnode *node = new_node(data, bintree->data_size);

            if (!left) {
                (*parent)->left = node;
            } else if (!right) {
                (*parent)->right = node;
            } else {
                // Insert left by default if parent has two children
                node->left      = btnode->left;
                (*parent)->left = node;
            }
            cspd_queue_clear(&queue_t);

            return node;
        }

        if (left) {
            cspd_queue_enqueue(&queue_t, &left);
        }
        if (right) {
            cspd_queue_enqueue(&queue_t, &right);
        }

        curr = curr->next;
    }

    cspd_queue_clear(&queue_t);

    return NULL;
}

void cspd_bintree_preorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_vector_push(vec, &node);

    cspd_bintree_preorder(node->left, vec);
    cspd_bintree_preorder(node->right, vec);
}

void cspd_bintree_inorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_bintree_inorder(node->left, vec);
    cspd_vector_push(vec, &node);
    cspd_bintree_inorder(node->right, vec);
}

void cspd_bintree_postorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_bintree_postorder(node->left, vec);
    cspd_bintree_postorder(node->right, vec);
    cspd_vector_push(vec, &node);
}

void cspd_bintree_dfs(cspd_btnode *node, cspd_vector *vec)
{
    cspd_bintree_preorder(node, vec);
}

void cspd_bintree_bfs(cspd_btnode *node, cspd_queue *queue_t)
{
    cspd_queue_enqueue(queue_t, &node);

    cspd_lnode *curr = queue_t->front;

    while (curr) {
        cspd_btnode *btnode = *(cspd_btnode **)curr->data;
        cspd_btnode *left   = btnode->left;
        cspd_btnode *right  = btnode->right;

        if (left) {
            cspd_queue_enqueue(queue_t, &left);
        }
        if (right) {
            cspd_queue_enqueue(queue_t, &right);
        }

        curr = curr->next;
    }
}

void cspd_bintree_invert(cspd_btnode *node)
{
    if (node == NULL) {
        return;
    }

    cspd_bintree_invert(node->left);
    cspd_bintree_invert(node->right);

    cspd_btnode *tmp = node->left;
    node->left       = node->right;
    node->right      = tmp;
}

i32 cspd_bintree_height(cspd_btnode *node)
{
    if (node == NULL) {
        return -1;
    }

    int lh = cspd_bintree_height(node->left);
    int rh = cspd_bintree_height(node->right);

    return (lh > rh ? lh : rh) + 1;
}

usize cspd_bintree_count(cspd_btnode *node)
{
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(cspd_btnode *));
    cspd_bintree_preorder(node, &vec);

    usize size = vec.size;
    cspd_vector_clear(&vec);

    return size;
}

void cspd_bintree_clear(cspd_bintree *bintree)
{
    recursive_delete(bintree->root);

    bintree->root      = NULL;
    bintree->data_size = 0;
}

static cspd_btnode *new_node(void *data, usize data_size)
{
    cspd_btnode *node = cspd_malloc(sizeof(cspd_btnode));

    node->data        = cspd_malloc(data_size);
    node->left        = NULL;
    node->right       = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

static void recursive_delete(cspd_btnode *node)
{
    if (!node) {
        return;
    }

    recursive_delete(node->left);
    recursive_delete(node->right);

    delete_node(node);
}

static void delete_node(cspd_btnode *node)
{
    node->left  = NULL;
    node->right = NULL;
    cspd_free(node->data);
    cspd_free(node);
}
