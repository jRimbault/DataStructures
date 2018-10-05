#include <memory.h>
#include <stdio.h>

#include "List.h"
#include "HashMap.h"


struct HashMap
{
    struct Link** map;
    size_t size;
    size_t capacity;
};

/** @see http://www.cse.yorku.ca/~oz/hash.html */
size_t hashcode(char* str)
{
    size_t hash = __DEFAULT_SALT_HASH;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}


size_t indexOfString(struct HashMap* hm, char* str)
{
    return hashcode(str) % hm->capacity;
}


struct HashMap* newHashMap(size_t size)
{
    struct HashMap* hm = malloc(sizeof(struct HashMap));
    hm->map = calloc(size, sizeof(struct Link*));
    hm->capacity = size;
    hm->size = 0;
    return hm;
}


void* freeHashMap(struct HashMap* hm)
{
    for (size_t i = 0; i < hm->capacity; i += 1) {
        hm->map[i] = List.free(hm->map[i]);
    }
    free(hm->map);
    free(hm);
    return NULL;
}


size_t getHashMapSize(struct HashMap* hm)
{
    return hm->size;
}


size_t getHashMapCapacity(struct HashMap* hm)
{
    return hm->capacity;
}


size_t addNewElement(struct HashMap* hm, char* key, int value)
{
    size_t index = indexOfString(hm, key);
    if (HashMap.get(hm, key)) {
        hm->map[index] = List.remove(hm->map[index], key);
        hm->size -= 1;
    }
    hm->map[index] = List.add(hm->map[index], key, value);
    hm->size += 1;
    return hm->size;
}


int getElement(struct HashMap* hm, char* key)
{
    size_t index = indexOfString(hm, key);
    struct Link* l = List.get(hm->map[index], key);
    if (!l) return 0;
    return l->value;
}


int iteratorOverMap(struct HashMap* hm, size_t index)
{
    if (index >= hm->size) return 0;
    for (size_t i = 0; i < hm->capacity; i += 1) {
        int length = List.length(hm->map[i]);
        if (index < length) {
            struct Link* link = List.getAt(hm->map[i], (int) index);
            if (!link) return 0;
            return link->value;
        }
        index -= length;
    }
    return 0;
}


size_t removeElement(struct HashMap* hm, char* key)
{
    size_t index = indexOfString(hm, key);
    if (!hm->map[index]) return hm->size;
    hm->map[index] = List.remove(hm->map[index], key);
    hm->size -= 1;
    return hm->size;
}


void hashMapInfos(struct HashMap* hm)
{
    if (!hm) return;
    fprintf(stdout, "Number of buckets : %zu\n", hm->capacity);
    fprintf(stdout, "Total number of elements : %zu\n", hm->size);
}


void displayHashMap(struct HashMap* hm)
{
    if (!hm) return;
    hashMapInfos(hm);
    for (size_t i = 0; i < hm->capacity; i += 1) {
        if (!hm->map[i]) continue;
        fprintf(stdout, " Bucket [%zu] : \n", i);
        List.display(hm->map[i]);
    }
}


const struct HashMapLibrary HashMap = {
    .new = newHashMap,
    .put = addNewElement,
    .get = getElement,
    .iter = iteratorOverMap,
    .remove = removeElement,
    .free = freeHashMap,
    .display = displayHashMap,
    .info = hashMapInfos,
    .size = getHashMapSize,
    .capacity = getHashMapCapacity,
};
