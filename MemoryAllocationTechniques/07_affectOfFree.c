#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_blocks> <block_size>\n", argv[0]);
        return 1;
    }

    int num_blocks = atoi(argv[1]);
    size_t block_size = (size_t)atoi(argv[2]);

    printf("Before allocation: No blocks allocated.\n");

    void **blocks = malloc(num_blocks * sizeof(void *));
    if (blocks == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < num_blocks; i++) {
        blocks[i] = malloc(block_size);
        if (blocks[i] == NULL) {
            perror("malloc");
            return 1;
        }
        printf("Block %d allocated at %p\n", i, blocks[i]);
    }

    printf("After allocation: All blocks allocated.\n");

    for (int i = 0; i < num_blocks; i++) {
        free(blocks[i]);
    }
    free(blocks);

    printf("After free: All blocks freed.\n");

    return 0;
}
