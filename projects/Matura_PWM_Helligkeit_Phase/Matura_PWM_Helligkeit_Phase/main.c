/*
 * Matura_PWM_Helligkeit_Phase.c
 *
 * Created: 05.08.2025 11:11:45
 * Author : Adrian
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 128;  // Starthelligkeit 50%

void init_Ports()
{
	DDRB |= (1 << PB3);      // PB3 (OC0) als PWM-Ausgang
	DDRA &= ~((1 << PA0) | (1 << PA1));  // PA0 & PA1 als Eingang
	PORTA |= (1 << PA0) | (1 << PA1);    // Pull-ups aktivieren
}

void init_PWM()
{
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << CS01);  // Phase Correct PWM, Prescaler 8
	OCR0 = OCR0Var;  // Initialer PWM-Wert
}

int main()
{
	init_Ports();
	init_PWM();

	while (1)
	{
		if (!(PINA & (1 << PA0)))
		{
			_delay_ms(20);
			if (!(PINA & (1 << PA0)))
			{
				if (OCR0Var < 255) OCR0Var += 5;  // Helligkeit erhöhen
				while (!(PINA & (1 << PA0)));  // Warte auf Loslassen
				OCR0 = OCR0Var;  // PWM aktualisieren
			}
		}
		if (!(PINA & (1 << PA1)))
		{
			_delay_ms(20);
			if (!(PINA & (1 << PA1)))
			{
				if (OCR0Var > 0) OCR0Var -= 5;  // Helligkeit verringern
				while (!(PINA & (1 << PA1)));  // Warte auf Loslassen
				OCR0 = OCR0Var;  // PWM aktualisieren
			}
		}
	}
}