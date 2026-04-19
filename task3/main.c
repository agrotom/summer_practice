#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 64
#define MAX_LINE_LENGTH 64

int lex_sort(const char* str1, const char* str2) {
    return strcasecmp(str1, str2);
}

int plain_sort(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

void bubble_sort(char lines[MAX_LINES][MAX_LINE_LENGTH], int length, int (*sort_func)(const char*, const char*), char reverse) {
    if (reverse) {
        for (int i = 0; i < length - 1; i++) {
            for (int j = 0; j < length - 1 - i; j++) {
                char temp[MAX_LINE_LENGTH];

                if (sort_func(lines[j], lines[j + 1]) < 0) {
                    strcpy(temp, lines[j]);
                    strcpy(lines[j], lines[j + 1]);
                    strcpy(lines[j + 1], temp);
                }
            }
        }   
    }
    else {
        for (int i = 0; i < length - 1; i++) {
            for (int j = 0; j < length - 1 - i; j++) {
                char temp[MAX_LINE_LENGTH];

                if (sort_func(lines[j], lines[j + 1]) > 0) {
                    strcpy(temp, lines[j]);
                    strcpy(lines[j], lines[j + 1]);
                    strcpy(lines[j + 1], temp);
                }
            }
        }   
    }
}

int is_str_visible(char line[MAX_LINE_LENGTH]) {
    for (int i = 0; i < MAX_LINE_LENGTH && line[i] != '\0'; i++) {
        if (isgraph(line[i])) {
            return 1;
        }
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Task #3 requires at least 3 argument!\n");
        return 1;
    }

    char* in_file_name = argv[1];
    char* out_file_name = argv[2];
    char* sort_type = argv[3];
    int (*sort_func)(const char*, const char*);
    
    char reverse = 0;

    if (strcmp(sort_type, "lex") == 0) {
        sort_func = lex_sort;
    }
    else if (strcmp(sort_type, "plain") == 0) {
        sort_func = plain_sort;
    }
    else if (strcmp(sort_type, "rlex") == 0) {
        sort_func = lex_sort;
        reverse = 1;
    }
    else if (strcmp(sort_type, "rplain") == 0) {
        sort_func = plain_sort;
        reverse = 1;
    }
    else {
        fprintf(stderr, "Unknown sort type: %s\n", sort_type);
        return 1;
    }
    
    FILE *in_file = NULL, *out_file = NULL;
    in_file = fopen(in_file_name, "r");
    
    if (in_file == NULL) {
        perror("Can't open the 'in' file");
        return 1;
    }

    out_file = fopen(out_file_name, "w");
    
    if (in_file == NULL) {
        perror("Can't open the 'out' file");
        return 1;
    }

    int current_line = 0;
    char lines[MAX_LINES][MAX_LINE_LENGTH];

    while (fgets(lines[current_line], sizeof(lines[current_line]), in_file) != NULL && current_line < MAX_LINES) {
        if (!is_str_visible(lines[current_line])) {
            continue;
        }

        current_line++;
    }

    bubble_sort(lines, current_line, sort_func, reverse);

    for (int i = 0; i < current_line; i++) {
        fputs(lines[i], out_file);
    }

    if (fclose(in_file) == EOF) {
        perror("Can't close the 'in' file");
        return 1;
    }

    if (fclose(out_file) == EOF) {
        perror("Can't close the 'out' file");
        return 1;
    }
    
    return 0;
}