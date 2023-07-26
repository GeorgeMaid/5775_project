#include "mvecmult.h"

void mvecmult(int A[SIZE][SIZE], int v[SIZE], int result[SIZE]) {
    #pragma HLS array_partition variable = A dim = 2 factor = 8 cyclic 
//    #pragma HLS array_partition variable=A dim=2 complete
    #pragma HLS array_partition variable=v complete
    #pragma HLS array_partition variable=result complete

    for (int i = 0; i < SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < SIZE; j++) {
            #pragma unroll 
            result[i] += A[i][j] * v[j];
        }
    }
}