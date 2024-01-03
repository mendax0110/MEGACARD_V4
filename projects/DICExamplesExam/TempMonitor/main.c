/*
 * TempMonitor.c
 *
 * Created: 02.01.2024 09:33:51
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "LCD_4.h"

volatile uint8_t ADC_value = 0;

void initADC()
{
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3); // ADC0 input
	ADCSRA |= (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
}

void initPorts()
{
	DDRB |= (1 << PB3);
	DDRC = 0xFF;
	PORTC &= 0x00;
}

void initTimer1()
{
	TCCR1A |= (1 << COM1A1)|(1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	
	ICR1 = 0xFF;
}

void startConversation()
{
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
}

int main(void)
{
	initPorts();
	initADC();
	initTimer1();
	lcd_init();
	
	while(1)
	{
		startConversation();
		
		ADC_value = ADC;
		
		uint16_t temp_adc = ADC_value;
		uint8_t temp = (temp_adc * 100) / 1023;

		lcd_pos(0,0);
		printf("TEMP: %d C ", temp);

		if (temp < 25) 
		{
			PORTC |= (1 << PC2) | (1 << PC4);
		} 
		else if (temp >= 25 && temp < 50) 
		{
			PORTC |= (1 << PC1);
		} 
		else 
		{
			PORTC |= (1 << PC0);
		}
	}
}