#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubble_sort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
     pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        char *strings[100];
        int count = argc - 1;

        for (int i = 0; i < count; i++) {
            strings[i] = argv[i + 1];
        }

        bubble_sort(strings, count);

        printf("Sorted strings:\n");
        for (int i = 0; i < count; i++) {
            printf("%s\n", strings[i]);
        }

        exit(0);
    } else {
        wait(NULL);

        printf("Unsorted strings:\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}
