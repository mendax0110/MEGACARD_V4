/*
 * Testfragen_Aufgabe_9.c
 *
 * Created: 19.05.2024 13:45:56
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/portpins.h>
#include <stdio.h>

#define F_CPU 12000000UL  // CPU frequency: 12 MHz
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define EEPROM_M95M01_WRITE	0x02	// Instruction Write
#define EEPROM_M95M01_READ	0x03	// Instruction Read

void initPorts()
{
	// Set Port C7 as output for the LED indicator
	DDRC |= (1 << PC7);
	PORTC |= (1 << PC7); // Turn on LED
	
	// Set Port B5, B6, and B7 as output for SPI (SCK, MOSI, CS) and MISO as input
	DDRB |= (1 << PB7) | (1 << PB5) | (1 << PB4) | (1 << PB3);
	DDRB &= ~(1 << PB6);
}

void initSpi()
{
	// SPI Configuration: Master mode, F_CPU/128 clock
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
}

char SpiTransmit(unsigned char value)
{
	// Write data into the SPI data register
	SPDR = value;
	// Wait for transmission to complete
	while(!(SPSR & (1 << SPIF)));
	// Return the received data
	return SPDR;
}

// Initialize UART
void USART_Init(unsigned int ubrr)
{
	// Set baud rate
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN)|(1<<TXEN);
	// Set data frame format: 8 data bits, 1 stop bit
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

// Transmit a character via UART
void USART_Transmit(unsigned char data)
{
	// Wait for empty transmit buffer
	while (!(UCSRA & (1<<UDRE)));
	// Put data into buffer, send the data
	UDR = data;
}

int main(void)
{
	unsigned char dummy1, dummy2, dummy3, dummy4, dummy5;
	
	// Initialization
	initPorts();
	initSpi();
	USART_Init(MYUBRR);
	
	// Main program loop
	while (1)
	{
		// Send dummy data to read data from the SPI EEPROM
		dummy1 = SpiTransmit(EEPROM_M95M01_READ);
		dummy2 = SpiTransmit(0x00);
		dummy3 = SpiTransmit(0x00);
		dummy4 = SpiTransmit(0x00);
		dummy5 = SpiTransmit(0x00);
		
		// Send the received data via UART
		USART_Transmit(dummy1);
		USART_Transmit(dummy2);
		USART_Transmit(dummy3);
		USART_Transmit(dummy4);
		USART_Transmit(dummy5);
	}
}
