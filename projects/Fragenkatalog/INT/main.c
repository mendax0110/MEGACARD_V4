
/*
 * INT.h
 *
 * Created: 24.05.2023 17:07:13
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

// hardware interrupt 0
ISR(INT0_vect)
{
	PORTC |= (1 << PC7);
}

// hardware interrupt 1
ISR(INT1_vect)
{
	PORTC &= ~(1 << PC7);
}

void init_Ports()
{
	DDRC = 0xFF;
	
	// set for S0 and S1
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

void init_interrupt0_1()
{
	GICR |= (1 << INT0)|(1 << INT1);	// Set int0 and int1
	MCUCR |= (1 << ISC11)|(1 << ISC01);	// set int0 and int1
}

int main(void)
{
	cli();
	init_Ports();
	init_interrupt0_1();
	sei();
	
	while(1)
	{
		// set and unset
		if((PINA & (1 << PA0)) == 0)
		{
			PORTC |= (1 << PC0);
		}
		else
		{
			PORTC &= ~(1 << PC0);
		}
		
		// set and unset
		if((PINA & (1 << PA1)) == 0)
		{
			PORTC |= (1 << PC1);
		}
		else
		{
			PORTC &= ~(1 << PC1);
		}
	}
}