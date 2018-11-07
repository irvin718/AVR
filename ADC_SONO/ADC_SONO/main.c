/*
 * ADC_ETUDE.c
 *
 * Created: 2018-09-13 오전 10:27:53
 * Author : kccistc
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART0.h"
#include "I2C_LCD.h"
#include "I2C.h"
#include "Sono.h"
#include "4_segment.h"

volatile uint8_t timercounter0 = 0;
volatile int counter =0;

enum {LightONWinON=1, LightOFFWinON, LightONWinOFF, LightOFFWinOFF,LightONWinSTOP, LightOFFWinSTOP};

FILE OUTPUT \
	= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);
	
void ADC_init(unsigned char channel)
{
	ADMUX |= (1<<REFS0);
	
	ADCSRA |= 0x07;
	
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADFR);
	
	ADMUX = ((ADMUX & 0xE0) | channel);
	ADCSRA |= (1<<ADSC);
}

int read_ADC(void)
{
	while (!(ADCSRA & (1<<ADIF)));
	
	return ADC;
}

struct state_light
{
	uint8_t states1;
};

void light_on_Win_on(void)
{
	PORTC = 0x01;
	printf("\r\nLight On\r\n");
	PORTE = 0x00;
	PORTB = 0x20;
	printf("\r\nWindow Open\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
}

void light_off_Win_on(void)
{
	PORTC = 0x00;
	printf("\r\nLight Off\r\n");
	PORTE = 0x00;
	PORTB = 0x20;
	printf("\r\nWindow Open\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
}

void light_on_Win_off(void)
{
	PORTC = 0x01;
	printf("\r\nLight On\r\n");
	PORTB = 0x00;
	PORTE = 0x08;
	printf("\r\nWindow Close\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
	
}

void light_off_Win_off(void)
{
	PORTC = 0x00;
	printf("\r\nLight Off\r\n");
	PORTB = 0x00;
	PORTE = 0x08;
	printf("\r\nWindow Close\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
	
}

void light_on_win_stop(void)
{
	PORTC = 0x01;
	printf("\r\nLight On\r\n");
	PORTB = 0x00;
	PORTE = 0x00;
	printf("\r\nWindow Stop\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
}

void light_off_win_stop(void)
{
	PORTC = 0x00;
	printf("\r\nLight Off\r\n");
	PORTB = 0x00;
	PORTE = 0x00;
	printf("\r\nWindow Stop\r\n");
	_delay_ms(1000);
	PORTB = 0x00;
}

ISR(TIMER0_OVF_vect)
{
	if (timercounter0%4 == 0)
	{
		display_FND(0,count%10); //count%10
	}
	else if (timercounter0%4 == 1)
	{
		display_FND(1,count%100/10); //count%100/10
	}
	else if (timercounter0%4 == 2)
	{
		display_FND(2,count%1000/100); //count%1000/100
	}
	else if (timercounter0%4 == 3)
	{
		display_FND(3,count/1000); //count/1000
	}
	timercounter0++;
	if (timercounter0 >= 200)
	{
		timercounter0 = 0;
	}
}

int main(void)
{
   // int read;
	int CDS_val,VA_val,Temp_val;
	char buff1[40];
	char buff2[40];
	char buff3[40];
	char buff4[40];
	
	int ki;
	
	uint8_t distance;
	
	struct state_light NOW_LIGHTSTS;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	ADC_init(0);
	I2C_LCD_init();
	Sono_Timer_init();
	
	NOW_LIGHTSTS.states1 = LightONWinSTOP;
	
	DDRB = 0xff;
	DDRE = 0xff;
	DDRG |= 0x10;
	DDRG &= ~0x08;
	DDRA = 0xff;
	DDRC = 0xf0;
	
	PORTB = 0x00;
	PORTE = 0x00;
	
	TCCR0 |= (1<<CS02) | ( 0<<CS01) | (0<<CS00);
	TIMSK |= (1<<TOIE0);
	
	sei();
	
	//PORTC = 0xf0;
	while (1) 
    {
		distance = measure_distance();
		
		//Seg_display();
		
		count = distance;
		
		/*if(count2 >= 10)
		{
			count++;
			count2=0;
		}
		count2++;
		*/
		/*
		display_digit(1,1);
		_delay_ms(SEGMENT_DELAY);
		
		display_digit(2,2);
		_delay_ms(SEGMENT_DELAY);
		
		display_digit(3,3);
		_delay_ms(SEGMENT_DELAY);
		
		display_digit(4,4);
		_delay_ms(SEGMENT_DELAY);
		*/
		
		  /*
		switch(NOW_LIGHTSTS.states1)
		{
			case LightONWinON:
			//light_on_Win_on();
			break;
			case LightOFFWinON:
			//light_off_Win_on();
			case LightONWinOFF:
			//light_on_Win_off();
			break;
			case LightOFFWinOFF:
			//light_off_Win_off();
			case LightONWinSTOP:
			//light_on_win_stop();
			break;
			case LightOFFWinSTOP:
			//light_off_win_stop();
			break;
			default:
			break;
		}
		
		ADC_init(0);
		_delay_ms(2);
		CDS_val = read_ADC();
		_delay_ms(2);
		
		ADC_init(3);
		_delay_ms(2);
		VA_val = read_ADC();
		_delay_ms(2);
		
		ADC_init(1);
		_delay_ms(2);
		Temp_val = read_ADC();
		_delay_ms(2);
		
		printf("CDS Value : %d\r\nVA Resist Value : %d\r\nTemp Value : %d\r\nUltraSona Value : %d cm\r\n\r\n",CDS_val, VA_val,Temp_val,distance);
		_delay_ms(1000);
		
		_delay_ms(5);
		sprintf(buff1, "CDS:%d",CDS_val);
		_delay_ms(5);
		I2C_LCD_write_string_XY(0,0,buff1);
		_delay_ms(5);
		sprintf(buff2, "VR:%d",VA_val);
		I2C_LCD_write_string_XY(1,0,buff2);
		_delay_ms(5);
		sprintf(buff3, "Tem:%d",Temp_val);
		I2C_LCD_write_string_XY(0, 9,buff3);
		_delay_ms(5);
		sprintf(buff4, "Sona:%d  ",distance);
		I2C_LCD_write_string_XY(1, 7,buff4);
		
		if ((CDS_val <= 501)&&(VA_val<= 300))
		{
			NOW_LIGHTSTS.states1 = LightONWinON;
		}
		else if ((CDS_val >= 500)&&(VA_val<=300))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinON;
		}
		else if ((CDS_val <= 501)&&((VA_val>=301)&&(VA_val<=499)))
		{
			NOW_LIGHTSTS.states1 = LightONWinSTOP;
		}
		else if ((CDS_val >= 501)&&((VA_val>=301)&&(VA_val<=499)))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinSTOP;
		}
		else if ((CDS_val <= 500)&&(VA_val>=499))
		{
			NOW_LIGHTSTS.states1 = LightONWinOFF;
		}
		else if ((CDS_val >= 500)&&(VA_val>=499))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinOFF;
		}
		*/
    }
	
	return 0;
}

