/*
 * RectangleSignals.c
 *
 * Created: 15.04.2023 20:21:28
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Timer0 compare match interrupt service routine
ISR(TIMER0_COMP_vect)
{
	PORTC ^= (1 << PC6); // Toggle PC6
}

// Initialize timer0 in CTC mode
void init_timer0(uint8_t ocr_value)
{
	TCCR0 = (1 << WGM01) | (1 << COM00); // CTC mode, toggle OC0 on match
	TCCR0 |= (1 << CS02) | (1 << CS00); // Prescaler = 1024

	OCR0 = ocr_value; // Set output compare value for desired frequency
	TIMSK |= (1 << OCIE0); // Enable compare match interrupt
}

// Initialize ports
void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7); // Set LED Indicator

	DDRB |= (1 << PB3); // OC0 output
}

// Main function
int main(void)
{
	cli(); // Disable global interrupts

	init_ports(); // Initialize ports
	init_timer0(117); // Initialize timer for 1000 Hz signal

	sei(); // Enable global interrupts

	while (1)
	{
		// Switch between different frequencies
		_delay_ms(500);
		init_timer0(58); // 2000 Hz
		_delay_ms(500);
		init_timer0(23); // 5000 Hz
		_delay_ms(500);
		init_timer0(117); // 1000 Hz
	}
}