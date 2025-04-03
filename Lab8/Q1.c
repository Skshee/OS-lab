#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resources

bool is_safe(int processes[], int avail[], int max[][R], int alloc[][R]) {
    int work[R];
    bool finish[P] = {0};
    int safe_seq[P];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int r = 0; r < R; r++) {
                    if (max[p][r] - alloc[p][r] > work[r]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int r = 0; r < R; r++) {
                        work[r] += alloc[p][r];
                    }
                    safe_seq[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safe_seq[i]);
    }
    printf("\n");

    return true;
}

bool request_resources(int processes[], int avail[], int max[][R], int alloc[][R], int request[], int p) {
    for (int r = 0; r < R; r++) {
        if (request[r] > max[p][r] - alloc[p][r]) {
            return false;
        }
    }

    for (int r = 0; r < R; r++) {
        if (request[r] > avail[r]) {
            return false;
        }
    }

    for (int r = 0; r < R; r++) {
        avail[r] -= request[r];
        alloc[p][r] += request[r];
    }

    if (is_safe(processes, avail, max, alloc)) {
        return true;
    } else {
        for (int r = 0; r < R; r++) {
            avail[r] += request[r];
            alloc[p][r] -= request[r];
        }
        return false;
    }
}

int main() {
    int processes[P];
    int avail[R];
    int max[P][R];
    int alloc[P][R];
    int request[R];
    int p;

    printf("Enter available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &avail[i]);
    }

    printf("Enter maximum resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocated resource matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter process number making the request: ");
    scanf("%d", &p);
    printf("Enter resource request for process %d: ", p);
    for (int i = 0; i < R; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(processes, avail, max, alloc, request, p)) {
        printf("Request can be granted.\n");
    } else {
        printf("Request cannot be granted. System would be unsafe.\n");
    }

    return 0;
}
