/*
 * TIMER_OVFINT.c
 *
 * Created: 2018-08-03 오후 12:11:23
 * Author : kccistc
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define TIMER_COUNT 5

volatile int count = 0;
int state = 0;

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
}

int main(void)
{
	DDRB = 0x10;
	PORTB = 0x00;
	
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	OCR0 = 255;
	
	TCCR0 |= (1 << COM00);
	
	TIMSK |= (1 << OCIE0);
	
	sei();
    /* Replace with your application code */
    while (1) 
    {
    }
	return 0;
}

