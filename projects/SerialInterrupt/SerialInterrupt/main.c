/*
 * SerialInterrupt.c
 *
 * Created: 04.02.2023 15:16:13
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// Quarz frequency

#include <avr/io.h>			// std avr input/output lin
#include <avr/interrupt.h>	// std interrupt lib
#include <util/delay.h>		// lib for delays

// init USART module
void USART_Init(unsigned int baud)
{
	UBRRH = (unsigned char)(baud >> 8);	// baud rate high reg
	UBRRL = (unsigned char)baud;		// baud rate low reg
	UCSRB = (1 << RXEN)|(1 << TXEN)|(1 << RXCIE);	// enable receiver, transmit, recevie
	UCSRC = (1 << URSEL)|(1 << UCSZ0)|(1 << UCSZ1);	// set data frame format 8-bit, 1 stop bit
}

// transmit data using USART
void USART_Transmit(unsigned char data)
{
	while(!(UCSRA & (1 << UDRE)))
	{
		// Wait for empty transmit buffer
	}
	UDR = data;	// put data into buffer and send it
}

// interrupt service routine for USART complete
ISR(USART_RCX_vect)
{
	unsigned char receivedData = UDR;	// read data
	USART_Transmit(receivedData);		// transmit the data
}

int main(void)
{
	DDRB = 0xFF;	// set portb as output
	PORTB = 0x00;	// init portb to 0
	
	USART_Init(51);	// init usart with baudrate of 51
	
	sei();			// enable global interrupts
	
	while(1)
	{
		PORTB = 0xFF;		// turn on all LED's connected to PORTB
		_delay_ms(1000);	// delay for 1 sec
		PORTB = 0x00;		// turn off all LED's connected to PORTB
		_delay_ms(1000);	// delay for 1 sec
	}
	
	return 0;
}
