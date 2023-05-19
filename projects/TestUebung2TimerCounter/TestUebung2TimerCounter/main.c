/*
 * TestUebung2TimerCounter.c
 *
 * Created: 19.05.2023 11:05:52
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t TCNT0Var = 245;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNT0Var;
}

void init_Ports()
{
	TCCR0 &= ~(1 << WGM00);	// Normal Mode
	TCCR0 &= ~(1 << WGM01);	
	TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);	// Toggle OC0
	
	TCNT0 = TCNT0Var;
	TIMSK |= (1 << TOIE0);
}

void init_Timer0()
{
	DDRC = 0xFF;			// Output
	PORTC ^= (1 << PC1);	// Indicator LED init timer0
	
	DDRB |= (1 << PB3);		// OC0 Ouput Toggle
	
	for(TCNT0Var = 245; TCNT0Var >= 100; TCNT0Var--)
	{
		_delay_ms(250);
		
		if(TCNT0Var >= 100)
		{
			PORTC ^= (1 << PC0);	// Indicator LED init ISR Timer0_OVF_vect
		}
	}
}

int main(void)
{
    cli();
	init_Ports();
	init_Timer0();
	sei();
	
    while (1) 
    {
    }
}

