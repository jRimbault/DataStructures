#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>

#include "Parallel.h"
#include "struct/TypeLessList.h"


void joinAllWorkers(size_t nThreads, pthread_t* loop)
{
    for (size_t i = 0; i < nThreads; i += 1) {
        pthread_join(loop[i], NULL);
    }
    free(loop);
}


void forLoop(size_t nThreads, void* (* task)(void*), void* o)
{
    pthread_t* loop = malloc(nThreads * sizeof(pthread_t));
    for (size_t i = 0; i < nThreads; i += 1) {
        int err = pthread_create(&loop[i], NULL, task, o);
        if (err) {
            fprintf(stderr, "Can't create thread: [%s]\n", strerror(err));
        }
    }
    joinAllWorkers(nThreads, loop);
}


void autoLoop(void* (* task)(void*), void* o)
{
    forLoop((size_t) sysconf(_SC_NPROCESSORS_ONLN), task, o);
}


void forEach(void* (* task)(void*), struct List* list)
{
    size_t length = List.length(list);
    pthread_t* loop = malloc(length * sizeof(pthread_t));
    for (size_t i = 0; i < length; i += 1) {
        int err = pthread_create(&loop[i], NULL, task, List.iter(list, i));
        if (err) {
            fprintf(stderr, "Can't create thread: [%s]\n", strerror(err));
        }
    }
    joinAllWorkers(length, loop);
}


const struct _parallel Parallel = {
    .forLoop = forLoop,
    .autoLoop = autoLoop,
    .forEach = forEach,
};
