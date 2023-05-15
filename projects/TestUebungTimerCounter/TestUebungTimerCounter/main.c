/*
 * TestUebungTimerCounter.c
 *
 * Created: 15.05.2023 20:39:32
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 200;
	PORTC ^= (1 << PC3);
}

void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7);	// LED inidcator
	
	DDRB |= (1 << PB3);
}

void init_timer0()
{
	TCCR0 &= ~(WGM00);								// normal mode
	TCCR0 &= ~(WGM01);
	TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);	// Toggle OCR0
	
	TCNT0 = 200;
	TIMSK |= (1 << TOIE0);
}


int main(void)
{
	cli();
	init_ports();
	init_timer0();
	sei();
	
	while(1)
	{
		
	}
}