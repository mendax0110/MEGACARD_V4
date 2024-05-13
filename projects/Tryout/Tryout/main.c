/*
 * Tryout.c
 *
 * Created: 12.05.2024 11:16:47
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/portpins.h>

unsigned char SPDR_Content = 0;

void initPorts()
{
	DDRC |= (1 << PC7);     // Indicator LED
	PORTC |= (1 << PC7);    // LED on
	
	DDRB |= (1 << PB7)|(1 << PB5);     // SPI - SCK, MOSI
	DDRB &= ~(1 << PB6);                // SPI - MISO
	
	DDRD |= (1 << PD7);     // SPI - Chip-Select
}

void initSpi()
{
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);     // SPI - Enable, MSTR, Fosc = F_CPU / 8
	SPSR |= (1 << SPI2X);
}

void SpiTransmit(unsigned char value)
{
	SPDR = value;    // Write to and Update Register
	while(!(SPSR & (1 << SPIF)));    // Wait until send is completed
	
	// Toggle the LED after transmission
	PORTC ^= (1 << PC7);
	
	SPSR |= (1 << SPIF);
}

int main(void)
{
	initPorts();
	initSpi();
	
	while(1)
	{
		// Send Data
		SpiTransmit(0x30);
		_delay_ms(100); // Add a delay for visualization
		
		SpiTransmit(0xff);
		_delay_ms(100); // Add a delay for visualization
		
		SpiTransmit(0xA0);
		_delay_ms(100); // Add a delay for visualization
	}
}