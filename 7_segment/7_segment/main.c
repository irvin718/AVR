/*
 * 7_segment.c
 *
 * Created: 2018-08-03 오후 4:05:31
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int interrupt_count = 0;

ISR(TIMER0_OVF_vect)
{
	interrupt_count++;
}

int main(void)
{
	uint8_t numbers[]
		={0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11011000, 0b10000000, 0b10011000};

//	uint8_t numbers[]
//		={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67};
	
	
	
	int i, j;
	int count = 0;
	
	DDRB = 0xff;
	PORTB = numbers[0];
    /* Replace with your application code */
	TCCR0 |= (1 << CS02) | (1 << CS01) | ( 1<< CS00);
	TIMSK |= (1 << TOIE0);
	sei();
    while (1) 
    {
		if(interrupt_count >= 64)
		{
			interrupt_count = 0;
			
			count = (count + 1) % 10;
			PORTB = numbers[count];
		}
    }
	return 0;
}

