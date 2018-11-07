/*
 * ComEcho.c
 *
 * Created: 2018-10-10 오전 10:37:12
 * Author : kccistc
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "usart.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(USART0_send, USART0_receive, _FDEV_SETUP_RW);

FILE OUTPUT \
= FDEV_SETUP_STREAM(USART0_send, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, USART0_receive, _FDEV_SETUP_READ);


int main(void)
{
	char buff;
	int temp, humi;
	//char buff_1[30];
	USART_init(BR9600);		//UBRR=103: 9600,  USART0 보레이트 : 115200(UBRR=8), 16MHz
	stdin = stdout = stderr = &usart0_stdio;
	sei();
	
	printf("AVR start\n");
    /* Replace with your application code */
	//DDRB = 0xff;
	DDRD =0xff;
	int L1_Sts = 0;
	int L2_Sts = 0;
	int L3_Sts = 0;
	
	//sprintf(temp,"temp Value : %d", 25);
	//sprintf(humi,"humi value : %d", 65);
	
	temp = 26;
	humi = 65;
	int B_Port_data;
	int ledsts;
	
    while (1)
    {
		temp++;
		humi++;
		
		printf("temp,%d,humid,%d\n",temp,humi);
		
		
		for(int i = 0; i <8; i++)
		{
			ledsts = 1<<i;
			PORTD = ledsts;
			for (int j = 0 ; j<8 ;j++)
			{
				if(ledsts & i<<j)
				{
					//printf("STS%d,ON\n",j);
				}
				else
				{
					//printf("STS%d,OFF\n",j);
				}
				
			}
			//printf("temp,%d,humid,%d\n",i,i);
			_delay_ms(2000);
		}
		
		/*
		
		if (USART0_rx_check())
		{
			buff = USART0_receive();
			USART0_send(buff);
			if (buff == '1')             //string 비교
			{
				L1_Sts++;
				if (L1_Sts == 2)
				{
					DDRD = 0xff;
					PORTD &= ~0x04;
					L1_Sts =0;
				}
				else if (L1_Sts ==1)
				{
					DDRD = 0xff;
					PORTD |= 0x04;
				}
				printf("temp,%d,humid,%d\n", temp, humi);
				DDRD = 0x00;
				B_Port_data = PIND;
				DDRD = 0xff;
				printf("PORTB byte = %02x\n",B_Port_data);
			}
			else if (buff == '2')
			{
				L2_Sts++;
				if (L2_Sts == 2)
				{
					DDRD = 0xff;
					PORTD &= ~0x08;
					L2_Sts =0;
				}
				else if (L2_Sts ==1)
				{
					DDRD = 0xff;
					PORTD |= 0x08;
				}
				printf("temp,%d,humid,%d\n", temp, humi);
				DDRD = 0x00;
				B_Port_data = PIND;
				DDRD = 0xff;
				printf("PORTB byte = %02x\n",B_Port_data);
			}
			else if (buff == '3')
			{
				L3_Sts++;
				if (L3_Sts == 2)
				{
					DDRD = 0xff;
					PORTD &= ~0x10;
					L3_Sts =0;
				}
				else if (L3_Sts ==1)
				{
					DDRD = 0xff;
					PORTD |= 0x10;
				}
				printf("temp,%d,humid,%d\n", temp, humi);
				DDRD = 0x00;
				B_Port_data = PIND;
				DDRD = 0xff;
				printf("PORTB byte = %02x\n",B_Port_data);
			}
			else if (buff == '4')
			{
				printf("temp,%d,humid,%d\n", temp, humi);
				DDRB = 0x00;
				B_Port_data = PINB;
				printf("PORTB byte = %02x\n",B_Port_data);
			}
			else if (buff == '5')
			{
				printf("temp,%d,humid,%d\n", temp, humi);
				DDRB = 0x00;
				B_Port_data = PINB;
				printf("PORTB byte = %02x\n",B_Port_data);
			}
			
			
			if (!strcmp(buff, "LED1"))             //string 비교
			{
				L1_Sts++;
				if (L1_Sts == 2)
				{
					DDRB = 0xff;
					PORTB &= ~0x04;
					L1_Sts =0;
				}
				else if (L1_Sts ==1)
				{
					DDRB = 0xff;
					PORTB |= 0x04;
				}
			}
			if (!strcmp(buff, "LED2"))
			{
				L2_Sts++;
				if (L2_Sts == 2)
				{
					DDRB = 0xff;
					PORTB &= ~0x08;
					L2_Sts =0;
				}
				else if (L2_Sts ==1)
				{
					DDRB = 0xff;
					PORTB |= 0x08;
				}
			}
			if (!strcmp(buff, "LED3"))
			{
				L3_Sts++;
				if (L3_Sts == 2)
				{
					DDRB = 0xff;
					PORTB &= ~0x10;
					L3_Sts =0;
				}
				else if (L3_Sts ==1)
				{
					DDRB = 0xff;
					PORTB |= 0x10;
				}
			}
			*/
			
		}
  }


