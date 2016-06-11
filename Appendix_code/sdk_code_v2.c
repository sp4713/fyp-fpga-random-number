/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */
//
#include <stdio.h>
#include "platform.h"
#include <math.h>
#include <stdlib.h> // Standard C functions, e.g. exit()
#include <stdbool.h> // Provides a Boolean data type for ANSI/ISO-C
#include "xparameters.h" // Parameter definitions for processor peripherals
#include "xscugic.h" // Processor interrupt controller device driver
#include "xfreq_serial.h" // Device driver for HLS HW block
#include "xtime_l.h" // Time-measuring functions for performance evaluation
#define A 15
bool debugValid = false; //toggle on to assist in debugging

static long double KM(long double S, long double Z);
static long double log_igf(long double S, long double Z);
long double log_gamma(double N);
double chisqr(int Dof, double Cv);

// please specify parameters here

//maximum: 17592186044415 (2^44-1)
#define n_input 200000
//maximum: 4294967295 (2^32-1)
#define seed_input 0
#define offset_input 0

// p-value parameters
double expected_freq = n_input/2;	//50% chance of occurring for each sample
double expected_serial_two = n_input/(2*4); //25% chance of occurrence every 2 samples
double expected_serial_three = n_input/(3*8); //12.5% chance of occurrence every 3 samples

double p_val_freq;
double p_val_serial_two;
double p_val_serial_three;

double Y_freq = 0.0;
double Y_serial_two = 0.0;
double Y_serial_three = 0.0;

double XSqr_freq;
double XSqr_serial_two;
double XSqr_serial_three;

// Decompression calculations parameters
double freq_cached[32];
double serial_two_cached[112];
double serial_two_decompressed[128];
double serial_three_cached[96];
double serial_three_decompressed[128];

// Freq Serial HW instance
XFreq_serial FreqSerial;

// Time-measuring variables
XTime tStart, tEnd;

// Address Pointers for test outputs
char *charDataAddress;
int *intDataAddress;

int freqchardebug_value;
int freqintdebug_value;

int serialtwochardebug_value; //saves how many bytes there are
int serialtwointdebug_value; //saves how many words there are

int serialthreechardebug_value; //saves how many bytes there are
int serialthreeintdebug_value; //saves how many words there are

u32 freqwritedebug_value;
u32 serialtwowritedebug_value;
u32 serialthreewritedebug_value;

//hw debug variables

int freq_base_address_hw, freq_high_address_hw, freq_total_bytes_hw,
		freq_bit_width_hw, freq_depth_hw;
int serial_2_base_address_hw, serial_2_high_address_hw, serial_2_total_bytes_hw,
		serial_2_bit_width_hw, serial_2_depth_hw;
int serial_3_base_address_hw, serial_3_high_address_hw, serial_3_total_bytes_hw,
		serial_3_bit_width_hw, serial_3_depth_hw;

//Interrupt Controller Instance
XScuGic ScuGic;

volatile static int RunFreqSerial = 0;
volatile static int ResultAvailSerialFreq = 0;

int XFreq_serial_init(XFreq_serial *XFreq_serialPtr) {
	XFreq_serial_Config *cfgPtr;
	int status;
	cfgPtr = XFreq_serial_LookupConfig(XPAR_FREQ_SERIAL_0_DEVICE_ID);
	if (!cfgPtr) {
		print("ERROR: Lookup of accelerator configuration failed.\n\r");
		return XST_FAILURE;
	}
	status = XFreq_serial_CfgInitialize(XFreq_serialPtr, cfgPtr);
	if (status != XST_SUCCESS) {
		print("ERROR: Could not initialise accelerator.\n\r");
		return XST_FAILURE;
	}
	return status;
}

void freq_serial_start(void *InstancePtr) {
	XFreq_serial *pHLS = (XFreq_serial *) InstancePtr;
//	XFreq_serial_InterruptEnable(pHLS, 1);
//	XFreq_serial_InterruptGlobalEnable(pHLS);
	XFreq_serial_Start(pHLS);
}

int main() {
	init_platform();
	//Setup the freq serial hw platform
	int status = XFreq_serial_init(&FreqSerial);
	if (status != XST_SUCCESS) {
		print("Freq Serial peripheral setup failed\n\r");
		exit(-1);
	}

//set the input parameters of the HLS block
	XFreq_serial_Set_seed_V(&FreqSerial, seed_input);
	XFreq_serial_Set_n_V(&FreqSerial, n_input);
	XFreq_serial_Set_offset_V(&FreqSerial, offset_input);

//initialise the histograms to zero
	freqwritedebug_value = XFreq_serial_Write_freqStream_V_Words(&FreqSerial, 0, 0, 128);
	serialtwowritedebug_value = XFreq_serial_Write_serialTwoStream_V_Words(&FreqSerial, 0, 0, 512);
	serialthreewritedebug_value = XFreq_serial_Write_serialThreeStream_V_Words(&FreqSerial, 0, 0, 512);

//check that suite is ready
	if (XFreq_serial_IsReady(&FreqSerial)){
		print("Freq Serial peripheral is ready. Starting test...\n\r");
		printf("Results ETA: %.2f seconds (%.2f minutes) \n\r",(double)(n_input/(COUNTS_PER_SECOND*0.3)), (double)(n_input/(COUNTS_PER_SECOND*43.2)));
	}else{
		print("!!!WARNING: Freq Serial peripheral is not ready! Exiting...\n\r");
		exit(-1);
	}

	// Simple non-interrupt driven test
	XFreq_serial_Start(&FreqSerial);

	//start time measurement
	XTime_GetTime(&tStart);

	do {
		//get freq test hardware specification information
		freq_base_address_hw = XFreq_serial_Get_freqStream_V_BaseAddress(&FreqSerial);
		freq_high_address_hw = XFreq_serial_Get_freqStream_V_HighAddress(&FreqSerial);
		freq_total_bytes_hw = XFreq_serial_Get_freqStream_V_TotalBytes(&FreqSerial);
		freq_bit_width_hw = XFreq_serial_Get_freqStream_V_BitWidth(&FreqSerial);
		freq_depth_hw = XFreq_serial_Get_freqStream_V_Depth(&FreqSerial);

		//get serial two-tuple test hardware specification information
		serial_2_base_address_hw = XFreq_serial_Get_serialTwoStream_V_BaseAddress(&FreqSerial);
		serial_2_high_address_hw = XFreq_serial_Get_serialTwoStream_V_HighAddress(&FreqSerial);
		serial_2_total_bytes_hw = XFreq_serial_Get_serialTwoStream_V_TotalBytes(&FreqSerial);
		serial_2_bit_width_hw = XFreq_serial_Get_serialTwoStream_V_BitWidth(&FreqSerial);
		serial_2_depth_hw = XFreq_serial_Get_serialTwoStream_V_Depth(&FreqSerial);

		//get serial three-tuple test hardware specification information
		serial_3_base_address_hw = XFreq_serial_Get_serialThreeStream_V_BaseAddress(&FreqSerial);
		serial_3_high_address_hw = XFreq_serial_Get_serialThreeStream_V_HighAddress(&FreqSerial);
		serial_3_total_bytes_hw = XFreq_serial_Get_serialThreeStream_V_TotalBytes(&FreqSerial);
		serial_3_bit_width_hw = XFreq_serial_Get_serialThreeStream_V_BitWidth(&FreqSerial);
		serial_3_depth_hw = XFreq_serial_Get_serialThreeStream_V_Depth(&FreqSerial);

		//read freq test values
		freqchardebug_value = XFreq_serial_Read_freqStream_V_Bytes(&FreqSerial, 0, charDataAddress, 128);
		freqintdebug_value = XFreq_serial_Read_freqStream_V_Words(&FreqSerial, 0, intDataAddress, 32);

		//read serial two-tuple test values
		serialtwochardebug_value = XFreq_serial_Read_serialTwoStream_V_Bytes(&FreqSerial, 0, charDataAddress+128, 512);
		serialtwointdebug_value = XFreq_serial_Read_serialTwoStream_V_Words(&FreqSerial, 0, intDataAddress+32, 128);

		//read serial three-tuple test values
		serialthreechardebug_value = XFreq_serial_Read_serialThreeStream_V_Bytes(&FreqSerial, 0, charDataAddress+640, 512);
		serialthreeintdebug_value = XFreq_serial_Read_serialThreeStream_V_Words(&FreqSerial, 0, intDataAddress+160, 128);

	} while (!XFreq_serial_IsReady(&FreqSerial));

	//get time measurement
	XTime_GetTime(&tEnd);

	//output the test parameters and results
	printf("Sample Size: %llu \n\r", (long long int)n_input);
	printf("Seed: %llu \n\r", (long long int)seed_input);

	//output time measurements
	printf("%llu samples were analysed in %.2f us (%.2f seconds).\n", (long long unsigned int) n_input, 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000), 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND));
	//Xilinx time functions measure time in PS clock cycles, so conversion to PL clock rate is required
	printf("PL clock cycles per sample: %.2f \n", (1.0)*((2*(tEnd - tStart))/((n_input*6.66666687))));

	if(debugValid){
		//number of chi-squared categories
		printf("Freq Char Debug Value: %d\n\r", freqchardebug_value);
		printf("Serial 2 Char Debug Value: %d\n\r", serialtwochardebug_value);
		printf("Serial 3 Char Debug Value: %d\n\r", serialthreechardebug_value);

		printf("Freq Int Debug Value: %d\n\r", freqintdebug_value);
		printf("Serial 2 Int Debug Value: %d\n\r", serialtwointdebug_value);
		printf("Serial 3 Int Debug Value: %d\n\r", serialthreeintdebug_value);

		//hardware specification information
		printf("Freq Base Address: %d\n\r", freq_base_address_hw);
		printf("Freq High Address: %d\n\r", freq_high_address_hw);
		printf("Freq Total Bytes: %d\n\r", freq_total_bytes_hw);
		printf("Freq Bit Width: %d\n\r", freq_bit_width_hw);
		printf("Freq Depth: %d\n\r", freq_depth_hw);

		printf("Serial 2 Base Address: %d\n\r", serial_2_base_address_hw);
		printf("Serial 2 High Address: %d\n\r", serial_2_high_address_hw);
		printf("Serial 2 Total Bytes: %d\n\r", serial_2_total_bytes_hw);
		printf("Serial 2 Bit Width: %d\n\r", serial_2_bit_width_hw);
		printf("Serial 2 Depth: %d\n\r", serial_2_depth_hw);

		printf("Serial 3 Base Address: %d\n\r", serial_3_base_address_hw);
		printf("Serial 3 High Address: %d\n\r", serial_3_high_address_hw);
		printf("Serial 3 Total Bytes: %d\n\r", serial_3_total_bytes_hw);
		printf("Serial 3 Bit Width: %d\n\r", serial_3_bit_width_hw);
		printf("Serial 3 Depth: %d\n\r", serial_3_depth_hw);
	}
	//output test values

	printf("Serial 3 Histogram: \n");
	for(int i=0; i<112; i++){
		serial_three_cached[i] = (*(intDataAddress+160+i))<<11;
		printf("%f, ",serial_three_cached[i]);
	}
	printf("\n");

	printf("Serial 2 Histogram: \n");
	for(int i=0; i<96; i++){
		serial_two_cached[i] = (*(intDataAddress+160+i))<<11;
		printf("%f, ",serial_two_cached[i]);
	}
	printf("\n");

	printf("Frequency Histogram: \n");
	for(int i=0; i<32; i++){
		freq_cached[i] = (*(intDataAddress+i))<<12;
		printf("%f, ", freq_cached[i]);
	}
	printf("\n");

//Histogram Decompression

	//serial two-tuple test decompression

	for (int i = 0; i<96; i++){
		serial_two_decompressed[i+i/3] = serial_two_cached[i];
	}
	for (int i = 0; i<32; i++){
		serial_two_decompressed[i * 4 + 3] = (expected_serial_two * 4)
				- (serial_two_decompressed[i * 4])
				- (serial_two_decompressed[i * 4 + 1])
				- (serial_two_decompressed[i * 4 + 2]);
	}

	//serial three-tuple test decompression
	for (int i = 0; i < 112; i++) {
		serial_three_decompressed[i + (i / 7)] = serial_three_cached[i];
	}

	for (int i = 0; i < 16; i++) {
		serial_three_decompressed[i * 8 + 7] = (expected_serial_three * 8)
				- (serial_three_decompressed[i * 8])
				- (serial_three_decompressed[i * 8 + 1])
				- (serial_three_decompressed[i * 8 + 2])
				- (serial_three_decompressed[i * 8 + 3])
				- (serial_three_decompressed[i * 8 + 4])
				- (serial_three_decompressed[i * 8 + 5])
				- (serial_three_decompressed[i * 8 + 6]);
	}

	// Y-value computations

	for(int i=0; i<32; i++){
		Y_freq += ((freq_cached[i]-expected_freq)*(freq_cached[i]-expected_freq))/expected_freq;
	}
	for(int i=0; i<128; i++){
		Y_serial_two += ((serial_two_decompressed[i]-expected_serial_two)*(serial_two_decompressed[i]-expected_serial_two))/expected_serial_two;
	}
	for(int i=0; i<128; i++){
		Y_serial_three += ((serial_three_decompressed[i]-expected_serial_three)*(serial_three_decompressed[i]-expected_serial_three))/expected_serial_three;
	}

	// p-value computations

	p_val_freq = chisqr(32, Y_freq);		//degrees of freedom for frequency: 32-1
	p_val_serial_two = chisqr(96, Y_serial_two);	//degrees of freedom for serial: 128-1
	p_val_serial_three = chisqr(112, Y_serial_three);	//degrees of freedom for serial: 128-1
	printf("p-value of Frequency Test: %g\n", p_val_freq);
	printf("p-value of Serial 2-Tuple Test: %g\n", p_val_serial_two);
	printf("p-value of Serial 3-Tuple Test: %g\n", p_val_serial_three);

	printf("Test Finished. Goodbye.\n");

	cleanup_platform();
	return 0;
}

double chisqr(int Dof, double Cv)
{
    printf("Dof:  %i\n", Dof);
    printf("Y:  %f\n", Cv);
    if(Cv < 0 || Dof < 1)
    {
        return 0.0;
    }
	double K = ((double)Dof) * 0.5;
	double X = Cv * 0.5;
	if(Dof == 2)
	{
		return exp(-1.0 * X);
	}
	long double PValue, Gam;
    long double ln_PV;
    ln_PV = log_igf(K, X);

    Gam = log_gamma(K);

    ln_PV -= Gam;
    PValue = 1.0 - expl(ln_PV);

	return (double)PValue;

}

static long double log_igf(long double S, long double Z)
{
	if(Z < 0.0)
	{
		return 0.0;
	}
	long double Sc, K;
	Sc = (logl(Z) * S) - Z - logl(S);

    K = KM(S, Z);

    return logl(K) + Sc;
}

static long double KM(long double S, long double Z)
{
	long double Sum = 1.0;
	long double Nom = 1.0;
	long double Denom = 1.0;

	for(int I = 0; I < 1000; I++) // Loops for 1000 iterations
	{
		Nom *= Z;
		S++;
		Denom *= S;
		Sum += (Nom / Denom);
	}

    return Sum;
}

long double log_gamma(double N)
{
	const long double SQRT2PI = sqrtl(atanl(1.0) * 8.0);

    long double Z = (long double)N;
    long double Sc;

    Sc = (logl(Z + A) * (Z + 0.5)) - (Z + A) - logl(Z);

	long double F = 1.0;
	long double Ck;
    long double Sum = SQRT2PI;


	for(int K = 1; K < A; K++)
	{
	    Z++;
		Ck = powl(A - K, K - 0.5);
		Ck *= expl(A - K);
		Ck /= F;

		Sum += (Ck / Z);

		F *= (-1.0 * K);
	}

	return logl(Sum) + Sc;
}
