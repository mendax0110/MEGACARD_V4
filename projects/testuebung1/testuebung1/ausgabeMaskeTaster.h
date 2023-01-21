/*
 * EinlesenMaskierung.h
 *
 * Created: 18.01.2023 13:51:49
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b00000000;	// DDRA als eingang
	PORTA = 0b11111111;
	
	DDRC = 0b11111111; // DDRC als ausgang
	PORTC = 0b00000000;
	
	
	while(1)
	{
		if(!(PINA & 0x01))
		{
			PORTC |= 0b00000011;
		}
		if(!(PINA & 0x02))
		{
			PORTC = PORTC & 0b00000000;
		}
	}
}
