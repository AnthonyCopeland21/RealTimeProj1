#include "startup.h"

// setup timers for captures
void timer_startup(void) {
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	// setup timer values
	// use TIM2

}

int POST(void) {
	int retval = FAIL;
	timer_startup();
	// check GPIO, should see pulse within 100ms of startup
	// wait 100ms, return failure if no signal
	// 
}