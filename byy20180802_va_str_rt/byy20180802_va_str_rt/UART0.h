/*
 * UART0.h
 *
 * Created: 2018-08-02 오후 12:30:33
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_





#endif /* UART0_H_ */

#include <avr/io.h>
/*
 * byy20180801.c
 *
 * Created: 2018-08-01 오후 12:53:26
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#define set_bit(value, bit) (_SFR_BYTE(value) |= _BV(bit))
#define clear_bit(value, bit) (_SFR_BYTE(value) &= ~_BV(bit))
#define invert_bit(value, bit) (_SFR_BYTE(value) ^= _BV(bit))
#define read_bit(value, bit) ((_SFR_BYTE(value) & _BV(bit)) >> bit)

#define BINARY_PATTERN "0b%d%d%d%d%d%d%d%d"
#define BYTE2BINARY(byte) \
	(byte & 0x80 ? 1 : 0), \
	(byte & 0x40 ? 1 : 0), \
	(byte & 0x20 ? 1 : 0), \
	(byte & 0x10 ? 1 : 0), \
	(byte & 0x08 ? 1 : 0), \
	(byte & 0x04 ? 1 : 0), \
	(byte & 0x02 ? 1 : 0), \
	(byte & 0x01 ? 1 : 0)     //0번 비트가 1이면 1 반환, 아니면 0 반환
	


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

char rx_data;  

void UART0_init(void)
{
	UBRR0H = 0X00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0B = 0x98; 
	UCSR0C |= 0X06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	
	if ( (data > 0x40) && (data < 0x5B))
	{
		data += 0x20;
	}
	else if( (data > 0x60) && (data < 0x7B))
	{
		data -= 0x20;
	}
	
	UDR0 = data;
}

unsigned char UART0_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
