#include <stdio.h>
#include <pthread.h>

void* threadExample(void* threadData) {
    printf("Hello world from %ld!\n", pthread_self());
    pthread_exit(0);
}

void partition(int* array, int* l, int* r) {

}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #1 requires at least 1 argument!\n");
        return 1;
    }

    int size = 0;
    int array[1024];
    int input = 0;

    while (1) {
        int result = scanf("%d", &input);

        if (result == EOF) {
            break;
        }

        if (result == 0) {
            fprintf(stderr, "Invalid input! Must be an array of integers, separated by whitespaces!\n");
            return 1;
        }

        array[size] = input;
        size++;
    }

    if (size == 0) {
        fprintf(stderr, "Please provide at least 1 integer to the input!\n");
        return 1;
    }

    if (size == 1) {
        printf("%d\n", array[0]);
        return 0;
    }

    return 0;
}