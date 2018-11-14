#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "File.h"


bool file_write_to(char* file, char* buffer, size_t size)
{
    FILE* fd = fopen(file, "wb");
    if (fd == NULL) {
        return false;
    }
    size_t written = fwrite(buffer, sizeof(char), size, fd);
    if (!written) {
        return false;
    }
    if (fclose(fd) != EOF) {
        return false;
    }
    return true;
}


size_t file_read_to_buffer(char* file, char** buffer)
{
    FILE* fd = fopen(file, "rb");
    if (fd == NULL) {
        return 0;
    }
    int rc = fseek(fd, 0L, SEEK_END);
    if (rc != 0) {
        return 0;
    }
    long offEnd;
    if ((offEnd = ftell(fd)) < 0) {
        return 0;
    }
    size_t size = (size_t) offEnd;
    *buffer = calloc(size + 1, sizeof(char));
    if (*buffer == NULL) {
        return 0;
    }
    rewind(fd);
    if (fread(*buffer, 1, size, fd) != size) {
        free(*buffer);
        return 0;
    }
    if (fclose(fd) == EOF) {
        free(*buffer);
        return 0;
    }
    return size;
}


const struct FileLibrary File = {
    .write = file_write_to,
    .read = file_read_to_buffer,
};
