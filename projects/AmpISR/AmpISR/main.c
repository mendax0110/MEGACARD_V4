/*
 * AmpISR.c
 *
 * Created: 01.03.2023 19:18:08
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

// define constants
#define SAMPLE_RATE  10000  // 10kHz
#define VOLTAGE_GAIN 5.0    // 5V/V

// define variables
volatile uint16_t adc_value;
volatile double voltage_in, voltage_out;

// ISR
ISR(ADC_vect)
{
	adc_value = ADC;    // read ADC value
	voltage_in = ((double)adc_value * 5.0) / 1023.0; // convert to voltage
	voltage_out = voltage_in * VOLTAGE_GAIN; // apply gain
}

int main(void)
{
	// set up ADC
	ADMUX = (1 << REFS0);   // use AVcc as the reference
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // enable ADC, enable interrupt, set prescaler to 128

	sei();  // enable interrupts

	// set up timer
	TCCR1B |= (1 << CS10) | (1 << WGM12); // set prescaler to 1 and CTC mode
	OCR1A = F_CPU / SAMPLE_RATE - 1;    // set compare match register
	TIMSK |= (1 << OCIE1A);    // enable timer compare interrupt

	// while loop
	while (1)
	{
		// do nothing
	}
}

ISR(TIMER1_COMPA_vect)
{
	ADCSRA |= (1 << ADSC);  // start ADC conversion
}