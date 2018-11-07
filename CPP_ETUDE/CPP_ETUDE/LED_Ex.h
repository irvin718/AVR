/* 
* LED_Ex.h
*
* Created: 2018-09-28 오전 11:37:05
* Author: kccistc
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "LED.h"  //상속받을 클래스가 있는 헤더파일

#ifndef __LED_EX_H__
#define __LED_EX_H__


class LED_Ex : public LED  // class LED_Ex 에 : public LED 붙이면 LED_Ex가 LED 클래스를 상속받는다는 의미
{
public:
	LED_Ex();
	~LED_Ex();
	void OneLED(uint8_t position, int ms);
}; //LED_Ex

#endif //__LED_EX_H__
