/*
 * DICExamplesExam.c
 *
 * Created: 17.12.2023 10:08:12
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t timerOverflowCount = 0;

ISR(TIMER0_OVF_vect)
{
	timerOverflowCount++;
}

void initTimer0()
{
	TCCR0 |= (1 << CS00)|(1 << CS02);	//prescaler 1024
	TIMSK |= (1 << TOIE0); // Timer0 OV aktiv
	TCNT0 = 0; // startwert timer 0
}

void initPorts()
{
	DDRC |= 0xFF;
	
	DDRA &= ~(1 << PA0)|(1 << PA1)|(1 << PA2)|(1 << PA3);
	PORTA |= (1 << PA0)|(1 << PA1)|(1 << PA2)|(1 << PA3);
}

int main(void)
{
	cli();
	initPorts();
	initTimer0();
	sei();
	
    while (1) 
    {	
		if(!(PINA & (1 << PA0)))
		{
			PORTC ^= (1 << PC0)|(1 << PC2)|(1 << PC4)|(1 << PC6);
		}

		
		if(!(PINA & (1 << PA1)))
		{
			PORTC ^= (1 << PC1)|(1 << PC3)|(1 << PC5)|(1 << PC7);
		}
		
		if(!(PINA & (1 << PA2)))
		{
			for(int i = 0; i < 10; i++)
			{
				PORTC ^= (1 << PC1)|(1 << PC3)|(1 << PC5)|(1 << PC7);
				_delay_ms(200);			
			}
		}
		
		if(!(PINA & (1 << PA3)))
		{
			if(timerOverflowCount >= 100)
			{
				PORTC ^= (1 << PC0) | (1 << PC2) | (1 << PC4) | (1 << PC6);
				timerOverflowCount = 0;			
			}	
		}
    }
}

