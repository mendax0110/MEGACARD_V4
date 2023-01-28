/*
 * InterruptLed.c
 *
 * Created: 28.01.2023 16:55:37
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

// toggle the LED on PC0
ISR(INT0_vect)
{
	PORTC ^= (1<<PC0);
}

int main(void)
{
	DDRC |= (1<<PC0);		// set PC0 as output
	PORTC &= ~(1 << PC0);	// turn off the LED on PC0
	MCUCR |= (1<<ISC01) | (1<<ISC00);	// set INT0 to tigger on rising edge
	GICR |= (1<<INT0);	// enable INT0 interrupt
	sei();	// enable global interrupts
	
	while(1)
	{
		
	}
}

