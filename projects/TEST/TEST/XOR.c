/*
 * XOR.c
 *
 * Created: 12.11.2022 18:53:52
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL        //Taktfrequenz Quarz
#include <avr/io.h>				//Headerdatei für I/O-Register
#include <util/delay.h>			//Headerdatei für _delay_ms

int main(void)
{
	/*XOR function with led ATMEGA 16*/

	DDRC = 0xFF;            //Port B als Ausgang
	PORTC = 0x00;           //Port B auf 0 setzen

	while(1)
	{
		PORTC ^= 0xFF;      //Port B invertieren
		_delay_ms(1000);    //1 Sekunde warten

		PORTC = ~PORTC;     //Port B invertieren
		_delay_ms(1000);    //1 Sekunde warten
	}
}
