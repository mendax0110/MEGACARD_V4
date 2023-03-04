/*
 * TimerCounterLED.c
 *
 * Created: 04.03.2023 18:05:03
 * Author : Adrian
 */ 
/* TimerCounterLED.c */
#include <avr/io.h>        //I/O Declarations
#include <avr/interrupt.h> //Interrupt Declarations

#define TEILER_SW_1 11719    // Software pre-scaler divisor factor (kS) for 0.5s blink rate
#define TEILER_SW_2 5859     // Software pre-scaler divisor factor (kS) for 0.25s blink rate
#define TEILER_SW_3 2930     // Software pre-scaler divisor factor (kS) for 0.125s blink rate

int main( void )  // *** Main program ***
{
	DDRC  = 0xFF; // Configure LED port as output
	PORTC = 0x00; // Turn off all LEDs
	TCCR0 = 0x02; // Set hardware pre-scaler factor: kH = 1/8

	TIMSK |= (1 << TOIE0); // Enable individual Timer0 Overflow interrupt
	sei();        // Enable global interrupts
	while(1) {}   // Endless loop without action
} // End of main

ISR(TIMER0_OVF_vect) // *** ISR for Timer0 Overflow ***
{
	static unsigned int count_sw = 0; // Declare software counter as static
	// => variable value remains after leaving the ISR
	count_sw++; // Increment software counter
	if(count_sw >= TEILER_SW_1)  // Maximal value reached for 0.5s blink rate?
	{
		count_sw = 0;     // Reset software counter
		PORTC ^= 0xFF;	  // Toggle all LEDs
	}
	else if(count_sw >= TEILER_SW_2) // Maximal value reached for 0.25s blink rate?
	{
		PORTC = 0xAA;     // Turn on odd numbered LEDs
	}
	else if(count_sw >= TEILER_SW_3) // Maximal value reached for 0.125s blink rate?
	{
		PORTC = 0x55;     // Turn on even numbered LEDs
	}
} // End of ISR
