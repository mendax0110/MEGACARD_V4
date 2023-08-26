/*
 * Timer1Zeitmessung.c
 *
 * Created: 15.06.2023 15:43:23
 * Author : Adrian
 */

#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

long int ending_edge = 0;
long int starting_edge = 0;
long int clocks = 0;
long int Time = 0;

volatile long int Timer1Counter = 0;

// Timer1 Input Capture Interrupt
ISR(TIMER1_CAPT_vect)
{
	ending_edge = 256 * ICR1H + ICR1L;
	clocks = ending_edge - starting_edge + Timer1Counter * 65535;
	Time = clocks / 1500; // Timer in ms (12Mhz/8) -> 1 500 000 / 1500 -> 1000Hz, das entspricht 1 ms
	Timer1Counter = 0;
	starting_edge = ending_edge;
}

// Timer0 Overflow Interrupt
ISR(TIMER0_OVF_vect)
{
	Timer1Counter++;
}

// Initialize Ports
void initPorts()
{
	DDRC |= 0xFF; // portc output
	PORTC = 0xFF; // all led dark

	DDRA &= ~(1 << PA0); // for S0
	PORTA |= (1 << PA0); // for S0

	DDRD &= ~(1 << PD6); // ICP Input Capture
	PORTD &= ~(1 << PD6); // Hi-Z, cuz connected to PA0 (Pull up)
	
	DDRC |= (1 << PC0);   // Set PC0 as output
	PORTC |= (1 << PC0);  // Set PC0 high initially
}

// Initialize Timer1
void initTimer1()
{
	TCCR1A = 0x00;                         // normal mode
	TCCR1B |= (1 << ICNC1) | (1 << CS11);  // prescaler 8bit, noise canceller -> 1.5Mhz -> 0.66us -> Zeiteinheit
}

// Main function
int main(void)
{
	cli();	// Disable global interrupts
	initPorts();	// Initialize ports
	initTimer1();	// Initialize Timer1
	sei();	// Enable global interrupts

	while (1)
	{
		if (!(PINA & (1 << PA0)))
		{
			TIMSK |= (1 << TICIE1);
			TIMSK |= (1 << TOIE0);
			PORTC ^= (1 << PC0); // Toggle PC0
			_delay_ms(500);      // Delay 500ms
		}
		else
		{
			TIMSK &= ~(1 << TICIE1);
			TIMSK &= ~(1 << TOIE0);
			PORTC |= (1 << PC0); // Set PC0 high
		}
	}
}