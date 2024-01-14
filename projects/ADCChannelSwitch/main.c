/*
 * ADCChannelSwitch.c
 *
 * Created: 14.01.2024 17:40:32
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initPorts()
{
	DDRA &= ~(1 << PA0);
	PORTA &= ~(1 << PA0);
	
	DDRC |= 0xFF;
}

void initADC()
{
	ADCSRA |= (1 << ADSC); // start conversation
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // trigger source on
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2); // prescaler 128
	
	ADMUX |= (1 << REFS0); // ref voltage to AVCC
}

int readADC(uint8_t channel)
{
	ADMUX |= (ADMUX & 0xF0)|(channel & 0x0F); // select ADC channel
	
	while(!(ADCSRA & (1 << ADIF))); // conversation complete (wait)
	
	return ADC; // full resolution 10 bit
}

int main(void)
{
	cli(); // lock
	initADC();
	initPorts();
	sei(); // release
	
	while(1)
	{
		for(uint8_t channel = 0; channel <= 2; ++channel)
		{
			int result = readADC(channel); // read ADC, switch channels
			PORTC = result; // show results on LED's
			_delay_ms(1000); // delay wanted 1 sec
		}
	}
}
