/*
 * ADC.c
 *
 * Created: 06.12.2022 20:16:12
 * Author : Adrian
 */ 
#define F_CPU 12000000UL
#include <util/delay.h> 
#include <avr/io.h>
#include <stdio.h>

// Set the baud rate of the serial port to 9600 bps
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (BAUD * 16UL)) - 1)

// Function to initialize the USART module
void usart_init()
{
	// Set the baud rate
	UBRRH = (uint8_t)(UBRR_VALUE >> 8);
	UBRRL = (uint8_t)UBRR_VALUE;

	// Set the USART to 8-bit, 1 stop bit, no parity
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);

	// Enable the transmitter and receiver
	UCSRB = (1 << RXEN) | (1 << TXEN);
}

// Function to write a character to the serial port
void usart_write(char c)
{
	// Wait for the transmitter to be ready
	while (!(UCSRA & (1 << UDRE)));

	// Write the character to the USART data register
	UDR = c;
}

// Function to read a character from the serial port
char usart_read()
{
	// Wait for a character to be available
	while (!(UCSRA & (1 << RXC)));

	// Return the character from the USART data register
	return UDR;
}

int main()
{
	// Initialize the USART module
	usart_init();

	// Set the ADC prescaler to 128, which sets the ADC clock to 125 kHz
	// This is within the recommended range of 50-200 kHz for the ATMEGA16A
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	// Set the ADC reference voltage to AVCC (5 V)
	ADMUX |= (1 << REFS0);

	// Enable the ADC
	ADCSRA |= (1 << ADEN);

	while (1)
	{
		// Start the next conversion
		ADCSRA |= (1 << ADSC);

		// Wait for the conversion to complete
		while (ADCSRA & (1 << ADSC));

		// The ADC value is now stored in the ADC register
		uint16_t adc_value = ADC;

		// Use printf to output the ADC value to the serial port
		printf("ADC value: %d\n", adc_value);

		// Wait 1 second before starting the next conversion
		_delay_ms(1000);
	}

	return 0;
}
