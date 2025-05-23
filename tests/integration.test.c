#include "integration.test.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

static void vector_test(void);
static void linked_list_test(void);
static void queue_test(void);
static void stack_test(void);
static void binary_tree_test(void);

#pragma pack(4)
typedef struct node
{
    int   value;
    void *data;
} node_t;

typedef struct data
{
    void *value;
} data_t;

void integration_tests(void)
{
    vector_test();
    linked_list_test();
    queue_test();
    stack_test();
    binary_tree_test();
}

static void vector_test(void)
{
    //! [Vector usage with custom data types]
    vector_t vec;
    vector_init(&vec,
                sizeof(node_t *)); // Store pointers instead of full structs

    // Allocate data_t dynamically
    data_t *data  = malloc(sizeof(data_t));

    int     value = 4;
    data->value   = malloc(sizeof(int));
    memcpy(data->value, &value, sizeof(int));

    // Allocate test_t dynamically
    node_t *test = malloc(sizeof(node_t));
    test->value  = 1;
    test->data   = data; // Assign the pointer directly

    vector_push(&vec, &test); // Store the pointer, not a copy

    // Retrieve
    void   *res       = vector_get(&vec, 0);
    node_t *test_res  = *(node_t **)res; // Dereference to get test_t pointer
    data_t *data_res  = test_res->data;
    int     res_value = *(int *)data_res->value;

    assert(res_value == 4);

    // Cleanup
    free(data->value);
    free(data);
    free(test);

    vector_clear(&vec);
    //! [Vector usage with custom data types]
}

static void linked_list_test(void) {}

static void queue_test(void) {}

static void stack_test(void) {}

static void binary_tree_test(void) {}
