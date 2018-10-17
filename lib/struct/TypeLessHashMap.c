#include <memory.h>
#include <stdio.h>

#include "TypeLessList.h"
#include "TypeLessHashMap.h"


struct HashMap
{
    struct List** map;
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
    hm->map = malloc(size * sizeof(struct List*));
    for (size_t i = 0; i < size; i += 1) {
        hm->map[i] = List.new();
    }
    hm->capacity = size;
    hm->size = 0;
    return hm;
}


void* freeHashMap(struct HashMap* hm)
{
    if (!hm) { return NULL; }
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


size_t addNewElement(struct HashMap* hm, char* key, void* value)
{
    if (HashMap.get(hm, key)) {
        HashMap.remove(hm, key);
    }
    size_t index = indexOfString(hm, key);
    List.add(hm->map[index], Node.new(key, value));
    hm->size += 1;
    return hm->size;
}


void* getElement(struct HashMap* hm, char* key)
{
    size_t index = indexOfString(hm, key);
    struct Node* node = List.get(hm->map[index], key);
    return Node.value(node);
}


void* iteratorOverMap(struct HashMap* hm, size_t index)
{
    if (index >= hm->size) { return 0; }
    for (size_t i = 0; i < hm->capacity; i += 1) {
        size_t length = List.length(hm->map[i]);
        if (index < length) {
            return Node.value(List.iter(hm->map[i], index));
        }
        index -= length;
    }
    return 0;
}


size_t removeElement(struct HashMap* hm, char* key)
{
    size_t index = indexOfString(hm, key);
    size_t len = List.length(hm->map[index]);
    if (!len) {
        return hm->size;
    }
    size_t newLen = List.remove(hm->map[index], key);
    if (newLen == len) {
        return hm->size;
    }
    hm->size -= 1;
    return hm->size;
}


void hashMapInfos(struct HashMap* hm)
{
    if (!hm) { return; }
    fprintf(stdout, "Number of buckets : %zu\n", hm->capacity);
    fprintf(stdout, "Total number of elements : %zu\n", hm->size);
}


void displayHashMap(struct HashMap* hm)
{
    if (!hm) { return; }
    hashMapInfos(hm);
    for (size_t i = 0; i < hm->capacity; i += 1) {
        if (!List.length(hm->map[i])) { continue; }
        fprintf(stdout, " Bucket [%zu] : \n", i);
        fprintf(stdout, "  %s\n", List.toString(hm->map[i]));
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
