/*
 * TestUebung2CTC.c
 *
 * Created: 19.05.2023 11:46:46
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;	// 77 or 78
volatile uint8_t timer = 0;

ISR(TIMER0_COMP_vect)
{
	
}

void init_Ports()
{
	DDRC = 0xFF;
	PORTC ^= (1 << PC0);		// Indicator LED
	
	DDRB |= (1 << PB3);		// Ouput for signal	
}

void init_Timer0_CTC()
{
	TCCR0 |= (1 << COM00)|(1 << WGM01)|(1 << CS02)|(1 << CS00);
	
	// OCR = (F_CPU/(2*Vorteilerwert*F_OUT) -1 = (12Mhz/(2*256*300)-1) = 77,125
	
	for(timer = 0; timer <= 10; timer++)
	{
		_delay_ms(1000);
		OCR0Var = 77;
		PORTC ^= (1 << PC1);
	}
	
	OCR0 = OCR0Var;
	TCNT0 = 0;
	TIMSK |= (1 << OCIE0);
}

int main(void)
{
    cli();
	init_Ports();
	init_Timer0_CTC();
	sei();
	
	// we have F_CPU 12 Mhz and Fout 300 Hz, we need OCR
	// we want to know the Fout,  (F_CPU/(2*256*77)+1
    while (1) 
    {
    }
}

