//this programme works for RNG periods up to 2^38 only as it uses up LUTs to 99% with maximum bit

#include <ap_int.h>

#define SEEDMAX 4294967295

//update the seedNext function below with your desired RNG algorithm

ap_uint<32> seedNext(ap_uint<32> seed){
	if(seed==SEEDMAX){
		return 0;
	}else{
		return seed+1;
	}
}

//do not edit the main function below

void freq_serial(//ap_uint<32> freqStream[32], ap_uint<32> serialStream[128],
		ap_uint<32> serialBigStream[224], ap_uint<32> seed, ap_uint<44> n) {

#pragma HLS INTERFACE s_axilite port=return bundle=FREQ_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=freqStream bundle=FREQ_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=serialStream bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=serialBigStream bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=seed bundle=FREQ_PERIPH_BUS
#pragma HLS INTERFACE s_axilite port=n bundle=FREQ_PERIPH_BUS
/*
	//frequency test
	ap_uint<43> freqCount[32];
#pragma HLS ARRAY_PARTITION variable=freqCount complete dim=1

	//serial 2-tuple test
	ap_uint<43> serialCount[128];
#pragma HLS ARRAY_PARTITION variable=serialCount complete dim=1
*/	ap_uint<32> seed_prev = 0;
/*	bool enableSerial = 0;
*/
	//serial 3-tuple test
	ap_uint<37> serialBigCount[224];
#pragma HLS ARRAY_PARTITION variable=serialBigCount complete dim=1
	ap_uint<32> seed_prev_prev = 0;
	int enableBigSerial = 0;
/*
	for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
		freqCount[i] = 0;
	}
	for (int i = 0; i < 128; i++) {
#pragma HLS PIPELINE
		serialCount[i] = 0;
	}
*/
	for (int i = 0; i < 224; i++) {
		serialBigCount[i] = 0;
	}

	for (int i = 0; i < n; i++) {
#pragma HLS LOOP_TRIPCOUNT min=100 max=10000
#pragma HLS PIPELINE
		/*
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

*/		seed_prev_prev = seed_prev;
		seed_prev = seed;
		seed = seedNext(seed);
/*
		//serial 2-tuple test
		enableSerial=!enableSerial;
		if(enableSerial){
			if (((seed_prev >>0)&1)==0) {if (((seed >>0)&1)==0) {serialCount[0 * 4]++;} else {serialCount[0* 4 + 1]++;}} else {if (((seed >> 0)&1)==0) {serialCount[0 * 4 + 2]++;} else {serialCount[0* 4 + 3]++;}}
			if (((seed_prev >>1)&1)==0) {if (((seed >>1)&1)==0) {serialCount[1 * 4]++;} else {serialCount[1* 4 + 1]++;}} else {if (((seed >> 1)&1)==0) {serialCount[1 * 4 + 2]++;} else {serialCount[1* 4 + 3]++;}}
			if (((seed_prev >>2)&1)==0) {if (((seed >>2)&1)==0) {serialCount[2 * 4]++;} else {serialCount[2* 4 + 1]++;}} else {if (((seed >> 2)&1)==0) {serialCount[2 * 4 + 2]++;} else {serialCount[2* 4 + 3]++;}}
			if (((seed_prev >>3)&1)==0) {if (((seed >>3)&1)==0) {serialCount[3 * 4]++;} else {serialCount[3* 4 + 1]++;}} else {if (((seed >> 3)&1)==0) {serialCount[3 * 4 + 2]++;} else {serialCount[3* 4 + 3]++;}}
			if (((seed_prev >>4)&1)==0) {if (((seed >>4)&1)==0) {serialCount[4 * 4]++;} else {serialCount[4* 4 + 1]++;}} else {if (((seed >> 4)&1)==0) {serialCount[4 * 4 + 2]++;} else {serialCount[4* 4 + 3]++;}}
			if (((seed_prev >>5)&1)==0) {if (((seed >>5)&1)==0) {serialCount[5 * 4]++;} else {serialCount[5* 4 + 1]++;}} else {if (((seed >> 5)&1)==0) {serialCount[5 * 4 + 2]++;} else {serialCount[5* 4 + 3]++;}}
			if (((seed_prev >>6)&1)==0) {if (((seed >>6)&1)==0) {serialCount[6 * 4]++;} else {serialCount[6* 4 + 1]++;}} else {if (((seed >> 6)&1)==0) {serialCount[6 * 4 + 2]++;} else {serialCount[6* 4 + 3]++;}}
			if (((seed_prev >>7)&1)==0) {if (((seed >>7)&1)==0) {serialCount[7 * 4]++;} else {serialCount[7* 4 + 1]++;}} else {if (((seed >> 7)&1)==0) {serialCount[7 * 4 + 2]++;} else {serialCount[7* 4 + 3]++;}}
			if (((seed_prev >>8)&1)==0) {if (((seed >>8)&1)==0) {serialCount[8 * 4]++;} else {serialCount[8* 4 + 1]++;}} else {if (((seed >> 8)&1)==0) {serialCount[8 * 4 + 2]++;} else {serialCount[8* 4 + 3]++;}}
			if (((seed_prev >>9)&1)==0) {if (((seed >>9)&1)==0) {serialCount[9 * 4]++;} else {serialCount[9* 4 + 1]++;}} else {if (((seed >> 9)&1)==0) {serialCount[9 * 4 + 2]++;} else {serialCount[9* 4 + 3]++;}}
			if (((seed_prev >>10)&1)==0) {if (((seed >>10)&1)==0) {serialCount[10 * 4]++;} else {serialCount[10* 4 + 1]++;}} else {if (((seed >> 10)&1)==0) {serialCount[10 * 4 + 2]++;} else {serialCount[10* 4 + 3]++;}}
			if (((seed_prev >>11)&1)==0) {if (((seed >>11)&1)==0) {serialCount[11 * 4]++;} else {serialCount[11* 4 + 1]++;}} else {if (((seed >> 11)&1)==0) {serialCount[11 * 4 + 2]++;} else {serialCount[11* 4 + 3]++;}}
			if (((seed_prev >>12)&1)==0) {if (((seed >>12)&1)==0) {serialCount[12 * 4]++;} else {serialCount[12* 4 + 1]++;}} else {if (((seed >> 12)&1)==0) {serialCount[12 * 4 + 2]++;} else {serialCount[12* 4 + 3]++;}}
			if (((seed_prev >>13)&1)==0) {if (((seed >>13)&1)==0) {serialCount[13 * 4]++;} else {serialCount[13* 4 + 1]++;}} else {if (((seed >> 13)&1)==0) {serialCount[13 * 4 + 2]++;} else {serialCount[13* 4 + 3]++;}}
			if (((seed_prev >>14)&1)==0) {if (((seed >>14)&1)==0) {serialCount[14 * 4]++;} else {serialCount[14* 4 + 1]++;}} else {if (((seed >> 14)&1)==0) {serialCount[14 * 4 + 2]++;} else {serialCount[14* 4 + 3]++;}}
			if (((seed_prev >>15)&1)==0) {if (((seed >>15)&1)==0) {serialCount[15 * 4]++;} else {serialCount[15* 4 + 1]++;}} else {if (((seed >> 15)&1)==0) {serialCount[15 * 4 + 2]++;} else {serialCount[15* 4 + 3]++;}}
			if (((seed_prev >>16)&1)==0) {if (((seed >>16)&1)==0) {serialCount[16 * 4]++;} else {serialCount[16* 4 + 1]++;}} else {if (((seed >> 16)&1)==0) {serialCount[16 * 4 + 2]++;} else {serialCount[16* 4 + 3]++;}}
			if (((seed_prev >>17)&1)==0) {if (((seed >>17)&1)==0) {serialCount[17 * 4]++;} else {serialCount[17* 4 + 1]++;}} else {if (((seed >> 17)&1)==0) {serialCount[17 * 4 + 2]++;} else {serialCount[17* 4 + 3]++;}}
			if (((seed_prev >>18)&1)==0) {if (((seed >>18)&1)==0) {serialCount[18 * 4]++;} else {serialCount[18* 4 + 1]++;}} else {if (((seed >> 18)&1)==0) {serialCount[18 * 4 + 2]++;} else {serialCount[18* 4 + 3]++;}}
			if (((seed_prev >>19)&1)==0) {if (((seed >>19)&1)==0) {serialCount[19 * 4]++;} else {serialCount[19* 4 + 1]++;}} else {if (((seed >> 19)&1)==0) {serialCount[19 * 4 + 2]++;} else {serialCount[19* 4 + 3]++;}}
			if (((seed_prev >>20)&1)==0) {if (((seed >>20)&1)==0) {serialCount[20 * 4]++;} else {serialCount[20* 4 + 1]++;}} else {if (((seed >> 20)&1)==0) {serialCount[20 * 4 + 2]++;} else {serialCount[20* 4 + 3]++;}}
			if (((seed_prev >>21)&1)==0) {if (((seed >>21)&1)==0) {serialCount[21 * 4]++;} else {serialCount[21* 4 + 1]++;}} else {if (((seed >> 21)&1)==0) {serialCount[21 * 4 + 2]++;} else {serialCount[21* 4 + 3]++;}}
			if (((seed_prev >>22)&1)==0) {if (((seed >>22)&1)==0) {serialCount[22 * 4]++;} else {serialCount[22* 4 + 1]++;}} else {if (((seed >> 22)&1)==0) {serialCount[22 * 4 + 2]++;} else {serialCount[22* 4 + 3]++;}}
			if (((seed_prev >>23)&1)==0) {if (((seed >>23)&1)==0) {serialCount[23 * 4]++;} else {serialCount[23* 4 + 1]++;}} else {if (((seed >> 23)&1)==0) {serialCount[23 * 4 + 2]++;} else {serialCount[23* 4 + 3]++;}}
			if (((seed_prev >>24)&1)==0) {if (((seed >>24)&1)==0) {serialCount[24 * 4]++;} else {serialCount[24* 4 + 1]++;}} else {if (((seed >> 24)&1)==0) {serialCount[24 * 4 + 2]++;} else {serialCount[24* 4 + 3]++;}}
			if (((seed_prev >>25)&1)==0) {if (((seed >>25)&1)==0) {serialCount[25 * 4]++;} else {serialCount[25* 4 + 1]++;}} else {if (((seed >> 25)&1)==0) {serialCount[25 * 4 + 2]++;} else {serialCount[25* 4 + 3]++;}}
			if (((seed_prev >>26)&1)==0) {if (((seed >>26)&1)==0) {serialCount[26 * 4]++;} else {serialCount[26* 4 + 1]++;}} else {if (((seed >> 26)&1)==0) {serialCount[26 * 4 + 2]++;} else {serialCount[26* 4 + 3]++;}}
			if (((seed_prev >>27)&1)==0) {if (((seed >>27)&1)==0) {serialCount[27 * 4]++;} else {serialCount[27* 4 + 1]++;}} else {if (((seed >> 27)&1)==0) {serialCount[27 * 4 + 2]++;} else {serialCount[27* 4 + 3]++;}}
			if (((seed_prev >>28)&1)==0) {if (((seed >>28)&1)==0) {serialCount[28 * 4]++;} else {serialCount[28* 4 + 1]++;}} else {if (((seed >> 28)&1)==0) {serialCount[28 * 4 + 2]++;} else {serialCount[28* 4 + 3]++;}}
			if (((seed_prev >>29)&1)==0) {if (((seed >>29)&1)==0) {serialCount[29 * 4]++;} else {serialCount[29* 4 + 1]++;}} else {if (((seed >> 29)&1)==0) {serialCount[29 * 4 + 2]++;} else {serialCount[29* 4 + 3]++;}}
			if (((seed_prev >>30)&1)==0) {if (((seed >>30)&1)==0) {serialCount[30 * 4]++;} else {serialCount[30* 4 + 1]++;}} else {if (((seed >> 30)&1)==0) {serialCount[30 * 4 + 2]++;} else {serialCount[30* 4 + 3]++;}}
			if (((seed_prev >>31)&1)==0) {if (((seed >>31)&1)==0) {serialCount[31 * 4]++;} else {serialCount[31* 4 + 1]++;}} else {if (((seed >> 31)&1)==0) {serialCount[31 * 4 + 2]++;} else {serialCount[31* 4 + 3]++;}}
		}*/
		enableBigSerial++;
		if(enableBigSerial==3){
			enableBigSerial=0;
			if (((seed_prev_prev >> 0) & 1) == 0) {if (((seed_prev >> 0) & 1) == 0) {if (((seed >> 0) & 1) == 0) {serialBigCount[0 * 7]++;} else {serialBigCount[0 * 7 + 1]++;serialBigCount[0 * 7 + 1]++;}}else {if (((seed >> 0) & 1) == 0) {serialBigCount[0 * 7 + 2]++;} else {serialBigCount[0 * 7 + 3]++;}}}else{if (((seed_prev >> 0) & 1) == 0) {if (((seed >> 0) & 1) == 0) {serialBigCount[0* 7 + 4]++;serialBigCount[0 * 7 + 4]++;} else {serialBigCount[0 * 7 + 5]++;}}else{if (((seed >> 0) & 1) == 0) {serialBigCount[0 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 1) & 1) == 0) {if (((seed_prev >> 1) & 1) == 0) {if (((seed >> 1) & 1) == 0) {serialBigCount[1 * 7]++;} else {serialBigCount[1 * 7 + 1]++;serialBigCount[1 * 7 + 1]++;}}else {if (((seed >> 1) & 1) == 0) {serialBigCount[1 * 7 + 2]++;} else {serialBigCount[1 * 7 + 3]++;}}}else{if (((seed_prev >> 1) & 1) == 0) {if (((seed >> 1) & 1) == 0) {serialBigCount[1* 7 + 4]++;serialBigCount[1 * 7 + 4]++;} else {serialBigCount[1 * 7 + 5]++;}}else{if (((seed >> 1) & 1) == 0) {serialBigCount[1 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 2) & 1) == 0) {if (((seed_prev >> 2) & 1) == 0) {if (((seed >> 2) & 1) == 0) {serialBigCount[2 * 7]++;} else {serialBigCount[2 * 7 + 1]++;serialBigCount[2 * 7 + 1]++;}}else {if (((seed >> 2) & 1) == 0) {serialBigCount[2 * 7 + 2]++;} else {serialBigCount[2 * 7 + 3]++;}}}else{if (((seed_prev >> 2) & 1) == 0) {if (((seed >> 2) & 1) == 0) {serialBigCount[2* 7 + 4]++;serialBigCount[2 * 7 + 4]++;} else {serialBigCount[2 * 7 + 5]++;}}else{if (((seed >> 2) & 1) == 0) {serialBigCount[2 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 3) & 1) == 0) {if (((seed_prev >> 3) & 1) == 0) {if (((seed >> 3) & 1) == 0) {serialBigCount[3 * 7]++;} else {serialBigCount[3 * 7 + 1]++;serialBigCount[3 * 7 + 1]++;}}else {if (((seed >> 3) & 1) == 0) {serialBigCount[3 * 7 + 2]++;} else {serialBigCount[3 * 7 + 3]++;}}}else{if (((seed_prev >> 3) & 1) == 0) {if (((seed >> 3) & 1) == 0) {serialBigCount[3* 7 + 4]++;serialBigCount[3 * 7 + 4]++;} else {serialBigCount[3 * 7 + 5]++;}}else{if (((seed >> 3) & 1) == 0) {serialBigCount[3 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 4) & 1) == 0) {if (((seed_prev >> 4) & 1) == 0) {if (((seed >> 4) & 1) == 0) {serialBigCount[4 * 7]++;} else {serialBigCount[4 * 7 + 1]++;serialBigCount[4 * 7 + 1]++;}}else {if (((seed >> 4) & 1) == 0) {serialBigCount[4 * 7 + 2]++;} else {serialBigCount[4 * 7 + 3]++;}}}else{if (((seed_prev >> 4) & 1) == 0) {if (((seed >> 4) & 1) == 0) {serialBigCount[4* 7 + 4]++;serialBigCount[4 * 7 + 4]++;} else {serialBigCount[4 * 7 + 5]++;}}else{if (((seed >> 4) & 1) == 0) {serialBigCount[4 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 5) & 1) == 0) {if (((seed_prev >> 5) & 1) == 0) {if (((seed >> 5) & 1) == 0) {serialBigCount[5 * 7]++;} else {serialBigCount[5 * 7 + 1]++;serialBigCount[5 * 7 + 1]++;}}else {if (((seed >> 5) & 1) == 0) {serialBigCount[5 * 7 + 2]++;} else {serialBigCount[5 * 7 + 3]++;}}}else{if (((seed_prev >> 5) & 1) == 0) {if (((seed >> 5) & 1) == 0) {serialBigCount[5* 7 + 4]++;serialBigCount[5 * 7 + 4]++;} else {serialBigCount[5 * 7 + 5]++;}}else{if (((seed >> 5) & 1) == 0) {serialBigCount[5 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 6) & 1) == 0) {if (((seed_prev >> 6) & 1) == 0) {if (((seed >> 6) & 1) == 0) {serialBigCount[6 * 7]++;} else {serialBigCount[6 * 7 + 1]++;serialBigCount[6 * 7 + 1]++;}}else {if (((seed >> 6) & 1) == 0) {serialBigCount[6 * 7 + 2]++;} else {serialBigCount[6 * 7 + 3]++;}}}else{if (((seed_prev >> 6) & 1) == 0) {if (((seed >> 6) & 1) == 0) {serialBigCount[6* 7 + 4]++;serialBigCount[6 * 7 + 4]++;} else {serialBigCount[6 * 7 + 5]++;}}else{if (((seed >> 6) & 1) == 0) {serialBigCount[6 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 7) & 1) == 0) {if (((seed_prev >> 7) & 1) == 0) {if (((seed >> 7) & 1) == 0) {serialBigCount[7 * 7]++;} else {serialBigCount[7 * 7 + 1]++;serialBigCount[7 * 7 + 1]++;}}else {if (((seed >> 7) & 1) == 0) {serialBigCount[7 * 7 + 2]++;} else {serialBigCount[7 * 7 + 3]++;}}}else{if (((seed_prev >> 7) & 1) == 0) {if (((seed >> 7) & 1) == 0) {serialBigCount[7* 7 + 4]++;serialBigCount[7 * 7 + 4]++;} else {serialBigCount[7 * 7 + 5]++;}}else{if (((seed >> 7) & 1) == 0) {serialBigCount[7 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 8) & 1) == 0) {if (((seed_prev >> 8) & 1) == 0) {if (((seed >> 8) & 1) == 0) {serialBigCount[8 * 7]++;} else {serialBigCount[8 * 7 + 1]++;serialBigCount[8 * 7 + 1]++;}}else {if (((seed >> 8) & 1) == 0) {serialBigCount[8 * 7 + 2]++;} else {serialBigCount[8 * 7 + 3]++;}}}else{if (((seed_prev >> 8) & 1) == 0) {if (((seed >> 8) & 1) == 0) {serialBigCount[8* 7 + 4]++;serialBigCount[8 * 7 + 4]++;} else {serialBigCount[8 * 7 + 5]++;}}else{if (((seed >> 8) & 1) == 0) {serialBigCount[8 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 9) & 1) == 0) {if (((seed_prev >> 9) & 1) == 0) {if (((seed >> 9) & 1) == 0) {serialBigCount[9 * 7]++;} else {serialBigCount[9 * 7 + 1]++;serialBigCount[9 * 7 + 1]++;}}else {if (((seed >> 9) & 1) == 0) {serialBigCount[9 * 7 + 2]++;} else {serialBigCount[9 * 7 + 3]++;}}}else{if (((seed_prev >> 9) & 1) == 0) {if (((seed >> 9) & 1) == 0) {serialBigCount[9* 7 + 4]++;serialBigCount[9 * 7 + 4]++;} else {serialBigCount[9 * 7 + 5]++;}}else{if (((seed >> 9) & 1) == 0) {serialBigCount[9 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 10) & 1) == 0) {if (((seed_prev >> 10) & 1) == 0) {if (((seed >> 10) & 1) == 0) {serialBigCount[10 * 7]++;} else {serialBigCount[10 * 7 + 1]++;serialBigCount[10 * 7 + 1]++;}}else {if (((seed >> 10) & 1) == 0) {serialBigCount[10 * 7 + 2]++;} else {serialBigCount[10 * 7 + 3]++;}}}else{if (((seed_prev >> 10) & 1) == 0) {if (((seed >> 10) & 1) == 0) {serialBigCount[10* 7 + 4]++;serialBigCount[10 * 7 + 4]++;} else {serialBigCount[10 * 7 + 5]++;}}else{if (((seed >> 10) & 1) == 0) {serialBigCount[10 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 11) & 1) == 0) {if (((seed_prev >> 11) & 1) == 0) {if (((seed >> 11) & 1) == 0) {serialBigCount[11 * 7]++;} else {serialBigCount[11 * 7 + 1]++;serialBigCount[11 * 7 + 1]++;}}else {if (((seed >> 11) & 1) == 0) {serialBigCount[11 * 7 + 2]++;} else {serialBigCount[11 * 7 + 3]++;}}}else{if (((seed_prev >> 11) & 1) == 0) {if (((seed >> 11) & 1) == 0) {serialBigCount[11* 7 + 4]++;serialBigCount[11 * 7 + 4]++;} else {serialBigCount[11 * 7 + 5]++;}}else{if (((seed >> 11) & 1) == 0) {serialBigCount[11 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 12) & 1) == 0) {if (((seed_prev >> 12) & 1) == 0) {if (((seed >> 12) & 1) == 0) {serialBigCount[12 * 7]++;} else {serialBigCount[12 * 7 + 1]++;serialBigCount[12 * 7 + 1]++;}}else {if (((seed >> 12) & 1) == 0) {serialBigCount[12 * 7 + 2]++;} else {serialBigCount[12 * 7 + 3]++;}}}else{if (((seed_prev >> 12) & 1) == 0) {if (((seed >> 12) & 1) == 0) {serialBigCount[12* 7 + 4]++;serialBigCount[12 * 7 + 4]++;} else {serialBigCount[12 * 7 + 5]++;}}else{if (((seed >> 12) & 1) == 0) {serialBigCount[12 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 13) & 1) == 0) {if (((seed_prev >> 13) & 1) == 0) {if (((seed >> 13) & 1) == 0) {serialBigCount[13 * 7]++;} else {serialBigCount[13 * 7 + 1]++;serialBigCount[13 * 7 + 1]++;}}else {if (((seed >> 13) & 1) == 0) {serialBigCount[13 * 7 + 2]++;} else {serialBigCount[13 * 7 + 3]++;}}}else{if (((seed_prev >> 13) & 1) == 0) {if (((seed >> 13) & 1) == 0) {serialBigCount[13* 7 + 4]++;serialBigCount[13 * 7 + 4]++;} else {serialBigCount[13 * 7 + 5]++;}}else{if (((seed >> 13) & 1) == 0) {serialBigCount[13 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 14) & 1) == 0) {if (((seed_prev >> 14) & 1) == 0) {if (((seed >> 14) & 1) == 0) {serialBigCount[14 * 7]++;} else {serialBigCount[14 * 7 + 1]++;serialBigCount[14 * 7 + 1]++;}}else {if (((seed >> 14) & 1) == 0) {serialBigCount[14 * 7 + 2]++;} else {serialBigCount[14 * 7 + 3]++;}}}else{if (((seed_prev >> 14) & 1) == 0) {if (((seed >> 14) & 1) == 0) {serialBigCount[14* 7 + 4]++;serialBigCount[14 * 7 + 4]++;} else {serialBigCount[14 * 7 + 5]++;}}else{if (((seed >> 14) & 1) == 0) {serialBigCount[14 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 15) & 1) == 0) {if (((seed_prev >> 15) & 1) == 0) {if (((seed >> 15) & 1) == 0) {serialBigCount[15 * 7]++;} else {serialBigCount[15 * 7 + 1]++;serialBigCount[15 * 7 + 1]++;}}else {if (((seed >> 15) & 1) == 0) {serialBigCount[15 * 7 + 2]++;} else {serialBigCount[15 * 7 + 3]++;}}}else{if (((seed_prev >> 15) & 1) == 0) {if (((seed >> 15) & 1) == 0) {serialBigCount[15* 7 + 4]++;serialBigCount[15 * 7 + 4]++;} else {serialBigCount[15 * 7 + 5]++;}}else{if (((seed >> 15) & 1) == 0) {serialBigCount[15 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 16) & 1) == 0) {if (((seed_prev >> 16) & 1) == 0) {if (((seed >> 16) & 1) == 0) {serialBigCount[16 * 7]++;} else {serialBigCount[16 * 7 + 1]++;serialBigCount[16 * 7 + 1]++;}}else {if (((seed >> 16) & 1) == 0) {serialBigCount[16 * 7 + 2]++;} else {serialBigCount[16 * 7 + 3]++;}}}else{if (((seed_prev >> 16) & 1) == 0) {if (((seed >> 16) & 1) == 0) {serialBigCount[16* 7 + 4]++;serialBigCount[16 * 7 + 4]++;} else {serialBigCount[16 * 7 + 5]++;}}else{if (((seed >> 16) & 1) == 0) {serialBigCount[16 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 17) & 1) == 0) {if (((seed_prev >> 17) & 1) == 0) {if (((seed >> 17) & 1) == 0) {serialBigCount[17 * 7]++;} else {serialBigCount[17 * 7 + 1]++;serialBigCount[17 * 7 + 1]++;}}else {if (((seed >> 17) & 1) == 0) {serialBigCount[17 * 7 + 2]++;} else {serialBigCount[17 * 7 + 3]++;}}}else{if (((seed_prev >> 17) & 1) == 0) {if (((seed >> 17) & 1) == 0) {serialBigCount[17* 7 + 4]++;serialBigCount[17 * 7 + 4]++;} else {serialBigCount[17 * 7 + 5]++;}}else{if (((seed >> 17) & 1) == 0) {serialBigCount[17 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 18) & 1) == 0) {if (((seed_prev >> 18) & 1) == 0) {if (((seed >> 18) & 1) == 0) {serialBigCount[18 * 7]++;} else {serialBigCount[18 * 7 + 1]++;serialBigCount[18 * 7 + 1]++;}}else {if (((seed >> 18) & 1) == 0) {serialBigCount[18 * 7 + 2]++;} else {serialBigCount[18 * 7 + 3]++;}}}else{if (((seed_prev >> 18) & 1) == 0) {if (((seed >> 18) & 1) == 0) {serialBigCount[18* 7 + 4]++;serialBigCount[18 * 7 + 4]++;} else {serialBigCount[18 * 7 + 5]++;}}else{if (((seed >> 18) & 1) == 0) {serialBigCount[18 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 19) & 1) == 0) {if (((seed_prev >> 19) & 1) == 0) {if (((seed >> 19) & 1) == 0) {serialBigCount[19 * 7]++;} else {serialBigCount[19 * 7 + 1]++;serialBigCount[19 * 7 + 1]++;}}else {if (((seed >> 19) & 1) == 0) {serialBigCount[19 * 7 + 2]++;} else {serialBigCount[19 * 7 + 3]++;}}}else{if (((seed_prev >> 19) & 1) == 0) {if (((seed >> 19) & 1) == 0) {serialBigCount[19* 7 + 4]++;serialBigCount[19 * 7 + 4]++;} else {serialBigCount[19 * 7 + 5]++;}}else{if (((seed >> 19) & 1) == 0) {serialBigCount[19 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 20) & 1) == 0) {if (((seed_prev >> 20) & 1) == 0) {if (((seed >> 20) & 1) == 0) {serialBigCount[20 * 7]++;} else {serialBigCount[20 * 7 + 1]++;serialBigCount[20 * 7 + 1]++;}}else {if (((seed >> 20) & 1) == 0) {serialBigCount[20 * 7 + 2]++;} else {serialBigCount[20 * 7 + 3]++;}}}else{if (((seed_prev >> 20) & 1) == 0) {if (((seed >> 20) & 1) == 0) {serialBigCount[20* 7 + 4]++;serialBigCount[20 * 7 + 4]++;} else {serialBigCount[20 * 7 + 5]++;}}else{if (((seed >> 20) & 1) == 0) {serialBigCount[20 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 21) & 1) == 0) {if (((seed_prev >> 21) & 1) == 0) {if (((seed >> 21) & 1) == 0) {serialBigCount[21 * 7]++;} else {serialBigCount[21 * 7 + 1]++;serialBigCount[21 * 7 + 1]++;}}else {if (((seed >> 21) & 1) == 0) {serialBigCount[21 * 7 + 2]++;} else {serialBigCount[21 * 7 + 3]++;}}}else{if (((seed_prev >> 21) & 1) == 0) {if (((seed >> 21) & 1) == 0) {serialBigCount[21* 7 + 4]++;serialBigCount[21 * 7 + 4]++;} else {serialBigCount[21 * 7 + 5]++;}}else{if (((seed >> 21) & 1) == 0) {serialBigCount[21 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 22) & 1) == 0) {if (((seed_prev >> 22) & 1) == 0) {if (((seed >> 22) & 1) == 0) {serialBigCount[22 * 7]++;} else {serialBigCount[22 * 7 + 1]++;serialBigCount[22 * 7 + 1]++;}}else {if (((seed >> 22) & 1) == 0) {serialBigCount[22 * 7 + 2]++;} else {serialBigCount[22 * 7 + 3]++;}}}else{if (((seed_prev >> 22) & 1) == 0) {if (((seed >> 22) & 1) == 0) {serialBigCount[22* 7 + 4]++;serialBigCount[22 * 7 + 4]++;} else {serialBigCount[22 * 7 + 5]++;}}else{if (((seed >> 22) & 1) == 0) {serialBigCount[22 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 23) & 1) == 0) {if (((seed_prev >> 23) & 1) == 0) {if (((seed >> 23) & 1) == 0) {serialBigCount[23 * 7]++;} else {serialBigCount[23 * 7 + 1]++;serialBigCount[23 * 7 + 1]++;}}else {if (((seed >> 23) & 1) == 0) {serialBigCount[23 * 7 + 2]++;} else {serialBigCount[23 * 7 + 3]++;}}}else{if (((seed_prev >> 23) & 1) == 0) {if (((seed >> 23) & 1) == 0) {serialBigCount[23* 7 + 4]++;serialBigCount[23 * 7 + 4]++;} else {serialBigCount[23 * 7 + 5]++;}}else{if (((seed >> 23) & 1) == 0) {serialBigCount[23 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 24) & 1) == 0) {if (((seed_prev >> 24) & 1) == 0) {if (((seed >> 24) & 1) == 0) {serialBigCount[24 * 7]++;} else {serialBigCount[24 * 7 + 1]++;serialBigCount[24 * 7 + 1]++;}}else {if (((seed >> 24) & 1) == 0) {serialBigCount[24 * 7 + 2]++;} else {serialBigCount[24 * 7 + 3]++;}}}else{if (((seed_prev >> 24) & 1) == 0) {if (((seed >> 24) & 1) == 0) {serialBigCount[24* 7 + 4]++;serialBigCount[24 * 7 + 4]++;} else {serialBigCount[24 * 7 + 5]++;}}else{if (((seed >> 24) & 1) == 0) {serialBigCount[24 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 25) & 1) == 0) {if (((seed_prev >> 25) & 1) == 0) {if (((seed >> 25) & 1) == 0) {serialBigCount[25 * 7]++;} else {serialBigCount[25 * 7 + 1]++;serialBigCount[25 * 7 + 1]++;}}else {if (((seed >> 25) & 1) == 0) {serialBigCount[25 * 7 + 2]++;} else {serialBigCount[25 * 7 + 3]++;}}}else{if (((seed_prev >> 25) & 1) == 0) {if (((seed >> 25) & 1) == 0) {serialBigCount[25* 7 + 4]++;serialBigCount[25 * 7 + 4]++;} else {serialBigCount[25 * 7 + 5]++;}}else{if (((seed >> 25) & 1) == 0) {serialBigCount[25 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 26) & 1) == 0) {if (((seed_prev >> 26) & 1) == 0) {if (((seed >> 26) & 1) == 0) {serialBigCount[26 * 7]++;} else {serialBigCount[26 * 7 + 1]++;serialBigCount[26 * 7 + 1]++;}}else {if (((seed >> 26) & 1) == 0) {serialBigCount[26 * 7 + 2]++;} else {serialBigCount[26 * 7 + 3]++;}}}else{if (((seed_prev >> 26) & 1) == 0) {if (((seed >> 26) & 1) == 0) {serialBigCount[26* 7 + 4]++;serialBigCount[26 * 7 + 4]++;} else {serialBigCount[26 * 7 + 5]++;}}else{if (((seed >> 26) & 1) == 0) {serialBigCount[26 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 27) & 1) == 0) {if (((seed_prev >> 27) & 1) == 0) {if (((seed >> 27) & 1) == 0) {serialBigCount[27 * 7]++;} else {serialBigCount[27 * 7 + 1]++;serialBigCount[27 * 7 + 1]++;}}else {if (((seed >> 27) & 1) == 0) {serialBigCount[27 * 7 + 2]++;} else {serialBigCount[27 * 7 + 3]++;}}}else{if (((seed_prev >> 27) & 1) == 0) {if (((seed >> 27) & 1) == 0) {serialBigCount[27* 7 + 4]++;serialBigCount[27 * 7 + 4]++;} else {serialBigCount[27 * 7 + 5]++;}}else{if (((seed >> 27) & 1) == 0) {serialBigCount[27 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 28) & 1) == 0) {if (((seed_prev >> 28) & 1) == 0) {if (((seed >> 28) & 1) == 0) {serialBigCount[28 * 7]++;} else {serialBigCount[28 * 7 + 1]++;serialBigCount[28 * 7 + 1]++;}}else {if (((seed >> 28) & 1) == 0) {serialBigCount[28 * 7 + 2]++;} else {serialBigCount[28 * 7 + 3]++;}}}else{if (((seed_prev >> 28) & 1) == 0) {if (((seed >> 28) & 1) == 0) {serialBigCount[28* 7 + 4]++;serialBigCount[28 * 7 + 4]++;} else {serialBigCount[28 * 7 + 5]++;}}else{if (((seed >> 28) & 1) == 0) {serialBigCount[28 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 29) & 1) == 0) {if (((seed_prev >> 29) & 1) == 0) {if (((seed >> 29) & 1) == 0) {serialBigCount[29 * 7]++;} else {serialBigCount[29 * 7 + 1]++;serialBigCount[29 * 7 + 1]++;}}else {if (((seed >> 29) & 1) == 0) {serialBigCount[29 * 7 + 2]++;} else {serialBigCount[29 * 7 + 3]++;}}}else{if (((seed_prev >> 29) & 1) == 0) {if (((seed >> 29) & 1) == 0) {serialBigCount[29* 7 + 4]++;serialBigCount[29 * 7 + 4]++;} else {serialBigCount[29 * 7 + 5]++;}}else{if (((seed >> 29) & 1) == 0) {serialBigCount[29 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 30) & 1) == 0) {if (((seed_prev >> 30) & 1) == 0) {if (((seed >> 30) & 1) == 0) {serialBigCount[30 * 7]++;} else {serialBigCount[30 * 7 + 1]++;serialBigCount[30 * 7 + 1]++;}}else {if (((seed >> 30) & 1) == 0) {serialBigCount[30 * 7 + 2]++;} else {serialBigCount[30 * 7 + 3]++;}}}else{if (((seed_prev >> 30) & 1) == 0) {if (((seed >> 30) & 1) == 0) {serialBigCount[30* 7 + 4]++;serialBigCount[30 * 7 + 4]++;} else {serialBigCount[30 * 7 + 5]++;}}else{if (((seed >> 30) & 1) == 0) {serialBigCount[30 * 7 + 6]++;} }}
			if (((seed_prev_prev >> 31) & 1) == 0) {if (((seed_prev >> 31) & 1) == 0) {if (((seed >> 31) & 1) == 0) {serialBigCount[31 * 7]++;} else {serialBigCount[31 * 7 + 1]++;serialBigCount[31 * 7 + 1]++;}}else {if (((seed >> 31) & 1) == 0) {serialBigCount[31 * 7 + 2]++;} else {serialBigCount[31 * 7 + 3]++;}}}else{if (((seed_prev >> 31) & 1) == 0) {if (((seed >> 31) & 1) == 0) {serialBigCount[31* 7 + 4]++;serialBigCount[31 * 7 + 4]++;} else {serialBigCount[31 * 7 + 5]++;}}else{if (((seed >> 31) & 1) == 0) {serialBigCount[31 * 7 + 6]++;} }}
		}
	}
/*
	for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
		freqStream[i] = freqCount[i]>>11;
	}

	for (int i = 0; i < 128; i++) {
#pragma HLS PIPELINE
		serialStream[i] = serialCount[i]>>11;
	}
*/
	for (int i = 0; i < 224; i++) {
		serialBigStream[i] = serialBigCount[i]>>5;
	}
}
