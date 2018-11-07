/*
 * COMP_Interrupt.c
 *
 * Created: 2018-08-21 오전 9:48:20
 * Author : kccistc
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Motor.h"

volatile int count = 0;
volatile int SW1 = 0;
volatile int SW2 = 0;
volatile int SW3 = 0;

ISR(INT4_vect)
{
	SW1 = 1;
	SW2 = 0;
}

ISR(INT5_vect)
{
	SW1 = 0;
	SW2 = 1;
}

ISR(INT6_vect)
{
	SW3 = 1;
}

/*
ISR(TIMER0_COMP_vect)
{
	count++;
	TCNT0 = 0;
	if(count == 64)
	{
		count = 0;
		state = !state;
		if(state) PORTD = 0x01;
		else PORTD = 0x00;
	}
}
*/
ISR(TIMER1_OVF_vect)
{
	//1초마다 동작
	count++;
}

void AVR_INIT()
{
	DDRD = 0x01;
	PORTD = 0x00;
	DDRB = 0xff; //pwm
	DDRE = 0x00;
	PORTE = 0x70;
}

void INT_INIT()
{
	EIMSK |= (1<< INT4) | (1<<INT5) |( 1<<INT6);
	EICRB |= (1<< ISC41) | ( 1<<ISC51) | ( 1<<ISC61);
}

void TIMER1_INIT()
{
	//TCCR1A |= (1<<WGM10);
	//TCCR1A |= (1<<COM1A1);
	//TCCR1A |= (1<<COM1B1) | (1<<COM1B0);
	TCCR1B |= (1<<CS12);
	TIMSK |=(1<<TOIE1);
}

void RunWash()
{
	count = 0;
	int temp_state1 = 1;
	DDRB = 0xff; //pwm
	
	while(temp_state1)
	{
		if((count > 0)&&(count <= 3))
		{
			OCR0 = 50;
			OCR2 = 200;
		}
		else if((count >3)&& (count <= 6))
		{
			OCR0 = 200;
			OCR2 = 50;
		}
		else if(count > 6)
		{
			temp_state1 = 0;
		}
	}
	DDRB = 0x00; //pwm
	OCR0 = 127;
	OCR2 = 127;
}

void RunDry()
{
	count = 0;
	int temp_state2 = 1;
	DDRB = 0xff; //pwm
	while(temp_state2)
	{
		if((count > 0)&&(count < 4))
		{
			OCR0 = 254;
			OCR2 = 1;
		}
		else if(count > 4)
		{
			temp_state2 = 0;
			DDRB = 0x00;
		}
	}
	DDRB = 0x00; //pwm
	OCR0 = 127;
	OCR2 = 127;
}

enum WashState {IDLE, WASH, DRY} WashState;

int main(void)
{
	AVR_INIT();
	PWM_INIT();
	INT_INIT();
	TIMER1_INIT();
	
	int washFlag = 0;
	int dryFlag = 0;
	sei();
	
    while (1) 
    {
		/*
		switch(WashState)
		{
			case IDLE:
				if(SW1)
				{
					washFlag = 1;
					dryFlag = 0;
					//LCDstring("Wash selected")
				}
				else if(SW2)
				{
					washFlag = 0;
					dryFlag = 1;
				}
				else if(SW3)
				{
					if(washFlag)
					{
						washFlag = 0;
						dryFlag = 0;
						WashState = WASH;
					}
					else if(dryFlag)
					{
						washFlag = 0;
						dryFlag = 0;
						WashState = DRY;
					}
				}
			break;
			
			case WASH:
				RunWash();  //duty 0.7 , 3초 좌, 3초 우 -> IDLE
				SW1 = 0;
				SW2 = 0;
				SW3 = 0;
				WashState = IDLE;
			break;
			
			case DRY:
				RunDry();   //최대속도 5초 -> IDLE
				SW1 = 0;
				SW2 = 0;
				SW3 = 0;
				WashState = IDLE;
			break;
		}
		*/
		
		if ((SW1 == 1)&&(SW3 == 0))
		{
			washFlag = 1;
			dryFlag = 0;
		}
		else if((SW2 == 1) &&(SW3 == 0))
		{
			washFlag = 0;
			dryFlag = 1;
		}
		else if((washFlag == 1 )&&(SW3 == 1))
		{
			washFlag = 0;
			dryFlag = 0;
			RunWash();
			SW1 = 0;
			SW2 = 0;
			SW3 = 0;
		}
		else if((dryFlag == 1)&&(SW3 == 1))
		{
			washFlag = 0;
			dryFlag = 0;
			RunDry();
			SW1 = 0;
			SW2 = 0;
			SW3 = 0;
		}
		
    }
	return 0;
}


