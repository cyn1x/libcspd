#include "binary_tree.test.h"
#include "integration.test.h"
#include "linked_list.test.h"
#include "queue.test.h"
#include "stack.test.h"
#include "vector.test.h"
// #include <log.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // TODO: #0020 - Dependency management
    // log_init(LOG_TRACE, stdout, NULL);

    cspd_vector_test();
    cspd_linked_list_test();
    cspd_queue_test();
    cspd_stack_test();
    cspd_btree_test();

    cspd_integration_tests();

    return 0;
}
