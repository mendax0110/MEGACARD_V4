/*
 * Beispiel_01.c
 *
 * Created: 13.10.2022 16:01:01
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	//define the CPU frequency
#include <avr/io.h>			//default lib AVR
#include <util/delay.h>		//delay lib add delay time

// main module
int main(void) 
{
	DDRC=0xFF;  //LED-Port: Output
	PORTC=0x00; //shut off all LED's(default)
	while(1)
	{
		PORTC++;		//LED-Status increment
		_delay_ms(500);	//wait 500ms 
	}
}


