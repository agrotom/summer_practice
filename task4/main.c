#include <stdio.h>
#include <getopt.h>
#include <string.h>

#define MAX_ELBRUS_OPTS 6

char is_elbrus_opt(char* opt) {
    return strcmp(opt, "1c+") == 0 || strcmp(opt, "2c+") == 0 || strcmp(opt, "2c3") == 0 || strcmp(opt, "4c") == 0 || strcmp(opt, "8c") == 0 || strcmp(opt, "16c") == 0; 
}

char has_elbrus_opt(char** elbrus_opts, size_t elbrus_opts_size, char* opt) {
    for (int i = 0; i < elbrus_opts_size; i++) {
        if (strcmp(elbrus_opts[i], opt) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char** argv) {
    char result = 0;
    opterr = 0; // отключение вывода getopt в stderr

    const char* shortopts = "mcst";

    const struct option longoptions[] = {
        { "elbrus", required_argument, NULL, 'e' }
    };

    char short_options[4];
    size_t short_size = 0;

    char* elbrus_values[MAX_ELBRUS_OPTS];
    size_t elbrus_value_size = 0;

    while ((result = getopt_long(argc, argv, shortopts, longoptions, NULL)) != -1) {
        switch (result) {
            case 'e':
                if (!is_elbrus_opt(optarg)) {
                    fprintf(stderr, "Incorrect option: 'elbrus=%s'\n", optarg);
                    return 1;
                }

                if (has_elbrus_opt(elbrus_values, elbrus_value_size, optarg)) {
                    continue;
                }

                elbrus_values[elbrus_value_size] = optarg;
                elbrus_value_size++;
                break;
            case 'm':
            case 'c':
            case 's':
            case 't':
                short_options[short_size] = result;
                short_size++;
                break;
            case '?':
                fprintf(stderr, "Incorrect option: '%c'\n", optopt);
                return 1;
        }
    }

    printf("Short options:");
    if (short_size > 0) {
        for (int i = 0; i < short_size; i++) {
            printf(" '%c'", short_options[i]);
        }
    }

    printf("\nLong options:");
    if (elbrus_value_size > 0) {
        for (int i = 0; i < elbrus_value_size; i++) {
            printf(" 'elbrus=%s'", elbrus_values[i]);
        }
    }

    printf("\nNon options:");
    if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            printf(" '%s'", argv[i]);
        }
    }
    putc('\n', stdout);
    
    return 0;
}