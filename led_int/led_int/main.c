/*
 * led_int.c
 *
 * Created: 2018-08-03 오전 10:33:59
 * Author : kccistc
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int state = 0;

ISR(INT0_vect)
{
	if (state == 1)
	{
		state = -1;
	}
	else if( state == -1)
	{
		state = 1;
	}
}

void INIT_PORT(void)
{
	DDRB = 0xff;
	PORTB = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x01;
}

void INIT_INT0(void)
{
	EIMSK |= ( 1 << INT1 | 1 << INT0);
	EICRA |= ( 1 << ISC00) | (1 << ISC01);
	sei();
}

int main(void)
{
	int index;
	
	INIT_PORT();
	INIT_INT0();
	
	index = 0;
    /* Replace with your application code */
    while (1) 
    {
		index += state;
		if(index  >= 8) index = 0;
		if(index < 0) index = 7;
		uint8_t pattern = (1 << index);
		PORTB = pattern;
		_delay_ms(500);
    }
	return 0;
}

