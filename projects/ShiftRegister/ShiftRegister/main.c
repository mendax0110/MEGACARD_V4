/*
 * ShiftRegister.c
 *
 * Created: 04.01.2023 10:35:39
 * Author : Adrian
 */ 
#define F_CPU 120000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define DATA_PIN PB0
#define CLOCK_PIN PB1
#define LATCH_PIN PB2

int main(void)
{
	// Set DATA_PIN, CLOCK_PIN and LATCH_PIN as outputs
	DDRB |= (1 << DATA_PIN) | (1 << CLOCK_PIN) | (1 << LATCH_PIN);
	
	// Set the data to be shifted out
	uint8_t data = 0b10101010;
	
	// Shift out the data, one bit at a time
	for(int i = 0; i < 8; i++)
	{
		// Set the value of the DATA_PIN to the value of the current bit
		if(data & (1 << i))
		{
			PORTB |= (1 << DATA_PIN);
		}
		else
		{
			PORTB &= ~(1 << DATA_PIN);
		}
		
		// Toggle the CLOCK_PIN to shift the data
		PORTB |= (1 << CLOCK_PIN);
		_delay_us(1);
		PORTB &= (1 << CLOCK_PIN);
		_delay_us(1);
	}
	
	// Toggle the LATCH_PIN to output the data to the shift register
	PORTB |= (1 << LATCH_PIN);
	_delay_us(1);
	PORTB &= (1 << LATCH_PIN);
	
	// Print the output to the serial port
	for(int i = 0; i < 8; i++)
	{
		if(PINB & (1 << PINB3))
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		_delay_us(1);
		PORTB |= (1 << CLOCK_PIN);
		_delay_us(1);
		PORTB &= (1 << CLOCK_PIN);
		_delay_us(1);
	}
	
	return 0;
}