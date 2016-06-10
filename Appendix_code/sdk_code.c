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

// please specify parameters here

//maximum: 17592186044415 (2^44-1)
#define n_input 4294967296
//maximum: 4294967295 (2^32-1)
#define seed_input 0

// p-value parameters
u32 expected_freq = n_input/4096;	//50% chance of occurring for each sample * 2^11 concatenation
u32 expected_serial = n_input/16384; //25% chance of occurrence every 2 samples * 2^11 concatenation
double p_val_freq;
double p_val_serial;

double Y_freq = 0.0;
double Y_serial = 0.0;
double XSqr_freq;
double XSqr_serial;

// Freq Serial HW instance
XFreq_serial FreqSerial;

// Time-measuring variables
XTime tStart, tEnd;

// Address Pointers for test outputs
char *charDataAddress;
int *intDataAddress;

int serialchardebug_value; //saves how many bytes there are
int serialintdebug_value; //saves how many words there are

int freqchardebug_value; //
int freqintdebug_value;

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

static double igf(double s, double t){
    if(t < 0.0)
    {
		return 0.0;
    }
    double sc = (1.0 / s);
    sc *= pow(t, s);
    sc *= exp(-t);

    double sum = 1.0;
    double nom = 1.0;
    double denom = 1.0;

    for(int i = 0; i < 200; i++)
    {
		nom *= t;
		s++;
		denom *= s;
		sum += (nom / denom);
    }

    return sum * sc;
}

double gamma(double t){
    const long double sqrt2pi = 2.5066282746310005024157652848110452530069867406099383;

    long double Z = (long double)t;
    long double Sc = powl((Z + A), (Z + 0.5));
    Sc *= expl(-1.0 * (Z + A));
    Sc /= Z;

    long double F = 1.0;
    long double Ck;
    long double sum = sqrt2pi;

    for(int K = 1; K < A; K++)
    {
        Z++;
		Ck = powl(A - K, K - 0.5);
		Ck *= expl(A - K);
		Ck /= F;

		sum += (Ck / Z);

		F *= (-1.0 * K);
    }

    return (double)(sum * Sc);
}


double chisqr(int v, double Y)
{
    if(Y < 0)
    {
        return 0.0;
    }
	double s = ((double)v) * 0.5;
	double t = Y * 0.5;
	double p = igf(s,t);
	if(isnan(p) || isinf(p) || p <= 1e-8)
    {
        return 1e-14;
    }

    p /= gamma(s);
    return (1.0 - p);
}

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
	XFreq_serial *pAccelerator = (XFreq_serial *) InstancePtr;
	XFreq_serial_InterruptEnable(pAccelerator, 1);
	XFreq_serial_InterruptGlobalEnable(pAccelerator);
	XFreq_serial_Start(pAccelerator);
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
		serialchardebug_value = XFreq_serial_Read_serialTwoStream_V_Bytes(&FreqSerial, 0, charDataAddress+128, 512);
		serialintdebug_value = XFreq_serial_Read_serialTwoStream_V_Words(&FreqSerial, 0, intDataAddress+32, 128);

		//read serial three-tuple test values
		serialchardebug_value = XFreq_serial_Read_serialThreeStream_V_Bytes(&FreqSerial, 0, charDataAddress+640, 512);
		serialintdebug_value = XFreq_serial_Read_serialThreeStream_V_Words(&FreqSerial, 0, intDataAddress+160, 128);

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
		printf("Serial Char Debug Value: %d\n\r", serialchardebug_value);
		printf("Freq Char Debug Value: %d\n\r", freqchardebug_value);

		printf("Serial Int Debug Value: %d\n\r", serialintdebug_value);
		printf("Freq Int Debug Value: %d\n\r", freqintdebug_value);

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
		for(int i=0; i<128; i++){
			printf("%lu, ",(unsigned long int)*(intDataAddress+160+i));
		}
	printf("\n");

	printf("Serial 2 Histogram: \n");
	for(int i=0; i<128; i++){
		printf("%lu, ",(unsigned long int)*(intDataAddress+32+i));
	}
	printf("\n");

	printf("Frequency Histogram: \n");
	for(int i=0; i<32; i++){
		printf("%lu, ",(unsigned long int)*(intDataAddress+i));
	}
	printf("\n");

	// Y-value computations

	for(int i=0; i<32; i++){
		Y_freq += (((u32)(*(intDataAddress+i))-expected_freq)*((u32)(*(intDataAddress+i))-expected_freq))/expected_freq;
	}
	for(int i=0; i<128; i++){
		Y_serial += (((u32)(*(intDataAddress+i+32))-expected_freq)*((u32)(*(intDataAddress+i+32))-expected_freq))/expected_freq;
	}
	printf("Y of Frequency Test: %g\n", Y_freq);
	printf("Y of Serial Test: %g\n", Y_serial);

	// p-value computations

	p_val_freq = chisqr(31, Y_freq);		//degrees of freedom for frequency: 32-1
	p_val_serial = chisqr(127, Y_serial);	//degrees of freedom for serial: 128-1
	printf("p-value of Frequency Test: %g\n", p_val_freq);
	printf("p-value of Serial Test: %g\n", p_val_serial);

	printf("Test Finished. Goodbye.\n");

	cleanup_platform();
	return 0;
}
