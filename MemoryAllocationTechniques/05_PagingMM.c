#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4
#define MEMORY_SIZE 16

void print_memory(int memory[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", memory[i]);
    }
    printf("\n");
}

int main() {
    int memory[MEMORY_SIZE] = {0};
    int page_table[MEMORY_SIZE / PAGE_SIZE];
    int logical_address, physical_address;
    int page_number, offset;

    // Initialize page table
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        page_table[i] = -1;
    }

    // Simulate loading pages into memory
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        page_table[i] = i;
        for (int j = 0; j < PAGE_SIZE; j++) {
            memory[i * PAGE_SIZE + j] = i * PAGE_SIZE + j;
        }
    }

    printf("Memory content:\n");
    print_memory(memory, MEMORY_SIZE);

    printf("Enter a logical address (page number and offset): ");
    scanf("%d %d", &page_number, &offset);

    if (page_number >= MEMORY_SIZE / PAGE_SIZE || offset >= PAGE_SIZE) {
        printf("Invalid logical address\n");
        return 1;
    }

    if (page_table[page_number] == -1) {
        printf("Page not in memory\n");
        return 1;
    }

    physical_address = page_table[page_number] * PAGE_SIZE + offset;
    printf("Physical address: %d\n", physical_address);
    printf("Value at physical address: %d\n", memory[physical_address]);

    return 0;
}