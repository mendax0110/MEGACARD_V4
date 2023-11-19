/*
 * 1_Aufgabe f.c
 *
 * Created: 21.10.2023 19:23:59
 * Author : Adrian
 */ 
#define F_CPU 12000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(TIMER0_COMP_vect) // Overflow durch vect ersetzen -> CTC Mode
{
	PORTC ^= 0x01;
	_delay_us(10); // Verzögerung von 10 Mikrosekunden
}

void init()
{
	DDRC |= 0xFF; // LEDs
	PORTC = 0;
	DDRA &= 0xF0; // Taster
	PORTA |= 0x0F; // Pull-up

	TCCR0 |= 1 << CS00 | 1 << WGM01;

	TIMSK |= 1 << OCIE0; // Verwende OCIE0 für den Compare Match Interrupt
	OCR0 = 120 - 1; // Grenze setzen durch OCR0
}

int main(void)
{
	init();
	sei();
	while (1)
	{
	}
	return 0;
}

