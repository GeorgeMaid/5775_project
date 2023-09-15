#include "mvecmult.h"
#include <stdint.h>
#include <hls_stream.h>
#include "ap_int.h"

/* The function mvecmult is the hw implimentation of matrix vector
multiplication
that will be tested when peforming Vivado testing
*/

typedef ap_uint<32> bit32_t;

void dut(hls::stream<bit32_t> &strm_in, hls::stream<bit32_t> &strm_out) {

  int A_tmp[SIZE][SIZE];
  int v_tmp[SIZE];
  int result[SIZE];
  for (unsigned i = 0; i < SIZE; ++i)
    for (unsigned j = 0; j < SIZE; ++j)
      A_tmp[i][j] = strm_in.read();
  for (unsigned i = 0; i < SIZE; ++i)
    v_tmp[i] = strm_in.read();
  mvecmult(A_tmp, v_tmp, result);

  for (unsigned i = 0; i < SIZE; ++i)
    strm_out.write(result[i]);
}

void mvecmult(int A[SIZE][SIZE], int v[SIZE], int result[SIZE]) {
#pragma HLS array_partition variable = A dim = 2 complete
#pragma HLS array_partition variable = v complete

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
