/*
 * OCRSignals.c
 *
 * Created: 14.04.2023 22:17:01
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMP_vect)
{
	PORTC ^= (1 << PC6); // Toggle PC6
}

void init_timer0()
{
	TCCR0 = (1 << WGM01) | (1 << COM00); // CTC mode, toggle OC0 on match
	TCCR0 |= (1 << CS02) | (1 << CS00); // Prescaler = 1024

	OCR0 = 117; // Set output compare value for 1000 Hz signal
	TIMSK |= (1 << OCIE0); // Enable compare match interrupt
}

void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7); // Set LED Indicator

	DDRB |= (1 << PB3); // OC0 output
}

int main(void)
{
	cli(); // Disable global interrupts

	init_ports(); // Initialize ports
	init_timer0(); // Initialize timer

	sei(); // Enable global interrupts

	while (1)
	{
		// Main loop
	}
}