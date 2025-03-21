#include <stdio.h>

int findOptimal(int pages[], int n, int frame[], int m, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < m; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}

void optimalPageReplacement(int pages[], int n, int m) {
    int frame[m], count = 0, pageFaults = 0;
    for (int i = 0; i < m; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (frame[j] == pages[i]) {
                break;
            }
        }

        if (j == m) {
            if (count < m) {
                frame[count++] = pages[i];
            } else {
                int pos = findOptimal(pages, n, frame, m, i + 1);
                frame[pos] = pages[i];
            }
            pageFaults++;
        }

        printf("Frame: ");
        for (int k = 0; k < m; k++) {
            if (frame[k] != -1) {
                printf("%d ", frame[k]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, m;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &m);

    optimalPageReplacement(pages, n, m);

    return 0;
}