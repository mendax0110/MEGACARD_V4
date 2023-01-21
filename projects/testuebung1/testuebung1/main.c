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

/*--------------------------------------------------------------------------------*/

#define F_CPU 12000000UL	// frequenz einstellen

#include <avr/io.h>			// standard AVR Input Output Library
#include <util/delay.h>		// verzögerungs library

int main(void)
{
	DDRC = 0b11111111;	// DDRC als Ausgang
	PORTC = 0b00000000; // PORTC HI-Z
	
	
	PORTC = PORTC | 0b10000000; // mit oder bit 7 ein alle anderen aus
	_delay_ms(2000);
	
	PORTC = PORTC & 0b00000000; // alle bits aus mit (UND)
	_delay_ms(2000);
	
	PORTC = PORTC | 0b00000010; // bit 1 ein, alle anderen aus (OR)
	_delay_ms(2000);
	
	PORTC = PORTC ^ 0b00000010; // bit 1 ein alle anderen aus (XOR)
	_delay_ms(2000);
	
	while(1)
	{
	}
}

/*--------------------------------------------------------------------------------*/

#define F_CPU 12000000UL	// Frequenz einstellen (Quarz)

#include <avr/io.h>			// Standard Input/Ouput AVR Library
#include <util/delay.h>		// Library um delays also Verzögerungen einstellen

int main(void)
{
	DDRC = 0b111111111;		// DDRC als Ausgang
	PORTC = 0b11110000;		// bit 7,6,5,4  Hi-Z, 3,2,1,0 low
	
	_delay_ms(2000);		// Verzögerung 2 Sekunden
	
	PORTC = ~(PORTC & 0b00001111);	// NAND um 7,6,5,4,3,2,1, 0 ein
	_delay_ms(2000);		// Verzögerung 2 Sekunden
	
	while(1)
	{
		
	}
}


int main(void)
{
	DDRA = 0b00000000;	// DDRA als eingang
	PORTA = 0b11111111;
	
	DDRC = 0b11111111; // DDRC als ausgang
	PORTC = 0b00000000;
	
	while(1)
	{
		PORTC = PINA & 0b00000011;
	}
}