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

    return 0;
}
