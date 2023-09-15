#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <assert.h>

#include <iostream>
#include <fstream>

#include "mvecmult.h"
// #include "ap_int.h"
// #include "timer.h"

//------------------------------------------------------------------------
// Helper function for hex to int conversion
//------------------------------------------------------------------------
int64_t hexstring_to_int64(std::string h) {
  int64_t x = 0;
  for (int i = 0; i < h.length(); ++i) {
    char c = h[i];
    int k = (c > '9') ? toupper(c) - 'A' + 10 : c - '0';
    x = x * 16 + k;
  }
  return x;
}

//--------------------------------------
// main function
//--------------------------------------
int main(int argc, char **argv) {
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0)) {
    fprintf(stderr, "Failed to open Xillybus device channels\n");
    exit(-1);
  }

  // Read input file for the testing set
  //   std::string line;
  //   std::ifstream myfile("data/testing_set.dat");

  int A[SIZE][SIZE];
  int v[SIZE];
  int result[SIZE];

  // Stage inputs as identity
  for (unsigned i = 0; i < SIZE; ++i) {
    for (unsigned j = 0; j < SIZE; ++j) {
      if (i == j)
        A[i][j] = i;
    }
    v[i] = 1;
  }

  int nbytes;
  for (unsigned i = 0; i < SIZE; ++i)
    for (unsigned j = 0; j < SIZE; ++j) {
      int32_t input = (int32_t)A[i][j];
      nbytes = write(fdw, (void *)&input, sizeof(input));
    }

  for (unsigned j = 0; j < SIZE; ++j) {
    int32_t input = v[j];
    nbytes = write(fdw, (void *)&input, sizeof(input));
  }

  // Now pull the output

  for (unsigned j = 0; j < SIZE; ++j) {
    int32_t output = 0;
    nbytes = read(fdr, (void *)&output, sizeof(output));
    printf("Out[%d] = %d", j, output);
  }

  //   // Number of test instances
  //   const int N = 180;

  //   // Arrays to store test data and expected results
  //   digit inputs[N];
  //   int expecteds[N];

  //   // Timer
  //   Timer timer("digitrec FPGA");

  //   int nbytes;
  //   int error = 0;
  //   int num_test_insts = 0;
  //   bit32_t interpreted_digit;

  //   //--------------------------------------------------------------------
  //   // Read data from the input file into two arrays
  //   //--------------------------------------------------------------------
  //   for (int i = 0; i < N; ++i) {
  //     assert(std::getline(myfile, line));
  //     // Read handwritten digit input
  //     std::string hex_digit = line.substr(2, line.find(",") - 2);
  //     digit input_digit = hexstring_to_int64(hex_digit);
  //     // Read expected digit
  //     int input_value = strtoul(
  //         line.substr(line.find(",") + 1, line.length()).c_str(), NULL, 10);

  //     // Store the digits into arrays
  //     inputs[i] = input_digit;
  //     expecteds[i] = input_value;
  //   }

  //   timer.start();
  //   int nbytes;
  //   int32_t sinput;
  //   int32_t soutput;
  //   for (int i = 0; i < N; i++) {
  //     sinput = inputs[i].range(31, 0);
  //     nbytes = write(fdw, (void *)&sinput, sizeof(sinput));
  //     assert(nbytes == sizeof(sinput));
  //     sinput = inputs[i].range(48, 32);
  //     nbytes = write(fdw, (void *)&sinput, sizeof(sinput));
  //     assert(nbytes == sizeof(sinput));

  //     num_test_insts++;
  //   }

  //   for (int i = 0; i < N; i++) {

  //     nbytes = read(fdr, (void *)&soutput, sizeof(soutput));
  //     // assert (nbytes == sizeof(soutput));
  //     // printf("%d\n", soutput);

  //     if (expecteds[i] != soutput) {
  //       error++;
  //     }
  //   }

  //   timer.stop();

  //   // Report overall error out of all testing instances
  //   std::cout << "Number of test instances = " << num_test_insts <<
  // std::endl;
  //   std::cout << "Overall Error Rate = " << std::setprecision(3)
  //             << ((double)error / num_test_insts) * 100 << "%" << std::endl;

  //   // Close input file for the testing set
  //   myfile.close();

  return 0;
}