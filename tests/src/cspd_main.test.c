#include "cspd_dsa.test.h"
#include "cspd_sys.test.h"
// #include <log.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    // TODO: 0020 - Dependency management
    // log_init(LOG_TRACE, stdout, NULL);

    /* DSA tests */
    cspd_bst_test();
    cspd_bintree_test();
    cspd_list_test();
    cspd_queue_test();
    cspd_stack_test();
    cspd_string_test();
    cspd_vector_test();

    /* Sys tests */
    cspd_path_test();

    // TODO: 0021 - Display test results

    return 0;
}
