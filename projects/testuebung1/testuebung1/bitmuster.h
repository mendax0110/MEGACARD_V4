
/*
 * bitmuster.h
 *
 * Created: 18.01.2023 15:37:29
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b11111111;	//DDRC als eingang
	PORTC = 0b00000000;	//PORTC als ausgang
	
	while(1)
	{
		PORTC = PORTC ^ 0b10101010;	// bit 7,5,3,1 ein
		_delay_ms(2000);
		
		PORTC = PORTC | 0b01010101; // bit 6,4,2,0 ein
		_delay_ms(2000);
		
		PORTC = ~PORTC;	// alle bit aus
		_delay_ms(2000);
		
	}
}