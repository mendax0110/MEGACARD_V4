/*
 * TEST.c
 *
 * Created: 04.11.2022 11:32:37
 * Author : Adrian
 */ 

#define F_CPU 12000000UL        //Taktfrequenz Quarz
#include <avr/io.h>
#include <util/delay.h>            // Verzoegerungen

int main(void)
{
	
	DDRC = 0b11111111;			//Data Direction Register C - 1-> Ausgang
	PORTC = 0b00001111;        //LED 0 bis 3 - leuchten/ LED 4 bis 7 sind dunkel
	
	_delay_ms(2000);
	
	DDRC = 0b11111110;
	
	_delay_ms(2000);
	
	DDRC = 0b00001111;        //oberen 4 Bit des Ports -> Eingang
							 //unteren 4 Bit des Ports -> Ausgang
	_delay_ms(2000);
	PORTC = PORTC & 0b00000100;     //Bit 0 wird gelöscht
									//LED 0 wird abgeschalten
	_delay_ms(2000);
	PORTC = PORTC | 0b100000000;	//Bit 7 wird gesetzt
									//LED wird zusätzlich eingeschaltet
	_delay_ms(2000);
	DDRC |= 0b10000000;				//Oberstes Bit PC
	
	while (1)
	{
	}
}
