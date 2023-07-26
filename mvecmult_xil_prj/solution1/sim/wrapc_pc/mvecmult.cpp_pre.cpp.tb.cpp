// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "/home/gpm58/5775_project/mvecmult.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "/home/gpm58/5775_project/mvecmult.cpp"
# 1 "/home/gpm58/5775_project/mvecmult.h" 1
       






void mvecmult(int A[256][256], int v[256], int result[256]);
# 2 "/home/gpm58/5775_project/mvecmult.cpp" 2

void mvecmult(int A[256][256], int v[256], int result[256]) {
#pragma HLS array_partition variable = A dim = 2 factor = 8 cyclic

#pragma HLS array_partition variable=v complete
#pragma HLS array_partition variable=result complete

    for (int i = 0; i < 256; i++) {
        result[i] = 0;
        for (int j = 0; j < 256; j++) {
#pragma unroll
            result[i] += A[i][j] * v[j];
        }
    }
}
