#include "Lab8_HLS_AxiMaster_header.h"

int setMem(unsigned char value, unsigned char addr, int size){

#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS
#pragma HLS INTERFACE m_axi port=addrMaster offset=slave bundle=MASTER_BUS
//#pragma HLS INTERFACE m_axi depth=addr offset=slave bundle=MASTER_BUS
#pragma HLS INTERFACE s_axilite port=size bundle=CRTL_BUS
#pragma HLS INTERFACE s_axilite port=value bundle=CRTL_BUS

	if(size<MAX_TRANSFER_SIZE){
		for(int idxMemAddr = 0; idxMemaAddr < size; idxMemAddr++){
			#pragma HLS PIPELINE
			addr[idxMemAddr] = value;
		}			
		return 0;
	}else{
		return -1;
	}
}