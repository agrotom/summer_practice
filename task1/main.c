#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t lock;
int max_threads = 1;
int used_threads = 1;

struct quicksort_data {
    int* array;
    int l;
    int r;
};

void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int*);

void print_array(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf(" %d", array[i]);
    }
    printf("\n");
}

struct quicksort_data* create_qs_data(int* array, int l, int r) {
    struct quicksort_data* data = malloc(sizeof(struct quicksort_data));
    data->array = array;
    data->l = l;
    data->r = r;

    return data;
}

void* quicksort_thread(void* thread_data) {
    struct quicksort_data* data = (struct quicksort_data*) thread_data;

    quicksort(data->array, data->l, data->r);
    free(data);

    pthread_mutex_lock(&lock);
    used_threads--;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int partition(int* array, int left, int right) {
    int pivot = array[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[j], &array[i]);
        }
    }

    swap(&array[i + 1], &array[right]);
    
    return i + 1;
}

void quicksort(int* array, int left, int right) {
    if (left < right) {
        int pivot = partition(array, left, right);

        char created = 0;

        pthread_mutex_lock(&lock);

        if (used_threads < max_threads) {
            used_threads++;
            created = 1;
        }

        pthread_mutex_unlock(&lock);

        if (created) {
            pthread_t th;

            int result = pthread_create(&th, NULL, quicksort_thread, create_qs_data(array, left, pivot - 1));

            if (result) {
                fprintf(stderr, "Can't create thread: %d\n", result);
                exit(1);
            }

            quicksort(array, pivot + 1, right);

            pthread_join(th, NULL);
        }
        else {
            quicksort(array, left, pivot - 1);
            quicksort(array, pivot + 1, right);
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Task #1 requires at least 1 argument!\n");
        return 1;
    }

    int number_of_threads = atoi(argv[1]);

    if (number_of_threads < 1) {
        fprintf(stderr, "Task #1 requires integer argument more than '0'\n");
        return 1;
    }

    pthread_mutex_init(&lock, NULL);

    max_threads = number_of_threads;

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

    quicksort(array, 0, size - 1);

    printf("Sorted: ");
    for (int i = 0; i < size; i++) {
        printf(" %d", array[i]);
    }

    printf("\n");

    pthread_mutex_destroy(&lock);

    return 0;
}