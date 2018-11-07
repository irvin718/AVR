/*
 * Sono.c
 *
 * Created: 2018-09-14 오전 9:53:09
 *  Author: kccistc
 */ 

#define F_CPU 16000000L
#define PRESCALER 1024
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Sono.h"

void Sono_Timer_init(void)
{
	TCCR1B |= (1<<CS12) | (1<<CS10);
}

uint8_t measure_distance(void)
{
	PORTG &= ~0x10;
	_delay_us(1);
	PORTG |= 0x10;
	_delay_us(10);
	PORTG &= ~0x10;
	
	TCNT1 = 0;
	while(!(PING & 0x08))
		if (TCNT1 > 65000) return 0;
		
	TCNT1 = 0;
	while(PING & 0x08)
	{
		if (TCNT1 > 650000)
		{
			TCNT1 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU;
	
	return pulse_width / 58;
}
