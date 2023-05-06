/*
 * PWMFrequency.c
 *
 * Created: 06.05.2023 11:10:15
 * Author : Adrian
 */ 
#define F_CPU 12000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/portpins.h>

ISR(TIMER0_COMP_vect)
{
	// empty
}

void inint_ports()
{
	DDRB |= (1 << PB3);	// set PB3 as ouput
	DDRC |= (1 << PC7);
}

void init_timer0_pwm()
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // COM = non inverting, fast pwm, prescaler
	OCR0 = 148;	// set PWM duty cycle to 58 % ( 148/255)
}

int main(void)
{
	
	cli();	// diable global interrupts
	
	inint_ports();		// init the ports method
	init_timer0_pwm();	// init the timer0 method
	
	sei();	// enable global interrupts
	
	while(1)
	{
		// do nothing
	}
}