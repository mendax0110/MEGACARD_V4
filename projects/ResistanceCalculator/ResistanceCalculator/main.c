/*
 * ResistanceCalculator.c
 *
 * Created: 08.12.2022 11:31:44
 * Author : Adrian
 */ 
// Include the necessary libraries
#include <stdio.h>
#include <avr/io.h>

// Set the ADC prescaler to 128 to reduce the ADC clock frequency
#define ADC_PRESCALER ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

int main(void) {
	// Set the ADC prescaler bits in the ADCSRA register
	ADCSRA |= ADC_PRESCALER;
	
	// Set the ADC reference voltage to AVCC (5V)
	ADMUX |= (1 << REFS0);
	
	// Enable the ADC by setting the ADEN bit in the ADCSRA register
	ADCSRA |= (1 << ADEN);
	
	while (1) {
		// Start a conversion by setting the ADSC bit in the ADCSRA register
		ADCSRA |= (1 << ADSC);
		
		// Wait for the conversion to complete by checking the ADSC bit
		while (ADCSRA & (1 << ADSC));
		
		// Read the ADC value from the ADCH and ADCL registers and calculate the resistance
		int adc_value = ADCH << 8 | ADCL;
		float resistance = 10000.0 / (1023.0 / adc_value - 1.0);
		
		// Print the resistance value to the serial port
		printf("Resistance: %f\n", resistance);
	}
	
	return 0;
}
