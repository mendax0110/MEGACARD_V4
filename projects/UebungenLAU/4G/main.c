/*
 * 4G.c
 *
 * Created: 21.09.2023 09:38:42
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	DDRC |= 0xFF;
	DDRA |= 0xFF;
	
	PORTC &= 0x00;
	PORTA &= 0x00;
	
	PORTA |= (1 << PA4)|(1 << PA5);
	PORTC |= (1 << PC4)|(1 << PC3)|(1 << PC1);
}

int main(void)
{
	initPorts();
	
	while(1)
	{
		// do smth
	}
}
