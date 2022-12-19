/*
 * IncrementLEDBlink.c
 *
 * Created: 19.12.2022 20:26:13
 * Author : Adrian
 */ 
#define F_CPU 12000000UL        // Taktfrequenz Quarz
#include <avr/io.h>				// AVR standart IO lib
#include <util/delay.h>			// delay lib

#define BLINK_LED 100

int main(void)
{
	/*XOR function with led ATMEGA 16*/

	DDRC = 0xFF;            // Port C als Ausgang
	PORTC = 0x00;           // Port C auf 0 setzen

	while(1)
	{
		PORTC += 1;			// PORTC LED's incrementieren
		if (PORTC == 0xFF)
		{
			PORTC = 0x00;
		}
		_delay_ms(BLINK_LED);    //1 Sekunde warten
	}
}


