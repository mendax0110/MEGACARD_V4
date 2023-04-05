/*
 * Signals.c
 *
 * Created: 09.03.2023 15:51:41
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 230;
	PORTC ^= (1<<PC6);
}

void init_timer0()
{
	TCCR0 &= ~(1 << WGM00);							// Normal Mode
	TCCR0 &= ~(1 << WGM01);	
	TCCR0 |= (1 << COM00) | (1 << CS02) | (CS00);	// Toggle - OC0, F_CPU: 1024
	
	TCNT0 = 245;									// Preload - 245 => Out = F_CPU:1024:10
	TIMSK |= (1 << TOIE0);						// Overflow Interrupts enabled
}

void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7);	// Set LED Indicator
	
	DDRB |= (1 << PB3);		// OC0 - Ausgang Toggle
}

int main(void)
{	
    cli();			// lock	
	init_ports();	// init the ports
	init_timer0();	// init the timer
	sei();			// enable global interrupts
	
    while (1) 
    {
    }
}