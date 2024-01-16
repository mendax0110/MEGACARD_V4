/*
 * ADC_Channel_Switch_012.c
 *
 * Created: 16.01.2024 20:08:28
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t adc_value = 0;

void initPorts()
{
	DDRC &= ~(1 << PA5); // use poti
	PORTA &= ~(1 << PA5);
	
	DDRC |= 0xFF; // display on LED's
}

void initADC()
{
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // auto trigger
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);  // prescaler
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2); // free running mode
	
	ADMUX |= (1 << REFS0); // AVCC ref.
	ADMUX |= (1 << ADLAR); // left 8 bit resolution
}

int main(void)
{
    initPorts();
	initADC();

	ADCSRA |= (1 << ADSC); // start meas
	
    while (1) 
    {
		ADMUX &= ~(1 << MUX0)&~(1 << MUX1)&~(1 << MUX2)&~(1 << MUX3)&~(1 << MUX4); // channel selection 0
		while(!(ADCSRA & (1 << ADIF))) {} // wait till conversation finished
		adc_value = ADCH;
		PORTC = adc_value;
		_delay_ms(1000);
		
		ADMUX |= (1 << MUX0); // channel selection 1
		while(!(ADCSRA & (1 << ADIF))){} // wait till conversation finished
		adc_value = ADCH;
		PORTC = adc_value;
		_delay_ms(1000);
		
		ADMUX |= (1 << MUX2); // channel selection 5  (would normally be channel 2 -> but to control via poti we use channel 5)
		while(!(ADCSRA & (1 << ADIF))) {} // wait till conversation finished
		adc_value = ADCH;
		PORTC = adc_value;
		_delay_ms(1000);
    }
}

