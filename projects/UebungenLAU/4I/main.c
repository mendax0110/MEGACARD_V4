/*
 * 4I.c
 *
 * Created: 21.09.2023 10:26:07
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	DDRC = 0xFF; // LED's
	DDRA = 0x00; // Taster als Eingänge
	
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

int main(void)
{
	initPorts();
	PORTC = 0x01; // Startposition 

	while (1)
	{
		if (!(PINA & (1 << PA0)))
		{
			PORTC <<= 1;
			
			if (PORTC == 0x00)
			PORTC = 0x01;
		}
		else if (!(PINA & (1 << PA1)))
		{
			PORTC >>= 1;
			
			if (PORTC == 0x00)
			PORTC = 0x80;
		}
		else
		{
			PORTC = 0x00;
		}

		_delay_ms(166); // Warte 166 ms / 3Hz
	}

	return 0;
}


