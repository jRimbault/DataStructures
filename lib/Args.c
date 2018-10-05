#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

#include "Args.h"


void help()
{
    printf("Show this help.");
}


static int verbose_flag;


int testingGetopt(int argc, char** argv)
{
    static struct option long_options[] =
        {
            /* These options set a flag. */
            {"verbose", no_argument, &verbose_flag, 0},
            {"brief", no_argument, &verbose_flag, 0},
            /* These options don’t set a flag.
               We distinguish them by their indices. */
            {"add", no_argument, 0, 'a'},
            {"append", no_argument, 0, 'b'},
            {"delete", required_argument, 0, 'd'},
            {"create", required_argument, 0, 'c'},
            {"file", required_argument, 0, 'f'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
        };
    /* getopt_long stores the option index here. */
    int option_index = 0;

    while (1) {
        int c = getopt_long(
            argc, argv, "abc:d:f:h",
            long_options, &option_index
        );

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }

        switch (c) {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if (long_options[option_index].flag != 0)
                    break;
                printf("option %s", long_options[option_index].name);
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;
            case 'a':
                puts("option -a\n");
                break;
            case 'b':
                puts("option -b\n");
                break;
            case 'c':
                printf("option -c with value `%s'\n", optarg);
                break;
            case 'd':
                printf("option -d with value `%s'\n", optarg);
                break;
            case 'f':
                printf("option -f with value `%s'\n", optarg);
                break;
            case 'h':
                printf("option -h\n");
                break;
            default:
                abort();
        }
    }

    /* Instead of reporting ‘--verbose’
       and ‘--brief’ as they are encountered,
       we report the final status resulting from them. */
    if (verbose_flag) {
        puts("verbose flag is set");
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc) {
            printf("%s ", argv[optind++]);
        }
        putchar('\n');
    }

    return 0;
}


bool argIs(char* actualArg, char* longArg, char* shortArg)
{
    const size_t max = 255;
    if (strncmp(actualArg, longArg, strnlen(longArg, max)) == 0) {
        return true;
    }
    if (strncmp(actualArg, shortArg, strnlen(shortArg, max)) == 0) {
        return true;
    }
    return false;
}
