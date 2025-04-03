#include <stdio.h>
#include <stdlib.h>

// Function to check if a page is in frames
int isPageInFrame(int *frames, int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

// FIFO Page Replacement Algorithm
void fifo(int *pages, int pageCount, int frameCount) {
    int *frames = (int *)malloc(frameCount * sizeof(int));
    int front = 0, pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    for (int i = 0; i < pageCount; i++) {
        if (!isPageInFrame(frames, frameCount, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % frameCount; // Circular queue behavior
            pageFaults++;
        }

        // Display current frame status
        printf("Frames: ");
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
    free(frames);
}

// Function to find the optimal page to replace
int findOptimalReplacement(int *frames, int frameCount, int *pages, int current, int pageCount) {
    int farthest = -1, replaceIndex = -1;

    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = current; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }

        // If a page is not used again, replace it immediately
        if (j == pageCount) return i;
    }
    return replaceIndex;
}

// Optimal Page Replacement Algorithm
void optimal(int *pages, int pageCount, int frameCount) {
    int *frames = (int *)malloc(frameCount * sizeof(int));
    int pageFaults = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    for (int i = 0; i < pageCount; i++) {
        if (!isPageInFrame(frames, frameCount, pages[i])) {
            if (i < frameCount) {
                frames[i] = pages[i]; // Fill empty slots first
            } else {
                int replaceIndex = findOptimalReplacement(frames, frameCount, pages, i + 1, pageCount);
                frames[replaceIndex] = pages[i];
            }
            pageFaults++;
        }

        // Display current frame status
        printf("Frames: ");
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
    free(frames);
}

int main() {
    int pageCount, frameCount;

    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    int *pages = (int *)malloc(pageCount * sizeof(int));

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    printf("\nRunning FIFO Page Replacement:\n");
    fifo(pages, pageCount, frameCount);

    printf("\nRunning Optimal Page Replacement:\n");
    optimal(pages, pageCount, frameCount);

    free(pages);
    return 0;
}
