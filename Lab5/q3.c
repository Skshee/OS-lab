#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

void bubbleSort(char arr[][MAX_LENGTH], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char temp[MAX_LENGTH];
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

void quickSort(char arr[][MAX_LENGTH], int low, int high) {
    if (low < high) {
        char pivot[MAX_LENGTH];
        strcpy(pivot, arr[high]);
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (strcmp(arr[j], pivot) < 0) {
                i++;
                char temp[MAX_LENGTH];
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        }
        char temp[MAX_LENGTH];
        strcpy(temp, arr[i + 1]);
        strcpy(arr[i + 1], arr[high]);
        strcpy(arr[high], temp);
        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int N;
    printf("Enter the number of strings: ");
    scanf("%d", &N);
    
    char strings[MAX_STRINGS][MAX_LENGTH];
    printf("Enter %d strings:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%s", strings[i]);
    }

    pid_t pid1, pid2;

    // Create first child process for Bubble Sort
    if ((pid1 = fork()) == 0) {
        bubbleSort(strings, N);
        printf("Bubble Sort Result:\n");
        for (int i = 0; i < N; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    // Create second child process for Quick Sort
    if ((pid2 = fork()) == 0) {
        quickSort(strings, 0, N - 1);
        printf("Quick Sort Result:\n");
        for (int i = 0; i < N; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }

    /* Parent process waits for one of the child processes to terminate
    int status;
    pid_t terminated_pid = wait(&status);
    if (terminated_pid == pid1) {
        printf("Child process for Bubble Sort terminated.\n");
    } else {
        printf("Child process for Quick Sort terminated.\n");
    }*/

    
    return 0;
}
