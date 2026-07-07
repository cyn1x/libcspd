#include "cspd_bstree.test.h"
#include "cspd_types.h"
#include <assert.h>
#include <cspd_bstree.h>
#include <cspd_print.h>

void bstree_setup(void)
{
    //! [Adding nodes]
    cspd_bstree bstree;

    cspd_bstree_init(&bstree, sizeof(i32));

    i32 a = 3;
    i32 b = 1;
    i32 c = 7;
    i32 d = 2;
    i32 e = 4;
    i32 f = 6;
    i32 g = 5;

    //               (4)
    //         /--------------\
    //        |               |
    //      (2)              (6)
    //   /-------\        /-------\
    //  |        |       |        |
    // (1)      (3)     (5)      (7)

    cspd_bstree_add(&bstree, &a);
    // cspd_bstree_add(&bstree, &b);
    // cspd_bstree_add(&bstree, &c);
    // cspd_bstree_add(&bstree, &d);
    // cspd_bstree_add(&bstree, &e);
    // cspd_bstree_add(&bstree, &f);
    // cspd_bstree_add(&bstree, &g);

    //! [Adding nodes]
}

void cspd_bstree_test(void) {}
