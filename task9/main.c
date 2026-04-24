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

    int maxSum = array[0];
    int sum = array[0];
    int maxI = 0, maxJ = 0;
    int i = 0, j = 1;
    while (j < size) {
        if (array[j - 1] > array[j]) {
            i = j;
            sum = array[i];
        }
        else {
            sum += array[j];
        }

        int max_len = maxJ - maxI + 1;
        int cur_len = j + 1 - i;
        if (max_len < cur_len || (max_len == cur_len && maxSum < sum)) {
            maxJ = j;
            maxI = i;
            maxSum = sum;
        }

        j++;
    }

    for (int i = maxI; i <= maxJ; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}