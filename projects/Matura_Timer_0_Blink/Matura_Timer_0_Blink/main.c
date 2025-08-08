/*
 * Matura_Timer_0_Blink.c
 *
 * Created: 05.08.2025 08:47:34
 * Author : Adrian
 */ 
#define F_CPU 12000000UL // CPU Takt

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t timerCount = 0;

void init_ports()
{
	DDRC |= 0xFF;	// Port C als Ausgang
	PORTC = 0x00;	// Alle LED's ausschalten
}

void init_timer0()
{
	TCCR0 |= (1 << CS00) | (1 << CS02); // Prescaler 1024
	TIMSK |= (1 << TOIE0); // Timer0 Overflow Interrupt aktiv
	TCNT0 = 0; // Startwert
}

/************************************************************************/
/* F_Timer = F_CPU / Prescaler = 11718.75Hz
   t_Overflow = 256 / F_Timer = 0.02184 = 21.84 ms
   t60_Overflows = 60 * 21.84ms = 0.0131072ms -> 1.31 Sekunden                                                                */
/************************************************************************/
ISR(TIMER0_OVF_vect)
{
	timerCount++;
	if (timerCount >= 60)
	{
		PORTC ^= 0xFF;
		timerCount = 0;
	}
}

int main(void)
{
	cli();
	init_ports();
	init_timer0();
	sei();
	
    
    while (1) 
    {
		
    }
}

