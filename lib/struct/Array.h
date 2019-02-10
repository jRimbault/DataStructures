#ifndef UNITTESTINGC_ARRAY_H
#define UNITTESTINGC_ARRAY_H

#include <stdlib.h>


struct Array
{
    long* values;
    size_t size;
    size_t capacity;
};

struct ArrayLibrary
{
    /**
     * Make a new empty Array
     */
    struct Array* (* empty)();
    /**
     * Make a new Array structure
     */
    struct Array* (* new)(const long*, size_t);
    /**
     * Add one element to the array
     */
    struct Array* (* add)(struct Array*, long);
    /**
     * Merge two Arrays together
     */
    struct Array* (* merge)(struct Array*, struct Array*);
    /**
     * Sort array
     */
    struct Array* (* sort)(struct Array*);
    /**
     * Clone array
     */
    struct Array* (* clone)(struct Array*);
    /**
     * Apply a function to each element of the array
     */
    struct Array* (* forEach)(struct Array*, long (*)(long));
    /**
    * Reduce array to one number
    */
    long (* reduce)(struct Array*, long (*)(long, long), long);
    /**
     * Return part of the array
     */
    struct Array* (* subArray)(struct Array*, size_t, size_t);
    /**
     * Get array size
     */
    size_t (* size)(struct Array*);
    /**
     * Get item at index
     */
    long (* get)(struct Array*, size_t);
    /**
     * Free allocated memory
     */
    void (* free)(struct Array*);
};

extern const struct ArrayLibrary Array;

#endif //UNITTESTINGC_ARRAY_H
