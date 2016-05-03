//Vivado HLS BRAM interface
#include <hls_math.h>

void crazyFunction(float x[100], float y, float res[100]){
#pragma HLS INTERFACE s_axilite port=y bundle=CTRL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS
#pragma HLS INTERFACE bram port=x
#pragma HLS INTERFACE bram port=res
	for(int idx=0; idx<100; idx++){
		res[idx] = (hls::sin(x[idx]) + hls::sqrtf(hls::expf(y)))/2;
	}
}
