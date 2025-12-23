#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_SIZE 1000 

typedef struct {
    int start;
    int size;
    bool isFree;
} Block;

Block memory[MEMORY_SIZE]; 

void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].start = i;
        memory[i].size = 1;
        memory[i].isFree = true;
    }
}

void displayMemory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].isFree) {
            printf("Block from %d to %d is occupied\n", memory[i].start, memory[i].start + memory[i].size - 1);
        }
    }
}

void allocateMemory(int size, char method) {
    int bestIdx = -1, worstIdx = -1, firstIdx = -1;
    int bestSize = MEMORY_SIZE + 1, worstSize = -1;

    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].isFree) {
            int j = i;
            int currentSize = 0;

            while (j < MEMORY_SIZE && memory[j].isFree) {
                currentSize++;
                j++;
            }

            if (currentSize >= size) {
                if (method == 'b' && currentSize < bestSize) {
                    bestSize = currentSize;
                    bestIdx = i;
                } else if (method == 'w' && currentSize > worstSize) {
                    worstSize = currentSize;
                    worstIdx = i;
                } else if (method == 'f' && firstIdx == -1) {
                    firstIdx = i;
                }
            }

            i = j - 1; 
        }
    }

    int idx = (method == 'b') ? bestIdx : (method == 'w') ? worstIdx : firstIdx;

    if (idx != -1) {
        int allocated = 0;

        // Allocate the memory
        for (int i = idx; i < MEMORY_SIZE && allocated < size; i++) {
            if (memory[i].isFree) {
                memory[i].isFree = false;
                allocated++;
            }
        }

        printf("Allocated %d units using %s fit starting at %d\n", size, (method == 'b') ? "Best" : (method == 'w') ? "Worst" : "First", idx);
    } else {
        printf("Failed to allocate %d units of memory\n", size);
    }
}

void deallocateMemory(int start, int size) {
    for (int i = start; i < start + size && i < MEMORY_SIZE; i++) {
        memory[i].isFree = true;
    }
    printf("Deallocated %d units of memory starting from %d\n", size, start);
}

int main() {
    char method;
    int size, start;

    initializeMemory();

    while (1) {
        printf("\nMemory Allocation Simulator\n");
        printf("1. Allocate Memory (First fit: 'f', Best fit: 'b', Worst fit: 'w')\n");
        printf("2. Deallocate Memory\n");
        printf("3. Display Memory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter allocation size: ");
                scanf("%d", &size);
                printf("Enter fit method (f for First fit, b for Best fit, w for Worst fit): ");
                scanf(" %c", &method); 
                allocateMemory(size, method);
                break;
            case 2:
                printf("Enter deallocation start and size: ");
                scanf("%d %d", &start, &size);
                deallocateMemory(start, size);
                break;
            case 3:
                displayMemory();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}