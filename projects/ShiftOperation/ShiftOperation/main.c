/*
 * ShiftOperation.c
 *
 * Created: 06.01.2023 16:11:17
 * Author : Adrian
 */ 
#define F_CPU 120000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set PORTB as output
	DDRB = 0xFF;
	
	// Set PORTC as input
	DDRC = 0x00;
	
	while(1)
	{
		// read PORTC
		uint8_t c = PINC;
		
		// left shift c by 1 and store in PORTB
		PORTB = c << 1;
		_delay_ms(1000);
		
		// right shift c by 1 and store in PORTB
		PORTB = c >> 1;
		_delay_ms(1000);
	}
	
	return 0;
}
