/*
 * SPI_Interface.c
 *
 * Created: 08.03.2024 15:38:28
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <avr/portpins.h>

unsigned char SPDR_Content :=;

void initPorts()
{
	DDRC |= (1 << PC7);		// indicator LED
	PORTC |= (1 << PC7);	// LED on
	
	DDRB |= (1 << PB7)|(1 << PB5);	// SPI - SCK, MOSI
	DDRB &= ~(1 << PB6); // SPI - MISO
	
	DDRD |= (1 << PD7);	// SPI - ChipSelect
}


void init_SPI()
{
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);	// SPI - Enable, MSTR, fosc = fcpu/8
	SPSR |= (1 << SPI2X);
	SPDR_Content = 0x00;	// Dateninhalt setzen
	
}

int main(void)
{
    initPorts();
	init_SPI();
	
    while (1) 
    {
		SPDR = 0x00;
		
		while(!(SPSR & (1 << SPIF)))
		{
			
		}	
    }
}

