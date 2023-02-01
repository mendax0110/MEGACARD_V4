/*
 * ShiftInterruptBit.c
 *
 * Created: 01.02.2023 19:14:47
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// Quarz Frequency

#include <avr/io.h>			// Include AVR IO library
#include <avr/interrupt.h>	// Include AVR interrupt library
#include <avr/portpins.h>	// avr lib for pins

// Declare a volatile variable to keep track of the number of interrupts
volatile unsigned char count;

// Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	// Increment the count variable every time the interrupt is triggered
	count++;
}

int main(void)
{
	DDRD &= ~(1 << PD2);	// set PD2 as input
	PORTD |= (1 << PD2);	// Enable pull-up resistor on PD2
	GICR |= (1 << INT0);	// Enable INT0 interrupt
	MCUCR |= (1 << ISC00);	// Trigger INT0 on any logical change
	
	sei();	// Enable global interrupts
	
	while(1)
	{
		 // Check if the count variable has reached 8
		if(count >= 8)
		{
			 // If it has, set PB0 to high
			PORTB |= (1 << PB0);
			// Reset the count variable to zero
			count = 0;
		}
		else
		{
			// If the count variable has not reached 8, set PB0 to low
			PORTB &= ~(1 << PB0);
		}
		
		// Shift the value of PORTB one bit to the left, rotating the LED pattern
		PORTB = (PORTB << 1) | (PORTB >> 7);
	} 
}