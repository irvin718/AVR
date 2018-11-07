/* 
* LED_Ex.cpp
*
* Created: 2018-09-28 오전 11:37:05
* Author: kccistc
*/


#include "LED_Ex.h"

// default constructor
LED_Ex::LED_Ex()
{
} //LED_Ex

// default destructor
LED_Ex::~LED_Ex()
{
} //~LED_Ex

void LED_Ex::OneLED(uint8_t position, int ms)
{
	if (position > 7)
	{
		position = 7;
	}
	PORTA = (1<<position);
	DelayMs(ms);              //led.DelayMs 가 아닌 이유는 상속받은 클래스 안에서 함수를 사용하기 때문 (DelayMs가 Public, Protected 일 때만)
	PORTA &= ~(1<<position);
	DelayMs(ms);
}