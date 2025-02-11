#include "ch32fun.h"
#include <stdio.h>
#include <string.h>
#include "rv003usb.h"
#include "help_functions.h"
// ./minichlink -D to use nrst, also PD1 needs pullup 


volatile char queue[10];
volatile int qp = 0;
const unsigned char i2k[] = {
  HID_KEY_0, 
  HID_KEY_1, 
  HID_KEY_2, 
  HID_KEY_3, 
  HID_KEY_4, 
  HID_KEY_5, 
  HID_KEY_6, 
  HID_KEY_7, 
  HID_KEY_8, 
  HID_KEY_9, 
  HID_KEY_A, 
  HID_KEY_B, 
  HID_KEY_C, 
  HID_KEY_D, 
  HID_KEY_E, 
  HID_KEY_F, 
};

int main()
{
  SystemInit();
  Delay_Ms(1); // Ensures USB re-enumeration after bootloader or reset; Spec demand >2.5µs ( TDDIS )
  systick_init();

  funGpioInitAll();
  funPinMode(PD1, GPIO_CFGLR_IN_PUPD);
  funDigitalWrite(PD1, FUN_HIGH);
  funPinMode(PC7, GPIO_CFGLR_IN_PUPD);
  funDigitalWrite(PC7, FUN_HIGH);

  usb_setup();

  while(1){
    Delay_Ms(100);
    funPinMode(PD1, GPIO_CFGLR_OUT_10Mhz_PP);
    funDigitalWrite(PD1, FUN_LOW);
    Delay_Ms(100);
    if (funDigitalRead(PC7) == FUN_LOW) {
          queue[0] = HID_KEY_1;
          queue[1] = i2k[3];
          queue[2] = i2k[3];
          queue[3] = HID_KEY_SPACE;
          queue[4] = 0;
          qp=0;
    }
    funPinMode(PD1, GPIO_CFGLR_IN_PUPD);
    funDigitalWrite(PD1, FUN_HIGH);
  }
}

void usb_handle_user_in_request( struct usb_endpoint * e, uint8_t * scratchpad, int endp, uint32_t sendtok, struct rv003usb_internal * ist )
{
  if( endp == 1 )
  {
    uint8_t key_report[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
    if (qp%2 == 0) {
      key_report[2] = queue[qp/2];
    }
    usb_send_data( key_report, 8, 0, sendtok );
    if (queue[qp/2] != 0) {
      qp++;
    }
  }
  else
  {
    usb_send_empty( sendtok );
  }
}


