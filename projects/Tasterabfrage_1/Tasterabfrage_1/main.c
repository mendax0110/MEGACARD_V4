/*
 * Taster.c
 *
 * Created: 01.12.2022 15:47:00
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL	// Systemtakt bereits in Project-Properties definiert
#include <util/delay.h>    // Delay-Funktionen einbinden
#include <avr/io.h>

init_ports(){
	DDRC |= 0xFF;	// PORTC - Ausgang
	PORTC |= 0x80;	// LED 7 wird gesetzt (1000 0000 -> 0x80)
	
	DDRA = 0x00;	// PORT A -> alle Pins auf Eingang	
	PORTA = 0xFF;	// alle PORTA -> Pullup
}

int main(void)
{
	char keyboard_in;	// Variable vom Typ character -> 8 Bit (1Byte)
	
	init_ports();
	
	while(1)
	{
        keyboard_in = PINA;	// Tastaturstatus wird in Variable gespeichert
        if(keyboard_in == 0xFE){	// wenn Taster 1 gedrückt
            PORTC = PORTC << 1;	// LED 7 wird ausgeschaltet
        }
	}
}