/*
 * operatoren.h
 *
 * Created: 18.01.2023 14:11:40
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b11111111;	//DDRC als eingang
	PORTC = 0b10101010;
	
	_delay_ms(2000);
	
	PORTC = PORTC ^ 0b01010101;
	
	_delay_ms(2000);
	
	PORTC = PORTC & ~0b01010101;
	
	_delay_ms(2000);
	
	PORTC = PORTC | 0b01010101;
	
	_delay_ms(2000);
}