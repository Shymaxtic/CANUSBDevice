#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "usblib/usblib.h"
#include "usblib/usb-ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdbulk.h"
#include "utils/uartstdio.h"
#include "utils/ustdlib.h"
#include <string.h>
#include "utils.h"
#include "device_status.h"
#include "usb_implementation.h"
#include <stdio.h>

// The system tick rate expressed both as ticks per second and a millisecond period.
#define SYSTICKS_PER_SECOND 100
#define SYSTICK_PERIOD_MS (1000 / SYSTICKS_PER_SECOND)

// The global system tick counter.
volatile uint32_t g_ui32SysTickCount = 0;

// Interrupt handler for the system tick counter.
void SysTickIntHandler(void) {
    // Update our system tick counter.
    g_ui32SysTickCount++;
}

// Receiving handler for USB
uint32_t USBTxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData) {
    sprintf(g_pcStatus, "Tx Event: %d\n", ui32Event);
    g_ui32StatusFlags |= STATUS_UPDATE;
    return(0);
}

// Reading handler for USB
uint32_t USBRxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue, void *pvMsgData) {
    // which event from host?
    switch (ui32Event){
    // host connected.
    case USB_EVENT_CONNECTED: {
        memset(g_pcStatus, 0, sizeof(g_pcStatus));
        strcpy(g_pcStatus, "Connected\n");
        g_ui32StatusFlags |= STATUS_UPDATE;
    }
    break;
    // host disconnect.
    case USB_EVENT_DISCONNECTED: {
        memset(g_pcStatus, 0, sizeof(g_pcStatus));
        strcpy(g_pcStatus, "Disconnected\n");
        g_ui32StatusFlags |= STATUS_UPDATE;
    }
    break;
    // host send data.
    case USB_EVENT_RX_AVAILABLE: {
        // TODO: read data.
    }
    break;
    case USB_EVENT_SUSPEND:
    case USB_EVENT_RESUME:
    break;
    default:
        break;
    }
    return(0);
}

/**
 * main.c
 */
int main(void) {
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    ROM_FPULazyStackingEnable();

    // Set the clocking to run from the PLL at 50MHz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                      SYSCTL_XTAL_16MHZ);

#ifdef DEBUG
    // Configure the UART for debug output.
    ConfigureUART();
#endif

    // Enable the system tick.
    ROM_SysTickPeriodSet(ROM_SysCtlClockGet() / SYSTICKS_PER_SECOND);
    ROM_SysTickIntEnable();
    ROM_SysTickEnable();
    
    DEBUG_PRINT("\nTiva C Series USB bulk device example\n");
    DEBUG_PRINT("---------------------------------\n\n");

    // Initialize USB bulk device.
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);
    USBDBulkInit(0, &g_sBulkDevice);

    while(1) {
        if (g_ui32StatusFlags & STATUS_UPDATE) {
            ShowStatus(g_pcStatus);

            // Clear the flags.
            g_ui32StatusFlags &= ~STATUS_UPDATE;
        }
    }
}
