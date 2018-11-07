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
#include "UART0.h"
#include "I2C_LCD.h"
#include "I2C.h"

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
	PORTC = 0x00;
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
	PORTC = 0x00;
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
	PORTC = 0x00;
	
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
	PORTC = 0x00;
}

int main(void)
{
   // int read;
	int CDS_val,VA_val,Temp_val;
	char buff1[40];
	char buff2[40];
	char buff3[40];
	
	struct state_light NOW_LIGHTSTS;
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART0_init();
	ADC_init(0);
	I2C_LCD_init();
	
	NOW_LIGHTSTS.states1 = LightONWinSTOP;
	
	DDRC = 0x01;
	DDRB = 0xff;
	DDRE = 0xff;
	
	PORTC = 0x00;
	PORTB = 0x00;
	PORTE = 0x00;
	
	while (1) 
    {
		
		switch(NOW_LIGHTSTS.states1)
		{
			case LightONWinON:
			light_on_Win_on();
			break;
			case LightOFFWinON:
			light_off_Win_on();
			case LightONWinOFF:
			light_on_Win_off();
			break;
			case LightOFFWinOFF:
			light_off_Win_off();
			case LightONWinSTOP:
			light_on_win_stop();
			break;
			case LightOFFWinSTOP:
			light_off_win_stop();
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
		
		//printf("CDS Value : %d\r\nVA Resist Value : %d\r\nTemp Value : %d\r\n",CDS_val, VA_val,Temp_val);
		
		_delay_ms(5);
		sprintf(buff1, "C V:%d",CDS_val);
		_delay_ms(5);
		I2C_LCD_write_string_XY(0,0,buff1);
		_delay_ms(5);
		sprintf(buff2, "VR V:%d",VA_val);
		I2C_LCD_write_string_XY(1,0,buff2);
		_delay_ms(5);
		sprintf(buff3, "T V:%d",Temp_val);
		I2C_LCD_write_string_XY(0, 9,buff3);
		_delay_ms(5);
		
		if ((CDS_val <= 501)&&(VA_val<= 300))
		{
			NOW_LIGHTSTS.states1 = LightONWinON;
			_delay_ms(5);
		}
		else if ((CDS_val >= 500)&&(VA_val<=300))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinON;
			_delay_ms(5);
		}
		else if ((CDS_val <= 501)&&((VA_val>=301)&&(VA_val<=499)))
		{
			NOW_LIGHTSTS.states1 = LightONWinSTOP;
			_delay_ms(5);
		}
		else if ((CDS_val >= 501)&&((VA_val>=301)&&(VA_val<=499)))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinSTOP;
			_delay_ms(5);
		}
		else if ((CDS_val <= 500)&&(VA_val>=499))
		{
			NOW_LIGHTSTS.states1 = LightONWinOFF;
			_delay_ms(5);
		}
		else if ((CDS_val >= 500)&&(VA_val>=499))
		{
			NOW_LIGHTSTS.states1 = LightOFFWinOFF;
			_delay_ms(5);
		}
    }
	
	return 0;
}

