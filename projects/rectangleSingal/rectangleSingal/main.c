/*
 * rectangleSignal.c
 *
 * Created: 09.03.2023 15:51:41
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0xFF - (255 * OCR0) / 100;
	PORTB ^= (1<<PB3);
}

void init_timer0()
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01);	// Fast PWM Mode
	TCCR0 |= (1 << COM01);					// Clear OC0 on compare match, set OC0 at BOTTOM
	TCCR0 |= (1 << CS02) | (1 << CS00);		// F_CPU: 1024
	
	OCR0 = 25;								// 25% duty cycle
	TCNT0 = 0xFF - (255 * OCR0) / 100;		// set initial timer value
	TIMSK |= (1 << TOIE0);					// Overflow Interrupts enabled
}

void init_ports()
{
	DDRB = (1 << PB3);		// PB3 - Ausgang Toggle
}

int main(void)
{	
	cli();			// lock	
	init_ports();	// init the ports
	init_timer0();	// init the timer
	sei();			// enable global interrupts
	
	while (1) 
	{
		// cycle through different duty cycles
		OCR0 = 25;
		_delay_ms(1000);
		OCR0 = 50;
		_delay_ms(1000);
		OCR0 = 75;
		_delay_ms(1000);
	}
}

