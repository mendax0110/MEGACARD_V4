/*
 * TestUebungCTC.c
 *
 * Created: 15.05.2023 20:40:53
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t freqDiv = 0;

ISR(TIMER0_COMP_vect)
{
	freqDiv++;
	
	if(freqDiv == 20)
	{
		PORTC ^= (1 << PB7);
		PORTC ^= (1 << PB6);
		PORTC ^= (1 << PB5);
		PORTC ^= (1 << PB4);
		PORTC ^= (1 << PB3);
		PORTC ^= (1 << PB2);
		PORTC ^= (1 << PB1);
		PORTC ^= (1 << PB0);
		
		freqDiv = 5;
	}
}

void init_ports()
{
	DDRC |= (1 << PC7)|(1 << PC6)|(1 << PC5)|(1 << PC4)|(1 << PC3)|(1 << PC2)|(1 << PC1)|(1 << PC0);

	DDRB |= (1 << PB3);
}

void init_timer0_ctc()
{
	TCCR0 |= (1 << COM00)|(1 << WGM01)|(1 << CS02)|(1 << CS00);
	OCR0 = 58;
	TCNT0 = 0;
	TIMSK |= (1 << OCIE0);
}


int main(void)
{
	cli();
	init_ports();
	init_timer0_ctc();
	sei();
	
	while(1)
	{
		
	}
}
