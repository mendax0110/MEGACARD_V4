/*
 * Timer1Zeitmessung.c
 *
 * Created: 15.06.2023 15:43:23
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

ISR(TIMER1_CAPT_vect)
{
		
}

void initPorts()
{
	DDRC |= 0xFF;	// portc output
	PORTC = 0xFF;	// all led dark
		
	DDRA &= ~(1 << PA0);	// for S0
	PORTA |= (1 << PA0);	// for S0
	
	DDRD &= ~(1 << PD6);	// ICP Input Capture
	PORTD &= ~(1 << PD6);	// Hi-Z, cuz connected to PA0 (Pull up)
}

void initTimer1()
{
	TCCR1A = 0x00;						// normal mode
	TCCR1B |= (1 << ICNC1)|(1 << CS11);	// prescaler 8bit, noise canceller -> 1.5Mhz -> 0.66us -> Zeiteinheit	
}

int main(void)
{
	cli();
	initPorts();
	initTimer1();
	sei();
    
    while (1) 
    {
    }
}

