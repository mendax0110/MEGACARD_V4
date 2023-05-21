/*
 * TestUebung4CTC.c
 *
 * Created: 21.05.2023 13:00:14
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;
volatile uint8_t Timer = 0;

ISR(TIMER0_COMP_vect)
{
	OCR0 = OCR0Var;
}

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC7);
	
	DDRB |= (1 << PB3);

	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_Timer0_CTC()
{
	TCCR0 |= (1 << WGM01)|(1 << COM00)|(1 << CS00)|(1 << CS02);
	
	for(OCR0Var = 0; OCR0Var <= 100; OCR0Var++)
	{
		_delay_ms(10);
		PORTC ^= (1 << PC6);
		_delay_ms(10);
		PORTC ^= (1 << PC5);
		_delay_ms(10);
		PORTC ^= (1 << PC4);
		_delay_ms(10);
		PORTC ^= (1 << PC3);
		_delay_ms(10);
		PORTC ^= (1 << PC2);
		_delay_ms(10);
		PORTC ^= (1 << PC1);
		_delay_ms(10);
		PORTC ^= (1 << PC0);
		_delay_ms(10);
	}
	
	OCR0 = OCR0Var;		// OCR = F_CPU/(2*256*F_OUT)+1 = 234 or 235
	// F_OUT = F_CPU/(2*256*OCR+1) = 100
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
		if((PINA & (1 << PA0)) == 0)
		{
			PORTC ^= (1 << PC0)|(1 << PC1)|(1 << PC2)|(1 << PC3)|(1 << PC4)|(1 << PC5)|(1 << PC6)|(1 << PC7);
			OCR0Var = 200;
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			for(Timer = 0; Timer <= 8; Timer++)
			{
				_delay_ms(100);
				PORTC ^= (1 << PC7);
				_delay_ms(100);
				PORTC ^= (1 << PC6);
				_delay_ms(100);
				PORTC ^= (1 << PC5);
				_delay_ms(100);
				PORTC ^= (1 << PC4);
				_delay_ms(100);
				PORTC ^= (1 << PC3);
				_delay_ms(100);
				PORTC ^= (1 << PC2);
				_delay_ms(100);
				PORTC ^= (1 << PC1);
				_delay_ms(100);
				PORTC ^= (1 << PC0);
				_delay_ms(100);
			}
			
			OCR0Var = 50;
		}
	}
}