/*
 * 1_Aufgabe c.c
 *
 * Created: 19.10.2023 09:12:27
 * Author : Nutzer
 */ 

#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(TIMER0_OVF_vect)	//fISR= F_CPU -> 12000000HZ
{
	static unsigned int cnt=0;
	cnt++;
	if (cnt>=47)		//f= 12Mhz/(TOP*cnt) = 12MHz/(256*4687)= ca. 10Hz; toggelt bei 10Hz, Periodendauer 5Hz
	{
		cnt=0;
		PORTC^=0x01;
	}
}


void init()
{
	DDRC|=0xFF;		//LEDs
	PORTC=0;
	DDRA&=0xF0;		//Taster
	PORTA|=0x0F;	//Pullup
	
	TCCR0|=1<<CS00;
	TIMSK|=1<<TOIE0;
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

