/*
 * byy20180801.c
 *
 * Created: 2018-08-01 오후 12:53:26
 * Author : kccistc
 */ 

#define F_CPU 16000000L
#define set_bit(value, bit) (_SFR_BYTE(value) |= _BV(bit))
#define clear_bit(value, bit) (_SFR_BYTE(value) &= ~_BV(bit))
#define invert_bit(value, bit) (_SFR_BYTE(value) ^= _BV(bit))
#define read_bit(value, bit) ((_SFR_BYTE(value) & _BV(bit)) >> bit)

#define BINARY_PATTERN "0b%d%d%d%d%d%d%d%d"
#define BYTE2BINARY(byte) \
	(byte & 0x80 ? 1 : 0), \
	(byte & 0x40 ? 1 : 0), \
	(byte & 0x20 ? 1 : 0), \
	(byte & 0x10 ? 1 : 0), \
	(byte & 0x08 ? 1 : 0), \
	(byte & 0x04 ? 1 : 0), \
	(byte & 0x02 ? 1 : 0), \
	(byte & 0x01 ? 1 : 0)     //0번 비트가 1이면 1 반환, 아니면 0 반환
	


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART0_init(void);
void UART0_transmit(char data);
FILE OUTPUT \
		= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

void UART0_init(void)
{
	UBRR0H = 0X00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= 0X06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}
int main(void)
{
    /* Replace with your application code */
    UART0_init();
	stdout = &OUTPUT;
	int i = 0;
	int sum = 0;
	unsigned int count = 1;
	
	int no[10] = {25, 41, 11, 8, 90, 87, 37, 52, 73, 63};
		
		for (int i =0; i<9; i++)
		{
			for (int j = i + 1; j <10; j++)
			{
#if 1
				if(no[i] < no[j])     // 내림차순
				{
					int temp = no[i];
					no[i] = no[j];
					no[j] = temp;
				}
#else
				if(no[i] > no[j])     // 오름차순
				{
					int temp = no[i];
					no[i] = no[j];
					no[j] = temp;
				}	
#endif
			}
		}
		
		for (int i = 0; i <10; i++)
		{
			printf("%d\n\r", no[i]);
		}

	char str[100] = "test string";
	printf("%s\n\r", str);
	
	sprintf(str, "the first element in array is %d", no[0]);
	printf("%s\n\r", str);
	
	unsigned char value = 0b00001111;
	printf("Original         : "BINARY_PATTERN"\r\n", BYTE2BINARY(value));
	
	set_bit(value, 6);
	printf("set 7th bit      : "BINARY_PATTERN"\r\n", BYTE2BINARY(value));
	
	clear_bit(value, 2);
	printf("clear 3rd bit    : "BINARY_PATTERN"\r\n", BYTE2BINARY(value));
	
	invert_bit(value, 0);
	printf("Invert 1st bit   : "BINARY_PATTERN"\r\n", BYTE2BINARY(value));
	
	int read = read_bit(value, 5);
	printf("6th bit is       : %d\r\n", read);
	
	while(1){}
    
	return 0;
}

