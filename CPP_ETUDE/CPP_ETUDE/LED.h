/* 
* LED.h
*
* Created: 2018-09-28 오전 11:21:15
* Author: kccistc
*/
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#ifndef __LED_H__
#define __LED_H__


class LED    //부모클래스
{
	public:									//접근제어지시자
	void Blink(int ms);						  //private, protected 로 선언하면 안됨 protected 는 상속했을 때 쓸 수 있음, 멤버함수,메소드(클래스내부 함수)
	//객체.Blink()의 형태로 사용가능(public의 경우)
	LED();									//생성자 (클래스이름이랑 같아야함)객체가 생성될때 자동으로 호출됨
	~LED();									//소멸자 (객체가 소멸할때 자동으로 호출됨)
	
	protected:
	void DelayMs(int ms);
	
	private:						           //해당 클래스 내에서만 사용할 수 있음
	int delayTime;					        //private 변수 조작하기
};

#endif //__LED_H__
