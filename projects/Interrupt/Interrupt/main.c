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

void init_ports() 
{
	DDRA = 0x00;						//PORTA -> Eingang
	PORTA = 0x0F;						//PORTA0 -> A1, A2, A3 -> Pullup
	
	DDRC = 0xFF;					// PORTC wird als Ausgang gesetzt
	PORTC = 0x00;					//Die oberen 4 Bits sind low, die unteren 4Bit sind High
}

int main(void)
{
	init_ports();					//Ports im main initialisieren 

	while (1)
	{
		PORTC = PINA;		//0xXF - solange keine Taste gedrückt wird
							//X..4..7 - X undefinierter Zustand
		
		PORTC = PINA & 0x0F;	// Verknüpfung 4..7 mit 0 
								// Wenn PA0 gedrückt wird-> PORTC: 0b00001110 -> 0x0E
		
		if((PINA & 0x0F) == 0x0E)	// Wenn Taste PA0 gedrückt wird -> LED3 leuchtet
		{
			PORTC = (1<<PC3);
		}
							
		_delay_ms(5000);
	}
}

