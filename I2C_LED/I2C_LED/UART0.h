/*
 * UART0.h
 *
 * Created: 2018-09-11 오전 11:33:07
 *  Author: kccistc
 */ 


#ifndef UART0_H_
#define UART0_H_

void UART0_init(void);
void UART0_transmit(char data);
unsigned char UART0_receive(void);
void UART0_print_string(char *str);
void UART0_print_1_byte_number(uint8_t n);
uint8_t UART0_rx_check(void);




#endif /* UART0_H_ */