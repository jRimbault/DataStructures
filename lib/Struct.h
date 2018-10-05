#ifndef CLANGPOOL_STRUCT_H
#define CLANGPOOL_STRUCT_H

#include "struct/List.h"
#include "struct/HashMap.h"


struct Library
{
    struct HashMapLibrary Hashmap;
    struct LinkedListLibrary List;
};


extern const struct Library MyLib;

#endif //CLANGPOOL_STRUCT_H
