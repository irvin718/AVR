#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count = 0;
int state = 0;

ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
}

int main(void)
{
	DDRD = 0xff;
	PORTD = 0x00;
	
	TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	
	OCR0 = 128;
	TIMSK |= (1<<OCIE0);
	sei();
	
	while (1)
	{
		if (count == 38)  // 0.3 sec
		{
			count = 0;
			state = !state;
			if(state) PORTD = 0xff;
			else PORTD = 0x00;
		}
	}
	return 0;
}