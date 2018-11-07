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
int tx_flag; 
char tx_buffer[200];
int data_count;

void UART0_init(void);
void UART0_transmit(char data);
unsigned char UART0_receive(void);
void UART0_print_string(char *str);	// 문자열 송신
void UART0_print_1_byte_number(uint8_t n);
uint8_t UART0_rx_check(void);