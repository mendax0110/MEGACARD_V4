/*
 * HiZPullup.c
 *
 * Created: 14.12.2022 19:01:16
 * Author : Adrian
 */ 
#define F_CPU 12000000UL    // System clock already defined in Project Properties
#include <util/delay.h>    // Include delay functions
#include <avr/io.h>

#define LED_PIN PA0    // Define the LED pin to use
#define BLINK_DELAY 500 // Delay between LED blinks in ms

int main(void)
{
	// Configure I/O ports:
	DDRA = 0x00;  // Set Tasterport as input (default)
	PORTA = 0x0F; // Enable pull-ups for Taster S0,1,2,3
	DDRC = 0xFF;  // Set LED port as output
	PORTC = 0x01; // Turn on LED0, turn off LED1...7

	// Main loop
	while (1)
	{
		// Toggle the LED state
		PORTC = ~PORTC;

		// Wait for the specified blink delay
		_delay_ms(BLINK_DELAY);
	}
}
