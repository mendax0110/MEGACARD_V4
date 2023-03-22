/*
 * TimerCounterRead.c
 *
 * Created: 22.03.2023 20:27:22
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

volatile uint16_t edge_count = 0;	// Counter for the number of edges
volatile uint8_t timer_overflow = 0;	// Counter for the number of overflows

void init_timer1()
{
	TCCR1A = 0x00;	// Normal mode
	TCCR1B = (1 << CS12)|(1 << CS10);	// Prescaler = 1024
	OCR1A = 0x7FFF;	// Compare value = 32767
	TIMSK |= (1 << OCIE1A)|(1 << TOIE1);	// Enable compare interrupt
}

void init_ports()
{
	DDRB |= (1 << PB3); // Set PB3 as output
	DDRB &= ~(1 << PB4); // Set PB4 as input
	PORTB |= (1 << PB4); // Enable pull-up resistor
}

int main(void)
{
	cli();	// Disable global interrupts
	init_ports();
	init_timer1();
	sei();	// Enable global interrupts

	while(1)
	{
		while(!timer_overflow)
		{
			// Wait for timer overflow
		}

		// disable interrupts
		cli();

		// get the number of edges
		uint16_t count = edge_count;

		// reset the counters
		edge_count = 0;
		timer_overflow = 0;

		// enable interrupts
		sei();

		// output the count to the LED inidcator
		PORTC = count & 0xFF;

		// wait for 1 second
		_delay_ms(1000);
	}
}

ISR(TIMER1_COMPA_vect)
{
	// toggle on compare match
	PORTB ^= (1 << PB3);
}

ISR(TIMER1_OVF_vect)
{
	if((PINB & (1 << PB4)) && !(TIFR & (1 << TOV1)))
	{
		// increment the edge count
		edge_count++;
	}

	// toggle on overflow
	if(TIFR & (1 << TOV1))
	{
		timer_overflow = 1;
		TIFR |= (1 << TOV1);
	}
}