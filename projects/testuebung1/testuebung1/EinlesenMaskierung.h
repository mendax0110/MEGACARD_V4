
/*
 * EinlesenMaskierung.h
 *
 * Created: 18.01.2023 13:51:49
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0b00000000;	// DDRA als ausgang
	PORTA = 0b11111111;
	
	DDRC = 0b11111111; // DDRC als eingang
	PORTC = 0b00000000;
	
	PORTC = (PORTA & 0b00000011); // Daten ein porta ausgelesen und an portc ausgeeben (nur bit 0 und bit 1)
}