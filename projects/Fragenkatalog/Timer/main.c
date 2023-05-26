#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t TCNT0Var = 106;
volatile uint8_t softwareprescaler = 0;

ISR(TIMER0_OVF_vect)
{
	/*
	* berechnung TCNTO: F_CPU/(2*F_OUT) = primzahlzerlungszahl solange bis dividenen geben -> vorteiler , 256 - restzahl = TCNT0
	*/
	TCNT0 = TCNT0Var;
	
	softwareprescaler++;
	
	if(softwareprescaler >= 25)	// 25 Hz on LED
	{
		PORTC ^= (PC1);
		softwareprescaler = 0;
	}
}

void init_Ports()
{
	DDRC = 0xFF;
	
	DDRB |= (1 << PB3);	// output for signal
}

void init_timer0()
{
	TCCR0 &= ~(1 << WGM00);		// normal mode
	TCCR0 &= ~(1 << WGM01);		// normal mode
	TCCR0 |= (1 << COM00)|(1 << CS00)|(1 << CS01);	// set 64 prescaler
	
	TCNT0 = TCNT0Var;
	OCR0 = 255;			//cross reference to get 625Hz on PB3
	
	TIMSK |= (1 << TOIE0);	// register
}

int main(void)
{
	cli();
	init_Ports();
	init_timer0();
	sei();
	
	while(1)
	{
		
	}
}