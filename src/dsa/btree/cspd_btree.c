#define CSPD_EXPORTS

#include "cspd_btree.h"
#include "cspd_mem.h"

static void recursive_delete(cspd_btnode *node);
static void delete_node(cspd_btnode *node);

void        cspd_btree_init(cspd_btree *btree, size_t data_size)
{
    btree->root      = NULL;
    btree->data_size = data_size;
}

static cspd_btnode *btnode_init(void *data, size_t data_size)
{
    cspd_btnode *node = cspd_malloc(sizeof(cspd_btnode));

    node->data        = cspd_malloc(data_size);
    node->left        = NULL;
    node->right       = NULL;

    memcpy(node->data, data, data_size);

    return node;
}

cspd_btnode *cspd_btree_add(cspd_btree *btree, cspd_btnode **leaf, void *data)
{
    cspd_btnode *node = btnode_init(data, btree->data_size);

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

cspd_btnode *cspd_btree_insert(cspd_btree *btree, cspd_btnode **parent,
                               void *data)
{
    (void)parent;
    (void)data;

    cspd_queue queue_t;
    cspd_queue_init(&queue_t, sizeof(cspd_btnode *));
    cspd_queue_enqueue(&queue_t, &btree->root);
    cspd_llnode *curr = queue_t.front;

    while (curr) {
        cspd_btnode *btnode = *(cspd_btnode **)curr->data;
        cspd_btnode *left   = btnode->left;
        cspd_btnode *right  = btnode->right;

        if (btnode == (*parent)) {

            cspd_btnode *new_node = btnode_init(data, btree->data_size);

            if (!left) {
                (*parent)->left = new_node;
            } else if (!right) {
                (*parent)->right = new_node;
            } else {
                // Insert left by default if parent has two children
                new_node->left  = btnode->left;
                (*parent)->left = new_node;
            }
            cspd_queue_clear(&queue_t);

            return new_node;
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

void cspd_btree_preorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_vector_push(vec, &node);

    cspd_btree_preorder(node->left, vec);
    cspd_btree_preorder(node->right, vec);
}

void cspd_btree_inorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_btree_inorder(node->left, vec);
    cspd_vector_push(vec, &node);
    cspd_btree_inorder(node->right, vec);
}

void cspd_btree_postorder(cspd_btnode *node, cspd_vector *vec)
{
    if (!node) {
        return;
    }

    cspd_btree_inorder(node->left, vec);
    cspd_btree_inorder(node->right, vec);
    cspd_vector_push(vec, &node);
}

void cspd_btree_dfs(cspd_btnode *node, cspd_vector *vec)
{
    cspd_btree_preorder(node, vec);
}

void cspd_btree_bfs(cspd_btnode *node, cspd_queue *queue_t)
{
    cspd_queue_enqueue(queue_t, &node);

    cspd_llnode *curr = queue_t->front;

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

void cspd_btree_invert(cspd_btnode *node)
{
    if (node == NULL) {
        return;
    }

    cspd_btree_invert(node->left);
    cspd_btree_invert(node->right);

    cspd_btnode *tmp = node->left;
    node->left       = node->right;
    node->right      = tmp;
}

int32 cspd_btree_height(cspd_btnode *node)
{
    if (node == NULL) {
        return -1;
    }

    int lh = cspd_btree_height(node->left);
    int rh = cspd_btree_height(node->right);

    return (lh > rh ? lh : rh) + 1;
}

size_t cspd_btree_count(cspd_btnode *node)
{
    cspd_vector vec;
    cspd_vector_init(&vec, sizeof(cspd_btnode *));
    cspd_btree_preorder(node, &vec);

    size_t size = vec.size;
    cspd_vector_clear(&vec);

    return size;
}

void cspd_btree_clear(cspd_btree *btree)
{
    recursive_delete(btree->root);

    btree->root      = NULL;
    btree->data_size = 0;
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
