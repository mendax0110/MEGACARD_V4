/*
 * Patterns.c
 *
 * Created: 29.12.2022 15:59:08
 * Author : Adrian
 */ 
#define  F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK 500
#define NUM_PATTERNS 5

const int patterns[NUM_PATTERNS][8] = {
	{1, 0, 1, 0, 1, 0, 1, 0}, // pattern 1
	{0, 1, 1, 0, 0, 1, 1, 0}, // pattern 2
	{1, 1, 0, 0, 1, 1, 0, 0}, // pattern 3
	{0, 0, 0, 1, 1, 1, 1, 0}, // pattern 4
	{1, 0, 0, 1, 0, 1, 0, 1}, // pattern 5
};

int main(void)
{
	DDRC = 0xFF;	// set PORTC as output
	PORTC = 0x00;	// clear PORTC
	DDRA = 0x00;	// set PORTA as input
	PORTA = 0xFF;	// enable pull-up resistors on PORTA
	
	int current_pattern = 0;	// index of the current pattern
	
	while(1)
	{
		// check if button 1 is pressed
		if(!(PINA & 0x01))
		{
			// move to the previous pattern
			current_pattern = (current_pattern - 1 + NUM_PATTERNS) % NUM_PATTERNS;
		}
		
		// check if button 2 is pressed
		if(!(PINA & 0x02))
		{
			// move to the next pattern
			current_pattern = (current_pattern + 1) % NUM_PATTERNS;
		}
		
		// convert the pattern to an unsigned char
		unsigned char pattern = 0;
		
		for(int i = 0; i < 8; i++)
		{
			pattern |= (patterns[current_pattern][i] << i);
		}
		
		// display the current pattern
		PORTC = pattern;
		_delay_ms(BLINK);
	}
}