#include <stdio.h>

#include "network/Download.h"
#include "minunit.h"


static char* should_download_example_dot_com()
{
    char* buffer;
    size_t size = Download.toBuffer("https://www.example.com", &buffer);
    printf("%s", buffer);
    printf("Downloaded %zu bytes.\n", size);
    free(buffer);
    return 0;
}


static char* all_tests()
{
    mu_run_test(should_download_example_dot_com);
    return 0;
}


mu_run(all_tests)
