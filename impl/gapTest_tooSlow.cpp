#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> gapStream[128], ap_uint<32> seed, ap_uint<44> n) {
	#pragma HLS INTERFACE ap_ctrl_none port=return	// remove unnecessary hardware ports

// 	begin			//
// 	initialisations	//

//gap test parameters
	ap_uint<3> gapSize[32];			//measures the gap size in each bit
	#pragma HLS ARRAY_PARTITION variable=gapSize complete dim=1
	ap_uint<32> gapCount[12];
	#pragma HLS ARRAY_PARTITION variable=gapCount complete dim=1

	for (int i = 0; i < 32; i++) {
	#pragma HLS PIPELINE
		gapSize[i] = 0;
	}

	for (int i = 0; i < 12; i++) {
	#pragma HLS PIPELINE
		gapCount[i]=0;
	}

	for (int idx = 0; idx < n; idx++) {
	#pragma HLS PIPELINE
	#pragma HLS LOOP_TRIPCOUNT min=100 max=1000

		//gap test
		if(((seed>>0)&1)==1){gapCount[gapSize[0]]++; gapSize[0]=0;}else{ gapSize[0]++; if(gapSize[0]>11){ gapSize[0]=11;}}
		if(((seed>>1)&1)==1){gapCount[gapSize[1]]++; gapSize[1]=0;}else{ gapSize[1]++; if(gapSize[1]>11){ gapSize[1]=11;}}
		if(((seed>>2)&1)==1){gapCount[gapSize[2]]++; gapSize[2]=0;}else{ gapSize[2]++; if(gapSize[2]>11){ gapSize[2]=11;}}
		if(((seed>>3)&1)==1){gapCount[gapSize[3]]++; gapSize[3]=0;}else{ gapSize[3]++; if(gapSize[3]>11){ gapSize[3]=11;}}
		if(((seed>>4)&1)==1){gapCount[gapSize[4]]++; gapSize[4]=0;}else{ gapSize[4]++; if(gapSize[4]>11){ gapSize[4]=11;}}
		if(((seed>>5)&1)==1){gapCount[gapSize[5]]++; gapSize[5]=0;}else{ gapSize[5]++; if(gapSize[5]>11){ gapSize[5]=11;}}
		if(((seed>>6)&1)==1){gapCount[gapSize[6]]++; gapSize[6]=0;}else{ gapSize[6]++; if(gapSize[6]>11){ gapSize[6]=11;}}
		if(((seed>>7)&1)==1){gapCount[gapSize[7]]++; gapSize[7]=0;}else{ gapSize[7]++; if(gapSize[7]>11){ gapSize[7]=11;}}
		if(((seed>>8)&1)==1){gapCount[gapSize[8]]++; gapSize[8]=0;}else{ gapSize[8]++; if(gapSize[8]>11){ gapSize[8]=11;}}
		if(((seed>>9)&1)==1){gapCount[gapSize[9]]++; gapSize[9]=0;}else{ gapSize[9]++; if(gapSize[9]>11){ gapSize[9]=11;}}
		if(((seed>>10)&1)==1){gapCount[gapSize[10]]++; gapSize[10]=0;}else{ gapSize[10]++; if(gapSize[10]>11){ gapSize[10]=11;}}
		if(((seed>>11)&1)==1){gapCount[gapSize[11]]++; gapSize[11]=0;}else{ gapSize[11]++; if(gapSize[11]>11){ gapSize[11]=11;}}
		if(((seed>>12)&1)==1){gapCount[gapSize[12]]++; gapSize[12]=0;}else{ gapSize[12]++; if(gapSize[12]>11){ gapSize[12]=11;}}
		if(((seed>>13)&1)==1){gapCount[gapSize[13]]++; gapSize[13]=0;}else{ gapSize[13]++; if(gapSize[13]>11){ gapSize[13]=11;}}
		if(((seed>>14)&1)==1){gapCount[gapSize[14]]++; gapSize[14]=0;}else{ gapSize[14]++; if(gapSize[14]>11){ gapSize[14]=11;}}
		if(((seed>>11)&1)==1){gapCount[gapSize[15]]++; gapSize[15]=0;}else{ gapSize[15]++; if(gapSize[15]>11){ gapSize[15]=11;}}
		if(((seed>>16)&1)==1){gapCount[gapSize[16]]++; gapSize[16]=0;}else{ gapSize[16]++; if(gapSize[16]>11){ gapSize[16]=11;}}
		if(((seed>>17)&1)==1){gapCount[gapSize[17]]++; gapSize[17]=0;}else{ gapSize[17]++; if(gapSize[17]>11){ gapSize[17]=11;}}
		if(((seed>>18)&1)==1){gapCount[gapSize[18]]++; gapSize[18]=0;}else{ gapSize[18]++; if(gapSize[18]>11){ gapSize[18]=11;}}
		if(((seed>>19)&1)==1){gapCount[gapSize[19]]++; gapSize[19]=0;}else{ gapSize[19]++; if(gapSize[19]>11){ gapSize[19]=11;}}
		if(((seed>>20)&1)==1){gapCount[gapSize[20]]++; gapSize[20]=0;}else{ gapSize[20]++; if(gapSize[20]>11){ gapSize[20]=11;}}
		if(((seed>>21)&1)==1){gapCount[gapSize[21]]++; gapSize[21]=0;}else{ gapSize[21]++; if(gapSize[21]>11){ gapSize[21]=11;}}
		if(((seed>>22)&1)==1){gapCount[gapSize[22]]++; gapSize[22]=0;}else{ gapSize[22]++; if(gapSize[22]>11){ gapSize[22]=11;}}
		if(((seed>>23)&1)==1){gapCount[gapSize[23]]++; gapSize[23]=0;}else{ gapSize[23]++; if(gapSize[23]>11){ gapSize[23]=11;}}
		if(((seed>>24)&1)==1){gapCount[gapSize[24]]++; gapSize[24]=0;}else{ gapSize[24]++; if(gapSize[24]>11){ gapSize[24]=11;}}
		if(((seed>>25)&1)==1){gapCount[gapSize[25]]++; gapSize[25]=0;}else{ gapSize[25]++; if(gapSize[25]>11){ gapSize[25]=11;}}
		if(((seed>>26)&1)==1){gapCount[gapSize[26]]++; gapSize[26]=0;}else{ gapSize[26]++; if(gapSize[26]>11){ gapSize[26]=11;}}
		if(((seed>>27)&1)==1){gapCount[gapSize[27]]++; gapSize[27]=0;}else{ gapSize[27]++; if(gapSize[27]>11){ gapSize[27]=11;}}
		if(((seed>>28)&1)==1){gapCount[gapSize[28]]++; gapSize[28]=0;}else{ gapSize[28]++; if(gapSize[28]>11){ gapSize[28]=11;}}
		if(((seed>>29)&1)==1){gapCount[gapSize[29]]++; gapSize[29]=0;}else{ gapSize[29]++; if(gapSize[29]>11){ gapSize[29]=11;}}
		if(((seed>>30)&1)==1){gapCount[gapSize[30]]++; gapSize[30]=0;}else{ gapSize[30]++; if(gapSize[30]>11){ gapSize[30]=11;}}
		if(((seed>>31)&1)==1){gapCount[gapSize[31]]++; gapSize[31]=0;}else{ gapSize[31]++; if(gapSize[31]>11){ gapSize[31]=11;}}
	}

		for (int i=0; i<12; i++) {
#pragma HLS PIPELINE
		gapStream[i] = gapCount[i];
	}
}
