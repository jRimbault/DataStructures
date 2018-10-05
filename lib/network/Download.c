#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <memory.h>

#include "Download.h"


const char* USER_AGENT = "libcurl-agent/1.0";

/** private dynamically reallocating struct */
struct MemoryStruct {
    char* memory;
    size_t size;
};


static size_t writeMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realSize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*) userp;
    char* ptr = realloc(mem->memory, mem->size + realSize + 1);
    if (ptr == NULL) {
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realSize);
    mem->size += realSize;
    mem->memory[mem->size] = 0;
    return realSize;
}


size_t downloadToBuffer(char* url, char** buffer)
{
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*) &chunk);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, USER_AGENT);
    CURLcode res = curl_easy_perform(handle);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    *buffer = chunk.memory;
    curl_easy_cleanup(handle);
    curl_global_cleanup();
    handle = NULL;
    return chunk.size;
}


/**
 * Downloads file from the given URL API
 * @param path where to write the returning json
 * @return success
 */
bool downloadToFile(char* file, char* url)
{
    CURL* handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, false);
    FILE* pd = fopen(file, "w");
    if (!pd) {
        fprintf(stderr, "Couldn't write to `%s`.\n", file);
        return 0;
    }
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, pd);
    CURLcode res = curl_easy_perform(handle);
    fclose(pd);
    curl_easy_cleanup(handle);
    curl_global_cleanup();
    handle = NULL;
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    return true;
}


const struct DownloadLibrary Download = {
    .toFile = downloadToFile,
    .toBuffer = downloadToBuffer,
};
