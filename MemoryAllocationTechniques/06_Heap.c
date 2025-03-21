#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>


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

Block *requestSpace(Block *last, size_t size) {
    Block *block = (Block *)malloc(size + BLOCK_SIZE);
    if (block == NULL) {
        return NULL;
    }

    block->size = size;
    block->next = NULL;
    block->free = 0;

    if (last) {
        last->next = block;
    }

    return block;
}

void *my_malloc(size_t size) {
    Block *block;

    if (size <= 0) {
        return NULL;
    }

    if (!freeList) {
        block = requestSpace(NULL, size);
        if (!block) {
            return NULL;
        }
        freeList = block;
    } else {
        Block *last = freeList;
        block = findFreeBlock(&last, size);
        if (!block) {
            block = requestSpace(last, size);
            if (!block) {
                return NULL;
            }
        } else {
            block->free = 0;
        }
    }

    return block->data;
}

void my_free(void *ptr) {
    if (!ptr) {
        return;
    }

    Block *block = (Block *)((char *)ptr - offsetof(Block, data));
    block->free = 1;
}

int main() {
    int *arr = (int *)my_malloc(10 * sizeof(int));
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

    my_free(arr);
    return 0;
}
