#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "Vec.h"


#define ARRAY_STARTING_SIZE 1024


size_t getStartSize(size_t count)
{
    size_t size = ARRAY_STARTING_SIZE;
    while (count > size) {
        size *= 2;
    }
    return size;
}


struct Vec* array_new_empty()
{
    struct Vec* new = calloc(1, sizeof(struct Vec));
    new->capacity = ARRAY_STARTING_SIZE;
    new->size = 0;
    new->values = calloc(ARRAY_STARTING_SIZE, sizeof(long));
    return new;
}


struct Vec* array_new(size_t size)
{
    struct Vec* new = calloc(1, sizeof(struct Vec));
    new->capacity = getStartSize(size);
    new->size = 0;
    new->values = calloc(new->capacity, sizeof(long));
    return new;
}


struct Vec* array_new_from(const long* values, size_t length)
{
    struct Vec* new = array_new(getStartSize(length));
    new->size = length;
    for (int i = 0; i < length; i += 1) {
        new->values[i] = values[i];
    }
    return new;
}


void array_free(struct Vec* a)
{
    free(a->values);
    free(a);
}


struct Vec* array_expand(struct Vec* array)
{
    struct Vec* new = array_new_from(array->values, array->capacity);
    array_free(array);
    return new;
}


struct Vec* array_add(struct Vec* a, long n)
{
    if (a->size == a->capacity) {
        a = array_expand(a);
    }
    a->values[a->size] = n;
    a->size += 1;
    return a;
}


struct Vec* array_clone(struct Vec* a)
{
    return array_new_from(a->values, a->size);
}


struct Vec* array_merge(struct Vec* a, struct Vec* b)
{
    struct Vec* new = array_new(a->size + b->size);
    long i = 0;
    long j = 0;
    size_t k = 0;

    while (i < a->size && j < b->size) {
        if (a->values[i] < b->values[j]) {
            new->values[k++] = a->values[i++];
        } else {
            new->values[k++] = b->values[j++];
        }
    }
    while (i < a->size) {
        new->values[k++] = a->values[i++];
    }
    while (j < b->size) {
        new->values[k++] = b->values[j++];
    }
    new->size = k;
    return new;
}


struct Vec* array_sub_array(struct Vec* a, size_t i, size_t j)
{
    size_t length = j - i;
    struct Vec* new = array_new(length);
    memcpy(new->values, &a->values[i], length * sizeof(long));
    new->size = length;
    return new;
}


struct Vec* array_sort(struct Vec* a)
{
    if (a->size < 2) { return a; }

    struct Vec* half1 = array_sub_array(a, 0, a->size / 2);
    struct Vec* half2 = array_sub_array(a, a->size / 2, a->size);

    a = array_merge(array_sort(half1), array_sort(half2));
    array_free(half1);
    array_free(half2);
    return a;
}


struct Vec* array_for_each(struct Vec* a, long (* fun)(long))
{
    for (long i = 0; i < a->size; i += 1) {
        a->values[i] = fun(a->values[i]);
    }
    return a;
}


long array_reduce(struct Vec* a, long (* reducer)(long, long), long b)
{
    long r = b;
    for (long i = 0; i < a->size; i += 1) {
        r = reducer(a->values[i], r);
    }
    return r;
}


size_t array_get_size(struct Vec* array)
{
    return array->size;
}


long array_get_index(struct Vec* array, size_t i)
{
    if (i >= array->size) {
        return 0;
    }
    return array->values[i];
}


const struct VecLibrary Vec = {
    .empty = array_new_empty,
    .new = array_new_from,
    .add = array_add,
    .clone = array_clone,
    .forEach = array_for_each,
    .reduce = array_reduce,
    .merge = array_merge,
    .subArray = array_sub_array,
    .sort = array_sort,
    .get = array_get_index,
    .size = array_get_size,
    .free = array_free,
};
