#include "capture_data.h"

int capture_data(int freq) {
	int freq_index_ref = freq - 50;
	uint8_t buffer[BufferSize];
	int i = 0;
	int *data, *buckets;
	uint32_t ref = 0;
	uint32_t data_point = 0;
	int first = 0;
	int variable_index = 0;
	data = (int *)malloc(101*sizeof(int));
	buckets = (int *)malloc(101*sizeof(int));
	for(int j = 0; j < 101; j++) {
		data[j] &= ~(0xFFFFFFFF);
		buckets[j] &= ~(0xFFFFFFFF);
		sprintf((char *)buffer, "%d %d\n\r\n",data[j],buckets[j]);
		USART_Write(USART2, (uint8_t *)buffer, sizeof(buffer)/sizeof(uint8_t));
	}
	while (i < 101){
		if ((TIM2->SR & TIM_SR_CC1IF) == TIM_SR_CC1IF){
			//take capture data from TIM2->CCR1
			if (first != 0){
				//set data to timer count
				data_point = TIM2->CCR1;
				
				//debug print statements
				//sprintf((char *)buffer, "%d %d", (int)data_point, (int)ref);
				//USART_Write(USART2, (uint8_t *)buffer, sizeof(buffer)/sizeof(uint8_t));				
				
				//find index where data will be stored into the 'buckets'
				variable_index = (int)(data_point-ref)/80000000 - freq_index_ref;  //2600 is not the right number. determine it.
				buckets[i] = (int)(data_point - ref)/80000000;
				
				//update reference to most recent data_point
				ref = data_point;
				
				//if the index is within range, then add one to the location in the array
				if(variable_index >= 0 && variable_index <= 100){
					data[variable_index] += 1;
				}
				
				//next data point
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
		//sprintf((char *)buffer, "%d %d",i, buckets[i]);
		//USART_Write(USART2, (uint8_t *)buffer, sizeof(buffer)/sizeof(uint8_t));
		if (data[i] != 0){                                               
			USART_Write(USART2, (uint8_t *)"DATA",4);
		}
		//USART_Write(USART2, (uint8_t *)"\n\r", 2);
		//sprintf((char *)buffer, "%d %d %d %d\n\r\n", i, freq_index_ref, (i+freq_index_ref), data[i+freq_index_ref]);
		//USART_Write(USART2, (uint8_t *)buffer, sizeof(buffer)/sizeof(uint8_t));
	}
	
	free(data);
	free(buckets);
	return PASS;
}
