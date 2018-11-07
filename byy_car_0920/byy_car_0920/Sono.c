/*
 * Sono.c
 *
 * Created: 2018-09-14 오전 9:53:09
 *  Author: kccistc
 */ 

#define F_CPU 16000000L
#define PRESCALER 256
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Sono.h"

double Distance_Data1 = 999;
double Distance_Data2 = 999;
double Distance_Data3 = 999;
double Distance_Data4 = 999;
double Distance_Data_sum = 9999;
int Data_count = 0;

void Sono_Timer_init(void)
{
	//TCCR1B |= (1<<CS12) | (1<<CS10);    // pwm이랑 충돌남
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
		if (TCNT1 > 65000) return 500;
		
	TCNT1 = 0;
	while(PING & 0x08)
	{
		if (TCNT1 > 650000)
		{
			TCNT1 = 0;
			break;
		}
	}
	
	double pulse_width = 1000000.0 * TCNT1 * PRESCALER / F_CPU ;
	
	if (Data_count == 0)
	{
		Distance_Data1 = pulse_width;
	}
	else if (Data_count == 1)
	{
		Distance_Data2 = pulse_width;
	}
	else if (Data_count == 2)
	{
		Distance_Data3 = pulse_width;
	}
	else if (Data_count == 3)
	{
		Distance_Data4 = pulse_width;
		Data_count= -1;
	}
	Data_count++;
	
	Distance_Data_sum = (Distance_Data1 + Distance_Data2 + Distance_Data3 + Distance_Data4) / 4;
	return (Distance_Data_sum / 58);
}
