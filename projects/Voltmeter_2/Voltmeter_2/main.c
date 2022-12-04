/*
 * Voltmeter_2.c
 *
 * Created: 04.12.2022 13:02:56
 * Author : Adrian
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT PORTB
#define LED_DDR DDRB

// ADC input channel
#define ADC_CHANNEL 0

// Reference voltage (in volts)
#define REF_VOLTAGE 5.0

// Resolution of the ADC (in bits)
#define ADC_RESOLUTION 10

// Calculate the voltage conversion factor
#define VOLT_FACTOR (REF_VOLTAGE / (1 << ADC_RESOLUTION))

void adc_init(void)
{
	// Set the ADC input channel as an input
	DDRB &= ~(1 << ADC_CHANNEL);

	// Enable the ADC and set the clock prescaler
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);

	// Set the ADC reference voltage to AVcc
	ADMUX = (1 << REFS0);
}

// Read the ADC value on the specified channel
uint16_t adc_read(uint8_t channel)
{
	// Set the ADC input channel
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Start a single conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC))
	;

	// Return the ADC value
	return ADC;
}

int main(void)
{
	// Initialize the ADC
	adc_init();

	// Set the LED as an output
	LED_DDR = 0xFF;

	// Continuously read the ADC value and display it on the LED
	while (1)
	{
		// Read the ADC value
		uint16_t adc_value = adc_read(ADC_CHANNEL);

		// Calculate the voltage
		float voltage = adc_value * VOLT_FACTOR;

		// Display the voltage on the LED
		LED_PORT = voltage;

		// Wait for a short period of time
		_delay_ms(100);
	}
}
