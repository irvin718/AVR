/*
 * TimerCounter.c
 *
 * Created: 2018-09-11 오후 12:37:36
 *  Author: kccistc
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "TimerCounter.h"

void TimerCounterInit(void)
{
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	TCCR0 |= (1 << COM00);
	TIMSK |= (1 << TOIE0);
	
	sei();
}

