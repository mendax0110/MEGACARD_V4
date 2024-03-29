/*
 * 3.c
 *
 * Created: 05.10.2023 09:37:59
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

// Z�hlervariable
volatile uint16_t count = 0;

//init ports
void InitPorts()
{
	// Port D: CLK-Pin und DIR-Pin als Eing�nge
	DDRD &= ~(1 << CLK_PIN);
	DDRD &= ~(1 << DIR_PIN);

	// Port B: LEDs als Ausg�nge
	DDRC = 0xFF;
}

// INT1 ISR
ISR(INT1_vect)
{
	// steigenden Flanke erh�hen der Z�hlvariable
	count++;
	PORTC=count;
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

