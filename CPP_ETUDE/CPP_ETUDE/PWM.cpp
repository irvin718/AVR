/*
 * PWM.c
 *
 * Created: 2018-09-11 오후 4:54:06
 *  Author: kccistc
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "PWM.h"
#include "uart0.h"

PWM::PWM()
{
	PWM_init();
}

PWM::~PWM()
{
	
}

void PWM::PWM_init(void)
{
	TCCR1A |= (1<<COM1A1); //A 비반전
	TCCR1A |= (1<<COM1B1); //B 비반전
	TCCR1A |= (1<<WGM10);  //fast pwm
	
	TCCR1B |= (1<<CS12);   //OCR1A PB5
	TCCR1B |= (1<<WGM12);  //fast pwm
	
	
	TCCR3A |= (1<<COM3A1);
	TCCR3A |= (1<<COM3B1);
	TCCR3A |= (1<<WGM30);
	
	
	TCCR3B |= (1<<CS32);   //OCR3A TOP값 PE3
	TCCR3B |= (1<<WGM32);
	
	DDRB |= 0x60;
	DDRE |= 0x18;
}

/*void PWM::SpeedControl(void)
{
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
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nGO\r\n");
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
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nRIGHT\r\n");
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
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nLEFT\r\n");
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
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nSTOP\r\n");
		}
		else if (buff_motor == '5')
		{
			//PORTB = 0x40;
			//PORTE = 0x08;
			OCR1A = 0;
			OCR1B = 100;
			
			OCR3A = 0;
			OCR3B = 100;
			
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nBACK\r\n");
		}
		else if (buff_motor == '6')
		{
			//PORTB = 0x40;
			//PORTE = 0x08;
			OCR1A = 0xff;
			OCR1B = 0;
			
			OCR3A = 0xff;
			OCR3B = 0;
			
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nFULL SPEED\r\n");
		}
		else if (buff_motor == '7')
		{
			//PORTB = 0x40;
			//PORTE = 0x08;
			OCR1A = 0xff;
			OCR1B = 0;
			
			OCR3A = 0;
			OCR3B = 0;
			
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nFULL SPEED Right\r\n");
		}
		else if (buff_motor == '8')
		{
			//PORTB = 0x40;
			//PORTE = 0x08;
			OCR1A = 0;
			OCR1B = 0;
			
			OCR3A = 0xff;
			OCR3B = 0;
			
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nFULL SPEED Left\r\n");
		}
		else if (buff_motor == '9')
		{
			//PORTB = 0x40;
			//PORTE = 0x08;
			OCR1A = 0;
			OCR1B = 0xff;
			
			OCR3A = 0;
			OCR3B = 0xff;
			
			printf("%d\r\n",buff_motor-48);
			buff_motor = '0';
			printf("\r\nFULL SPEED BACK\r\n");
		}
}
*/

