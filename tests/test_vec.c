#include <stdio.h>

#include "struct/Vec.h"
#include "minunit.h"


#define ARRAY_STARTING_SIZE 1024


int isSorted(struct Vec* a)
{
    for (size_t i = 1; i < Vec.size(a); i += 1) {
        if (Vec.get(a, i - 1) > Vec.get(a, i)) {
            return 0;
        }
    }
    return 1;
}


void display(struct Vec* a)
{
    printf("Vec{size: %ld, capacity: %zu}\n", Vec.size(a), a->capacity);
    for (size_t i = 0; i < Vec.size(a); i += 1) {
        printf(" %ld", Vec.get(a, i));
    }
    printf("\n");
}


static char* should_create_standard_array()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Vec* array = Vec.new(values, count);
    mu_assert("array size isn't 5", Vec.size(array) == count);
    mu_assert("array capacity should be 1024", array->capacity == ARRAY_STARTING_SIZE);
    Vec.free(array);
    return 0;
}


static char* should_add_one_item()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Vec* array = Vec.new(values, count);
    Vec.add(array, 6);
    mu_assert("array size isn't 6", Vec.size(array) == count + 1);
    mu_assert("array capacity should be 1024", array->capacity == ARRAY_STARTING_SIZE);
    mu_assert("last element should be 6", Vec.get(array, 5) == 6);
    Vec.free(array);
    return 0;
}


static char* should_merge_two_arrays()
{
    size_t count1 = 5;
    long values1[] = {1, 2, 3, 4, 5};
    struct Vec* array1 = Vec.new(values1, count1);
    size_t count2 = 5;
    long values2[] = {6, 7, 8, 9, 10};
    struct Vec* array2 = Vec.new(values2, count2);
    struct Vec* merge = Vec.merge(array1, array2);
    Vec.free(array1);
    Vec.free(array2);
    mu_assert("merger should have 10 size", Vec.size(merge) == count1 + count2);
    mu_assert("array capacity should be 1024", merge->capacity == ARRAY_STARTING_SIZE);
    Vec.free(merge);
    return 0;
}


static char* should_get_a_sub_array()
{
    size_t count = 10;
    long values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct Vec* array = Vec.new(values, count);
    struct Vec* sub = Vec.subArray(array, 2, 7);
    int is_sub = 1;
    for (size_t i = 2; i < 7; i += 1) {
        if (Vec.get(sub, i - 2) != Vec.get(array, i)) {
            is_sub = 0;
        }
    }
    mu_assert("sub array should have 5 size", Vec.size(sub) == 5);
    mu_assert("sub array should a copy of array[2:7]", is_sub);
    mu_assert("sub array capacity should be 1024", sub->capacity == ARRAY_STARTING_SIZE);
    Vec.free(array);
    Vec.free(sub);
    return 0;
}


static char* should_expand_array_fast()
{
    size_t count = 5;
    long values[] = {1, 2, 3, 4, 5};
    struct Vec* array = Vec.new(values, count);
    struct Vec* merge = Vec.empty();
    for (int i = 0; i < 250; i += 1) {
        merge = Vec.merge(merge, array);
    }
    mu_assert("array size isn't 1250", Vec.size(merge) == 1250);
    mu_assert("array capacity should be 2048", merge->capacity == ARRAY_STARTING_SIZE * 2);
    Vec.free(array);
    Vec.free(merge);
    return 0;
}


static char* should_sort_two_arrays()
{
    size_t count1 = 5;
    size_t count2 = 5;
    long values1[] = {3, 2, 6, 7, 5};
    long values2[] = {3, 4, 1, 9, 10};
    struct Vec* array1 = Vec.new(values1, count1);
    struct Vec* array2 = Vec.new(values2, count2);
    struct Vec* merge = Vec.sort(Vec.merge(array1, array2));
    Vec.free(array1);
    Vec.free(array2);
    mu_assert("array should have 10 size", Vec.size(merge) == count1 + count2);
    mu_assert("array capacity should be 1024", merge->capacity == ARRAY_STARTING_SIZE);
    mu_assert("array should be sorted", isSorted(merge));
    Vec.free(merge);
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
    struct Vec* array = Vec.new(values, count);
    Vec.forEach(array, &addOne);
    for (size_t i = 0; i < count; i += 1) {
        mu_assert("value should be incremented by one", Vec.get(array, i) == values[i] + 1);
    }
    Vec.free(array);
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
    struct Vec* array = Vec.new(values, count);
    long odds = Vec.reduce(array, &countOdds, 0);
    long sum = Vec.reduce(array, &sumAll, 0);
    mu_assert("there should be 3 odds number", odds == 3);
    mu_assert("total sum should be 19", sum == 19);
    Vec.free(array);
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
