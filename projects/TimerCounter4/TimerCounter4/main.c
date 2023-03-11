/*
 * TimerCounter4.c
 *
 * Created: 11.03.2023 20:48:48
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

volatile uint8_t led_state = 0x01;  // Start with the first LED on (PB0)

void init_timer0()
{
	// CTC mode, TOP value = OCR0
	TCCR0 |= (1 << WGM01);

	// Set prescaler to 1024
	TCCR0 |= (1 << COM00) | (1 << CS02) | (1 << CS00);	// Toggle - OC0, F_CPU: 1024

	// Set compare match value for 1s interrupt
	OCR0 = 117; // (F_CPU / prescaler / desired frequency) - 1 = (12000000 / 1024 / 1) - 1 = 117

	// Enable compare match interrupt
	TIMSK |= (1 << OCIE0);
}

void init_ports()
{
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2); // Set PB0, PB1, PB2 as output pins
	PORTB = led_state; // Set initial LED state on PORTB
}

int main(void)
{
	cli();          // Disable global interrupts
	init_ports();   // Initialize ports
	init_timer0();  // Initialize Timer0
	sei();          // Enable global interrupts

	while (1)
	{
		// Do nothing in the main loop
	}
}

ISR(TIMER0_COMP_vect)
{
	led_state <<= 1; // Shift LED state left
	if (led_state == 0x00)
	{
		led_state = 0x01; // Reset to the first LED
	}
	PORTB = led_state; // Update LED state on PORTB
}