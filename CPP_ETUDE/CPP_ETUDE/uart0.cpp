
#include	"uart0.h"

volatile unsigned char rx0_buffer[LENGTH_RX0_BUFFER];
volatile unsigned char rx0_head=0, rx0_tail=0;

UART0::UART0()
{
	init(BR9600);
}

UART0::~UART0()
{
}


// 인터럽트 USART 초기화
void UART0::init(unsigned int ubrr_baud)
{
	UCSR0B |= 1<<RXEN0 | 1<<TXEN0 | 1<<RXCIE0;
	UBRR0H = 0;
	UBRR0L = ubrr_baud;
}

void UART0::print_string(char *str)	// 문자열 송신
{
	for(int i = 0; str[i]; i++)			// ‘\0’ 문자를 만날 때까지 반복
	transmit(str[i]);			// 바이트 단위 출력
}

void UART0::transmit(char data)
{
	while( !(UCSR0A & (1 << UDRE0)) );	// 송신 가능 대기
	UDR0 = data;				// 데이터 전송
}

// 인터럽트에 의한 문자 수신 호출
int UART0::receive(void)
{	unsigned char data;
	
	while( rx0_head==rx0_tail );	// 수신 문자가 없음

	data = rx0_buffer[rx0_tail];
	rx0_tail = (rx0_tail==LENGTH_RX0_BUFFER-1) ? 0 : rx0_tail + 1;
	
	return data;
}

// USART1 RXC interrupt service
ISR(USART0_RX_vect)
{	
	volatile unsigned char data;
	
	// rx_buffer[] full, 마지막 수신 문자 버림
	if( (rx0_head+1==rx0_tail) || ((rx0_head==LENGTH_RX0_BUFFER-1) && (rx0_tail==0)) ){
		data = UDR0;
		}else{
		rx0_buffer[rx0_head] = UDR0;
		rx0_head = (rx0_head==LENGTH_RX0_BUFFER-1) ? 0 : rx0_head+1;
	}
}

// USART1 receive char check
int	UART0::rx_check(void)
{
	return (rx0_head != rx0_tail) ? 1 : 0;
}
