/*
 * SPI_AD_DAC.c
 *
 * Created: 18.05.2024 13:01:37
 * Author : Adrian
 */ 

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void init_spi()
{
	// Set CS , MOSI und CLK
	DDRB |= (1 << PB3)|(1 << PB4)|(1 << PB5)|(1 << PB7);
	// MISO
	DDRB &= ~(1 << PB6);
	// Set CS high
	PORTB |= (1 << PB4)|(1 << PB4);
	// SPI -Enable, MSTR, fosc = F_CPU/8
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0)|(1 << SPI2X);
}

unsigned char SPI_Transfer (unsigned char value)
{
	SPDR = value; // Write to and Update Register
	while(!(SPDR & (1 << SPIF))); // Wait until send is completed
	return SPDR;
}

unsigned int get_adc()
{
	// Sample on Falling Edge - ADC
	SPCR |= (1 << CPHA);
	// LSB -comes out first
	SPCR |= (1 << DORD);
	// Chip Select set to low
	PORTB &= ~(1 << PB4);
	// Set var
	unsigned char upperBits, lowerBits;
	// Read high bits
	upperBits = SPI_Transfer(0x00);
	// Read low bits
	lowerBits = SPI_Transfer(0x00);
	// Chip Select to high
	PORTB |= (1 << PB4);
	// Combine high and low bytes
	return (upperBits << 8) | lowerBits;
}

void set_dac(unsigned int value)
{
	// Sample on Rising Edge
	SPCR &= ~(1 << CPHA);
	// MSB -first
	SPCR &= ~(1 << DORD);
	// set var
	unsigned char upperBits, lowerBits;
	// first bit write to DAC_A, ignorebit, GAIN1, no shutdown
	upperBits = (value >> 8) | 0b00110000;
	lowerBits = value;
	// CS low to select DAC
	PORTB &= ~(1 << PB4);
	// Send high bits
	SPI_Transfer(upperBits);
	// Send low  bits
	SPI_Transfer(lowerBits);
	// CS high
	PORTB |= (1 << PB4);
}

int main(void)
{
	unsigned int adcValue;
	init_spi();
	
	while (1)
	{
		adcValue = get_adc();
		set_dac(adcValue);

	}
}