#include <stdio.h>

#include "struct/Array.h"
#include "minunit.h"


#define ARRAY_STARTING_SIZE 1024


int isSorted(struct Array* a)
{
    for (long i = 1; i < a->size; i += 1) {
        if (a->values[i - 1] > a->values[i]) {
            return 0;
        }
    }
    return 1;
}


void display(struct Array* a)
{
    printf("Array{size: %ld, capacity: %zu}\n", a->size, a->capacity);
    for (long i = 0; i < a->size; i += 1) {
        printf(" %ld", a->values[i]);
    }
    printf("\n");
}


static char* should_create_standard_array()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Array* array = Array.new(values, count);
    mu_assert("array size isn't 5", array->size == count);
    mu_assert("array capacity should be 1024", array->capacity == ARRAY_STARTING_SIZE);
    Array.free(array);
    return 0;
}


static char* should_add_one_item()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Array* array = Array.new(values, count);
    Array.push(array, 6);
    mu_assert("array size isn't 6", array->size == count + 1);
    mu_assert("array capacity should be 1024", array->capacity == ARRAY_STARTING_SIZE);
    mu_assert("last element should be 6", array->values[5] == 6);
    Array.free(array);
    return 0;
}


static char* should_merge_two_arrays()
{
    size_t count1 = 5;
    long values1[] = {1, 2, 3, 4, 5};
    struct Array* array1 = Array.new(values1, count1);
    size_t count2 = 5;
    long values2[] = {6, 7, 8, 9, 10};
    struct Array* array2 = Array.new(values2, count2);
    struct Array* merge = Array.merge(array1, array2);
    Array.free(array1);
    Array.free(array2);
    mu_assert("merger should have 10 size", merge->size == count1 + count2);
    mu_assert("array capacity should be 1024", merge->capacity == ARRAY_STARTING_SIZE);
    Array.free(merge);
    return 0;
}


static char* should_get_a_sub_array()
{
    size_t count = 10;
    long values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct Array* array = Array.new(values, count);
    struct Array* sub = Array.subArray(array, 2, 7);
    int is_sub = 1;
    for (long i = 2; i < 7; i += 1) {
        if (sub->values[i - 2] != array->values[i]) { is_sub = 0; }
    }
    mu_assert("sub array should have 5 size", sub->size == 5);
    mu_assert("sub array should a copy of array[2:7]", is_sub);
    mu_assert("sub array capacity should be 1024", sub->capacity == ARRAY_STARTING_SIZE);
    Array.free(array);
    Array.free(sub);
    return 0;
}


static char* should_expand_array_fast()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Array* array = Array.new(values, count);
    struct Array* merge = Array.empty();
    for (int i = 0; i < 250; i += 1) {
        merge = Array.merge(merge, array);
    }
    mu_assert("array size isn't 1250", merge->size == 1250);
    mu_assert("array capacity should be 2048", merge->capacity == ARRAY_STARTING_SIZE * 2);
    Array.free(array);
    Array.free(merge);
    return 0;
}


static char* should_sort_two_arrays()
{
    size_t count1 = 5;
    size_t count2 = 5;
    long values1[] = {3, 2, 6, 7, 5};
    long values2[] = {3, 4, 1, 9, 10};
    struct Array* array1 = Array.new(values1, count1);
    struct Array* array2 = Array.new(values2, count2);
    struct Array* merge = Array.sort(Array.merge(array1, array2));
    Array.free(array1);
    Array.free(array2);
    mu_assert("array should have 10 size", merge->size == count1 + count2);
    mu_assert("array capacity should be 1024", merge->capacity == ARRAY_STARTING_SIZE);
    mu_assert("array should be sorted", isSorted(merge));
    Array.free(merge);
    return 0;
}


long addOne(long n)
{
    return n + 1;
}


static char* test_apply_fun()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Array* array = Array.new(values, count);
    Array.forEach(array, &addOne);
    for (long i = 0; i < count; i += 1) {
        mu_assert("value should be incremented by one", array->values[i] == values[i] + 1);
    }
    Array.free(array);
    return 0;
}


long countOdds(long i, long r)
{
    return i % 2 + r;
}


long sumAll(long i, long r)
{
    return i + r;
}


static char* test_reduce_fun()
{
    size_t count = 5;
    long values[] = {1, 2, 7, 4, 5};
    struct Array* array = Array.new(values, count);
    long odds = Array.reduce(array, &countOdds, 0);
    long sum = Array.reduce(array, &sumAll, 0);
    mu_assert("there should be 3 odds number", odds == 3);
    mu_assert("total sum should be 19", sum == 19);
    Array.free(array);
    return 0;
}


/**
 * If a test fails, its array won't be free-ed
 */
static char* all_tests()
{
    mu_run_test(should_create_standard_array);
    mu_run_test(should_add_one_item);
    mu_run_test(should_get_a_sub_array);
    mu_run_test(should_merge_two_arrays);
    mu_run_test(should_expand_array_fast);
    mu_run_test(should_sort_two_arrays);
    mu_run_test(test_apply_fun);
    mu_run_test(test_reduce_fun);
    return 0;
}


mu_run(all_tests)
