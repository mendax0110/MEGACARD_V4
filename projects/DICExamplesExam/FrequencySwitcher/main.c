/*
 * FrequencySwitcher.c
 *
 * Created: 18.12.2023 19:54:58
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "LCD_4.h"

volatile uint8_t OCR0Var = 0;

void initPorts() 
{
	DDRC = 0xFF;
	DDRB |= (1 << PB3);
	
	DDRA &= ~(1 << PA0)|(1 << PA1);
	PORTA |= (1 << PA0)|(1 << PA1);
}

void initTimer0() 
{
	TCCR0 |= (1 << COM00);
	TCCR0 |= (1 << WGM01);
	TCCR0 |= (1 << CS02); // prescaler 256
	TIMSK |= (1 << OCIE0); // Enable Timer0 compare match interrupt
	
	TCNT0 = 0;
	OCR0 = 0; // Set initial OCR0 value
	
	sei(); // Enable global interrupts
}

ISR(TIMER0_COMP_vect) 
{
	if(!(PINA & (1 << PA0))) 
	{
		OCR0Var = 38;	// 600 hz
		OCR0 = OCR0Var;
		PORTC ^= (1 << PC0);
	}
	
	if(!(PINA & (1 << PA1))) 
	{
		OCR0Var = 78;	// 300 Hz
		OCR0 = OCR0Var;
		PORTC ^= (1 << PC1);
	}
}

int main(void)
{
	initPorts();
	initTimer0();
	lcd_init();
	
	while (1)
	{
		if (OCR0Var == 78)
		{
			PORTC |= (1 << PC3);
			PORTC |= (1 << PC0);
			_delay_ms(2000);
			PORTC &= ~(1 << PC0);
			_delay_ms(2000);
			
			PORTC |= (1 << PC0);
			_delay_ms(2000);
			PORTC &= ~(1 << PC0);
			_delay_ms(2000);
		}
		
		if (OCR0Var == 38)
		{
			PORTC |= (1 << PC6);
			PORTC |= (1 << PC0);
			_delay_ms(2000);
			PORTC &= ~(1 << PC0);
			_delay_ms(2000);
					
			PORTC |= (1 << PC0);
			_delay_ms(2000);
			PORTC &= ~(1 << PC0);
			_delay_ms(2000);
		}
		
		lcd_pos(0,0);
		printf("OCR0-Value: %d", OCR0Var);
	}
}
