/*
 * SignalerzeugungCTC.c
 * Timer0_CTC_Mode
 *
 * Created: 20.04.2023 15:40:16
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t freqDivider = 0; // max 356

// ISR for the timer0
ISR(TIMER0_COMP_vect)
{
	freqDivider++; // with every run increment +1
	
	if(freqDivider == 10)
	{
		PORTC ^= (1 << PC7);	// toggle LED7	
		freqDivider = 0;		// Reset
	}
}

// init the ports
void init_ports()
{
	DDRC |= (1 << PC7);		// LED 7 for Output LED		-> Info in ATMEGA16.PDF
	DDRB |= (1 << PB3);		// OC0 - for Output Signal  -> Info in ATMEGA16.PDF
}

// init the timer0 in CTC mode
void init_timer0_CTC()
{
	TCCR0 |= (1 << COM00)|(1 << WGM01)|(1 << CS02)|(1<< CS00);		// (Info in ATMEGA16.PF S.129) Toggle-Mode, CTC-Mode 2, Clock division prescaler 1024
	OCR0 = 57; 	// look at the calcuations -> Calculations CTC (fout = fcpu/(2*(OCR0+1)*Vorteiler)
	TCNT0 = 0;	// reset the timer
	TIMSK |= (1 << OCIE0);	// enable the interrupt
}

// main, init and loop
int main(void)
{
	cli();				// interrupt lock
	init_ports();		// init the ports
	init_timer0_CTC();	// init CTC
	sei();				// interrupt release
	
    while (1) 
    {
		// nothing to do
    }
}