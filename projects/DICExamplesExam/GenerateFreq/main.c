/*
 * GenerateFreq.c
 *
 * Created: 17.12.2023 10:54:29
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t toggle = 0;

ISR(TIMER0_COMP_vect)
{
	// Hier wird der Zustand des Pins umgeschaltet
	toggle = !toggle;
	if (toggle)
	{
		PORTB |= (1 << PB3); // Setze Pin PB0
	} 
	else 
	{
		PORTB &= ~(1 << PB3); // Lösche Pin PB0
	}
}

void initPorts()
{
	DDRB |= (1 << PB3); // Setze PB0 als Ausgang
	DDRC = 0xFF;
}

void initTimer0CTC()
{
	TCCR0 |= (1 << WGM01); // CTC-Modus aktivieren
	OCR0 = 116; // Vergleichswert für 200 Hz bei F_CPU = 12 MHz und Prescaler 256
	TIMSK |= (1 << OCIE0); // Aktiviere den Compare Match Interrupt
	TCCR0 |= (1 << CS02); // Setze den Timer-Prescaler auf 256
}

int main(void)
{
	cli();
	initPorts();
	initTimer0CTC();
	sei();

	while (1)
	{
		auto output = DDRB |= (1 << PB3);
		PORTC ^= output;
		_delay_ms(200);
	}
}

