#include "cspd_btree.test.h"
#include "cspd_integration.test.h"
#include "cspd_linked_list.test.h"
#include "cspd_queue.test.h"
#include "cspd_stack.test.h"
#include "cspd_vector.test.h"
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

    // TODO: #0021 - Display test results

    return 0;
}
