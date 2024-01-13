/*
 * ADCFan.c
 *
 * Created: 13.01.2024 21:29:29
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#include "LCD_4.h"

#define MIN 100
#define MAX 600
#define ADC_MAX 1023

volatile uint8_t value = 0;

void initPorts() 
{
	DDRA &= ~(1 << PA5);
	PORTA &= ~(1 << PA5);
	DDRC |= 0xFF;
	DDRB |= (1 << PB3);
}

void initADC() 
{
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2);
	
	ADMUX |= (1 << MUX0)|(1 << MUX2);
	ADMUX |= (1 << REFS0);
	
	ADMUX |= (1 << ADLAR);
}

void initPWM() 
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
}

void setFanSpeed(uint16_t speed) 
{
	uint16_t new_pos = (speed * (MAX - MIN) / ADC_MAX) + MIN;
	OCR0 = new_pos;
}

int main(void) 
{
	cli();
	initPorts();
	initADC();
	initPWM();
	lcd_init();
	sei();
	
	ADCSRA |= (1 << ADSC);

	while (1) 
	{	
		while ((ADCSRA & (1 << ADIF)))
		{
			value = ADC;
			PORTC = value;
			setFanSpeed(value);
			lcd_pos(0,0);
			printf("ADC: %d", value);
			lcd_pos(1,0);
			printf("OCR: %d", OCR0);
		}
	}
}
