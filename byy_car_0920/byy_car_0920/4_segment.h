/*
 * _4_segment.h
 *
 * Created: 2018-09-14 오후 2:05:30
 *  Author: kccistc
 */ 



#define  SEGMENT_DELAY 2
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


uint8_t numbers[];
uint8_t fndselect[];
int num_i, num_j;
int count;
int count2;
void Seg_display(void);
void display_digit(int position, int number);
void display_FND(uint8_t position, uint8_t number);
void displayNumber(int count);

		