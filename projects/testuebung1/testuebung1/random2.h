/*
 * random2.h
 *
 * Created: 21.01.2023 09:13:01
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL	// frequenz einstellen

#include <avr/io.h>			// standard AVR Input Output Library
#include <util/delay.h>		// verzögerungs library

int main(void)
{
	DDRA = 0b00000000;	// DDRA als eingang
	PORTA = 0b11111111;
	
	DDRC = 0b11111111; // DDRC als ausgang
	PORTC = 0b00000000;
	
	while(1)
	{
		PORTC = PINA & 0b00000011;
	}
}