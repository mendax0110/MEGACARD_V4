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
volatile uint8_t running = 0; 

// 7-segment display segment patterns (0-9)
const uint8_t digitPatterns[10] = {
	0b00111111,  // 0
	0b00000110,  // 1
	0b01011011,  // 2
	0b01001111,  // 3
	0b01100110,  // 4
	0b01101101,  // 5
	0b01111101,  // 6
	0b00000111,  // 7
	0b01111111,  // 8
	0b01101111   // 9
};

void initTimer1()
{
	// Set Timer1 to CTC mode
	TCCR1B |= (1 << WGM12);

	// Set the prescaler to 64
	TCCR1B |= (1 << CS11)|(1 << CS10);

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
	
	DDRC |= (1 << PC3);

	// Set PA0 and PA1 as input with pull-up resistors
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= (1 << PA0)|(1 << PA1);
}

void toggleLED()
{
	// Toggle the state of the LED on PB2
	PORTB ^= (1 << PC3);
}

void displayDigit(uint8_t digit)
{
	// Select the digit by clearing PB3
	PORTB &= ~(1 << PB3);

	// Set the segment pattern for the corresponding digit
	PORTB = (PORTB & 0xF0) | digitPatterns[digit];

	// Delay to allow the digit to be displayed
	_delay_ms(2);

	// Disable all segments by setting PB3
	PORTB |= (1 << PB3);
}

void printTime()
{
	// Convert milliseconds to seconds and minutes
	unsigned int seconds = milliseconds / 1000;
	unsigned int minutes = seconds / 60;
	seconds %= 60;

	// Display the minutes digit
	displayDigit(minutes % 10);

	// Delay to separate the digit display
	_delay_ms(2);

	// Display the seconds digit
	displayDigit(seconds % 10);
}

ISR(TIMER1_COMPA_vect)
{
	// increment
	milliseconds++;

	// Update the time output every second if the program is running
	if (milliseconds % 1000 == 0 && running)
	{
		printTime();

		// Toggle the LED every second
		toggleLED();
	}
}

int main(void)
{
	cli();	// lock global interrupts
	initTimer1();	// init the timer
	initGPIO();		// init the ports/reg
	sei();	// release global interrupts

	while (1)
	{
		// Check the status of PA0 and PA1 buttons
		uint8_t buttonS0 = (PINA & (1 << PA0)) == 0;
		uint8_t buttonS1 = (PINA & (1 << PA1)) == 0;

		// Start the program if S0 button is pressed
		if (buttonS0)
		{
			running = 1;
			milliseconds = 0;
		}

		// Stop the program if S1 button is pressed
		if (buttonS1)
		{
			running = 0;
		}
	}
}