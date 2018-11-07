/*
 * byy20180802_va_str_rt.c
 *
 * Created: 2018-08-02 오후 12:23:27
 * Author : kccistc
 */ 
#define F_CPU 16000000L

#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "uart0.h"
#include <avr/interrupt.h>

FILE OUTPUT \
		= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
		= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

int main(void)
{
	uint8_t counter = 100;
	char buffer[20] = "";
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	
    /* Replace with your application code */
    while (1) 
    {
			rx_data = UART0_receive();
			UART0_transmit(rx_data);
    }
	return 0;
}

