/*
 * ArithmeticPatterns.c
 *
 * Created: 07.01.2023 16:07:32
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Set PORTC as output
	DDRC = 0xFF;
	
	// Loop
	while(1)
	{
		// Turn on all LEDs
		PORTC = 0xFF;
		_delay_ms(500);
		
		// Turn off all LEDs
		PORTC = 0x00;
		_delay_ms(500);
		
		// Turn on every other LED
		PORTC = 0xAA;
		_delay_ms(500);
		
		// Turn on every third LED
		PORTC = 0x55;
		_delay_ms(500);
	}
	
	return 0;
}