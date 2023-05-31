
/*
 * PWM.h
 *
 * Created: 24.05.2023 17:01:06
 *  Author: Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>
#include <util/delay.h>

volatile uint8_t OCR0Var = 0;

ISR(TIMER0_COMP_vect)
{
	OCR0 = OCR0Var;			// for PWM via S0 and S1
	PORTC |= (1 << PC4);	// set LED
}

ISR(TIMER0_OVF_vect)
{
	PORTC &= ~(1 << PC4);	// reset LED
}

// initialize ports
void init_Ports()
{
	DDRC = 0xFF;
	
	PORTC ^= (1 << PC7);	// indicator LED
	
	DDRB |= (1 << PB3);		// signal output
	
	// for S0 and S1
	DDRA &= ~((1 << PA0)|(1 << PA1));
	PORTA |= ((1 << PA0)|(1 << PA1));
}

// initialize fast PWM
void init_fast_PWM()
{
	PORTC ^= (1 << PC6);	// indicator LED
	
	TCCR0 |= (1 << WGM00)|(1 << WGM01)|(1 << CS00)|(1 << COM01); // PWM Mode
	
	OCR0 = OCR0Var; // for PWM via S0 and S1
	
	TIMSK |= (1 << OCIE0)|(1 << TOIE0); // software casting PWM Signal to the desired LED
}

int main(void)
{
	cli();  // disable global interrupts
	init_Ports();       // initialize ports
	init_fast_PWM();    // initialize fast PWM    
	sei();  // enable global interrupts
	
	while(1)
	{
        // for S0 and S1, if pressed, increase or decrease the PWM value
		if((PINA & (1 << PA0)) == 0)
		{
			OCR0Var += 25;
			_delay_ms(200);
		}
		else if((PINA & (1 << PA1)) == 0)
		{
			OCR0Var -= 25;
			_delay_ms(200);
		}
	}
}