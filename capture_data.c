#include "capture_data.h"

int data[101];
uint8_t buffer[BufferSize];

int capture_data(void) {
	int i = 0;
	int ref = 0;
	int first = 0;
	while (i < 101){
		// TIM_SR_CC1IF
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){
			//take capture data from TIM2->CCR1
			if (first != 0){
				data[i] = TIM2->CCR1 - ref;
				ref = data[i];
				i++;
			}
			// if first data point collected, set as reference
			else {
				first = 1;
				ref = TIM2->CCR1;
			}
		}
	}
	//print out data points that aren't set to 0
	return PASS;
}

void print_data(void) {
	int i;
	char out[10];
	for (i = 0; i < 101; i++) {
		//if data point is not 0
		if (data[i] != 0){
			//then print out the value
			sprintf((char *)out, "%d %d", i, data[i]);
			USART_Write(USART2, (uint8_t *)"\n\r\n",10);
		}
	}
}
