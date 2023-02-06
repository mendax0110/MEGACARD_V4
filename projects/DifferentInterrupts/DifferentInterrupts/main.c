/*
 * DifferentInterrupts.c
 *
 * Created: 06.02.2023 19:17:53
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>


// function prototypes for interrupt service routines
ISR(INT0_vect)
ISR(TIMER0_OVF_vect);
ISR(ADC_vect);

// Interrupt service routine for INT0
ISR(INT0_vect)
{
	
}

// Interrupt service routine Timero overflow
ISR(TIMER0_OVF_vect)
{
	
}

// Interrupt service routine for ADC conversion complete
ISR(ADC_vect)
{
	
}

int main(void)
{
	// Configure INT0 as falling edge interrupt
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	MCUCR |= (1 << ISC01)|(1 << ISC00);
	GICR |= (1 << INT0);
	
	// Configure Timer0 overflow interrupt
	TCCR0 |= (1 << CS01)|(1 << CS00);
	TIMSK |= (1 << TOIE0);
	
	// Configure ADC conversion complete interrupt
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN)|(1 << ADIE)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
	ADCSRA |= (1 << ADSC);
	
	// Enable global interrupts
	sei();
	
	while(1)
	{
		// Main prog
	}
}


