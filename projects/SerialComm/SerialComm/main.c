/*
 * SerialComm.c
 *
 * Created: 11.12.2022 14:48:25
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set up the USART in asynchronous mode
	// Set baud rate to 9600
	UBRRH = 0;
	UBRRL = 12;
	
	// Enable transmitter and receiver
	UCSRB = (1 << TXEN) | (1 << RXEN);
	
	// Set frame format: 9 data bits, 1 stop bit
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	
	// Send a string to the serial port
	while(1)
	{
		// Wait until the transmit buffer is empty
		while(!(UCSRA & (1 << UDRE)));
		
		// Put the data into the transmit buffer
		UDR = 'I';
		UDR = 'N';
		UDR = 'P';
		UDR = 'U';
		UDR = 'T';
		UDR = ',';
		UDR = ' ';
		UDR = 'D';
		UDR = 'A';
		UDR = 'T';
		UDR = 'A';
		UDR = '*';
		UDR = '!';
		UDR = '\n';
		
		// Delay for a bit
		_delay_ms(500);
	}
}



