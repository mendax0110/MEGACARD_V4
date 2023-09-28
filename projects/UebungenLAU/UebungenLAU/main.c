/*
 * UebungenLAU.c
 *
 * Created: 21.09.2023 08:17:52
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

void initPorts()
{
	// Konfiguriere PortA als Eingang mit Pull-up-Widerständen
	DDRA = 0x00; // Alle Pins von PortA als Eingang
	PORTA = 0xFF; // Aktiviere Pull-up-Widerstände für alle Pins von PortA
}

int main(void)
{
    initPorts();
	
    while (1) 
    {
		uint8_t buttonState = PINA;

		
		PORTC = buttonState;

		
		_delay_ms(100);
    }
}



