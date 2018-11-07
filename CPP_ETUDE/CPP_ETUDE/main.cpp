/*
 * CPP_ETUDE.cpp
 *
 * Created: 2018-09-28 오전 9:46:25
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "LED.h"
#include "LED_Ex.h"
#include "uart0.h"
#include "PWM.h"

int main(void)
{	
	int a = 100;
	LED led;// 클래스명, 객체명 //객체를 만드는 방법 //객체가 만들어지면서 생성자(LED())가 호출됨
											//led.DelayMs(100); //private라서 에러남
	LED_Ex led_ex;
	PWM pwm;
	UART0 uart;
	char buff_motor;
	
	sei();
	
	uart.print_string("1.GO\r\n2.RIGHT\r\n3.LEFT\r\n4.STOP\r\n5.BACK\r\n");
	uart.print_string("6.FULL SPEED\r\n7.FULL SPEED RIGHT\r\n8.FULL SPEED LEFT\r\n9.FULL SPEED BACK\r\nSelect Num>\r\n");
	OCR1A = 0;
	OCR1B = 0;
	
	OCR3A = 0;
	OCR3B = 0;
											
	while(1)
	{
		if(uart.rx_check())
		{
			buff_motor = uart.receive();
			uart.transmit(buff_motor);
			
			if (buff_motor == '1')
			{
				//PORTB = 0x20;
				//PORTE = 0x10;
				OCR1A = 100;
				OCR1B = 0;
				
				OCR3A = 100;
				OCR3B = 0;
				
				//OCR1A = 0xff;
				//OCR3A = 0xff;
				buff_motor = '0';
				uart.print_string("\r\nGO\r\n");
			}
			else if (buff_motor == '2')
			{
				//PORTB = 0x00;
				//PORTE = 0x10;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 100;
				OCR3B = 0;
				//OCR1A = 0x00;
				//OCR3A = 0xff;
				buff_motor = '0';
				uart.print_string("\r\nRIGHT\r\n");
			}
			else if (buff_motor == '3')
			{
				//PORTB = 0x20;
				//PORTE = 0x00;
				OCR1A = 100;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				//OCR1A = 0xff;
				//OCR3A = 0x0000;
				buff_motor = '0';
				uart.print_string("\r\nLEFT\r\n");
			}
			else if (buff_motor == '4')
			{
				//PORTB = 0x00;
				//PORTE = 0x00;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				//OCR1A = 0x00;
				//OCR3A = 0x00;
				buff_motor = '0';
				uart.print_string("\r\nSTOP\r\n");
			}
			else if (buff_motor == '5')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 100;
				
				OCR3A = 0;
				OCR3B = 100;
				buff_motor = '0';
				uart.print_string("\r\nBACK\r\n");
			}
			else if (buff_motor == '6')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0xff;
				OCR1B = 0;
				
				OCR3A = 0xff;
				OCR3B = 0;
				buff_motor = '0';
				uart.print_string("\r\nFULL SPEED\r\n");
			}
			else if (buff_motor == '7')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0xff;
				OCR1B = 0;
				
				OCR3A = 0;
				OCR3B = 0;
				buff_motor = '0';
				uart.print_string("\r\nFULL SPEED Right\r\n");
			}
			else if (buff_motor == '8')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 0;
				
				OCR3A = 0xff;
				OCR3B = 0;
				buff_motor = '0';
				uart.print_string("\r\nFULL SPEED Left\r\n");
			}
			else if (buff_motor == '9')
			{
				//PORTB = 0x40;
				//PORTE = 0x08;
				OCR1A = 0;
				OCR1B = 0xff;
				
				OCR3A = 0;
				OCR3B = 0xff;
				buff_motor = '0';
				uart.print_string("\r\nFULL SPEED BACK\r\n");
			}
		}
	}
	return 0;
}

