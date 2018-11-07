/*
 * code3_1.c
 *
 * Created: 2018-07-30 오후 2:34:59
 * Author : kccistc
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

char circular_shift_left(char pattern)
{
	return ((pattern <<1)| (pattern >>7));	
}
int get_button_state(void)
{
	if((PINF & 0x04) >> 2 == 1)
	{
		_delay_ms(10);
		if((PINF & 0x04) >> 2 == 1)
		{
			return 1;
		}
	}
	return 0;
}
int main(void)
{
	DDRB = 0xff;   
	DDRF &= ~0X04;
	
	char pattern = 0x01;
	PORTB = pattern;
	
	char state_previous = 0, state_current;
	
	while (1) 
    {
		state_current = get_button_state();
		
		if(state_current == 1 && state_previous == 0)
		{
			pattern = circular_shift_left(pattern);
			PORTB = pattern;
		}
		state_previous = state_current;
	
    }
	return 0;
}

