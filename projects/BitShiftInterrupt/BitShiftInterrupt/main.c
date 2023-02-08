/*
 * BitShiftInterrupt.c
 *
 * Created: 08.02.2023 17:54:21
 * Author : Adrian
 */ 
#define  F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h
#include <avr/portpins.h>

volatile uint8_t shift_count = 0;

ISR(INT1_vect)
{
	shift_count++;
}

int main(void)
{
	DDRD &= ~(1 << PD3);	// set PD3 as input
	PORTD |= (1 << PD3);	// enable Pull-Up resistor on PD3
	MCUCR |= (1 << ISC10);	// trigger interrupt on rising edge
	GICR |= (1 << INT1);	// enable external interrupt on INT1
	
	sei();	// enable global interrupts
	
	while(1)
	{
		uint8_t input_value = PIND;
		
		input_value = (input_value >> shift_count) & 1;
	}
	
}
