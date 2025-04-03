#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int size;
    int allocated;
    struct Block* next;
} Block;

Block* create_block(int size) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->size = size;
    block->allocated = 0;
    block->next = NULL;
    return block;
}

Block* first_fit(Block* head, int size) {
    Block* current = head;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Block* best_fit(Block* head, int size) {
    Block* best_block = NULL;
    Block* current = head;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            if (best_block == NULL || current->size < best_block->size) {
                best_block = current;
            }
        }
        current = current->next;
    }
    return best_block;
}

void allocate(Block* block, int size) {
    block->allocated = 1;
    printf("Allocated block of size %d\n", size);
}

void deallocate(Block* block) {
    block->allocated = 0;
    printf("Deallocated block of size %d\n", block->size);
}

void print_memory(Block* head) {
    Block* current = head;
    while (current != NULL) {
        printf("Block size: %d, allocated: %d\n", current->size, current->allocated);
        current = current->next;
    }
}

int main() {
    int n, size, alloc_size;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    Block *head = NULL, *tail = NULL;

    for (int i = 0; i < n; i++) {
        printf("Enter size for block %d: ", i + 1);
        scanf("%d", &size);
        Block* new_block = create_block(size);
        if (head == NULL) {
            head = new_block;
        } else {
            tail->next = new_block;
        }
        tail = new_block;
    }

    printf("\nEnter size to allocate (First Fit): ");
    scanf("%d", &alloc_size);
    Block* block = first_fit(head, alloc_size);
    if (block != NULL) {
        allocate(block, alloc_size);
    } else {
        printf("No suitable block found for allocation (First Fit).\n");
    }

    printf("\nEnter size to allocate (Best Fit): ");
    scanf("%d", &alloc_size);
    block = best_fit(head, alloc_size);
    if (block != NULL) {
        allocate(block, alloc_size);
    } else {
        printf("No suitable block found for allocation (Best Fit).\n");
    }

    printf("\nMemory blocks after allocations:\n");
    print_memory(head);

    printf("\nEnter size of block to deallocate: ");
    scanf("%d", &alloc_size);
    block = head;
    while (block != NULL) {
        if (block->allocated && block->size == alloc_size) {
            deallocate(block);
            break;
        }
        block = block->next;
    }
    if (block == NULL) {
        printf("No allocated block found with the given size.\n");
    }

    printf("\nMemory blocks after deallocation:\n");
    print_memory(head);

    while (head != NULL) {
        Block* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
