#include "capture_data.h"

//uint8_t buffer[BufferSize];

int capture_data(void) {
	int i = 0;
	uint32_t *data;
	data = malloc(101);
	for(i = 0; i<101; i++){
		data[i] = 0;
	}
	i = 0;
	uint32_t ref = 0;
	int first = 0;
	while (i < 101){
		// TIM_SR_CC1IF
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){
			//USART_Write(USART2, (uint8_t *)"Data\n\r\n", 6);
			//take capture data from TIM2->CCR1
			if (first != 0){
				data[i] = TIM2->CCR1 - ref;
				ref = data[i];
				USART_Write(USART2, (uint8_t *)ref, 8);
				data[i] = data[i] * (1/80000000);
				//USART_Write(USART2, (uint8_t *)data[i], 10);
				USART_Write(USART2, (uint8_t *)"\n\r\n",2);
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
		char out[12];
		for (i = 0; i < 101; i++) {
			//if data point is not 0
			if (data[i] != 0){
				//then print out the value
				sprintf((char *)out, "%d %d\n\r\n", i, data[i]);
				USART_Write(USART2, (uint8_t *)out, strlen(out));
			}
		}	
	
	free(data);
	return PASS;
}
