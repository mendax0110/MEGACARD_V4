/*
 * erster_test.c
 *
 * Created: 06.10.2022 16:08:20
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	//Systemtakt bereits in Project-Properties definiert
#include <util/delay.h>    //Delay-Funktionen einbinden
#include <avr/io.h>

#define TASTER PA0		//verwendeten Taster definieren:
#define T_PRELL 20 //Entprellzeit f�r Taster in ms

int main(void)
{
	//Konfiguration der I/O-Ports:
	DDRA=0x00;  //Tasterport: Eingang (default)
	PORTA=0x0F; //Pullups f?r Taster S0,1,2,3 aktivieren
	DDRC=0xFF;  //LED-Port: Ausgang
	PORTC=0x01; //LED0 ein, LED1...7 aus
	
	//Arbeitsschleife
	while(1)
	{
		if (!(PINA & (1<<TASTER)))
		{
			//Pr?fen, ob Taster Sx gedr?ckt
			PORTC = (PORTC<<1) | (PORTC>>7); //LED Status um 1 Bit links rotieren
			_delay_ms(T_PRELL);	//Entprellung f?r Tasterschlie?en

			while(!(PINA & (1<<TASTER)));	//warten solange Taster Sx gedr?ckt
			_delay_ms(T_PRELL);	//Entprellung f?r Taster?ffnen
		}
	}//ende Arbeitsschleife
} //ende main