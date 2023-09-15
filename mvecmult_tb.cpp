#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mvecmult.h"

#define NUM_TESTS 5

int A[SIZE][SIZE]; // Matrix array
int B[SIZE];       // Vector array
int C_hw[SIZE];    // Hardware result matrix
int C_sw[SIZE];    // Software result matrix

/* The makeRandomInputs function fills in random inputs for matrix and
 vector arrays us to perform effective testing
 */
void makeRandomInputs() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      A[i][j] = rand() % 10;
    }
    B[i] = rand() % 10;
  }
}

/* The mvecmult_golden is a function that allows us to perform computations
of matrix vector multiplication without any hardware optimizations so we can
compare hw and sw results
 */
void mvecmult_golden() {
  for (int i = 0; i < SIZE; i++) {
    C_sw[i] = 0;
    for (int j = 0; j < SIZE; j++) {
      C_sw[i] += A[i][j] * B[j];
    }
  }
}

/*The compareOutput function compares the results from hw and sw computations
*/
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
    makeRandomInputs(A, B); // Generates random inputs for matricies

    mvecmult(A, B, C_hw); // Function for testing Hardware version of code

    mvecmult_golden(A, B,
                    C_sw); // Function for testing Software version of code

    int result = compareOutput(); // Compares Hardware and Software Result
    if (result == EXIT_FAILURE) {
      printf("Test %d: Failure\n", i + 1);
    } else {
      printf("Test %d: Success\n", i + 1);
    }
  }

  return 0;
}

return 0;
}
