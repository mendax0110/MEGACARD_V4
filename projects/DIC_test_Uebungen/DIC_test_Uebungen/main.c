/*
 * SPI_Interface.c
 *
 * Created: 11.05.2024 09:40:58
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/portpins.h>

unsigned char SPDR_Content = 0;

void initPorts()
{
	DDRC |= (1 << PC7);		// Indicator LED
	PORTC |= (1 << PC7);	// LED on
	
	DDRB |= (1 << PB7)|(1 << PB5);	// SPI - SCK, MOSI
	DDRB &= ~(1 << PB6);			// SPI - MISO
	
	DDRD |= (1 << PD7);		// SPI - Chip-Select
}

void initSpi()
{
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);	// SPI - Enable, MSTR, fosc = FCPU / 8
	SPSR |= (1 << SPI2X);
	SPDR_Content = 0x00;	// set Data
}

void SpiTransmit(unsigned char value)
{
	SPDR = value;	// Write to and Update Register
	while(!(SPDR & (1 << SPIF)));	// wait until send is completed
}

int main(void)
{
	initPorts();
	initSpi();
	
    while (1) 
    {
		// Send data
		SpiTransmit(0x30);
		SpiTransmit(0xff);
		SpiTransmit(0xA0);
    }
}

