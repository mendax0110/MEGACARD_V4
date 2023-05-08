/*
 * InitFunctions.c
 *
 * Created: 08.05.2023 20:28:21
 *  Author: Adrian
 */
#include "initFunctions.h"
#include <avr/io.h>
#include <util/delay.h>

void init_ports(void)
{
	DDRB |= (1 << PB3);     // set PB3 as ouput
	//DDRC |= (1 << PC7);
	DDRC = 0xFF;    // set all pins of PORTB as output
}

void init_timer0_pwm(void)
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01); // COM = non inverting, fast pwm, prescaler
	OCR0 = 148; // set PWM duty cycle to 58 % ( 148/255)
}