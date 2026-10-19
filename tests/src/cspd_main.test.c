#include "cspd_dsa.test.h"
// #include <log.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // TODO: 0020 - Dependency management
    // log_init(LOG_TRACE, stdout, NULL);

    cspd_bstree_test();
    cspd_btree_test();
    cspd_list_test();
    cspd_queue_test();
    cspd_stack_test();
    cspd_string_test();
    cspd_vector_test();

    // TODO: 0021 - Display test results

    return 0;
}
