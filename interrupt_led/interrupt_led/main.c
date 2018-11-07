/*
 * interrupt_led.c
 *
 * Created: 2018-08-02 오후 3:25:07
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int state = 0;

ISR(INT0_vect)
{
	state = (state + 1) % 2;
}
void INIT_PORT(void)
{
	DDRB = 0Xff;
	PORTB = 0X00;
	
	DDRD = 0X00;
	PORTD = 0X01;
}

void INIT_INT0(void)
{
	EIMSK |= (1 << INT0);
	EICRA |= (1 << ISC01);
	sei();
}

int main(void)
{
	INIT_PORT();
    INIT_INT0();
	
	int i = 0;
	char temp;
	PORTB = 0x80;
	while (1) 
    {
		for(i = 0; i<8; i++)
		{
	
		temp = PORTB >> 1;
		_delay_ms(500);
		if(PORTB == 0x00)
		{
			i = 0;
		}
		}
	}
	return 0;
}

