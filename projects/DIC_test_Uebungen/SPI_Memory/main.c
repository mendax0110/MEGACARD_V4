/*
 * SPI_Memory.c
 *
 * Created: 11.05.2024 09:50:40
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/portpins.h>

#define EEPROM_M95M01_WRITE	0x02	// Instruction Write
#define EEPROM_M95M01_READ	0x03	// Instruction Read

unsigned char SPDR_Content = 0;

void initPorts()
{
	DDRC |= (1 << PC7);		// Indicator LED
	PORTC |= (1 << PC7);	// LED on
	
	DDRB |= (1 << PB7)|(1 << PB5);	//SPI - SCK, MOSI
	DDRB &= ~(1 << PB6);	// SPI - MISO
	
	DDRD |= (1 << PD7);	// SPI - Chip-Select
}

void initSpi()
{
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);	// SPI - Enable, MSTR, fosc = fCPU / 8
	SPSR |= (1 << SPI2X);
	SPDR_Content = 0x00;	// Set Data
}

char SpiTransmit(unsigned char value)
{
	SPDR = value;	// Write to and Update Register
	while(!(SPDR & (1 << SPIF)));	// Wait until send is completed
	return SPDR;	// Datasheet s140 help!
}

int main(void)
{
    unsigned char dummy1, dummy2, dummy3, dummy4, dummy5;
	
	initPorts();
	initSpi();
	
    while (1) 
    {
		dummy1 = SpiTransmit(EEPROM_M95M01_WRITE);		// Write to and Update Register
		dummy2 = SpiTransmit(0x00);						// Write to Adress 0
		dummy3 = SpiTransmit(0x00);						// Write to Adress 0
		dummy4 = SpiTransmit(0x00);						// Write to Adress 0
		dummy5 = SpiTransmit(0xAA);						// Write to content AA to Adress 0
    }
}

