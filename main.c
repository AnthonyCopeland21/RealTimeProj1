#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"

#include <string.h>
#include <stdio.h>

char rxByte = 0;
uint8_t buffer[BufferSize];
char str[] = "Give Red LED control input (Y = On, N = off):\r\n";
char str_echo[10];

int main(void){
	//POST should go first
	//char rxByte;
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
		//rxByte = USART_Read(USART2);
//		if (rxByte == 'N' || rxByte == 'n'){
//			Red_LED_Off();
//			USART_Write(USART2, (uint8_t *)"LED is Off\r\n\r\n", 16);
//		}
//		else if (rxByte == 'Y' || rxByte == 'y'){
//			Red_LED_On();
//			USART_Write(USART2, (uint8_t *)"LED is on\r\n\r\n", 15);
//		}
	}
}

