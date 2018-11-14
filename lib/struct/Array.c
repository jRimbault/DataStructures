#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include "Array.h"


size_t getStartSize(long count)
{
    size_t size = ARRAY_STARTING_SIZE;
    while (count > size) {
        size *= 2;
    }
    return size;
}


struct Array* array_new_empty()
{
    struct Array* new = calloc(1, sizeof(struct Array));
    new->size = ARRAY_STARTING_SIZE;
    new->length = 0;
    new->values = calloc(ARRAY_STARTING_SIZE, sizeof(long));
    return new;
}


struct Array* array_new(long size)
{
    struct Array* new = calloc(1, sizeof(struct Array));
    new->size = getStartSize(size);
    new->length = 0;
    new->values = calloc(new->size, sizeof(long));
    return new;
}


struct Array* array_new_from(const long* values, long length)
{
    struct Array* new = array_new(getStartSize(length));
    new->length = length;
    for (int i = 0; i < length; i += 1) {
        new->values[i] = values[i];
    }
    return new;
}


void array_free(struct Array* a)
{
    free(a->values);
    free(a);
}


struct Array* array_expand(struct Array* array)
{
    struct Array* new = array_new_from(array->values, array->size);
    array_free(array);
    return new;
}


struct Array* array_add(struct Array* a, long n)
{
    if (a->length == a->size) {
        a = array_expand(a);
    }
    a->values[a->length] = n;
    a->length += 1;
    return a;
}


struct Array* array_clone(struct Array* a)
{
    return array_new_from(a->values, a->length);
}


struct Array* array_merge(struct Array* a, struct Array* b)
{
    struct Array* new = array_new(a->length + b->length);
    long i = 0;
    long j = 0;
    long k = 0;

    while (i < a->length && j < b->length) {
        if (a->values[i] < b->values[j]) {
            new->values[k++] = a->values[i++];
        } else {
            new->values[k++] = b->values[j++];
        }
    }
    while (i < a->length) {
        new->values[k++] = a->values[i++];
    }
    while (j < b->length) {
        new->values[k++] = b->values[j++];
    }
    new->length = k;
    return new;
}


struct Array* array_sub_array(struct Array* a, long i, long j)
{
    long length = j - i;
    struct Array* new = array_new(length);
    memcpy(new->values, &a->values[i], length * sizeof(long));
    new->length = length;
    return new;
}


struct Array* array_sort(struct Array* a)
{
    if (a->length < 2) return a;

    struct Array* half1 = array_sub_array(a, 0, a->length / 2);
    struct Array* half2 = array_sub_array(a, a->length / 2, a->length);

    a = array_merge(array_sort(half1), array_sort(half2));
    array_free(half1);
    array_free(half2);
    return a;
}


struct Array* array_for_each(struct Array* a, long (* fun)(long))
{
    for (long i = 0; i < a->length; i += 1) {
        a->values[i] = fun(a->values[i]);
    }
    return a;
}


long array_reduce(struct Array* a, long (* reducer)(long, long), long b)
{
    long r = b;
    for (long i = 0; i < a->length; i += 1) {
        r = reducer(a->values[i], r);
    }
    return r;
}


const struct ArrayLibrary Array = {
    .empty = array_new_empty,
    .new = array_new_from,
    .push = array_add,
    .clone = array_clone,
    .forEach = array_for_each,
    .reduce = array_reduce,
    .merge = array_merge,
    .subArray = array_sub_array,
    .sort = array_sort,
    .free = array_free,
};
