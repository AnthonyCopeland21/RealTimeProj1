#include "startup.h"

int post(void) {
	int retval = FAIL;
	// check GPIO, should see pulse within 100ms of startup
	// wait 100ms, return failure if no signal

	retval = PASS;
	return retval;
}

int start(void){
	
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	timer_startup();
	input_setup();
	
	//retval is the return value for pass/fail of the current function
	
	int retval = FAIL;
	char rxByte = 0;
	if (PASS != post()) {
		//post fails. user chooses what to do next
		USART_Write(USART2, (uint8_t *)"Post failed. Try again?(y/n)\n\r\n", 30);
		rxByte = USART_Read(USART2);
		if (rxByte == 'y') {
			if (PASS != post()){
				USART_Write(USART2, (uint8_t *)"Failed. Goodbye!\n\r\n", 17);
				goto failout;
			}
		}
		else {
			USART_Write(USART2, (uint8_t *)"Goodbye!\n\r\n", 10);
			goto failout;
		}
	}
	//data aquisition
	capture_data();
	retval = PASS;
failout:
	return retval;
}

// setup timers for captures
void timer_startup(void) {
	// setup timer values
	// use TIM2

	//TIMER CONFIG
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; 	// ensure RCC->APB1ENR1 set to right timer
	TIM2->PSC = 0; 													// load prescaler into TIM2->PSC register. it will be
																					// 80MHz divided by prescaler plus 1
	TIM2->EGR |= TIM_EGR_CC1G;              // create an update event using the TIM2->EGR register
																					//Try TIM_EGR_UG if this doesn't work
	
	// CAPTURE CONFIG
	// setup TIM2 to capture mode using CCR
	
	TIM2->CCER  &= ~0xFFFF;          //Disables the input enable by clearing register
	TIM2->CCMR1 &= ~0xFFFF;					 //Clear CCMR1 register
	TIM2->CCMR1 |= TIM_CCMR1_IC1F_0; //Set filter to 1st setting on page 909
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0; //Set CC1 channel as input
	TIM2->CCER  |= TIM_CCER_CC1E;    //Re-enables input enable
	TIM2->CR1   |= TIM_CR1_CEN;      //Starts Counter
	
	
	// turn off output enable in TIM2->CCER
	// setup CCMR2 for desired capture channel with cleared input event filter
	// Set enable bit for input channel
	// start input capture by setting TIM_CRx_CEN bit in TIM2->CCRx
		// clear this bit to stop input capture
	// TIM2->CCRx will be loaded with timer count when capture occurs
	// TIM_SR_CCxIF will be set in TIM2->SR when capture ocurs
	// reading captured counter value from TIM2->CCRx will clear IF bit in SR

}

void input_setup(void) {
	
	GPIOA->MODER   &= ~(0xF << (2*0));	// Clear bits
	GPIOA->MODER   |=   0xA << (2*0);      		
	GPIOA->AFR[0]  |=   0x1 << (2*0);      	
	
}
