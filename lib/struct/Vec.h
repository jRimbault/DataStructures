#ifndef UNITTESTINGC_ARRAY_H
#define UNITTESTINGC_ARRAY_H

#include <stdlib.h>


struct Vec
{
    long* values;
    size_t size;
    size_t capacity;
};

struct VecLibrary
{
    /**
     * Make a new empty Array
     */
    struct Vec* (* empty)();
    /**
     * Make a new Array structure
     */
    struct Vec* (* new)(const long*, size_t);
    /**
     * Add one element to the array
     */
    struct Vec* (* add)(struct Vec*, long);
    /**
     * Merge two Arrays together
     */
    struct Vec* (* merge)(struct Vec*, struct Vec*);
    /**
     * Sort array
     */
    struct Vec* (* sort)(struct Vec*);
    /**
     * Clone array
     */
    struct Vec* (* clone)(struct Vec*);
    /**
     * Apply a function to each element of the array
     */
    struct Vec* (* forEach)(struct Vec*, long (*)(long));
    /**
    * Reduce array to one number
    */
    long (* reduce)(struct Vec*, long (*)(long, long), long);
    /**
     * Return part of the array
     */
    struct Vec* (* subArray)(struct Vec*, size_t, size_t);
    /**
     * Get array size
     */
    size_t (* size)(struct Vec*);
    /**
     * Get item at index
     */
    long (* get)(struct Vec*, size_t);
    /**
     * Free allocated memory
     */
    void (* free)(struct Vec*);
};

extern const struct VecLibrary Vec;

#endif //UNITTESTINGC_ARRAY_H
