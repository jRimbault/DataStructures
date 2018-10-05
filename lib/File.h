#ifndef CLANGPOOL_FILE_H
#define CLANGPOOL_FILE_H

#include <stdlib.h>
#include <stdbool.h>


struct FileLibrary {
    bool (* write)(char*, char*);
    size_t (* read)(char*, char**);
};


extern const struct FileLibrary File;

#endif //CLANGPOOL_FILE_H
