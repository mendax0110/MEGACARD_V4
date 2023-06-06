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

volatile uint8_t seconds = 0;   // seconds counter
volatile uint8_t s0_Time = 0;   // s0 time counter
volatile unsigned char s0_Pressed = 0;  // s0 pressed flag

// timer0 overflow interrupt for counting seconds
ISR(TIMER0_COMP_vect)
{
	seconds++;
	
	if(s0_Pressed)
	{
		s0_Time++;
	}	
}

// method for initializing timer0
void init_Timer0()
{
	TCCR0 |= (1 << WGM01)|(1 << CS02)|(1 << CS00);
	
	OCR0 = 150;
	
	TIMSK |= (1 << OCIE0);
}

// method for updating the leds
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

// method for initializing the ports
void init_Ports()
{
	DDRC |= (1 << PC1)|(1 << PC2);
	
	DDRA &= ~(1 << PA1);
	
	PORTA |= (1 << PA1);
}

// main to run the program
int main(void)
{
	cli();  // disable global interrupts
	init_Ports();   // initialize the ports
	init_Timer0();  // initialize timer0
	sei();  // enable global interrupts
	
	while(1)
	{
        // check if the seconds are 5
		updates_leds();
		
        // check if the button is pressed
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