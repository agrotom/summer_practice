#include <sys/stat.h>
#include <sys/sysmacros.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

char get_file_type_short(mode_t st_mode) {
    if (S_ISBLK(st_mode)) {
        return 'b';
    }
    else if (S_ISCHR(st_mode)) {
        return 'c';
    }
    else if (S_ISDIR(st_mode)) {
        return 'd';
    }
    else if (S_ISFIFO(st_mode)) {
        return 'p';
    }
    else if (S_ISLNK(st_mode)) {
        return 'l';
    }
    else if (S_ISSOCK(st_mode)) {
        return 's';
    }
    else {
        return '-';
    }
}

char* get_file_type(mode_t st_mode) {
    if (S_ISBLK(st_mode)) {
        return "block special file";
    }
    else if (S_ISCHR(st_mode)) {
        return "character special file";
    }
    else if (S_ISDIR(st_mode)) {
        return "directory";
    }
    else if (S_ISFIFO(st_mode)) {
        return "fifo";
    }
    else if (S_ISREG(st_mode)) {
        return "regular file";
    }
    else if (S_ISLNK(st_mode)) {
        return "symbolic link";
    }
    else if (S_ISSOCK(st_mode)) {
        return "socket";
    }
    else {
        return "";
    }
}

char* get_access_mode(mode_t st_mode) {
    char* access_array = (char*)malloc(11 * sizeof(char));

    int access = st_mode & 0777;

    access_array[0] = get_file_type_short(st_mode);

    for (int i = 1; i < 10; i++) {
        char mode = 'r';

        if ((i - 1) % 3 == 1) {
            mode = 'w';
        }
        else if ((i - 1) % 3 == 2) {
            mode = 'x';
        }

        if ((access & (1 << (9 - i))) != 0) {
            access_array[i] = mode;
        }
        else {
            access_array[i] = '-';
        }

    }

    access_array[10] = '\0';

    return access_array;
}

void print_timestamp(char* type, struct timespec ts) {
    time_t raw_time = ts.tv_sec;
    struct tm *time_info;
    char* buffer = malloc(64 * sizeof(char));
    char* utc_code = malloc(16 * sizeof(char));

    time_info = localtime(&raw_time);

    strftime(buffer, 64 * sizeof(char), "%Y-%m-%d %X", time_info);
    strftime(utc_code, 16 * sizeof(char), "%z", time_info);
    printf("%s: %s.", type, buffer);
    printf("%ld ", ts.tv_nsec);
    printf("%s\n", utc_code);

    free(buffer);
    free(utc_code);
}

char* get_user_name(long int uid) {
    struct passwd *pw = getpwuid(uid);

    if (pw == NULL) {
        return "null";
    }

    return pw->pw_name;
}

char* get_group_name(long int gid) {
    struct group *gr = getgrgid(gid);

    if (gr == NULL) {
        return "null";
    }

    return gr->gr_name;
}

long int get_dev(struct stat file_stat) {
    return S_ISCHR(file_stat.st_mode) || S_ISBLK(file_stat.st_mode) ? file_stat.st_rdev : file_stat.st_dev;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #6 requires name of file!\n");
        return 1;
    }

    char* file_name = argv[1];

    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1) {
        perror("Can't open file");
        return 1;
    }

    int st_mode = file_stat.st_mode;

    char* access_code = get_access_mode(st_mode);

    char* file_type = get_file_type(st_mode);

    long int st_dev = S_ISCHR(st_mode) || S_ISBLK(st_mode) ? file_stat.st_rdev : file_stat.st_dev;

    printf("File: %s\nSize: %ld\tBlocks: %ld\tIO Block: %ld\t%s\nDevice: %d,%d\tInode: %ld\tLinks: %ld\nAccess: (%04o/%s)\tUid: (\t%d/\t%s)\tGid: (\t%d/\t%s)\n",
        file_name, file_stat.st_size, file_stat.st_blocks,
        file_stat.st_blksize, get_file_type(st_mode), major(file_stat.st_dev), minor(file_stat.st_dev),
        file_stat.st_ino, file_stat.st_nlink, st_mode & 0777, access_code,
        file_stat.st_uid, get_user_name(file_stat.st_uid), file_stat.st_gid, get_group_name(file_stat.st_gid));

    print_timestamp("Access", file_stat.st_atim);
    print_timestamp("Modify", file_stat.st_mtim);
    print_timestamp("Change", file_stat.st_ctim);

    free(access_code);

    return 0;
}