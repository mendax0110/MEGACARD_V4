/*
 * TestUebung4FastPWM.c
 *
 * Created: 21.05.2023 13:01:36
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;
volatile uint8_t timer = 0;

void init_Ports()
{
	DDRC = 0xFF;
	
	DDRB |= (1 << PB3);
	
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_fast_PWM()
{
	TCCR0 |= (1 << WGM00)|(1 << COM01)|(1 << COM00)|(1 << WGM01)|(1 << CS01)|(1 << CS00);
	
	for(OCR0Var = 0; OCR0Var <= 200; OCR0Var++)
	{
		_delay_ms(10);
		PORTC ^= (1 << PC0);
		_delay_ms(10);
		PORTC ^= (1 << PC1);
		_delay_ms(10);
		PORTC ^= (1 << PC2);
		_delay_ms(10);
		PORTC ^= (1 << PC3);
		_delay_ms(10);
		PORTC ^= (1 << PC4);
		_delay_ms(10);
		PORTC ^= (1 << PC5);
		_delay_ms(10);
		PORTC ^= (1 << PC6);
		_delay_ms(10);
		PORTC ^= (1 << PC7);
		_delay_ms(10);
	}
	
	
	OCR0 = OCR0Var;
}

int main(void)
{
	cli();
	init_Ports();
	init_fast_PWM();
	sei();
	
	while(1)
	{
		if((PINA & (1 << PA0)) == 0)
		{
			for(timer = 0; timer <= 8; timer++)
			{
				_delay_ms(10);
				PORTC ^= (1 << PC0);
				_delay_ms(10);
				PORTC ^= (1 << PC2);
				_delay_ms(10);
				PORTC ^= (1 << PC4);
				_delay_ms(10);
				PORTC ^= (1 << PC6);
				_delay_ms(10);
			}
			
			OCR0 = 50;
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			for(timer = 0; timer <= 8; timer++)
			{
				_delay_ms(10);
				PORTC ^= (1 << PC1);
				_delay_ms(10);
				PORTC ^= (1 << PC3);
				_delay_ms(10);
				PORTC ^= (1 << PC5);
				_delay_ms(10);
				PORTC ^= (1 << PC7);
				_delay_ms(10);
			}
			
			OCR0 = 100;
		}
	}
}
