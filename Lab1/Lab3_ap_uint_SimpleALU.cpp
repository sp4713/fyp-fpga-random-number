#include <ap_int.h>

ap_uint<17> simpleALU(ap_uint<17> inA, ap_uint<17> inB, ap_uint<1> op){

	if(op==1) return inA+inB;
	else return inA-inB;
}
