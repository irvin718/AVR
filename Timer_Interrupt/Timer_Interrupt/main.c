/*
 * Timer_Interrupt.c
 *
 * Created: 2018-08-14 오전 9:29:40
 * Author : kccistc
 */ 
#define PORT_DATA PORTC
#define PORT_CONTROL PORTB
#define DDR_DATA DDRC
#define DDR_CONTROL DDRB

#define RS_PIN 5
#define RW_PIN 6
#define E_PIN 7

#define COMMAND_CLEAR_DISPLAY 0X01
#define COMMAND_8_BIT_MODE 0X38
#define COMMAND_4_BIT_MODE 0X28

#define COMMAND_DISPLAY_ON_OFF_BIT 2
#define COMMAND_CURSOR_ON_OFF_BIT 1
#define COMMAND_BLINK_ON_OFF_BIT 0
#define COMMAND_SHIFT_RIGHT 0xc1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

char buff[20];
char buff_horizon[20];
char buff_vertical[20];
uint8_t mm , ss, ms;

void LCD_pulse_enable(void)
{
	PORT_CONTROL |= (1<<E_PIN);
	_delay_ms(1);
	PORT_CONTROL &= ~(1<<E_PIN);
	_delay_ms(1);
}

void LCD_write_data(uint8_t data)
{
	PORT_CONTROL |= (1<<RS_PIN);
	PORT_DATA = data;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_write_command(uint8_t command)
{
	PORT_CONTROL &= ~(1<<RS_PIN);
	PORT_DATA = command;
	LCD_pulse_enable();
	_delay_ms(2);
}

void LCD_clear(void)
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_init(void)
{
	_delay_ms(50);
	
	DDR_DATA = 0xff;
	PORT_DATA = 0x00;
	DDR_CONTROL |= (1<< RS_PIN) | (1<< RW_PIN) | (1<<E_PIN);
	
	PORT_CONTROL &= ~(1 << RW_PIN);
	
	LCD_write_command(COMMAND_8_BIT_MODE);
	
	uint8_t command = 0x08 | (1<< COMMAND_DISPLAY_ON_OFF_BIT);
	LCD_write_command(command);
	LCD_clear();
	
	LCD_write_command(0x06);
}

void LCD_write_string(char *string)
{
	uint8_t i;
	for(i=0; string[i]; i++)
	{
		LCD_write_data(string[i]);
	}
}

void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_write_command(command);
}

int count = 0;
int state = 0;
int count_LED = 0;
volatile int state_LED = 0;
int count_flag5 = 5;
int count_flag7 = 7;
int count_flag12 = 12;
int count_flag14 = 14;
int state_count5 = 5;
int state_count7 = 0;
int state_count12 = 0;
int state_count14 = 0;

#define RowGreen 0
#define RowYellow 1
#define RowRed 2
#define	ColGreen 3
#define ColYellow 4
#define ColRed 5


ISR(TIMER0_OVF_vect)
{
	count++;
	if(count == 1000)
	{
		count = 0;
		ms++;
		state_LED++;
		state_count5 = count_flag5 - state_LED;
		state_count7 = count_flag7 - state_LED; 
		state_count12 = count_flag12 - state_LED; 
		state_count14 = count_flag14 - state_LED;  
	}
	TCNT0 = (256-250);
}

/*ISR(TIMER1_OVF_vect)
{ 
	count_LED++;
	if(count_LED == 1000)
	{
		state_LED++;
	}
	
}*/

int main(void)
{
	enum{GreenRed, YellowRed, RedGreen, RedYellow};
	DDRD = 0xff;
	PORTD = 0x00;
	DDRE = 0xff;
	PORTE = 0x00;
	
	TCCR0 |= (1 << CS02) | ( 0 << CS01) | ( 0 << CS00);
	
	
	TIMSK |= (1 << TOIE0);
	//TIMSK |= (1 << TOIE1);
	
	sei();
	///////////////////////////////
	
	
	mm = 12;
	ss = 0;
	ms = 0;
	int sw_state = 0;
	
	LCD_init();
	LCD_write_string("Stop Watch");
	_delay_ms(500);
	LCD_clear();
	
    while (1) 
    {
		LCD_goto_XY(1,0);
		sprintf(buff, "%02d:%02d:%02d", mm,ss,ms); //화면에 출력되지 않음,  buff에 값 저장
		LCD_write_string(buff);
		_delay_ms(1);
		/*LCD_goto_XY(2,0);
		LCD_write_string(buff_horizon);
		_delay_ms(1);
		LCD_goto_XY(2,6);
		LCD_write_string(buff_vertical);
		_delay_ms(1);
		*/
		switch(sw_state)
		{
			case GreenRed :
				PORTD = (1<<RowGreen) | (1 <<ColRed);
				sprintf(buff_vertical,"Green, Red");
				LCD_goto_XY(0, 0);
				LCD_write_string(buff_vertical);
				if(state_LED >= 5 && state_LED < 7)
				state = YellowRed;
			break;
			
		}
		
		if((state_LED >= 0) && (state_LED < 5))
		{
			PORTD = 0b00000010;
			PORTE = 0b00001000;
			LCD_goto_XY(2,0);
			LCD_write_string("    G");
			LCD_goto_XY(2,7);
			LCD_write_string("    R   ");
			LCD_goto_XY(2,6);
			sprintf(buff_horizon, "%d", state_count5);
			LCD_write_string(buff_horizon);
			
		}
		else if((state_LED >= 5) && (state_LED < 7))
		{
			PORTD = 0b00000100;
			PORTE = 0b00001000;
			LCD_goto_XY(2,0);
			LCD_write_string("    Y");
			LCD_goto_XY(2,7);
			LCD_write_string("    R   ");
			LCD_goto_XY(2,6);
			sprintf(buff_horizon, "%d", state_count7);
			LCD_write_string(buff_horizon);
		}
		else if((state_LED >= 7) && ( state_LED < 12))
		{
			PORTD = 0b00001000;
			PORTE = 0b00000010;
			LCD_goto_XY(2,0);
			LCD_write_string("    R");
			LCD_goto_XY(2,7);
			LCD_write_string("    G   ");
			LCD_goto_XY(2,6);
			sprintf(buff_horizon, "%d", state_count12);
			LCD_write_string(buff_horizon);
		}
		else if((state_LED >= 12) && ( state_LED <14))
		{
			PORTD = 0b00001000;
			PORTE = 0b00000100;
			LCD_goto_XY(2,0);
			LCD_write_string("    R");
			LCD_goto_XY(2,7);
			LCD_write_string("    Y   ");
			LCD_goto_XY(2,6);
			sprintf(buff_horizon, "%d", state_count14);
			LCD_write_string(buff_horizon);
		}
		else if(state_LED == 14)
		{
			state_LED = 0;
			state_count5 = 5;
			state_count7 = 0;
			state_count12 = 0;
			state_count14 = 0;
		}
		
		
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
		
    }
	return 0;
}

