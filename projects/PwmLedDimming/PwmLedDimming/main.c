/*
 * PwmLedDimming.c
 *
 * Created: 27.05.2023 20:17:00
 * Author : Adrian
 */
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

// Variable zur Steuerung des PWM-Werts
volatile uint8_t OCR0Var = 0;

// Timer 0 Compare-Match Interrupt Service Routine
ISR(TIMER0_COMP_vect)
{
	OCR0 = OCR0Var;
	PORTC |= (1 << PC4); // Schalte den Ausgang für die LED ein
}

// Timer 0 Overflow Interrupt Service Routine
ISR(TIMER0_OVF_vect)
{
	PORTC &= ~(1 << PC4); // Schalte den Ausgang für die LED aus
}

// Funktion zur Initialisierung der Ports
void init_Ports()
{
	DDRC = 0xFF; // Setze Port C als Ausgangsport für die LED
	DDRB |= (1 << PB3); // Setze PB3 als Ausgangsport für den PWM-Ausgang
	
	DDRA &= ~((1 << PA0)|(1 << PA1)); // Setze PA0 und PA1 als Eingänge
	PORTA |= ((1 << PA0)|(1 << PA1)); // Aktiviere Pull-Up-Widerstände für PA0 und PA1
}

// Funktion zur Initialisierung des PWM
void init_PWM()
{
	TCCR0 |= (1 << WGM00)|(1 << WGM01)|(1 << CS00)|(1 << COM01); // Fast-PWM-Modus, Prescaler auf 1, non-inverting PWM
	
	OCR0 = OCR0Var; // Setze den Anfangswert für den PWM-Duty-Cycle
	
	TIMSK |= (1 << TOIE0)|(1 << OCIE0); // Aktiviere Timer 0 Overflow- und Compare-Match-Interrupts
}

int main(void)
{
	cli(); // Deaktiviere Interrupts während der Initialisierung
	init_Ports();
	init_PWM();
	sei(); // Aktiviere Interrupts
	
	while(1)
	{
		if((PINA & (1 << PC0)) == 0) // Überprüfe, ob der Taster an PA0 gedrückt ist
		{
			OCR0Var += 1; // Erhöhe den PWM-Wert
			_delay_ms(10); // Warte für eine kurze Zeit zur Entprellung
		}
		else if((PINA & (1 << PA1)) == 0) // Überprüfe, ob der Taster an PA1 gedrückt ist
		{
			OCR0Var -= 1; // Verringere den PWM-Wert
			_delay_ms(10); // Warte für eine kurze Zeit zur Entprellung
		}
		
		if(OCR0Var >= 255) // Begrenze den PWM-Wert auf 253
		{
			OCR0Var = 253;
		}
		else if(OCR0Var == 0) // Stelle sicher, dass der PWM-Wert nicht 0 ist
		{
			OCR0Var = 1;
		}
	}
}
