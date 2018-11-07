/*
 * _4_segment.c
 *
 * Created: 2018-09-14 오후 2:05:14
 *  Author: kccistc
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "4_segment.h"

uint8_t numbers[]
= {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
uint8_t fndselect[] 
= {0x10,0x20,0x40,0x80};


int num_i=0, num_j=0;
	
void Seg_display(void)
{
	for (num_i = 0; num_i < 4; num_i++ )
	{
		PORTC |= 0xf0;
		PORTC &= ~(1<<(num_i+4)); // PORTC 0xf0 기준
			_delay_ms(3000);
		for (num_j = 0; num_j < 10 ; num_j++)
		{
			PORTA  = numbers[num_j];
			_delay_ms(3000);
		}
	}
}

void display_FND(uint8_t position, uint8_t number)
{
	uint8_t num[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
	uint8_t fndselect[] = {0x80,0x40,0x20,0x10};
	
	PORTC = PORTC|0xf0;
	PORTC &= ~fndselect[position];
	PORTA = num[number]; 
}


void display_digit(int position, int number)
{
	PORTC |= 0xf0;
	PORTC &= ~(1 << (position - 1 +4));
	
	PORTA = numbers[number];
}

void displayNumber(int count)
{
	display_FND(0,count%10);
	_delay_ms(10);
	display_FND(1,count%100/10);
	_delay_ms(10);
	display_FND(2,count%1000/100);
	_delay_ms(10);
	display_FND(3,count/1000);
	_delay_ms(10);
}