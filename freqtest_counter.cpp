#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> outStream[32], ap_uint<32> seed, ap_uint<44> n) {
	// seed is 0 to 2^32-1 inclusive
	ap_uint<32> out[32];
	ap_uint<32> temp[32];
	ap_uint<32> count[32];

	//initialise
	for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
		out[i] = 0;
		temp[i] = 0;
		count[i] = 0;
	}

	//for every sample
	for (int idx = 0; idx < n; idx++) {
#pragma HLS UNROLL

		//detect 1s
		for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
			//read current count of 1s
			temp[i] = out[i];
			count[i] = (seed & (0x1 << i)) >> i;
			outStream[i] = out[i];
			out[i] = temp[i] + count[i];
		}
		seed++;
	}
};
