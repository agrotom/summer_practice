#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    const char* open_error = "Can't open the file";
    
    FILE* fd;

    fd = fopen("somefile", "r");

    if (fd == NULL) {
        perror(open_error);
        fprintf(stderr, "%s: %s\n", open_error, strerror(errno)); // в новых версиях GNU напрямую обратиться к sys_errlist нельзя, поэтому исползуем strerror
        fprintf(stderr, "Errno = %s\n", strerrorname_np(errno));
        return 1;
    }
    
    return 0;
}