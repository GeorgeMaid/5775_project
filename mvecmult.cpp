#include "mvecmult.h"

/* The function mvecmult is the hw implimentation of matrix vector multiplication
that will be tested when peforming Vivado testing 
*/
void mvecmult(int A[SIZE][SIZE], int v[SIZE], int result[SIZE]) {
    #pragma HLS array_partition variable=A dim=2 complete
    #pragma HLS array_partition variable=v complete

    for (int i = 0; i < SIZE; i++) {
        #pragma HLS pipeline
        int acc = 0;
        for (int j = 0; j < SIZE; j++) {
            #pragma HLS unroll 
            acc += A[i][j] * v[j];
        }
        result[i] = acc;
    }
}
