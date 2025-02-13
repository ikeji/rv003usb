// (lazy-make-configulation
//   (task "default" ()
//     "make"))

#include "ch32fun.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "rv003usb.h"
#include "help_functions.h"
#include "generate_report.h"
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

const uint8_t nrows = 4;
const uint8_t rows[] = {
  PC6,
  PC7,
  PD0,
  PA2,
};

uint32_t lastChangeTime = 0;
volatile uint8_t key_report[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

void scan_matrix() {
  uint32_t now = GetSystemTime();
  bool leaped = now < lastChangeTime;
  bool debunceTime = lastChangeTime + 10 > now;
  if (!leaped && debunceTime) return;

  bool changed = false;
  for (int i=0;i<nrows;i++){
    funPinMode(rows[i], GPIO_CFGLR_OUT_10Mhz_PP);
    funDigitalWrite(rows[i], FUN_LOW);
    Delay_Us(1);
    for (int j=0;j<ncols;j++){
      bool state = funDigitalRead(cols[j]) == FUN_LOW;
      if (state != matrix[i][j]) changed = true;
      matrix[i][j] = state;
    }
    funPinMode(rows[i], GPIO_CFGLR_IN_PUPD);
    funDigitalWrite(rows[i], FUN_HIGH);
  }
  for (int i=0;i<ncols;i++){
    funPinMode(cols[i], GPIO_CFGLR_OUT_10Mhz_PP);
    funDigitalWrite(cols[i], FUN_LOW);
    Delay_Us(1);
    for (int j=0;j<nrows;j++){
      bool state = funDigitalRead(rows[j]) == FUN_LOW;
      if (state != matrix[j][11-i]) changed = true;
      matrix[j][11-i] = state;
    }
    funPinMode(cols[i], GPIO_CFGLR_IN_PUPD);
    funDigitalWrite(cols[i], FUN_HIGH);
  }
  if (changed) {
    lastChangeTime = now;
  }
}

int main()
{
  SystemInit();
  Delay_Ms(1); // Ensures USB re-enumeration after bootloader or reset; Spec demand >2.5µs ( TDDIS )
  systick_init();

  // Enable GPIOs
  RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_AFIOEN;
  // Convert PD1 from SWIO to GPIO
  AFIO->PCFR1 &= ~(AFIO_PCFR1_SWJ_CFG);
  AFIO->PCFR1 |= AFIO_PCFR1_SWJ_CFG_DISABLE;

  funGpioInitAll();
  for (int i=0;i<nrows;i++){
    funPinMode(rows[i], GPIO_CFGLR_IN_PUPD);
    funDigitalWrite(rows[i], FUN_HIGH);
  }
  for (int i=0;i<ncols;i++){
    funPinMode(cols[i], GPIO_CFGLR_IN_PUPD);
    funDigitalWrite(cols[i], FUN_HIGH);
  }

  usb_setup();

  while(1){
    scan_matrix();
    generate_report();
  }
}

uint8_t previous_report[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

void usb_handle_user_in_request( struct usb_endpoint * e, uint8_t * scratchpad, int endp, uint32_t sendtok, struct rv003usb_internal * ist )
{
  if( endp == 1 )
  {
    bool changed = false;
    for (int i=0;i<8;i++) {
      if (key_report[i] != previous_report[i]) changed = true;
      previous_report[i] = key_report[i];
    }
    if (changed) {
      usb_send_data( key_report, 8, 0, sendtok );
    }
  }
  else
  {
    usb_send_empty( sendtok );
  }
}
