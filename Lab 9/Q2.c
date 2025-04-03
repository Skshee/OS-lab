#include <stdio.h>
#include <stdlib.h>

// Function to find the LRU page index
int findLRU(int *time, int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int n, frames, *referenceString, *frame, *time, pageFaults = 0, counter = 0;

    // Input: Number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Input: Length of reference string
    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    // Dynamic memory allocation
    referenceString = (int *)malloc(n * sizeof(int));
    frame = (int *)malloc(frames * sizeof(int));
    time = (int *)malloc(frames * sizeof(int));

    if (!referenceString || !frame || !time) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input: Reference string
    printf("Enter the reference string: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &referenceString[i]);
    }

    // Initialize frames to -1 (empty)
    for (int i = 0; i < frames; ++i) {
        frame[i] = -1;
    }

    // LRU Page Replacement Algorithm
    for (int i = 0; i < n; ++i) {
        int page = referenceString[i];
        int found = 0;

        // Check if the page is already in frame
        for (int j = 0; j < frames; ++j) {
            if (frame[j] == page) {
                found = 1;
                time[j] = counter++; // Update time for LRU
                break;
            }
        }

        // If the page is not found (Page Fault)
        if (!found) {
            int pos = -1;

            // Find an empty frame
            for (int j = 0; j < frames; ++j) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find the LRU frame
            if (pos == -1) {
                pos = findLRU(time, frames);
            }

            // Replace the LRU page
            frame[pos] = page;
            time[pos] = counter++;
            ++pageFaults;
        }

        // Print current frame status
        printf("Frames: ");
        for (int j = 0; j < frames; ++j) {
            if (frame[j] == -1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    // Free allocated memory
    free(referenceString);
    free(frame);
    free(time);

    return 0;
}
