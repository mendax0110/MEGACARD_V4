/*
 * TimerCounterLED2.c
 *
 * Created: 18.03.2023 17:58:02
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

volatile uint8_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
	counter++;
}

int main(void)
{
	DDRB |= (1 << PB0);		// set PB0 as output
	PORTB |= (1 << PB0);	// set PB0 high
	
	// setup timer/counter 1
	TCCR1A = 0;				// set normal mode
	OCR1A = 11999;			// set compare match value for 1 sec at 12MHz
	TIMSK |= (1 << OCIE1A);	// enable interrrupt
	
	sei();					// enable gloabl interrupts
	TCCR1B |= (1 << CS12);	// start timer with prescaler of 256
	
	while(1)
	{
		if(counter > 100)
		{
			counter = 0;
			PORTB ^= (1 << PB0);	// toggle PB0
		}
	}
}