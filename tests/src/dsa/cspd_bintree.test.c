#include "cspd_dsa.test.h"
#include <cspd_assert.h>
#include <cspd_bintree.h>
#include <cspd_print.h>
#include <cspd_queue.h>
#include <cspd_types.h>
#include <cspd_vector.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

/* Verifies a vector of node pointers holds the expected values in order. */
#define tb_expect_vec(TYPE, VEC, ARR)                                          \
    do {                                                                       \
        const cspd_vector *_v = (VEC);                                         \
        const TYPE        *_e = (ARR);                                         \
        usize              _n = sizeof(ARR) / sizeof((ARR)[0]);                \
                                                                               \
        cspd_assert(_v->data_size == sizeof(cspd_btnode *));                   \
        cspd_assert(_v->size == _n);                                           \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_btnode *_node = *(cspd_btnode **)cspd_vector_get(_v, _i);     \
            cspd_assert(_node != NULL);                                        \
            cspd_assert(*(TYPE *)_node->data == _e[_i]);                       \
        }                                                                      \
    } while (0)

/* Verifies a queue of node pointers holds the expected values front to back
 * without modifying the queue. */
#define tb_expect_queue(TYPE, QUEUE, ARR)                                      \
    do {                                                                       \
        const cspd_queue *_q = (QUEUE);                                        \
        const TYPE       *_e = (ARR);                                          \
        usize             _n = sizeof(ARR) / sizeof((ARR)[0]);                 \
        const cspd_lnode *_c = _q->front;                                      \
                                                                               \
        for (usize _i = 0; _i < _n; ++_i) {                                    \
            cspd_assert(_c != NULL);                                           \
            cspd_btnode *_node = *(cspd_btnode **)_c->data;                    \
            cspd_assert(*(TYPE *)_node->data == _e[_i]);                       \
            _c = _c->next;                                                     \
        }                                                                      \
        cspd_assert(_c == NULL);                                               \
    } while (0)

/* Verifies the shape of a tree with unique values by comparing both its
 * preorder and inorder traversals, which together identify the tree. */
#define tb_expect_tree(TYPE, ROOT, PRE, IN)                                    \
    do {                                                                       \
        cspd_vector _pv;                                                       \
        cspd_vector _iv;                                                       \
                                                                               \
        cspd_vector_init(&_pv, sizeof(cspd_btnode *));                         \
        cspd_vector_init(&_iv, sizeof(cspd_btnode *));                         \
                                                                               \
        cspd_bintree_preorder((ROOT), &_pv);                                   \
        cspd_bintree_inorder((ROOT), &_iv);                                    \
                                                                               \
        tb_expect_vec(TYPE, &_pv, PRE);                                        \
        tb_expect_vec(TYPE, &_iv, IN);                                         \
                                                                               \
        cspd_vector_clear(&_pv);                                               \
        cspd_vector_clear(&_iv);                                               \
    } while (0)

/* Verifies a tree matches the one built by `tb_setup()`. */
#define tb_expect_base(ROOT)                                                   \
    do {                                                                       \
        i32 _pre[] = {7, 23, 8, 14, 5, 1, 6, 2, 9, 15};                        \
        i32 _ino[] = {8, 23, 14, 7, 6, 1, 2, 5, 15, 9};                        \
        tb_expect_tree(i32, ROOT, _pre, _ino);                                 \
    } while (0)

static cspd_bintree tb_setup(void);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_bintree_init(void);
static void test_bintree_add(void);
static void test_bintree_insert(void);
static void test_bintree_preorder(void);
static void test_bintree_inorder(void);
static void test_bintree_postorder(void);
static void test_bintree_dfs(void);
static void test_bintree_bfs(void);
static void test_bintree_invert(void);
static void test_bintree_height(void);
static void test_bintree_count(void);
static void test_bintree_clear(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/
void cspd_bintree_test(void)
{
    test_bintree_init();
    test_bintree_add();
    test_bintree_insert();
    test_bintree_preorder();
    test_bintree_inorder();
    test_bintree_postorder();
    test_bintree_dfs();
    test_bintree_bfs();
    test_bintree_invert();
    test_bintree_height();
    test_bintree_count();
    test_bintree_clear();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_bintree_init(void)
{
    cspd_bintree bintree;
    cspd_bintree_init(&bintree, sizeof(i32));

    cspd_assert(bintree.data_size == sizeof(i32));
    cspd_assert(bintree.root == NULL);

    cspd_bintree_clear(&bintree);
}

static void test_bintree_add(void)
{
    {
        //! [Adding nodes]
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));

        i32 a = 7;
        i32 b = 23;
        i32 c = 5;
        i32 d = 8;
        i32 e = 14;
        i32 f = 1;
        i32 g = 9;
        i32 h = 6;
        i32 i = 2;
        i32 j = 15;
        i32 k = 4;

        //                  (7)
        //          +--------+--------+
        //          |                 |
        //        (23)               (5)
        //      +---+---+       +-----+-----+
        //      |       |       |           |
        //     (8)    (14)     (1)         (9)
        //                    +--+--+      +
        //                    |     |      |
        //                   (6)   (2)    (15)

        cspd_btnode *node_a = cspd_bintree_add(&bintree, NULL, &a);
        cspd_btnode *node_b = cspd_bintree_add(&bintree, &node_a->left, &b);
        cspd_btnode *node_c = cspd_bintree_add(&bintree, &node_a->right, &c);
        cspd_bintree_add(&bintree, &node_b->left, &d);
        cspd_bintree_add(&bintree, &node_b->right, &e);
        cspd_btnode *node_f = cspd_bintree_add(&bintree, &node_c->left, &f);
        cspd_btnode *node_g = cspd_bintree_add(&bintree, &node_c->right, &g);
        cspd_bintree_add(&bintree, &node_f->left, &h);
        cspd_bintree_add(&bintree, &node_f->right, &i);
        cspd_bintree_add(&bintree, &node_g->left, &j);

        // Adding a node to an occupied leaf is not valid and returns `NULL`
        cspd_btnode *node_k = cspd_bintree_add(&bintree, &node_g->left, &k);
        cspd_assert(node_k == NULL);
        //! [Adding nodes]

        cspd_assert(bintree.root == node_a);
        cspd_assert(cspd_bintree_count(bintree.root) == 10);
        tb_expect_base(bintree.root);

        cspd_bintree_clear(&bintree);
    }

    /* Edge cases */
    {
        // Edge case: first node becomes the root
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));

        i32          a    = 1;
        cspd_btnode *root = cspd_bintree_add(&bintree, NULL, &a);

        cspd_assert(root != NULL && bintree.root == root);
        cspd_assert(root->left == NULL && root->right == NULL);
        cspd_assert(*(i32 *)root->data == 1);

        // The node owns a copy of the data
        cspd_assert(root->data != &a);

        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: occupied leaf leaves the tree unchanged
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));

        i32 a             = 1;
        i32 b             = 2;
        i32 c             = 3;

        cspd_btnode *root = cspd_bintree_add(&bintree, NULL, &a);
        cspd_btnode *left = cspd_bintree_add(&bintree, &root->left, &b);
        cspd_btnode *dup  = cspd_bintree_add(&bintree, &root->left, &c);

        cspd_assert(dup == NULL);
        cspd_assert(root->left == left);
        cspd_assert(*(i32 *)left->data == 2);
        cspd_assert(cspd_bintree_count(bintree.root) == 2);

        cspd_bintree_clear(&bintree);
    }
}

static void test_bintree_insert(void)
{
    {
        cspd_bintree bintree = tb_setup();

        //! [Insertion]

        //                  (7)
        //          +--------+--------+
        //          |                 |
        //        (23)               (5)
        //      +---+---+       +-----+-----+
        //      |       |       |           |
        //     (8)    (14)     (10)        (9)
        //                     +            +
        //                     |            |
        //                    (1)          (15)
        //                  +--+--+
        //                  |     |
        //                 (6)   (2)

        i32          data = 10;
        cspd_btnode *node =
            cspd_bintree_insert(&bintree, &bintree.root->right, &data);

        cspd_assert(node != NULL);
        cspd_assert(bintree.root->right->left == node);
        cspd_assert(node->left != NULL && *(i32 *)node->left->data == 1);
        //! [Insertion]

        i32 pre[] = {7, 23, 8, 14, 5, 10, 1, 6, 2, 9, 15};
        i32 ino[] = {8, 23, 14, 7, 6, 1, 2, 10, 5, 15, 9};
        tb_expect_tree(i32, bintree.root, pre, ino);

        cspd_bintree_clear(&bintree);
    }

    /* Edge cases */
    {
        // Edge case: parent without children, new node becomes `left`
        cspd_bintree bintree = tb_setup();

        i32          data    = 99;
        cspd_btnode *node =
            cspd_bintree_insert(&bintree, &bintree.root->left->left, &data);

        cspd_assert(node != NULL);
        cspd_assert(bintree.root->left->left->left == node);
        cspd_assert(bintree.root->left->left->right == NULL);

        i32 pre[] = {7, 23, 8, 99, 14, 5, 1, 6, 2, 9, 15};
        i32 ino[] = {99, 8, 23, 14, 7, 6, 1, 2, 5, 15, 9};
        tb_expect_tree(i32, bintree.root, pre, ino);

        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: parent with one child, new node takes the free `right`
        cspd_bintree bintree = tb_setup();

        i32          data    = 99;
        cspd_btnode *node =
            cspd_bintree_insert(&bintree, &bintree.root->right->right, &data);

        cspd_assert(node != NULL);
        cspd_assert(bintree.root->right->right->right == node);
        cspd_assert(*(i32 *)bintree.root->right->right->left->data == 15);

        i32 pre[] = {7, 23, 8, 14, 5, 1, 6, 2, 9, 15, 99};
        i32 ino[] = {8, 23, 14, 7, 6, 1, 2, 5, 15, 9, 99};
        tb_expect_tree(i32, bintree.root, pre, ino);

        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: parent does not belong to the tree
        cspd_bintree bintree = tb_setup();

        cspd_btnode  stray   = {0};
        cspd_btnode *parent  = &stray;
        i32          data    = 99;

        cspd_assert(cspd_bintree_insert(&bintree, &parent, &data) == NULL);
        tb_expect_base(bintree.root);

        cspd_bintree_clear(&bintree);
    }
}

static void test_bintree_preorder(void)
{
    cspd_bintree bintree = tb_setup();

    {
        //! [Preorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_preorder(bintree.root, &vec);

        // cspd_print_bintree(i32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 0);
        cspd_assert(*(i32 *)node->data == 7);
        //! [Preorder traversal]

        i32 expected[] = {7, 23, 8, 14, 5, 1, 6, 2, 9, 15};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: subtree
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_preorder(bintree.root->left, &vec);

        i32 expected[] = {23, 8, 14};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: NULL node
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_preorder(NULL, &vec);

        cspd_assert(vec.size == 0);

        cspd_vector_clear(&vec);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_inorder(void)
{
    cspd_bintree bintree = tb_setup();

    {
        //! [Inorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_inorder(bintree.root, &vec);

        // cspd_print_bintree(i32, &vec);
        // Output: { 8 23 14 7 6 1 2 5 15 9 }

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_get(&vec, 0);
        cspd_assert(*(i32 *)node->data == 8);
        //! [Inorder traversal]

        i32 expected[] = {8, 23, 14, 7, 6, 1, 2, 5, 15, 9};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: subtree
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_inorder(bintree.root->left, &vec);

        i32 expected[] = {8, 23, 14};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: NULL node
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_inorder(NULL, &vec);

        cspd_assert(vec.size == 0);

        cspd_vector_clear(&vec);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_postorder(void)
{
    cspd_bintree bintree = tb_setup();

    {
        //! [Postorder traversal]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_postorder(bintree.root, &vec);

        // cspd_print_bintree(i32, &vec);
        // Output: { 8 14 23 6 2 1 15 9 5 7 }

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_back(&vec);
        cspd_assert(*(i32 *)node->data == 7);
        //! [Postorder traversal]

        i32 expected[] = {8, 14, 23, 6, 2, 1, 15, 9, 5, 7};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: subtree
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_postorder(bintree.root->left, &vec);

        i32 expected[] = {8, 14, 23};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    {
        // Edge case: NULL node
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_postorder(NULL, &vec);

        cspd_assert(vec.size == 0);

        cspd_vector_clear(&vec);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_dfs(void)
{
    cspd_bintree bintree = tb_setup();

    {
        //! [Depth-first search]
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_dfs(bintree.root, &vec);

        // cspd_print_bintree(i32, &vec);
        // Output: { 7 23 8 14 5 1 6 2 9 15 }

        cspd_btnode *node = *(cspd_btnode **)cspd_vector_front(&vec);
        cspd_assert(*(i32 *)node->data == 7);
        //! [Depth-first search]

        i32 expected[] = {7, 23, 8, 14, 5, 1, 6, 2, 9, 15};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    /* Edge cases */
    {
        // Edge case: subtree
        cspd_vector vec;
        cspd_vector_init(&vec, sizeof(cspd_btnode *));

        cspd_bintree_dfs(bintree.root->right, &vec);

        i32 expected[] = {5, 1, 6, 2, 9, 15};
        tb_expect_vec(i32, &vec, expected);

        cspd_vector_clear(&vec);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_bfs(void)
{
    {
        cspd_bintree bintree = tb_setup();

        //! [Breadth-first search]
        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(cspd_btnode *));

        cspd_bintree_bfs(bintree.root, &queue);

        // Output: { 7 23 5 8 14 1 9 6 2 15 }

        i32 expected[] = {7, 23, 5, 8, 14, 1, 9, 6, 2, 15};
        for (usize i = 0; i < 10; ++i) {
            cspd_btnode *node = *(cspd_btnode **)cspd_queue_peek(&queue);
            cspd_assert(*(i32 *)node->data == expected[i]);
            cspd_queue_deque(&queue);
        }

        cspd_assert(queue.front == NULL);
        //! [Breadth-first search]

        cspd_queue_clear(&queue);
        cspd_bintree_clear(&bintree);
    }

    /* Edge cases */
    {
        // Edge case: queue contents are intact before any dequeue
        cspd_bintree bintree = tb_setup();

        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(cspd_btnode *));

        cspd_bintree_bfs(bintree.root, &queue);

        i32 expected[] = {7, 23, 5, 8, 14, 1, 9, 6, 2, 15};
        tb_expect_queue(i32, &queue, expected);

        cspd_queue_clear(&queue);
        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: subtree
        cspd_bintree bintree = tb_setup();

        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(cspd_btnode *));

        cspd_bintree_bfs(bintree.root->left, &queue);

        i32 expected[] = {23, 8, 14};
        tb_expect_queue(i32, &queue, expected);

        cspd_queue_clear(&queue);
        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: single node
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));

        i32 a = 1;
        cspd_bintree_add(&bintree, NULL, &a);

        cspd_queue queue;
        cspd_queue_init(&queue, sizeof(cspd_btnode *));

        cspd_bintree_bfs(bintree.root, &queue);

        i32 expected[] = {1};
        tb_expect_queue(i32, &queue, expected);

        cspd_queue_clear(&queue);
        cspd_bintree_clear(&bintree);
    }
}

static void test_bintree_invert(void)
{
    {
        cspd_bintree bintree = tb_setup();

        //! [Inversion]

        //                  (7)
        //          +--------+--------+
        //          |                 |
        //        (23)               (5)
        //      +---+---+       +-----+-----+
        //      |       |       |           |
        //     (8)    (14)     (1)         (9)
        //                    +--+--+      +
        //                    |     |      |
        //                   (6)   (2)    (15)

        cspd_bintree_invert(bintree.root);

        //                  (7)
        //          +--------+--------+
        //          |                 |
        //         (5)              (23)
        //      +---+------+       +--+--+
        //      |          |       |     |
        //     (9)        (1)    (14)   (8)
        //       +      +--+--+
        //       |      |     |
        //     (15)    (2)   (6)

        cspd_assert(*(i32 *)bintree.root->left->data == 5);
        cspd_assert(*(i32 *)bintree.root->right->data == 23);
        //! [Inversion]

        i32 pre[] = {7, 5, 9, 15, 1, 2, 6, 23, 14, 8};
        i32 ino[] = {9, 15, 5, 2, 1, 6, 7, 14, 23, 8};
        tb_expect_tree(i32, bintree.root, pre, ino);

        cspd_bintree_clear(&bintree);
    }

    /* Edge cases */
    {
        // Edge case: inverting twice restores the tree
        cspd_bintree bintree = tb_setup();

        cspd_bintree_invert(bintree.root);
        cspd_bintree_invert(bintree.root);

        tb_expect_base(bintree.root);

        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: subtree
        cspd_bintree bintree = tb_setup();

        cspd_bintree_invert(bintree.root->left);

        i32 pre[] = {7, 23, 14, 8, 5, 1, 6, 2, 9, 15};
        i32 ino[] = {14, 23, 8, 7, 6, 1, 2, 5, 15, 9};
        tb_expect_tree(i32, bintree.root, pre, ino);

        cspd_bintree_clear(&bintree);
    }

    {
        // Edge case: NULL node
        cspd_bintree_invert(NULL);
    }

    {
        // Edge case: leaf node
        cspd_bintree bintree = tb_setup();

        cspd_bintree_invert(bintree.root->left->left);

        tb_expect_base(bintree.root);

        cspd_bintree_clear(&bintree);
    }
}

static void test_bintree_height(void)
{
    cspd_bintree bintree = tb_setup();

    //! [Calculating height]

    //                7(3)
    //          +-------+-------+
    //          |               |
    //        23(1)           5(2)
    //       +--+--+        +--+--+
    //       |     |        |     |
    //     8(0)  14(0)    1(1)   9(1)
    //                   +--+--+   +
    //                   |     |   |
    //                 6(0)  2(0) 15(0)

    i32 height = cspd_bintree_height(bintree.root);
    cspd_assert(height == 3);
    //! [Calculating height]

    cspd_assert(cspd_bintree_height(bintree.root->left) == 1);
    cspd_assert(cspd_bintree_height(bintree.root->right) == 2);

    /* Edge cases */
    {
        // Edge case: leaf node
        cspd_assert(cspd_bintree_height(bintree.root->left->left) == 0);
    }

    {
        // Edge case: NULL node
        cspd_assert(cspd_bintree_height(NULL) == -1);
    }

    {
        // Edge case: height grows after an insertion
        i32 data = 10;
        cspd_bintree_insert(&bintree, &bintree.root->right, &data);

        cspd_assert(cspd_bintree_height(bintree.root) == 4);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_count(void)
{
    cspd_bintree bintree = tb_setup();

    //! [Retrieving node count]
    usize count = cspd_bintree_count(bintree.root);

    cspd_assert(count == 10);
    //! [Retrieving node count]

    /* Edge cases */
    {
        // Edge case: subtrees
        cspd_assert(cspd_bintree_count(bintree.root->left) == 3);
        cspd_assert(cspd_bintree_count(bintree.root->right) == 6);
    }

    {
        // Edge case: leaf node
        cspd_assert(cspd_bintree_count(bintree.root->left->left) == 1);
    }

    {
        // Edge case: NULL node
        cspd_assert(cspd_bintree_count(NULL) == 0);
    }

    cspd_bintree_clear(&bintree);
}

static void test_bintree_clear(void)
{
    {
        cspd_bintree bintree = tb_setup();

        cspd_bintree_clear(&bintree);

        cspd_assert(bintree.root == NULL);
        cspd_assert(bintree.data_size == 0);
    }

    /* Edge cases */
    {
        // Edge case: empty tree
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));
        cspd_bintree_clear(&bintree);

        cspd_assert(bintree.root == NULL);
    }

    {
        // Edge case: single node
        cspd_bintree bintree;
        cspd_bintree_init(&bintree, sizeof(i32));

        i32 a = 1;
        cspd_bintree_add(&bintree, NULL, &a);
        cspd_bintree_clear(&bintree);

        cspd_assert(bintree.root == NULL);
    }
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_bintree tb_setup(void)
{
    cspd_bintree bintree;
    cspd_bintree_init(&bintree, sizeof(i32));

    i32 v[]        = {7, 23, 5, 8, 14, 1, 9, 6, 2, 15};

    cspd_btnode *a = cspd_bintree_add(&bintree, NULL, &v[0]);
    cspd_btnode *b = cspd_bintree_add(&bintree, &a->left, &v[1]);
    cspd_btnode *c = cspd_bintree_add(&bintree, &a->right, &v[2]);
    cspd_bintree_add(&bintree, &b->left, &v[3]);
    cspd_bintree_add(&bintree, &b->right, &v[4]);
    cspd_btnode *f = cspd_bintree_add(&bintree, &c->left, &v[5]);
    cspd_btnode *g = cspd_bintree_add(&bintree, &c->right, &v[6]);
    cspd_bintree_add(&bintree, &f->left, &v[7]);
    cspd_bintree_add(&bintree, &f->right, &v[8]);
    cspd_bintree_add(&bintree, &g->left, &v[9]);

    return bintree;
}
