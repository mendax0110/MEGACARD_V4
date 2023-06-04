/*
 * Clock.c
 *
 * Created: 04.06.2023 17:10:35
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t seconds = 0;
volatile uint8_t s0_Time = 0;
volatile unsigned char s0_Pressed = 0;

ISR(TIMER0_COMP_vect)
{
	seconds++;
	
	if(s0_Pressed)
	{
		s0_Time++;
	}	
}

void init_Timer0()
{
	TCCR0 |= (1 << WGM01)|(1 << CS02)|(1 << CS00);
	
	OCR0 = 150;
	
	TIMSK |= (1 << OCIE0);
}

void updates_leds()
{
	if(s0_Pressed)
	{
		PORTC |= (1 << PC1);
	}
	else
	{
		PORTC |= (1 << PC2);
	}
}

void init_Ports()
{
	DDRC |= (1 << PC1)|(1 << PC2);
	
	DDRA &= ~(1 << PA1);
	
	PORTA |= (1 << PA1);
}

int main(void)
{
	cli();
	init_Ports();
	init_Timer0();
	sei();
	
	while(1)
	{
		updates_leds();
		
		if(!(PINA & (1 << PA1)))
		{
			s0_Pressed = 1;
		}
		else
		{
			s0_Pressed = 0;
		}
	}
}