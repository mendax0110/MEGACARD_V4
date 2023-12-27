/*
 * AdcTimerLedDisplay.c
 *
 * Created: 25.12.2023 15:00:05
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD_4.h"

volatile uint8_t value = 0;
volatile uint8_t TCNTVAR = 0;
volatile uint8_t counter = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNTVAR;
	
	if(!(PINA & (1 << PA1)))
	{
		TCNTVAR = 0;
		initTimer0();
	}
}

ISR(TIMER1_COMPA_vect)
{
	OCR0 = counter;
	
	if(!(PINA & (1 << PA0)))
	{
		counter = 0;
		initTimer1();
	}
}

void initTimer1()
{
	TCCR1A |= (1 << COM1A1)|(1 << WGM11)|(1 << WGM10);
	TCCR1B |= (1 << WGM12)|(1 << CS11);
	
	for(counter = 0; counter < 127; counter++)
	{
		_delay_ms(200);
		lcd_pos(0,0);
		printf("PWM: %u ", counter);
		_delay_ms(200);
	}
	
	OCR1A = counter;
	
	DDRB |= (1 << PB3);
}

void initTimer0()
{
	lcd_init();
	TCCR0 &= ~(1 << WGM00)|(1 << WGM01);
	TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);
	 
	for(int TCNTVAR = 0; TCNTVAR < 20; TCNTVAR++)
	{
		_delay_ms(200);
		lcd_pos(1,0);
		printf("Timer0 Count: %d", TCNTVAR);
		_delay_ms(200);
	}
	 
	TCNT0 = TCNTVAR;
	TIMSK |= (1 << TOIE0);
}

void initPorts()
{
	DDRA &= ~(1 << PA5);	// set with and neg because of voltage measurment -> potentiometer Megacard (inout)
	PORTA &= ~(1 << PA5);	// set high-z
	
	DDRA &= ~(1 << PA1)|(1 << PA0);
	PORTA |= (1 << PA1)|(1 << PA0);
	
	DDRC |= 0xFF;		// indicator LED
	PORTC |= 0x00;
}

void initADC()	// now without return type, later with return type  
{
	ADCSRA |= (1 << ADEN);	// enable ADC
	ADCSRA |= (1 << ADATE);	// Trigger Source on
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);	// Prescaler 128 -> Teilung fck/128 -> clk for ADC = 93,75 kHz
	
	SFIOR &= ~(1 << ADTS0)&~(1 << ADTS1)&~(1 << ADTS2); // Free running mode
	
	ADMUX |= (1 << MUX0)|(1 << MUX2);	// Channel 5 set on on the multiplexer -> ADC Poti
	ADMUX |= (1 << REFS0);	// external reference for voltage AVCC
	
	ADMUX |= (1 << ADLAR);	// presentation of bits in the ADC Data Register
}

void displayLEDsBasedOnADC(uint8_t adcValue) 
{
	if (adcValue < 64) 
	{
		PORTC = (1 << PC6)|(1 << PC4);
	} 
	else if (adcValue < 128) 
	{
		PORTC = (1 << PC1)|(1 << PC2)|(1 << PC7);
	} 
	else if (adcValue < 192) 
	{
		PORTC = (1 << PC1)|(1 << PC2)|(1 << PC6);
	} 
	else 
	{
		PORTC = 0x00;
	}
}

int main(void)
{
	cli();
    initPorts();
	initADC();
	initTimer0();
	initTimer1();
	lcd_init();
	sei();
	
	ADCSRA |= (1 << ADSC); // Start the ADC Measurment one time, for free running mode!
	
    while (1) 
    {
		while((ADCSRA & (1 << ADIF)))
		{
			value = ADCH;
			
			displayLEDsBasedOnADC(value);
			
			lcd_pos(0,0);
			printf("ADC-VALUE: %d" ,value);
		} // wait till measurment finished
    }
}