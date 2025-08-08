/*
 * Matura_Timer_1_Counter_LED.c
 *
 * Created: 05.08.2025 09:31:08
 * Author : Adrian
 */ 
#define F_CPU 12000000UL // 12 MHz Systemtakt

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0;

void init_ports()
{
	DDRC = 0xFF; // PortC als Ausgang
	PORTC = 0x00; // LED'S ausschalten
}

void init_timer1()
{
	TCCR1B |= (1 << WGM01); // Timer1 im CTC Modus (Clear Timer on Compare Match)
	// value = F_CPU / Prescaler(1024) ) = 11718.75 Hz
	// OCR1A = value - 1 = 11718
	OCR1A = 11718;
	TIMSK |= (1 << OCIE1A); // Compare Match Interrupt aktiv setzen
	TCCR1B |= (1 << CS00) | (1 << CS02); // 1024 Prescaler
}

ISR(TIMER1_COMPA_vect)
{
	counter++;
	if (counter > 7) // beregenzen auf 3-Bit, da nur 8 LED's vorhanden
	{
		counter = 0;
	}
	PORTC = (1 << counter); // Nur jeweils eine LED aktiv
}

int main(void)
{
    cli(); // interrupts deaktivieren
	init_ports();
	init_timer1();
	sei(); // interrupts aktivieren
    while (1) 
    {
    }
}

