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

#include <stdio.h>
#include "platform.h"
#include <stdlib.h> // Standard C functions, e.g. exit()
#include <stdbool.h> // Provides a Boolean data type for ANSI/ISO-C
#include "xparameters.h" // Parameter definitions for processor peripherals
#include "xscugic.h" // Processor interrupt controller device driver
#include "xfreq_serial.h" // Device driver for HLS HW block

// Test parameters
int n_input = 10000000;
int seed_input = 0;

// Freq Serial HW instance
XFreq_serial FreqSerial;

// Address Pointers for test outputs
char *serialcharDataAddress;
char *freqcharDataAddress;
int *serialintDataAddress;
int *freqintDataAddress;
int serialchardebug_value;
int serialintdebug_value;

int freqchardebug_value;
int freqintdebug_value;

int someValue = 0;

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
/*
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
	print("Begin test of communication with Serial Freq peripheral in PL\n\r");

	//hw variables
	int freq_base_address_hw, freq_high_address_hw, freq_total_bytes_hw,
			freq_bit_width_hw, freq_depth_hw;
	int serial_base_address_hw, serial_high_address_hw, serial_total_bytes_hw,
			serial_bit_width_hw, serial_depth_hw;

/*	//sw variables
	int sw_freq_base_address_hw, sw_freq_high_address_hw, sw_freq_total_bytes_hw,
			sw_freq_bit_width_hw, sw_freq_depth_hw;
	int sw_serial_base_address_hw, sw_serial_high_address_hw, sw_serial_total_bytes_hw,
			sw_serial_bit_width_hw, sw_serial_depth_hw;
*/

	//int i;
	int status;
//Setup the matrix mult
	status = XFreq_serial_init(&FreqSerial);
	if (status != XST_SUCCESS) {
		print("HLS peripheral setup failed\n\r");
		exit(-1);
	}
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
		print("Freq Serial peripheral is ready. Starting...\n\r");
	else {
		print("!!! HLS peripheral is not ready! Exiting...\n\r");
		exit(-1);
	}
	// Simple non-interrupt driven test
	XFreq_serial_Start(&FreqSerial);
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
		serialchardebug_value = XFreq_serial_Read_serialStream_V_Bytes(&FreqSerial, 0, freqcharDataAddress+128, 512);
		serialintdebug_value = XFreq_serial_Read_serialStream_V_Words(&FreqSerial, 0, freqintDataAddress+32, 128);

		//get freq test values
		freqchardebug_value = XFreq_serial_Read_freqStream_V_Bytes(&FreqSerial, 0, freqcharDataAddress, 128);
		freqintdebug_value = XFreq_serial_Read_freqStream_V_Words(&FreqSerial, 0, freqintDataAddress, 32);


	} while (!XFreq_serial_IsReady(&FreqSerial));

	//test feedback to user
	printf("Sample Size: %d\n\r", n_input);
	printf("Seed: %d\n\r", seed_input);

/*
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

*/

	//output serial test values
	printf("Serial Histogram: \n");
	printf("%d, ",(int)*(freqintDataAddress+32));
	printf("%d, ",(int)*(freqintDataAddress+33));
	printf("%d, ",(int)*(freqintDataAddress+34));
	printf("%d, ",(int)*(freqintDataAddress+35));
	printf("%d, ",(int)*(freqintDataAddress+36));
	printf("%d, ",(int)*(freqintDataAddress+37));
	printf("%d, ",(int)*(freqintDataAddress+38));
	printf("%d, ",(int)*(freqintDataAddress+39));
	printf("%d, ",(int)*(freqintDataAddress+40));
	printf("%d, ",(int)*(freqintDataAddress+41));
	printf("%d, ",(int)*(freqintDataAddress+42));
	printf("%d, ",(int)*(freqintDataAddress+43));
	printf("%d, ",(int)*(freqintDataAddress+44));
	printf("%d, ",(int)*(freqintDataAddress+45));
	printf("%d, ",(int)*(freqintDataAddress+46));
	printf("%d, ",(int)*(freqintDataAddress+47));
	printf("%d, ",(int)*(freqintDataAddress+48));
	printf("%d, ",(int)*(freqintDataAddress+49));
	printf("%d, ",(int)*(freqintDataAddress+50));
	printf("%d, ",(int)*(freqintDataAddress+51));
	printf("%d, ",(int)*(freqintDataAddress+52));
	printf("%d, ",(int)*(freqintDataAddress+53));
	printf("%d, ",(int)*(freqintDataAddress+54));
	printf("%d, ",(int)*(freqintDataAddress+55));
	printf("%d, ",(int)*(freqintDataAddress+56));
	printf("%d, ",(int)*(freqintDataAddress+57));
	printf("%d, ",(int)*(freqintDataAddress+58));
	printf("%d, ",(int)*(freqintDataAddress+59));
	printf("%d, ",(int)*(freqintDataAddress+60));
	printf("%d, ",(int)*(freqintDataAddress+61));
	printf("%d, ",(int)*(freqintDataAddress+62));
	printf("%d, ",(int)*(freqintDataAddress+63));
	printf("%d, ",(int)*(freqintDataAddress+64));
	printf("%d, ",(int)*(freqintDataAddress+65));
	printf("%d, ",(int)*(freqintDataAddress+66));
	printf("%d, ",(int)*(freqintDataAddress+67));
	printf("%d, ",(int)*(freqintDataAddress+68));
	printf("%d, ",(int)*(freqintDataAddress+69));
	printf("%d, ",(int)*(freqintDataAddress+70));
	printf("%d, ",(int)*(freqintDataAddress+71));
	printf("%d, ",(int)*(freqintDataAddress+72));
	printf("%d, ",(int)*(freqintDataAddress+73));
	printf("%d, ",(int)*(freqintDataAddress+74));
	printf("%d, ",(int)*(freqintDataAddress+75));
	printf("%d, ",(int)*(freqintDataAddress+76));
	printf("%d, ",(int)*(freqintDataAddress+77));
	printf("%d, ",(int)*(freqintDataAddress+78));
	printf("%d, ",(int)*(freqintDataAddress+79));
	printf("%d, ",(int)*(freqintDataAddress+80));
	printf("%d, ",(int)*(freqintDataAddress+81));
	printf("%d, ",(int)*(freqintDataAddress+82));
	printf("%d, ",(int)*(freqintDataAddress+83));
	printf("%d, ",(int)*(freqintDataAddress+84));
	printf("%d, ",(int)*(freqintDataAddress+85));
	printf("%d, ",(int)*(freqintDataAddress+86));
	printf("%d, ",(int)*(freqintDataAddress+87));
	printf("%d, ",(int)*(freqintDataAddress+88));
	printf("%d, ",(int)*(freqintDataAddress+89));
	printf("%d, ",(int)*(freqintDataAddress+90));
	printf("%d, ",(int)*(freqintDataAddress+91));
	printf("%d, ",(int)*(freqintDataAddress+92));
	printf("%d, ",(int)*(freqintDataAddress+93));
	printf("%d, ",(int)*(freqintDataAddress+94));
	printf("%d, ",(int)*(freqintDataAddress+95));
	printf("%d, ",(int)*(freqintDataAddress+96));
	printf("%d, ",(int)*(freqintDataAddress+97));
	printf("%d, ",(int)*(freqintDataAddress+98));
	printf("%d, ",(int)*(freqintDataAddress+99));
	printf("%d, ",(int)*(freqintDataAddress+100));
	printf("%d, ",(int)*(freqintDataAddress+101));
	printf("%d, ",(int)*(freqintDataAddress+102));
	printf("%d, ",(int)*(freqintDataAddress+103));
	printf("%d, ",(int)*(freqintDataAddress+104));
	printf("%d, ",(int)*(freqintDataAddress+105));
	printf("%d, ",(int)*(freqintDataAddress+106));
	printf("%d, ",(int)*(freqintDataAddress+107));
	printf("%d, ",(int)*(freqintDataAddress+108));
	printf("%d, ",(int)*(freqintDataAddress+109));
	printf("%d, ",(int)*(freqintDataAddress+110));
	printf("%d, ",(int)*(freqintDataAddress+111));
	printf("%d, ",(int)*(freqintDataAddress+112));
	printf("%d, ",(int)*(freqintDataAddress+113));
	printf("%d, ",(int)*(freqintDataAddress+114));
	printf("%d, ",(int)*(freqintDataAddress+115));
	printf("%d, ",(int)*(freqintDataAddress+116));
	printf("%d, ",(int)*(freqintDataAddress+117));
	printf("%d, ",(int)*(freqintDataAddress+118));
	printf("%d, ",(int)*(freqintDataAddress+119));
	printf("%d, ",(int)*(freqintDataAddress+120));
	printf("%d, ",(int)*(freqintDataAddress+121));
	printf("%d, ",(int)*(freqintDataAddress+122));
	printf("%d, ",(int)*(freqintDataAddress+123));
	printf("%d, ",(int)*(freqintDataAddress+124));
	printf("%d, ",(int)*(freqintDataAddress+125));
	printf("%d, ",(int)*(freqintDataAddress+126));
	printf("%d, ",(int)*(freqintDataAddress+127));
	printf("%d, ",(int)*(freqintDataAddress+128));
	printf("%d, ",(int)*(freqintDataAddress+129));
	printf("%d, ",(int)*(freqintDataAddress+130));
	printf("%d, ",(int)*(freqintDataAddress+131));
	printf("%d, ",(int)*(freqintDataAddress+132));
	printf("%d, ",(int)*(freqintDataAddress+133));
	printf("%d, ",(int)*(freqintDataAddress+134));
	printf("%d, ",(int)*(freqintDataAddress+135));
	printf("%d, ",(int)*(freqintDataAddress+136));
	printf("%d, ",(int)*(freqintDataAddress+137));
	printf("%d, ",(int)*(freqintDataAddress+138));
	printf("%d, ",(int)*(freqintDataAddress+139));
	printf("%d, ",(int)*(freqintDataAddress+140));
	printf("%d, ",(int)*(freqintDataAddress+141));
	printf("%d, ",(int)*(freqintDataAddress+142));
	printf("%d, ",(int)*(freqintDataAddress+143));
	printf("%d, ",(int)*(freqintDataAddress+144));
	printf("%d, ",(int)*(freqintDataAddress+145));
	printf("%d, ",(int)*(freqintDataAddress+146));
	printf("%d, ",(int)*(freqintDataAddress+147));
	printf("%d, ",(int)*(freqintDataAddress+148));
	printf("%d, ",(int)*(freqintDataAddress+149));
	printf("%d, ",(int)*(freqintDataAddress+150));
	printf("%d, ",(int)*(freqintDataAddress+151));
	printf("%d, ",(int)*(freqintDataAddress+152));
	printf("%d, ",(int)*(freqintDataAddress+153));
	printf("%d, ",(int)*(freqintDataAddress+154));
	printf("%d, ",(int)*(freqintDataAddress+155));
	printf("%d, ",(int)*(freqintDataAddress+156));
	printf("%d, ",(int)*(freqintDataAddress+157));
	printf("%d, ",(int)*(freqintDataAddress+158));
	printf("%d, \n",(int)*(freqintDataAddress+159));

	//output freq test values

	printf("Frequency Histogram: \n");
	printf("%d, ",(int)*(freqintDataAddress+0));
	printf("%d, ",(int)*(freqintDataAddress+1));
	printf("%d, ",(int)*(freqintDataAddress+2));
	printf("%d, ",(int)*(freqintDataAddress+3));
	printf("%d, ",(int)*(freqintDataAddress+4));
	printf("%d, ",(int)*(freqintDataAddress+5));
	printf("%d, ",(int)*(freqintDataAddress+6));
	printf("%d, ",(int)*(freqintDataAddress+7));
	printf("%d, ",(int)*(freqintDataAddress+8));
	printf("%d, ",(int)*(freqintDataAddress+9));
	printf("%d, ",(int)*(freqintDataAddress+10));
	printf("%d, ",(int)*(freqintDataAddress+11));
	printf("%d, ",(int)*(freqintDataAddress+12));
	printf("%d, ",(int)*(freqintDataAddress+13));
	printf("%d, ",(int)*(freqintDataAddress+14));
	printf("%d, ",(int)*(freqintDataAddress+15));
	printf("%d, ",(int)*(freqintDataAddress+16));
	printf("%d, ",(int)*(freqintDataAddress+17));
	printf("%d, ",(int)*(freqintDataAddress+18));
	printf("%d, ",(int)*(freqintDataAddress+19));
	printf("%d, ",(int)*(freqintDataAddress+20));
	printf("%d, ",(int)*(freqintDataAddress+21));
	printf("%d, ",(int)*(freqintDataAddress+22));
	printf("%d, ",(int)*(freqintDataAddress+23));
	printf("%d, ",(int)*(freqintDataAddress+24));
	printf("%d, ",(int)*(freqintDataAddress+25));
	printf("%d, ",(int)*(freqintDataAddress+26));
	printf("%d, ",(int)*(freqintDataAddress+27));
	printf("%d, ",(int)*(freqintDataAddress+28));
	printf("%d, ",(int)*(freqintDataAddress+29));
	printf("%d, ",(int)*(freqintDataAddress+30));
	printf("%d, \n",(int)*(freqintDataAddress+31));

	printf("Test Finished. Goodbye.");

	//finish frequency

	//call the software version of the function

	/*
	for(int j=0; j<32; j++){
		printf("Bit %d: Observed: %d. Expected: %d",j,(int)freq_test_stream[j],(int)freq_expected[j]);
	}
	*/

	/*
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
