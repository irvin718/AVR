/*
 * Motor.c
 *
 * Created: 2018-08-22 오전 11:42:31
 *  Author: kccistc
 */ 
#include <avr/io.h>

void PWM_INIT()
{
	TCCR0 |= (1<< CS02) | (1<< CS01);
	TCCR0 |= (1<<WGM01) | (1<<WGM00);
	TCCR0 |= (1<<COM01);
	
	TCCR2 |= (1<< CS22);
	TCCR2 |= (1<< WGM20) | (1<< WGM21);
	TCCR2 |= (1<< COM21);
}