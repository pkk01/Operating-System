#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_program_break(const char *msg) {
    void *brk = sbrk(0);
    printf("%s: Program break is at %p\n", msg, brk);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_blocks> <block_size> [<step> [<start> <end>]]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_blocks = atoi(argv[1]);
    size_t block_size = (size_t)atoi(argv[2]);
    int step = (argc > 3) ? atoi(argv[3]) : 1;
    int start = (argc > 4) ? atoi(argv[4]) : 0;
    int end = (argc > 5) ? atoi(argv[5]) : num_blocks;

    if (step <= 0 || start < 0 || end > num_blocks || start >= end) {
        fprintf(stderr, "Invalid arguments\n");
        exit(EXIT_FAILURE);
    }

    print_program_break("Before allocation");

    void **blocks = malloc(num_blocks * sizeof(void *));
    if (blocks == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_blocks; i++) {
        blocks[i] = malloc(block_size);
        if (blocks[i] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }

    print_program_break("After allocation");

    for (int i = start; i < end; i += step) {
        free(blocks[i]);
    }

    print_program_break("After free");

    free(blocks);

    // Expand the program break by 1000000 bytes
    void *current_brk = sbrk(0);
    if (brk(current_brk + 1000000) == -1) {
        perror("brk");
        exit(EXIT_FAILURE);
    }

    print_program_break("After expanding program break");

    return 0;
}