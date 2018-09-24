#include "capture_data.h"

int data[101];
//uint8_t buffer[BufferSize];

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
				data[i] = convert_to_time(data[i]);
				i++;
			}
			// if first data point collected, set as reference
			else {
				first = 1;
				ref = TIM2->CCR1;
			}
		}
	}
	return PASS;
}

int convert_to_time(int data_point) {
	return (data_point * (1 / 80000000));
}

void print_data(void) {
	int i;
	char out[12];
	for (i = 0; i < 101; i++) {
		//if data point is not 0
		if (data[i] != 0){
			//then print out the value
			sprintf((char *)out, "%d %d\n\r\n", i, data[i]);
			USART_Write(USART2, (uint8_t *)out, 12);
		}
	}
}
