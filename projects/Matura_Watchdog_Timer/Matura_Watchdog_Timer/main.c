/*
 * Matura_Watchdog_Timer.c
 *
 * Created: 06.08.2025 12:12:27
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/portpins.h>
#include <avr/wdt.h>
#include <util/delay.h>

uint8_t wdt_reset_happened = 0; // global reset erkennungs flag 

void init_watchdog()
{
	wdt_enable(WDTO_500MS); // setze watchdog mit 500ms timeout
}

void init_ports()
{
	DDRC |= 0xFF; // alle Pins PORT auf Ausgang
	PORTC = 0x00; // LED's ausschalten
}

void show_watchog_reset()
{
	// zeige pattern mit alle LED's aus und alle LED's ein
	for (uint8_t i = 0; i < 3; i++)
	{
		PORTC = 0xFF;
		_delay_ms(200);
		PORTC = 0x00;
		_delay_ms(200);
	}
}

int main(void)
{
	uint8_t counter = 0; // interner counter für LED lauflicht
	
	// Überprüfen ob Reset Uhrsache
	if (MCUCSR & (1 << WDRF))
	{
		wdt_reset_happened = 1; // reset war erfolgreich
	}
	MCUCSR = 0; // reset flags löschen
	
	init_watchdog();
	init_ports();
	
    while (1) 
    {
		if (wdt_reset_happened)
		{
			show_watchog_reset();
			wdt_reset_happened = 0;
			counter = 0;
		}
		
		PORTC = (1 << counter); // LED lauflicht shift
		
		// Solange lauflicht noch nicht am Ende -> Watchdog zurücksetzen
		if (counter < 7)
		{
			wdt_reset();
			counter++;
		}
		else
		{
			// kein Reset -> nach 500ms Reset wird ausgelöst
			while(1);
		}

		_delay_ms(300);
    }
}

