/*
 * 1_Aufgabe e.c
 *
 * Created: 19.10.2023 10:21:44
 * Author : Bonelli
 */ 

#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(TIMER0_COMP_vect)	//overflow durch vect ersezten -> CTC Mode
{
	PORTC^=0x01;
	
}


void init()
{
	DDRC|=0xFF;		//LEDs
	PORTC=0;
	DDRA&=0xF0;		//Taster
	PORTA|=0x0F;	//Pullup
	
	TCCR0|=1<<CS00 | 1<< WGM01;
	
	TIMSK|=1<<OCIE0;
	OCR0 = 120 - 1; // grenze setzen durch ORC0
}

int main(void)
{
	init();
	sei();
	while (1)
	{
	}
	return 0;
}

