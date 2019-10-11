#include "usb_can_structs.h"
#include "usblib/usblib.h"
#include "usblib/usb-ids.h"

// Languages supported by this device.
const uint8_t g_pui8LangDescriptor[] = {
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

// The manufacturer string.
const uint8_t g_pui8ManufacturerString[] = {
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0, 's', 0,
    't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0, 's', 0,
};

// The product string.
const uint8_t g_pui8ProductString[] = {
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'G', 0, 'e', 0, 'n', 0, 'e', 0, 'r', 0, 'i', 0, 'c', 0, ' ', 0, 'B', 0,
    'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0,
    'e', 0
};

// The serial number string.
const uint8_t g_pui8SerialNumberString[] = {
    (8 + 1) * 2,
    USB_DTYPE_STRING,
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0
};

// The data interface description string.
const uint8_t g_pui8DataInterfaceString[] = {
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'B', 0, 'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'a', 0, 't', 0,
    'a', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0,
    'a', 0, 'c', 0, 'e', 0
};

// The configuration description string.
const uint8_t g_pui8ConfigString[] = {
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'B', 0, 'u', 0, 'l', 0, 'k', 0, ' ', 0, 'D', 0, 'a', 0, 't', 0,
    'a', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0, 'g', 0,
    'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0    
};

// The description string table.
const uint8_t* const g_ppui8StringDescriptors[] = {
    g_pui8LangDescriptor,
    g_pui8ManufacturerString,
    g_pui8ProductString,
    g_pui8SerialNumberString,
    g_pui8DataInterfaceString,
    g_pui8ConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_ppui8StringDescriptors) / \
                                sizeof(uint8_t*))



// Init bulk device.
tUSBDBulkDevice g_sBulkDevice = {
    .ui16VID                    = USB_VID_TI_1CBE,
    .ui16PID                    = USB_PID_BULK,
    .ui16MaxPowermA             = 500,
    .ui8PwrAttributes           = USB_CONF_ATTR_SELF_PWR,
    .pfnRxCallback              = USBBufferEventCallback,
    .pvRxCBData                 = (void *)&g_sRxBuffer,
    .pfnTxCallback              = USBBufferEventCallback,
    .pvTxCBData                 = (void *)&g_sTxBuffer,
    .ppui8StringDescriptors     = g_ppui8StringDescriptors,
    .ui32NumStringDescriptors   = NUM_STRING_DESCRIPTORS
};

// Receive buffer for USB
uint8_t g_pui8USBRxBuffer[BULK_BUFFER_SIZE];
tUSBBuffer g_sRxBuffer = {
    .bTransmitBuffer    = false,
    .pfnCallback        = RxHandler,
    .pvCBData           = (void *)&g_sBulkDevice,
    .pfnTransfer        = USBDBulkPacketRead,
    .pfnAvailable       = USBDBulkRxPacketAvailable,
    .pvHandle           = (void *)&g_sBulkDevice,
    .pui8Buffer         = g_pui8USBRxBuffer,
    .ui32BufferSize     = BULK_BUFFER_SIZE
};

// Transmit buffer for USB
uint8_t g_pui8USBTxBuffer[BULK_BUFFER_SIZE];
tUSBBuffer g_sTxBuffer = {
    .bTransmitBuffer    = true,
    .pfnCallback        = TxHandler,
    .pvCBData           = (void *)&g_sBulkDevice,
    .pfnTransfer        = USBDBulkPacketWrite,
    .pfnAvailable       = USBDBulkTxPacketAvailable,
    .pvHandle           = (void *)&g_sBulkDevice,
    .pui8Buffer         = g_pui8USBTxBuffer,
    .ui32BufferSize     = BULK_BUFFER_SIZE
};

extern uint32_t RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void* pvMsgData) {
    
}
extern uint32_t TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void* pvMsgData) {

}
