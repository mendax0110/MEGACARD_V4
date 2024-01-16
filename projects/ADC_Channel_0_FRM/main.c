/*
 * ADC_Channel_0_FRM.c
 *
 * Created: 16.01.2024 19:21:23
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

volatile uint8_t adc_value = 0;

void initPorts()
{
	//DDRA &= ~(1 << PA0); // no poti
	//PORTA &= ~(1 << PA0);
	
	DDRA &= ~(1 << PA5); // poti
	PORTA &= ~(1 << PA5);
	
	DDRC |= 0xFF;
}

void initADC()
{
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // auto triggger enable
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2); // prescaler 128 , 12Mhz/128 = 93750 Hz
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2); // free running mode
	
	ADMUX |= (1 << ADLAR); // left 8bit resolution
	ADMUX |= (1 << REFS0); // AVCC ref.
	//ADMUX &= ~(1 << MUX0)&~(1 << MUX1)&~(1 << MUX2)&~(1 << MUX3)&~(1 << MUX4); // set ADC0
	ADMUX |= (1 << MUX0)|(1 << MUX2); // using with potentiometer
}

int main(void)
{
    initPorts();
	initADC();
	
	ADCSRA |= (1 << ADSC); // start meas
	
    while (1) 
    {
		while(!(ADCSRA & (1 << ADIF))) {} // wait till converstion is finished
		
		adc_value = ADCH;	// assign 8bit value to var
		PORTC = adc_value; // show value of 
    }
}

