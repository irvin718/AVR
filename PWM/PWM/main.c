
#define F_CPU 16000000UL

#include <avr/io.h>

#include <util/delay.h>

#include <avr/interrupt.h>



uint8_t GetSWSts1(void);

uint8_t GetSWSts2(void);

void avrInit(void);


int main(void)
{
	avrInit();
	OCR0 = 10;
	sei();                // 인터럽트 시작
	while (1)
	{
		if (GetSWSts1())
		{
			OCR0 = OCR0 + 5;
				if (OCR0 >= 250)
				{
					OCR0 = 250;
				}
		}
		if (GetSWSts2())
		{
			OCR0 = OCR0 - 5;
			if (OCR0 <= 10)
			{
				OCR0 = 10;
			}
		}
	}
}

void avrInit(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
	DDRD = 0xff;
	PORTD = 0xff;
	DDRE = 0x00;
	PORTE = 0xff;
	
	TCCR0 |= (1<<CS02);   // 64분주
	TCCR0 |= (1<<WGM01) | (1<<WGM00);
	TCCR0 |= (1<<COM00) | (1<<COM01);
	TIMSK |= (1<<OCR0);   // 비교일치 인터럽트
}

uint8_t GetSWSts1(void)
{
	static unsigned char state_previous=1, state_current;
	state_current = (PINE & 0x20) >> 1;
	_delay_ms(10);
	if (state_current != state_previous)
	{
		state_previous = state_current;
		if (state_current == 0) return 1;
	}
	return 0;
}

uint8_t GetSWSts2(void)
{
	static uint8_t state_previous=1, state_current;
	state_current = (PINE & 0x10) >> 2;
	_delay_ms(10);
	if (state_current != state_previous)
	{
		state_previous = state_current;
		if (state_current == 0) return 1;
	}
	return 0;
}