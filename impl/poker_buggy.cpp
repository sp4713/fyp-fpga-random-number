#include <hls_stream.h>
#include <ap_int.h>

void freqTest(ap_uint<32> pokerStream[5], ap_uint<32> seed, ap_uint<44> n) {
	#pragma HLS INTERFACE ap_ctrl_none port=return	// remove unnecessary hardware ports

// 	begin			//
// 	initialisations	//

//poker test parameters
	//bool enablePoker[4] = 1;
	ap_uint<32> card[4];
#pragma HLS ARRAY_PARTITION variable=card complete dim=1
	ap_uint<32> pokerCount[5];
#pragma HLS ARRAY_PARTITION variable=pokerCount complete dim=1

//initialise test arrays to zero
	for (int i = 0; i < 4; i++) {
	#pragma HLS PIPELINE
		card[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
	#pragma HLS PIPELINE
		pokerCount[i] = 0;
	}
//	begin		//
//	number		//
//	sampling	//

	for (int idx = 0; idx < n; idx++) {
	#pragma HLS PIPELINE
	#pragma HLS LOOP_TRIPCOUNT min=100 max=1000

		//begin card sampling
		card[0] = seed & 0x77;
		card[1] = ((seed >> 8) & 0x77);
		card[2] = ((seed >> 16) & 0x77);
		card[3] = ((seed >> 24) & 0x77);

		//four of a kind
		if(card[0]==card[1]==card[2]==card[3]){
			pokerCount[0]++;
		}
		//three of a kind
		else if((card[0]==card[1]==card[2]!=card[3])
		||(card[0]==card[1]==card[3]!=card[2])
		||(card[0]!=card[1]==card[2]==card[3])
		||(card[2]!=card[0]==card[1]!=card[3])){
			pokerCount[1]++;
		}
		//two pairs
		else if(((card[0]==card[1]) && (card[2]==card[3]) )
		||( (card[0]==card[2]) && (card[1]==card[3]) )
		||( (card[0]==card[3]) && (card[1]==card[2]) ))
		{
			pokerCount[2]++;
		}
		//One Pair
		else if(card[0]!=card[1]!=card[2]!=card[3]){
			pokerCount[4]++;
		}
		else
		/*
		if(((card[0]==card[1]) && (!(card[2]==card[3])) )
		||( (card[0]==card[2]) && (!(card[1]==card[3])) )
		||( (card[0]==card[3]) && (!(card[1]==card[2])) )
		||( (card[1]==card[2]) && (!(card[0]==card[3])) )
		||( (card[1]==card[3]) && (!(card[0]==card[2])) )
		||( (card[2]==card[3]) && (!(card[0]==card[1])) )
		)
		*/
		{
			pokerCount[3]++;
		//end poker test
		}
		//all different
		seed++;
	}
	for(int i=0; i<5; i++){
#pragma HLS PIPELINE
		pokerStream[i] = pokerCount[i];
	}
}
