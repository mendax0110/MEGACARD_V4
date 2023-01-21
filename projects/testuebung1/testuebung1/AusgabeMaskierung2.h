
/*
 * AusgabeMaskierung2.h
 *
 * Created: 18.01.2023 16:29:06
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b11111111;
	PORTC = 0b00000000;
	
	PORTC = PORTC | 0b10000000;
	_delay_ms(2000);
	
	PORTC = ~(0b11111111);
	_delay_ms(2000);
	
	PORTC = PORTC | 0b00000010;
	_delay_ms(2000);
}