#include <ap_int.h>

void freq_serial(ap_uint<32> freqStream[32], ap_uint<32> serialStream[128],
		ap_uint<32> seed, ap_uint<44> n);

int main() {
	ap_uint<32> freq_test_stream[32];
	ap_uint<32> serial_test_stream[128];
	ap_uint<32> seed_value = 0;
	ap_uint<44> sample_size = 1000;

	ap_uint<32> freq_expected[32];
	ap_uint<32> serial_expected[128];

	for (int i = 0; i < 32; i++) {
		freq_test_stream[i] = 0;
		freq_expected[i] = sample_size / 2;
	}

	for (int i = 0; i < 128; i++) {
		serial_test_stream[i] = 0;
		serial_expected[i] = sample_size / 8;
	}

	freq_serial(freq_test_stream, serial_test_stream, seed_value, sample_size);


	for(int j=0; j<32; j++){
		printf("Bit %d: Observed: %d. Expected: %d",j,(int)freq_test_stream[j],(int)freq_expected[j]);
	}

	for(int j=0; j<128; j++){
		printf("Bit %d, tuple %d: Observed: %d. Expected: %d\n", j / 4, j % 4,
				(int) serial_test_stream[j], (int) serial_expected[j]);
	}
}
