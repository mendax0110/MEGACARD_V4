/*
 * Matura_Interrupts.c
 *
 * Created: 06.08.2025 11:51:28
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

void init_ports()
{
	DDRC |= (1 << PC0);		// PC0 als Ausgang setzen
	PORTC &= ~(1 << PC0);	// PC0 LED ausschalten
	
	PORTD |= (1 << PD2); // internen Pull-Up aktiv
}

void init_interrupt_0()
{
	MCUCR |= (1 << ISC01) | (1 << ISC00); // INT0 trigger auf steigende Flanke
	GICR |= (1 << INT0); // aktivieren von INT0 interrupt
}

ISR(INT0_vect)
{
	PORTC ^= (1 << PC0); // toggeln von LED an PC0
}

int main(void)
{
    cli(); // deaktivieren global interrupt
	init_ports();
	init_interrupt_0();
	sei(); // aktivieren global interrupt
	
    while (1)
    {
		
    }
}

