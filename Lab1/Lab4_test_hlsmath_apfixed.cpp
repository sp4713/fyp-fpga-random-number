#include <stdio.h>
#include <ap_fixed.h>

typedef ap_fixed<16,5> fix_t;

double distPoints_double(double Ax, double Ay, double Bx, double By);
float distPoints_float(float Ax, float Ay, float Bx, float By);
fix_t distPoints_fixed(fix_t Ax, fix_t Ay, fix_t Bx, fix_t By);

int main(){
	double Ax = 1;		double Bx = 0.5f;
	double Ay = 2.5f;	double By = 4.5f;

	double dist_double = distPoints_double(Ax, Ay, Bx, By);

	float dist_float = distPoints_float((float)Ax, (float)Ay, (float)Bx, (float)By);

	fix_t dist_fixed = distPoints_fixed((fix_t)Ax, (fix_t)Ay, (fix_t)Bx, (fix_t)By);

	printf("Distance between A-B (DOUBLE):%f\n",(float)dist_double);
	printf("Distance between A-B (FLOAT):%f\n",(float)dist_float);
	printf("Distance between A-B (FIXED):%f\n",(float)dist_fixed);

	return 0;
}
/*
   Compiling ../../../../Lab4_test_hlsmath_apfixed.cpp in debug mode
   Compiling ../../../../Lab4_hlsmath_apfixed.cpp in debug mode
   Generating csim.exe
Distance between A-B (DOUBLE):2.061553
Distance between A-B (FLOAT):2.061553
Distance between A-B (FIXED):2.061523
@I [SIM-1] CSim done with 0 errors.
*/