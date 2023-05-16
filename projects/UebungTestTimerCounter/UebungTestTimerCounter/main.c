/*
 * UebungTestTimerCounter.c
 *
 * Created: 16.05.2023 20:19:50
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t TCNT0Var = 0;
volatile uint8_t i = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNT0Var;
	
	for(TCNT0Var = 0; TCNT0Var <= 200;)
	{
		TCNT0Var++;
		_delay_ms(100);
	}
	
	for(i = 0; i <= 7;)
	{
		PORTC ^= (1 << PC0);
		_delay_ms(500);
		PORTC ^= (1 << PC1);
		_delay_ms(500);
		PORTC ^= (1 << PC2);
		_delay_ms(500);
		PORTC ^= (1 << PC3);
		_delay_ms(500);
		PORTC ^= (1 << PC4);
		_delay_ms(500);
		PORTC ^= (1 << PC5);
		_delay_ms(500);
		PORTC ^= (1 << PC6);
		_delay_ms(500);
		PORTC ^= (1 << PC7);
		_delay_ms(500);
		
	}
}

void init_Ports()
{
	DDRC = 0xFF;
	
	DDRB |= (1 << PB3);
}

void init_timer0()
{
	TCCR0 &= ~(WGM00);
	TCCR0 &= ~(WGM01);
	TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);
	
	TCNT0 = TCNT0Var;
	TIMSK |= (1 << TOIE0);
}

int main(void)
{
	cli();
	init_Ports();
	init_timer0();
	sei();
	
	while(1)
	{
	}
}
