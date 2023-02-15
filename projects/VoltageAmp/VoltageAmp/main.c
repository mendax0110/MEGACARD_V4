/*
 * VoltageAmp.c
 *
 * Created: 15.02.2023 11:29:29
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

volatile uint16_t input_voltage = 0;
volatile uint16_t output_voltage = 0;

// ISR for timer1 overflow
ISR(TIMER1_OVF_vect)
{
	uint16_t base_voltage = input_voltage / 2;
	uint16_t collector_voltage = 512 - base_voltage;
	output_voltage = collector_voltage * 2;
}

int main(void)
{
	// init I/O ports
	DDRA = 0xFF;		// set all pins of PORTA as output
	
	// init Timer1 for interrupt generation
	TCCR1A = 0x00;		// normale mode
	TCCR1B = 0x04;		// clk/256 prescaler
	TIMSK = 0x04;		// enable timer1 overflow interrupt
	
	// enable global interrupt
	sei();
	
	while(1)
	{
		// read the intput voltage from ADC
		ADCSRA = (1 << ADEN)|(1 << ADSC)|(1 << ADPS2)|(1 << ADIE);	// enable ADC, start conversion, set prescaler to 16, enable interrupt
		
		while(ADCSRA & (1 << ADSC));	// wait for conversion to complete
		
		input_voltage = ADC;	// store the ADC result in input_value
		
		// update the output voltage
		PORTA = output_voltage >> 2;
	}
}