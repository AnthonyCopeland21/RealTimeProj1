#include "startup.h"

//This will still need work. I unplugged the PA0 and it didn't fail out
int post(void) {
	while (TIM2->CCR1 < 8000000){
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){
			return PASS;
		}
	}
	return FAIL;
}

int start(void){
	uint8_t buffer[BufferSize];
	System_Clock_Init();
	LED_Init();
	UART2_Init();
	timer_startup();
	input_setup();
	
	//retval is the return value for pass/fail of the current function
	int retval = FAIL;
	int user_value = '\0';
	char rxByte = 0;
	uint8_t new_buffer[BufferSize];
	char str[10];
	int i = 0;
	if (PASS != post()) {
		//post fails. user chooses what to do next
		USART_Write(USART2, (uint8_t *)"Post failed. Try again?(y/n)\n\r\n", 30);
		rxByte = USART_Read(USART2);
		sprintf((char *)buffer, "%c\n\r\n", rxByte);
		USART_Write(USART2, buffer, sizeof(buffer)/sizeof(uint8_t));
		if (rxByte == 'y' || rxByte == 'Y') {
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
	//ask user for input frequency
	sprintf((char *)buffer, "Please enter the frequency: ");
	USART_Write(USART2, buffer, sizeof(buffer)/sizeof(uint8_t));
	//this loop is intended to let the user see what they're typing
	rxByte = '\0';
	while(rxByte != '\r'){
		rxByte = USART_Read(USART2);
		sprintf((char *)new_buffer, "%c", rxByte);
		USART_Write(USART2, new_buffer, sizeof(new_buffer)/sizeof(uint8_t));
		str[i] = rxByte;
		i++;
	}
	user_value = atoi(str);
	for(i = 0; i < strlen((char *)buffer); i++){
		buffer[i] = '\0';
	}
	//sprintf((char *)buffer, "\n\r\n");
	USART_Write(USART2, (uint8_t *)"\n\r\n", 4);
	//data aquisition
	capture_data(user_value);
	
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
	TIM2->PSC = 0; 											// load prescaler into TIM2->PSC register. it will be
																					// 80MHz divided by prescaler plus 1
	TIM2->EGR |= TIM_EGR_UG;              // create an update event using the TIM2->EGR register
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
  // Clear bits

}

void input_setup(void) {
	
	RCC->AHB2ENR   |=   RCC_AHB2ENR_GPIOAEN; //Enable GPIOA
	
	GPIOA->MODER 	 &=   ~3 ;										// clear out bits 0 and 1 for PA0
	
	GPIOA->MODER   &=   ~(0xF << (2*0));     //Set desired values to tie PA0
	GPIOA->MODER   |=   0x2 << (2*0);      //as an input tied to TIM2_CH1
	//GPIOA->AFR[0]  |=   0x11 << (4*1); 0x1 << (4*0)
	GPIOA->AFR[0] &= ~(0x0000000F);
	GPIOA->AFR[0] |= 0x00000001;
	GPIOA->PUPDR   |=   0x2 << (2*0);
	
}
