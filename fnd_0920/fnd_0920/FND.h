/*
 * FND.h
 *
 * Created: 2018-09-14 오후 4:56:46
 *  Author: kccistc
 */ 


#ifndef FND_H_
#define FND_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FND_DATA_DDR		DDRF   // FND Data Port
#define FND_CONTROL_DDR		DDRC   // FND Control Port
#define FND_DATA_PORT		PORTF   // FND Data Port
#define FND_CONTROL_PORT	PORTC   // FND Control Port
#define setbit(X, Y)				( X |= (1 << Y) )
#define clearbit(X, Y)				( X &= ~(1 << Y) )

void FND_init(void);
void displayFND(uint8_t position, uint8_t number);
void displayNumber(int count);
void TimerInterruptInit(void);
void IOPortInit(void);

#endif /* FND_H_ */