#include "cspd_integration.test.h"
#include <assert.h>
#include <cspd_vector.h>
#include <stdlib.h>
#include <string.h>

// Declare generic vector type
cspd_vector_declare(i32, i32);

static void vector_test(void);
static void linked_list_test(void);
static void queue_test(void);
static void stack_test(void);
static void binary_tree_test(void);

#pragma pack(4)
typedef struct node_t
{
    int   value;
    void *data;
} node;

typedef struct data_t
{
    void *value;
} data;

void cspd_integration_tests(void)
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
    i32_vector vec;
    cspd_vector_init(&vec,
                     sizeof(node *)); // Store pointers instead of full structs

    // Allocate data_t dynamically
    data *test_data  = malloc(sizeof(data));

    int   a          = 4;
    test_data->value = malloc(sizeof(int));
    memcpy(test_data->value, &a, sizeof(int));

    // Allocate test_t dynamically
    node *test_node  = malloc(sizeof(node));
    test_node->value = 1;
    test_node->data  = test_data; // Assign the pointer directly

    cspd_vector_push(&vec, &test_node); // Store the pointer, not a copy

    // Retrieve
    void *result      = cspd_vector_get(&vec, 0);
    node *test_result = *(node **)result; // Dereference to get node pointer
    data *data_result = test_result->data;
    int   value       = *(int *)data_result->value;

    assert(value == 4);

    // Cleanup
    free(test_data->value);
    free(test_data);
    free(test_node);

    cspd_vector_clear(&vec);
    //! [Vector usage with custom data types]
}

static void linked_list_test(void) {}

static void queue_test(void) {}

static void stack_test(void) {}

static void binary_tree_test(void) {}
