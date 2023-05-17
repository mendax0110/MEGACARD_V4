/*
 * TestUebungenFastPWM.c
 *
 * Created: 17.05.2023 19:04:07
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;

void init_ports()
{
	DDRC = 0xFF;
	PORTC |= (1 << PC7);
	
	DDRB |= (1 << PB3);
	PORTB &= ~(1 << PB3);
}

void init_fast_PMW()
{
	TCCR0 |= (1 << WGM00)|(1 << COM01)|(1 << WGM01)|(1 << CS01)|(1 << CS00);
	
	OCR0 = OCR0Var;	
}

void increaseOCR0()
{
	for(OCR0Var = 0; OCR0Var <= 7; OCR0Var++)
	{
		_delay_ms(500);
		if(OCR0Var == 1)
		{
			PORTC |= (1 << PC0);
		}
		else if(OCR0Var == 2)
		{
			PORTC |= (1 << PC1);
		}
		else if(OCR0Var == 3)
		{
			PORTC |= (1 << PC2);
		}
		else if(OCR0Var == 4)
		{
			PORTC |= (1 << PC3);
		}
		else if(OCR0Var == 5)
		{
			PORTC |= (1 << PC4);
		}
		else if(OCR0Var == 6)
		{
			PORTC |= (1 << PC5);
		}
	}
	
	OCR0 = OCR0Var;
}

void decreaseOCR0()
{
	for(OCR0Var = 7; OCR0Var >= 0; OCR0Var--)
	{
		_delay_ms(500);
		if(OCR0Var == 0)
		{
			PORTC &= ~(1 << PC6);
		}
		else if(OCR0Var == 1)
		{
			PORTC &= ~(1 << PC5);
		}
		else if(OCR0Var == 2)
		{
			PORTC &= ~(1 << PC4);
		}
		else if(OCR0Var == 3)
		{
			PORTC &= ~(1 << PC3);
		}
		else if(OCR0Var == 4)
		{
			PORTC &= ~(1 << PC2);
		}
		else if(OCR0Var == 5)
		{
			PORTC &= ~(1 << PC1);
		}
		else if(OCR0Var == 6)
		{
			PORTC &= ~(1 << PC0);
		}
	}
}

int main(void)
{
	cli();
	init_ports();
	increaseOCR0();
	init_fast_PMW();
	decreaseOCR0();
	sei();
	
	while(1)
	{
		
	}
}