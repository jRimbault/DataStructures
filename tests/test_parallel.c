#include <stdio.h>
#include <zconf.h>

#include "minunit.h"
#include "Parallel.h"


unsigned int sleepPause = 0;


struct List* exampleList()
{
    struct List* list = List.new();
    for (size_t i = 0; i < 5; i += 1) {
        List.add(list, Node.new("key", (void*) (i + 1)));
    }
    return list;
}


void* adder(void* i)
{
    /** this is actually a dangerous sharing of one int */
    int* value = (int*) i;
    *value += 1;
    usleep(sleepPause);
    sleepPause += 20;
    printf("{i: %d}\n", *value);
    return NULL;
}


void* showNode(void* n)
{
    usleep(sleepPause);
    sleepPause += 20;
    printf("{%s: %zu}\n", Node.key(n), (size_t) Node.value(n));
    return NULL;
}


static char* tests()
{
    int i = 0;
    sleepPause = 20;
    printf("Adding 1, 5 times, sleep in each thread before printing\n");
    Parallel.forLoop(5, adder, &i);
    i = 0;
    sleepPause = 20;
    printf("Adding 1, 12 times\n");
    Parallel.autoLoop(adder, &i);
    sleepPause = 20;
    struct List* list = exampleList();
    Parallel.forEach(showNode, list);
    List.free(list);
    return 0;
}


mu_run(tests)
