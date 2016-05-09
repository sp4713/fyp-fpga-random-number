#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> freqStream[32], ap_uint<32> serialStream[128],
		ap_uint<32> seed, ap_uint<44> n) {
#pragma HLS INTERFACE ap_ctrl_none port=return

	// initialisations
	bool enableSerial = 1;
	ap_uint<32> seed_old = 0;
	ap_uint<32> freqCount[32];
#pragma HLS ARRAY_PARTITION variable=freqCount complete dim=1
	ap_uint<32> serialCount[128];
#pragma HLS ARRAY_PARTITION variable=serialCount complete dim=1
	for (int i = 0; i < 32; i++) {
#pragma HLS PIPELINE
		freqCount[i] = 0;
	}
	for (int i=0; i<128; i++) {
#pragma HLS PIPELINE
		serialCount[i] = 0;
	}

	//for every sample
	//for (int idx = 0; idx < n; idx+=2) {
//#pragma HLS PIPELINE II=2 rewind
//#pragma HLS LOOP_TRIPCOUNT min=100 max=1000
	//detect 1s
	for (int idx = 0; idx < n; idx++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=100 max=1000
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
		seed_old = seed;
		seed++;
		enableSerial=!enableSerial;
		//serial test
	//enableSerial = !enableSerial;
		if(enableSerial){
			if ((seed_old >>0)==0) {if (((seed) >>0)==0) {serialCount[0 * 4]++;} else {serialCount[0* 4 + 1]++;}} else {if (((seed) >> 0)==0) {serialCount[0 * 4 + 2]++;} else {serialCount[0* 4 + 3]++;}}
			if ((seed_old >>1)==0) {if (((seed) >>1)==0) {serialCount[1 * 4]++;} else {serialCount[1* 4 + 1]++;}} else {if (((seed) >> 1)==0) {serialCount[1 * 4 + 2]++;} else {serialCount[1* 4 + 3]++;}}
			if ((seed_old >>2)==0) {if (((seed) >>2)==0) {serialCount[2 * 4]++;} else {serialCount[2* 4 + 1]++;}} else {if (((seed) >> 2)==0) {serialCount[2 * 4 + 2]++;} else {serialCount[2* 4 + 3]++;}}
			if ((seed_old >>3)==0) {if (((seed) >>3)==0) {serialCount[3 * 4]++;} else {serialCount[3* 4 + 1]++;}} else {if (((seed) >> 3)==0) {serialCount[3 * 4 + 2]++;} else {serialCount[3* 4 + 3]++;}}
			if ((seed_old >>4)==0) {if (((seed) >>4)==0) {serialCount[4 * 4]++;} else {serialCount[4* 4 + 1]++;}} else {if (((seed) >> 4)==0) {serialCount[4 * 4 + 2]++;} else {serialCount[4* 4 + 3]++;}}
			if ((seed_old >>5)==0) {if (((seed) >>5)==0) {serialCount[5 * 4]++;} else {serialCount[5* 4 + 1]++;}} else {if (((seed) >> 5)==0) {serialCount[5 * 4 + 2]++;} else {serialCount[5* 4 + 3]++;}}
			if ((seed_old >>6)==0) {if (((seed) >>6)==0) {serialCount[6 * 4]++;} else {serialCount[6* 4 + 1]++;}} else {if (((seed) >> 6)==0) {serialCount[6 * 4 + 2]++;} else {serialCount[6* 4 + 3]++;}}
			if ((seed_old >>7)==0) {if (((seed) >>7)==0) {serialCount[7 * 4]++;} else {serialCount[7* 4 + 1]++;}} else {if (((seed) >> 7)==0) {serialCount[7 * 4 + 2]++;} else {serialCount[7* 4 + 3]++;}}
			if ((seed_old >>8)==0) {if (((seed) >>8)==0) {serialCount[8 * 4]++;} else {serialCount[8* 4 + 1]++;}} else {if (((seed) >> 8)==0) {serialCount[8 * 4 + 2]++;} else {serialCount[8* 4 + 3]++;}}
			if ((seed_old >>9)==0) {if (((seed) >>9)==0) {serialCount[9 * 4]++;} else {serialCount[9* 4 + 1]++;}} else {if (((seed) >> 9)==0) {serialCount[9 * 4 + 2]++;} else {serialCount[9* 4 + 3]++;}}
			if ((seed_old >>10)==0) {if (((seed) >>10)==0) {serialCount[10 * 4]++;} else {serialCount[10* 4 + 1]++;}} else {if (((seed) >> 10)==0) {serialCount[10 * 4 + 2]++;} else {serialCount[10* 4 + 3]++;}}
			if ((seed_old >>11)==0) {if (((seed) >>11)==0) {serialCount[11 * 4]++;} else {serialCount[11* 4 + 1]++;}} else {if (((seed) >> 11)==0) {serialCount[11 * 4 + 2]++;} else {serialCount[11* 4 + 3]++;}}
			if ((seed_old >>12)==0) {if (((seed) >>12)==0) {serialCount[12 * 4]++;} else {serialCount[12* 4 + 1]++;}} else {if (((seed) >> 12)==0) {serialCount[12 * 4 + 2]++;} else {serialCount[12* 4 + 3]++;}}
			if ((seed_old >>13)==0) {if (((seed) >>13)==0) {serialCount[13 * 4]++;} else {serialCount[13* 4 + 1]++;}} else {if (((seed) >> 13)==0) {serialCount[13 * 4 + 2]++;} else {serialCount[13* 4 + 3]++;}}
			if ((seed_old >>14)==0) {if (((seed) >>14)==0) {serialCount[14 * 4]++;} else {serialCount[14* 4 + 1]++;}} else {if (((seed) >> 14)==0) {serialCount[14 * 4 + 2]++;} else {serialCount[14* 4 + 3]++;}}
			if ((seed_old >>15)==0) {if (((seed) >>15)==0) {serialCount[15 * 4]++;} else {serialCount[15* 4 + 1]++;}} else {if (((seed) >> 15)==0) {serialCount[15 * 4 + 2]++;} else {serialCount[15* 4 + 3]++;}}
			if ((seed_old >>16)==0) {if (((seed) >>16)==0) {serialCount[16 * 4]++;} else {serialCount[16* 4 + 1]++;}} else {if (((seed) >> 16)==0) {serialCount[16 * 4 + 2]++;} else {serialCount[16* 4 + 3]++;}}
			if ((seed_old >>17)==0) {if (((seed) >>17)==0) {serialCount[17 * 4]++;} else {serialCount[17* 4 + 1]++;}} else {if (((seed) >> 17)==0) {serialCount[17 * 4 + 2]++;} else {serialCount[17* 4 + 3]++;}}
			if ((seed_old >>18)==0) {if (((seed) >>18)==0) {serialCount[18 * 4]++;} else {serialCount[18* 4 + 1]++;}} else {if (((seed) >> 18)==0) {serialCount[18 * 4 + 2]++;} else {serialCount[18* 4 + 3]++;}}
			if ((seed_old >>19)==0) {if (((seed) >>19)==0) {serialCount[19 * 4]++;} else {serialCount[19* 4 + 1]++;}} else {if (((seed) >> 19)==0) {serialCount[19 * 4 + 2]++;} else {serialCount[19* 4 + 3]++;}}
			if ((seed_old >>20)==0) {if (((seed) >>20)==0) {serialCount[20 * 4]++;} else {serialCount[20* 4 + 1]++;}} else {if (((seed) >> 20)==0) {serialCount[20 * 4 + 2]++;} else {serialCount[20* 4 + 3]++;}}
			if ((seed_old >>21)==0) {if (((seed) >>21)==0) {serialCount[21 * 4]++;} else {serialCount[21* 4 + 1]++;}} else {if (((seed) >> 21)==0) {serialCount[21 * 4 + 2]++;} else {serialCount[21* 4 + 3]++;}}
			if ((seed_old >>22)==0) {if (((seed) >>22)==0) {serialCount[22 * 4]++;} else {serialCount[22* 4 + 1]++;}} else {if (((seed) >> 22)==0) {serialCount[22 * 4 + 2]++;} else {serialCount[22* 4 + 3]++;}}
			if ((seed_old >>23)==0) {if (((seed) >>23)==0) {serialCount[23 * 4]++;} else {serialCount[23* 4 + 1]++;}} else {if (((seed) >> 23)==0) {serialCount[23 * 4 + 2]++;} else {serialCount[23* 4 + 3]++;}}
			if ((seed_old >>24)==0) {if (((seed) >>24)==0) {serialCount[24 * 4]++;} else {serialCount[24* 4 + 1]++;}} else {if (((seed) >> 24)==0) {serialCount[24 * 4 + 2]++;} else {serialCount[24* 4 + 3]++;}}
			if ((seed_old >>25)==0) {if (((seed) >>25)==0) {serialCount[25 * 4]++;} else {serialCount[25* 4 + 1]++;}} else {if (((seed) >> 25)==0) {serialCount[25 * 4 + 2]++;} else {serialCount[25* 4 + 3]++;}}
			if ((seed_old >>26)==0) {if (((seed) >>26)==0) {serialCount[26 * 4]++;} else {serialCount[26* 4 + 1]++;}} else {if (((seed) >> 26)==0) {serialCount[26 * 4 + 2]++;} else {serialCount[26* 4 + 3]++;}}
			if ((seed_old >>27)==0) {if (((seed) >>27)==0) {serialCount[27 * 4]++;} else {serialCount[27* 4 + 1]++;}} else {if (((seed) >> 27)==0) {serialCount[27 * 4 + 2]++;} else {serialCount[27* 4 + 3]++;}}
			if ((seed_old >>28)==0) {if (((seed) >>28)==0) {serialCount[28 * 4]++;} else {serialCount[28* 4 + 1]++;}} else {if (((seed) >> 28)==0) {serialCount[28 * 4 + 2]++;} else {serialCount[28* 4 + 3]++;}}
			if ((seed_old >>29)==0) {if (((seed) >>29)==0) {serialCount[29 * 4]++;} else {serialCount[29* 4 + 1]++;}} else {if (((seed) >> 29)==0) {serialCount[29 * 4 + 2]++;} else {serialCount[29* 4 + 3]++;}}
			if ((seed_old >>30)==0) {if (((seed) >>30)==0) {serialCount[30 * 4]++;} else {serialCount[30* 4 + 1]++;}} else {if (((seed) >> 30)==0) {serialCount[30 * 4 + 2]++;} else {serialCount[30* 4 + 3]++;}}
			if ((seed_old >>31)==0) {if (((seed) >>31)==0) {serialCount[31 * 4]++;} else {serialCount[31* 4 + 1]++;}} else {if (((seed) >> 31)==0) {serialCount[31 * 4 + 2]++;} else {serialCount[31* 4 + 3]++;}}
		}
	}
	for(int i=0; i<32; i++){
#pragma HLS PIPELINE
		freqStream[i] = freqCount[i];
	}
	for (int i=0; i<128; i++) {
#pragma HLS PIPELINE
		serialStream[i] = serialCount[i];
	}
}
