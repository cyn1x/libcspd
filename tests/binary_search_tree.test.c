#include "binary_search_tree.test.h"
#include "types.h"
#include <assert.h>
#include <binary_search_tree.h>
#include <print.h>

#ifdef __clang__
static void print_data(void *data) __attribute__((unused));
#endif /* ifdef __clang__ */

static void print_data(void *data)
{
    printf("{ ");
    print(*(int32 *)data, " ");
    printf("} \n");
}

void bstree_setup(void)
{
    //! [Adding nodes]
    bstree_t bstree;

    bstree_init(&bstree, sizeof(int32));

    int32 a = 3;
    int32 b = 1;
    int32 c = 7;
    int32 d = 2;
    int32 e = 4;
    int32 f = 6;
    int32 g = 5;

    //               (4)
    //         /--------------\
    //        |               |
    //      (2)              (6)
    //   /-------\        /-------\
    //  |        |       |        |
    // (1)      (3)     (5)      (7)

    bstree_add(&bstree, &a);
    // bstree_add(&bstree, &b);
    // bstree_add(&bstree, &c);
    // bstree_add(&bstree, &d);
    // bstree_add(&bstree, &e);
    // bstree_add(&bstree, &f);
    // bstree_add(&bstree, &g);

    //! [Adding nodes]
}

void bstree_test(void) {}
