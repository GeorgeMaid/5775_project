#include <stdio.h>
#include "mvecmult.h"
#include <stdlib.h>

#define SIZE 256

int compare_res(int res_sw[SIZE], int res_hw[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (res_hw[i] != res_sw[i]) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int softwareTesting1() {
    int mat1[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int vec1[SIZE] = {1, 2, 3};

    int res_sw[SIZE];
    int expected[SIZE] = {14, 32, 50};

    mvecmult(mat1, vec1, res_sw);

    return compare_res(res_sw, expected);
}

int softwareTesting2() {
    int mat2[SIZE][SIZE] = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    int vec2[SIZE] = {1, 3, 5};

    int res_sw[SIZE];
    int expected[SIZE] = {44, 116, 188};

    mvecmult(mat2, vec2, res_sw);

    return compare_res(res_sw, expected);
}

int main(int argc, char **argv) {
    int result1 = softwareTesting1();
    printf("Software testing 1 result: %d\n", result1);

    int result2 = softwareTesting2();
    printf("Software testing 2 result: %d\n", result2);

    return 0;
}