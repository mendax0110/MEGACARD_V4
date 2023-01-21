/*
 * random1.h
 *
 * Created: 21.01.2023 09:12:18
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL	// frequenz einstellen

#include <avr/io.h>			// standard AVR Input Output Library
#include <util/delay.h>		// verzögerungs library

int main(void)
{
	DDRC = 0b11111111;	// DDRC als Ausgang
	PORTC = 0b00000000; // PORTC HI-Z
	
	
	PORTC = PORTC | 0b10000000; // mit oder bit 7 ein alle anderen aus
	_delay_ms(2000);
	
	PORTC = PORTC & 0b00000000; // alle bits aus mit (UND)
	_delay_ms(2000);
	
	PORTC = PORTC | 0b00000010; // bit 1 ein, alle anderen aus (OR)
	_delay_ms(2000);
	
	PORTC = PORTC ^ 0b00000010; // bit 1 ein alle anderen aus (XOR)
	_delay_ms(2000);
	
	while(1)
	{
	}
}