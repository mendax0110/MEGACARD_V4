/*
 * 5.c
 *
 * Created: 05.10.2023 09:48:03
 * Author : Adrian
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LCD_4.h"

// Pinbelegung
#define CLK_PIN   PD3
#define DIR_PIN   PD2
#define LED_PORT  PORTC

// Zählervariable
volatile int16_t count = 0;
volatile uint8_t encoderTicks = 0;
const uint8_t vorteiler = 4;

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

	//wenn drehrichtung geändert, invertiere die Zählrichtung
	if (currentDir != lastDir)
	{
		encoderTicks++;
		if (encoderTicks >= vorteiler)
		{
			if (currentDir) // increment
			{
				count++;
			}
			else
			{
				count--;	// decrement
			}
			encoderTicks = 0; // reset
		}
	}

	lastDir = currentDir;

	PORTC = count;
}

int main(void)
{
	InitPorts();
	lcd_init();

	cli();
	MCUCR |= (1 << ISC11) | (1 << ISC10); // Steigende Flanke erzeugt Interrupt
	GICR |= (1 << INT1); // INT1 aktivieren
	sei(); // Globale Interrupts aktivieren

	while (1)
	{
		lcd_pos(0, 1);
		printf("Position: %d\n", count);
	}
}