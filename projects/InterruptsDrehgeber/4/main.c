/*
 * 4.c
 *
 * Created: 05.10.2023 09:38:38
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

// Pinbelegung
#define CLK_PIN   PD3
#define DIR_PIN   PD2
#define LED_PORT  PORTC

// Zählervariable
volatile int16_t count = 0;

// Init Ports
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
	static uint8_t lastDir = 0; // Speichere den vorherigen Zustand des DIR-Signals
	uint8_t currentDir = PIND & (1 << DIR_PIN); // Lese den aktuellen Zustand des DIR-Signals

	// Wenn die Drehrichtung geändert hat, invertiere die Zählrichtung

	if (currentDir) // Wenn "dir" gesetzt ist, zähle aufwärts
	{
		count++;
	}
	else
	{
		count--;
	}

	lastDir = currentDir;

	PORTC = count;
}

int main(void)
{
	InitPorts();

	cli();
	MCUCR |= (1 << ISC11) | (1 << ISC10); // Steigende Flanke erzeugt Interrupt
	GICR |= (1 << INT1); // INT1 aktivieren
	sei(); // Globale Interrupts aktivieren

	while (1)
	{
	}
}


