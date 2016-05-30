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
#include <stdlib.h> // Standard C functions, e.g. exit()
#include <stdbool.h> // Provides a Boolean data type for ANSI/ISO-C
#include "xparameters.h" // Parameter definitions for processor peripherals
#include "xscugic.h" // Processor interrupt controller device driver
#include "xfreq_serial.h" // Device driver for HLS HW block
#include "xtime_l.h" // Time-measuring functions for performance evaluation

// Test parameters
u64 n_input = 700000000000;
int seed_input = 0;

// Freq Serial HW instance
XFreq_serial FreqSerial;

// Time-measuring variables
XTime tStart, tEnd;

// Address Pointers for test outputs
char *charDataAddress;
int *intDataAddress;

int serialchardebug_value;
int serialintdebug_value;

int freqchardebug_value;
int freqintdebug_value;

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
		print("ERROR: Could not initialize accelerator.\n\r");
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

/*
	void freq_serial_isr(void *InstancePtr) {
	XFreq_serial *pAccelerator = (XFreq_serial *) InstancePtr;
//Disable the global interrupt
	XFreq_serial_InterruptGlobalDisable(pAccelerator);
//Disable the local interrupt
	XFreq_serial_InterruptDisable(pAccelerator, 0xffffffff);
// clear the local interrupt
	XFreq_serial_InterruptClear(pAccelerator, 1);
	ResultAvailSerialFreq = 1;
// restart the core if it should run again
	if (RunFreqSerial) {
		freq_serial_start(pAccelerator);
	}
}
int setup_interrupt() {
//This functions sets up the interrupt on the ARM
	int result;
	XScuGic_Config *pCfg = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
	if (pCfg == NULL) {
		print("Interrupt Configuration Lookup Failed\n\r");
		return XST_FAILURE;
	}
	result = XScuGic_CfgInitialize(&ScuGic, pCfg, pCfg->CpuBaseAddress);
	if (result != XST_SUCCESS) {
		return result;
	}
// self-test
	result = XScuGic_SelfTest(&ScuGic);
	if (result != XST_SUCCESS) {
		return result;
	}
// Initialize the exception handler
	Xil_ExceptionInit();
// Register the exception handler
//print("Register the exception handler\n\r");
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, &ScuGic);
//Enable the exception handler
	Xil_ExceptionEnable();
// Connect the Adder ISR to the exception table
//print("Connect the Adder ISR to the Exception handler table\n\r");
	result = XScuGic_Connect(&ScuGic, XPAR_FABRIC_XFreq_serial_0_INTERRUPT_INTR,
			(Xil_InterruptHandler) XFreq_serial_isr, &FreqSerial);
	if (result != XST_SUCCESS) {
		return result;
	}
//print("Enable the Adder ISR\n\r");
	XScuGic_Enable(&ScuGic, XPAR_FABRIC_XFreq_serial_0_INTERRUPT_INTR);
	return XST_SUCCESS;
}
*/

/*
void sw_serial_freq(unsigned int freqCount[32], unsigned int *accum, bool accum_clr) {
	unsigned int serialCount[128];
	unsigned int seed_prev = 0;
	bool enableSerial = 0;

	for (int i = 0; i < 32; i++) {
		freqCount[i] = 0;
	}
	for (int i = 0; i < 128; i++) {
#pragma HLS PIPELINE
		serialCount[i] = 0;
	}

	for (int i = 0; i < n_input; i++) {
#pragma HLS LOOP_TRIPCOUNT min=100 max=10000
#pragma HLS PIPELINE
		freqCount[0] += ((seed >> 0) & 1);
		freqCount[1] += ((seed >> 1) & 1);
		freqCount[2] += ((seed >> 2) & 1);
		freqCount[3] += ((seed >> 3) & 1);
		freqCount[4] += ((seed >> 4) & 1);
		freqCount[5] += ((seed >> 5) & 1);
		freqCount[6] += ((seed >> 6) & 1);
		freqCount[7] += ((seed >> 7) & 1);
		freqCount[8] += ((seed >> 8) & 1);
		freqCount[9] += ((seed >> 9) & 1);
		freqCount[10] += ((seed >> 10) & 1);
		freqCount[11] += ((seed >> 11) & 1);
		freqCount[12] += ((seed >> 12) & 1);
		freqCount[13] += ((seed >> 13) & 1);
		freqCount[14] += ((seed >> 14) & 1);
		freqCount[15] += ((seed >> 15) & 1);
		freqCount[16] += ((seed >> 16) & 1);
		freqCount[17] += ((seed >> 17) & 1);
		freqCount[18] += ((seed >> 18) & 1);
		freqCount[19] += ((seed >> 19) & 1);
		freqCount[20] += ((seed >> 20) & 1);
		freqCount[21] += ((seed >> 21) & 1);
		freqCount[22] += ((seed >> 22) & 1);
		freqCount[23] += ((seed >> 23) & 1);
		freqCount[24] += ((seed >> 24) & 1);
		freqCount[25] += ((seed >> 25) & 1);
		freqCount[26] += ((seed >> 26) & 1);
		freqCount[27] += ((seed >> 27) & 1);
		freqCount[28] += ((seed >> 28) & 1);
		freqCount[29] += ((seed >> 29) & 1);
		freqCount[30] += ((seed >> 30) & 1);
		freqCount[31] += ((seed >> 31) & 1);
		//end of freqCount algorithm
		seed_prev = seed;
		seed++;

		//serial test}
		enableSerial=!enableSerial;
		if(enableSerial){
			if (((seed_prev >>0)&1)==0) {if (((seed >>0)&1)==0) {serialCount[0 * 4]++;} else {serialCount[0* 4 + 1]++;}} else {if (((seed >> 0)&1)==0) {serialCount[0 * 4 + 2]++;} else {serialCount[0* 4 + 3]++;}}
			if (((seed_prev >>1)&1)==0) {if (((seed >>1)&1)==0) {serialCount[1 * 4]++;} else {serialCount[1* 4 + 1]++;}} else {if (((seed >> 1)&1)==0) {serialCount[1 * 4 + 2]++;} else {serialCount[1* 4 + 3]++;}}
			if (((seed_prev >>2)&1)==0) {if (((seed >>2)&1)==0) {serialCount[2 * 4]++;} else {serialCount[2* 4 + 1]++;}} else {if (((seed >> 2)&1)==0) {serialCount[2 * 4 + 2]++;} else {serialCount[2* 4 + 3]++;}}
			if (((seed_prev >>3)&1)==0) {if (((seed >>3)&1)==0) {serialCount[3 * 4]++;} else {serialCount[3* 4 + 1]++;}} else {if (((seed >> 3)&1)==0) {serialCount[3 * 4 + 2]++;} else {serialCount[3* 4 + 3]++;}}
			if (((seed_prev >>4)&1)==0) {if (((seed >>4)&1)==0) {serialCount[4 * 4]++;} else {serialCount[4* 4 + 1]++;}} else {if (((seed >> 4)&1)==0) {serialCount[4 * 4 + 2]++;} else {serialCount[4* 4 + 3]++;}}
			if (((seed_prev >>5)&1)==0) {if (((seed >>5)&1)==0) {serialCount[5 * 4]++;} else {serialCount[5* 4 + 1]++;}} else {if (((seed >> 5)&1)==0) {serialCount[5 * 4 + 2]++;} else {serialCount[5* 4 + 3]++;}}
			if (((seed_prev >>6)&1)==0) {if (((seed >>6)&1)==0) {serialCount[6 * 4]++;} else {serialCount[6* 4 + 1]++;}} else {if (((seed >> 6)&1)==0) {serialCount[6 * 4 + 2]++;} else {serialCount[6* 4 + 3]++;}}
			if (((seed_prev >>7)&1)==0) {if (((seed >>7)&1)==0) {serialCount[7 * 4]++;} else {serialCount[7* 4 + 1]++;}} else {if (((seed >> 7)&1)==0) {serialCount[7 * 4 + 2]++;} else {serialCount[7* 4 + 3]++;}}
			if (((seed_prev >>8)&1)==0) {if (((seed >>8)&1)==0) {serialCount[8 * 4]++;} else {serialCount[8* 4 + 1]++;}} else {if (((seed >> 8)&1)==0) {serialCount[8 * 4 + 2]++;} else {serialCount[8* 4 + 3]++;}}
			if (((seed_prev >>9)&1)==0) {if (((seed >>9)&1)==0) {serialCount[9 * 4]++;} else {serialCount[9* 4 + 1]++;}} else {if (((seed >> 9)&1)==0) {serialCount[9 * 4 + 2]++;} else {serialCount[9* 4 + 3]++;}}
			if (((seed_prev >>10)&1)==0) {if (((seed >>10)&1)==0) {serialCount[10 * 4]++;} else {serialCount[10* 4 + 1]++;}} else {if (((seed >> 10)&1)==0) {serialCount[10 * 4 + 2]++;} else {serialCount[10* 4 + 3]++;}}
			if (((seed_prev >>11)&1)==0) {if (((seed >>11)&1)==0) {serialCount[11 * 4]++;} else {serialCount[11* 4 + 1]++;}} else {if (((seed >> 11)&1)==0) {serialCount[11 * 4 + 2]++;} else {serialCount[11* 4 + 3]++;}}
			if (((seed_prev >>12)&1)==0) {if (((seed >>12)&1)==0) {serialCount[12 * 4]++;} else {serialCount[12* 4 + 1]++;}} else {if (((seed >> 12)&1)==0) {serialCount[12 * 4 + 2]++;} else {serialCount[12* 4 + 3]++;}}
			if (((seed_prev >>13)&1)==0) {if (((seed >>13)&1)==0) {serialCount[13 * 4]++;} else {serialCount[13* 4 + 1]++;}} else {if (((seed >> 13)&1)==0) {serialCount[13 * 4 + 2]++;} else {serialCount[13* 4 + 3]++;}}
			if (((seed_prev >>14)&1)==0) {if (((seed >>14)&1)==0) {serialCount[14 * 4]++;} else {serialCount[14* 4 + 1]++;}} else {if (((seed >> 14)&1)==0) {serialCount[14 * 4 + 2]++;} else {serialCount[14* 4 + 3]++;}}
			if (((seed_prev >>15)&1)==0) {if (((seed >>15)&1)==0) {serialCount[15 * 4]++;} else {serialCount[15* 4 + 1]++;}} else {if (((seed >> 15)&1)==0) {serialCount[15 * 4 + 2]++;} else {serialCount[15* 4 + 3]++;}}
			if (((seed_prev >>16)&1)==0) {if (((seed >>16)&1)==0) {serialCount[16 * 4]++;} else {serialCount[16* 4 + 1]++;}} else {if (((seed >> 16)&1)==0) {serialCount[16 * 4 + 2]++;} else {serialCount[16* 4 + 3]++;}}
			if (((seed_prev >>17)&1)==0) {if (((seed >>17)&1)==0) {serialCount[17 * 4]++;} else {serialCount[17* 4 + 1]++;}} else {if (((seed >> 17)&1)==0) {serialCount[17 * 4 + 2]++;} else {serialCount[17* 4 + 3]++;}}
			if (((seed_prev >>18)&1)==0) {if (((seed >>18)&1)==0) {serialCount[18 * 4]++;} else {serialCount[18* 4 + 1]++;}} else {if (((seed >> 18)&1)==0) {serialCount[18 * 4 + 2]++;} else {serialCount[18* 4 + 3]++;}}
			if (((seed_prev >>19)&1)==0) {if (((seed >>19)&1)==0) {serialCount[19 * 4]++;} else {serialCount[19* 4 + 1]++;}} else {if (((seed >> 19)&1)==0) {serialCount[19 * 4 + 2]++;} else {serialCount[19* 4 + 3]++;}}
			if (((seed_prev >>20)&1)==0) {if (((seed >>20)&1)==0) {serialCount[20 * 4]++;} else {serialCount[20* 4 + 1]++;}} else {if (((seed >> 20)&1)==0) {serialCount[20 * 4 + 2]++;} else {serialCount[20* 4 + 3]++;}}
			if (((seed_prev >>21)&1)==0) {if (((seed >>21)&1)==0) {serialCount[21 * 4]++;} else {serialCount[21* 4 + 1]++;}} else {if (((seed >> 21)&1)==0) {serialCount[21 * 4 + 2]++;} else {serialCount[21* 4 + 3]++;}}
			if (((seed_prev >>22)&1)==0) {if (((seed >>22)&1)==0) {serialCount[22 * 4]++;} else {serialCount[22* 4 + 1]++;}} else {if (((seed >> 22)&1)==0) {serialCount[22 * 4 + 2]++;} else {serialCount[22* 4 + 3]++;}}
			if (((seed_prev >>23)&1)==0) {if (((seed >>23)&1)==0) {serialCount[23 * 4]++;} else {serialCount[23* 4 + 1]++;}} else {if (((seed >> 23)&1)==0) {serialCount[23 * 4 + 2]++;} else {serialCount[23* 4 + 3]++;}}
			if (((seed_prev >>24)&1)==0) {if (((seed >>24)&1)==0) {serialCount[24 * 4]++;} else {serialCount[24* 4 + 1]++;}} else {if (((seed >> 24)&1)==0) {serialCount[24 * 4 + 2]++;} else {serialCount[24* 4 + 3]++;}}
			if (((seed_prev >>25)&1)==0) {if (((seed >>25)&1)==0) {serialCount[25 * 4]++;} else {serialCount[25* 4 + 1]++;}} else {if (((seed >> 25)&1)==0) {serialCount[25 * 4 + 2]++;} else {serialCount[25* 4 + 3]++;}}
			if (((seed_prev >>26)&1)==0) {if (((seed >>26)&1)==0) {serialCount[26 * 4]++;} else {serialCount[26* 4 + 1]++;}} else {if (((seed >> 26)&1)==0) {serialCount[26 * 4 + 2]++;} else {serialCount[26* 4 + 3]++;}}
			if (((seed_prev >>27)&1)==0) {if (((seed >>27)&1)==0) {serialCount[27 * 4]++;} else {serialCount[27* 4 + 1]++;}} else {if (((seed >> 27)&1)==0) {serialCount[27 * 4 + 2]++;} else {serialCount[27* 4 + 3]++;}}
			if (((seed_prev >>28)&1)==0) {if (((seed >>28)&1)==0) {serialCount[28 * 4]++;} else {serialCount[28* 4 + 1]++;}} else {if (((seed >> 28)&1)==0) {serialCount[28 * 4 + 2]++;} else {serialCount[28* 4 + 3]++;}}
			if (((seed_prev >>29)&1)==0) {if (((seed >>29)&1)==0) {serialCount[29 * 4]++;} else {serialCount[29* 4 + 1]++;}} else {if (((seed >> 29)&1)==0) {serialCount[29 * 4 + 2]++;} else {serialCount[29* 4 + 3]++;}}
			if (((seed_prev >>30)&1)==0) {if (((seed >>30)&1)==0) {serialCount[30 * 4]++;} else {serialCount[30* 4 + 1]++;}} else {if (((seed >> 30)&1)==0) {serialCount[30 * 4 + 2]++;} else {serialCount[30* 4 + 3]++;}}
			if (((seed_prev >>31)&1)==0) {if (((seed >>31)&1)==0) {serialCount[31 * 4]++;} else {serialCount[31* 4 + 1]++;}} else {if (((seed >> 31)&1)==0) {serialCount[31 * 4 + 2]++;} else {serialCount[31* 4 + 3]++;}}
		}
	}
*/

int main() {
	init_platform();
	print("Begin test of communication with Serial Freq peripheral in PL\n\r");

	//Setup the freq serial hw platform
	int status = XFreq_serial_init(&FreqSerial);
	if (status != XST_SUCCESS) {
		print("Freq Serial peripheral setup failed\n\r");
		exit(-1);
	}
	print("Freq Serial peripheral setup success.\n\r");

	//hw variables
	int freq_base_address_hw, freq_high_address_hw, freq_total_bytes_hw,
			freq_bit_width_hw, freq_depth_hw;
	int serial_base_address_hw, serial_high_address_hw, serial_total_bytes_hw,
			serial_bit_width_hw, serial_depth_hw;

/*
//Setup the interrupt
//	status = setup_interrupt();
	if (status != XST_SUCCESS) {
		print("Interrupt setup failed\n\r");
		exit(-1);
	}
*/
//set the input parameters of the HLS block
	XFreq_serial_Set_seed_V(&FreqSerial, seed_input);
	XFreq_serial_Set_n_V(&FreqSerial, n_input);
	if (XFreq_serial_IsReady(&FreqSerial))
		print("Freq Serial peripheral is ready. Starting test...\n\r");
	else {
		print("!!! HLS peripheral is not ready! Exiting...\n\r");
		exit(-1);
	}
	// Simple non-interrupt driven test
	XFreq_serial_Start(&FreqSerial);

	//start time measurement
	XTime_GetTime(&tStart);

	do {
		//get freq test hardware specification information
		freq_base_address_hw = XFreq_serial_Get_freqStream_V_BaseAddress(
				&FreqSerial);
		freq_high_address_hw = XFreq_serial_Get_freqStream_V_HighAddress(
				&FreqSerial);
		freq_total_bytes_hw = XFreq_serial_Get_freqStream_V_TotalBytes(
				&FreqSerial);
		freq_bit_width_hw = XFreq_serial_Get_freqStream_V_BitWidth(&FreqSerial);
		freq_depth_hw = XFreq_serial_Get_freqStream_V_Depth(&FreqSerial);

		//get serial test hardware specification information
		serial_base_address_hw = XFreq_serial_Get_freqStream_V_BaseAddress(
				&FreqSerial);
		serial_high_address_hw = XFreq_serial_Get_freqStream_V_HighAddress(
				&FreqSerial);
		serial_total_bytes_hw = XFreq_serial_Get_freqStream_V_TotalBytes(
				&FreqSerial);
		serial_bit_width_hw = XFreq_serial_Get_freqStream_V_BitWidth(&FreqSerial);
		serial_depth_hw = XFreq_serial_Get_freqStream_V_Depth(&FreqSerial);

		//get serial test values
		serialchardebug_value = XFreq_serial_Read_serialStream_V_Bytes(&FreqSerial, 0, charDataAddress+128, 512);
		serialintdebug_value = XFreq_serial_Read_serialStream_V_Words(&FreqSerial, 0, intDataAddress+32, 128);

		//get freq test values
		freqchardebug_value = XFreq_serial_Read_freqStream_V_Bytes(&FreqSerial, 0, charDataAddress, 128);
		freqintdebug_value = XFreq_serial_Read_freqStream_V_Words(&FreqSerial, 0, intDataAddress, 32);

	} while (!XFreq_serial_IsReady(&FreqSerial));

	//get time measurement
	XTime_GetTime(&tEnd);

	//output the test parameters and results
	printf("Sample Size: %llu \n\r", n_input);
	printf("Seed: %d\n\r", seed_input);

	//output time measurements
	printf("%llu samples were analysed in %.2f us.\n", (long long unsigned int) n_input, 1.0 * (tEnd - tStart) / (COUNTS_PER_SECOND/1000000));
	//time functions measure time in PS clock cycles, so conversion to PL clock rate is required
	printf("PL clock cycles per sample: %.2f \n", (1.0)*((2*(tEnd - tStart))/((n_input*6.66666687))));

	//number of chi-squared categories
	printf("Serial Char Debug Value: %d\n\r", serialchardebug_value);
	printf("Freq Char Debug Value: %d\n\r", freqchardebug_value);

	//hardware specification information
	printf("Freq Base Address: %d\n\r", freq_base_address_hw);
	printf("Freq High Address: %d\n\r", freq_high_address_hw);
	printf("Freq Total Bytes: %d\n\r", freq_total_bytes_hw);
	printf("Freq Bit Width: %d\n\r", freq_bit_width_hw);
	printf("Freq Depth: %d\n\r", freq_depth_hw);
	printf("Serial Base Address: %d\n\r", serial_base_address_hw);
	printf("Serial High Address: %d\n\r", serial_high_address_hw);
	printf("Serial Total Bytes: %d\n\r", serial_total_bytes_hw);
	printf("Serial Bit Width: %d\n\r", serial_bit_width_hw);
	printf("Serial Depth: %d\n\r", serial_depth_hw);

	//output serial test values
	printf("Serial Histogram: \n");
	printf("%lu, ",(unsigned long int)*(intDataAddress+32));
	printf("%lu, ",(unsigned long int)*(intDataAddress+33));
	printf("%lu, ",(unsigned long int)*(intDataAddress+34));
	printf("%lu, ",(unsigned long int)*(intDataAddress+35));
	printf("%lu, ",(unsigned long int)*(intDataAddress+36));
	printf("%lu, ",(unsigned long int)*(intDataAddress+37));
	printf("%lu, ",(unsigned long int)*(intDataAddress+38));
	printf("%lu, ",(unsigned long int)*(intDataAddress+39));
	printf("%lu, ",(unsigned long int)*(intDataAddress+40));
	printf("%lu, ",(unsigned long int)*(intDataAddress+41));
	printf("%lu, ",(unsigned long int)*(intDataAddress+42));
	printf("%lu, ",(unsigned long int)*(intDataAddress+43));
	printf("%lu, ",(unsigned long int)*(intDataAddress+44));
	printf("%lu, ",(unsigned long int)*(intDataAddress+45));
	printf("%lu, ",(unsigned long int)*(intDataAddress+46));
	printf("%lu, ",(unsigned long int)*(intDataAddress+47));
	printf("%lu, ",(unsigned long int)*(intDataAddress+48));
	printf("%lu, ",(unsigned long int)*(intDataAddress+49));
	printf("%lu, ",(unsigned long int)*(intDataAddress+50));
	printf("%lu, ",(unsigned long int)*(intDataAddress+51));
	printf("%lu, ",(unsigned long int)*(intDataAddress+52));
	printf("%lu, ",(unsigned long int)*(intDataAddress+53));
	printf("%lu, ",(unsigned long int)*(intDataAddress+54));
	printf("%lu, ",(unsigned long int)*(intDataAddress+55));
	printf("%lu, ",(unsigned long int)*(intDataAddress+56));
	printf("%lu, ",(unsigned long int)*(intDataAddress+57));
	printf("%lu, ",(unsigned long int)*(intDataAddress+58));
	printf("%lu, ",(unsigned long int)*(intDataAddress+59));
	printf("%lu, ",(unsigned long int)*(intDataAddress+60));
	printf("%lu, ",(unsigned long int)*(intDataAddress+61));
	printf("%lu, ",(unsigned long int)*(intDataAddress+62));
	printf("%lu, ",(unsigned long int)*(intDataAddress+63));
	printf("%lu, ",(unsigned long int)*(intDataAddress+64));
	printf("%lu, ",(unsigned long int)*(intDataAddress+65));
	printf("%lu, ",(unsigned long int)*(intDataAddress+66));
	printf("%lu, ",(unsigned long int)*(intDataAddress+67));
	printf("%lu, ",(unsigned long int)*(intDataAddress+68));
	printf("%lu, ",(unsigned long int)*(intDataAddress+69));
	printf("%lu, ",(unsigned long int)*(intDataAddress+70));
	printf("%lu, ",(unsigned long int)*(intDataAddress+71));
	printf("%lu, ",(unsigned long int)*(intDataAddress+72));
	printf("%lu, ",(unsigned long int)*(intDataAddress+73));
	printf("%lu, ",(unsigned long int)*(intDataAddress+74));
	printf("%lu, ",(unsigned long int)*(intDataAddress+75));
	printf("%lu, ",(unsigned long int)*(intDataAddress+76));
	printf("%lu, ",(unsigned long int)*(intDataAddress+77));
	printf("%lu, ",(unsigned long int)*(intDataAddress+78));
	printf("%lu, ",(unsigned long int)*(intDataAddress+79));
	printf("%lu, ",(unsigned long int)*(intDataAddress+80));
	printf("%lu, ",(unsigned long int)*(intDataAddress+81));
	printf("%lu, ",(unsigned long int)*(intDataAddress+82));
	printf("%lu, ",(unsigned long int)*(intDataAddress+83));
	printf("%lu, ",(unsigned long int)*(intDataAddress+84));
	printf("%lu, ",(unsigned long int)*(intDataAddress+85));
	printf("%lu, ",(unsigned long int)*(intDataAddress+86));
	printf("%lu, ",(unsigned long int)*(intDataAddress+87));
	printf("%lu, ",(unsigned long int)*(intDataAddress+88));
	printf("%lu, ",(unsigned long int)*(intDataAddress+89));
	printf("%lu, ",(unsigned long int)*(intDataAddress+90));
	printf("%lu, ",(unsigned long int)*(intDataAddress+91));
	printf("%lu, ",(unsigned long int)*(intDataAddress+92));
	printf("%lu, ",(unsigned long int)*(intDataAddress+93));
	printf("%lu, ",(unsigned long int)*(intDataAddress+94));
	printf("%lu, ",(unsigned long int)*(intDataAddress+95));
	printf("%lu, ",(unsigned long int)*(intDataAddress+96));
	printf("%lu, ",(unsigned long int)*(intDataAddress+97));
	printf("%lu, ",(unsigned long int)*(intDataAddress+98));
	printf("%lu, ",(unsigned long int)*(intDataAddress+99));
	printf("%lu, ",(unsigned long int)*(intDataAddress+100));
	printf("%lu, ",(unsigned long int)*(intDataAddress+101));
	printf("%lu, ",(unsigned long int)*(intDataAddress+102));
	printf("%lu, ",(unsigned long int)*(intDataAddress+103));
	printf("%lu, ",(unsigned long int)*(intDataAddress+104));
	printf("%lu, ",(unsigned long int)*(intDataAddress+105));
	printf("%lu, ",(unsigned long int)*(intDataAddress+106));
	printf("%lu, ",(unsigned long int)*(intDataAddress+107));
	printf("%lu, ",(unsigned long int)*(intDataAddress+108));
	printf("%lu, ",(unsigned long int)*(intDataAddress+109));
	printf("%lu, ",(unsigned long int)*(intDataAddress+110));
	printf("%lu, ",(unsigned long int)*(intDataAddress+111));
	printf("%lu, ",(unsigned long int)*(intDataAddress+112));
	printf("%lu, ",(unsigned long int)*(intDataAddress+113));
	printf("%lu, ",(unsigned long int)*(intDataAddress+114));
	printf("%lu, ",(unsigned long int)*(intDataAddress+115));
	printf("%lu, ",(unsigned long int)*(intDataAddress+116));
	printf("%lu, ",(unsigned long int)*(intDataAddress+117));
	printf("%lu, ",(unsigned long int)*(intDataAddress+118));
	printf("%lu, ",(unsigned long int)*(intDataAddress+119));
	printf("%lu, ",(unsigned long int)*(intDataAddress+120));
	printf("%lu, ",(unsigned long int)*(intDataAddress+121));
	printf("%lu, ",(unsigned long int)*(intDataAddress+122));
	printf("%lu, ",(unsigned long int)*(intDataAddress+123));
	printf("%lu, ",(unsigned long int)*(intDataAddress+124));
	printf("%lu, ",(unsigned long int)*(intDataAddress+125));
	printf("%lu, ",(unsigned long int)*(intDataAddress+126));
	printf("%lu, ",(unsigned long int)*(intDataAddress+127));
	printf("%lu, ",(unsigned long int)*(intDataAddress+128));
	printf("%lu, ",(unsigned long int)*(intDataAddress+129));
	printf("%lu, ",(unsigned long int)*(intDataAddress+130));
	printf("%lu, ",(unsigned long int)*(intDataAddress+131));
	printf("%lu, ",(unsigned long int)*(intDataAddress+132));
	printf("%lu, ",(unsigned long int)*(intDataAddress+133));
	printf("%lu, ",(unsigned long int)*(intDataAddress+134));
	printf("%lu, ",(unsigned long int)*(intDataAddress+135));
	printf("%lu, ",(unsigned long int)*(intDataAddress+136));
	printf("%lu, ",(unsigned long int)*(intDataAddress+137));
	printf("%lu, ",(unsigned long int)*(intDataAddress+138));
	printf("%lu, ",(unsigned long int)*(intDataAddress+139));
	printf("%lu, ",(unsigned long int)*(intDataAddress+140));
	printf("%lu, ",(unsigned long int)*(intDataAddress+141));
	printf("%lu, ",(unsigned long int)*(intDataAddress+142));
	printf("%lu, ",(unsigned long int)*(intDataAddress+143));
	printf("%lu, ",(unsigned long int)*(intDataAddress+144));
	printf("%lu, ",(unsigned long int)*(intDataAddress+145));
	printf("%lu, ",(unsigned long int)*(intDataAddress+146));
	printf("%lu, ",(unsigned long int)*(intDataAddress+147));
	printf("%lu, ",(unsigned long int)*(intDataAddress+148));
	printf("%lu, ",(unsigned long int)*(intDataAddress+149));
	printf("%lu, ",(unsigned long int)*(intDataAddress+150));
	printf("%lu, ",(unsigned long int)*(intDataAddress+151));
	printf("%lu, ",(unsigned long int)*(intDataAddress+152));
	printf("%lu, ",(unsigned long int)*(intDataAddress+153));
	printf("%lu, ",(unsigned long int)*(intDataAddress+154));
	printf("%lu, ",(unsigned long int)*(intDataAddress+155));
	printf("%lu, ",(unsigned long int)*(intDataAddress+156));
	printf("%lu, ",(unsigned long int)*(intDataAddress+157));
	printf("%lu, ",(unsigned long int)*(intDataAddress+158));
	printf("%lu, \n",(unsigned long int)*(intDataAddress+159));

	//output freq test values

	printf("Frequency Histogram: \n");
	printf("%lu, ",(unsigned long int)*(intDataAddress+0));
	printf("%lu, ",(unsigned long int)*(intDataAddress+1));
	printf("%lu, ",(unsigned long int)*(intDataAddress+2));
	printf("%lu, ",(unsigned long int)*(intDataAddress+3));
	printf("%lu, ",(unsigned long int)*(intDataAddress+4));
	printf("%lu, ",(unsigned long int)*(intDataAddress+5));
	printf("%lu, ",(unsigned long int)*(intDataAddress+6));
	printf("%lu, ",(unsigned long int)*(intDataAddress+7));
	printf("%lu, ",(unsigned long int)*(intDataAddress+8));
	printf("%lu, ",(unsigned long int)*(intDataAddress+9));
	printf("%lu, ",(unsigned long int)*(intDataAddress+10));
	printf("%lu, ",(unsigned long int)*(intDataAddress+11));
	printf("%lu, ",(unsigned long int)*(intDataAddress+12));
	printf("%lu, ",(unsigned long int)*(intDataAddress+13));
	printf("%lu, ",(unsigned long int)*(intDataAddress+14));
	printf("%lu, ",(unsigned long int)*(intDataAddress+15));
	printf("%lu, ",(unsigned long int)*(intDataAddress+16));
	printf("%lu, ",(unsigned long int)*(intDataAddress+17));
	printf("%lu, ",(unsigned long int)*(intDataAddress+18));
	printf("%lu, ",(unsigned long int)*(intDataAddress+19));
	printf("%lu, ",(unsigned long int)*(intDataAddress+20));
	printf("%lu, ",(unsigned long int)*(intDataAddress+21));
	printf("%lu, ",(unsigned long int)*(intDataAddress+22));
	printf("%lu, ",(unsigned long int)*(intDataAddress+23));
	printf("%lu, ",(unsigned long int)*(intDataAddress+24));
	printf("%lu, ",(unsigned long int)*(intDataAddress+25));
	printf("%lu, ",(unsigned long int)*(intDataAddress+26));
	printf("%lu, ",(unsigned long int)*(intDataAddress+27));
	printf("%lu, ",(unsigned long int)*(intDataAddress+28));
	printf("%lu, ",(unsigned long int)*(intDataAddress+29));
	printf("%lu, ",(unsigned long int)*(intDataAddress+30));
	printf("%lu, \n",(unsigned long int)*(intDataAddress+31));

	printf("Test Finished. Goodbye.");

	//finish frequency

	//call the software version of the function

	/*
	for(int j=0; j<32; j++){
		printf("Bit %d: Observed: %d. Expected: %d",j,(int)freq_test_stream[j],(int)freq_expected[j]);
	}

	if (res_hw == res_sw) {
		print("*** Results match ***\n\r");
		status = 0;
	} else {
		print("!!! MISMATCH !!!\n\r");
		status = -1;
	}
	*/
	cleanup_platform();
	return 0;
}
