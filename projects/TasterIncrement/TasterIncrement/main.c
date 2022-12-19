/*
 * TasterIncrement.c
 *
 * Created: 19.12.2022 20:29:50
 * Author : Adrian
 *
 */ 
#define F_CPU 12000000UL        // Taktfrequenz Quarz
#include <avr/io.h>            // AVR standard IO library
#include <util/delay.h>        // delay library

#define TASTER_FAST PA0        // fast button
#define TASTER_SLOW PA1        // slow button

int main(void)
{
	DDRC = 0xFF;            // Port C as output
	DDRA &= ~(1<<PINA0) & ~(1<<PINA1);   // PA0 and PA1 as inputs
	PORTC = 0x00;           // Set Port C to 0

	while(1)
	{
		if (PINA & (1<<TASTER_FAST))  // If PA0 is pressed
		{
			// LED blinks faster
			PORTC += 1;         // Increment PORTC LEDs
			if (PORTC == 0xFF)
			{
				PORTC = 0x00;
			}
			_delay_ms(10);      // Wait 10ms
		}
		else if (PINA & (1<<TASTER_SLOW)) // If PA1 is pressed
		{
			// LED blinks slower
			PORTC += 1;         // Increment PORTC LEDs
			if (PORTC == 0xFF)
			{
				PORTC = 0x00;
			}
			_delay_ms(100);     // Wait 100ms
		}
		else
		{
			// LED blinks at normal speed
			PORTC += 1;         // Increment PORTC LEDs
			if (PORTC == 0xFF)
			{
				PORTC = 0x00;
			}
			_delay_ms(50);      // Wait 50ms
		}
	}
}
