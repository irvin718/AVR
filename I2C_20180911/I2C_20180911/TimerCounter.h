/*
 * TimerCounter.h
 *
 * Created: 2018-09-11 오후 12:39:29
 *  Author: kccistc
 */ 


#ifndef TIMERCOUNTER_H_
#define TIMERCOUNTER_H_





#endif /* TIMERCOUNTER_H_ */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void TimerCounterInit(void);
int led_blink_flag;
int tmcount;