/*
 * ADCFreeRunningMode.c
 *
 * Created: 14.01.2024 17:10:41
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t ADC_value = 0;

void initPorts()
{
	DDRA &= ~(1 << PA0);
	PORTA &= ~(1 << PA0);
	
	DDRC |= 0xFF;
	PORTC |= (1 << PC7);
}

void initADC()
{
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // tigger source on
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2); // Prescaler 128 -> Teilung fck/128 -> clk 93,75
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2);
	
	ADMUX |= (1 << MUX0); // set channel 0
	ADMUX |= (1 << REFS0); // ser external ref for voltage AVCC
	ADMUX |= (1 << ADLAR); //  presentation of the bits in the ADC reg
}

int main(void)
{
	cli();
	initPorts();
	initADC();
	sei();
	
	ADCSRA |= (1 << ADSC); //start meas- free running mode
	
	while(1)
	{
		while(ADCSRA & (1 << ADIF))
		{
			ADC_value = ADCH;
			PORTC = ADC_value;
		}
	}
}

