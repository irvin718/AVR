/*
 * LCD.c
 *
 * Created: 2018-08-10 오후 12:00:31
 * Author : kccistc
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "LCD.h"

#define  F_CPU 16000000



int main(void)
{
	mm = 12;
	ss = 0;
	ms = 0;
	state = 0;
	state2 = 0;
	
	DDRD = 0x00;
	LCD_init();
	LCD_write_string("Stop Watch");
	_delay_ms(500);
	LCD_clear();
	INIT_INT0();
	
	while (1)
	{
		LCD_goto_XY(2,0);
		sprintf(buff, "%02d:%02d:%02d", mm,ss,ms); //화면에 출력되지 않음,  buff에 값 저장
		LCD_write_string(buff);
		_delay_ms(1);
		ms++;
		if (ms>= 60)
		{
			ms = 0;
			ss++;
			if (ss>=60)
			{
				mm++;
				ss =0;
				if(mm >= 24)
				{
					mm = 0;
					ss = 0;
					ms = 0;
				}
			}
		}
		if(state == 1)
		{
			LCD_clear();
			_delay_ms(50);
			LCD_goto_XY(2,1);
			LCD_write_string("Stop state");
			while(state)
			{_delay_ms(10);}
			LCD_clear();
			_delay_ms(50);
			LCD_goto_XY(2,1);
			LCD_write_string("Start");
			_delay_ms(500);
		}
		if(state2 == 1)
		{
			LCD_clear();
			_delay_ms(50);
			LCD_clear();
			LCD_goto_XY(2,1);
			LCD_write_string("reset");
			_delay_ms(50);
			LCD_write_string("reset");
			_delay_ms(50);
			mm =12;
			ss = 0;
			ms = 0;
			_delay_ms(500);
			while(state)
			{
				LCD_clear();
				_delay_ms(50);
				LCD_write_string("reset");
			}
		}
	}

	return 0;
}

