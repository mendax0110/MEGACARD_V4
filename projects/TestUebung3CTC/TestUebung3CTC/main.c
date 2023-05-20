/*
 * TestUebung3CTC.c
 *
 * Created: 20.05.2023 13:24:35
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;
volatile uint8_t freqDiv = 0;

ISR(TIMER0_COMP_vect)
{
	freqDiv++;
	
	if(freqDiv == 78)
	{
		PORTC ^= (1 << PB0)|(1 << PB1)|(1 << PB2)|(1 << PB3)|(1 << PB4)|(1 << PB5)|(1 << PB6)|(1 << PB7);
		
		freqDiv = 10;
	}
}

void init_Ports()
{
	DDRC = 0xFF;
	DDRC |= (1 << PC7);		// inicator LED
	
	DDRB |= (1 << PB3);		// output for signal
}

void init_timer0_ctc()
{
	TCCR0 |= (1 << COM00)|(1 << WGM01)|(1 << CS02)|(1 << CS00);
	
	for(OCR0Var = 0; OCR0Var <= 78; OCR0Var++)
	{
		_delay_ms(10);
		PORTC ^= (1 << PC1);
		_delay_ms(10);
		PORTC ^= (1 << PC3);
		_delay_ms(10);
		PORTC ^= (1 << PC5);
		_delay_ms(10);
		PORTC ^= (1 << PC7);
		_delay_ms(10);
	}
	
	OCR0 = OCR0Var; // OCR = (FCPU/2*256*FOUT)+1
	// FOUT = (FCPU/2*256*(OCR+1)
	
	TCNT0 = 0;
	TIMSK |= (1 << OCIE0);
}

int main(void)
{
	cli();
	init_Ports();
	init_timer0_ctc();
	sei();
	
	while(1)
	{
		
	}
}