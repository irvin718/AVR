/*
 * pwm_test.c
 *
 * Created: 2018-09-28 오후 4:23:20
 * Author : kccistc
 */ 
#include <avr/io.h>

int main(void)
{
	DDRB = 0x20; //PB5에서 출력
	TCCR1A |= (1<<COM1A1); //A 비반전
	TCCR1B |= (1<<CS12) | (1<<CS10);   //1024분주
	TCCR1B |= (1<<WGM13);  //fast pwm 14번 모드
	TCCR1B |= (1<<WGM12);  
	TCCR1A |= (1<<WGM11);  
	ICR1 = 7;
    while (1) 
    {
    }
}

