/*
 * 1_Aufgabe d.c
 *
 * Created: 19.10.2023 09:31:58
 * Author : Nutzer
 */ 

#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(TIMER0_OVF_vect)	//fISR= F_CPU -> 12000000HZ
{
	PORTC^=0x01;
	TCNT0 += 135; // vorladen des TCNT0-Wertes	(255-120)Hz
}


void init()
{
	DDRC|=0xFF;		//LEDs
	PORTC=0;
	DDRA&=0xF0;		//Taster
	PORTA|=0x0F;	//Pullup
	
	TCCR0|=1<<CS00;
	TIMSK|=1<<TOIE0;
	TCNT0 += 135;
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