#include "capture_data.h"

int capture_data(int freq) {
	int i = 0;
	int first = 0;
	int variable_index = 0;
	int data[101];
	uint8_t buffer[BufferSize];
	uint32_t ref = 0;
	uint32_t data_point = 0;
	for(int j = 0; j < 101; j++) {
		data[j] = 0;
	}
	while (i < 1000) {
		// TIM_SR_CC1IF
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF) {
			if (first != 0){
				data_point = TIM2->CCR1;
				variable_index = (int)(data_point-ref)/80;
				ref = data_point;
				if(variable_index - freq > -1 && variable_index - freq <= 100){
					data[variable_index - freq] += 1;
				}
				i++;
			}
			// if first data point collected, set as reference
			else {
				first = 1;
				ref = TIM2->CCR1;
			}
		}
	}
	//print data
	for (i = 0; i < 101; i++) {
		if(data[i] != 0) {
			sprintf((char *)buffer, "%d %d\n\r", (i+freq), data[i]);
			USART_Write(USART2, buffer, 11);
		}
	}
	return PASS;
}
