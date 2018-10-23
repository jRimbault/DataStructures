#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "File.h"


bool writeToFile(char* file, char* buffer)
{
    return false;
}


size_t readFileToBuffer(char* file, char** buffer)
{
    FILE* fd = fopen(file, "rb");
    if (NULL == fd) {
        return 0;
    }
    int rc = fseek(fd, 0L, SEEK_END);
    if (0 != rc) {
        return 0;
    }
    long offEnd;
    if (0 > (offEnd = ftell(fd))) {
        return 0;
    }
    size_t size = (size_t) offEnd;
    *buffer = calloc(size + 1, sizeof(char));
    if (NULL == *buffer) {
        return 0;
    }
    rewind(fd);
    if (size != fread(*buffer, 1, size, fd)) {
        free(*buffer);
        return 0;
    }
    if (EOF == fclose(fd)) {
        free(*buffer);
        return 0;
    }
    return size;
}


const struct FileLibrary File = {
    .write = writeToFile,
    .read = readFileToBuffer,
};
