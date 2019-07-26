#ifndef UNITTESTINGC_VECSTRING_H
#define UNITTESTINGC_VECSTRING_H

#include <stdlib.h>

#include "../String.h"

typedef struct cstring cstring;

struct VecString;

struct VecStringLibrary
{
    /**
     * Make a new empty Array
     */
    struct VecString* (* empty)();
    /**
     * Make a new Array structure
     */
    struct VecString* (* new)(cstring**, size_t);
    /**
     * Add one element to the array
     */
    struct VecString* (* add)(struct VecString*, cstring*);
    /**
     * Clone array
     */
    struct VecString* (* clone)(struct VecString*);
    /**
     * Return part of the array
     */
    struct VecString* (* subArray)(struct VecString*, size_t, size_t);
    /**
     * Get array size
     */
    size_t (* size)(struct VecString*);
    /**
     * Get item at index
     */
    cstring* (* get)(struct VecString*, size_t);
    /**
     * Free allocated memory
     */
    void (* free)(struct VecString*);
};

extern const struct VecStringLibrary VecString;

#endif //UNITTESTINGC_VECSTRING_H
