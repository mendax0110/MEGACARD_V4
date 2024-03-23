/*
 * SPI_Speicher.c
 *
 * Created: 22.03.2024 15:32:20
 * Author : Adrian
 */ 
#define EEPROM_M95M01_WRITE		0x02	// Instruction write
#define EEPROM_M95M01_READ		0x03	// Instruction read

#include <avr/io.h>
#include <avr/portpins.h>


unsigned char SPDR_Content = 0;

void init_ports()
{
	DDRC |= (1<<PC7); //indikator LED setzen
	PORTC |= (1<<PC7); //LED on
	DDRB |= (1<<PB7) | (1<<PB5); //SPI - SCK, MOSI
	DDRB |= (1<<PD7); //SPI - ChipSelect
	DDRB &= ~(1<<PB6); //SPI - MISO
}

void init_SPI()
{
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0); // SPI - Enable, MSTR, fosc = fcpu/8
	SPSR |= (1<<SPI2X);
	SPDR_Content = 0x00; // Dateninhalt setzen
}

char SPI_Transmit(unsigned char value)
{
	SPDR = value;		//Write to and Update register
	while( !(SPSR & (1<<SPIF)));	//wait until send is completed
	return SPDR;					// DAtenblatt Seite 140 Hilfe
}

int main(void)
{
	unsigned char dummy1, dummy2, dummy3, dummy4, dummy5;
	
	init_ports();
	init_SPI();
	
	while (1)
	{
		//SPDR = 0x10;									// SPI - Datenregister ->0x10
		dummy1 = SPI_Transmit(EEPROM_M95M01_WRITE);		// Write to and Update Register
		dummy2 = SPI_Transmit(0x00);					// Write to Address 0
		dummy3 = SPI_Transmit(0x00);					// Write to Address 0
		dummy4 = SPI_Transmit(0x00);					// Write to Address 0
		dummy5 = SPI_Transmit(0xAA);					// Write content AA to address 00
	}
}