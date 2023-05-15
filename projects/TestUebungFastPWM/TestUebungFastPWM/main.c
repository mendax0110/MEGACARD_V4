/*
 * TestUebungFastPWM.c
 *
 * Created: 15.05.2023 20:42:19
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>

void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7);
	
	DDRB |= (1 << PB3);
	PORTB &= ~(1 << PB3);
	
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_fast_PMW()
{
	TCCR0 |= (1 << WGM00)|(1 << COM01)|(1 << WGM01)|(1 << CS01)|(1 << CS00);
	
	OCR0 = 150;
}

int main(void)
{
	cli();
	init_ports();
	init_fast_PMW();
	sei();
	
	while(1)
	{
		if((PINA & (1 << PA0)) == 0)
		{
			PORTC |= (1 << PC0);
			PORTC &= ~(1 << PC1);
			
			OCR0 = 200;
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			PORTC &= ~(1 << PC0);
			PORTC |= (1 << PC1);
			
			OCR0 = 100;
		}
		
		if(OCR0 == 200)
		{
			PORTC |= (1 << PC0);
			PORTC &= ~(1 << PC1);
		}
		else if(OCR0 == 100)
		{
			PORTC &= ~(1 << PC0);
			PORTC |= (1 << PC1);
		}
	}
}
