#include "cspd_dsa.test.h"
#include "cspd_types.h"
#include <cspd_assert.h>
#include <cspd_bst.h>
#include <cspd_print.h>

/******************************************************************************
 * Helper Declarations
 *****************************************************************************/

static cspd_bst tb_setup(void);

/******************************************************************************
 * Test Declarations
 *****************************************************************************/

static void test_bst_init(void);
static void test_bst_add(void);
static void test_bst_clear(void);

/******************************************************************************
 * Test Runner
 *****************************************************************************/

void cspd_bst_test(void)
{
    test_bst_init();
    test_bst_add();
}

/******************************************************************************
 * Test Definitions
 *****************************************************************************/

static void test_bst_init(void)
{
    cspd_bst bst;
    cspd_bst_init(&bst, sizeof(i32));

    cspd_assert(bst.data_size == sizeof(i32));
    cspd_assert(bst.root == NULL);

    cspd_bst_clear(&bst);
}

void test_bst_add(void)
{
    //! [Adding nodes]
    // cspd_bst bst;

    // cspd_bst_init(&bst, sizeof(i32));

    // i32 a = 3;
    // i32 b = 1;
    // i32 c = 7;
    // i32 d = 2;
    // i32 e = 4;
    // i32 f = 6;
    // i32 g = 5;

    //                  (4)
    //          +--------+--------+
    //          |                 |
    //         (2)               (6)
    //      +---+---+       +-----+-----+
    //      |       |       |           |
    //     (1)     (3)     (5)         (7)

    // cspd_bst_add(&bst, &a);
    // cspd_bst_add(&bst, &b);
    // cspd_bst_add(&bst, &c);
    // cspd_bst_add(&bst, &d);
    // cspd_bst_add(&bst, &e);
    // cspd_bst_add(&bst, &f);
    // cspd_bst_add(&bst, &g);

    //! [Adding nodes]
}

/******************************************************************************
 * Helper Definitions
 *****************************************************************************/

static cspd_bst tb_setup(void)
{
    cspd_bst bst;
    cspd_bst_init(&bst, sizeof(i32));

    i32 v[]         = {3, 1, 7, 2, 4, 6, 5};

    cspd_bstnode *a = cspd_bst_add(&bst, &v[0]);
    cspd_bstnode *b = cspd_bst_add(&bst, &v[1]);
    cspd_bstnode *c = cspd_bst_add(&bst, &v[2]);
    cspd_bst_add(&bst, &v[3]);
    cspd_bst_add(&bst, &v[4]);
    cspd_bstnode *f = cspd_bst_add(&bst, &v[5]);
    cspd_bstnode *g = cspd_bst_add(&bst, &v[6]);
    cspd_bst_add(&bst, &v[7]);

    (void)a;
    (void)b;
    (void)c;
    (void)f;
    (void)g;

    return bst;
}
