#ifndef UNITTESTINGC_ASYNC_H
#define UNITTESTINGC_ASYNC_H

#include <stdlib.h>

#include "struct/List.h"


struct _parallel
{
    void (* forLoop)(size_t nLoops, void* (* function)(void* o), void* o);
    void (* autoLoop)(void* (* function)(void* o), void* o);
    void (* forEach)(void* (* function)(void* list), struct List* list);
};

extern const struct _parallel Parallel;

#endif //UNITTESTINGC_ASYNC_H
