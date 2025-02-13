#include "ch32fun.h"

// Define HID Usage IDs (Partial List)
#define HID_KEY_LEFT_SHIFT 0xE1
#define HID_KEY_RIGHT_SHIFT 0xE5
#define HID_KEY_LEFT_CTRL  0xE0
#define HID_KEY_RIGHT_CTRL 0xE4
#define HID_KEY_LEFT_WIN   0xE3
#define HID_KEY_LEFT_ALT   0xE2
#define HID_KEY_RIGHT_ALT  0xE6
#define HID_KEY_DEL        0x4C
#define HID_KEY_PTRSC      0x46

#define HID_KEY_INSERT     0x49

volatile uint32_t SysTick_Count;

/*
 * Start up the SysTick IRQ
 */
void systick_init(void)
{
	/* disable default SysTick behavior */
	SysTick->CTLR = 0;
	
	/* enable the SysTick IRQ */
	NVIC_EnableIRQ(SysTicK_IRQn);
	
	/* Set the tick interval to 1ms for normal op */
	SysTick->CMP = (FUNCONF_SYSTEM_CORE_CLOCK/1000)-1;
	
	/* Start at zero */
	SysTick->CNT = 0;
	SysTick_Count = 0;
	
	/* Enable SysTick counter, IRQ, HCLK/1 */
	SysTick->CTLR = SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE |
					SYSTICK_CTLR_STCLK;
}

/*
 * SysTick ISR just counts ticks
 * note - the __attribute__((interrupt)) syntax is crucial!
 */
void SysTick_Handler(void) __attribute__((interrupt));
void SysTick_Handler(void)
{
	// move the compare further ahead in time.
	// as a warning, if more than this length of time
	// passes before triggering, you may miss your
	// interrupt.
	SysTick->CMP += (FUNCONF_SYSTEM_CORE_CLOCK/1000);

	/* clear IRQ */
	SysTick->SR = 0;

	/* update counter */
	SysTick_Count++;
}

// Get Current Time in ms
uint32_t GetSystemTime(void) {
    return SysTick_Count;
}
