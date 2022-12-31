/*
 * AVRSerialPC.c
 *
 * Created: 31.12.2022 16:33:28
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// function prototypes
void USART_init(unsigned int ubrr);
void USART_transmit(unsigned char data);
unsigned char USART_receive(void);

int main(void)
{
	USART_init(MYUBRR);

	while (1)
	{
		// receive data from computer
		unsigned char data = USART_receive();

		// transmit data back to computer
		USART_transmit(data);
	}

	return 0;
}

// initialize USART
void USART_init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// transmit data over USART
void USART_transmit(unsigned char data)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

// receive data over USART
unsigned char USART_receive(void)
{
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
