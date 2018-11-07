/*
 * UART0.c
 *
 * Created: 2018-09-11 오전 11:33:45
 *  Author: kccistc
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART0.h"

void UART0_init(void)
{
	UBRR0H = 0X00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0B = 0x98;
	UCSR0C |= 0X06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
	
	
	/*
	UCSR0A=0x00;    // Communication Parameters: 8 Data, 1 Stop, No Parity, Asynchronous
	UCSR0B=0x98;    // USART0 RX complete int. enable, enable, Receiver: On, Transmitter: On
	UCSR0C=0x06;
	UBRR0H=0x00;
	UBRR0L=0x207;    // USART0 Baud Rate: 115,200
	//UBRR0L=0x67;    // 9600
	*/
}

void UART0_transmit(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

unsigned char UART0_receive(void)
{
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}


void UART0_print_string(char *str)	// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
	UART0_transmit(str[i]);			// 바이트 단위 출력
}



void UART0_print_1_byte_number(uint8_t n)
{
	char numString[4] = "0";
	int i, index = 0;
	
	if(n > 0){					// 문자열 변환
		for(i = 0; n != 0 ; i++)
		{
			numString[i] = n % 10 + '0';
			n = n / 10;
		}
		numString[i] = '\0';
		index = i - 1;
	}
	
	for(i = index; i >= 0; i--)		// 변환된 문자열을 역순으로 출력
	UART0_transmit(numString[i]);
}

uint8_t UART0_rx_check(void)
{
	if( UCSR0A & (1<<RXC0) )	// 데이터 수신 대기
	return 1;
	else
	return 0;
}