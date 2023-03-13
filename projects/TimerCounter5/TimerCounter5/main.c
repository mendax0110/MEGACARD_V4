/*
 * TimerCounter5.c
 *
 * Created: 13.03.2023 19:02:37
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0;

ISR(TIMER1_COMPA_vect)
{
	counter++;
}

int main(void)
{
	DDRB |= (1 << PB0);		// set PB0 as output
	PORTB |= (1 << PB0);	// set PB0 high
	
	// setup Timer/Counter 0
	TCCR1A |= (1 << WGM01);	// set CTC mode
	OCR1A = 59;				// set compare match value (59 for 1ms 12Mhz clock)
	TIMSK |= (1 << OCIE1A);	// enable interrupt
	sei();
	TCCR1B |= (1 << CS01)|(1 << CS00);	// start timer with prescaler of 64
	
	while(1) 
	{
		if(counter > 100)
		{
			counter = 0;
			PORTB ^= (1 << PB0);
		}
	}
}
