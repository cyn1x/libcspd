#include "binary_tree.test.h"
#include <assert.h>
#include <binary_tree.h>
#include <print.h>
#include <queue.h>

void      bfs_test(void);

bintree_t bintree_setup(void)
{
    //! [Adding nodes]
    bintree_t btree;

    bintree_init(&btree, sizeof(int32));

    int32 a = 7;
    int32 b = 23;
    int32 c = 5;
    int32 d = 8;
    int32 e = 14;
    int32 f = 1;
    int32 g = 9;
    int32 h = 6;
    int32 i = 2;
    int32 j = 15;
    int32 k = 4;

    //                  (7)
    //         /--------------------\
    //        |                     |
    //      (23)                   (5)
    //   /-------\           /-------------\
    //  |        |          |              |
    // (8)     (14)        (1)            (9)
    //                   /-----\        /
    //                  |      |       |
    //                 (6)    (2)    (15)

    btnode_t *node_a = bintree_add(&btree, NULL, &a);
    btnode_t *node_b = bintree_add(&btree, &node_a->left, &b);
    btnode_t *node_c = bintree_add(&btree, &node_a->right, &c);
    btnode_t *node_d = bintree_add(&btree, &node_b->left, &d);
    btnode_t *node_e = bintree_add(&btree, &node_b->right, &e);
    btnode_t *node_f = bintree_add(&btree, &node_c->left, &f);
    btnode_t *node_g = bintree_add(&btree, &node_c->right, &g);
    btnode_t *node_h = bintree_add(&btree, &node_f->left, &h);
    btnode_t *node_i = bintree_add(&btree, &node_f->right, &i);
    btnode_t *node_j = bintree_add(&btree, &node_g->left, &j);
    btnode_t *node_k = bintree_add(&btree, &node_g->left, &k);
    assert(node_k == NULL);
    //! [Adding nodes]

    (void)node_d;
    (void)node_e;
    (void)node_f;
    (void)node_g;
    (void)node_h;
    (void)node_i;
    (void)node_j;

    return btree;
}

void binary_tree_test(void)
{
    bintree_t btree = bintree_setup();

    //! [Retrieving node count]
    size_t count = bintree_count(btree.root);
    assert(count == 10);
    //! [Retrieving node count]

    {
        //! [Preorder traversal]
        vector_t vec;
        vector_init(&vec, sizeof(btnode_t *));

        bintree_preorder(btree.root, &vec);

        btnode_t *node = *(btnode_t **)vector_get(&vec, 0);
        assert(*(int32 *)node->data == 7);

        // print_binary_tree(int32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        vector_clear(&vec);
        //! [Preorder traversal]
    }

    {
        //! [Inorder traversal]
        vector_t vec;
        vector_init(&vec, sizeof(btnode_t *));

        bintree_inorder(btree.root, &vec);

        btnode_t *node = *(btnode_t **)vector_get(&vec, 0);
        assert(*(int32 *)node->data == 8);

        // print_binary_tree(int32, &vec);
        // Output: { 8 23 14 7 6 1 2 5 15 9 }

        vector_clear(&vec);
        //! [Inorder traversal]
    }

    {
        //! [Postorder traversal]
        vector_t vec;
        vector_init(&vec, sizeof(btnode_t *));

        bintree_postorder(btree.root, &vec);

        // print_binary_tree(int32, &vec);
        // Output: { 8 23 14 6 1 2 5 15 9 7 }

        vector_clear(&vec);
        //! [Postorder traversal]
    }

    {
        //! [Depth-first search]
        vector_t vec;
        vector_init(&vec, btree.data_size);

        bintree_dfs(btree.root, &vec);

        // print_binary_tree(int32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        vector_clear(&vec);
        //! [Depth-first search]
    }

    // Breadth-first search traversal test
    bfs_test();

    {
        //! [Insertion]

        //                  (7)
        //         /--------------------\
        //        |                     |
        //      (23)                   (5)
        //   /-------\           /-------------\
        //  |        |          |              |
        // (8)     (14)       (10)            (9)
        //                    /              /
        //                   /              |
        //                 (1)            (15)
        //               /-----\
        //              |      |
        //             (6)    (2)

        int       data = 10;

        btnode_t *node = bintree_insert(&btree, &btree.root->right, &data);
        assert(node != NULL);
        //! [Insertion]
    }

    {
        //! [Inversion]

        //                      (7)
        //             /--------------------\
        //            |                     |
        //           (5)                   (23)
        //     /-------------\          /-------\
        //     |             |         |        |
        //    (9)          (10)      (14)      (8)
        //    /             /
        //   |             /
        // (15)          (1)
        //             /-----\
        //            |      |
        //           (2)    (6)

        bintree_invert(btree.root);

        vector_t vec;
        vector_init(&vec, sizeof(btnode_t *));

        bintree_preorder(btree.root, &vec);

        {
            btnode_t *node = *(btnode_t **)vector_get(&vec, 2);
            assert(*(int32 *)node->data == 9);
        }

        {
            btnode_t *node = *(btnode_t **)vector_get(&vec, 7);
            assert(*(int32 *)node->data == 6);
        }

        {
            btnode_t *node = *(btnode_t **)vector_get(&vec, vec.size - 1);
            assert(*(int32 *)node->data == 8);
        }

        // print_binary_tree(int32, &vec);
        // Output: { 7 5 9 15 10 1 2 6 23 14 8 }

        vector_clear(&vec);
        //! [Inversion]
    }

    //! [Calculating height]
    uint32 height = bintree_height(btree.root);
    assert(height == 4);
    //! [Calculating height]

    //! [Clearing the tree]
    bintree_clear(&btree);
    //! [Clearing the tree]
}

void bfs_test(void)
{
    //! [Breadth-first search]
    bintree_t btree = bintree_setup();

    {
        queue_t queue_t;
        queue_init(&queue_t, sizeof(btnode_t *));

        bintree_bfs(btree.root, &queue_t);

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 7);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 23);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 5);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 8);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 14);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 1);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 9);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 6);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 2);
            queue_deque(&queue_t);
        }

        {
            btnode_t *btnode = *(btnode_t **)queue_peek(&queue_t);
            assert(*(int32 *)btnode->data == 15);
            queue_deque(&queue_t);
        }

        queue_clear(&queue_t);
        bintree_clear(&btree);
    }
    //! [Breadth-first search]
}
