//Vivado top level arrays as parameters
//void find (char val, char in_vec[10], char out_vec[10])
//Arrays on top functions infer:
//RAM ports
//FIFO ports

//		IN_VEC_ADDRESS				OUT_VEC_ADDRESS
//		IN_VEC_CE					OUT_VEC_CE
//		IN_VEC_Q (output of RAM)	OUT_VEC_WE
//									OUT_VEC_D (output D)

//#pragma HLS INTERFACE ap_memory port=in_vec
//#pragma HLS INTERFACE ap_memory port=out_vec

void find (char val, char in_vec[10], char out_vec[10]){
	#pragma HLS INTERFACE ap_fifo port=in_vec
	#pragma HLS INTERFACE ap_fifo port=out_vec

	for(int idx=0; idx<10; idx++){
		if(in_vec[idx]==val)	out_vec[idx]=1;
		else					out_vec[idx]=0;
	}
}


//									(optionally specify port)
//	#pragma hls interface AP_MEMORY PORT = IN_VEC
//	#prag

//	AXIS (AXI4-Stream)
//	S_AXILITE (AXI4-Lite)
//	M_AXI (AXI4_Full Master)
//	BRAM (Block RAM)

//	In Vivado HLS:
//	Lab_2_HLS
//	Top function: find
