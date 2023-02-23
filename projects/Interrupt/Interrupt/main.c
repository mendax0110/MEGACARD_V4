/*
 * Interrupt.c
 *
 * Created: 26.01.2023 10:10:41
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// Frequenz Quarz

#include <avr/io.h>			// std avr library
#include <util/delay.h>		// std delay lib
#include <avr/portpins.h>	// std port pin lib
#include <avr/interrupt.h>	// std avr interrupt lib

ISR(INT1_vect)
{
	if(PORTC == 0b10000000)
	{
		PORTC |= (1 << PC4);
	}
	else
	{
		PORTC &= 0b10000000;
	}
}

void init_interrupt()		// Interrupt Funktion(um im main aufzurufen)
{
	GICR |= (1 << INT1);	// Interrupt 1 wird freigeschaltet - Auslösen möglich
	MCUCR |= (1 << ISC11);	// Interrupt 1 wird bei fallender Flanke aufgelöst
}

void init_ports()        // Funktion (um im main aufzurufen)
{
	DDRD &= (1<<PD3);					// Input für INT1
	
	DDRA &= ~(1 << PA0);				// PA1, PA0 -> Eingang
	DDRA &= ~(1 << PA1);				// PA1, PA0 -> Eingang
	PORTA |= (1 << PA1)|(1<<PA0);;		// PortA = Pullup  -> auf High setzen
	
	DDRC = 0xFF;						// Port C - Ausgang
	PORTC |= (1 << PC7);				// LED 7 wird gesetzt (1000 0000 -> 0x80)	
}

int main(void)
{
	char keyboard_in = 0x00;    //Variable vom Typ Character -> 8 Bit (1Byte)
	
	cli();						// interrupt sperren
	init_interrupt();
	init_ports();
	sei();						// interrupt freischalten
	
	//PORTC &= ~(1 << PC4);
	
	while (1)
	{
		keyboard_in = PINA;		// Maskierung -> Erzwinge, dass die Bits A4 - A7 = 0 sind
		if ((keyboard_in & (0x01)) == 0x00)
		{
			PORTC = 0x01;
		}
		
		_delay_ms(5000);
		PORTC = (1<<PC7);	
	}
}