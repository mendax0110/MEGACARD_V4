/*
 * Signal.c
 *
 * Created: 08.04.2023 14:38:42
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

// quartz frequency
#define F_CPU 12000000UL

// Timer0 overflow interrupt service routine
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 245;
	PORTC ^= (1 << PC6);    // Toggle output on PC6
	PORTB ^= (1 << PB3);    // Toggle output on PB3
	PORTB ^= (1 << PB4);    // Toggle output on PB4
}

// Timer0 initialization
void init_timer0()
{
	TCCR0 &= ~(1 << WGM00);                         // Normal Mode
	TCCR0 &= ~(1 << WGM01);  						// Normal Mode
	TCCR0 |= (1 << COM00) | (1 << CS02) | (CS00);   // Toggle - OC0, F_CPU: 1024
	
	TCNT0 = 245;                                    // Preload - 245 => Out = F_CPU:1024:10
	TIMSK |= (1 << TOIE0);                        	// Overflow Interrupts enabled
}

// Port initialization
void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7);    			// Set LED Indicator
	
	DDRB |= (1 << PB3) | (1 << PB4);    // Set PB3 and PB4 as output
}

// Main function, program entry point
int main(void)
{
	cli();          // lock
	init_ports();   // init the ports
	init_timer0();  // init the timer
	sei();          // enable global interrupts
	
	while (1)
	{
		// do nothing
	}
}