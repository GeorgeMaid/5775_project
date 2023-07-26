#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mvecmult.h"

#define NUM_TESTS 5

int A[SIZE][SIZE];     
int B[SIZE];            
int C_hw[SIZE];         
int C_sw[SIZE];        

void makeRandomInputs() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = rand() % 10;
        }
        B[i] = rand() % 10;
    }
}

void mvecmult_golden() {
    for (int i = 0; i < SIZE; i++) {
        C_sw[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            C_sw[i] += A[i][j] * B[j];
        }
    }
}

int compareOutput() {
    for (int i = 0; i < SIZE; i++) {
        if (C_hw[i] != C_sw[i]) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int main() {
    for (int i = 0; i < NUM_TESTS; i++) {
        makeRandomInputs();

        mvecmult(A, B, C_hw);

        mvecmult_golden();

        int result = compareOutput();
        if (result == EXIT_FAILURE) {
            printf("Test %d: Failure\n", i + 1);
        } else {
            printf("Test %d: Success\n", i + 1);
        }
    }

    return 0;
}