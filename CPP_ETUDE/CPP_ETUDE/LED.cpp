/* 
* LED.cpp
*
* Created: 2018-09-28 오전 11:21:15
* Author: kccistc
*/


#include "LED.h"

LED::LED() : delayTime(300)  //객체가 만들어질때 자동으로 호출됨
{
	DDRA = 0xff;
	PORTA = 0xff;
}

LED::~LED()
{
	
}

void LED::Blink(int ms)             //클래스 이름:: 멤버변수 LED클래스에 속한 blink 함수
{
	PORTA = 0xff;
	DelayMs(ms);
	PORTA = 0x00;
	DelayMs(ms);
}

void LED::DelayMs(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}
