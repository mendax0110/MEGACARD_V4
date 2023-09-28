/*
 * 4D.c
 *
 * Created: 21.09.2023 08:37:20
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	DDRC = 0xFF;
	
	// for S2 and S1
	DDRA &= ~((1 << PA2)|(1 << PA1));
	PORTA |= ((1 << PA2)|(1 << PA1));
}

int main(void)
{
	initPorts();
	
	while (1)
	{
		if(!(PINA & (1 << PA2)))
		{
			PORTC |= (1 << PC6);
		}
		else if(!(PINA & (1 << PA1)))
		{
			PORTC &= ~(1 << PC6);
		}
	}
}