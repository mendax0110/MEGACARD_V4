/*
 * InterruptsDrehgeber.c
 *
 * Created: 05.10.2023 08:29:16
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// pinbelegung
#define CLK_PIN   PD3
#define DIR_PIN   PD2
#define LED_PORT  PORTC

// Zählervariable
volatile uint16_t count = 0;

//init ports
void InitPorts()
{
	// Port D: CLK-Pin und DIR-Pin als Eingänge
	DDRD &= ~(1 << CLK_PIN);
	DDRD &= ~(1 << DIR_PIN);

	// Port B: LEDs als Ausgänge
	DDRC = 0xFF;
}

// INT1 ISR
ISR(INT1_vect)
{
	// steigenden Flanke erhöhen der Zählvariable
	count++;
	
	// ouput binät
	for (int i = 0; i < 8; i++)
	{
		 if (count & (1 << i)) 
		 {
			 LED_PORT |= (1 << i); // son
		 } 
		 else 
		 {
			 LED_PORT &= ~(1 << i); // clear
		 }
	 }
}

int main(void)
{
	InitPorts();
	
	cli();
	MCUCR |= (1 << ISC11) | (1 << ISC10); // steigende Flanke erzeugt Interrupt
	GICR |= (1 << INT1); // INT1 aktivieren
	sei(); // Globale Interrupts aktivieren

	while (1)
	{
	}
}

