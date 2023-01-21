/*
 * testuebung1.c
 *
 * Created: 18.01.2023 13:08:27
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b11111111;
	PORTC = 0b10000000;
	
	_delay_ms(2000);
	
	PORTC = PORTC & 0b00000000;
	
	_delay_ms(2000);
	
	PORTC |= 0b00000010;
}