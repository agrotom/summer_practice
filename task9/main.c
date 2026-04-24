#include <stdio.h>

int main(int argc, char** argv) {
    int size = 0;
    int array[1024];
    int input = 0;
    char ch = 0;

    while (1) {
        int result = scanf("%d%c", &input, &ch);

        if (result == EOF) {
            break;
        }

        if (result == 0) {
            fprintf(stderr, "Invalid input! Must be an array of integers, separated by whitespaces!\n");
            return 1;
        }

        array[size] = input;
        size++;

        if (ch == '\n') {
            break;
        }
    }

    if (size == 1) {
        printf("%d\n", array[0]);
        return 0;
    }

    int maxI = 0, maxJ = 1;
    int i = 0, j = 1;
    while (j < size) {
        if (maxJ - maxI < j - i) {
            maxJ = j;
            maxI = i;
        }

        if (array[j - 1] > array[j]) {
            maxJ--;
            i = j;
        }

        j++;
    }

    for (int i = maxI; i <= maxJ; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}