#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define RESOURCES 3
#define PROCESSES 5

void calculateNeed(int need[PROCESSES][RESOURCES], int max[PROCESSES][RESOURCES], int allot[PROCESSES][RESOURCES]);
bool isSafe(int processes[], int avail[], int max[][RESOURCES], int allot[][RESOURCES]);

int main() {
    int processes[] = {0, 1, 2, 3, 4};

    int resources[] = {10, 5, 7}; 

    int allot[PROCESSES][RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[PROCESSES][RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[RESOURCES];
    for (int i = 0; i < RESOURCES; i++) {
        avail[i] = resources[i];
        for (int j = 0; j < PROCESSES; j++) {
            avail[i] -= allot[j][i];
        }
    }

    isSafe(processes, avail, max, allot);

    return 0;
}

void calculateNeed(int need[PROCESSES][RESOURCES], int max[PROCESSES][RESOURCES], int allot[PROCESSES][RESOURCES]) {
    for (int i = 0; i < PROCESSES; i++) {
        for (int j = 0; j < RESOURCES; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int max[][RESOURCES], int allot[][RESOURCES]) {
    int need[PROCESSES][RESOURCES];
    calculateNeed(need, max, allot);

    bool finish[PROCESSES] = {0};
    int safeSeq[PROCESSES];
    int work[RESOURCES];

    for (int i = 0; i < RESOURCES ; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < PROCESSES) {
        bool found = false;
        for (int p = 0; p < PROCESSES; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == RESOURCES) {
                    for (int k = 0 ; k < RESOURCES ; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < PROCESSES ; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}