/*
 * Tryout_1.c
 *
 * Created: 12.05.2024 11:22:05
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>

#define EEPROM_M95M01_WRITE	0x02	// Instruction WRITE
#define EEPROM_M95M01_READ	0x03	// Instruction READ

unsigned char SPDR_Content = 0;

void initPorts()
{
	DDRC |= (1 << PC7);		// Indicator LED
	PORTC |= (1 << PC7);	// LED on
	
	DDRB |= (1 << PB7)|(1 << PB5);		// SPI - SCK, MOSI
	DDRB &= ~(1 << PB6);				// SPI - MISO
	
	DDRD |= (1 << PD7);		// SPI - Chip-Select
	DDRB |= (1 << PB4);
}

void initSpi()
{
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);		// SPI - Enable, MSTR, Fosc = F_CPU / 8
	SPSR |= (1 << SPI2X);
	SPDR_Content = 0x00;	// Set Data
}

char SpiTransmit(unsigned char value)
{
	SPDR = value;		// Write to and Update Register
	while(!(SPDR & (1 << SPIF)));	// Wait until send is completed
	return SPDR;		// Datasheet s140 Help!
}

int main(void)
{
	unsigned char dummy1, dummy2, dummy3, dummy4, dummy5;
	
	initPorts();
	initSpi();
	
	while(1)
	{
		dummy1 = SpiTransmit(EEPROM_M95M01_WRITE);		// Write to and update Register
		dummy2 = SpiTransmit(0x00);						// Write to Address 0
		dummy3 = SpiTransmit(0x00);						// Write to Address 0
		dummy4 = SpiTransmit(0x00);						// Write to Address 0
		dummy5 = SpiTransmit(0xAA);						// Write to address 0 Content AA
		
		PORTB = (dummy1 << 4);
	}
}

