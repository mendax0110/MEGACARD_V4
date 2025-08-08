/*
 * Matura_ADC_LCD.c
 *
 * Created: 05.08.2025 13:04:55
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t value = 0;

void init_ports()
{
	DDRA &= ~(1 << PA5); // set neg voltage meas
	PORTA &= ~(1 << PA5); // set high-z
	
	DDRC |= 0xFF;	// indicator LED
	PORTC |= (1 << PC7);
}

void init_ADC()
{
	ADCSRA |= (1 << ADEN); // enable ADC
	ADCSRA |= (1 << ADATE); // trigger source on
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // prescaler 128 -> teilung fck/128 = ADC 93.75 khz
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2); // free running mode
	
	ADMUX |= (1 << MUX0) | (1 << MUX2); // chennel 5 set on the mux
	ADMUX |= (1 << REFS0); // external volt ref
	ADMUX |= (1 << ADLAR); // presenation of bits in ADC reg
}

int main(void)
{
    cli();
	init_ports();
	init_ADC();
	sei();
	
	ADCSRA |= (1 << ADSC); // start meas, freerunning mode!
    while (1) 
    {
		// wait unitl meas is finished
		while ((ADCSRA & (1 << ADIF)))
		{
			value = ADCH;
			PORTC = value;
		}
    }
}

