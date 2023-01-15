/*
 * EinlesenMaskierung.h
 *
 * Created: 15.01.2023 12:44:05
 *  Author: Adrian
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b00000000;
	DDRC = 0b11111111;
	
	while(1)
	{
		PINA &= 0b00000011;
		
		PINA &= ~(0b00000100) & ~(0b00000000);
		
		PORTC = PINA;
	}
}