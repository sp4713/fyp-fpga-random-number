#include "hls_math.h" 

#include <math.h> //included for pow method

#include <ap_fixed.h> //included for fixed point support

typedef ap_fixed<16,5> fix_t;

double distPoints_double(double Ax, double Ay, double Bx, double By){
	return hls::sqrt(pow(Ax-Bx,2) + pow(Ay-By,2));
}//Latency 46-46 - Interval 47-47
 //BRAM_18K 0 0% - DSP48E 28 12% - FF 3659 3% - LUT 5854 11%
 //Ax, Ay, Bx, By apreturn 64Bits
 
float distPoints_float(float Ax, float Ay, float Bx, float By){
	return hls::sqrt(pow(Ax-Bx,2) + pow(Ay-By,2));
}//Latency 48-48 - Interval 49-49
 //BRAM_18K 0 0% - DSP48E 29 13% - FF 4146 3% - LUT 5854 11%
 //Ax, Ay, Bx, By apreturn 64Bits

fix_t distPoints_fixed(fix_t Ax, fix_t Ay, fix_t Bx, fix_t By){
	return hls::sqrt((Ax-Bx)*(Ax-Bx) + ((Ay-By)*(Ay-By)));
}//Latency 41-41 - Interval 42-42
 //BRAM_18K 0 0% - DSP48E 2 0% - FF 2652 2% - LUT 3546 6%
 //Ax, Ay, Bx, By apreturn 64Bits