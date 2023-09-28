/*
 * 4C.c
 *
 * Created: 21.09.2023 08:32:29
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	DDRC = 0xFF;
	
	// for S2
	DDRA &= ~(1 << PA2);
	PORTA |= (1 << PA2);
}

int main(void)
{
	initPorts();
	
	while (1)
	{
		if(!(PINA & (1 << PA2)))
		{
			PORTC |= (1 << PC7);
		}
		else
		{
			PORTC &= ~(1 << PC7);
		}
	}
}


