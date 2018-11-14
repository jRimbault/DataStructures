#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <zconf.h>

#include "Parallel.h"
#include "struct/TypeLessList.h"


void join_all_workers(size_t nThreads, pthread_t* loop)
{
    for (size_t i = 0; i < nThreads; i += 1) {
        pthread_join(loop[i], NULL);
    }
    free(loop);
}


void parallel_for_loop(size_t nThreads, void* (* task)(void*), void* o)
{
    pthread_t* loop = malloc(nThreads * sizeof(pthread_t));
    for (size_t i = 0; i < nThreads; i += 1) {
        int err = pthread_create(&loop[i], NULL, task, o);
        if (err) {
            fprintf(stderr, "Can't create thread: [%s]\n", strerror(err));
        }
    }
    join_all_workers(nThreads, loop);
}


void parallel_auto_loop(void* (* task)(void*), void* o)
{
    parallel_for_loop((size_t) sysconf(_SC_NPROCESSORS_ONLN), task, o);
}


void parallel_for_each(void* (* task)(void*), struct List* list)
{
    size_t length = List.length(list);
    pthread_t* loop = malloc(length * sizeof(pthread_t));
    for (size_t i = 0; i < length; i += 1) {
        int err = pthread_create(&loop[i], NULL, task, List.iter(list, i));
        if (err) {
            fprintf(stderr, "Can't create thread: [%s]\n", strerror(err));
        }
    }
    join_all_workers(length, loop);
}


const struct _parallel Parallel = {
    .forLoop = parallel_for_loop,
    .autoLoop = parallel_auto_loop,
    .forEach = parallel_for_each,
};
