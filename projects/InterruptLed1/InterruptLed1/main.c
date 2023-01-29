/*
 * InterruptLed1.c
 *
 * Created: 29.01.2023 10:05:00
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// Quarzfrequenz UL Unsigned Long
#include <avr/io.h>			// Library Ein/Ausgabe - Ports
#include <avr/interrupt.h> // Library für Interrupts
#include <util/delay.h>		// Delay Library
#include <avr/portpins.h>	// Library für portpins

volatile uint8_t flag = 0;

void init_ports()
{
	DDRB = 0xFF;		//PORTB als Ausgang
	PORTB = 0x00;		//alle Bits auf 0
	
	DDRA = 0x00;		//PORTA als Eingang
	PORTA = 0x01;		//PA0 als Pull-up Eingang

	GICR = (1 << INT0);						//Interrupt 0 aktivieren
	MCUCR = (1 << ISC01) | (1 << ISC00);	//Interrupt 0 auf steigende Flanke
	sei();									//Interrupts global aktivieren
}

//Interrupt Service Routine
ISR(INT0_vect) 
{
	flag = 1;
}

int main(void)
{
	//Ports im main initialisieren
	init_ports();
	
	while (1)
	{
		if(flag == 1)
		{
			PORTB = (1<<PB0);
			flag = 0;
		}
	}	_delay_ms(1000);
}

