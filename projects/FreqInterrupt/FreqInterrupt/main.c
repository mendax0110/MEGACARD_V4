/*
 * FreqInterrupt.c
 *
 * Created: 13.02.2023 19:24:06
 * Author : Adrian
 */ 
#define F_CPU 12000000UL // max freq

#include <avr/io.h>
#include <avr/interrupt.h>	
#include <avr/portpins.h>

volatile unsigned long frequency = 0;	// current freq

// ISR for timer/counter0 overflow interrupt
ISR(TIMER0_OVF_vect)
{
	frequency += 1000;	// increase freq by 1000Hz
	
	if(frequency > F_CPU)
	{
		frequency = 0;	// reset freq if it exceed the max
	}
}

int main(void)
{
	// set timer/counter0 to overflow at F_CPU/256
	TCCR0 = (1 << CS02);
	TCNT0 = 0;	// init timer/counter
	
	// enable timer/counter overflow interrupt
	TIMSK = (1 << TOIE0);
	
	// enable global interrupt
	sei();
	
	while (1)
	{
		
	}
}
