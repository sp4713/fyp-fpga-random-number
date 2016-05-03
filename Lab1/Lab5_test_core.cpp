#include <ap_int.h>
#include <math.h>
#include <hls_stream.h>

void simpleCounter(ap_uint<32> *seed, ap_uint<32> *out, ap_uint<32> *n);

int main(){
	printf("Testing simpleCounter for initial seed=0");
	ap_uint<32> seed = 0;
	ap_uint<32> out = 0;
	ap_uint<32> n = 5;
	//ap_uint<32> n = 16;
	//ap_uint<32> n = 32;
	//ap_uint<32> n = 4;
	//ap_uint<32> n = 4;
	ap_uint<32> sum;
		simpleCounter(&seed, &out, &n);
		printf("Out: %d, n: %d, seed: %d\n",(unsigned int)out,(unsigned int)seed,(unsigned int)n);
		sum+=out;
		simpleCounter(&seed, &out, &n);
		printf("Out: %d, n: %d, seed: %d\n",(unsigned int)out,(unsigned int)seed,(unsigned int)n);
		sum+=out;
		simpleCounter(&seed, &out, &n);
		printf("Out: %d, n: %d, seed: %d\n",(unsigned int)out,(unsigned int)seed,(unsigned int)n);
		sum+=out;
	return 0;
}
