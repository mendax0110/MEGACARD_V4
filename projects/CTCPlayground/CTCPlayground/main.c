/*
 * CTCPlayground.c
 *
 * Created: 01.05.2023 09:46:19
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

// Interrupt service routine for Timer0 compare match A
ISR(TIMER0_COMP_vect)
{
	// Toggle PB3
	PORTB ^= (1 << PB3);
}

void init_ports()
{
	// Set PB3 as output
	DDRB |= (1 << PB3);
}

void init_timer()
{
	// Configure Timer0 for CTC mode with prescaler = 64
	TCCR0 = (1 << WGM01);       // CTC mode
	TCCR0 = (1 << CS01) | (1 << CS00);  // Prescaler = 64
	OCR0 = 62;                 // 1 kHz frequency at 16 MHz clock with prescaler = 64

	// Enable interrupts
	TIMSK |= (1 << OCIE0);	
}

int main(void)
{
	cli();
	init_ports();
	init_timer();
	sei();

	while (1) 
	{
		// Main program loop
	}
}