/*
 * FastPWM.c
 *
 * Created: 11.05.2023 15:37:55
 * Author : Adrian
 */ 
#define F_CPU 12000000UL	// quarz frequency

#include <avr/io.h>			// std Input/output lib
#include <avr/interrupt.h>	// std interrupt lib
#include <avr/portpins.h>	// std port and pins lib

void init_ports()
{
	DDRC = 0xFF;			// set all to output
	PORTC |= (1 << PC7);	// Indicator LED - Turn on to check
	
	DDRB |= (1 << PB3);		// signal on PB3
	PORTB &= ~(1 << PB3);	// set PB3 to low (OC0 -> Output) 
}

void init_fast_PWM()
{
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS01) | (1 << CS00);	// fast PWM Mode(WGM00/WGM01), clear OC0 on compare match(COM01)
	OCR0 = 150;																			// Fout = 12Mhz / (64*256) = 732,421875 Hz, if OCR0 gets bigger the pulse width get bigger
}


int main(void)
{
	cli();				// lock the global interrupt
	
	init_ports();		// init the ports
	init_fast_PWM();	// init the fast pwm
    
	sei();				// free the global interrupt
	
	// how to change the pulse width with S0 or S1
	// how to set on the LED's
	
	
    while (1) 
    {
    }
}

