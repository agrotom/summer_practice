#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int file_writer(char* name, FILE* r_file) {
    FILE* w_file = NULL;
    w_file = fopen(name, "w");

    if (w_file == NULL) {
        perror("Can't open file");
        return -1;
    }

    fpos_t pos;
    fgetpos(r_file, &pos);

    char buffer[BUFFER_SIZE];
    size_t read_size = fread(buffer, sizeof(char), BUFFER_SIZE, r_file);

    fsetpos(r_file, &pos);

    if (fwrite(buffer, sizeof(char), read_size, w_file) < read_size) {
        perror("Can't write to the file");
        return -1;
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #7 requires file name!\n");
        return 1;
    }

    char* file_name = argv[1];
    FILE* file = NULL;
    file = fopen(file_name, "r");

    if (file == NULL) {
        perror("Can't open the file");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Can't perform fork");
        return 1;
    }
    else if (pid == 0) {
        if (file_writer("child_copy", file) == -1) {
            return 1;
        }
    }
    else {
        if (file_writer("parent_copy", file) == -1) {
            return 1;
        }
    }
    
    return 0;
}