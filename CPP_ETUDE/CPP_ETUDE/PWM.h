/*
 * PWM.h
 *
 * Created: 2018-09-11 오후 4:54:20
 *  Author: kccistc
 */ 


#ifndef PWM_H_
#define PWM_H_





#endif /* PWM_H_ */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart0.h"

class PWM
{
	public:
	PWM();
	~PWM();
	protected:
	private:
	void PWM_init(void);
};


