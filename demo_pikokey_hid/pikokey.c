#include "ch32fun.h"
#include <stdio.h>
#include <string.h>
#include "rv003usb.h"
#include "help_functions.h"
// ./minichlink -D to use nrst, also PD1 needs pullup 

const uint8_t ncols = 6;
const uint8_t cols[] = {
  PC1,
  PC2,
  PC0,
  PC3,
  PD1,
  PC5,
};
const uint8_t cols_port[] = {
  GPIO_port_C,
  GPIO_port_C,
  GPIO_port_C,
  GPIO_port_C,
  GPIO_port_D,
  GPIO_port_C,
};
const uint8_t cols_pin[] = {
  1,
  2,
  0,
  3,
  1,
  5,
};

const uint8_t nrows = 4;
const uint8_t rows[] = {
  PC6,
  PC7,
  PD0,
  PA2,
};
const uint8_t rows_port[] = {
  GPIO_port_C,
  GPIO_port_C,
  GPIO_port_D,
  GPIO_port_A,
};
const uint8_t rows_pin[] = {
  6,
  7,
  0,
  2,
};

char queue[10];
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

  GPIO_port_enable(GPIO_port_A);
  GPIO_port_enable(GPIO_port_C);
  GPIO_port_enable(GPIO_port_D);
  // funGpioInitAll();
  for (int i=0;i<nrows;i++){
    GPIO_pinMode(
        GPIOv_from_PORT_PIN(rows_port[i], rows_pin[i]),
        GPIO_pinMode_I_pullUp, GPIO_Speed_In);
    // funPinMode(rows[i], GPIO_CFGLR_IN_PUPD);
    // funDigitalWrite(rows[i], FUN_HIGH);
  }
  for (int i=0;i<ncols;i++){
    GPIO_pinMode(
        GPIOv_from_PORT_PIN(cols_port[i], cols_pin[i]),
        GPIO_pinMode_I_pullUp, GPIO_Speed_In);
    // funPinMode(cols[i], GPIO_CFGLR_IN_PUPD);
    // funDigitalWrite(cols[i], FUN_HIGH);
  }

  usb_setup();

  while(1){
    Delay_Ms(100);
    for (int i=0;i<nrows;i++){
      GPIO_pinMode(
          GPIOv_from_PORT_PIN(rows_port[i], rows_pin[i]),
          GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
      GPIO_digitalWrite(
          GPIOv_from_PORT_PIN(rows_port[i], rows_pin[i]),
          low);
      // funPinMode(rows[i], GPIO_CFGLR_OUT_10Mhz_PP);
      // funDigitalWrite(rows[i], FUN_LOW);
      Delay_Us(1);
      for (int j=0;j<ncols;j++){
        if (!GPIO_digitalRead(
              GPIOv_from_PORT_PIN(
                cols_port[j], cols_pin[j]))) {
        // if (funDigitalRead(cols[j]) == FUN_LOW) {
          queue[0] = HID_KEY_0;
          queue[1] = i2k[i];
          queue[2] = i2k[j];
          queue[3] = HID_KEY_SPACE;
          queue[4] = 0;
          qp=0;
        }
      }
      GPIO_pinMode(
          GPIOv_from_PORT_PIN(rows_port[i], rows_pin[i]),
          GPIO_pinMode_I_pullUp, GPIO_Speed_In);
      // funPinMode(rows[i], GPIO_CFGLR_IN_PUPD);
      // funDigitalWrite(rows[i], FUN_HIGH);
    }
    for (int i=0;i<ncols;i++){
      GPIO_pinMode(
          GPIOv_from_PORT_PIN(cols_port[i], cols_pin[i]),
          GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
      GPIO_digitalWrite(
          GPIOv_from_PORT_PIN(cols_port[i], cols_pin[i]),
          low);
      // funPinMode(cols[i], GPIO_CFGLR_OUT_10Mhz_PP);
      // funDigitalWrite(cols[i], FUN_LOW);
      Delay_Us(1);
      for (int j=0;j<nrows;j++){
        if (!GPIO_digitalRead(
              GPIOv_from_PORT_PIN(
                rows_port[j], rows_pin[j]))) {
        // if (funDigitalRead(rows[j]) == FUN_LOW) {
          queue[0] = HID_KEY_1;
          queue[1] = i2k[i];
          queue[2] = i2k[j];
          queue[3] = HID_KEY_SPACE;
          queue[4] = 0;
          qp=0;
        }
      }
      GPIO_pinMode(
          GPIOv_from_PORT_PIN(cols_port[i], cols_pin[i]),
          GPIO_pinMode_I_pullUp, GPIO_Speed_In);
      // funPinMode(cols[i], GPIO_CFGLR_IN_PUPD);
      // funDigitalWrite(cols[i], FUN_HIGH);
    }
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


