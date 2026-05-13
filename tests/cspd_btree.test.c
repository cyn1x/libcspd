#include "cspd_btree.test.h"
#include <assert.h>
#include <cspd_btree.h>
#include <cspd_print.h>
#include <cspd_queue.h>

void       bfs_test(void);

cspd_btree cspd_btree_setup(void)
{
    //! [Adding nodes]
    cspd_btree btree;

    cspd_btree_init(&btree, sizeof(int32));

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

    cspd_btnode *node_a = cspd_btree_add(&btree, NULL, &a);
    cspd_btnode *node_b = cspd_btree_add(&btree, &node_a->left, &b);
    cspd_btnode *node_c = cspd_btree_add(&btree, &node_a->right, &c);
    cspd_btnode *node_d = cspd_btree_add(&btree, &node_b->left, &d);
    cspd_btnode *node_e = cspd_btree_add(&btree, &node_b->right, &e);
    cspd_btnode *node_f = cspd_btree_add(&btree, &node_c->left, &f);
    cspd_btnode *node_g = cspd_btree_add(&btree, &node_c->right, &g);
    cspd_btnode *node_h = cspd_btree_add(&btree, &node_f->left, &h);
    cspd_btnode *node_i = cspd_btree_add(&btree, &node_f->right, &i);
    cspd_btnode *node_j = cspd_btree_add(&btree, &node_g->left, &j);
    cspd_btnode *node_k = cspd_btree_add(&btree, &node_g->left, &k);
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

void cspd_btree_test(void)
{
    cspd_btree btree = cspd_btree_setup();

    //! [Retrieving node count]
    size_t count = cspd_btree_count(btree.root);
    assert(count == 10);
    //! [Retrieving node count]

    {
        //! [Preorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_btree_preorder(btree.root, &vec);

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 0);
        assert(*(int32 *)node->data == 7);

        // cspd_print_btree(int32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        cspd_vector_clear(&vec);
        //! [Preorder traversal]
    }

    {
        //! [Inorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_btree_inorder(btree.root, &vec);

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 0);
        assert(*(int32 *)node->data == 8);

        // cspd_print_btree(int32, &vec);
        // Output: { 8 23 14 7 6 1 2 5 15 9 }

        cspd_vector_clear(&vec);
        //! [Inorder traversal]
    }

    {
        //! [Postorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_btree_postorder(btree.root, &vec);

        // cspd_print_btree(int32, &vec);
        // Output: { 8 23 14 6 1 2 5 15 9 7 }

        cspd_vector_clear(&vec);
        //! [Postorder traversal]
    }

    {
        //! [Depth-first search]
        cspd_vector vec;
        cspd_vector_init(&vec, btree.data_size);

        cspd_btree_dfs(btree.root, &vec);

        // cspd_print_btree(int32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        cspd_vector_clear(&vec);
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

        int          data = 10;

        cspd_btnode *node =
            cspd_btree_insert(&btree, &btree.root->right, &data);
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

        cspd_btree_invert(btree.root);

        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_btree_preorder(btree.root, &vec);

        {
            cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 2);
            assert(*(int32 *)node->data == 9);
        }

        {
            cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 7);
            assert(*(int32 *)node->data == 6);
        }

        {
            cspd_btnode *node =
                *(cspd_btnode **)cspd_vector_get(&vec, vec.size - 1);
            assert(*(int32 *)node->data == 8);
        }

        // cspd_print_btree(int32, &vec);
        // Output: { 7 5 9 15 10 1 2 6 23 14 8 }

        cspd_vector_clear(&vec);
        //! [Inversion]
    }

    //! [Calculating height]
    uint32 height = cspd_btree_height(btree.root);
    assert(height == 4);
    //! [Calculating height]

    //! [Clearing the tree]
    cspd_btree_clear(&btree);
    //! [Clearing the tree]
}

void bfs_test(void)
{
    //! [Breadth-first search]
    cspd_btree btree = cspd_btree_setup();

    {
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(cspd_btnode *));

        cspd_btree_bfs(btree.root, &queue);

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 7);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 23);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 5);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 8);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 14);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 1);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 9);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 6);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 2);
            cspd_queue_deque(&queue);
        }

        {
            cspd_btnode *btnode = *(cspd_btnode **)cspd_queue_peek(&queue);
            assert(*(int32 *)btnode->data == 15);
            cspd_queue_deque(&queue);
        }

        cspd_queue_clear(&queue);
        cspd_btree_clear(&btree);
    }
    //! [Breadth-first search]
}
