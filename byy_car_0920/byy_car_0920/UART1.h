/*
 * UART1.h
 *
 * Created: 2018-09-12 오전 11:29:13
 *  Author: kccistc
 */ 


#ifndef UART1_H_
#define UART1_H_


#include	<stdio.h>


#define	USART1	((unsigned char)1)
#define	LENGTH_RX_BUFFER_1	20
#define	LENGTH_TX_BUFFER_1	20

#define BR9600_1		103
#define BR57600_1	16
#define BR115200_1	8

extern	void UART1_init(unsigned int ubrr_baud);
extern	int UART1_send(char data);
extern	int UART1_receive(void);
extern	int	UART1_rx_check(void);
extern void UART1_print_string(char *str);	// 문자열 송신
extern void UART1_transmit(char data);

#endif


