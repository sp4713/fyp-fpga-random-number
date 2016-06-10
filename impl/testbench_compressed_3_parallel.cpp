#include <ap_int.h>

void freq_serial(ap_uint<32> freqStream[32], ap_uint<32> serialTwoStream[96],
		ap_uint<32> serialThreeStream[112], ap_uint<32> seed, ap_uint<44> n,
		ap_uint<1> offset);

int main() {
	//test parameters
	ap_uint<1> test_offset = 1;
	ap_uint<32> test_seed = 0;
	ap_uint<44> test_sample_size = 50000;
	//ap_uint<44> test_sample_size = 2000;

	//expected frequency computations
	/*
	ap_uint<32> freq_expected = test_sample_size / (8192); //50% of occurring for each sample * 2^11
	ap_uint<32> serial_two_expected = test_sample_size / (32768);
	ap_uint<32> serial_three_expected = test_sample_size / (256);
*/
	ap_uint<44> freq_expected = test_sample_size / (2);
	ap_uint<44> serial_two_expected = test_sample_size / (2*4);
	ap_uint<44> serial_three_expected = test_sample_size / (3*8);

	//initialisations of concatenated histograms
	ap_uint<32> freq_test_stream[32];
	ap_uint<32> serial_two_test_stream[96];
	ap_uint<32> serial_three_test_stream[112];

	for (int i = 0; i < 32; i++) {
		freq_test_stream[i] = 0;
	}
	for (int i = 0; i < 96; i++) {
		serial_two_test_stream[i] = 0;
	}
	for (int i = 0; i < 112; i++) {
		serial_three_test_stream[i] = 0;
	}

	//declarations of decompressed histograms
	ap_uint<44> freq_big_stream[32];
	ap_uint<44> serial_two_big_stream[128];
	ap_uint<44> serial_three_big_stream[128];

	for (int i = 0; i < 32; i++) {
		freq_big_stream[i] = 0;
	}
	for (int i = 0; i < 128; i++) {
		serial_two_big_stream[i] = 0;
	}
	for (int i = 0; i < 128; i++) {
		serial_three_big_stream[i] = 0;
	}

	//run testbench

	freq_serial(freq_test_stream, serial_two_test_stream,
			serial_three_test_stream, test_seed, test_sample_size, test_offset);

	//frequency test decompression
	for (int i = 0; i < 32; i++) {
		freq_big_stream[i] = freq_test_stream[i] << 12;
	}
	printf("Frequency Test\n");
	for(int j=0; j<32; j++){
		printf("Bit %d: Observed: %d. Expected: %d\n",j,(int)freq_big_stream[j],(int)freq_expected);
	}

	//compute missing values
	//serial two-tuple test decompression
	for (int i = 0; i<96; i++){
		serial_two_big_stream[i+i/3] = serial_two_test_stream[i] << 11;
	}
	for (int i = 0; i<32; i++){
		serial_two_big_stream[i * 4 + 3] = (serial_two_expected * 4)
				- (serial_two_big_stream[i * 4])
				- (serial_two_big_stream[i * 4 + 1])
				- (serial_two_big_stream[i * 4 + 2]);
	}
	printf("2-Tuple Test\n");
	for(int j=0; j<128; j++){
		printf("Bit %d, tuple %d: Observed: %d. Expected: %d\n", j / 4, j % 4,
				(int) serial_two_big_stream[j], (int) serial_two_expected);
	}

	//serial three-tuple test decompression
	for (int i = 0; i < 112; i++) {
		serial_three_big_stream[i + (i / 7)] = serial_three_test_stream[i] << 11;
	}

	for (int i = 0; i < 16; i++) {
		serial_three_big_stream[i * 8 + 7] = (serial_three_expected * 8)
				- (serial_three_big_stream[i * 8])
				- (serial_three_big_stream[i * 8 + 1])
				- (serial_three_big_stream[i * 8 + 2])
				- (serial_three_big_stream[i * 8 + 3])
				- (serial_three_big_stream[i * 8 + 4])
				- (serial_three_big_stream[i * 8 + 5])
				- (serial_three_big_stream[i * 8 + 6]);
	}

	printf("3-Tuple Test\n");
	for(int j=0; j<128; j++){
		printf("Bit %d, tuple %d: Observed: %d. Expected: %d\n", (j / 8)*2+(int)test_offset, j % 8,
				(int) serial_three_big_stream[j], (int) serial_three_expected);
	}
}
