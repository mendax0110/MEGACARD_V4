/*
 * lauflichtButton.h
 *
 * Created: 18.01.2023 16:05:22
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b11111111;
	PORTB = 0b00000000;
	
	DDRC = 0b11111111;
	PORTC = 0b00000000;
	
	char keyboard_in;
	
	while(keyboard_in = PINA1)
	{
		PORTC = PORTB | 0b00000001;
		_delay_ms(2000);
		PORTC = PORTB | 0b00000010;
		_delay_ms(2000);
		PORTC = PORTB | 0b00000100;
		_delay_ms(2000);
		PORTC = PORTB | 0b00001000;
		_delay_ms(2000);
		PORTC = PORTB | 0b00010000;
		_delay_ms(2000);
		PORTC = PORTB | 0b00100000;
		_delay_ms(2000);
		PORTC = PORTB | 0b01000000;
		_delay_ms(2000);
		PORTC = PORTB | 0b10000000;
		_delay_ms(2000);
	}
}