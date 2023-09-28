/*
 * 4A.c
 *
 * Created: 21.09.2023 08:42:09
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

void initPorts()
{
	DDRC=0xFF;
	DDRA = 0x00;
}

int main(void)
{
	initPorts();
	
	while (1)
	{
		uint8_t buttonState = PINA;

		PORTC = buttonState;
	}
}

