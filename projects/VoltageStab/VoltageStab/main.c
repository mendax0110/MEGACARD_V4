/*
 * VoltageStab.c
 *
 * Created: 16.02.2023 13:57:58
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

volatile uint16_t voltage = 0; // Global variable to store the voltage
volatile uint16_t reference_voltage = 5000; // Desired voltage in millivolts

// Interrupt service routine for ADC conversion complete
ISR(ADC_vect)
{
	voltage = ADC * 5000 / 1023; // Convert the ADC value to millivolts
	uint16_t error = reference_voltage - voltage; // Calculate the error
	int16_t correction = error / 10; // Calculate the correction
	OCR1A = OCR1A + correction; // Apply the correction
}

int main(void)
{
	// set up ADC for single ended input on PC0
	ADMUX = (1 << REFS0); // AVcc as reference
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, interrupt, prescaler 128

	// set up Timer/Counter1 for Fast PWM mdoe with OCR1A as top
	DDRB |= (1 << PB1);     // set OC1A as output
	TCCR1A = (1 << COM1A1) | (1 << WGM11); // Clear OC1A on compare match, set OC1A at TOP, fast PWM mode
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); // Fast PWM mode, prescaler 1
	ICR1 = 9999; // Set TOP to 9999
	OCR1A = 4999; // Set initial duty cycle to 50%

	sei(); // Enable global interrupts

	ADCSRA |= (1 << ADSC); // Start ADC conversion

	while (1)
	{
		// Do nothing
	}

	return 0;
}