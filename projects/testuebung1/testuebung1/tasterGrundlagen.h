
/*
 * tasterGrundlagen.h
 *
 * Created: 18.01.2023 15:23:23
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC = 0b11111111;
	PORTC = 0b00000000;	//PORTC als ausgang
	
	DDRA = 0b00000000;
	PORTA = 0b11111111;
	
	char keyboard_in;
	
	while(1)
	{
		keyboard_in = PINA;
		
		PORTC = keyboard_in;
		
		_delay_ms(100);
	}
}