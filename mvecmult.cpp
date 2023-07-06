#include "mvecmult.h"

void mvecmult(int A[SIZE][SIZE], int v[SIZE], int result[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            result[i] += A[i][j] * v[j];
        }
    }
}