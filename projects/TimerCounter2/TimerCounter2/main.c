/*
 * TimerCounter2.c
 *
 * Created: 08.03.2023 19:26:49
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

int main(void)
{
	// conifg port C0 as output
	DDRC |= (1 << DDC0);

	// setup timer/counter 1
	TCCR1B |= (1 << CS12);          // prescaler 256
	TCNT1 = 0;                      // reset counter
	OCR1A = 46875;                  // set compare value
	TIMSK |= (1 << OCIE1A);         // enable compare interrupt

	// enable interrupts
	sei();

	while (1)
	{
		// do nothing
	}

	return 0;
}

ISR(TIMER1_COMPA_vect)
{
	PORTC ^= (1 << PORTC0);         // toggle LED
}