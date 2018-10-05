#include <stdio.h>

#include "File.h"
#include "minunit.h"


static char* should_read_file()
{
    char* buffer;
    size_t size = File.read(__FILE__, &buffer);
    printf("%s", buffer);
    printf("File %zu bytes\n", size);
    free(buffer);
    return 0;
}


static char* all_tests()
{
    mu_run_test(should_read_file);
    return 0;
}


mu_run(all_tests)
