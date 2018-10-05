
#include "Struct.h"
#include "struct/List.c"
#include "struct/HashMap.c"


const struct Library MyLib = {
    .List = {
        .new = newLinkedList,
        .insertFirst = insertFirst,
        .insertAt = insertAt,
        .add = insertLast,
        .freeFirst = deleteFirst,
        .freeAt = deleteAt,
        .pop = deleteLast,
        .free = deleteList,
        .length = listLength,
        .contains = listContains,
        .getAt = getAt,
        .get = getLink,
        .remove = removeLink,
        .invert = invertList,
        .merge = mergeLists,
        .display = displayLinkedList,
    },
    .Hashmap = {
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
    },
};
