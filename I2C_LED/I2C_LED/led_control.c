/*
 * led_control.c
 *
 * Created: 2018-09-11 오후 3:42:10
 *  Author: kccistc
 */ 
#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "led_control.h"

void ledinit(void)
{
	LED_DDR = 0xff;
}

void ledoff(void)
{
	LED_PORT = 0xff;
	I2C_LCD_write_string_XY(0, 0, "LED OFF      ");
}

void ledon(void)
{
	LED_PORT = 0x00;
	I2C_LCD_write_string_XY(0, 0, "LED ON       ");
}

void ledblink(void)
{
	LED_PORT = 0x00;
	_delay_ms(100);
	LED_PORT = 0xff;
	_delay_ms(100);
	I2C_LCD_write_string_XY(0, 0, "LED BLINK    ");
}