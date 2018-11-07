/*
 * FND_595.c
 *
 * Created: 2018-09-19 오후 3:16:25
 * Author : kccistc
 */ 
#define DataPin 2
#define LatchPin 1
#define ClockPin 0
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xff;
	DDRC = 0xff;
	PORTC = 0xff;
	
	uint8_t Data;
	
	Data = 0xaa;
	
	int i;
	
	//DATA PIN : PORTB = 0b00000100;
	//CLOCK PIN : PORTB = 0b00000001;
	//LATCH PIN : PORTB = 0b00000010;
	
    while (1) 
    {	
		for (i = 0; i < 8; i++)
		{
			Data = (Data << i);
			if (Data & 0x80)
			{
				PORTA |=  (1 << DataPin);
			}
			else
			{
				PORTA &= ~(1<<DataPin);
			}
			PORTA &= ~(1 << ClockPin);
			PORTA |= (1 << ClockPin);
			PORTA &= ~(1 << ClockPin);
		}
		PORTA &= ~(1 << LatchPin);
		PORTA |= (1 << LatchPin);
		PORTA &= ~(1 << LatchPin);
    }
	return 0;
}

