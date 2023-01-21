/*
 * ADCWinSerial.c
 *
 * Created: 05.01.2023 15:32:58
 * Author : Adrian
 */ 
#define __AVR_ATmega15A__
// This line specifies that the code is intended for the ATmega15A microcontroller.

#define F_CPU 12000000UL
// Define the frequency of the microcontroller's clock as 12 MHz.

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
// Include necessary libraries for AVR microcontroller, delay functions, and standard input/output.

#define BAUD 9600
// Define the baud rate for USART communication as 9600.

#define UBBR_VALUE ((F_CPU)/(BAUD*16UL)-1)
// Calculate the value for the baud rate register based on the F_CPU and BAUD constants.

/*init the USART*/
void USART_init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)(ubrr);
	UCSRB = (1<<TXEN);
	// Set the baud rate for USART communication and enable the transmitter.
}

/*send the data over USART*/
int USART_send(char c, FILE *stream)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = c;
	return 0;
	// Wait for the UART Data Register Empty (UDRE) flag to be set before sending the data.
}

/*main function*/
int main(void)
{
	USART_init(UBBR_VALUE);
	stdout = fdevopen(USART_send, NULL);
	// Initialize the USART communication and redirect standard output to the USART_send function.
	
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(7<<ADPS0);
	// Set the reference voltage for the ADC and enable the ADC module with a prescaler of 128.
	
	char buffer[10];
	// Declare a buffer to store the formatted voltage value as a string.
	
	/*loop through*/
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		uint16_t voltage = ADC;
		// Start a conversion and wait for it to complete. Store the result in the voltage variable.
		
		float volts = (voltage * 5.0) / 1024.0;
		// Calculate the voltage in volts by multiplying the digital value by 5 and dividing by 1024.
		
		sprintf(buffer, "%.2f\n", volts);
		printf("%s", buffer);
		_delay_ms(1000);
		// Format the voltage value as a string with 2 decimal places, print it over the USART and wait for 1000ms.
	}
	return 0;
}
