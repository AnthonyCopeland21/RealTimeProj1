#include "startup.h"

void timer_startup(void){
	System_Clock_Init();
	LED_Init();
	UART2_Init();
}