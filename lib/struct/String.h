#ifndef UNITTESTINGC_CSTRING
#define UNITTESTINGC_CSTRING

#include <stdbool.h>

#include "String/VecString.h"


typedef struct cstring cstring;

struct StringLibrary
{
    cstring* (* new)(char* initial);
    cstring* (* empty)();
    cstring* (* copy)(cstring* initial);
    char* (* text)(cstring* input);
    bool (* equals)(cstring* s1, cstring* s2);
    bool (* equalsArray)(cstring* s1, char* s2);
    cstring* (* append)(cstring* s1, cstring* s2);
    cstring* (* appendChar)(cstring* input, char character);
    cstring* (* appendArray)(cstring* input, char* characters);
    cstring* (* trim)(cstring* input);
    cstring* (* ltrim)(cstring* input);
    cstring* (* rtrim)(cstring* input);
    size_t (* free)(cstring* input);
    size_t (* length)(cstring* input);
    cstring* (* replace)(cstring* input, char character, char with);
    struct VecString* (* split)(cstring* input, char separator);
    cstring* (* join)(struct VecString* array, char separator);
};

extern const struct StringLibrary String;

#endif //UNITTESTINGC_CSTRING
