#include "binary_tree.test.h"
#include "integration.test.h"
#include "linked_list.test.h"
#include "queue.test.h"
#include "stack.test.h"
#include "vector.test.h"
#include <log.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    log_init(LOG_TRACE, stdout, NULL);

    vector_test();
    linked_list_test();
    queue_test();
    stack_test();
    binary_tree_test();

    integration_tests();

    return 0;
}
