#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> freqStream[32], ap_uint<32> serialStream[32],
		ap_uint<32> seed, ap_uint<44> n) {
//#pragma HLS ARRAY_PARTITION variable=freqStream dim=1
#pragma HLS INTERFACE ap_ctrl_none port=return

	// initialisations
	bool enableSerial = 1;
	ap_uint<32> seed_old = 0;
	ap_uint<32> freqCount[32];
	ap_uint<32> serialCount[128];
#pragma HLS ARRAY_PARTITION variable=serialCount dim=1
	ap_uint<32> freqCount_0 = 0;
	ap_uint<32> freqCount_1 = 0;
	ap_uint<32> freqCount_2 = 0;
	ap_uint<32> freqCount_3 = 0;
	ap_uint<32> freqCount_4 = 0;
	ap_uint<32> freqCount_5 = 0;
	ap_uint<32> freqCount_6 = 0;
	ap_uint<32> freqCount_7 = 0;
	ap_uint<32> freqCount_8 = 0;
	ap_uint<32> freqCount_9 = 0;
	ap_uint<32> freqCount_10 = 0;
	ap_uint<32> freqCount_11 = 0;
	ap_uint<32> freqCount_12 = 0;
	ap_uint<32> freqCount_13 = 0;
	ap_uint<32> freqCount_14 = 0;
	ap_uint<32> freqCount_15 = 0;
	ap_uint<32> freqCount_16 = 0;
	ap_uint<32> freqCount_17 = 0;
	ap_uint<32> freqCount_18 = 0;
	ap_uint<32> freqCount_19 = 0;
	ap_uint<32> freqCount_20 = 0;
	ap_uint<32> freqCount_21 = 0;
	ap_uint<32> freqCount_22 = 0;
	ap_uint<32> freqCount_23 = 0;
	ap_uint<32> freqCount_24 = 0;
	ap_uint<32> freqCount_25 = 0;
	ap_uint<32> freqCount_26 = 0;
	ap_uint<32> freqCount_27 = 0;
	ap_uint<32> freqCount_28 = 0;
	ap_uint<32> freqCount_29 = 0;
	ap_uint<32> freqCount_30 = 0;
	ap_uint<32> freqCount_31 = 0;
	for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
		freqCount[i] = 0;
		serialCount[i] = 0;
	}

	//for every sample
	//for (int idx = 0; idx < n; idx+=2) {
//#pragma HLS PIPELINE II=2 rewind
//#pragma HLS LOOP_TRIPCOUNT min=100 max=1000
	//detect 1s
	for (int idx = 0; idx < n; idx++) {
#pragma HLS LOOP_TRIPCOUNT min=100 max=1000
#pragma HLS PIPELINE
		freqCount_0 += ((seed >> 0) & 1);
		freqCount_1 += ((seed >> 1) & 1);
		freqCount_2 += ((seed >> 2) & 1);
		freqCount_3 += ((seed >> 3) & 1);
		freqCount_4 += ((seed >> 4) & 1);
		freqCount_5 += ((seed >> 5) & 1);
		freqCount_6 += ((seed >> 6) & 1);
		freqCount_7 += ((seed >> 7) & 1);
		freqCount_8 += ((seed >> 8) & 1);
		freqCount_9 += ((seed >> 9) & 1);
		freqCount_10 += ((seed >> 10) & 1);
		freqCount_11 += ((seed >> 11) & 1);
		freqCount_12 += ((seed >> 12) & 1);
		freqCount_13 += ((seed >> 13) & 1);
		freqCount_14 += ((seed >> 14) & 1);
		freqCount_15 += ((seed >> 15) & 1);
		freqCount_16 += ((seed >> 16) & 1);
		freqCount_17 += ((seed >> 17) & 1);
		freqCount_18 += ((seed >> 18) & 1);
		freqCount_19 += ((seed >> 19) & 1);
		freqCount_20 += ((seed >> 20) & 1);
		freqCount_21 += ((seed >> 21) & 1);
		freqCount_22 += ((seed >> 22) & 1);
		freqCount_23 += ((seed >> 23) & 1);
		freqCount_24 += ((seed >> 24) & 1);
		freqCount_25 += ((seed >> 25) & 1);
		freqCount_26 += ((seed >> 26) & 1);
		freqCount_27 += ((seed >> 27) & 1);
		freqCount_28 += ((seed >> 28) & 1);
		freqCount_29 += ((seed >> 29) & 1);
		freqCount_30 += ((seed >> 30) & 1);
		freqCount_31 += ((seed >> 31) & 1);
		seed_old = seed;
		seed++;
		enableSerial=!enableSerial;
		//serial test
	//enableSerial = !enableSerial;
		if(enableSerial){
			if (!(seed_old >>0)) {if (!((seed) >>0)) {serialCount[0 * 4]++;} else {serialCount[0* 4 + 1]++;}} else {if (!((seed) >> 0)) {serialCount[0 * 4 + 2]++;} else {serialCount[0* 4 + 3]++;}}
			if (!(seed_old >>1)) {if (!((seed) >>1)) {serialCount[1 * 4]++;} else {serialCount[1* 4 + 1]++;}} else {if (!((seed) >> 1)) {serialCount[1 * 4 + 2]++;} else {serialCount[1* 4 + 3]++;}}
			if (!(seed_old >>2)) {if (!((seed) >>2)) {serialCount[2 * 4]++;} else {serialCount[2* 4 + 1]++;}} else {if (!((seed) >> 2)) {serialCount[2 * 4 + 2]++;} else {serialCount[2* 4 + 3]++;}}
			if (!(seed_old >>3)) {if (!((seed) >>3)) {serialCount[3 * 4]++;} else {serialCount[3* 4 + 1]++;}} else {if (!((seed) >> 3)) {serialCount[3 * 4 + 2]++;} else {serialCount[3* 4 + 3]++;}}
			if (!(seed_old >>4)) {if (!((seed) >>4)) {serialCount[4 * 4]++;} else {serialCount[4* 4 + 1]++;}} else {if (!((seed) >> 4)) {serialCount[4 * 4 + 2]++;} else {serialCount[4* 4 + 3]++;}}
			if (!(seed_old >>5)) {if (!((seed) >>5)) {serialCount[5 * 4]++;} else {serialCount[5* 4 + 1]++;}} else {if (!((seed) >> 5)) {serialCount[5 * 4 + 2]++;} else {serialCount[5* 4 + 3]++;}}
			if (!(seed_old >>6)) {if (!((seed) >>6)) {serialCount[6 * 4]++;} else {serialCount[6* 4 + 1]++;}} else {if (!((seed) >> 6)) {serialCount[6 * 4 + 2]++;} else {serialCount[6* 4 + 3]++;}}
			if (!(seed_old >>7)) {if (!((seed) >>7)) {serialCount[7 * 4]++;} else {serialCount[7* 4 + 1]++;}} else {if (!((seed) >> 7)) {serialCount[7 * 4 + 2]++;} else {serialCount[7* 4 + 3]++;}}
			if (!(seed_old >>8)) {if (!((seed) >>8)) {serialCount[8 * 4]++;} else {serialCount[8* 4 + 1]++;}} else {if (!((seed) >> 8)) {serialCount[8 * 4 + 2]++;} else {serialCount[8* 4 + 3]++;}}
			if (!(seed_old >>9)) {if (!((seed) >>9)) {serialCount[9 * 4]++;} else {serialCount[9* 4 + 1]++;}} else {if (!((seed) >> 9)) {serialCount[9 * 4 + 2]++;} else {serialCount[9* 4 + 3]++;}}
			if (!(seed_old >>10)) {if (!((seed) >>10)) {serialCount[10 * 4]++;} else {serialCount[10* 4 + 1]++;}} else {if (!((seed) >> 10)) {serialCount[10 * 4 + 2]++;} else {serialCount[10* 4 + 3]++;}}
			if (!(seed_old >>11)) {if (!((seed) >>11)) {serialCount[11 * 4]++;} else {serialCount[11* 4 + 1]++;}} else {if (!((seed) >> 11)) {serialCount[11 * 4 + 2]++;} else {serialCount[11* 4 + 3]++;}}
			if (!(seed_old >>12)) {if (!((seed) >>12)) {serialCount[12 * 4]++;} else {serialCount[12* 4 + 1]++;}} else {if (!((seed) >> 12)) {serialCount[12 * 4 + 2]++;} else {serialCount[12* 4 + 3]++;}}
			if (!(seed_old >>13)) {if (!((seed) >>13)) {serialCount[13 * 4]++;} else {serialCount[13* 4 + 1]++;}} else {if (!((seed) >> 13)) {serialCount[13 * 4 + 2]++;} else {serialCount[13* 4 + 3]++;}}
			if (!(seed_old >>14)) {if (!((seed) >>14)) {serialCount[14 * 4]++;} else {serialCount[14* 4 + 1]++;}} else {if (!((seed) >> 14)) {serialCount[14 * 4 + 2]++;} else {serialCount[14* 4 + 3]++;}}
			if (!(seed_old >>15)) {if (!((seed) >>15)) {serialCount[15 * 4]++;} else {serialCount[15* 4 + 1]++;}} else {if (!((seed) >> 15)) {serialCount[15 * 4 + 2]++;} else {serialCount[15* 4 + 3]++;}}
			if (!(seed_old >>16)) {if (!((seed) >>16)) {serialCount[16 * 4]++;} else {serialCount[16* 4 + 1]++;}} else {if (!((seed) >> 16)) {serialCount[16 * 4 + 2]++;} else {serialCount[16* 4 + 3]++;}}
			if (!(seed_old >>17)) {if (!((seed) >>17)) {serialCount[17 * 4]++;} else {serialCount[17* 4 + 1]++;}} else {if (!((seed) >> 17)) {serialCount[17 * 4 + 2]++;} else {serialCount[17* 4 + 3]++;}}
			if (!(seed_old >>18)) {if (!((seed) >>18)) {serialCount[18 * 4]++;} else {serialCount[18* 4 + 1]++;}} else {if (!((seed) >> 18)) {serialCount[18 * 4 + 2]++;} else {serialCount[18* 4 + 3]++;}}
			if (!(seed_old >>19)) {if (!((seed) >>19)) {serialCount[19 * 4]++;} else {serialCount[19* 4 + 1]++;}} else {if (!((seed) >> 19)) {serialCount[19 * 4 + 2]++;} else {serialCount[19* 4 + 3]++;}}
			if (!(seed_old >>20)) {if (!((seed) >>20)) {serialCount[20 * 4]++;} else {serialCount[20* 4 + 1]++;}} else {if (!((seed) >> 20)) {serialCount[20 * 4 + 2]++;} else {serialCount[20* 4 + 3]++;}}
			if (!(seed_old >>21)) {if (!((seed) >>21)) {serialCount[21 * 4]++;} else {serialCount[21* 4 + 1]++;}} else {if (!((seed) >> 21)) {serialCount[21 * 4 + 2]++;} else {serialCount[21* 4 + 3]++;}}
			if (!(seed_old >>22)) {if (!((seed) >>22)) {serialCount[22 * 4]++;} else {serialCount[22* 4 + 1]++;}} else {if (!((seed) >> 22)) {serialCount[22 * 4 + 2]++;} else {serialCount[22* 4 + 3]++;}}
			if (!(seed_old >>23)) {if (!((seed) >>23)) {serialCount[23 * 4]++;} else {serialCount[23* 4 + 1]++;}} else {if (!((seed) >> 23)) {serialCount[23 * 4 + 2]++;} else {serialCount[23* 4 + 3]++;}}
			if (!(seed_old >>24)) {if (!((seed) >>24)) {serialCount[24 * 4]++;} else {serialCount[24* 4 + 1]++;}} else {if (!((seed) >> 24)) {serialCount[24 * 4 + 2]++;} else {serialCount[24* 4 + 3]++;}}
			if (!(seed_old >>25)) {if (!((seed) >>25)) {serialCount[25 * 4]++;} else {serialCount[25* 4 + 1]++;}} else {if (!((seed) >> 25)) {serialCount[25 * 4 + 2]++;} else {serialCount[25* 4 + 3]++;}}
			if (!(seed_old >>26)) {if (!((seed) >>26)) {serialCount[26 * 4]++;} else {serialCount[26* 4 + 1]++;}} else {if (!((seed) >> 26)) {serialCount[26 * 4 + 2]++;} else {serialCount[26* 4 + 3]++;}}
			if (!(seed_old >>27)) {if (!((seed) >>27)) {serialCount[27 * 4]++;} else {serialCount[27* 4 + 1]++;}} else {if (!((seed) >> 27)) {serialCount[27 * 4 + 2]++;} else {serialCount[27* 4 + 3]++;}}
			if (!(seed_old >>28)) {if (!((seed) >>28)) {serialCount[28 * 4]++;} else {serialCount[28* 4 + 1]++;}} else {if (!((seed) >> 28)) {serialCount[28 * 4 + 2]++;} else {serialCount[28* 4 + 3]++;}}
			if (!(seed_old >>29)) {if (!((seed) >>29)) {serialCount[29 * 4]++;} else {serialCount[29* 4 + 1]++;}} else {if (!((seed) >> 29)) {serialCount[29 * 4 + 2]++;} else {serialCount[29* 4 + 3]++;}}
			if (!(seed_old >>30)) {if (!((seed) >>30)) {serialCount[30 * 4]++;} else {serialCount[30* 4 + 1]++;}} else {if (!((seed) >> 30)) {serialCount[30 * 4 + 2]++;} else {serialCount[30* 4 + 3]++;}}
			if (!(seed_old >>31)) {if (!((seed) >>31)) {serialCount[31 * 4]++;} else {serialCount[31* 4 + 1]++;}} else {if (!((seed) >> 31)) {serialCount[31 * 4 + 2]++;} else {serialCount[31* 4 + 3]++;}}
		}
	}
	freqStream[0] = freqCount_0;
	freqStream[1] = freqCount_1;
	freqStream[2] = freqCount_2;
	freqStream[3] = freqCount_3;
	freqStream[4] = freqCount_4;
	freqStream[5] = freqCount_5;
	freqStream[6] = freqCount_6;
	freqStream[7] = freqCount_7;
	freqStream[8] = freqCount_8;
	freqStream[9] = freqCount_9;
	freqStream[10] = freqCount_10;
	freqStream[11] = freqCount_11;
	freqStream[12] = freqCount_12;
	freqStream[13] = freqCount_13;
	freqStream[14] = freqCount_14;
	freqStream[15] = freqCount_15;
	freqStream[16] = freqCount_16;
	freqStream[17] = freqCount_17;
	freqStream[18] = freqCount_18;
	freqStream[19] = freqCount_19;
	freqStream[20] = freqCount_20;
	freqStream[21] = freqCount_21;
	freqStream[22] = freqCount_22;
	freqStream[23] = freqCount_23;
	freqStream[24] = freqCount_24;
	freqStream[25] = freqCount_25;
	freqStream[26] = freqCount_26;
	freqStream[27] = freqCount_27;
	freqStream[28] = freqCount_28;
	freqStream[29] = freqCount_29;
	freqStream[30] = freqCount_30;
	freqStream[31] = freqCount_31;
}
