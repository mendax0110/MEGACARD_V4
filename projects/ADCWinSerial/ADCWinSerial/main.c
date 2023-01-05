/*
 * ADCWinSerial.c
 *
 * Created: 05.01.2023 15:32:58
 * Author : Adrian
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUD 9600
#define UBBR_VALUE ((F_CPU)/(BAUD*16UL)-1)

void USART_init(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)(ubrr);
	UCSRB = (1<<TXEN);
}

int USART_send(char c, FILE *stream)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = c;
	return 0;
}

int main(void)
{
	USART_init(UBBR_VALUE);
	stdout = fdevopen(USART_send, NULL);
	
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADEN)|(7<<ADPS0);
	
	char buffer[10];
	
	while(1)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		uint16_t voltage = ADC;
		float volts = (voltage * 5.0) / 1024.0;
		sprintf(buffer, "%.2f\n", volts);
		printf("%s", buffer);
		_delay_ms(1000);
	}
	
	return 0;
}

