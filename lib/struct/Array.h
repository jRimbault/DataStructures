#ifndef UNITTESTINGC_ARRAY_H
#define UNITTESTINGC_ARRAY_H

#include <stdlib.h>


#define ARRAY_STARTING_SIZE 1024

struct Array {
    long* values;
    long length;
    size_t size;
};


struct ArrayLibrary {
    /**
     * Make a new empty Array
     */
    struct Array* (* empty)();
    /**
     * Make a new Array structure
     */
    struct Array* (* new)(const long*, long);
    /**
     * Add one element to the array
     */
    struct Array* (* push)(struct Array*, long);
    /**
     * Remove the last element from the array
     */
    struct Array* (* pop)(struct Array*);
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
    struct Array* (* subArray)(struct Array*, long, long);
    /**
     * Free allocated memory
     */
    void (* free)(struct Array*);
};


extern const struct ArrayLibrary Array;

#endif //UNITTESTINGC_ARRAY_H
