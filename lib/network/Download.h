#ifndef CLANGPOOL_DOWNLOAD_H
#define CLANGPOOL_DOWNLOAD_H

#include <stdlib.h>
#include <stdbool.h>


struct DownloadLibrary {
    bool (* toFile)(char*, char*);
    size_t (* toBuffer)(char*, char**);
};


extern const char* USER_AGENT;

extern const struct DownloadLibrary Download;

#endif //CLANGPOOL_DOWNLOAD_H
