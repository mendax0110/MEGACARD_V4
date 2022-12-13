/*
 * AnalogDigitalConverter.c
 *
 * Created: 13.12.2022 18:49:34
 * Author : Adrian
 */ 
#include <avr/io.h>

// Function prototypes
void initADC();
uint16_t readADC(uint8_t channel);
void serial_output(uint16_t value);

int main()
{
	// Initialize ADC
	initADC();

	// Loop indefinitely
	while (1)
	{
		// Read ADC value on channel 0
		uint16_t adc_value = readADC(0);

		// Output ADC value over serial
		serial_output(adc_value);
	}

	return 0;
}

// Initializes ADC
void initADC()
{
	// Set ADC reference voltage to AVCC
	ADMUX |= (1 << REFS0);

	// Set ADC prescaler to 128
	// This sets the ADC clock to 125kHz
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Enable ADC
	ADCSRA |= (1 << ADEN);
}

// Reads a value from the specified ADC channel
uint16_t readADC(uint8_t channel)
{
	// Set the ADC channel
	ADMUX |= (channel & 0x0F);

	// Start a conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Return the ADC value
	return ADC;
}

// Outputs the specified value over serial
void serial_output(uint16_t value)
{
	// First, you need to wait until the UDR (data register) is empty
	// This is indicated by the UDRE (data register empty) flag in the
	// UCSRA (USART control and status register A)
	while(!(UCSRA & (1 << UDRE)));

	// Once the data register is empty, you can load the value into the UDR
	// and it will be sent over the serial connection
	UDR = value;
}
