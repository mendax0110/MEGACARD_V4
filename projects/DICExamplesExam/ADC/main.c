/*
 * ADC.c
 *
 * Created: 17.12.2023 12:42:09
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include "LCD_4.h"

void initADC() 
{
	// Set ADC reference voltage to AVCC
	ADMUX |= (1 << REFS0);
	
	// Set ADC clock prescaler to 128 (Assuming F_CPU = 12MHz)
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	// Enable ADC
	ADCSRA |= (1 << ADEN);
}

uint16_t readADC(uint8_t channel) 
{
	// Select ADC channel (0-7 in single-ended mode)
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
	
	// Start ADC conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	
	// Return ADC result (10-bit resolution)
	return ADC;
}

void initPorts()
{
	// Set PORTB as output (for LED indication)
	DDRC |= (1 << PC0);	
	
	DDRA &= ~(1 << PA0);
	PORTA |= (1 << PA0);
}

int main(void) 
{
	initADC();
	lcd_init();
	lcd_pos(0,0);
	
	while (1) 
	{
		uint16_t adc_value = readADC(0);
		
		if (adc_value > 512) 
		{
			PORTC |= (1 << PC0); // Turn on LED connected to PB0
		} 
		else 
		{
			PORTC &= ~(1 << PC0); // Turn off LED connected to PB0
		}
		
		if(!(PINA) & (1 << PA0))
		{
			// Reset ADC
			ADCSRA &= ~(1 << ADEN); // Disable ADC
			_delay_ms(10); // Small delay for stability
			ADCSRA |= (1 << ADEN); // Enable ADC
			_delay_ms(10); // Small delay for stability
		}
		
		_delay_ms(100); // Delay for stability
		
		lcd_pos(0,1);
		printf("ADC Value: %d", adc_value);
	}
}


