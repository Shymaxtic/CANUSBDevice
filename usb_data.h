/*
 * usb_can_data.h
 *
 *  Created on: Oct 1, 2019
 *      Author: quynhpp
 */

#ifndef USB_CAN_DATA_H_
#define USB_CAN_DATA_H_


#define D_USB_PACKET_MAX_LEN        64  // equal sizeof endpoint

// usb packet type from host.
typedef enum {
    E_USB_CAN_PING = 0,
    E_USB_CAN_GET_BAUDRATE,
    E_USB_CAN_GET_CAN_FRAME
} usb_can_packet_type_t;

/*
  Info of chunk of can frames sent via usb.
 | Frame num  (1 byte) |[| ID (4 bytes) | info (1 byte) | data (8 bytes) |...]
*/
typedef struct {
    uint32_t     u32id;
    uint8_t      u8info;
    uint8_t      au8data[8];
} __attribute__ ((packed)) usb_can_frame_info_t;

#define D_USB_PACKET_DATA_LEN       (D_USB_PACKET_MAX_LEN - sizeof(uint8_t))

// data packet for my usb. maximum is equal 64 byte endpoint of TM4C123GH6PGE
typedef struct usb_can_packet_t {
    uint8_t u8type;
    uint8_t au8data[D_USB_PACKET_DATA_LEN];
}   __attribute__ ((packed)) usb_can_packet_t;


#endif /* USB_CAN_DATA_H_ */
