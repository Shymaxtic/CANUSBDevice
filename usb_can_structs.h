#ifndef _USB_CAN_STRUCTS_H_
#define _USB_CAN_STRUCTS_H_

#include <stdint.h>
#include <stdbool.h>
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdbulk.h"

// Struct for bulk device

// should be at least twice the size of a maximum-sized USB packet.
#define BULK_BUFFER_SIZE 512

extern uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void* pvMsgData);
extern uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void* pvMsgData);

extern tUSBBuffer g_sTxBuffer;
extern tUSBBuffer g_sRxBuffer;
extern uint8_t g_pui8USBTxBuffer[];
extern uint8_t g_pui8USBRxBuffer[];
extern tUSBDBulkDevice g_sBulkDevice;
#endif
