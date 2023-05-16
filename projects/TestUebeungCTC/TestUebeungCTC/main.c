/*
 * TestUebeungCTC.c
 *
 * Created: 16.05.2023 20:54:23
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t divider = 0;
volatile uint8_t OCR0Var = 0;

ISR(TIMER0_COMP_vect)
{
	for(divider = 0; divider <= 10; divider++)
	{
		if(divider == 10)
		{
			PORTC ^= (1 << PC0);
			_delay_ms(500);
			PORTC ^= (1 << PC1);
			_delay_ms(500);
			PORTC ^= (1 << PC2);
			_delay_ms(500);
			PORTC ^= (1 << PC3);
			_delay_ms(500);
		}
	}
}

void init_Ports()
{
	DDRC = 0xFF;
	
	DDRB |= (1 << PB3);
}

void init_Timer0_CTC()
{
	TCCR0 |= (1 << COM00)|(1 << WGM01)|(1 << CS01)|(1 << CS00);
	OCR0 = OCR0Var;
	
	for(OCR0Var = 0; OCR0Var <= 58; OCR0Var++)
	{
		_delay_ms(10);
	}
	
	TCNT0 = 0;
	TIMSK |= (1 << OCIE0);
}

int main(void)
{
	cli();
	init_Ports();
	init_Timer0_CTC();
	sei();
	
	while(1)
	{
		
	}
}