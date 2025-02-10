#include "linked_list.test.h"
#include "queue.test.h"
#include "vector.test.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    vector_test();
    linked_list_test();
    queue_test();

    return 0;
}
