#include <ap_int.h>
#include <stdio.h>
ap_uint<17> simpleALU(ap_uint<17> inA, ap_uint<17> inB, ap_uint<1> op);

int main(){
	ap_uint<17> inA = 10;
	ap_uint<17> inB = 10;
	ap_uint<17> resultAdd, resultSub;

	printf("Reference\n");
	printf("(SUM) inA + inB = %d\n",(unsigned int)inA + (unsigned int)inB);
	printf("(SUB) inA - inB = %d\n",(unsigned int)inA - (unsigned int)inB);

	resultAdd = simpleALU(inA, inB, 1);
	resultSub = simpleALU(inA, inB, 0);

	printf("Our core\n");
	printf("(SUM) inA + inB = %d\n",(unsigned int)resultAdd);
	printf("(SUB) inA - inB = %d\n",(unsigned int)resultSub);

	return 0;
}
