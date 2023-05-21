/*
 * TestUebung4TimerCounter.c
 *
 * Created: 21.05.2023 12:59:13
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
	
	PORTC ^= (1 << PC0);
}

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC1);
	
	DDRB |= (1 << PB3);
}

void init_Timer0()
{
	TCCR0 &= ~(1 << WGM00);
	TCCR0 &= ~(1 << WGM01);
	TCCR0 |= (1 << COM00)|(1 << CS00)|(1 << CS01);
	
	for(TCNT0Var = 0; TCNT0Var <= 245; TCNT0Var++)
	{
		_delay_ms(100);
		PORTC ^= (1 << PC2);
		_delay_ms(100);
		PORTC ^= (1 << PC3);
		_delay_ms(100);
		PORTC ^= (1 << PC4);
		_delay_ms(100);
		PORTC ^= (1 << PC5);
		_delay_ms(100);
		PORTC ^= (1 << PC6);
		_delay_ms(100);
		PORTC ^= (1 << PC7);
		_delay_ms(100);
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
