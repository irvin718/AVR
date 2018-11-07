/*
 * COMP_Interrupt.c
 *
 * Created: 2018-08-21 오전 9:48:20
 * Author : kccistc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0;
volatile int state = 0;

ISR(INT4_vect)
{
	OCR0= 255;
	OCR2 = 255;
	OCR1A = 0;
}

ISR(INT5_vect)
{
	OCR0 = 0;
	OCR2 = 0;
	OCR1A = 255;
}

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
	if(count == 64)
	{
		count = 0;
		state = !state;
		if(state) PORTD = 0x01;
		else PORTD = 0x00;
	}
}

int main(void)
{
	DDRD = 0x01;
	PORTD = 0x00;
	DDRB = 0xff;
	DDRE = 0x00;
	PORTE = 0x30;
	
	TCCR0 |= (1<< CS02);
	TCCR0 |= (1<<WGM01) | (1<<WGM00);
	TCCR0 |= (1<<COM01);
	
	TCCR2 |= (1<< CS01) | (1 <<CS00);
	TCCR2 |= (1<< WGM20) | (1<< WGM21);
	TCCR2 |= (1<< COM21) | (1<< COM20);
	
	TCCR1A |= (1<<WGM10);
	TCCR1A |= (1<<COM1A1);
	TCCR1A |= (1<<COM1B1) | (1<<COM1B0);
	TCCR1B |= (1<<CS12);
	
	EIMSK |= (1<< INT4);
	EIMSK |= (1<< INT5); 
	EICRB |= (1<< ISC41);
	EICRB |= (1<< ISC51);
	
	OCR0 = 127;
	OCR2 = 127;
	
	OCR1A = 500;
	
	sei();
    while (1) 
    {
    }
	return 0;
}

