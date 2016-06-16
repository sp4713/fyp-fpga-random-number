// ==============================================================
// File generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2016.1
// Copyright (C) 1986-2016 Xilinx, Inc. All Rights Reserved.
// 
// ==============================================================

#ifndef XFREQ_SERIAL_H
#define XFREQ_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xfreq_serial_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Freq_periph_bus_BaseAddress;
} XFreq_serial_Config;
#endif

typedef struct {
    u32 Freq_periph_bus_BaseAddress;
    u32 IsReady;
} XFreq_serial;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFreq_serial_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFreq_serial_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFreq_serial_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFreq_serial_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XFreq_serial_Initialize(XFreq_serial *InstancePtr, u16 DeviceId);
XFreq_serial_Config* XFreq_serial_LookupConfig(u16 DeviceId);
int XFreq_serial_CfgInitialize(XFreq_serial *InstancePtr, XFreq_serial_Config *ConfigPtr);
#else
int XFreq_serial_Initialize(XFreq_serial *InstancePtr, const char* InstanceName);
int XFreq_serial_Release(XFreq_serial *InstancePtr);
#endif

void XFreq_serial_Start(XFreq_serial *InstancePtr);
u32 XFreq_serial_IsDone(XFreq_serial *InstancePtr);
u32 XFreq_serial_IsIdle(XFreq_serial *InstancePtr);
u32 XFreq_serial_IsReady(XFreq_serial *InstancePtr);
void XFreq_serial_EnableAutoRestart(XFreq_serial *InstancePtr);
void XFreq_serial_DisableAutoRestart(XFreq_serial *InstancePtr);

void XFreq_serial_Set_seed_V(XFreq_serial *InstancePtr, u32 Data);
u32 XFreq_serial_Get_seed_V(XFreq_serial *InstancePtr);
void XFreq_serial_Set_n_V(XFreq_serial *InstancePtr, u64 Data);
u64 XFreq_serial_Get_n_V(XFreq_serial *InstancePtr);
void XFreq_serial_Set_offset_V(XFreq_serial *InstancePtr, u32 Data);
u32 XFreq_serial_Get_offset_V(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_freqStream_V_BaseAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_freqStream_V_HighAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_freqStream_V_TotalBytes(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_freqStream_V_BitWidth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_freqStream_V_Depth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Write_freqStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Read_freqStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Write_freqStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);
u32 XFreq_serial_Read_freqStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);
u32 XFreq_serial_Get_serialTwoStream_V_BaseAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialTwoStream_V_HighAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialTwoStream_V_TotalBytes(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialTwoStream_V_BitWidth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialTwoStream_V_Depth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Write_serialTwoStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Read_serialTwoStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Write_serialTwoStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);
u32 XFreq_serial_Read_serialTwoStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);
u32 XFreq_serial_Get_serialThreeStream_V_BaseAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialThreeStream_V_HighAddress(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialThreeStream_V_TotalBytes(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialThreeStream_V_BitWidth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Get_serialThreeStream_V_Depth(XFreq_serial *InstancePtr);
u32 XFreq_serial_Write_serialThreeStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Read_serialThreeStream_V_Words(XFreq_serial *InstancePtr, int offset, int *data, int length);
u32 XFreq_serial_Write_serialThreeStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);
u32 XFreq_serial_Read_serialThreeStream_V_Bytes(XFreq_serial *InstancePtr, int offset, char *data, int length);

void XFreq_serial_InterruptGlobalEnable(XFreq_serial *InstancePtr);
void XFreq_serial_InterruptGlobalDisable(XFreq_serial *InstancePtr);
void XFreq_serial_InterruptEnable(XFreq_serial *InstancePtr, u32 Mask);
void XFreq_serial_InterruptDisable(XFreq_serial *InstancePtr, u32 Mask);
void XFreq_serial_InterruptClear(XFreq_serial *InstancePtr, u32 Mask);
u32 XFreq_serial_InterruptGetEnabled(XFreq_serial *InstancePtr);
u32 XFreq_serial_InterruptGetStatus(XFreq_serial *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
