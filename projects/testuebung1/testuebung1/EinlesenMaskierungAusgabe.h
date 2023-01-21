
/*
 * EinlesenMaskierungAusgabe.h
 *
 * Created: 18.01.2023 15:46:54
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	
	DDRC = 0b11111111;
	PORTC = 0b00000000;
	
	while(1)
	{
		PORTC = PORTA | 0b10101010;
		_delay_ms(2000);
		PORTC = ~PORTA;
		PORTA = PORTC | 0b01010101;
		_delay_ms(2000);
		PORTA = ~PORTC;
	}
}