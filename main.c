#include "startup.h"

#include <string.h>
#include <stdio.h>

/*
char rxByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input (Y = On, N = off):\r\n";
char str_echo[10];
*/

int main(void){
	//POST should go first
	int retval = post();
	if (retval != PASS) {
		//POST failed. Ask user if they want to try post again
	}

/*
	int		a ;
	int		n ;
	int		i ;
	float b;
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	UART2_Init();
		
	while (1){		
		for (i = 0; i < 10; i++){
			str_echo[i] = '\0';
		}
		rxByte = USART_Read(USART2);
		USART_Write(USART2, (uint8_t *)rxByte, 1);
		i = 0; 
		
		while (rxByte != '\r'){
			str_echo[i] = rxByte;
			i++;
			rxByte = USART_Read(USART2);
			USART_Write(USART2, (uint8_t *)rxByte, 1);
		}
		
		USART_Write(USART2, (uint8_t *)str_echo, strlen(str_echo));
		USART_Write(USART2, (uint8_t *)"\r\n", 2);
	}
*/
}

