#ifndef CLANGPOOL_MINUNIT_H
#define CLANGPOOL_MINUNIT_H

#include <stdio.h>


#define mu_assert(message, test) \
    do { \
        if (!(test)) return message; \
    } while (0)

#define mu_run_test(test) \
    do { \
        char *message = test(); \
        tests_run++; \
        if (message) { \
            errors += 1; \
            fprintf(stderr, "error, %s\n", message); \
        } \
    } while (0)

#define mu_run(tests) \
    int errors = 0; \
    int tests_run = 0; \
    int main() \
    { \
        char* result = tests(); \
        if (!errors) { \
            printf("All tests ran without errors\n"); \
        } \
        printf("Tests run: %d, errors: %d\n", tests_run, errors); \
        return result != 0; \
    }

extern int errors;
extern int tests_run;

#endif //CLANGPOOL_MINUNIT_H
