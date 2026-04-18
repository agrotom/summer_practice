#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MATRIX_SIZE 3

static int i = 0;
static int j = 0;
static int k = 0;

void sigintHandler(int arg) {
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
                sleep(0.5);
            }
        }
    }
}

int main(int argc, char** argv) {

    srand(time(NULL));

    signal(SIGINT, sigintHandler);

    int matrix1[MATRIX_SIZE][MATRIX_SIZE], matrix2[MATRIX_SIZE][MATRIX_SIZE];
    int res_matrix[MATRIX_SIZE][MATRIX_SIZE];

    fill_matrix(matrix1);
    fill_matrix(matrix2);
    init_matrix(res_matrix);

    mult_matrices(matrix1, matrix2, res_matrix);

    print_matrix(res_matrix);

    return 0;
}