#include <ap_int.h>

#define SEEDMAX 4294967295

ap_uint<32> seedNext(ap_uint<32> seed){
	//insert custom RNG here
	if(seed==SEEDMAX){
		return 0;
	}else{
		return seed+1;
	}
}

//do not edit from here onwards

void freq_serial(ap_uint<32> freqStream[32], ap_uint<32> serialTwoStream[96],
		ap_uint<32> serialThreeStream[112], ap_uint<32> seed, ap_uint<44> n,
		ap_uint<1> offset) {

#pragma HLS INTERFACE s_axilite port=return bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=freqStream bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=serialTwoStream bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=serialThreeStream bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=seed bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=n bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=offset bundle=FREQ_PERIPH_BUS

	ap_uint<44> freqCount[32];
#pragma HLS ARRAY_PARTITION variable=freqCount complete dim=1

	ap_uint<43> serialTwoCount[96];
#pragma HLS ARRAY_PARTITION variable=serialTwoCount complete dim=1

	ap_uint<43> serialThreeCount[112];
#pragma HLS ARRAY_PARTITION variable=serialThreeCount complete dim=1

	ap_uint<32> seed_prev_prev, seed_prev;
	bool enableTwoSerial = 0;
	int enableThreeSerial = 0;

/*	Computations below will be done in software

	for (int i = 0; i < 32; i++) {
		freqCount[i] = 0;
	}
	for (int i = 0; i < 96; i++) {
		serialTwoCount[i] = 0;
	}
	for (int i = 0; i < 112; i++) {
		serialThreeCount[i] = 0;
	}
*/
	for (int i = 0; i < n; i++) {
#pragma HLS LOOP_TRIPCOUNT min=100 max=10000
#pragma HLS PIPELINE
		freqCount[0] += ((seed >> 0) & 1);
		freqCount[1] += ((seed >> 1) & 1);
		freqCount[2] += ((seed >> 2) & 1);
		freqCount[3] += ((seed >> 3) & 1);
		freqCount[4] += ((seed >> 4) & 1);
		freqCount[5] += ((seed >> 5) & 1);
		freqCount[6] += ((seed >> 6) & 1);
		freqCount[7] += ((seed >> 7) & 1);
		freqCount[8] += ((seed >> 8) & 1);
		freqCount[9] += ((seed >> 9) & 1);
		freqCount[10] += ((seed >> 10) & 1);
		freqCount[11] += ((seed >> 11) & 1);
		freqCount[12] += ((seed >> 12) & 1);
		freqCount[13] += ((seed >> 13) & 1);
		freqCount[14] += ((seed >> 14) & 1);
		freqCount[15] += ((seed >> 15) & 1);
		freqCount[16] += ((seed >> 16) & 1);
		freqCount[17] += ((seed >> 17) & 1);
		freqCount[18] += ((seed >> 18) & 1);
		freqCount[19] += ((seed >> 19) & 1);
		freqCount[20] += ((seed >> 20) & 1);
		freqCount[21] += ((seed >> 21) & 1);
		freqCount[22] += ((seed >> 22) & 1);
		freqCount[23] += ((seed >> 23) & 1);
		freqCount[24] += ((seed >> 24) & 1);
		freqCount[25] += ((seed >> 25) & 1);
		freqCount[26] += ((seed >> 26) & 1);
		freqCount[27] += ((seed >> 27) & 1);
		freqCount[28] += ((seed >> 28) & 1);
		freqCount[29] += ((seed >> 29) & 1);
		freqCount[30] += ((seed >> 30) & 1);
		freqCount[31] += ((seed >> 31) & 1);
		//end of freqCount algorithm

		seed_prev_prev = seed_prev;
		seed_prev = seed;
		seed = seedNext(seed);

		//serial two-tuple test
		enableTwoSerial=!enableTwoSerial;
		if (enableTwoSerial) {
			if(((seed_prev>>0)&1)==0){if(((seed>>0)&1)==0){serialTwoCount[0*3]++;}else{serialTwoCount[0*3+1]++;}}else{if(((seed>>0)&1)==0){serialTwoCount[0*3+2]++;}}
			if(((seed_prev>>1)&1)==0){if(((seed>>1)&1)==0){serialTwoCount[1*3]++;}else{serialTwoCount[1*3+1]++;}}else{if(((seed>>1)&1)==0){serialTwoCount[1*3+2]++;}}
			if(((seed_prev>>2)&1)==0){if(((seed>>2)&1)==0){serialTwoCount[2*3]++;}else{serialTwoCount[2*3+1]++;}}else{if(((seed>>2)&1)==0){serialTwoCount[2*3+2]++;}}
			if(((seed_prev>>3)&1)==0){if(((seed>>3)&1)==0){serialTwoCount[3*3]++;}else{serialTwoCount[3*3+1]++;}}else{if(((seed>>3)&1)==0){serialTwoCount[3*3+2]++;}}
			if(((seed_prev>>4)&1)==0){if(((seed>>4)&1)==0){serialTwoCount[4*3]++;}else{serialTwoCount[4*3+1]++;}}else{if(((seed>>4)&1)==0){serialTwoCount[4*3+2]++;}}
			if(((seed_prev>>5)&1)==0){if(((seed>>5)&1)==0){serialTwoCount[5*3]++;}else{serialTwoCount[5*3+1]++;}}else{if(((seed>>5)&1)==0){serialTwoCount[5*3+2]++;}}
			if(((seed_prev>>6)&1)==0){if(((seed>>6)&1)==0){serialTwoCount[6*3]++;}else{serialTwoCount[6*3+1]++;}}else{if(((seed>>6)&1)==0){serialTwoCount[6*3+2]++;}}
			if(((seed_prev>>7)&1)==0){if(((seed>>7)&1)==0){serialTwoCount[7*3]++;}else{serialTwoCount[7*3+1]++;}}else{if(((seed>>7)&1)==0){serialTwoCount[7*3+2]++;}}
			if(((seed_prev>>8)&1)==0){if(((seed>>8)&1)==0){serialTwoCount[8*3]++;}else{serialTwoCount[8*3+1]++;}}else{if(((seed>>8)&1)==0){serialTwoCount[8*3+2]++;}}
			if(((seed_prev>>9)&1)==0){if(((seed>>9)&1)==0){serialTwoCount[9*3]++;}else{serialTwoCount[9*3+1]++;}}else{if(((seed>>9)&1)==0){serialTwoCount[9*3+2]++;}}
			if(((seed_prev>>10)&1)==0){if(((seed>>10)&1)==0){serialTwoCount[10*3]++;}else{serialTwoCount[10*3+1]++;}}else{if(((seed>>10)&1)==0){serialTwoCount[10*3+2]++;}}
			if(((seed_prev>>11)&1)==0){if(((seed>>11)&1)==0){serialTwoCount[11*3]++;}else{serialTwoCount[11*3+1]++;}}else{if(((seed>>11)&1)==0){serialTwoCount[11*3+2]++;}}
			if(((seed_prev>>12)&1)==0){if(((seed>>12)&1)==0){serialTwoCount[12*3]++;}else{serialTwoCount[12*3+1]++;}}else{if(((seed>>12)&1)==0){serialTwoCount[12*3+2]++;}}
			if(((seed_prev>>13)&1)==0){if(((seed>>13)&1)==0){serialTwoCount[13*3]++;}else{serialTwoCount[13*3+1]++;}}else{if(((seed>>13)&1)==0){serialTwoCount[13*3+2]++;}}
			if(((seed_prev>>14)&1)==0){if(((seed>>14)&1)==0){serialTwoCount[14*3]++;}else{serialTwoCount[14*3+1]++;}}else{if(((seed>>14)&1)==0){serialTwoCount[14*3+2]++;}}
			if(((seed_prev>>15)&1)==0){if(((seed>>15)&1)==0){serialTwoCount[15*3]++;}else{serialTwoCount[15*3+1]++;}}else{if(((seed>>15)&1)==0){serialTwoCount[15*3+2]++;}}
			if(((seed_prev>>16)&1)==0){if(((seed>>16)&1)==0){serialTwoCount[16*3]++;}else{serialTwoCount[16*3+1]++;}}else{if(((seed>>16)&1)==0){serialTwoCount[16*3+2]++;}}
			if(((seed_prev>>17)&1)==0){if(((seed>>17)&1)==0){serialTwoCount[17*3]++;}else{serialTwoCount[17*3+1]++;}}else{if(((seed>>17)&1)==0){serialTwoCount[17*3+2]++;}}
			if(((seed_prev>>18)&1)==0){if(((seed>>18)&1)==0){serialTwoCount[18*3]++;}else{serialTwoCount[18*3+1]++;}}else{if(((seed>>18)&1)==0){serialTwoCount[18*3+2]++;}}
			if(((seed_prev>>19)&1)==0){if(((seed>>19)&1)==0){serialTwoCount[19*3]++;}else{serialTwoCount[19*3+1]++;}}else{if(((seed>>19)&1)==0){serialTwoCount[19*3+2]++;}}
			if(((seed_prev>>20)&1)==0){if(((seed>>20)&1)==0){serialTwoCount[20*3]++;}else{serialTwoCount[20*3+1]++;}}else{if(((seed>>20)&1)==0){serialTwoCount[20*3+2]++;}}
			if(((seed_prev>>21)&1)==0){if(((seed>>21)&1)==0){serialTwoCount[21*3]++;}else{serialTwoCount[21*3+1]++;}}else{if(((seed>>21)&1)==0){serialTwoCount[21*3+2]++;}}
			if(((seed_prev>>22)&1)==0){if(((seed>>22)&1)==0){serialTwoCount[22*3]++;}else{serialTwoCount[22*3+1]++;}}else{if(((seed>>22)&1)==0){serialTwoCount[22*3+2]++;}}
			if(((seed_prev>>23)&1)==0){if(((seed>>23)&1)==0){serialTwoCount[23*3]++;}else{serialTwoCount[23*3+1]++;}}else{if(((seed>>23)&1)==0){serialTwoCount[23*3+2]++;}}
			if(((seed_prev>>24)&1)==0){if(((seed>>24)&1)==0){serialTwoCount[24*3]++;}else{serialTwoCount[24*3+1]++;}}else{if(((seed>>24)&1)==0){serialTwoCount[24*3+2]++;}}
			if(((seed_prev>>25)&1)==0){if(((seed>>25)&1)==0){serialTwoCount[25*3]++;}else{serialTwoCount[25*3+1]++;}}else{if(((seed>>25)&1)==0){serialTwoCount[25*3+2]++;}}
			if(((seed_prev>>26)&1)==0){if(((seed>>26)&1)==0){serialTwoCount[26*3]++;}else{serialTwoCount[26*3+1]++;}}else{if(((seed>>26)&1)==0){serialTwoCount[26*3+2]++;}}
			if(((seed_prev>>27)&1)==0){if(((seed>>27)&1)==0){serialTwoCount[27*3]++;}else{serialTwoCount[27*3+1]++;}}else{if(((seed>>27)&1)==0){serialTwoCount[27*3+2]++;}}
			if(((seed_prev>>28)&1)==0){if(((seed>>28)&1)==0){serialTwoCount[28*3]++;}else{serialTwoCount[28*3+1]++;}}else{if(((seed>>28)&1)==0){serialTwoCount[28*3+2]++;}}
			if(((seed_prev>>29)&1)==0){if(((seed>>29)&1)==0){serialTwoCount[29*3]++;}else{serialTwoCount[29*3+1]++;}}else{if(((seed>>29)&1)==0){serialTwoCount[29*3+2]++;}}
			if(((seed_prev>>30)&1)==0){if(((seed>>30)&1)==0){serialTwoCount[30*3]++;}else{serialTwoCount[30*3+1]++;}}else{if(((seed>>30)&1)==0){serialTwoCount[30*3+2]++;}}
			if(((seed_prev>>31)&1)==0){if(((seed>>31)&1)==0){serialTwoCount[31*3]++;}else{serialTwoCount[31*3+1]++;}}else{if(((seed>>31)&1)==0){serialTwoCount[31*3+2]++;}}
		}

		//serial three-tuple test
		enableThreeSerial++;
		if(enableThreeSerial==3){
			enableThreeSerial = 0;
			if (((seed_prev_prev >> offset) & 1) == 0) {
				if (((seed_prev >> offset) & 1) == 0) {
					if (((seed >> offset) & 1) == 0) {
						serialThreeCount[0 * 7]++;
					} else {
						serialThreeCount[0 * 7 + 1]++;
					}
				} else {
					if (((seed >> offset) & 1) == 0) {
						serialThreeCount[0 * 7 + 2]++;
					} else {
						serialThreeCount[0 * 7 + 3]++;
					}
				}
			} else {
				if (((seed_prev >> offset) & 1) == 0) {
					if (((seed >> offset) & 1) == 0) {
						serialThreeCount[0 * 7 + 4]++;
					} else {
						serialThreeCount[0 * 7 + 5]++;
					}
				} else {
					if (((seed >> offset) & 1) == 0) {
						serialThreeCount[0 * 7 + 6]++;
					}
				}
			}
			if (((seed_prev_prev >> (2 + offset)) & 1) == 0) {
				if (((seed_prev >> (2 + offset)) & 1) == 0) {
					if (((seed >> (2 + offset)) & 1) == 0) {
						serialThreeCount[1 * 7]++;
					} else {
						serialThreeCount[1 * 7 + 1]++;
					}
				} else {
					if (((seed >> (2 + offset)) & 1) == 0) {
						serialThreeCount[1 * 7 + 2]++;
					} else {
						serialThreeCount[1 * 7 + 3]++;
					}
				}
			} else {
				if (((seed_prev >> (2 + offset)) & 1) == 0) {
					if (((seed >> (2 + offset)) & 1) == 0) {
						serialThreeCount[1 * 7 + 4]++;
					} else {
						serialThreeCount[1 * 7 + 5]++;
					}
				} else {
					if (((seed >> (2 + offset)) & 1) == 0) {
						serialThreeCount[1 * 7 + 6]++;
					}
				}
			}
			if (((seed_prev_prev >> (4+offset)) & 1) == 0) {if (((seed_prev >> (4+offset)) & 1) == 0) {if (((seed >> (4+offset)) & 1) == 0) {serialThreeCount[2 * 7]++;} else {serialThreeCount[2 * 7 + 1]++;}}else {if (((seed >> (4+offset)) & 1) == 0) {serialThreeCount[2 * 7 + 2]++;} else {serialThreeCount[2 * 7 + 3]++;}}}else{if (((seed_prev >> (4+offset)) & 1) == 0) {if (((seed >> (4+offset)) & 1) == 0) {serialThreeCount[2 * 7 + 4]++;} else {serialThreeCount[2 * 7 + 5]++;}}else{if (((seed >> (4+offset)) & 1) == 0) {serialThreeCount[2 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (6+offset)) & 1) == 0) {if (((seed_prev >> (6+offset)) & 1) == 0) {if (((seed >> (6+offset)) & 1) == 0) {serialThreeCount[3 * 7]++;} else {serialThreeCount[3 * 7 + 1]++;}}else {if (((seed >> (6+offset)) & 1) == 0) {serialThreeCount[3 * 7 + 2]++;} else {serialThreeCount[3 * 7 + 3]++;}}}else{if (((seed_prev >> (6+offset)) & 1) == 0) {if (((seed >> (6+offset)) & 1) == 0) {serialThreeCount[3 * 7 + 4]++;} else {serialThreeCount[3 * 7 + 5]++;}}else{if (((seed >> (6+offset)) & 1) == 0) {serialThreeCount[3 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (8+offset)) & 1) == 0) {if (((seed_prev >> (8+offset)) & 1) == 0) {if (((seed >> (8+offset)) & 1) == 0) {serialThreeCount[4 * 7]++;} else {serialThreeCount[4 * 7 + 1]++;}}else {if (((seed >> (8+offset)) & 1) == 0) {serialThreeCount[4 * 7 + 2]++;} else {serialThreeCount[4 * 7 + 3]++;}}}else{if (((seed_prev >> (8+offset)) & 1) == 0) {if (((seed >> (8+offset)) & 1) == 0) {serialThreeCount[4 * 7 + 4]++;} else {serialThreeCount[4 * 7 + 5]++;}}else{if (((seed >> (8+offset)) & 1) == 0) {serialThreeCount[4 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (10+offset)) & 1) == 0) {if (((seed_prev >> (10+offset)) & 1) == 0) {if (((seed >> (10+offset)) & 1) == 0) {serialThreeCount[5 * 7]++;} else {serialThreeCount[5 * 7 + 1]++;}}else {if (((seed >> (10+offset)) & 1) == 0) {serialThreeCount[5 * 7 + 2]++;} else {serialThreeCount[5 * 7 + 3]++;}}}else{if (((seed_prev >> (10+offset)) & 1) == 0) {if (((seed >> (10+offset)) & 1) == 0) {serialThreeCount[5 * 7 + 4]++;} else {serialThreeCount[5 * 7 + 5]++;}}else{if (((seed >> (10+offset)) & 1) == 0) {serialThreeCount[5 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (12+offset)) & 1) == 0) {if (((seed_prev >> (12+offset)) & 1) == 0) {if (((seed >> (12+offset)) & 1) == 0) {serialThreeCount[6 * 7]++;} else {serialThreeCount[6 * 7 + 1]++;}}else {if (((seed >> (12+offset)) & 1) == 0) {serialThreeCount[6 * 7 + 2]++;} else {serialThreeCount[6 * 7 + 3]++;}}}else{if (((seed_prev >> (12+offset)) & 1) == 0) {if (((seed >> (12+offset)) & 1) == 0) {serialThreeCount[6 * 7 + 4]++;} else {serialThreeCount[6 * 7 + 5]++;}}else{if (((seed >> (12+offset)) & 1) == 0) {serialThreeCount[6 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (14+offset)) & 1) == 0) {if (((seed_prev >> (14+offset)) & 1) == 0) {if (((seed >> (14+offset)) & 1) == 0) {serialThreeCount[7 * 7]++;} else {serialThreeCount[7 * 7 + 1]++;}}else {if (((seed >> (14+offset)) & 1) == 0) {serialThreeCount[7 * 7 + 2]++;} else {serialThreeCount[7 * 7 + 3]++;}}}else{if (((seed_prev >> (14+offset)) & 1) == 0) {if (((seed >> (14+offset)) & 1) == 0) {serialThreeCount[7 * 7 + 4]++;} else {serialThreeCount[7 * 7 + 5]++;}}else{if (((seed >> (14+offset)) & 1) == 0) {serialThreeCount[7 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (16+offset)) & 1) == 0) {if (((seed_prev >> (16+offset)) & 1) == 0) {if (((seed >> (16+offset)) & 1) == 0) {serialThreeCount[8 * 7]++;} else {serialThreeCount[8 * 7 + 1]++;}}else {if (((seed >> (16+offset)) & 1) == 0) {serialThreeCount[8 * 7 + 2]++;} else {serialThreeCount[8 * 7 + 3]++;}}}else{if (((seed_prev >> (16+offset)) & 1) == 0) {if (((seed >> (16+offset)) & 1) == 0) {serialThreeCount[8 * 7 + 4]++;} else {serialThreeCount[8 * 7 + 5]++;}}else{if (((seed >> (16+offset)) & 1) == 0) {serialThreeCount[8 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (18+offset)) & 1) == 0) {if (((seed_prev >> (18+offset)) & 1) == 0) {if (((seed >> (18+offset)) & 1) == 0) {serialThreeCount[9 * 7]++;} else {serialThreeCount[9 * 7 + 1]++;}}else {if (((seed >> (18+offset)) & 1) == 0) {serialThreeCount[9 * 7 + 2]++;} else {serialThreeCount[9 * 7 + 3]++;}}}else{if (((seed_prev >> (18+offset)) & 1) == 0) {if (((seed >> (18+offset)) & 1) == 0) {serialThreeCount[9 * 7 + 4]++;} else {serialThreeCount[9 * 7 + 5]++;}}else{if (((seed >> (18+offset)) & 1) == 0) {serialThreeCount[9 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (20+offset)) & 1) == 0) {if (((seed_prev >> (20+offset)) & 1) == 0) {if (((seed >> (20+offset)) & 1) == 0) {serialThreeCount[10 * 7]++;} else {serialThreeCount[10 * 7 + 1]++;}}else {if (((seed >> (20+offset)) & 1) == 0) {serialThreeCount[10 * 7 + 2]++;} else {serialThreeCount[10 * 7 + 3]++;}}}else{if (((seed_prev >> (20+offset)) & 1) == 0) {if (((seed >> (20+offset)) & 1) == 0) {serialThreeCount[10 * 7 + 4]++;} else {serialThreeCount[10 * 7 + 5]++;}}else{if (((seed >> (20+offset)) & 1) == 0) {serialThreeCount[10 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (22+offset)) & 1) == 0) {if (((seed_prev >> (22+offset)) & 1) == 0) {if (((seed >> (22+offset)) & 1) == 0) {serialThreeCount[11 * 7]++;} else {serialThreeCount[11 * 7 + 1]++;}}else {if (((seed >> (22+offset)) & 1) == 0) {serialThreeCount[11 * 7 + 2]++;} else {serialThreeCount[11 * 7 + 3]++;}}}else{if (((seed_prev >> (22+offset)) & 1) == 0) {if (((seed >> (22+offset)) & 1) == 0) {serialThreeCount[11 * 7 + 4]++;} else {serialThreeCount[11 * 7 + 5]++;}}else{if (((seed >> (22+offset)) & 1) == 0) {serialThreeCount[11 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (24+offset)) & 1) == 0) {if (((seed_prev >> (24+offset)) & 1) == 0) {if (((seed >> (24+offset)) & 1) == 0) {serialThreeCount[12 * 7]++;} else {serialThreeCount[12 * 7 + 1]++;}}else {if (((seed >> (24+offset)) & 1) == 0) {serialThreeCount[12 * 7 + 2]++;} else {serialThreeCount[12 * 7 + 3]++;}}}else{if (((seed_prev >> (24+offset)) & 1) == 0) {if (((seed >> (24+offset)) & 1) == 0) {serialThreeCount[12 * 7 + 4]++;} else {serialThreeCount[12 * 7 + 5]++;}}else{if (((seed >> (24+offset)) & 1) == 0) {serialThreeCount[12 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (26+offset)) & 1) == 0) {if (((seed_prev >> (26+offset)) & 1) == 0) {if (((seed >> (26+offset)) & 1) == 0) {serialThreeCount[13 * 7]++;} else {serialThreeCount[13 * 7 + 1]++;}}else {if (((seed >> (26+offset)) & 1) == 0) {serialThreeCount[13 * 7 + 2]++;} else {serialThreeCount[13 * 7 + 3]++;}}}else{if (((seed_prev >> (26+offset)) & 1) == 0) {if (((seed >> (26+offset)) & 1) == 0) {serialThreeCount[13 * 7 + 4]++;} else {serialThreeCount[13 * 7 + 5]++;}}else{if (((seed >> (26+offset)) & 1) == 0) {serialThreeCount[13 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (28+offset)) & 1) == 0) {if (((seed_prev >> (28+offset)) & 1) == 0) {if (((seed >> (28+offset)) & 1) == 0) {serialThreeCount[14 * 7]++;} else {serialThreeCount[14 * 7 + 1]++;}}else {if (((seed >> (28+offset)) & 1) == 0) {serialThreeCount[14 * 7 + 2]++;} else {serialThreeCount[14 * 7 + 3]++;}}}else{if (((seed_prev >> (28+offset)) & 1) == 0) {if (((seed >> (28+offset)) & 1) == 0) {serialThreeCount[14 * 7 + 4]++;} else {serialThreeCount[14 * 7 + 5]++;}}else{if (((seed >> (28+offset)) & 1) == 0) {serialThreeCount[14 * 7 + 6]++;} }}
			if (((seed_prev_prev >> (30+offset)) & 1) == 0) {if (((seed_prev >> (30+offset)) & 1) == 0) {if (((seed >> (30+offset)) & 1) == 0) {serialThreeCount[15 * 7]++;} else {serialThreeCount[15 * 7 + 1]++;}}else {if (((seed >> (30+offset)) & 1) == 0) {serialThreeCount[15 * 7 + 2]++;} else {serialThreeCount[15 * 7 + 3]++;}}}else{if (((seed_prev >> (30+offset)) & 1) == 0) {if (((seed >> (30+offset)) & 1) == 0) {serialThreeCount[15 * 7 + 4]++;} else {serialThreeCount[15 * 7 + 5]++;}}else{if (((seed >> (30+offset)) & 1) == 0) {serialThreeCount[15 * 7 + 6]++;} }}
		}
	}
	for (int i = 0; i < 32; i++) {
		freqStream[i] = freqCount[i] >> 12;
	}
	for (int i = 0; i < 96; i++) {
		serialTwoStream[i] = serialTwoCount[i] >> 11;
	}
	for (int i = 0; i < 112; i++) {
		serialThreeStream[i] = serialThreeCount[i] >> 11;
	}
}
