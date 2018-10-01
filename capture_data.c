#include "capture_data.h"

int capture_data(int freq) {
	//int freq_index_ref = freq - 50;
	uint8_t buffer[BufferSize];
	int i = 0;
	int *data;
	uint32_t ref = 0;
	uint32_t data_point = 0;
	int first = 0;
	int variable_index = 0;
	data = (int *)malloc(101*sizeof(int));
	for(int j = 0; j < 101; j++) {
		data[j] = 0;
	}
	while (i < 101){
		// TIM_SR_CC1IF
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){
			//USART_Write(USART2, (uint8_t *)"Data\n\r\n", 6);
			//take capture data from TIM2->CCR1
			if (first != 0){
				data_point = TIM2->CCR1;
				variable_index = (int)(data_point-ref)/80; /*- freq_index_ref*/
				data[i] = variable_index;
				ref = data_point;
				/*if(variable_index > -1 && variable_index <= 100){
					data[variable_index] += 1;
				}*/
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
		sprintf((char *)buffer, "%d %d\n\r\n", i, data[i]);
		USART_Write(USART2, (uint8_t *)buffer, sizeof(buffer)/sizeof(uint8_t));
	}
	
	free(data);
	return PASS;
}
