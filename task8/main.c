#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

#define MATRIX_SIZE 3

#define SLEEP_INTERVAL 1

#define P_SIGNAL 1
#define P_SIGACTION 2

static int i = 0;
static int j = 0;
static int k = 0;

void sigintHandler(int arg) {
    printf("\n%d %d\n%d %d\n%d %d\n", i, k, k, i, i, j);
    signal(SIGINT, SIG_DFL);
}

void sigaction_handler(int arg) {
    printf("\n%d %d\n%d %d\n%d %d\n", i, k, k, i, i, j);
    signal(SIGINT, SIG_DFL);
}

int rand_int() {
    return rand() % 3 + 1;
}

void fill_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand_int();
        }
    }
}

void init_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = 0;
        }
    }
}

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void mult_matrices(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE][MATRIX_SIZE], int res_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            for(k = 0; k < MATRIX_SIZE; k++) {
                res_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
                sleep(SLEEP_INTERVAL);
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #8 requires at least 1 argument (--signal or --sigaction)!\n");
        return 1;
    }

    srand(time(NULL));

    int signal_flag = 0;

    struct option longoptions[] = {
        { "signal", no_argument, &signal_flag, 1 },
        { "sigaction", no_argument, &signal_flag, 2 },
        { 0, 0, 0, 0 }
    };

    opterr = 0;

    while (getopt_long_only(argc, argv, "", longoptions, NULL) != -1) {}

    switch (signal_flag) {
        case P_SIGNAL:
            signal(SIGINT, sigintHandler);
            break;
        case P_SIGACTION:
            struct sigaction action;

            action.sa_handler = sigaction_handler;
            sigemptyset(&action.sa_mask);
            action.sa_flags = SA_RESETHAND;
            sigaction(SIGINT, &action, NULL);

            break;
        default:
            fprintf(stderr, "Unknown type of signal!\n");
            return 1;
    }

    int matrix1[MATRIX_SIZE][MATRIX_SIZE], matrix2[MATRIX_SIZE][MATRIX_SIZE];
    int res_matrix[MATRIX_SIZE][MATRIX_SIZE];

    fill_matrix(matrix1);
    fill_matrix(matrix2);
    init_matrix(res_matrix);

    mult_matrices(matrix1, matrix2, res_matrix);

    return 0;
}