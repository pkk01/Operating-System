#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct block {
    size_t size;
    struct block *next;
    int free;
    char data[1];
} Block;

#define BLOCK_SIZE (sizeof(Block) - sizeof(char))

Block *freeList = NULL;

Block *findFreeBlock(Block **last, size_t size) {
    Block *current = freeList;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

Block *requestSpace(Block* last, size_t size) {
    Block *block;
    block = sbrk(0);
    void *request = sbrk(size + BLOCK_SIZE);
    if (request == (void*) -1) {
        return NULL; // sbrk failed
    }

    if (last) { // NULL on first request
        last->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}

void *malloc(size_t size) {
    Block *block;

    if (size <= 0) {
        return NULL;
    }

    if (!freeList) { // First call
        block = requestSpace(NULL, size);
        if (!block) {
            return NULL;
        }
        freeList = block;
    } else {
        Block *last = freeList;
        block = findFreeBlock(&last, size);
        if (!block) { // Failed to find free block
            block = requestSpace(last, size);
            if (!block) {
                return NULL;
            }
        } else { // Found free block
            block->free = 0;
        }
    }

    return(block->data);
}

void free(void *ptr) {
    if (!ptr) {
        return;
    }

    Block *block = (Block*)ptr - 1;
    block->free = 1;
}

int main() {
    int *arr = (int*)malloc(10 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i * i;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}