#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "UART1.h"
#include "PWM.h"
#include "UART0.h"
#include "I2C_LCD.h"
#include "I2C.h"
#include "Sono.h"
#include "4_segment.h"
#include "FND.h"
#include "ShiftRegister.h"

static FILE usart0_stdio = FDEV_SETUP_STREAM(USART0_send, USART0_receive, _FDEV_SETUP_RW);

FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

volatile uint8_t timercounter0 = 0;
volatile int counter =0;
volatile unsigned int FndValue = 0;

void Motor_action(void);
void CDS_LightOn(void);

char buff_motor;
int CDS_val,VA_val,Temp_val;
uint8_t distance;
char buff1[40];
char buff2[40];
char buff3[40];
char buff4[40];
int SelfDrivFlag = 0;
int DirectFlag = 0;
int delayflag=0;
int delaycount=0;

void SetFndValue(int value)
{
	FndValue = value;
}

ISR(TIMER0_OVF_vect)
{
	if(timercounter0%4 == 0){
		displayFND(0, FndValue%10);  // 1???먮━
	}
	else if(timercounter0%4 == 1){
		displayFND(1, FndValue%100/10);  // 10???먮━
	}
	else if(timercounter0%4 == 2){
		displayFND(2, FndValue%1000/100);  // 100???먮━
	}
	else if(timercounter0%4 == 3){
		displayFND(3, FndValue/1000);  // 1000???먮━
	}
	
	timercounter0++;
	
	if (timercounter0 >= 200){
		timercounter0 = 0;
	}
	
}

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

ISR(TIMER1_COMPA_vect)
{
}

ISR(TIMER2_OVF_vect)
{
}


int	main(void)
{
	char cStr[100];
	int count=0;
	int j = 0;
	USART_init(BR115200);		//UBRR=103: 9600,  USART0 보오레이트 : 115200(UBRR=8), 16MHz
	UART1_init(BR115200_1);
	sei();
	
	PWM_init();
	ADC_init(0);
	I2C_LCD_init();
	Sono_Timer_init();
	FND_init();
	
	DDRB = 0xff;
	DDRE = 0xff;
	DDRG |= 0x10;
	DDRG &= ~0x08;
	DDRA |= 0xff;
	DDRC |= 0xf0;
	DDRF |= 0xf0; //CDS LED
	
	PORTB |= 0x01;   //state LED    Manual
	PORTB &= ~0x02;
	
	TCCR0 |= (1<<CS02) | ( 0<<CS01) | (0<<CS00);
	
	OCR1A = 0;  //top 0xff;
	OCR1B = 0;  //PB6 에서 25%duty
	OCR3A = 0;
	OCR3B = 0;  //PE4 에서 25%duty

	stdin = stdout = stderr = &usart0_stdio;
	
	printf("1.GO\r\n2.RIGHT\r\n3.LEFT\r\n4.STOP\r\n5.BACK\r\n");
	printf("6.FULL SPEED\r\n7.FULL SPEED RIGHT\r\n8.FULL SPEED LEFT\r\n9.FULL SPEED BACK\r\n");
	printf("a.Self Driving Mode\r\nSelect Num>\r\n");
	
	while(1)
	{
		
		CDS_LightOn();
		
		if(USART0_rx_check())
		{
			buff_motor = USART0_receive();
		}
		Motor_action();
		
		
	}
	return 0;
}

void Motor_action(void)
{
	ADC_init(0);
	CDS_val = read_ADC();
	/*
	ADC_init(3);
	VA_val = read_ADC();
	
	ADC_init(1);
	Temp_val = read_ADC();
	*/
	sprintf(buff1, "Manual Mode");
	I2C_LCD_write_string_XY(0,0,buff1);
	sprintf(buff2, "CDS:%d  ",CDS_val);
	I2C_LCD_write_string_XY(1,0,buff2);
	//sprintf(buff3, "Tem:%d",Temp_val);
	//I2C_LCD_write_string_XY(0, 9,buff3);
	sprintf(buff4, "Sona:%d  ",distance);
	I2C_LCD_write_string_XY(1, 7,buff4);
	
	distance = measure_distance();
	SetFndValue(distance);
	
	if (buff_motor == '1')
	{
		OCR1A = 110;                    //오른바퀴
		OCR1B = 0;
		OCR3A = 104;                    //왼바퀴
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nGO\r\n");
	}
	
	else if (buff_motor == '2')
	{
		OCR1A = 0;
		OCR1B = 0;
		OCR3A = 100;                      //오른바퀴
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nRIGHT\r\n");
	}
	else if (buff_motor == '3')
	{
		OCR1A = 100;
		OCR1B = 0;
		OCR3A = 0;
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nLEFT\r\n");
	}
	else if (buff_motor == '4')
	{
		OCR1A = 0;
		OCR1B = 0;
		OCR3A = 0;
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nSTOP\r\n");
	}
	else if (buff_motor == '5')
	{
		OCR1A = 0;
		OCR1B = 140;
		OCR3A = 0;
		OCR3B = 150;
		buff_motor = '0';
		printf("\r\nBACK\r\n");
	}
	else if (buff_motor == '6')
	{
		OCR1A = 255;
		OCR1B = 0;
		OCR3A = 251;
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nFULL SPEED\r\n");
	}
	else if (buff_motor == '7')
	{
		OCR1A = 0;
		OCR1B = 0;
		OCR3A = 0xff;
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nFULL SPEED Right\r\n");
	}
	else if (buff_motor == '8')
	{
		OCR1A = 0xff;
		OCR1B = 0;
		OCR3A = 0;
		OCR3B = 0;
		buff_motor = '0';
		printf("\r\nFULL SPEED Left\r\n");
	}
	else if (buff_motor == '9')
	{
		OCR1A = 0;
		OCR1B = 0xff;
		OCR3A = 0;
		OCR3B = 0xff;
		buff_motor = '0';
		printf("\r\nFULL SPEED BACK\r\n");
	}
	else if (buff_motor == 'c')
	{
		buff_motor = '0';
		OCR1A = 0;
		OCR1B = 0;
		OCR3A = 0;
		OCR3B = 0;
		printf("\r\nSelf Driving Mode...1\r\n");
		
		PORTB |= 0x02;
		PORTB &= ~0x01;      //state LED   Auto
		
		SelfDrivFlag = 1;
		while(SelfDrivFlag)
		{
			ADC_init(0);
			CDS_val = read_ADC();
	/*
	ADC_init(3);
	VA_val = read_ADC();
	
	ADC_init(1);
	Temp_val = read_ADC();
	*/
			sprintf(buff1, "Manual Mode");
			I2C_LCD_write_string_XY(0,0,buff1);
			sprintf(buff2, "CDS:%d  ",CDS_val);
			I2C_LCD_write_string_XY(1,0,buff2);
	//sprintf(buff3, "Tem:%d",Temp_val);
	//I2C_LCD_write_string_XY(0, 9,buff3);
			sprintf(buff4, "Sona:%d  ",distance);
			I2C_LCD_write_string_XY(1, 7,buff4);
	
			distance = measure_distance();
			SetFndValue(distance);
			CDS_LightOn();
			OCR1A = 110;
			OCR1B = 0;
			OCR3A = 104;
			OCR3B = 0;
			if(USART0_rx_check())
			{
				buff_motor = USART0_receive();
				if (buff_motor == 'c')
				{
					buff_motor = '0';
					printf("\r\nAbort Self Driving Mode...2\r\n");	
					SelfDrivFlag = 0;
					
					PORTB |= 0x01;            //state LED Manual
					PORTB &= ~0x02;
					
					OCR1A = 0;
					OCR1B = 0;
					OCR3A = 0;
					OCR3B = 0;
				}
			}
			
			
			
			if ((distance <=10)&&(DirectFlag == 0))   //////1 left
			{
				OCR1A = 100;
				OCR1B = 0;
				OCR3A = 0;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==1))  ///////2 left
			{
				OCR1A = 100;
				OCR1B = 0;
				OCR3A = 0;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==2))   ////////3  right
			{
				OCR1A = 0;
				OCR1B = 0;
				OCR3A = 100;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==3))  ///////////4   left
			{
				OCR1A = 100;
				OCR1B = 0;
				OCR3A = 0;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==4))  ///////////5   right
			{
				OCR1A = 0;
				OCR1B = 0;
				OCR3A = 100;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==5)) //////////6   right
			{
				OCR1A = 0;
				OCR1B = 0;
				OCR3A = 100;
				OCR3B = 0;
				DirectFlag++;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
			else if ((distance <=10)&&(DirectFlag ==6))  ///////////7  left
			{
				OCR1A = 100;
				OCR1B = 0;
				OCR3A = 0;
				OCR3B = 0;
				DirectFlag=0;
				_delay_ms(1000);
				distance = measure_distance();
				Distance_Data1 = 999;
				Distance_Data2 = 999;
				Distance_Data3 = 999;
				Distance_Data4 = 999;
			}
		}
	}
}

void CDS_LightOn(void)
{
	if (CDS_val <= 9)
	{
		PORTF |= 0xf0;
	}
		PORTF &= ~0xf0;
}
