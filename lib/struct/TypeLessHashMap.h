#ifndef UNITTESTINGC_TYPELESSHASHMAP_H
#define UNITTESTINGC_TYPELESSHASHMAP_H

#include <stdlib.h>


#define __DEFAULT_SALT_HASH 5381

struct HashMap;

struct HashMapLibrary
{
    /** Create a new HashMap with {size} buckets */
    struct HashMap* (* new)(size_t size);
    /** Add a pair of {key: value} to the HashMap */
    size_t (* put)(struct HashMap* hm, char* key, void* value);
    /** Return the value associated with the {key} */
    void* (* get)(struct HashMap* hm, char* key);
    /** Return the value associated with the {index} */
    void* (* iter)(struct HashMap* hm, size_t index);
    /** Remove the {key: value} pair from the HashMap */
    size_t (* remove)(struct HashMap* hm, char* key);
    /** Free the HashMap, return NULL */
    void* (* free)(struct HashMap* hm);
    /** Display the HashMap */
    void (* display)(struct HashMap* hm);
    void (* info)(struct HashMap* hm);
    size_t (* capacity)(struct HashMap* hm);
    size_t (* size)(struct HashMap* hm);
};

extern const struct HashMapLibrary HashMap;

#endif //UNITTESTINGC_TYPELESSHASHMAP_H
