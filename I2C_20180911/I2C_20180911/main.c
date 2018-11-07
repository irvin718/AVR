
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UART0.h"
#include "I2C_LCD.h"
#include "TimerCounter.h"


FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);



/*
ISR(USART0_RX_vect)
{
	rx_data = UDR0;
	tx_flag = 0;
}
*/


/*
ISR(USART0_TX_vect)
{
	static char tx_count = 0;
	
	UDR0 = tx_buffer[tx_count++];;
	if(tx_count == strlen(tx_buffer))
	{
		UCSR0B &= 0xDF; // 송신 준비 인터럽트 비활성화
		tx_count = 0;
	}
}
*/


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0;
	if(tmcount > 64)
	{
		if(led_blink_flag == 1)
		{
			PORTC = ~PORTC;
		}
		tmcount = 0;
		/*
		if(tx_flag == 1) 
		{
			// 데이터 송신 주기:  DATA_COUNT/PWM_FREQUENCY
			if(++data_count > 5) 
			{
				UCSR0B |= 0x20;                     // 송신 준비 인터럽트 인에이블
				data_count = 0;
			}
		}
		*/
	}
	
	tmcount++;
}

int main(void)
{
	long count=0;
	char buffer[20];
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	int i = 0;
	
	TimerCounterInit();
	UART0_init();
	I2C_LCD_init();
	DDRC = 0x0f;
	PORTC = 0x01;

	I2C_LCD_write_string_XY(0, 0, "hello world");
	UART0_print_string("Menu\r\n");
	UART0_print_string("1. LED ON\r\n2. LED Blink\r\n3. LED OFF\r\n");
	
	
	sei();	
	
	while (1)
	{
		printf("input...\r\n");
		scanf("%d",i);
		printf("%d\r\n",i);
		
		_delay_ms(100);
		sprintf(buffer, "%010d", count);
		I2C_LCD_write_string_XY(1,0, buffer);
		count++;
		 i = UDR0; 
		
		if(i == 1)
		{
			PORTC = 0x01;
			UART0_print_string("LED ON\r\n");
			i = 0;
		}
		else if(i == 2)
		{
			led_blink_flag = 1;
			UART0_print_string("LED Blink\r\n");
			i = 0;
		}
		else if (i == 3)
		{
			PORTC = 0x00;
			led_blink_flag = 0;
			UART0_print_string("LED OFF\r\n");
			UART0_print_string("Menu\r\n");
			UART0_print_string("1. LED ON\r\n2. LED Blink\r\n3. LED OFF\r\n");
			i = 0;
		}
		
	}
}
