#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> outStream[32], ap_uint<32> seed, ap_uint<44> n);
int main(){
	ap_uint<32> outputStream[32];
	ap_uint<32> inputSeed = 0;
	ap_uint<44> sampleSize = 500000;
	ap_uint<43> expectedCount = sampleSize/2;
	ap_uint<32> testStream[32];

	for(int i=0; i<32; i++){
		outputStream[i]=0;
		testStream[i]=0;
	}

	freqTest(outputStream, inputSeed, sampleSize);


	for(int j=0; j<32; j++){
		printf("Bit %d: Observed: %d. Expected: %d\n",j,(int)outputStream[j],(int)expectedCount);
	}
}
