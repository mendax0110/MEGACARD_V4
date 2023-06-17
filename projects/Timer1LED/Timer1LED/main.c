/*
 * Timer1LED.c
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

ISR(TIMER1_CAPT_vect)
{
	ending_edge = 256 * ICR1H + ICR1L;
	clocks = ending_edge - starting_edge + Timer1Counter * 65535;
	Time = clocks / 1500; // Timer in ms (12Mhz/8) -> 1 500 000 / 1500 -> 1000Hz, das entspricht 1 ms
	Timer1Counter = 0;
	starting_edge = ending_edge;
}

ISR(TIMER0_OVF_vect)
{
	Timer1Counter++;
}

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

void initTimer1()
{
	TCCR1A = 0x00;                         // normal mode
	TCCR1B |= (1 << ICNC1) | (1 << CS11);  // prescaler 8bit, noise canceller -> 1.5Mhz -> 0.66us -> Zeiteinheit
}

void toggleLEDs()
{
	PORTC ^= 0xFF;  // Toggle all LEDs
}


int main(void)
{
	cli();
	initPorts();
	initTimer1();
	sei();

	while (1)
	{
		if (!(PINA & (1 << PA0)))  // Check if S0 button is pressed
		{
			toggleLEDs();
			_delay_ms(100);  // Debounce delay
		}
		else if (!(PINA & (1 << PA1)))  // Check if S1 button is pressed
		{
			toggleLEDs();
			_delay_ms(100);  // Debounce delay
		}
	}
}