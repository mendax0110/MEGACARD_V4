/*
 * StopWatchLED1.c
 *
 * Created: 13.06.2023 20:58:13
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/portpins.h>

// globale Variablen für Sekunden, Minuten, Stunden und Tastenstatus
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;
volatile uint8_t s0_Pressed = 0;
volatile uint8_t s1_Pressed = 0;
volatile uint8_t stopwatch_running = 0;

// Interrupt Service Routine für Timer0 Compare Match
ISR(TIMER0_COMP_vect)
{
	if (stopwatch_running)
	{
		seconds++;

		if (seconds >= 60)
		{
			seconds = 0;
			minutes++;

			if (minutes >= 60)
			{
				minutes = 0;
				hours++;

				if (hours >= 24)
				{
					hours = 0;
				}
			}
		}
	}
}

// Timer0-Initialisierung, 8-Bit, CTC, Prescaler 1024
void init_Timer0()
{
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (1 << CS00);

	OCR0 = 150;

	TIMSK |= (1 << OCIE0);
}

// Ports initialisieren
void init_Ports()
{
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);  // LED PC0, PC1 und PC2 als Ausgabe festlegen

	DDRA &= ~(1 << PA0) & ~(1 << PA1);  // Tasten PA0 und PA1 als Eingabe festlegen

	PORTA |= (1 << PA0) | (1 << PA1);   // Pull-Up-Widerstände für Tasten aktivieren
}

// Stoppuhr starten
void start_stopwatch()
{
	stopwatch_running = 1;
}

// Stoppuhr stoppen
void stop_stopwatch()
{
	stopwatch_running = 0;
}

// Stoppuhr zurücksetzen
void reset_stopwatch()
{
	stopwatch_running = 0;
	seconds = 0;
	minutes = 0;
	hours = 0;
}

int main(void)
{
	cli();          // Interrupts deaktivieren
	init_Ports();   // Ports initialisieren
	init_Timer0();  // Timer0 initialisieren
	sei();          // Interrupts aktivieren

	while (1)
	{
		// LED PC0 aktualisieren
		if (seconds % 2 == 0)
		PORTC |= (1 << PC0);
		else
		PORTC &= ~(1 << PC0);

		// LED PC1 aktualisieren
		if (minutes % 2 == 0)
		PORTC |= (1 << PC1);
		else
		PORTC &= ~(1 << PC1);

		// LED PC2 aktualisieren
		if (hours % 2 == 0)
		PORTC |= (1 << PC2);
		else
		PORTC &= ~(1 << PC2);

		// Überprüfen, ob Tasten gedrückt sind
		if (!(PINA & (1 << PA0)))
		{
			_delay_ms(50);
			if (!(PINA & (1 << PA0)))
			{
				if (stopwatch_running)
				{
					stop_stopwatch();
				}
				else
				{
					start_stopwatch();
				}
				_delay_ms(200);
			}
		}

		// Überprüfen, ob Tasten gedrückt sind
		if (!(PINA & (1 << PA1)))
		{
			_delay_ms(50);
			if (!(PINA & (1 << PA1)))
			{
				reset_stopwatch();
				_delay_ms(200);
			}
		}
	}
}
