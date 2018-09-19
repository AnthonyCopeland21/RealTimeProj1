#include "startup.h"

// setup timers for captures
void timer_startup(void) {
	// setup timer values
	// use TIM2

	//TIMER CONFIG
	// ensure RCC->APB1ENR1 set to right timer
	// load prescaler into TIM2->PSC register
	// create an update event using the TIM2->EGR register
	
	// CAPTURE CONFIG
	// setup TIM2 to capture mode using CCR
	// turn off output enable in TIM2->CCER
	// setup CCMR2 for desired capture channel with cleared input event filter
	// Set enable bit for input channel
	// start input capture by setting TIM_CRx_CEN bit in TIM2->CCRx
		// clear this bit to stop input capture
	// TIM2->CCRx will be loaded with timer count when capture occurs
	// TIM_SR_CCxIF will be set in TIM2->SR when capture ocurs
	// reading captured counter value from TIM2->CCRx will clear IF bit in SR

}

int post(void) {
	int retval = FAIL;
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	timer_startup();
	// check GPIO, should see pulse within 100ms of startup
	// wait 100ms, return failure if no signal
}