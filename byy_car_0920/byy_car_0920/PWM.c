/*
 * PWM.c
 *
 * Created: 2018-09-11 오후 4:54:06
 *  Author: kccistc
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "PWM.h"

void PWM_init(void)
{
	/*TCCR1A |= (1<<COM1A1); //A 비반전
	TCCR1A |= (1<<COM1B1); //B 비반전
	TCCR1A |= (1<<WGM11);  //fast pwm
	TCCR1A |= (1<<WGM10);  //fast pwm
	
	TCCR1B |= (1<<CS12);   //OCR1A PB5
	TCCR1B |= (1<<WGM13);  //fast pwm
	TCCR1B |= (1<<WGM12);  //fast pwm
	
	
	TCCR3A |= (1<<COM3A1);
	TCCR3A |= (1<<COM3B1);
	TCCR3A |= (1<<WGM31);
	TCCR3A |= (1<<WGM30);
	
	
	TCCR3B |= (1<<CS32);   //OCR3A TOP값 PE3
	TCCR3B |= (1<<WGM33);
	TCCR3B |= (1<<WGM32);
	*/
	
	TCCR1A |= (1<<COM1A1); //A 비반전
	TCCR1A |= (1<<COM1B1); //B 비반전
	TCCR1A |= (1<<WGM10);  //fast pwm
	
	TCCR1B |= (1<<CS12);   //OCR1A PB5
	TCCR1B |= (1<<WGM12);  //fast pwm
	
	
	TCCR3A |= (1<<COM3A1);
	TCCR3A |= (1<<COM3B1);
	TCCR3A |= (1<<WGM30);
	
	
	TCCR3B |= (1<<CS32);   //OCR3A TOP값 PE3
	TCCR3B |= (1<<WGM32);
	
	
	
	//TIMSK |= (1<<OCIE1A); 
	//ETIMSK |= (1<<OCIE3A);

}