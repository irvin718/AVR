/*
 * exc_time.c
 *
 * Created: 2018-08-03 오후 3:29:05
 * Author : kccistc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define MILLIS_INCREMENT_PER_OVERFLOW 1
#define MICROS_INCREMENT_PER_OVERFLOW 24

volatile unsigned long timer0_millis = 0;
volatile int timer0_micros = 0;

ISR(TIMER0_OVF_vect)
{
	unsigned long m = timer0_millis;
	int f = timer0_micros;
	
	m += MILLIS_INCREMENT_PER_OVERFLOW;
	f += MICROS_INCREMENT_PER_OVERFLOW;
	
	m += (f / 1000);
	f = f % 1000;
	
	timer0_millis = m;
	timer0_micros = f;
} 

unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;
	
	cli();
	
	m = timer0_millis;
	
	SREG = oldSREG;
	
	return m;
}

void init_timer0()
{
	TCCR0 |= (1 << CS02);
	TIMSK |= (1 << TOIE0);
	
	sei();
}

int main(void)
{
	uint8_t state = 0;
	
	init_timer0();
	
	DDRB = 0x01;
	PORTB = 0x00;
	
	unsigned long time_previous, time_current;
	time_previous = millis();
    /* Replace with your application code */
    while (1) 
    {
		time_current= millis();
		
		if((time_current - time_previous) > 1000)
		{
			time_previous = time_current;
			
			state = (state +1) %2;
			PORTB = state;	
		}
	}
	return 0;
}

