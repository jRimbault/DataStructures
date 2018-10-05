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


struct Array* _newEmpty()
{
    struct Array* new = calloc(1, sizeof(struct Array));
    new->size = ARRAY_STARTING_SIZE;
    new->length = 0;
    new->values = calloc(ARRAY_STARTING_SIZE, sizeof(long));
    return new;
}


struct Array* newEmptyArray(long size)
{
    struct Array* new = calloc(1, sizeof(struct Array));
    new->size = getStartSize(size);
    new->length = 0;
    new->values = calloc(new->size, sizeof(long));
    return new;
}


struct Array* newArray(const long* values, long length)
{
    struct Array* new = newEmptyArray(getStartSize(length));
    new->length = length;
    for (int i = 0; i < length; i += 1) {
        new->values[i] = values[i];
    }
    return new;
}


void freeArray(struct Array* a)
{
    free(a->values);
    free(a);
}


long* copyArray(struct Array* array, size_t size)
{
    long* copy = calloc(size, sizeof(long));
    for (long i = 0; i < array->length; i += 1) {
        copy[i] = array->values[i];
    }
    return copy;
}


struct Array* expand(struct Array* array)
{
    struct Array* new = newArray(array->values, array->size);
    freeArray(array);
    return new;
}


struct Array* add(struct Array* a, long n)
{
    if (a->length == a->size) {
        a = expand(a);
    }
    a->values[a->length] = n;
    a->length += 1;
    return a;
}


struct Array* clone(struct Array* a)
{
    return newArray(a->values, a->length);
}


struct Array* merge(struct Array* a, struct Array* b)
{
    struct Array* new = newEmptyArray(a->length + b->length);
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


struct Array* subArray(struct Array* a, long i, long j)
{
    long length = j - i;
    struct Array* new = newEmptyArray(length);
    memcpy(new->values, &a->values[i], length * sizeof(long));
    new->length = length;
    return new;
}


struct Array* sort(struct Array* a)
{
    if (a->length < 2) return a;

    struct Array* half1 = subArray(a, 0, a->length / 2);
    struct Array* half2 = subArray(a, a->length / 2, a->length);

    a = merge(sort(half1), sort(half2));
    freeArray(half1);
    freeArray(half2);
    return a;
}


struct Array* forEach(struct Array* a, long (* fun)(long))
{
    for (long i = 0; i < a->length; i += 1) {
        a->values[i] = fun(a->values[i]);
    }
    return a;
}


long reduce(struct Array* a, long (* reducer)(long, long), long b)
{
    long r = b;
    for (long i = 0; i < a->length; i += 1) {
        r = reducer(a->values[i], r);
    }
    return r;
}


const struct ArrayLibrary Array = {
    .empty = _newEmpty,
    .new = newArray,
    .push = add,
    .clone = clone,
    .forEach = forEach,
    .reduce = reduce,
    .merge = merge,
    .subArray = subArray,
    .sort = sort,
    .free = freeArray,
};
