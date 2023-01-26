/*
 * Interrupt.c
 *
 * Created: 26.01.2023 10:10:41
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// Quarzfrequenz UL Unsigned Long

#include <avr/io.h>			// Library Ein/Ausgabe - Ports
#include <util/delay.h>		// Delay Library
#include <avr/portpins.h>	// Library für Port Pins

void init_ports()        //Funktion
{
	DDRC = 0xFF;        //Port C - Ausgang
	PORTC |= (1 << PC7);    //LED 7 wird gesetzt (1000 0000 -> 0x80)     DDRA = 0x00;    //PortA = Alle Pins auf Eingang
	PORTA |= (1 << PA0);    //PortA = Pullup
}
int main(void)
{
	char keyboard_in = 0x00;    //Variable vom Typ Character -> 8 Bit (1Byte)     init_ports();
	while (1)
	{
		keyboard_in = PINA; // Maskierung -> Erzwinge, dass die Bits A4 - A7 = 0 sind
		if ((keyboard_in & (0x01)) == 0x00)
		{
			PORTC = 0x01;
		}
		_delay_ms(200);
		PORTC = (1<<PC7);
	}
}

