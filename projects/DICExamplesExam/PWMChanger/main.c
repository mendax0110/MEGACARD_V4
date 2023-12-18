/*
 * PWMChanger.c
 *
 * Created: 18.12.2023 20:48:37
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include "LCD_4.h"

void init_ports()
{
	DDRC = 0xFF;
	
	DDRB |= (1 << PB3);
	PORTB &= ~(1 << PB3);
	
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_fast_PMW()
{
	TCCR0 |= (1 << WGM00)|(1 << WGM01);
	TCCR0 |= (1 << CS01)|(1 << CS00);
	TCCR0 |= (1 << COM01);
	
	OCR0 = 0;
}

int main(void)
{
	cli();
	init_ports();
	init_fast_PMW();
	lcd_init();
	sei();
	
	while(1)
	{
		if(!(PINA & (1 << PA0)))
		{
			PORTC |= (1 << PC0);
			PORTC &= ~(1 << PC1);
			
			OCR0 += 10;
			lcd_pos(0,0);
			printf("OCR0: %d", OCR0);
		}
		else if(!(PINA & (1 << PA1)))
		{
			PORTC &= ~(1 << PC0);
			PORTC |= (1 << PC1);
			
			OCR0 -= 10;
			lcd_pos(0,0);
			printf("OCR0: %d", OCR0);
		}
	}
}

