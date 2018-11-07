/*
 * byy_step_motor.c
 *
 * Created: 2018-11-05 오전 9:41:38
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(USART0_send, USART0_receive, _FDEV_SETUP_RW);

FILE OUTPUT \
= FDEV_SETUP_STREAM(USART0_send, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, USART0_receive, _FDEV_SETUP_READ);



uint8_t step_onetwo[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09}; //1-2상 여자방식
uint8_t step_two[8] = {0x03, 0x06, 0x0c, 0x09, 0x03, 0x06, 0x0c, 0x09};   //2상 여자방식
uint8_t step_two_op[8] = {0x09, 0x0c, 0x06, 0x03, 0x09, 0x0c, 0x06, 0x03};   //2상 여자방식

volatile int i = 0;
volatile int count=0;
volatile int count2 = 0;

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
	if (count == 4)
	{
		count = 0;
		PORTC = step_two[i];
		i++;
		if (i >= 9)
		{
			i = 0;
		}
	}
	
}

void timer_init(void)
{
	TCCR0 |= (1<<CS00) | (1<<CS01) | (1<<CS02); //1024
	TCCR0 |= (1<<COM01); //set when down counting OCR
	TCCR0 |= (1<<WGM01); //ctc
	TIMSK |= (1<<OCIE0);
	TIMSK |= (1<<TOIE0);
}


int main(void)
{
	char buff = 0;
	int count3 = 0;
	timer_init();
	USART_init(BR9600);
	stdin = stdout = stderr = &usart0_stdio;
	sei();
	
	printf("input Velocity...\r\n");
	DDRC = 0xff;
	PORTC = 0x00;
	
	OCR0 = 15; //5~15
	
    while (1) 
    {
		count2++;
		if(count2 == 20000)
		{
			count2 = 0;
			count3++;
			if(count3 == 10)
			{
				count3 = 0;
				printf("Current OCR0 Value : %d\r\n" , OCR0);
			}
		}
		if(USART0_rx_check())
		{
			buff = USART0_receive();
			OCR0 = buff - 48;
			printf("buff value = %d\r\n", OCR0);
			printf(" Input OCR0 Value : %d\r\n", OCR0);
		}
    }
}

