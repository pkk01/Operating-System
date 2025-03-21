#include <stdio.h>

int main() {
    int n, frames, pages[30], temp[10], m, n, position, k, l, pageFaults = 0;
    int flag1, flag2;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the reference string: ");
    for(m = 0; m < n; m++) {
        scanf("%d", &pages[m]);
    }
    
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    
    for(m = 0; m < frames; m++) {
        temp[m] = -1;
    }
    
    for(m = 0; m < n; m++) {
        flag1 = flag2 = 0;
        
        for(k = 0; k < frames; k++) {
            if(temp[k] == pages[m]) {
                flag1 = flag2 = 1;
                break;
            }
        }
        
        if(flag1 == 0) {
            for(k = 0; k < frames; k++) {
                if(temp[k] == -1) {
                    pageFaults++;
                    temp[k] = pages[m];
                    flag2 = 1;
                    break;
                }
            }
        }
        
        if(flag2 == 0) {
            temp[position] = pages[m];
            position++;
            if(position >= frames) {
                position = 0;
            }
            pageFaults++;
        }
        
        printf("\n");
        
        for(k = 0; k < frames; k++) {
            if(temp[k] != -1) {
                printf("%d\t", temp[k]);
            } else {
                printf("-\t");
            }
        }
    }
    
    printf("\nTotal Page Faults: %d\n", pageFaults);
    
    return 0;
}