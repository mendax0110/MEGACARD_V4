/*
 * TestUebung3TimerCounter.c
 *
 * Created: 20.05.2023 13:23:26
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t TCNT0Var = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNT0Var;
	
	PORTC ^= (1 << PC7);
}

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC6);	// inicator LED for init Ports
	
	DDRB |= (1 << PB3);
}

void init_Timer0()
{
	TCCR0 &= ~(1 << WGM00);		// normal mode
	TCCR0 &= ~(1 << WGM01);
	TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);	// toggle mode
	
	
	for(TCNT0Var = 0; TCNT0Var <= 10; TCNT0Var++)
	{
		_delay_ms(500);
		PORTC ^= (1 << PC5);	// inidcator LED for ISR
		_delay_ms(500);
		PORTC ^= (1 << PC4);
		_delay_ms(500);
		PORTC ^= (1 << PC3);
		_delay_ms(500);
		PORTC ^= (1 << PC2);
		_delay_ms(500);
		PORTC ^= (1 << PC1);
		_delay_ms(500);
		PORTC ^= (1 << PC0);
	}
	
	TCNT0 = TCNT0Var;
	TIMSK |= (1 << TOIE0);
}

int main(void)
{
	cli();
	init_Ports();
	init_Timer0();
	sei();
	
	while(1)
	{
		
	}
}