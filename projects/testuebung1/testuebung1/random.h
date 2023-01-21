
/*
 * random.h
 *
 * Created: 21.01.2023 09:11:43
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL	// frequenz einstellen

#include <avr/io.h>		// standard AVR Input Output Library
#include <util/delay.h>	// verzögerungs library

int main(void)
{
	DDRA = 0b00000000;	// DDRA als eingang
	PORTA = 0b11111111; // PORTA auf HI-Z
	
	DDRC = 0b11111111; // DDRC als ausgang
	PORTC = 0b00000000; // PORTC als low
	
	while(1)
	{
		if(!(PINA & 0x01))		// wenn taster PA0 gedrück
		{
			PORTC = PORTC | 0b00000011;		// wird hier bit 0 und bit 1 betrachet und der rest nicht
			_delay_ms(2000);
		}
	}
}