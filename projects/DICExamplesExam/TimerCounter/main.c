/*
 * TimerCounter.c
 *
 * Created: 18.12.2023 19:23:54
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t TCNTVAR = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = TCNTVAR;
}

void initPorts()
{
	DDRC = 0xFF;
	DDRB |= (1 << PB3);
	
	DDRA &= ~(1 << PA0);
	PORTA |= (1 <<PA0);
}

void initTimerCounter()
{
	 TCCR0 &= ~(1 << WGM00)|(1 << WGM01);
	 TCCR0 |= (1 << COM00)|(1 << CS01)|(1 << CS00);
	 
	for(int TCNTVAR = 0; TCNTVAR < 20; TCNTVAR++)
 	{
 		PORTC ^= (1 << PC1)|(1 << PC6);
		_delay_ms(200);
	}
	 
	 TCNT0 = TCNTVAR;
	 TIMSK |= (1 << TOIE0);
}

int main(void)
{
	cli();
	initPorts();
	initTimerCounter();
	sei();
	
    while (1) 
    {
		
		if(!(PINA & (1 << PA0)))
		{
			TCNTVAR = 0;
			initTimerCounter();
		}
    }
}

