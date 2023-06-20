/*
* Timer1SerialOutput.c
*
* Created: 20.06.2023 20:55:20
* Author : Adrian
*/
#define F_CPU 120000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include <stdio.h>

volatile unsigned int milliseconds = 0;

void initTimer1()
{
	// Set Timer1 to CTC mode
	TCCR1B |= (1 << WGM12);

	// Set the prescaler to 64
	TCCR1B |= (1 << CS11) | (1 << CS10);

	// Set the compare match value for 1ms interrupt
	OCR1A = 250;

	// Enable Timer1 compare match A interrupt
	TIMSK |= (1 << OCIE1A);

	// Enable global interrupts
	sei();
}

void initGPIO()
{
	// Set PB3 as output
	DDRB |= (1 << PB3);
}

void printTime()
{
	// Convert milliseconds to seconds and minutes
	unsigned int seconds = milliseconds / 1000;
	unsigned int minutes = seconds / 60;
	seconds %= 60;

	// Print the time output
	printf("%02u:%02u\r", minutes, seconds);
	fflush(stdout);
}

ISR(TIMER1_COMPA_vect)
{
	milliseconds++;

	// Update the time output every second
	if (milliseconds % 1000 == 0)
	{
		printTime();
	}
}

int main(void)
{
	cli();
	initTimer1();
	initGPIO();
	sei();
	
	while (1)
	{
	
	}
}
