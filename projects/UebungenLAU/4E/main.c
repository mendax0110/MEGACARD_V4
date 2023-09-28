/*
 * 4E.c
 *
 * Created: 21.09.2023 09:25:20
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>
#include <stdbool.h>

void initPorts()
{
	DDRC = 0xFF;
	
	DDRA &= ~(1 << PA0);
	PORTA |= (1 << PA0);
}

int main(void)
{
	initPorts();
	
	bool buttonState = false;
	bool lastButtonState = false;
	
	while (1)
	{
		buttonState = PINA & (1 << PA0);

		if (!lastButtonState && buttonState)
		{
			PORTC ^= (1 << PC5);
		}

		lastButtonState = buttonState;
	}
}
