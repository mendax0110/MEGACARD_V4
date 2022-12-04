/*
 * Voltmeter_2.c
 *
 * Created: 04.12.2022 13:02:56
 * Author : Adrian
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"  // Include the LCD driver

int main(void)
{
	// Initialize the LCD screen
	lcd_init();

	// Set up the Atmega16A's ADC
	ADMUX |= (1 << REFS0);  // Set the reference voltage to AVcc
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Set the ADC clock prescaler to 128
	ADCSRA |= (1 << ADEN);  // Enable the ADC

	while (1)
	{
		// Start a conversion on channel 0
		ADMUX &= 0xF0;  // Clear the channel bits
		ADMUX |= 0x00;  // Set the channel to 0
		ADCSRA |= (1 << ADSC);  // Start the conversion

		// Wait for the conversion to complete
		while (ADCSRA & (1 << ADSC));

		// Read the conversion result and display it on the LCD screen
		uint16_t result = ADC;  // Read the result

		char buffer[16];  // Create a buffer to hold the result as a string
		snprintf(buffer, 16, "%d", result);  // Convert the result to a string

		lcd_clear();  // Clear the LCD screen
		lcd_puts(buffer);  // Display the result on the LCD screen

		_delay_ms(500);  // Wait for half a second before starting the next conversion
	}

	return 0;
}
