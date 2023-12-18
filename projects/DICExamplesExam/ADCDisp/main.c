/*
 * ADCDisp.c
 *
 * Created: 18.12.2023 21:36:16
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/portpins.h>
#include "LCD_4.h"

void initPorts() 
{
	DDRC = 0xFF;
	DDRB |= (1 << PB3);
	DDRA &= ~((1 << PA0) | (1 << PA1));
	PORTA |= (1 << PA0) | (1 << PA1);
}

void initADC() 
{
	ADMUX |= (1 << REFS1) | (1 << REFS0);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
}

uint16_t readADC(uint8_t channel) 
{
	ADMUX &= 0xF8;
	ADMUX |= (channel & 0x07);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}


int main(void) 
{
	initPorts();
	initADC();
	lcd_init();

	while (1) 
	{
		uint16_t adcValue = readADC(0);
		
		if (!(PINA & (1 << PA0)) && adcValue > 0) 
		{
			adcValue--;
			lcd_pos(0,0);
			printf("ADC: %d  ", (uint8_t)adcValue);
		}

		if (!(PINA & (1 << PA1))) 
		{
			adcValue++;
			lcd_pos(0,0);
			printf("ADC: %d  ", (uint8_t)adcValue);
		}

		PORTC = (uint8_t)adcValue;
		_delay_ms(100);
		lcd_pos(0,0);
		printf("ADC: %d  ", (uint8_t)adcValue);
	}

	return 0;
}

