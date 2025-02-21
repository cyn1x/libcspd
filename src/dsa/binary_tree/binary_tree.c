#define LIBCSPD_EXPORTS

#include "binary_tree.h"
#include <stdlib.h>
#include <string.h>

static void recursive_delete(btnode_t *node);
static void delete_node(btnode_t *node);

void        bintree_init(bintree *btree, size_t data_size)
{
    btree->root      = NULL;
    btree->data_size = data_size;
}

static btnode_t *btnode_init(void *data, size_t data_size)
{
    btnode_t *node = malloc(sizeof(btnode_t));

    node->data     = malloc(data_size);
    node->left     = NULL;
    node->right    = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

btnode_t *bintree_add(bintree *btree, btnode_t **leaf, void *data)
{
    btnode_t *node = btnode_init(data, btree->data_size);

    if (btree->root == NULL) {
        btree->root = node;

        return btree->root;
    }

    if (*leaf != NULL) {
        // TODO: handle overwrite violation
        delete_node(node);
        return NULL;
    }

    *leaf = node;

    return node;
}

btnode_t *bintree_insert(bintree *btree, btnode_t **parent, void *data)
{
    (void)parent;
    (void)data;
    queue queue;
    queue_init(&queue, sizeof(btnode_t *));

    queue_enqueue(&queue, &btree->root);

    lnode_t *curr = queue.front;

    while (curr) {
        btnode_t *btnode = *(btnode_t **)curr->data;
        btnode_t *left   = btnode->left;
        btnode_t *right  = btnode->right;

        if (btnode == (*parent)) {

            btnode_t *new_node = btnode_init(data, btree->data_size);

            if (!left) {
                (*parent)->left = new_node;
            } else if (!right) {
                (*parent)->right = new_node;
            } else {
                // Insert left by default if parent has two children
                new_node->left  = btnode->left;
                (*parent)->left = new_node;
            }
            queue_clear(&queue);

            return new_node;
        }

        if (left) {
            queue_enqueue(&queue, &left);
        }
        if (right) {
            queue_enqueue(&queue, &right);
        }

        curr = curr->next;
    }

    queue_clear(&queue);

    return NULL;
}

void bintree_preorder(btnode_t *node, vector *vec)
{
    if (!node) {
        return;
    }

    vector_push(vec, &node);

    bintree_preorder(node->left, vec);
    bintree_preorder(node->right, vec);
}

void bintree_inorder(btnode_t *node, vector *vec)
{
    if (!node) {
        return;
    }

    bintree_inorder(node->left, vec);
    vector_push(vec, &node);
    bintree_inorder(node->right, vec);
}

void bintree_postorder(btnode_t *node, vector *vec)
{
    if (!node) {
        return;
    }

    bintree_inorder(node->left, vec);
    bintree_inorder(node->right, vec);
    vector_push(vec, &node);
}

void bintree_dfs(btnode_t *node, vector *vec) { bintree_preorder(node, vec); }

void bintree_bfs(btnode_t *node, queue *queue)
{
    queue_enqueue(queue, &node);

    lnode_t *curr = queue->front;

    while (curr) {
        btnode_t *btnode = *(btnode_t **)curr->data;
        btnode_t *left   = btnode->left;
        btnode_t *right  = btnode->right;

        if (left) {
            queue_enqueue(queue, &left);
        }
        if (right) {
            queue_enqueue(queue, &right);
        }

        curr = curr->next;
    }
}

int32 bintree_height(btnode_t *node)
{
    if (node == NULL) {
        return -1;
    }

    int lh = bintree_height(node->left);
    int rh = bintree_height(node->right);

    return (lh > rh ? lh : rh) + 1;
}

size_t bintree_count(btnode_t *node)
{
    vector vec;
    vector_init(&vec, sizeof(btnode_t *));
    bintree_preorder(node, &vec);

    size_t size = vec.size;
    vector_clear(&vec);

    return size;
}

void bintree_clear(bintree *btree)
{
    recursive_delete(btree->root);

    btree->root      = NULL;
    btree->data_size = 0;
}

static void recursive_delete(btnode_t *node)
{
    if (!node) {
        return;
    }

    recursive_delete(node->left);
    recursive_delete(node->right);

    delete_node(node);
}

static void delete_node(btnode_t *node)
{
    node->left  = NULL;
    node->right = NULL;
    free(node->data);
    free(node);
}
