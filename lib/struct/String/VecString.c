#include <stdlib.h>
#include <memory.h>

#include "VecString.h"
#include "../String.h"


#define ARRAY_STARTING_SIZE 1024

struct VecString
{
    cstring** values;
    size_t size;
    size_t capacity;
};


size_t getStartSize(size_t count)
{
    size_t size = ARRAY_STARTING_SIZE;
    while (count > size) {
        size *= 2;
    }
    return size;
}


struct VecString* array_new_empty()
{
    struct VecString* new = calloc(1, sizeof(struct VecString));
    new->capacity = ARRAY_STARTING_SIZE;
    new->size = 0;
    new->values = calloc(ARRAY_STARTING_SIZE, sizeof(long));
    return new;
}


struct VecString* array_new(size_t size)
{
    struct VecString* new = calloc(1, sizeof(struct VecString));
    new->capacity = getStartSize(size);
    new->size = 0;
    new->values = calloc(new->capacity, sizeof(long));
    return new;
}


struct VecString* array_new_from(cstring** values, size_t length)
{
    struct VecString* new = array_new(getStartSize(length));
    new->size = length;
    for (size_t i = 0; i < length; i += 1) {
        new->values[i] = values[i];
    }
    return new;
}


void array_free(struct VecString* a)
{
    for (size_t i = 0; i < a->size; i += 1) {
        String.free(a->values[i]);
    }
    free(a->values);
    free(a);
}


struct VecString* array_expand(struct VecString* array)
{
    struct VecString* new = array_new_from(array->values, array->capacity);
    array_free(array);
    return new;
}


struct VecString* array_add(struct VecString* a, cstring* n)
{
    if (a->size == a->capacity) {
        a = array_expand(a);
    }
    a->values[a->size] = n;
    a->size += 1;
    return a;
}


struct VecString* array_clone(struct VecString* a)
{
    return array_new_from(a->values, a->size);
}


struct VecString* array_sub_array(struct VecString* a, size_t i, size_t j)
{
    size_t length = j - i;
    struct VecString* new = array_new(length);
    memcpy(new->values, &a->values[i], length * sizeof(long));
    new->size = length;
    return new;
}


size_t array_get_size(struct VecString* array)
{
    return array->size;
}


cstring* array_get_index(struct VecString* array, size_t i)
{
    if (i >= array->size) {
        return 0;
    }
    return array->values[i];
}


const struct VecStringLibrary VecString = {
    .empty = array_new_empty,
    .new = array_new_from,
    .add = array_add,
    .clone = array_clone,
    .subArray = array_sub_array,
    .get = array_get_index,
    .size = array_get_size,
    .free = array_free,
};
