#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int count = 0;
int state = 1;

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
	int i=0;
    while (1) 
    {
		if (count == 38)  // 0.3 sec
		{
			count = 0;
			if (state == 1)
			{
				PORTD = 0x01 << i;
				i++;
				if (i == 8)
				{
					state = 2;
					i = 0;
				}
			}
			else if (state == 2)
			{
				PORTD = 0x80 >> i;
				i++;
				if (i == 8)
				{
					state = 1;
					i = 0;
				}
			}
		}
		
    }
	return 0;
}

